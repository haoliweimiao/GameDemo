//
//  socket_api.cpp
//  lib_socket
//
//  Created by Von on 2020/10/18.
//

#include <json/json.h>
#include "socket_api.h"

static pthread_mutex_t mSocketDemoLock = PTHREAD_MUTEX_INITIALIZER;
static int mMsgId = 0;

/**
 * create socket message id
 */
int getMessageId()
{
    pthread_mutex_lock(&mSocketDemoLock);
    mMsgId++;
    pthread_mutex_unlock(&mSocketDemoLock);
    return mMsgId;
}

/**
 * 生成ping消息
 */
void createPingMessage(char *message)
{
    memset(message, '\0', 1);
    Json::Value createJson;
    // {"type":"heartbreak", "id":"12345678", "len":"1", "lenID":"1", "content":"ping", "contentLen":4}
    createJson[SOCKET_MSG_KEY_TYPE] = SOCKET_TYPE_HEART_BREAK;
    createJson[SOCKET_MSG_KEY_ID] = getMessageId();
    createJson[SOCKET_MSG_KEY_LEN] = 1;
    createJson[SOCKET_MSG_KEY_CONTENT] = SOCKET_MSG_PING;
    int contentLen = strlen(SOCKET_MSG_PING);
    createJson[SOCKET_MSG_KEY_CONTENT_LEN] = contentLen;

    std::string jsonMsg = createJson.toStyledString();
    strcpy(message, jsonMsg.c_str());
}
