//
// Created by Von on 2020/9/26.

#include "socket_server.h"
#include <arpa/inet.h>
#include <log.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void printSocketInfo(const int socket) {
  unsigned optVal;
  socklen_t optLen = sizeof(socklen_t);
  getsockopt(socket, SOL_SOCKET, SO_SNDBUF, (char *)&optVal, &optLen);
  // 打印
  LOG_I("Socket id: %d, Buffer length: %d", socket, optVal);
}

/**
 * server start state, 1: start
 */
static int socket_server_state = 0;

/**
 * start server
 * @return fun return value
 */
SOCKET_API int startSocketServer() {
  if (socket_server_state == 1) {
    LOG_I("server start run");
    return FUN_NORMAL;
  }

  //创建套接字
  int serverSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (serverSock == -1) {
    LOG_I("server socket open failed :%d", serverSock);
    return FUN_SOCKET_CONNECT_ERROR;
  }

  //将套接字和IP、端口绑定
  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));      //每个字节都用0填充
  serv_addr.sin_family = PF_INET;                //使用IPv4地址
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); //具体的IP地址
  serv_addr.sin_port = htons(SOCKET_LOCAL_PORT); //端口
  int bindResult =
      bind(serverSock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

  if (bindResult == -1) {
    LOG_I("server start bind port:%d result:%d ,port locked!PF_INET",
          SOCKET_LOCAL_PORT, bindResult);
    return 0;
  }

  //进入监听状态，等待用户发起请求
  int result = 0;
  socket_server_state = 1;
  while ((result = listen(serverSock, 20)) >= 0) {
    LOG_I("listen client result:%d PF_INET", result);
    //接收客户端请求
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock = 0;
    char sendBuffer[SOCKET_DATA_LEN];
    char readBuffer[SOCKET_DATA_LEN];
    while ((clnt_sock = accept(serverSock, (struct sockaddr *)&clnt_addr,
                               &clnt_addr_size)) >= 0) {
      //            printSocketInfo(clnt_sock);
      memset(readBuffer, '\0', 1);
      read(clnt_sock, readBuffer, sizeof(readBuffer) - 1);
      //            recv(clnt_sock, readBuffer, sizeof(readBuffer) - 1, 0);
      LOG_I("receiver client->server :%s", readBuffer);
      //向客户端发送数据
      memset(sendBuffer, '\0', 1);
      strcat(sendBuffer, "message from server: ");
      strcat(sendBuffer, readBuffer);
      write(clnt_sock, sendBuffer, sizeof(sendBuffer));
      close(clnt_sock);
      LOG_I("send server->client socket:%d message:%s , close socket",
            clnt_sock, sendBuffer);
    }
  }

  //关闭套接字
  close(serverSock);
  socket_server_state = 0;
  LOG_I("close serverSock:%d PF_INET", serverSock);

  return FUN_NORMAL;
}

/**
 * stop server
 * @return fun return value
 */
SOCKET_API int stopServer() { return FUN_NORMAL; }
