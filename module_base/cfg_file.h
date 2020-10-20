/**
 * some header/method about file
 */
#ifndef cfg_file_h
#define cfg_file_h

#ifdef __cplusplus
extern "C" {
#endif

#include "cfg_base.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * 文件类型:文件夹
 */
#define FILE_TYPE_FLODER 1
/**
 * 文件类型:文本
 */
#define FILE_TYPE_TEXT 2
/**
 * 该文件是否可以读写
 */
CFG_API int fileCanRW(const char *path);
/**
 * create file if not exist
 */
CFG_API int create_file_if_not_exist(const char *file, const int file_type);

#ifdef __cplusplus
}
#endif

#endif /* cfg_file_h */
