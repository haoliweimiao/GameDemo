#include "socket_uv_client.h"
#include <uv.h>

uv_loop_t loop;
uv_tcp_t tcp_client;
uv_connect_t connection_request;
uv_write_t write_request;

static void write_cb(uv_write_t *req, int status)
{
    printf("write_cb status: %d, %s\n", status, strerror(status));
    uv_close((uv_handle_t *)req->handle, NULL);
}

static void connect_cb(uv_connect_t *req, int status)
{
    const char send[1024] = "hello world\n";
    uv_buf_t buf = uv_buf_init(send, strlen(send));
    printf("connect_cb status: %d\n", status);
    int r = uv_write(&write_request,
                     (uv_stream_t *)&tcp_client,
                     &buf, 1,
                     write_cb);
}

/**
 * uv socket client
 */
SOCKET_API int startUvSocketClient()
{

    memset(&loop, 0, sizeof(uv_loop_t));
    memset(&tcp_client, 0, sizeof(uv_tcp_t));
    memset(&connection_request, 0, sizeof(uv_connect_t));
    struct sockaddr_in sa;
    int ret = uv_ip4_addr(SOCKET_LOCAL_URL, SOCKET_LOCAL_PORT, &sa);
    if (ret != 0)
    {
        return FUN_SOCKET_CONNECT_ERROR;
    }

    ret = uv_loop_init(&loop);
    if (ret != 0)
    {
        return FUN_SOCKET_CONNECT_ERROR;
    }

    ret = uv_tcp_init(&loop, &tcp_client);
    if (ret != 0)
    {
        return FUN_SOCKET_CONNECT_ERROR;
    }

    ret = uv_tcp_connect(&connection_request,
                         &tcp_client,
                         (const struct sockaddr *)&sa,
                         connect_cb);
    if (ret != 0)
    {
        return FUN_SOCKET_CONNECT_ERROR;
    }

    uv_run(&loop, UV_RUN_DEFAULT);
    return FUN_NORMAL;
}