#include <stdio.h>
#include <stdlib.h>

#include <module_init/init.h>
#include <module_view/view_start.h>

int main()
{
  system("clear");

  init_task_exec();

  show_view_start();

  return 0;
}