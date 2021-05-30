//
// Created by 19216 on 2021/5/29.
//

#ifndef NIMQTCLIENT_REGISTERWIDGET_H
#define NIMQTCLIENT_REGISTERWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QEvent>

#include "client.h"

#include <QDebug>

class RegisterWidget : public QWidget {
Q_OBJECT

public:
    explicit RegisterWidget(QWidget *parent = nullptr);

    ~RegisterWidget() override;

    void setVisible(bool visible) override;


private:
    void InitControl();
    void SetLayout();
    void SetConnect();

    void clear();       // 清空输入框中的内容

private:
    QLineEdit *usernameLE;      // 用户名输入框
    QIcon userNormalIcon;       // 用户未选中时的icon图标
    QIcon userSelectIcon;       // 用户选中时的icon图标
    QIcon userErrorIcon;        // 用户名错误时的icon图标
    QPushButton *userIconBtn;   // 用户输入框图标显示在按钮上

    QLineEdit *nickLE;          // 昵称输入框
    QIcon nickNormalIcon;       // 昵称未选中时的icon图标
    QIcon nickSelectIcon;       // 昵称选中时的icon图标
    QIcon nickErrorIcon;        // 昵称错误时的icon图标
    QPushButton *nickIconBtn;   // 用户输入框图标显示在按钮上

    QLineEdit *passwordLE;      // 密码输入框
    QIcon pwdNormalIcon;        // 密码未选中时的icon图标
    QIcon pwdSelectIcon;        // 密码选中时的icon图标
    QIcon pwdErrorIcon;         // 密码错误时的icon图标
    QPushButton *pwdIconBtn;    // 密码输入框图标显示在按钮上

    QWidget *user_nick_pwd_widget;   // 用户名、昵称和密码输入框组合的一个控件
    QLabel *helpInfoLB;         // 帮助信息提示
    QPushButton *registerBtn;   // 注册按钮

    QVBoxLayout *mainLayout;    // 主界面布局

public slots:
    bool eventFilter(QObject *obj, QEvent *ev) override;     // 注册监听器
    void OnRegisterClicked();

};


#endif //NIMQTCLIENT_REGISTERWIDGET_H
