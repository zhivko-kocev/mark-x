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

    char fullPath[PATH_MAX + PATH_MAX + MAX_NAME];
    sprintf(fullPath, "(%s/mark_xi/mark.js) | %s/mark_xi/mark_x", execPath, execPath);
    system(fullPath);
    return 0;
}
