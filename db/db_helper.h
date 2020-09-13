#ifndef db_helper_h
#define db_helper_h

#define DB_API

/**
 * create config db, save something common data in this db
 */
DB_API int create_config_db();

DB_API int db_callback(void *NotUsed, int argc, char **argv, char **azColName);

#endif /* db_helper_h */
