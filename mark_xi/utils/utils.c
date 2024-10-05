#include "utils.h"
#include <jansson.h>
#include <string.h>
#include <linux/limits.h>
#include <stdio.h>

void fillProjectDetails(Project *project, const char *jsonString) {
    json_error_t error;
    json_t *root = json_loads(jsonString, 0, &error);

    if (!root) {
        printf("Error parsing JSON: %s\n", error.text);
        return;
    }

    project->projectName = strdup(json_string_value(json_object_get(root, "projectName")));
    project->frontendType = strdup(json_string_value(json_object_get(root, "frontendType")));
    project->backendType = strdup(json_string_value(json_object_get(root, "backendType")));

    const json_t *models = json_object_get(root, "models");
    if (!json_is_array(models)) {
        printf("Error: Models should be an array\n");
        json_decref(root);
        return;
    }

    const size_t modelCount = json_array_size(models);
    project->models = malloc(modelCount * sizeof(Model));
    project->modelCount = modelCount;

    for (size_t index = 0; index < modelCount; index++) {
        const json_t *model = json_array_get(models, index);
        const json_t *attributes = json_object_get(model, "attributes");

        project->models[index].modelName = strdup(json_string_value(json_object_get(model, "modelName")));

        const size_t attrCount = json_array_size(attributes);
        project->models[index].attributes = malloc(attrCount * sizeof(Attribute));
        project->models[index].attrCount = attrCount;

        for (size_t attr_index = 0; attr_index < attrCount; attr_index++) {
            const json_t *attribute = json_array_get(attributes, attr_index);

            project->models[index].attributes[attr_index].name = strdup(
                json_string_value(json_object_get(attribute, "name")));

            project->models[index].attributes[attr_index].type = strdup(
                json_string_value(json_object_get(attribute, "type")));
        }
    }

    json_decref(root);
}

char *getDirPath(const char *fullPath) {
    char *dirPath = malloc(PATH_MAX);
    const char *directory = strrchr(fullPath, '/');

    strncpy(dirPath, fullPath, directory - fullPath);

    return dirPath;
}

void createProject(char *dirPath, char *cwd, const char *name, const char *frontend, const char *backend,
                   char *backendDir) {
    char *mkdirCommand = malloc(7 + strlen(name) + 1 + strlen(cwd) + 1);
    sprintf(mkdirCommand, "mkdir %s/%s", cwd, name);
    system(mkdirCommand);
    free(mkdirCommand);


    char *createBackFront = malloc(112 + strlen(name) + 1 + strlen(frontend) + 1 + strlen(backend) + 1);
    sprintf(createBackFront,
            "%s/setup-project-bash.sh %s %s %s", dirPath,
            name, frontend, backend);
    system(createBackFront);
    free(createBackFront);

    char *dirs[] = {"controllers", "services", "repositories", "models", "exceptions", "utils"};
    char *subdirs = malloc(PATH_MAX + 7);
    for (int i = 0; i < 6; i++) {
        sprintf(subdirs, "mkdir %s/%s", backendDir, dirs[i]);
        system(subdirs);
    }
    free(subdirs);
}

void createRestController(const char *backendDir, const Model *model) {
    char controllerFileName[PATH_MAX];
    snprintf(controllerFileName, sizeof(controllerFileName), "%s/controllers/%sController.java", backendDir,
             model->modelName);

    // Open the file for writing
    FILE *file = fopen(controllerFileName, "w");
    if (!file) {
        perror("Failed to create controller file");
        return;
    }
    fprintf(
        file,
        "package com.example.backend.controllers;\n\nimport org.springframework.web.bind.annotation.*;\nimport org.springframework.beans.factory.annotation.Autowired;\nimport com.example.backend.models.%s;\nimport com.example.backend.services.%sService;\nimport java.util.List;\n\n@RestController\n@RequestMapping(\"/%s\")\npublic class %sController {\n@Autowired\nprivate %sService %sService;\n@GetMapping\npublic List<%s> getAll%s() { return %sService.getAll%s(); }\n@PostMapping\npublic %s create%s(@RequestBody %s %s) { return %sService.create%s(%s); }\n}",
        model->modelName, model->modelName, model->modelName, model->modelName, model->modelName, model->modelName,
        model->modelName, model->modelName, model->modelName, model->modelName, model->modelName, model->modelName,
        model->modelName, model->modelName, model->modelName, model->modelName, model->modelName);
    fclose(file);
}

void createService(const char *backendDir, const Model *model) {
    char serviceFileName[PATH_MAX];
    snprintf(serviceFileName, sizeof(serviceFileName), "%s/services/%sService.java", backendDir, model->modelName);

    // Open the file for writing
    FILE *file = fopen(serviceFileName, "w");
    if (!file) {
        perror("Failed to create service file");
        return;
    }
    fprintf(
        file,
        "package com.example.backend.services;\n\nimport org.springframework.stereotype.Service;\nimport org.springframework.beans.factory.annotation.Autowired;\nimport com.example.backend.models.%s;\nimport com.example.backend.repositories.%sRepository;\n\n@Service\npublic class %sService {\n@Autowired\nprivate %sRepository %sRepository;\npublic List<%s> getAll%s() { return %sRepository.findAll(); }\npublic %s create%s(%s %s) { return %sRepository.save(%s); }\n}",
        model->modelName, model->modelName, model->modelName, model->modelName, model->modelName, model->modelName,
        model->modelName, model->modelName, model->modelName, model->modelName, model->modelName, model->modelName,
        model->modelName, model->modelName);
    fclose(file);
}

void createRepository(const char *backendDir, const Model *model) {
    char repositoryFileName[PATH_MAX];
    snprintf(repositoryFileName, sizeof(repositoryFileName), "%s/repositories/%sRepository.java", backendDir,
             model->modelName);

    // Open the file for writing
    FILE *file = fopen(repositoryFileName, "w");
    if (!file) {
        perror("Failed to create repository file");
        return;
    }
    fprintf(
        file,
        "package com.example.backend.repositories;\n\nimport org.springframework.data.jpa.repository.JpaRepository;\nimport com.example.backend.models.%s;\n\npublic interface %sRepository extends JpaRepository<%s, Long> { }\n",
        model->modelName, model->modelName, model->modelName);
    fclose(file);
}

void createModels(const char *backendDir, const Model *model) {
    char repositoryFileName[PATH_MAX];
    snprintf(repositoryFileName, sizeof(repositoryFileName), "%s/models/%s.java", backendDir,
             model->modelName);

    // Open the file for writing
    FILE *file = fopen(repositoryFileName, "w");
    if (!file) {
        perror("Failed to create repository file");
        return;
    }
    fprintf(
        file,
        "package com.example.backend.models;\nimport lombok.Getter\nimport lombok.Setter\n\n@Getter\n@Setter\npublic class %s{\n",
        model->modelName);

    for (int i = 0; i < model->attrCount; ++i) {
        fprintf(file, "%s %s;\n", model->attributes[i].type, model->attributes[i].name);
    }
    fprintf(file, "}\n");
    fclose(file);
}
