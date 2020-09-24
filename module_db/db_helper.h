#ifndef db_helper_h
#define db_helper_h

#include <sqlite3.h>
#include <module_base/cfg_base.h>
#define DB_API

/**
 * create config db, save something common data in this db
 */
DB_API int create_config_db(const char *dbPath);

/**
 * create save table in config.db
 */
DB_API int create_save_table(const char *dbPath);

/**
 * sqlite3_exec common print log callback
 */
DB_API int db_callback(void *NotUsed, int argc, char **argv, char **azColName);

/**
 * save key:value to table OPTION
 */
DB_API int db_insert_data(const char *dbPath, const char *key, const char *value);

/**
 * delete key:value in table OPTION
 */
DB_API int db_delete_data(const char *dbPath, const char *key);

/**
 * query value by key in table OPTION
 */
DB_API int db_query_data(const char *dbPath, char *key, char *value);

/**
 * update value by key in table OPTION
 */
DB_API int db_update_data(const char *dbPath, char *key, char *value);

#endif /* db_helper_h */
