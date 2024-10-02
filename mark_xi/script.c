#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "structs/project.h"
#include "utils/utils.h"

int main(const int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [JSON String]\n", argv[0]);
        return 1;
    }

    char *jsonString = argv[1];

    Project project;
    getProjectDetails(&project, jsonString);

    char *dirPath = getDirPath(__FILE__);


    const char *name = project.projectName;
    const char *frontend = project.frontendType;
    const char *backend = project.backendType;
    size_t modelCount = project.modelCount;
    Model *models = project.models;

    char *cwd = malloc(PATH_MAX);
    getcwd(cwd, PATH_MAX);

    char *backendDir = malloc(PATH_MAX);
    sprintf(backendDir, "%s/%s/backend/src/main/java/com/example/backend", cwd, name);


    createProject(dirPath, cwd, name, frontend, backend,backendDir);
    for (size_t i = 0; i < modelCount; i++) {
        createRestController(backendDir,&models[i]);
        createService(backendDir,&models[i]);
        createRepository(backendDir,&models[i]);
    }

    free(dirPath);
    free(cwd);
    free(backendDir);
    return 0;
}
