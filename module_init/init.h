#ifndef init_h
#define init_h

#ifdef __cplusplus
extern "C"
{
#endif

#include <module_base/cfg_file.h>
#include <module_base/cfg_base.h>
#include <module_cache/cache_key.h>
#include <module_cache/cache_file.h>
#include <module_db/db_config.h>
#include <module_db/db_helper.h>

    /**
     * 初始化任务执行
     * for循环执行 INIT_TASK
     */
    CFG_API int init_task_exec();
    /**
     * check save data file save1...save3
     */
    const CFG_API int check_save_file(void);
    /**
     * check save database in file save1...save3
     */
    const CFG_API int check_save_db_create_state(void);

/**
 * init task count
 */
#define INIT_TASK_COUNT 2

    /**
     * init task array
     */
    const int (*INIT_TASK[INIT_TASK_COUNT])(void) = {check_save_file, check_save_db_create_state};

#ifdef __cplusplus
}
#endif

#endif /* init_h */