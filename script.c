#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "structs/project.h"
#include "structs/config_info.h"
#include "utils/utils.h"
#define MAX_PATH 4096
#define BUFFER_SIZE 4096
#define MAX_PROJECT_NAME 200
#define MAX_MODEL_NAME 150
#define MAX_BACKEND 100
#define MAX_FRONTEND 100
#define MAX_CONFIG_NAME 100

int main()
{
    clock_t start_time = clock();

    char execPath[MAX_PATH];
    if (populateExecutablePath(execPath, MAX_PATH))
    {
        printf("Failed to load executable path\n");
        return 1;
    }

    char *content = getJsonContent();
    if (!content)
    {
        printf("Failed reading from stdin\n");
        return 1;
    }

    Project project;
    if (populateProjectDetails(content, &project))
    {
        printf("Failed to load project details\n");
        return 1;
    }

    if (createProjectDirectories(execPath, &project))
    {
        printf("Failed to create project directory\n");
        return 1;
    }

    ConfigInfo configInfo;
    if (populateConfig(execPath, &project, &configInfo))
    {
        printf("Failed to load config info\n");
        return 1;
    }

    // traverse for all the models in the project and all the directories that need to be populated
    for (size_t i = 0; i < project.modelCount; ++i)
    {
        for (size_t j = 0; j < configInfo.dirSettingCount; ++j)
        {

            // the full path to a given file in the backend directory
            char fullPath[MAX_PATH + MAX_CONFIG_NAME + MAX_CONFIG_NAME + MAX_MODEL_NAME + MAX_CONFIG_NAME + MAX_CONFIG_NAME];
            snprintf(fullPath, sizeof(fullPath), "./%s%s%s/%s%s%s",
                     project.projectName,
                     configInfo.rootPath,
                     configInfo.dirSetting[j],
                     project.models[i].ModelName,
                     !strcmp(configInfo.fileSetting[j], "Model") ? "" : configInfo.fileSetting[j],
                     !strcmp(configInfo.fileSetting[j], "Template") || !strcmp(configInfo.fileSetting[j], "View") ? ".html" : configInfo.extension);

            // path to the current template file
            char templatePath[MAX_PATH + MAX_BACKEND + MAX_CONFIG_NAME];
            snprintf(templatePath, sizeof(templatePath), "%s/mark_xi/templates/%s-templates/%s.tt",
                     execPath,
                     project.backendType,
                     configInfo.fileSetting[j]);

            // get the current model attributes as a json string
            char *jsonString = getModelJsonString(&project.models[i]);

            // command to call the template engine and write the content to fullPath to the current file
            char fullCommand[sizeof(templatePath) + sizeof(fullPath) + MAX_PATH + BUFFER_SIZE];
            sprintf(fullCommand, "(cat %s;echo 'razdeli';echo '%s') | %s/mark_xi/mu.js > %s",
                    templatePath,
                    jsonString,
                    execPath,
                    fullPath);

            if (system(fullCommand))
            {
                printf("Failed to execute command\n");
                return 1;
            }
        }
    }

    free(content);
    freeProject(&project);
    freeConfig(&configInfo);

    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    printf("Done in %f seconds\n", elapsed_time);

    return 0;
}
