#include "socket_uv_client.h"
#include <json/json.h>
#include <iostream>
#include <module_log/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

uv_loop_t mLoop;
uv_tcp_t mTcpClient;
uv_connect_t mConnRrequest;
uv_write_t mWriteRequest;
int mClientState;

typedef struct {
    uv_write_t req;
    uv_buf_t buf;
} write_req_t;

typedef struct {
  int pongs;
  int state;
  uv_tcp_t tcp;
  uv_connect_t connect_req;
  uv_shutdown_t shutdown_req;
} pinger_t;

static void clientWriteCB(uv_write_t *req, int status) {
  LOG_I("clientWriteCB status: %d, %s", status, strerror(status));
  uv_close((uv_handle_t *)req->handle, NULL);
}

typedef struct buf_s {
  uv_buf_t uv_buf_t;
  struct buf_s *next;
} buf_t;

static buf_t *buf_freelist = NULL;

static void buf_alloc(uv_handle_t *tcp, size_t size, uv_buf_t *buf) {
  buf->base = (char *)malloc(size);
  buf->len = size;
}

static void pinger_read_cb(uv_stream_t *tcp, ssize_t nread,
                           const uv_buf_t *buf) {
  if (nread > 0) {
    write_req_t *req = (write_req_t *)malloc(sizeof(write_req_t));
    req->buf = uv_buf_init(buf->base, nread);
    char *message = buf->base;
    int clientMsgLen = strlen(buf->base);
    if (clientMsgLen == 0) {
      LOG_E("server recv len: 0!");
      return;
    }

    const auto rawJsonLength = static_cast<int>(clientMsgLen);

    JSONCPP_STRING err;
    Json::Value root;

    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    if (!reader->parse(message, message + rawJsonLength, &root, &err)) {
      std::cout << "error" << std::endl;
      return;
    }

    const std::string type = root[SOCKET_MSG_KEY_TYPE].asString();
    const std::string content = root[SOCKET_MSG_KEY_CONTENT].asString();
    const int id = root[SOCKET_MSG_KEY_ID].asInt();

    LOG_I("client recv type: %s: content: %s", type.c_str(), content.c_str());

    if (strcmp(SOCKET_TYPE_HEART_BREAK, type.c_str())) {
      char callbackMsg[SOCKET_DATA_LEN] = {0};
      createPongMessage(callbackMsg, id);
      //        uv_buf_t *bufCallback;
      //        bufCallback->base=callbackMsg;
      //        bufCallback->len=strlen(callbackMsg);
      uv_write((uv_write_t *)req, client, &req->buf, 1, echo_write);
    }
    uv_write((uv_write_t *)req, client, &req->buf, 1, echo_write);
    return;
  }
  if (nread < 0) {
    if (nread != UV_EOF)
      LOG_E("Read error %s", uv_err_name(nread));
    uv_close((uv_handle_t *)client, on_close);
  }

  free(buf->base);
}

static void clientConnectCB(uv_connect_t *req, int status) {
  if (status != 0) {
    LOG_I("clientConnectCB error status: %d", status);
  }

  mClientState = status;

  if (uv_read_start(req->handle, buf_alloc, pinger_read_cb)) {
    FATAL("uv_read_start failed");
  }
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
