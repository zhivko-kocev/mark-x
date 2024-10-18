//
// Created by zhivko-kocev on 10/2/24.
//

#ifndef UTILS_H
#define UTILS_H
#include "../structs/project.h"
#include "../structs/config_info.h"

int populateExecutablePath(char *execPath, size_t size);

char *getJsonContent();

int populateProjectDetails(char *jsonString, Project *project);

int createProjectDirectories(char *execPath, const Project *project);

char *getModelJsonString(Model *model);

int populateConfig(char *execPath, const Project *model, ConfigInfo *configInfo);

void freeProject(Project *project);

void freeConfig(ConfigInfo *configInfo);

#endif // UTILS_H
