//
// Created by zhivko-kocev on 10/7/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/limits.h>

int main() {
    char path[1024];
    ssize_t count = readlink("/proc/self/exe", path, 1024);

    if (count == -1) {
        perror("readlink");
    }

    path[count] = '\0';
    char *end = strrchr(path, '/');
    *end = '\0';

    char fullPath[PATH_MAX];
    sprintf(fullPath, "%s/mark_xi/mark.js", path);

    system(fullPath);

    sprintf(fullPath, "%s/mark_xi/mark_x", path);
    system(fullPath);
    return 0;
}
