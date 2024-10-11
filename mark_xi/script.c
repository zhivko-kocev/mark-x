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
    if (!strcmp(content, "err")) {
        printf("Failed to load json content\n");
        return 1;
    }

    Project project;
    if (populateProjectDetails(&project, content)) {
        printf("Failed to load project details\n");
        return 1;
    }

    createProjectDirectory(project.projectName);

    char setupPath[PATH_MAX + MAX_NAME + MAX_FRONTEND + MAX_BACKEND];
    sprintf(setupPath, "%s/setup.sh %s %s %s", execPath, project.projectName, project.frontendType,
            project.backendType);
    system(setupPath);

    if (writeModelsJSON(content, execPath)) {
        printf("Failed to write models to JSON\n");
        return 1;
    }
    free(content);

    ConfigInfo configInfo;
    if (populateConfig(execPath, &project, &configInfo)) {
        printf("Failed to load config info\n");
        return 1;
    }

    if (writeToFiles(execPath, &project, &configInfo)) {
        printf("Failed to write the templates to the files!\n");
        return 1;
    }

    return 0;
}
