#include <stdio.h>
#include <string.h>

#include "db_test.h"

DB_API int db_test()
{
       char dbPath[128];
       memset(dbPath, '\0', 1);
       strcat(dbPath, CONFIG_DB_NAME);
       create_config_db(dbPath);
       create_save_table(dbPath);
       db_delete_data(dbPath, "hehe");
       db_insert_data(dbPath, "hehe", "da");
       char value[1024] = "";
       db_query_data(dbPath, "hehe", value);
       printf("query hehe from option table, value: %s \n",
              strlen(value) ? value : "NULL");

       db_update_data(dbPath, "hehe", "hei");
       //   value[0] = '\0';
       memset(value, '\0', sizeof(value) / sizeof(char));
       db_query_data(dbPath, "hehe", value);
       printf("query hehe from option table, value: %s \n",
              strlen(value) ? value : "NULL");

       db_update_data(dbPath, "hehe1", "hei");
       value[0] = '\0';
       db_query_data(dbPath, "hehe1", value);
       printf("query hehe1 from option table, value: %s \n",
              strlen(value) ? value : "NULL");

       value[0] = '\0';
       db_query_data(dbPath, "save_cache", value);
       printf("query save_cache from option table, value: %s \n",
              strlen(value) ? value : "NULL");

       return FUN_NORMAL;
}