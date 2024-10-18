//
// Created by zhivko-kocev on 10/11/24.
//

#ifndef CONFIG_INFO_H
#define CONFIG_INFO_H

typedef struct
{
    char *rootPath;
    char *extension;
    char **dirSetting;
    char **fileSetting;
    int dirSettingCount;
    int fileSettingCount;
} ConfigInfo;

#endif // CONFIG_INFO_H
