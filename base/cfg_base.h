#ifndef cfg_base_h
#define cfg_base_h

/**
 * config module API tag
 */
#define CFG_API
/**
 * fun run success, return normal
 */
#define FUN_NORMAL 0
/**
 * fun run failed, return error
 */
#define FUN_ERROR -1
/**
 * 文件不存在
 */
#define FUN_ERROR_FILE_NOT_EXIST -1000
/**
 * 文件不可读
 */
#define FUN_ERROR_FILE_NOT_READ -1001
/**
 * 文件不可写
 */
#define FUN_ERROR_FILE_NOT_WRITE -1002
/**
 * 文件创建失败
 */
#define FUN_ERROR_CREATE -1003

const static char CFG_SAVE_BASE_FILE[5] = "save";

#endif /* cfg_base_h */
