#ifndef db_helper_h
#define db_helper_h

#define DB_API
#define FUN_NORMAL 0
#define FUN_ERROR -1

/**
 * create config db, save something common data in this db
 */
DB_API int create_config_db();

/**
 * create save table in config.db
 */
DB_API int create_save_table();

/**
 * sqlite3_exec common print log callback
 */
DB_API int db_callback(void *NotUsed, int argc, char **argv, char **azColName);

/**
 * save key:value to table OPTION
 */
DB_API int db_insert_data(const char *key, const char *value);

/**
 * delete key:value in table OPTION
 */
DB_API int db_delete_data(const char *key);

/**
 * query value by key in table OPTION
 */
DB_API int db_query_data(char *key, char *value);

/**
 * update value by key in table OPTION
 */
DB_API int db_update_data(char *key, char *value);

#endif /* db_helper_h */
