#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
// #include <jansson.h> todo

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [filename]\n", argv[0]);
        return 1;
    }

    char *dirPath = malloc(PATH_MAX);
    const char *fullPath = __FILE__;
    const char *directory = strrchr(fullPath, '/');

    strncpy(dirPath, fullPath, directory - fullPath);


    char *projectName = argv[1];
    char *frontendType = argv[2];

    char cwd[PATH_MAX];
    getcwd(cwd, PATH_MAX);

    char *mkdirCommand = malloc(7 + strlen(projectName) + 1 + strlen(cwd) + 1);
    sprintf(mkdirCommand, "mkdir %s/%s", cwd, projectName);
    system(mkdirCommand);


    char *createBackFront = malloc(112 + strlen(projectName) + 1 + strlen(frontendType) + 1);
    sprintf(createBackFront,
            "%s/setup-project-zsh.sh %s %s", dirPath,
            projectName, frontendType);
    system(createBackFront);

    free(mkdirCommand);
    free(createBackFront);
    free(dirPath);
    return 0;
}
