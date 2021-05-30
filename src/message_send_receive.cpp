//
// Created by 19216 on 2021/5/28.
//
#include "client.h"

void sendTextMessage(const std::string &content) {

    std::string msg_json = nim::Talk::CreateTextMessage("HBK1", nim::kNIMSessionTypeP2P, nim::Tool::GetUuid(),
                                                        content, nim::MessageSetting());
    nim::Talk::SendMsg(msg_json);
}

