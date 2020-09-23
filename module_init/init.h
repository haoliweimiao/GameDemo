#ifndef init_h
#define init_h

#include <module_base/cfg_file.h>
#include <module_base/cfg_base.h>

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
#define INIT_TASK_COUNT 1
/**
 * init task array
 */
const int (*INIT_TASK[INIT_TASK_COUNT])(void) = {check_save_file};

/**
 * 初始化任务执行
 * for循环执行 INIT_TASK
 */
CFG_API int init_task_exec();

#endif /* init_h */