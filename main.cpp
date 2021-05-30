
#include <QApplication>
#include <QDebug>
#include<QPixmap>
#include <iostream>

#include "window/qmainwindow.h"
#include "login/loginwindow.h"
#include "src/client.h"

#ifdef NIM_SDK_DLL_IMPORT
#define TEST "NIM_SDK_DLL_IMPORT"
#else
#define TEST "NOT NIM_SDK_DLL_IMPORT"
#endif

void initData(MainWindow &w) {
    QDateTime time = QDateTime::currentDateTime().addDays(-16);
    Message msg = {QPixmap(":/header/header1"),
                   "韩冰凯",
                   {"在干嘛呢？"},
                   time.addYears(-1)};
//    w.addMessageItem(msg);  // 新增一个会话item

}

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    if(!InitInstance(app_key)) {
        qDebug() << "sdk init failed ...";
        return -1;
    }

    LoginWindow login;
    login.show();


    return QApplication::exec();
}
