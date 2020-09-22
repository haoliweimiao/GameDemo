#include "cfg_file.h"

/**
 * 该文件是否可以读写
 */
CFG_API int fileCanRW(const char *path)
{
    int result = FUN_NORMAL;
    int fd;
    if ((fd = access(path, F_OK)) == 0)
    {
        printf("[access] flie:%s exist! \n", path);
    }
    else
    {
        result = FUN_ERROR_FILE_NOT_EXIST;
        printf("[access] flie:%s not exist!!\n", path);
        return result;
    }

    if ((fd = access(path, R_OK)) == 0)
    {
        printf("[access] read flie:%s ok!\n", path);
    }
    else
    {
        result = FUN_ERROR_FILE_NOT_READ;
        printf("[access] read flie:%s no!\n", path);
        return result;
    }

    if ((fd = access(path, W_OK)) == 0)
    {
        printf("[access] write flie:%s ok!\n", path);
    }
    else
    {
        result = FUN_ERROR_FILE_NOT_WRITE;
        printf("[access] write flie:%s no!\n", path);
        return result;
    }

    // if ((fd = access(path, X_OK)) == 0)
    //     printf("[access] execute flie:%s ok!\n", path);
    // else
    //     printf("[access] execute flie:%s no!\n", path);

    return result;
}

/**
 * create file if not exist
 */
CFG_API int create_file_if_not_exist(const char *file, const int file_type)
{
    // 有创建新文件设置为1
    int createNewTag = 0;
    if (file_type == FILE_TYPE_FLODER)
    {
        int fd;
        if ((fd = access(file, F_OK)) != 0)
        {
            int mode = strtol("0777", NULL, 8);
            mkdir(file, mode);
            createNewTag = 1;
        }
    }
    else if (file_type == FILE_TYPE_TEXT)
    {
        int fd;
        if ((fd = access(file, F_OK)) != 0)
        {
            FILE *fp = NULL;
            // 创建文本
            fp = fopen(file, "a+");
            printf("create text:%s \n", file);
            fclose(fp);
            createNewTag = 1;
        }
    }

    if (createNewTag)
    {
        int result = fileCanRW(file);
        if (result == FUN_NORMAL)
        {
            printf("create folder:%s \n", file);
            return FUN_NORMAL;
        }
        else
        {
            printf("create folder:%s failed \n", file);
            return FUN_ERROR_CREATE;
        }
    }

    return FUN_NORMAL;
}