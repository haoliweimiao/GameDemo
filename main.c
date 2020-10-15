#include <stdio.h>
#include <stdlib.h>

#include <module_init/init.h>
#include <module_view/view_start.h>
#include <module_socket/socket_demo.h>
#include <module_json/json_demo.h>

int main()
{

  // system("clear");

  // readFromStringDemo();

  // init_task_exec();

  // show_view_start();

  startServer$Client();

  return 0;
}