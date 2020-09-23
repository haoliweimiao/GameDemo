#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <module_db/db_helper.h>
#include <module_db/db_test.h>
#include <module_cache/cache_file.h>

#include "init.h"

int main()
{
  system("clear");

  init_task_exec();

  return 0;
}