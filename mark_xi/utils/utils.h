//
// Created by zhivko-kocev on 10/2/24.
//

#ifndef UTILS_H
#define UTILS_H
#include "../structs/project.h"

void fillProjectDetails(Project *project, const char *jsonString);

void createRestController(const char *backendDir, const Model *model);

void createService(const char *backendDir, const Model *model);

void createRepository(const char *backendDir, const Model *model);

void createModels(const char *backendDir, const Model *model);

#endif //UTILS_H
