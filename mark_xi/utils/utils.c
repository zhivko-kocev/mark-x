#include "utils.h"

#include <ctype.h>
#include <jansson.h>
#include <string.h>
#include <linux/limits.h>
#include <stdio.h>

void fillProjectDetails(Project *project, const char *jsonString) {
    json_error_t error;
    json_t *root = json_loads(jsonString, 0, &error);

    if (!root) {
        printf("Error parsing JSON: %s\n", error.text);
        return;
    }

    project->projectName = strdup(json_string_value(json_object_get(root, "projectName")));
    project->frontendType = strdup(json_string_value(json_object_get(root, "frontendType")));
    project->backendType = strdup(json_string_value(json_object_get(root, "backendType")));

    const json_t *models = json_object_get(root, "models");
    if (!json_is_array(models)) {
        printf("Error: Models should be an array\n");
        json_decref(root);
        return;
    }

    const size_t modelCount = json_array_size(models);
    project->models = malloc(modelCount * sizeof(Model));
    project->modelCount = modelCount;

    for (size_t index = 0; index < modelCount; index++) {
        const json_t *model = json_array_get(models, index);
        const json_t *attributes = json_object_get(model, "attributes");

        project->models[index].modelName = strdup(json_string_value(json_object_get(model, "modelName")));

        const size_t attrCount = json_array_size(attributes);
        project->models[index].attributes = malloc(attrCount * sizeof(Attribute));
        project->models[index].attrCount = attrCount;

        for (size_t attr_index = 0; attr_index < attrCount; attr_index++) {
            const json_t *attribute = json_array_get(attributes, attr_index);

            project->models[index].attributes[attr_index].name = strdup(
                json_string_value(json_object_get(attribute, "name")));

            project->models[index].attributes[attr_index].type = strdup(
                json_string_value(json_object_get(attribute, "type")));
        }
    }

    json_decref(root);
}

void writeModelsJSON(const char *jsonString, char *filePath) {
    json_error_t error;
    json_t *root = json_loads(jsonString, 0, &error);

    if (!root) {
        printf("Error parsing JSON: %s\n", error.text);
        return;
    }

    const json_t *models = json_object_get(root, "models");
    const size_t modelsCount = json_array_size(models);

    for (size_t i = 0; i < modelsCount; ++i) {
        json_t *new_root = json_object();
        if (!new_root) {
            fprintf(stderr, "Failed to create new JSON object\n");
            json_decref(root);
            return;
        }
        const json_t *model = json_array_get(models, i);
        json_t *name = json_object_get(model, "modelName");
        json_t *attrs = json_object_get(model, "attributes");
        json_object_set(new_root, "modelName", name);
        json_object_set(new_root, "attributes", attrs);

        const char *modelName = json_string_value(json_object_get(model, "modelName"));
        char modelPath[PATH_MAX];
        sprintf(modelPath, "%s/models/%s.json", filePath, modelName);

        if (json_dump_file(new_root, modelPath, JSON_INDENT(4)) != 0) {
            fprintf(stderr, "Failed to write new JSON to file\n");
            json_decref(root);
            json_decref(new_root);
            return;
        }
        json_decref(new_root);
    }

    json_decref(root);
}

void writeToFile(const char *fullPath, char *templatePath, const char *filePath, char *modelName) {
    char fullCommand[PATH_MAX];
    sprintf(fullCommand, "cat %s | %s/tt %s/models/%s.json > %s", templatePath, filePath, filePath, modelName,
            fullPath);
    system(fullCommand);
}
