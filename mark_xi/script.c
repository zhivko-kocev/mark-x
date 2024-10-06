#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include "structs/project.h"
#include "utils/utils.h"

int main(const int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [JSON String]\n", argv[0]);
        return 1;
    }

    const char *jsonString = argv[1];

    Project project;
    fillProjectDetails(&project, jsonString);

    char dirPath[PATH_MAX];
    const char *directory = strrchr(__FILE__, '/');

    strncpy(dirPath, __FILE__, directory - __FILE__);


    const char *name = project.projectName;
    const char *frontend = project.frontendType;
    const char *backend = project.backendType;
    const size_t modelCount = project.modelCount;
    const Model *models = project.models;

    char cwd[PATH_MAX];
    getcwd(cwd, PATH_MAX);

    char backendDir[PATH_MAX + strlen(cwd) + strlen(name) + 2];
    sprintf(backendDir, "%s/%s/backend/src/main/java/com/example/backend", cwd, name);


    createProject(dirPath, cwd, name, frontend, backend, backendDir);

    for (size_t i = 0; i < modelCount; i++) {
        createRestController(backendDir, &models[i]);
        createService(backendDir, &models[i]);
        createRepository(backendDir, &models[i]);
        createModels(backendDir, &models[i]);
    }

    return 0;
}
