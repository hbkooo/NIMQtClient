
#include <QApplication>
#include <QDebug>

#include "window/qmainwindow.h"
#include "login/loginwindow.h"
#include "src/client.h"

#ifdef NIM_SDK_DLL_IMPORT
#define TEST "NIM_SDK_DLL_IMPORT"
#else
#define TEST "NOT NIM_SDK_DLL_IMPORT"
#endif

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    if(!InitInstance(app_key)) {
        qDebug() << "sdk init failed ...";
        return -1;
    }
    // 初始化聊天室资源
    InitChatRoom();

    LoginWindow login;
    login.show();

    return QApplication::exec();
}
