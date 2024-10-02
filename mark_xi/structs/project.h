//
// Created by zhivko-kocev on 10/2/24.
//
#ifndef PROJECT_H
#define PROJECT_H
#include "model.h"
#include <stddef.h>

typedef struct {
    const char *projectName;
    const char *backendType;
    const char *frontendType;
    Model *models;
    size_t modelCount;
} Project;

#endif //PROJECT_H
