//
// Created by Von on 2020/9/26.
//
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <log.h>
#include "socket_client.h"

/**
 * connect server Socket
 * @return fun return value
 */
SOCKET_API int connectSocket(int *sock)
{
    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));                //每个字节都用0填充
    serv_addr.sin_family = PF_INET;                          //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr(SOCKET_LOCAL_URL); //具体的IP地址
    serv_addr.sin_port = htons(SOCKET_LOCAL_PORT);           //端口

    //创建套接字
    int socket_client = socket(PF_INET, SOCK_STREAM, 0);
    int result = connect(socket_client, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    if (result != 0)
    {
        close(socket_client);
        (*sock) = -1;
        LOG_I("connect server failed, exit processPF_INET");
        return FUN_SOCKET_CONNECT_ERROR;
    }

    (*sock) = socket_client;

    return FUN_NORMAL;
}

/**
 * send message to server
 * @param msg send message content
 * @param value message return message, can be null
 * @return fun return value
 */
SOCKET_API int clientSendMsg(const char *msg, char *value)
{
    int socket = -100;
    connectSocket(&socket);
    if (socket < 0)
    {
        LOG_I("client send message error, socket:%d code: %d", socket, FUN_SOCKET_NOT_CONNECT_ERROR);
        return FUN_SOCKET_NOT_CONNECT_ERROR;
    }
    LOG_I("send client->server : %s", msg);
    memset(value, '\0', 1);
    send(socket, msg, strlen(msg), 0);
    read(socket, value, sizeof(value) - 1);
    LOG_I("server->client message: %s", value);
    return FUN_NORMAL;
}