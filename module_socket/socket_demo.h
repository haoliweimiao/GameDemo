#ifndef socket_demo_h
#define socket_demo_h

#ifdef __cplusplus
extern "C" {
#endif

#include "socket_api.h"
#include "socket_client.h"
#include "socket_server.h"
#include "socket_uv_client.h"
#include "socket_uv_server.h"
#include <module_log/log.h>
#include <stdio.h>
#include <string.h>

/**
 * start socket and client
 */
SOCKET_API int startServer$Client();

#ifdef __cplusplus
}
#endif

#endif /* socket_demo_h */
