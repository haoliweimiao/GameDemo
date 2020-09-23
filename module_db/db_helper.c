#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db_helper.h"
#include "db_sql.h"

DB_API int create_config_db()
{
  sqlite3 *db;
  int rc;

  /* Open database */
  rc = sqlite3_open(CONFIG_DB_NAME, &db);
  if (rc)
  {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    return FUN_ERROR;
  }
  else
  {
    fprintf(stdout, "Opened database successfully\n");
  }

  sqlite3_close(db);
  return FUN_NORMAL;
}

DB_API int create_save_table()
{
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  char *sql;

  /* Open database */
  rc = sqlite3_open(CONFIG_DB_NAME, &db);
  if (rc)
  {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    return FUN_ERROR;
  }
  else
  {
    fprintf(stdout, "Opened database successfully\n");
  }

  /* Create SQL statement */
  sql = "CREATE TABLE OPTION("
        "ID INTEGER PRIMARY KEY  AUTOINCREMENT NOT NULL,"
        "KEY            TEXT     NOT NULL,"
        "VALUE          TEXT     NOT NULL);";

  /* Execute SQL statement */
  rc = sqlite3_exec(db, sql, db_callback, 0, &zErrMsg);
  if (rc != SQLITE_OK)
  {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  else
  {
    fprintf(stdout, "Table created successfully\n");
  }

  sqlite3_close(db);
  return FUN_NORMAL;
}

DB_API int db_insert_data(const char *key, const char *value)
{

  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;

  /* Open database */
  rc = sqlite3_open(CONFIG_DB_NAME, &db);
  if (rc)
  {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    return FUN_ERROR;
  }

  char sql[1024] = "INSERT INTO OPTION (KEY, VALUE) ";
  // "VALUES (1, 'Paul', 32, 'California', 20000.00 ); ";
  strcat(sql, "VALUES ('");
  strcat(sql, key);
  strcat(sql, "', '");
  strcat(sql, value);
  strcat(sql, "');");

  printf("sql: %s \n", sql);

  /* Execute SQL statement */
  rc = sqlite3_exec(db, sql, db_callback, 0, &zErrMsg);
  if (rc != SQLITE_OK)
  {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  else
  {
    fprintf(stdout, "insert data successfully\n");
  }

  sqlite3_close(db);

  return FUN_NORMAL;
}

/**
 * db_query_data query value char[] length
 */
const int DB_QUERY_VALUE_LEN = 1024;
/**
 * db_query_data query value char[]
 */
char db_query_value[DB_QUERY_VALUE_LEN] = "";
/**
 * db_query_data sqlite3_exec callback function
 */
DB_API int db_query_callback(void *NotUsed, int argc, char **argv,
                             char **azColName)
{
  int i;
  for (i = 0; i < argc; i++)
  {
    memset(db_query_value, '\0', 1);
    if (argv[i] != NULL)
    {
      strcat(db_query_value, argv[i]);
    }
  }
  return FUN_NORMAL;
}

DB_API int db_query_data(char *key, char *value)
{
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;

  /* Open database */
  rc = sqlite3_open(CONFIG_DB_NAME, &db);
  if (rc)
  {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    return FUN_ERROR;
  }

  char sql[1024] = "select VALUE from OPTION where KEY = '";
  strcat(sql, key);
  strcat(sql, "';");

  printf("sql: %s \n", sql);

  /* Execute SQL statement */
  rc = sqlite3_exec(db, sql, db_query_callback, 0, &zErrMsg);
  if (rc != SQLITE_OK)
  {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  else
  {
    fprintf(stdout, "query data:%s successfully\n", db_query_value);
  }

  strcat(value, db_query_value);
  memset(db_query_value, '\0', sizeof(db_query_value) / sizeof(char));

  sqlite3_close(db);

  return FUN_NORMAL;
}

DB_API int db_delete_data(const char *key)
{
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;

  /* Open database */
  rc = sqlite3_open(CONFIG_DB_NAME, &db);
  if (rc)
  {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    return FUN_ERROR;
  }
  else
  {
    fprintf(stdout, "Opened database successfully\n");
  }

  char sql[1024] = "delete from OPTION where KEY = '";
  strcat(sql, key);
  strcat(sql, "';");

  printf("sql: %s \n", sql);

  /* Execute SQL statement */
  rc = sqlite3_exec(db, sql, db_callback, 0, &zErrMsg);
  if (rc != SQLITE_OK)
  {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }

  sqlite3_close(db);

  return FUN_NORMAL;
}

DB_API int db_update_data(char *key, char *value)
{
  // 数据库不存在key，应该先插入数据
  char query_value[1024] = {0};
  db_query_data(key, query_value);
  int query_value_length = strlen(query_value);
  //   printf("db_update_data value:%s length:%d \n", query_value,
  //          query_value_length);
  if (query_value_length == 0)
  {
    db_insert_data(key, value);
    return FUN_NORMAL;
  }

  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;

  /* Open database */
  rc = sqlite3_open(CONFIG_DB_NAME, &db);
  if (rc)
  {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    return FUN_ERROR;
  }

  // "UPDATE COMPANY set SALARY = 25000.00 where ID=1; "
  char sql[1024] = "UPDATE OPTION set VALUE = '";
  strcat(sql, value);
  strcat(sql, "' where key = '");
  strcat(sql, key);
  strcat(sql, "';");

  printf("sql: %s \n", sql);

  /* Execute SQL statement */
  rc = sqlite3_exec(db, sql, db_callback, 0, &zErrMsg);
  if (rc != SQLITE_OK)
  {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  else
  {
    fprintf(stdout, "insert data successfully\n");
  }

  sqlite3_close(db);

  return FUN_NORMAL;
}

DB_API int db_callback(void *NotUsed, int argc, char **argv, char **azColName)
{
  int i;
  for (i = 0; i < argc; i++)
  {
    printf("callback %s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return FUN_NORMAL;
}