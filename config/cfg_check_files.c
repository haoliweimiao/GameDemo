#include <stdio.h>
#include <base/cfg_file.h>
#include <string.h>

#include "cfg_check_files.h"
/**
 * 存档文件夹数量
 */
#define CFG_SAVE_FILES_NUMBER 3
/**
 * 存档文件列表
 */
const char CFG_SAVE_FILES[CFG_SAVE_FILES_NUMBER][16] = {"save_1", "save_2", "save_3"};
/**
 * check save data file save1...save3
 */
const CFG_API int check_save_file(void)
{
    printf("check save file task starting! \n");
    char file[128];
    memset(file, '\0', 1);
    strcat(file, CFG_SAVE_BASE_FILE);
    // 创建save文件夹
    create_file_if_not_exist(file, FILE_TYPE_FLODER);

    for (size_t i = 0; i < CFG_SAVE_FILES_NUMBER; i++)
    {
        memset(file, '\0', 1);
        strcat(file, CFG_SAVE_BASE_FILE);
        strcat(file, "/");
        strcat(file, CFG_SAVE_FILES[i]);
        int result = create_file_if_not_exist(file, FILE_TYPE_FLODER);
        if (result != FUN_NORMAL)
        {
            printf("check save file task finish, state:failed! \n");
            return FUN_ERROR_CREATE_SAVE_FILE;
        }
    }

    printf("check save file task finish, state:success! \n");
    return FUN_NORMAL;
}