//
// Created by 19216 on 2021/5/28.
//

#ifndef NIMQTCLIENT_LOGINWINDOW_H
#define NIMQTCLIENT_LOGINWINDOW_H

#include <iostream>

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QSettings>

#include "qmainwindow.h"
#include "client.h"
#include "registerwidget.h"

class LoginWindow : public QWidget {
Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);

    ~LoginWindow() override;

private:
    void InitControl();
    void SetLayout();
    void SetConnect();

private:
    // 登录回调
    void OnLoginCallback(const nim::LoginRes& login_res);
    // 记住账号密码
    void SavePwd();
    // 加载账号密码密码
    void LoadPwd();

private:
    /// API 获取用户信息操作
    // 获取本地用户信息
    void GetUserNameCard(const std::string & account);
    // 获取服务器用户信息
    void GetUserNameCardOnLine(const std::string & account);
    //  获取用户信息回调
    void OnGetUserCard(const std::list<nim::UserNameCard> &json_result);

protected:
    void closeEvent(QCloseEvent* event) override;

private:

    QPushButton *registerBtn;   // 注册按钮

    QLineEdit *usernameLE;      // 用户名输入框
    QIcon userNormalIcon;       // 用户未选中时的icon图标
    QIcon userSelectIcon;       // 用户选中时的icon图标
    QIcon userErrorIcon;        // 用户名错误时的icon图标
    QPushButton *userIconBtn;   // 用户输入框图标显示在按钮上

    QLineEdit *passwordLE;      // 密码输入框
    QIcon pwdNormalIcon;        // 密码未选中时的icon图标
    QIcon pwdSelectIcon;        // 密码选中时的icon图标
    QIcon pwdErrorIcon;         // 密码错误时的icon图标
    QPushButton *pwdIconBtn;    // 密码输入框图标显示在按钮上

    QWidget *user_pwd_widget;   // 用户名和密码输入框组合的一个控件

    QCheckBox *rememberCB;      // 记住密码

    QLabel *helpInfoLB;         // 帮助信息提示
    QPushButton *loginBtn;      // 登录按钮

    QWidget *loginWidget;           // 登录时的界面控件
    RegisterWidget *registerWidget; // 注册时的控件信息

    QVBoxLayout *mainLayout;    // 主界面布局

    MainWindow *mainWindow = nullptr;   // 登录成功主界面

    signals:
    void LoginSuccessSignal();
    void LoginFailedSignal(QString errorInfo);

    void GetLoginUserNameCardSuccessSignal();

public slots:
    bool eventFilter(QObject *obj, QEvent *ev) override;     // 注册监听器
    void OnLoginClicked();
    void OnRegisterClicked();

    void OnLogoutSlot();        // 在主界面退出登录时回调到这里的槽函数

    void LoginSuccessSlot();    // 登录成功
    void LoginFailedSlot(const QString& errorInfo);    // 登录失败

};


#endif //NIMQTCLIENT_LOGINWINDOW_H
