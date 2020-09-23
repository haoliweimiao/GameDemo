#include "db_helper.h"

#include <stdio.h>
#include <string.h>

DB_API int db_test() {
  create_config_db();
  create_save_table();
  db_delete_data("hehe");
  db_insert_data("hehe", "da");
  char value[1024] = "";
  db_query_data("hehe", value);
  printf("query hehe from option table, value: %s \n",
         strlen(value) ? value : "NULL");

  db_update_data("hehe", "hei");
  //   value[0] = '\0';
  memset(value, '\0', sizeof(value) / sizeof(char));
  db_query_data("hehe", value);
  printf("query hehe from option table, value: %s \n",
         strlen(value) ? value : "NULL");

  db_update_data("hehe1", "hei");
  value[0] = '\0';
  db_query_data("hehe1", value);
  printf("query hehe1 from option table, value: %s \n",
         strlen(value) ? value : "NULL");

  value[0] = '\0';
  db_query_data("save_cache", value);
  printf("query save_cache from option table, value: %s \n",
         strlen(value) ? value : "NULL");

  return FUN_NORMAL;
}