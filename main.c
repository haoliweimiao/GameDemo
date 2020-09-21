#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <db/db_helper.h>
#include <db/db_test.h>

int main() {
  system("clear");
  db_test();
  int fd;

  char *path = "test.txt";
  printf("access function -------------------------\n");

  if ((fd = access(path, F_OK)) == 0)
    printf("[access] file exist! \n");
  else
    printf("[access] file not exist!!\n");

  if ((fd = access(path, R_OK)) == 0)
    printf("[access] read file ok!\n");
  else
    printf("[access] read file no!\n");

  if ((fd = access(path, W_OK)) == 0)
    printf("[access] write file ok!\n");
  else
    printf("[access] write file no!\n");

  if ((fd = access(path, X_OK)) == 0)
    printf("[access] execute file ok!\n");
  else
    printf("[access] execute file no!\n");

  mkdir("./test/adf", O_RDWR);

  return 0;
}