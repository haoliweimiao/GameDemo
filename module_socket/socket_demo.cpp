#include "socket_demo.h"
#include <iostream>
#include <json/json.h>
#include <module_base/cfg_base.h>
#include <pthread.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

CFG_API int readFromStringDemo() {
  const std::string rawJson = R"({"Age": 20, "Name": "colin"})";
  const auto rawJsonLength = static_cast<int>(rawJson.length());
  JSONCPP_STRING err;
  Json::Value root;

  Json::CharReaderBuilder builder;
  const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
  if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJsonLength, &root,
                     &err)) {
    std::cout << "error" << std::endl;
    return EXIT_FAILURE;
  }

  const std::string name = root["Name"].asString();
  const int age = root["Age"].asInt();

  std::cout << name << std::endl;
  std::cout << age << std::endl;

  Json::Value createJson;
  // createJson["null"] = NULL; //注意此处在输出是显示为0，而非null
  createJson["message"] = "OK";
  createJson["age"] = 52;
  createJson["array"].append(
      "arr"); // 新建一个key为array，类型为数组，对第一个元素赋值为字符串“arr”
  createJson["array"].append(
      123); // 为数组 key_array 赋值，对第二个元素赋值为：1234
  createJson["test"].append(createJson);

  Json::ValueType type = createJson.type(); // createJson的类型

  std::cout << createJson.toStyledString() << std::endl; //格式化输出
  std::cout << "createJson_type：" << type
            << std::endl; //类型为7，即为类型为对象

  // Json::FastWriter fast_writer;
  // std::string str = fast_writer.write(createJson);
  // std::cout << str << std::endl;

  // Json::StyledWriter style_writer;
  // str = style_writer.write(createJson);
  // std::cout << str << std::endl;

  //     // 判断key是否存在
  //     bool is_age = root.isMember("age");
  //     cout << "isMember:" << is_age << endl;

  //     // 判断是否为null
  //     //bool is_null = root["null"].isNull(); //注意此处被赋值为0，而非null
  //     bool is_null = json_object["null"].isNull();
  //     cout << "is_null:" << is_null << endl;

  //     // 得到所有的key
  //     for (auto elem : root.getMemberNames())
  //     {
  //         cout << elem << " ";
  //     }
  //     cout << endl;

  //     // 删除成员
  //     cout << "remove_age:" << root.removeMember("age") << endl;

  return EXIT_SUCCESS;
}

void *startServer(void *p) {
  // LOG_TIME();
  // startSocketServer();
  startUvSocketServer();
  return 0;
}

void *startClient(void *p) {

  // LOG_TIME();
  int ret = initClient();
  if (ret != FUN_NORMAL) {
    LOG_E("init client failed!");
  }
  char message[SOCKET_DATA_LEN] = {0};
  createPingMessage(message);
  int sendMsgLen = strlen(message);
  ret = clientSendMessage(message, sendMsgLen);
  return 0;
}

/**
 * start socket and client
 */
SOCKET_API int startServer$Client() {

  //    readFromStringDemo();
  int rc;
  pthread_t id;
  // 创建第一个线程
  rc = pthread_create(&id, NULL, startServer, NULL);
  if (rc)
    printf("Failed to create the thread startServer().");
  // 休眠1s，让server先创建完
  // sleep(1);
  // 创建第二个线程
  while (1) {
    sleep(1);
    rc = pthread_create(&id, NULL, startClient, NULL);
    if (rc)
      printf("Failed to create the thread startClient().");
  }

  // 阻塞主线程的运行，以免主线程运行结束时提前终止子线程
  pthread_join(id, NULL);

  return FUN_NORMAL;
}
