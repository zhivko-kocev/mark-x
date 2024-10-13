//
// Created by zhivko-kocev on 10/7/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <linux/limits.h>

#include "mark_xi/utils/utils.h"
#define MAX_NAME 1024

int main() {
    char execPath[PATH_MAX];
    if (populateExecutablePath(execPath,PATH_MAX)) {
        printf("Failed to load executable path\n");
        return 1;
    }

    char command[PATH_MAX + MAX_NAME];
    sprintf(command, "rm -rf %s/mark_xi/models/*", execPath);
    system(command);

    char fullPath[PATH_MAX + MAX_NAME];
    sprintf(fullPath, "%s/mark_xi/mark.js", execPath);

    system(fullPath);

    sprintf(fullPath, "%s/mark_xi/mark_x", execPath);
    system(fullPath);
    return 0;
}
