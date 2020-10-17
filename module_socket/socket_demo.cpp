#include "socket_demo.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <stddef.h>
#include <string.h>
#include <module_base/cfg_base.h>
#include <json/json.h>

static pthread_mutex_t mSocketDemoLock = PTHREAD_MUTEX_INITIALIZER;
static int mMsgId = 0;

int getMessageId()
{
    pthread_mutex_lock(&mSocketDemoLock);
    mMsgId++;
    pthread_mutex_unlock(&mSocketDemoLock);
    return mMsgId;
}

int jsoncppDemo()
{
    //     using namespace std;
    //     const char *age;
    //     Json::Value root;
    //     Json::FastWriter fast_writer;
    //     Json::StyledWriter style_writer;
    //     Json::StyledStreamWriter stream_writer;
    //     Json::Reader reader;
    //     Json::Value json_object;

    //     root["null"] = NULL; //注意此处在输出是显示为0，而非null
    //     root["message"] = "OK";
    //     root["age"] = 52;
    //     root["array"].append("arr"); // 新建一个key为array，类型为数组，对第一个元素赋值为字符串“arr”
    //     root["array"].append(123);   // 为数组 key_array 赋值，对第二个元素赋值为：1234

    //     Json::ValueType type = root.type(); //root的类型

    //     cout << root.toStyledString() << endl; //格式化输出
    //     cout << "root_type：" << type << endl; //类型为7，即为类型为对象

    //     // 写到本地文件
    //     cout << "快速输出：" << endl;
    //     string str = fast_writer.write(root);
    //     cout << str << endl; //快速输出,紧凑型
    //     ofstream ofs("fast_writer.json");
    //     ofs << str;
    //     ofs.close();

    //     cout << "格式化输出：" << endl;
    //     str = style_writer.write(root);
    //     cout << str << endl; //格式化输出，排版型
    //     ofs.open("style_writer.json");
    //     ofs << str;
    //     ofs.close();

    //     // 对字符串解析
    //     //const char* json_document = "{\"age\" : 12, \"name\" : \"weng\"}";
    //     string json_document = "{\"age\" : 123, \"name\" : \"weng\"}";
    //     if (!reader.parse(json_document, json_object))
    //     {
    //         cout << "error" << endl;
    //         return 0;
    //     }
    //     else
    //     {
    //         cout << "age:" << json_object["age"] << " name" << json_object["name"] << endl;
    //     }

    //     // 对文件解析
    //     ifstream ifs("E:\\demo\\JsonTest\\JsonTest\\example.json", ios::binary);
    //     if (!reader.parse(ifs, json_object))
    //     {
    //         cout << "open error" << endl;
    //         ifs.close();
    //     }
    //     else
    //     {
    //         cout << "encoding:" << json_object["encoding"].asString() << endl;
    //         cout << "age:" << json_object["age"].asInt() << endl;
    //         int num = json_object["plug"].size();
    //         for (int i = 0; i < num; i++)
    //         {
    //             cout << json_object["plug"][i].asString() << " ";
    //         }
    //         ifs.close();
    //         cout << endl;
    //     }

    //     // 判断key是否存在
    //     bool is_age = root.isMember("age");
    //     cout << "isMember:" << is_age << endl;

    //     // 判断是否为null
    //     //bool is_null = root["null"].isNull();			//注意此处被赋值为0，而非null
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

    //     system("pause");
    return 0;
}

CFG_API int readFromStringDemo()
{
    const std::string rawJson = R"({"Age": 20, "Name": "colin"})";
    const auto rawJsonLength = static_cast<int>(rawJson.length());
    constexpr bool shouldUseOldWay = false;
    JSONCPP_STRING err;
    Json::Value root;

    if (shouldUseOldWay)
    {
        Json::Reader reader;
        reader.parse(rawJson, root);
    }
    else
    {
        Json::CharReaderBuilder builder;
        const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
        if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJsonLength, &root,
                           &err))
        {
            std::cout << "error" << std::endl;
            return EXIT_FAILURE;
        }
    }
    const std::string name = root["Name"].asString();
    const int age = root["Age"].asInt();

    std::cout << name << std::endl;
    std::cout << age << std::endl;

    Json::Value createJson;
    // createJson["null"] = NULL; //注意此处在输出是显示为0，而非null
    createJson["message"] = "OK";
    createJson["age"] = 52;
    createJson["array"].append("arr"); // 新建一个key为array，类型为数组，对第一个元素赋值为字符串“arr”
    createJson["array"].append(123);   // 为数组 key_array 赋值，对第二个元素赋值为：1234
    createJson["test"].append(createJson);

    Json::ValueType type = createJson.type(); //createJson的类型

    std::cout << createJson.toStyledString() << std::endl; //格式化输出
    std::cout << "createJson_type：" << type << std::endl; //类型为7，即为类型为对象

    // Json::FastWriter fast_writer;
    // std::string str = fast_writer.write(createJson);
    // std::cout << str << std::endl;

    // Json::StyledWriter style_writer;
    // str = style_writer.write(createJson);
    // std::cout << str << std::endl;

    return EXIT_SUCCESS;
}

void *startServer(void *p)
{
    // LOG_TIME();
    // startSocketServer();
    startUvSocketServer();
    return 0;
}

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

void *startClient(void *p)
{

    // LOG_TIME();
    int ret = initClient();
    if (ret != FUN_NORMAL)
    {
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
SOCKET_API int startServer$Client()
{

    readFromStringDemo();
    int rc;
    pthread_t id;
    // 创建第一个线程
    rc = pthread_create(&id, NULL, startServer, NULL);
    if (rc)
        printf("Failed to create the thread startServer().");
    // 休眠1s，让server先创建完
    // sleep(1);
    // 创建第二个线程
    while (1)
    {
        sleep(1);
        rc = pthread_create(&id, NULL, startClient, NULL);
        if (rc)
            printf("Failed to create the thread startClient().");
    }

    // 阻塞主线程的运行，以免主线程运行结束时提前终止子线程
    pthread_join(id, NULL);

    return FUN_NORMAL;
}