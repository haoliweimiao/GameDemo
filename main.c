#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <db/db_helper.h>
#include <db/db_test.h>
#include <base/cfg_file.h>
#include <config/cfg_check_files.h>
#include <cache/cache_file.h>

#define INIT_TASK_COUNT 1
const int (*INIT_TASK[INIT_TASK_COUNT])(void) = {check_save_file};

int main()
{
  system("clear");

  for (size_t i = 0; i < INIT_TASK_COUNT; i++)
  {
    int fun_result = INIT_TASK[i]();
    if (fun_result != FUN_NORMAL)
    {
      printf("run init task error, code:%d", fun_result);
      return 0;
    }
  }

  return 0;
}