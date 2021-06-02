//
// Created by 19216 on 2021/5/28.
//

#ifndef NIMQTCLIENT_CLIENT_H
#define NIMQTCLIENT_CLIENT_H

#include <string>
#include "nim_cpp_wrapper/nim_cpp_api.h"

const extern std::string app_key;

// 初始化
bool InitInstance(const std::string& appKey);

// 登录
void Login(const std::string& appKey, const std::string& account, const std::string& token);

// 登出
void Logout();

// 发送文本消息
void sendTextMessage(const std::string &receiver, const std::string &content);

#endif //NIMQTCLIENT_CLIENT_H
