#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "structs/project.h"
#include "structs/config_info.h"
#include "utils/utils.h"

#define MAX_NAME 1024
#define MAX_BACKEND 1024
#define MAX_FRONTEND 1024

int main() {
    char execPath[PATH_MAX];
    if (populateExecutablePath(execPath,PATH_MAX)) {
        printf("Failed to load executable path\n");
        return 1;
    }

    char *content = getJsonContent(execPath);
    if (!content) {
        printf("Failed reading from stdin\n");
        return 1;
    }

    Project project;
    if (populateProjectDetails(&project, content)) {
        printf("Failed to load project details\n");
        return 1;
    }
    if (createProjectDirectories(execPath, &project)) {
        printf("Failed to create project directory\n");
        return 1;
    }

    ConfigInfo configInfo;
    if (populateConfig(execPath, &project, &configInfo)) {
        printf("Failed to load config info\n");
        return 1;
    }

    for (size_t i = 0; i < project.modelCount; ++i) {
        for (size_t j = 0; j < configInfo.dirSettingCount; ++j) {
            char fullPath[PATH_MAX + PATH_MAX];

            sprintf(fullPath, "./%s%s%s/%s%s%s", project.projectName, configInfo.rootPath,
                    configInfo.dirSetting[j], project.models[i].ModelName,
                    !strcmp(configInfo.fileSetting[j], "Model") ? "" : configInfo.fileSetting[j],
                    !strcmp(configInfo.fileSetting[j], "Template") || !strcmp(configInfo.fileSetting[j], "View")
                        ? ".html"
                        : configInfo.extension);

            char templatePath[PATH_MAX + PATH_MAX + MAX_BACKEND];
            sprintf(templatePath, "%s/templates/%s-templates/%s.tt", execPath, project.backendType,
                    configInfo.fileSetting[j]);

            char *jsonString = getModelJSON(content, i);

            char fullCommand[PATH_MAX * 8 + MAX_BACKEND];
            sprintf(fullCommand, "(cat %s;echo 'razdeli';echo '%s') | %s/mu.js > %s", templatePath, jsonString,
                    execPath,
                    fullPath);
            if (system(fullCommand)) {
                printf("Failed to execute command\n");
                return 1;
            }
        }
    }

    return 0;
}
