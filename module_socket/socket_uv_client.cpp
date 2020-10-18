#include "socket_uv_client.h"

#include <iostream>
#include <json/json.h>
#include <module_log/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

uv_loop_t mLoop;
uv_tcp_t mTcpClient;
uv_connect_t mConnRrequest;
uv_write_t mWriteRequest;
int mClientState;

static void clientWriteCB(uv_write_t *req, int status) {
  LOG_I("clientWriteCB status: %d, %s", status, strerror(status));

  int ret = uv_is_readable(req->handle);
  LOG_I("uv_is_readable %d", ret);

  ret = uv_is_writable(req->handle);
  LOG_I("uv_is_writable %d", ret);

  ret = uv_is_closing((uv_handle_t *)req->handle);
  LOG_I("uv_is_closing %d", ret);
  LOG_I("client msg %s", req->bufs->base);

  free(req);

  uv_close((uv_handle_t *)req->handle, NULL);
}

static void clientConnectCB(uv_connect_t *req, int status) {
  if (status != 0) {
    LOG_I("clientConnectCB error status: %d", status);
    free(req);
  }

  mClientState = status;
}

/**
 * client send message
 * @params message: send message
 * @params len:     send message lenght
 */
SOCKET_API int clientSendMessage(const char *message, int len) {
  if (mClientState != 0) {
    return FUN_SOCKET_NOT_CONNECT_ERROR;
  }

  uv_buf_t buf = uv_buf_init((char *)message, len);

  int ret = uv_write(&mWriteRequest, (uv_stream_t *)&mTcpClient, &buf, 1,
                     clientWriteCB);

  //    LOG_I("client ret 1 %d",ret);

  if (ret != 0) {
    return FUN_SOCKET_CLIENT_SEND_MSG_ERROR;
  }

  return FUN_NORMAL;
}

/**
 * init client
 */
SOCKET_API int initClient() {
  memset(&mLoop, 0, sizeof(uv_loop_t));
  memset(&mTcpClient, 0, sizeof(uv_tcp_t));
  memset(&mConnRrequest, 0, sizeof(uv_connect_t));
  struct sockaddr_in sa;
  int ret = uv_ip4_addr(SOCKET_LOCAL_URL, SOCKET_LOCAL_PORT, &sa);
  if (ret != 0) {
    return FUN_SOCKET_CONNECT_ERROR;
  }

  ret = uv_loop_init(&mLoop);
  if (ret != 0) {
    return FUN_SOCKET_CONNECT_ERROR;
  }

  ret = uv_tcp_init(&mLoop, &mTcpClient);
  if (ret != 0) {
    return FUN_SOCKET_CONNECT_ERROR;
  }

  ret = uv_tcp_connect(&mConnRrequest, &mTcpClient,
                       (const struct sockaddr *)&sa, clientConnectCB);
  if (ret != 0) {
    return FUN_SOCKET_CONNECT_ERROR;
  }

  uv_run(&mLoop, UV_RUN_DEFAULT);
  return FUN_NORMAL;
}
