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
 * 程序初始化任务运行失败
 */
#define FUN_ERROR_INIT_TASK_FAILED -10
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
/**
 * 创建save基类文件失败 /save /save/save_1 ... /save/save_3
 */
#define FUN_ERROR_CREATE_SAVE_FILE -1004
/**
 * 创建db失败
 */
#define FUN_ERROR_CREATE_DB -1200
/**
 * gCacheMap 缓存插入数据失败
 */
#define FUN_ERROR_CACHE_INSERT_FAILED -2000
/**
 * gCacheMap 缓存查询数据失败
 */
#define FUN_ERROR_CACHE_QUERY_FAILED -2001
/**
 * gCacheMap 缓存清除数据失败
 */
#define FUN_ERROR_CACHE_REMOVE_FAILED -2002

/**
 * 存储文件夹
 */
#define CFG_SAVE_BASE_FILE "save"
/**
 * 存储文件夹内数据库名称
 */
#define CFG_SAVE_DB_NAME "save.db"

#endif /* cfg_base_h */
