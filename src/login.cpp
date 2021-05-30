//
// Created by 19216 on 2021/5/28.
//

#include <iostream>
#include "client.h"

using namespace std;
void OnLoginCallback(const nim::LoginRes& login_res) {
    cout << "login callback thread id : " << this_thread::get_id() << endl;
//    if(login_res.login_step_ == nim::kNIMLoginStepLogin) {
//        if(login_res.res_code_ == nim::kNIMResSuccess) {
//            cout << "Login success ..." << endl;
//        } else {
//            cout << "Login result code is " << login_res.res_code_ << ", login failed ..." << endl;
//        }
//    } else {
//        cout << "Login " << login_res.login_step_ << " step ..." << endl;
//    }
    if (login_res.res_code_ == nim::kNIMResSuccess) {
        cout << "login result success ..." << endl;
        if(login_res.login_step_ == nim::kNIMLoginStepLogin) {
            cout << "login checking ..." << endl;
        }
    } else {
        cout << "login result failed ..." << endl;
    }
}

void Login(const std::string& appKey, const std::string& account, const std::string& token) {
    cout << "start login ..." << endl;
    if(!nim::Client::Login(appKey, account, token, &OnLoginCallback)) {
        cout << "login failed ..." << endl;
    }
    cout << "end login ..." << endl;
}

void OnLogoutCallback(nim::NIMResCode res_code) {
    cout << "logout callback, rescode is " << res_code << endl;
    // 退出程序
    nim::Client::Cleanup();

    // 如果是退出到登录界面，则不能执行清理工作，否则会报错
}

void Logout() {
    // 登出到登录界面(nim::kNIMLogoutChangeAccout) 或者 退出程序(nim::kNIMLogoutAppExit)
    nim::Client::Logout(nim::kNIMLogoutAppExit, &OnLogoutCallback);
}

