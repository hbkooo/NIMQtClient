//
// Created by 19216 on 2021/5/28.
//

#ifndef NIMQTCLIENT_CLIENT_H
#define NIMQTCLIENT_CLIENT_H

#include <QObject>
#include <QDebug>
#include <string>
#include "nim_cpp_wrapper/nim_cpp_api.h"
#include "nim_chatroom.h"
#include "nim_chatroom_cpp_wrapper/nim_cpp_chatroom_api.h"

extern nim::UserNameCard SELF_USER_NAME_CARD;

const extern std::string app_key;

// 初始化云信SDK
bool InitInstance(const std::string& appKey);

// 初始化聊天室 SDK
void InitChatRoom();

// 登录
void Login(const std::string& appKey, const std::string& account, const std::string& token);

// 登出
void Logout();

// 发送文本消息
void sendTextMessage(const std::string &receiver, const std::string &content);


#endif //NIMQTCLIENT_CLIENT_H
