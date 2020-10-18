#include "socket_uv_server.h"

#include <iostream>
#include <json/json.h>
#include <module_log/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

#define DEFAULT_BACKLOG 128

uv_loop_t *loop;
struct sockaddr_in addr;

typedef struct {
  uv_write_t req;
  uv_buf_t buf;
} write_req_t;

void free_write_req(uv_write_t *req) {
  write_req_t *wr = (write_req_t *)req;
  free(wr->buf.base);
  free(wr);
}

void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
  buf->base = (char *)malloc(suggested_size);
  buf->len = suggested_size;
  LOG_E("server alloc_buffer");
}

void on_close(uv_handle_t *handle) {
  free(handle);
  LOG_E("server on_close");
}

void echo_write(uv_write_t *req, int status) {
  if (status) {
    LOG_E("Write error %s", uv_strerror(status));
  }

  uv_close((uv_handle_t *)req->handle, on_close);
  //    free_write_req(req);
  LOG_E("server echo_write");
}

/**
 * 创建pong消息返回给client
 */
void createPongMessage(char *message, const int messageID) {
  memset(message, '\0', 1);
  Json::Value createJson;
  // {"type":"heartbreak", "id":"12345678", "len":"1", "lenID":"1",
  // "content":"ping", "contentLen":4}
  createJson[SOCKET_MSG_KEY_TYPE] = SOCKET_TYPE_HEART_BREAK;
  createJson[SOCKET_MSG_KEY_ID] = messageID;
  createJson[SOCKET_MSG_KEY_LEN] = 1;
  createJson[SOCKET_MSG_KEY_CONTENT] = SOCKET_MSG_PING;
  int contentLen = strlen(SOCKET_MSG_PING);
  createJson[SOCKET_MSG_KEY_CONTENT_LEN] = contentLen;

  std::string jsonMsg = createJson.toStyledString();
  strcpy(message, jsonMsg.c_str());
}

void echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) {
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

    LOG_I("server recv type: %s: content: %s", type.c_str(), content.c_str());

    uv_write_t wr;
    int ret = strcmp(SOCKET_TYPE_HEART_BREAK, type.c_str());
    if (ret == 0) {
      char callbackMsg[SOCKET_DATA_LEN] = {0};
      createPongMessage(callbackMsg, id);
      uv_buf_t sndbuf = uv_buf_init(callbackMsg, strlen(callbackMsg));
      int ret = uv_write(&wr, client, &sndbuf, 1, echo_write);
      if (ret != 0) {
        LOG_E("server send message error!!");
      }
      LOG_E("server send message :%s", sndbuf.base);
      return;
    }
    ret = uv_write((uv_write_t *)req, client, &req->buf, 1, echo_write);
    if (ret != 0) {
      LOG_E("server send message error!!!!");
    }
    return;
  }
  if (nread < 0) {
    if (nread != UV_EOF)
      LOG_E("Read error %s", uv_err_name(nread));
    uv_close((uv_handle_t *)client, on_close);
  }

  free(buf->base);
}

void on_new_connection(uv_stream_t *server, int status) {
  if (status < 0) {
    LOG_E("New connection error %s", uv_strerror(status));
    // error!
    return;
  }

  uv_tcp_t *client = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));
  uv_tcp_init(loop, client);
  int ret = uv_accept(server, (uv_stream_t *)client);
  if (ret == 0) {
    ret = uv_read_start((uv_stream_t *)client, alloc_buffer, echo_read);
    if (ret) {
      LOG_I("uv_read_start result:%d", ret);
    }
  } else {
    LOG_E("on_new_connection failed");
    uv_close((uv_handle_t *)client, on_close);
  }
}

/**
 * uv socket demo
 */
SOCKET_API int startUvSocketServer() {

  loop = uv_default_loop();

  uv_tcp_t server;
  uv_tcp_init(loop, &server);

  uv_ip4_addr(SOCKET_LOCAL_URL, SOCKET_LOCAL_PORT, &addr);

  uv_tcp_bind(&server, (const struct sockaddr *)&addr, 0);
  int ret = 0;

  ret = uv_listen((uv_stream_t *)&server, DEFAULT_BACKLOG, on_new_connection);
  if (ret) {
    LOG_E("Listen error %s", uv_strerror(ret));
    return FUN_SOCKET_SERVER_LISTEN_ERROR;
  }

  ret = uv_run(loop, UV_RUN_DEFAULT);

  return FUN_NORMAL;
}
