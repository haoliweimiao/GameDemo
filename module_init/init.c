#include <module_base/cfg_file.h>
#include <module_db/db_helper.h>
#include <stdio.h>
#include <string.h>

#include "init.h"

/**
 * 存档文件夹数量
 */
#define CFG_SAVE_FILES_NUMBER 3
/**
 * 存档文件列表
 */
const char CFG_SAVE_FILES[CFG_SAVE_FILES_NUMBER][16] = {"save_1", "save_2",
                                                        "save_3"};
/**
 * check save data file save1...save3
 */
const CFG_API int check_save_file(void) {
  printf("check save file task starting! \n");
  char file[128];
  memset(file, '\0', 1);
  strcat(file, CFG_SAVE_BASE_FILE);
  // 创建save文件夹
  create_file_if_not_exist(file, FILE_TYPE_FLODER);

  for (size_t i = 0; i < CFG_SAVE_FILES_NUMBER; i++) {
    memset(file, '\0', 1);
    strcat(file, CFG_SAVE_BASE_FILE);
    strcat(file, "/");
    strcat(file, CFG_SAVE_FILES[i]);
    int result = create_file_if_not_exist(file, FILE_TYPE_FLODER);
    if (result != FUN_NORMAL) {
      printf("check save file task finish, state:failed! \n");
      return FUN_ERROR_CREATE_SAVE_FILE;
    }
  }

  printf("check save file task finish, state:success! \n");
  return FUN_NORMAL;
}

/**
 * check save database in file save1...save3
 */
const CFG_API int check_save_db_create_state(void) {
  printf("check save db task starting! \n");
  char file[128];

  for (size_t i = 0; i < CFG_SAVE_FILES_NUMBER; i++) {
    memset(file, '\0', 1);
    strcat(file, CFG_SAVE_BASE_FILE);
    strcat(file, "/");
    strcat(file, CFG_SAVE_FILES[i]);
    strcat(file, "/");
    strcat(file, CFG_SAVE_DB_NAME);
    int ret = create_config_db(file);
    if (ret != FUN_NORMAL) {
      return ret;
    }

    ret = create_save_table(file);
    if (ret != FUN_NORMAL) {
      return ret;
    }

    // 查询数据库是否被创建使用
    char value[16];
    ret = db_query_data(file, CACHE_KEY_SAVE_CREATE_TAG_INT, value);
    if (ret != FUN_NORMAL) {
      // 未查询到数据，默认为0
      memset(value, '\0', 1);
      strcat(value, "0");
    }

    if (i == 0) {
      cache_insert(CACHE_KEY_SAVE_1_CREATE_INT, value);
    } else if (i == 1) {
      cache_insert(CACHE_KEY_SAVE_2_CREATE_INT, value);
    } else {
      cache_insert(CACHE_KEY_SAVE_3_CREATE_INT, value);
    }
  }

  printf("check save db task finish, state:success! \n");
  return FUN_NORMAL;
}

/**
 * 初始化任务执行
 */
CFG_API int init_task_exec() {
  for (size_t i = 0; i < INIT_TASK_COUNT; i++) {
    int fun_result = INIT_TASK[i]();
    if (fun_result != FUN_NORMAL) {
      printf("run init task error, code:%d", fun_result);
      return FUN_ERROR_INIT_TASK_FAILED;
    }
  }

  return FUN_NORMAL;
}