#ifndef socket_uv_client_h
#define socket_uv_client_h

#ifdef __cplusplus
extern "C" {
#endif

#include "socket_api.h"

/**
 * init client
 */
SOCKET_API int initClient();
/**
 * client send message
 * @params message: send message
 * @params len:     send message lenght
 */
SOCKET_API int clientSendMessage(const char *message, int len);

#ifdef __cplusplus
}
#endif

#endif /* socket_uv_client_h */