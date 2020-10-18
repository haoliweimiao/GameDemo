//
// Created by Von on 2020/9/26.
//

#ifndef REMOTEPROTOCOLMODULE_SOCKET_API_H
#define REMOTEPROTOCOLMODULE_SOCKET_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

#define SOCKET_API

/* fun return value */
/**
 * fun exec success
 */
#define FUN_NORMAL 0
#define FUN_SOCKET_CONNECT_ERROR -1
#define FUN_SOCKET_NOT_CONNECT_ERROR -2
#define FUN_SOCKET_SERVER_LISTEN_ERROR -3
#define FUN_SOCKET_CLIENT_SEND_MSG_ERROR -10

/* socket config */
#define SOCKET_DATA_LEN 1024 * 32
#define SOCKET_LOCAL_URL "127.0.0.1"
#define SOCKET_LOCAL_PORT 12346

/**
 * socket message key
 */
#define SOCKET_MSG_KEY_TYPE "type"
#define SOCKET_MSG_KEY_ID "id"
#define SOCKET_MSG_KEY_LEN "len"
#define SOCKET_MSG_KEY_CONTENT "content"
#define SOCKET_MSG_KEY_CONTENT_LEN "contentLen"

#define SOCKET_TYPE_HEART_BREAK "heartbreak"
#define SOCKET_MSG_PING "ping"
#define SOCKET_MSG_PING_LEN 5
#define SOCKET_MSG_PONG "pong"
#define SOCKET_MSG_PONG_LEN 5

/**
 * 生成ping消息
 */
void createPingMessage(char *message);

#ifdef __cplusplus
}
#endif

#endif // REMOTEPROTOCOLMODULE_SOCKET_API_H
