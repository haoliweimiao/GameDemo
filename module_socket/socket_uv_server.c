#include "socket_uv_server.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>
#include <module_log/log.h>

#define DEFAULT_BACKLOG 128

uv_loop_t *loop;
struct sockaddr_in addr;

typedef struct
{
    uv_write_t req;
    uv_buf_t buf;
} write_req_t;

void free_write_req(uv_write_t *req)
{
    write_req_t *wr = (write_req_t *)req;
    free(wr->buf.base);
    free(wr);
}

void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
    buf->base = (char *)malloc(suggested_size);
    buf->len = suggested_size;
}

void on_close(uv_handle_t *handle)
{
    free(handle);
}

void echo_write(uv_write_t *req, int status)
{
    if (status)
    {
        LOG_E("Write error %s", uv_strerror(status));
    }

    free_write_req(req);
}

void echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
    if (nread > 0)
    {
        write_req_t *req = (write_req_t *)malloc(sizeof(write_req_t));
        req->buf = uv_buf_init(buf->base, nread);
        LOG_I("server recv len: %d: content: \n%s", strlen(buf->base), buf->base);
        uv_write((uv_write_t *)req, client, &req->buf, 1, echo_write);
        return;
    }
    if (nread < 0)
    {
        if (nread != UV_EOF)
            LOG_E("Read error %s", uv_err_name(nread));
        uv_close((uv_handle_t *)client, on_close);
    }

    free(buf->base);
}

void on_new_connection(uv_stream_t *server, int status)
{
    if (status < 0)
    {
        LOG_E("New connection error %s", uv_strerror(status));
        // error!
        return;
    }

    uv_tcp_t *client = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, client);
    int ret = uv_accept(server, (uv_stream_t *)client);
    if (ret == 0)
    {
        ret = uv_read_start((uv_stream_t *)client, alloc_buffer, echo_read);
        if (ret)
        {
            LOG_I("uv_read_start result:%d", ret);
        }
    }
    else
    {
        LOG_E("on_new_connection failed");
        uv_close((uv_handle_t *)client, on_close);
    }
}

/**
 * uv socket demo
 */
SOCKET_API int startUvSocketServer()
{

    loop = uv_default_loop();

    uv_tcp_t server;
    uv_tcp_init(loop, &server);

    uv_ip4_addr(SOCKET_LOCAL_URL, SOCKET_LOCAL_PORT, &addr);

    uv_tcp_bind(&server, (const struct sockaddr *)&addr, 0);
    int ret = 0;

    ret = uv_listen((uv_stream_t *)&server, DEFAULT_BACKLOG, on_new_connection);
    if (ret)
    {
        LOG_E("Listen error %s", uv_strerror(ret));
        return FUN_SOCKET_SERVER_LISTEN_ERROR;
    }

    ret = uv_run(loop, UV_RUN_DEFAULT);

    return FUN_NORMAL;
}