//
// Created by zhivko-kocev on 10/2/24.
//

#ifndef UTILS_H
#define UTILS_H
#include "../structs/project.h"
#include "../structs/config_info.h"

int populateExecutablePath(char *execPath, size_t size);

char *getJsonContent(char *execPath);

int populateProjectDetails(Project *project, const char *jsonString);

int createProjectDirectory(const char *projectName);

int writeModelsJSON(const char *jsonString, char *filePath);

int populateConfig(char *execPath, const Project *model, ConfigInfo *configInfo);

int writeToFiles(char *execPath, const Project *project, const ConfigInfo *configInfo);

#endif //UTILS_H
