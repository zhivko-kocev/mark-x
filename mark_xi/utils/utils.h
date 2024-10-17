//
// Created by zhivko-kocev on 10/2/24.
//

#ifndef UTILS_H
#define UTILS_H
#include "../structs/project.h"
#include "../structs/config_info.h"

int populateExecutablePath(char *execPath, size_t size);

char *getJsonContent();

int populateProjectDetails(Project *project, const char *jsonString);

int createProjectDirectories(char *execPath, const Project *project);

char *getModelJSON(const char *jsonString, int index);

int populateConfig(char *execPath, const Project *model, ConfigInfo *configInfo);

#endif //UTILS_H
