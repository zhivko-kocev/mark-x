//
// Created by zhivko-kocev on 10/2/24.
//

#ifndef UTILS_H
#define UTILS_H
#include "../structs/project.h"

void fillProjectDetails(Project *project, const char *jsonString);

void writeModelsJSON(const char *jsonString, char *filePath);

void writeToFile(const char *fullPath, char *modelName,const char *extension);
#endif //UTILS_H
