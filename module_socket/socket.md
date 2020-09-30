# socket

+ [参数说明](#参数说明)
+ [Socket传输协议](#Socket传输协议)
    + [心跳](#心跳)
    + [文本传输](#文本传输)

## 参数说明

|参数|说明|
|:-|:-|
| id | 消息ID |

|参数|说明|
|:-|:-|
| len | 消息段总长度(消息过长会拆分成多个) |

|参数|说明|
|:-|:-|
| lenID | 消息段ID(消息过长会拆分成多个, 发送的第几段ID) |

|参数|说明|
|:-|:-|
| type | 消息类型 |
|    | heartbreak : 心跳 |
|    | text : 文本传输 |

|参数|说明|
|:-|:-|
| content | 消息内容 |

|参数|说明|
|:-|:-|
| contentLen | 消息内容长度，不包含结束符 |

## Socket传输协议

### 心跳

``` c
// client 发送 {"type":"heartbreak", "id":"12345678", "len":"1", "lenID":"1", "content":"ping", "contentLen":4}
// server 发送 {"type":"heartbreak", "id":"12345678", "len":"1", "lenID":"1", "content":"pong", "contentLen":4}
```

### 文本传输

``` c
// client 发送 {"type":"text", "id":"12345678", "len":"3", "lenID":"1", "content":"text111...", "contentLen":4096}
// client 发送 {"type":"text", "id":"12345678", "len":"3", "lenID":"2", "content":"text222...", "contentLen":4096}
// client 发送 {"type":"text", "id":"12345678", "len":"3", "lenID":"3", "content":"text333...", "contentLen":1024}
// server 发送 {"type":"text", "id":"12345678", "len":"1", "lenID":"1", "content":"finish", "contentLen":6}
```
