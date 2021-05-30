//
// Created by 19216 on 2021/5/28.
//
#include "client.h"

const std::string app_key = "3f60bf50f8c77e3e9d91ac890f36b0e5";

bool InitInstance(const std::string& appKey) {

    // 初始化云信SDK
    nim::SDKConfig sdk_config;
    // 设置数据库秘钥前缀
    sdk_config.database_encrypt_key_ = "NIMClient";
    // 初始化IM SDK
    bool ret = nim::Client::Init(appKey, "NIMClient",
                                 "", sdk_config);
    return ret;
}