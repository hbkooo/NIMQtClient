//
// Created by 19216 on 2021/5/28.
//
#include "client.h"

const std::string app_key = "3f60bf50f8c77e3e9d91ac890f36b0e5";

// 初始化云信SDK
bool InitInstance(const std::string& appKey) {

    // 初始化云信SDK
    nim::SDKConfig sdk_config;
    // 设置数据库秘钥前缀
    sdk_config.database_encrypt_key_ = "NIMClient";
    // 初始化IM SDK。app_install_dir 表示 nim.dll 链接库所放的存储位置
    bool ret = nim::Client::Init(appKey, "NIMClient",
                                 "", sdk_config);
    return ret;
}

// 初始化聊天室 SDK
void InitChatRoom() {
    qDebug() << "[info]: 初始化聊天室资源 ...";
    // 初始化聊天室资源 SDK。app_install_dir 表示 nim_chatroom.dll 链接库所放的存储位置
    nim_chatroom::ChatRoom::Init("");
    qDebug() << "[info]: 聊天室资源加载结束";
}