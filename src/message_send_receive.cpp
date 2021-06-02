//
// Created by 19216 on 2021/5/28.
//
#include "client.h"

void sendTextMessage(const std::string &receiver, const std::string &content) {

    printf("receiver : %s\n", receiver.c_str());
    printf("content : %s\n", content.c_str());
    std::string msg_json = nim::Talk::CreateTextMessage(receiver, nim::kNIMSessionTypeP2P, nim::Tool::GetUuid(),
                                                        content, nim::MessageSetting());
    printf("message_json: %s\n", msg_json.c_str());
    nim::Talk::SendMsg(msg_json);
}

