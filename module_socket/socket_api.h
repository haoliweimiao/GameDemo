//
// Created by Von on 2020/9/26.
//

#ifndef REMOTEPROTOCOLMODULE_SOCKET_API_H
#define REMOTEPROTOCOLMODULE_SOCKET_API_H

#ifdef __cplusplus
extern "C"
{
#endif

#define SOCKET_API

/* fun return value */
/**
 * fun exec success
 */
#define FUN_NORMAL 0
#define FUN_SOCKET_CONNECT_ERROR -1
#define FUN_SOCKET_NOT_CONNECT_ERROR -2
#define FUN_SOCKET_CLIENT_SEND_MSG_ERROR -10

/* socket config */
#define SOCKET_DATA_LEN 1024 * 32
#define SOCKET_LOCAL_URL "127.0.0.1"
#define SOCKET_LOCAL_PORT 12346

#ifdef __cplusplus
}
#endif

#endif //REMOTEPROTOCOLMODULE_SOCKET_API_H
