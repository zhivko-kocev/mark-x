//
// Created by zhivko-kocev on 10/2/24.
//

#ifndef UTILS_H
#define UTILS_H
#include "../structs/project.h"
void getProjectDetails(Project *project,const char *jsonString);
char *getDirPath(const char *fullPath);
void createProject(char *dirPath,char *cwd,const char *name,const char *frontend,const char *backend,char *backendDir);
void createFiles(Model *models, size_t modelsCount);
void createRestController(const char *backendDir, const Model *model);
void createService(const char *backendDir, const Model *model);
void createRepository(const char *backendDir, const Model *model);


#endif //UTILS_H
