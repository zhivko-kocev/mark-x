#include "utils.h"
#include <ctype.h>
#include <jansson.h>
#include <string.h>
#include <linux/limits.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <libconfig.h>
#define MAX_NAME 1024
#define MAX_BACKEND 1024
#define MAX_FRONTEND 1024
#define PATH_MAX 4096
#define BUFFER_SIZE 4096

int populateExecutablePath(char *execPath, size_t size)
{

    if (readlink("/proc/self/exe", execPath, size) == -1)
    {
        perror("readlink");
        return 1;
    }

    char *end = strrchr(execPath, '/');
    *end = '\0';

    return 0;
}

char *getJsonContent()
{
    size_t buffer_size = BUFFER_SIZE;
    char *buffer = malloc(buffer_size * sizeof(char));
    if (!buffer)
    {
        perror("Memory allocation failed");
        return NULL;
    }

    size_t total_length = 0;

    while (fgets(buffer + total_length, (int)buffer_size - (int)total_length, stdin) != NULL)
    {
        total_length += strlen(buffer + total_length);

        if (total_length >= buffer_size - 1)
        {
            buffer_size *= 2;
            char *new_buffer = realloc(buffer, buffer_size);
            if (!new_buffer)
            {
                perror("Memory allocation failed");
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
        }
    }

    buffer[total_length] = '\0';

    return buffer;
}

int populateProjectDetails(char *jsonString, Project *project)
{
    json_error_t error;
    json_t *root = json_loads(jsonString, 0, &error);

    if (!root)
    {
        printf("Error parsing JSON: %s\n", error.text);
        return 1;
    }

    project->projectName = strdup(json_string_value(json_object_get(root, "projectName")));
    project->frontendType = strdup(json_string_value(json_object_get(root, "frontendType")));
    project->backendType = strdup(json_string_value(json_object_get(root, "backendType")));

    const json_t *models = json_object_get(root, "models");
    if (!json_is_array(models))
    {
        printf("Error: Models should be an array\n");
        json_decref(root);
        return 1;
    }

    const size_t modelCount = json_array_size(models);
    project->models = malloc(modelCount * sizeof(Model));
    project->modelCount = modelCount;

    for (size_t index = 0; index < modelCount; index++)
    {
        const json_t *model = json_array_get(models, index);
        const json_t *attributes = json_object_get(model, "attributes");

        project->models[index].modelName = strdup(json_string_value(json_object_get(model, "modelName")));
        project->models[index].ModelName = strdup(json_string_value(json_object_get(model, "ModelName")));

        const size_t attrCount = json_array_size(attributes);
        project->models[index].attributes = malloc(attrCount * sizeof(Attribute));
        project->models[index].attrCount = attrCount;

        for (size_t attr_index = 0; attr_index < attrCount; attr_index++)
        {
            const json_t *attribute = json_array_get(attributes, attr_index);

            project->models[index].attributes[attr_index].name = strdup(
                json_string_value(json_object_get(attribute, "name")));

            project->models[index].attributes[attr_index].Name = strdup(
                json_string_value(json_object_get(attribute, "Name")));

            project->models[index].attributes[attr_index].type = strdup(
                json_string_value(json_object_get(attribute, "type")));
        }
    }

    json_decref(root);

    return 0;
}

int createProjectDirectories(char *execPath, const Project *project)
{
    char cwd[PATH_MAX];
    getcwd(cwd, PATH_MAX);

    char newDirPath[PATH_MAX + MAX_NAME];
    sprintf(newDirPath, "%s/%s", cwd, project->projectName);
    if (mkdir(newDirPath, 0777))
    {
        perror("mkdir");
        return 1;
    }
    char setupPath[PATH_MAX + MAX_NAME + MAX_FRONTEND + MAX_BACKEND];
    sprintf(setupPath, "%s/mark_xi/setup.sh %s %s %s", execPath, project->projectName, project->frontendType,
            project->backendType);

    return system(setupPath);
}

char *getModelJsonString(Model *model)
{
    json_t *new_root = json_object();
    if (!new_root)
    {
        fprintf(stderr, "Failed to create new JSON object\n");
        return NULL;
    }

    json_object_set_new(new_root, "ModelName", json_string(model->modelName));
    json_object_set_new(new_root, "modelName", json_string(model->ModelName));

    json_t *attrs_array = json_array();
    for (int i = 0; i < model->attrCount; i++)
    {
        json_t *attr_obj = json_object();
        json_object_set_new(attr_obj, "name", json_string(model->attributes[i].name));
        json_object_set_new(attr_obj, "Name", json_string(model->attributes[i].Name));
        json_object_set_new(attr_obj, "type", json_string(model->attributes[i].type));

        json_array_append_new(attrs_array, attr_obj);
    }

    json_object_set_new(new_root, "attributes", attrs_array);

    char *newJsonString = json_dumps(new_root, 0);

    json_decref(new_root);

    return newJsonString; // Remember to free this string after usage
}

int populateConfig(char *execPath, const Project *project, ConfigInfo *configInfo)
{
    config_t cfg;
    const char *root_path;
    const char *extension;
    config_init(&cfg);

    char configPath[PATH_MAX];
    sprintf(configPath, "%s/mark_xi/templates/%s-templates/%s.conf", execPath, project->backendType, project->backendType);

    if (!config_read_file(&cfg, configPath))
    {
        printf("Failed to read config file\n");
        return 1;
    }

    if (!config_lookup_string(&cfg, "Root.path", &root_path))
    {
        printf("Failed to get root path\n");
        return 1;
    }
    configInfo->rootPath = strdup(root_path);

    if (!config_lookup_string(&cfg, "Extension.type", &extension))
    {
        printf("Failed to get extension type\n");
        return 1;
    }
    configInfo->extension = strdup(extension);

    const config_setting_t *dirSetting = config_lookup(&cfg, "Directories");
    if (dirSetting == NULL)
    {
        printf("Failed to get Directories setting\n");
        return 1;
    }
    configInfo->dirSettingCount = config_setting_length(dirSetting);
    configInfo->dirSetting = malloc(configInfo->dirSettingCount * sizeof(char *));

    for (int i = 0; i < configInfo->dirSettingCount; ++i)
    {
        const config_setting_t *setting = config_setting_get_elem(dirSetting, i);
        configInfo->dirSetting[i] = strdup(config_setting_get_string(setting));
    }

    const config_setting_t *fileSetting = config_lookup(&cfg, "Files");
    if (fileSetting == NULL)
    {
        printf("Failed to get Directories setting\n");
        return 1;
    }
    configInfo->fileSettingCount = config_setting_length(fileSetting);
    configInfo->fileSetting = malloc(configInfo->fileSettingCount * sizeof(char *));

    for (int i = 0; i < configInfo->fileSettingCount; ++i)
    {
        const config_setting_t *setting = config_setting_get_elem(fileSetting, i);
        configInfo->fileSetting[i] = strdup(config_setting_get_string(setting));
    }

    if (configInfo->dirSettingCount != configInfo->fileSettingCount)
    {
        printf("Directories count does not match file settings\n");
        return 1;
    }

    config_destroy(&cfg);

    return 0;
}

void freeProject(Project *project)
{
    free(project->projectName);
    free(project->frontendType);
    free(project->backendType);

    for (size_t i = 0; i < project->modelCount; i++)
    {
        for (size_t j = 0; j < project->models[i].attrCount; j++)
        {
            free(project->models[i].attributes[j].Name);
            free(project->models[i].attributes[j].name);
            free(project->models[i].attributes[j].type);
            free(project->models[i].modelName);
            free(project->models[i].ModelName);
        }
        free(project->models[i].attributes);
    }

    free(project->models);
}

void freeConfig(ConfigInfo *configInfo)
{

    free(configInfo->rootPath);
    free(configInfo->extension);
    for (size_t i = 0; i < configInfo->dirSettingCount; i++)
    {
        free(configInfo->dirSetting[i]);
    }

    for (size_t i = 0; i < configInfo->fileSettingCount; i++)
    {
        free(configInfo->fileSetting[i]);
    }

    free(configInfo->dirSetting);
    free(configInfo->fileSetting);
}