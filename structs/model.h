//
// Created by zhivko-kocev on 10/2/24.
//

#ifndef MODEL_H
#define MODEL_H
#include "attribute.h"
#include <stddef.h>

typedef struct
{
    char *modelName;
    char *ModelName;
    Attribute *attributes;
    size_t attrCount;
} Model;

#endif // MODEL_H
