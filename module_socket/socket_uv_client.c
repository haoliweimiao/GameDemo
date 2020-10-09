#include "socket_uv_client.h"
#include <module_log/log.h>
#include <uv.h>

uv_loop_t mLoop;
uv_tcp_t mTcpClient;
uv_connect_t mConnRrequest;
uv_write_t mWriteRequest;
int mClientState;

static void clientWriteCB(uv_write_t *req, int status)
{
    LOG_I("clientWriteCB status: %d, %s\n", status, strerror(status));
    uv_close((uv_handle_t *)req->handle, NULL);
}

static void clientConnectCB(uv_connect_t *req, int status)
{
    LOG_I("clientConnectCB status: %d\n", status);
    mClientState = status;
}

/**
 * client send message
 * @params message: send message
 * @params len:     send message lenght
 */
SOCKET_API int clientSendMessage(const char *message, int len)
{
    if (mClientState != 0)
    {
        return FUN_SOCKET_NOT_CONNECT_ERROR;
    }

    uv_buf_t buf = uv_buf_init(message, len);

    int ret = uv_write(&mWriteRequest,
                       (uv_stream_t *)&mTcpClient,
                       &buf, 1,
                       clientWriteCB);

    if (ret != 0)
    {
        return FUN_SOCKET_CLIENT_SEND_MSG_ERROR;
    }

    return FUN_NORMAL;
}

/**
 * init client
 */
SOCKET_API int initClient()
{
    memset(&mLoop, 0, sizeof(uv_loop_t));
    memset(&mTcpClient, 0, sizeof(uv_tcp_t));
    memset(&mConnRrequest, 0, sizeof(uv_connect_t));
    struct sockaddr_in sa;
    int ret = uv_ip4_addr(SOCKET_LOCAL_URL, SOCKET_LOCAL_PORT, &sa);
    if (ret != 0)
    {
        return FUN_SOCKET_CONNECT_ERROR;
    }

    ret = uv_loop_init(&mLoop);
    if (ret != 0)
    {
        return FUN_SOCKET_CONNECT_ERROR;
    }

    ret = uv_tcp_init(&mLoop, &mTcpClient);
    if (ret != 0)
    {
        return FUN_SOCKET_CONNECT_ERROR;
    }

    ret = uv_tcp_connect(&mConnRrequest,
                         &mTcpClient,
                         (const struct sockaddr *)&sa,
                         clientConnectCB);
    if (ret != 0)
    {
        return FUN_SOCKET_CONNECT_ERROR;
    }

    uv_run(&mLoop, UV_RUN_DEFAULT);
    return FUN_NORMAL;
}