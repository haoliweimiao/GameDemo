//
// Created by Von on 2020/9/26.
//

#ifndef REMOTEPROTOCOLMODULE_SOCKET_CLIENT_H
#define REMOTEPROTOCOLMODULE_SOCKET_CLIENT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "socket_api.h"

   /**
 * connect server Socket
 * @return fun return value
 */
   SOCKET_API int connectSocket(int *sock);

   /**
 * send message to server
 * @param msg send message content
 * @param value message return message, can be null
 * @return fun return value
 */
   SOCKET_API int clientSendMsg(const char *msg, char *value);

#ifdef __cplusplus
}
#endif

#endif //REMOTEPROTOCOLMODULE_SOCKET_CLIENT_H
