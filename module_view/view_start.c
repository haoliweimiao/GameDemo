#include "view_start.h"

/**
 * show start page
 */
CFG_API int show_view_start() {
  char showMsg[1024];
  memset(showMsg, '\0', 1);

  char queryValue[16];
  memset(queryValue, '\0', 1);
  cache_query(CACHE_KEY_SAVE_1_CREATE_INT, queryValue);
  if (strcmp("1", queryValue)) {
    strcat(showMsg, "1:start game from save1 \n");
  } else {
    strcat(showMsg, "1:create save1 \n");
  }

  memset(queryValue, '\0', 1);
  cache_query(CACHE_KEY_SAVE_2_CREATE_INT, queryValue);
  if (strcmp("1", queryValue)) {
    strcat(showMsg, "2:start game from save2 \n");
  } else {
    strcat(showMsg, "2:create save2 \n");
  }

  memset(queryValue, '\0', 1);
  cache_query(CACHE_KEY_SAVE_3_CREATE_INT, queryValue);
  if (strcmp("1", queryValue)) {
    strcat(showMsg, "3:start game from save3 \n");
  } else {
    strcat(showMsg, "3:create save3 \n");
  }

  system("clear");
  printf("%s", showMsg);
  return FUN_NORMAL;
}