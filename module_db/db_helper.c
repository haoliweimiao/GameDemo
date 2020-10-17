#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db_helper.h"
#include "db_sql.h"

DB_API int create_config_db(const char *dbPath)
{
  sqlite3 *db;
  int rc;

  /* Open database */
  rc = sqlite3_open(dbPath, &db);
  if (rc)
  {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    return FUN_ERROR_CREATE_DB;
  }
  else
  {
    fprintf(stdout, "Opened database:%s successfully\n", dbPath);
  }

  sqlite3_close(db);
  return FUN_NORMAL;
}

DB_API int create_save_table(const char *dbPath)
{
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  char *sql;

  /* Open database */
  rc = sqlite3_open(dbPath, &db);
  if (rc)
  {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    return FUN_ERROR_CREATE_DB;
  }
  else
  {
    fprintf(stdout, "Opened database:%s successfully\n", dbPath);
  }

  /* Create SQL statement */
  sql = "CREATE TABLE IF NOT EXISTS OPTION("
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

DB_API int db_insert_data(const char *dbPath, const char *key, const char *value)
{

  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;

  /* Open database */
  rc = sqlite3_open(dbPath, &db);
  if (rc)
  {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
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
#define DB_QUERY_VALUE_LEN 1024
/**
 * db_query_data query value char[]
 */
char db_query_value[DB_QUERY_VALUE_LEN] = {0};
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

DB_API int db_query_data(const char *dbPath, char *key, char *value)
{
  sqlite3 *db;
  char *zErrMsg = NULL;
  int rv;
  char szSql[128] = {0};
  sqlite3_stmt *stmt;
  rv = sqlite3_open(dbPath, &db);
  if (rv)
  {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return FUN_ERROR;
  }

  strcpy(szSql, "SELECT VALUE FROM OPTION where KEY=?");
  rv = sqlite3_prepare(db, szSql, 128, &stmt, NULL);
  if (rv != SQLITE_OK)
  {
    fprintf(stderr, "sqlite3_prepare(%d): %s\n", rv, sqlite3_errmsg(db));
    sqlite3_close(db);
    return FUN_ERROR;
  }
  rv = sqlite3_bind_text(stmt, 1, key, strlen(key), SQLITE_STATIC);
  if (rv != SQLITE_OK)
  {
    fprintf(stderr, "sqlite3_bind_text(%d): %s\n", rv, sqlite3_errmsg(db));
    sqlite3_close(db);
    return FUN_ERROR;
  }
  rv = sqlite3_step(stmt);
  if ((rv != SQLITE_OK) && (rv != SQLITE_DONE) && (rv != SQLITE_ROW))
  {
    fprintf(stderr, "sqlite3_step(%d): %s\n", rv, sqlite3_errmsg(db));
    sqlite3_close(db);
    return FUN_ERROR;
  }
  while (rv == SQLITE_ROW)
  {
    memset(value, '\0', 1);
    strcat(value, sqlite3_column_text(stmt, 0));
    fprintf(stderr, "result: %s\n", value);
    rv = sqlite3_step(stmt);
  }
  rv = sqlite3_finalize(stmt);
  if (rv != SQLITE_OK)
  {
    fprintf(stderr, "sqlite3_finalize(%d): %s\n", rv, sqlite3_errmsg(db));
    sqlite3_close(db);
    return FUN_ERROR;
  }
  sqlite3_close(db);
  return FUN_NORMAL;
}

DB_API int db_delete_data(const char *dbPath, const char *key)
{
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;

  /* Open database */
  rc = sqlite3_open(dbPath, &db);
  if (rc)
  {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return FUN_ERROR;
  }
  else
  {
    fprintf(stdout, "Opened database:%s successfully\n", dbPath);
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

DB_API int db_update_data(const char *dbPath, char *key, char *value)
{
  // 数据库不存在key，应该先插入数据
  char query_value[1024] = {0};
  db_query_data(dbPath, key, query_value);
  int query_value_length = strlen(query_value);
  //   printf("db_update_data value:%s length:%d \n", query_value,
  //          query_value_length);
  if (query_value_length == 0)
  {
    db_insert_data(dbPath, key, value);
    return FUN_NORMAL;
  }

  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;

  /* Open database */
  rc = sqlite3_open(dbPath, &db);
  if (rc)
  {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
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
