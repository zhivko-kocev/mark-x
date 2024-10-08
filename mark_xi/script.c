#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "structs/project.h"
#include "utils/utils.h"
#include <sys/stat.h>

int main() {
    char filePath[1024];
    const ssize_t count = readlink("/proc/self/exe", filePath, 1024);

    if (count == -1) {
        perror("readlink");
    }

    filePath[count] = '\0';
    char *end = strrchr(filePath, '/');
    *end = '\0';

    char jsonPath[PATH_MAX];
    sprintf(jsonPath, "%s/data.json", filePath);

    FILE *file = fopen(jsonPath, "r");
    if (file == NULL) {
        perror("File not found\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    const long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = malloc(fileSize * sizeof(char));
    if (!content) {
        perror("Memory allocation failed\n");
        fclose(file);
        return 1;
    }

    fread(content, 1, fileSize, file);
    content[fileSize] = '\0';
    fclose(file);

    Project project;
    fillProjectDetails(&project, content);
    free(content);

    const char *name = project.projectName;
    size_t nameLength = strlen(name);

    const char *frontend = project.frontendType;
    size_t frontendLength = strlen(frontend);

    const char *backend = project.backendType;
    size_t backendLength = strlen(backend);

    const size_t modelCount = project.modelCount;
    const Model *models = project.models;


    char cwd[PATH_MAX];
    getcwd(cwd, PATH_MAX);

    char newDirPath[PATH_MAX + strlen(name)];
    sprintf(newDirPath, "%s/%s", cwd, name);
    mkdir(newDirPath, 0777);

    char setupPath[PATH_MAX + nameLength + frontendLength + backendLength];
    sprintf(setupPath, "%s/setup.sh %s %s %s", filePath, name, frontend, backend);
    system(setupPath);

    //
    // for (size_t i = 0; i < modelCount; i++) {
    //     createRestController(backendDir, &models[i]);
    //     createService(backendDir, &models[i]);
    //     createRepository(backendDir, &models[i]);
    //     createModels(backendDir, &models[i]);
    // }

    return 0;
}
