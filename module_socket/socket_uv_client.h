#ifndef socket_uv_client_h
#define socket_uv_client_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "socket_api.h"

    /**
     * uv socket client
     */
    SOCKET_API int startUvSocketClient();

#ifdef __cplusplus
}
#endif

#endif /* socket_uv_client_h */