//
// Created by 19216 on 2021/5/28.
//
#include "client.h"

const std::string app_key = "3f60bf50f8c77e3e9d91ac890f36b0e5";
//const std::string app_key = "89253e22460f67d7384da8550b0724eb";
//const std::string app_key = "go9dnk49bkd9jd9vmel1kglw0803mgq3";

bool InitInstance(const std::string& appKey) {

    // 初始化云信SDK
    nim::SDKConfig sdk_config;
    // 设置数据库秘钥前缀
    sdk_config.database_encrypt_key_ = "NIMClient";
    // 初始化IM SDK
    bool ret = nim::Client::Init(appKey, "NIMClient",
                                 "", sdk_config);

//    sdk_config.database_encrypt_key_ = "NIMAudioVideo";
//    bool ret = nim::Client::Init(appKey, "NIMAudioVideo",
//                                 "", sdk_config);
    return ret;
}