#include "socket_demo.h"
#include <pthread.h>

void *startServer(void *p)
{
    LOG_TIME();
    // startSocketServer();
    startUvSocketServer();
    return 0;
}

void *startClient(void *p)
{

    LOG_TIME();
    initClient();
    char message[SOCKET_DATA_LEN] = {};
    memset(message, '\0', 1);
    for (int i = 0; i < 1024; i++)
    {
        strcat(message, "hei");
        strcat(message, "\n");
    }

    clientSendMessage(message, strlen(message));
    return 0;
}

/**
 * start socket and client
 */
SOCKET_API int startServer$Client()
{

    int rc;
    pthread_t id;
    // 创建第一个线程
    rc = pthread_create(&id, NULL, startServer, NULL);
    if (rc)
        printf("Failed to create the thread fun1().");

    // 创建第二个线程
    rc = pthread_create(&id, NULL, startClient, NULL);
    if (rc)
        printf("Failed to create the thread fun2().");

    // 阻塞主线程的运行，以免主线程运行结束时提前终止子线程
    pthread_join(id, NULL);

    return FUN_NORMAL;
}