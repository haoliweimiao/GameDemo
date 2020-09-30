//
// Created by 吴祎诚 on 2020/9/26.
//

#ifndef REMOTEPROTOCOLMODULE_SOCKET_SERVER_H
#define REMOTEPROTOCOLMODULE_SOCKET_SERVER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "socket_api.h"

    /**
     * start server
     * @return fun return value
     */
    SOCKET_API int startSocketServer();
    /**
     * stop server
     * @return fun return value
     */
    SOCKET_API int stopServer();

#ifdef __cplusplus
}
#endif

#endif //REMOTEPROTOCOLMODULE_SOCKET_SERVER_H
