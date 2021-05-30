//
// Created by 19216 on 2021/5/29.
//

// You may need to build the project (run Qt uic code generator) to get "ui_RegisterWidget.h" resolved

#include "registerwidget.h"


RegisterWidget::RegisterWidget(QWidget *parent) :
        QWidget(parent){

    InitControl();
    SetLayout();
    SetConnect();
}

RegisterWidget::~RegisterWidget() {

}

void RegisterWidget::setVisible(bool visible) {
    clear();
    QWidget::setVisible(visible);
}

void RegisterWidget::clear() {
    usernameLE->clear();
    nickLE->clear();
    passwordLE->clear();
}

void RegisterWidget::InitControl() {

    // 用户名输入框样式
    usernameLE = new QLineEdit();
    usernameLE->setPlaceholderText("账号限32位字母或数字");
    usernameLE->setMaxLength(32);
    usernameLE->setFixedSize(280, 50);
    usernameLE->setTextMargins(36, 0, 0 , 0);
    usernameLE->installEventFilter(this);
    usernameLE->setAlignment(Qt::AlignVCenter);
    usernameLE->setStyleSheet("QLineEdit { border: 1px none #e5e5e5;"
                              "border-bottom-style:solid;"
                              "font-size:18px;"
                              "background:#ffffff;"
                              "color:#2c2c2c; }"
                              "QLineEdit:focus {"
                              "border-color:#238efa;}"
    );

    userNormalIcon.addPixmap(QPixmap(":/res/user_normal"));
    userSelectIcon.addPixmap(QPixmap(":/res/user_select"));
    userErrorIcon.addPixmap(QPixmap(":/res/user_error"));

    userIconBtn = new QPushButton();
    userIconBtn->setFixedSize(24,24);
    userIconBtn->setIcon(userNormalIcon);
    userIconBtn->setIconSize(userIconBtn->size());
    userIconBtn->setFlat(true);
    userIconBtn->setFocusPolicy(Qt::NoFocus);
    auto *user_layout = new QHBoxLayout();
    user_layout->setMargin(0);
    user_layout->setSpacing(0);
    user_layout->setContentsMargins(6,0,0,0);
    user_layout->addWidget(userIconBtn);
    user_layout->addStretch();
    usernameLE->setLayout(user_layout);

    // 昵称样式
    nickLE = new QLineEdit();
    nickLE->setPlaceholderText("昵称为汉字、字母或数字的组合");
    nickLE->setMaxLength(32);
    nickLE->setFixedSize(280, 50);
    nickLE->setTextMargins(36, 0, 0 , 0);
    nickLE->installEventFilter(this);
    nickLE->setAlignment(Qt::AlignVCenter);
    nickLE->setStyleSheet("QLineEdit { border: 1px none #e5e5e5;"
                              "border-bottom-style:solid;"
                              "font-size:18px;"
                              "background:#ffffff;"
                              "color:#2c2c2c; }"
                              "QLineEdit:focus {"
                              "border-color:#238efa;}"
    );

    nickNormalIcon.addPixmap(QPixmap(":/res/nick_normal"));
    nickSelectIcon.addPixmap(QPixmap(":/res/nick_select"));
    nickErrorIcon.addPixmap(QPixmap(":/res/nick_error"));

    nickIconBtn = new QPushButton();
    nickIconBtn->setFixedSize(24,24);
    nickIconBtn->setIcon(nickNormalIcon);
    nickIconBtn->setIconSize(nickIconBtn->size());
    nickIconBtn->setFlat(true);
    nickIconBtn->setFocusPolicy(Qt::NoFocus);
    auto *nick_layout = new QHBoxLayout();
    nick_layout->setMargin(0);
    nick_layout->setSpacing(0);
    nick_layout->setContentsMargins(6,0,0,0);
    nick_layout->addWidget(nickIconBtn);
    nick_layout->addStretch();
    nickLE->setLayout(nick_layout);

    // 密码输入框样式
    passwordLE = new QLineEdit();
    passwordLE->setPlaceholderText("密码限6~128位字母或数字");
    passwordLE->setMaxLength(128);
    passwordLE->setEchoMode(QLineEdit::Password);
    passwordLE->setAlignment(Qt::AlignVCenter);
    passwordLE->installEventFilter(this);               //注册密码监听器
    passwordLE->setFixedSize(280,50);
    passwordLE->setTextMargins(36,0,0,0);
    passwordLE->setContentsMargins(0,0,0,0);
    passwordLE->setStyleSheet("QLineEdit[echoMode=\"2\"] {"
                              "lineedit-password-character: 42;}"
                              "QLineEdit { border: 1px none #e5e5e5;"
                              "border-bottom-style:solid;"
                              "background: #ffffff;"
                              "font-size:18px;"
                              "color:#2c2c2c;}"
                              " QLineEdit:focus{"
                              "border-color:#238efa;"
                              "}");

    pwdNormalIcon.addPixmap(QPixmap(":/res/pwd_normal"));
    pwdSelectIcon.addPixmap(QPixmap(":/res/pwd_select"));
    pwdErrorIcon.addPixmap(QPixmap(":/res/pwd_error"));

    pwdIconBtn = new QPushButton();
    pwdIconBtn->setFixedSize(24,24);
    pwdIconBtn->setIcon(pwdNormalIcon);
    pwdIconBtn->setIconSize(pwdIconBtn->size());
    pwdIconBtn->setFlat(true);
    pwdIconBtn->setFocusPolicy(Qt::NoFocus);
    auto *pwd_layout = new QHBoxLayout();
    pwd_layout->setMargin(0);
    pwd_layout->setSpacing(0);
    pwd_layout->setContentsMargins(6,0,0,0);
    pwd_layout->addWidget(pwdIconBtn);
    pwd_layout->addStretch();
    passwordLE->setLayout(pwd_layout);

    auto *user_nick_pwd_layout = new QVBoxLayout();
    user_nick_pwd_layout->setMargin(0);
    user_nick_pwd_layout->setContentsMargins(10, 10, 10, 10);
    user_nick_pwd_layout->setSpacing(0);
    user_nick_pwd_layout->addWidget(usernameLE, 0, Qt::AlignHCenter);
    user_nick_pwd_layout->addWidget(nickLE, 0, Qt::AlignHCenter);
    user_nick_pwd_layout->addWidget(passwordLE, 0, Qt::AlignHCenter);
    user_nick_pwd_widget = new QWidget();
    // .QWidget仅将CSS应用于完全QWidget且不继承QWidget的类 您还可以使用对象名称选择器
    user_nick_pwd_widget->setStyleSheet(".QWidget { "
                                   "border: 1px solid #ced2d6; "
                                   "background-color: #ffffff;"
                                   "}");
    user_nick_pwd_widget->setLayout(user_nick_pwd_layout);

    helpInfoLB = new QLabel("提示信息");
    helpInfoLB->setContentsMargins(0, 0, 0, 20);
    helpInfoLB->setStyleSheet("color:red;");
    helpInfoLB->setVisible(false);

    // 登录按钮
    registerBtn = new QPushButton("注 册");
    registerBtn->setFixedSize(300,50);
    registerBtn->setStyleSheet("QPushButton { font-size:20px;"
                            "color:white;"
                            "background-color:#238efa;}"
                            "QPushButton:hover {"
                            "background-color:#4ca6ff;}"
                            "QPushButton:pressed {"
                            "background-color:#1f7ddb;}"
                            "QPushButton:focus{outline: none;}" // 获取焦点时不显示虚线框
    );

}

void RegisterWidget::SetLayout() {
    mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(user_nick_pwd_widget, 0, Qt::AlignHCenter);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(helpInfoLB);
    mainLayout->addWidget(registerBtn, 0, Qt::AlignHCenter);
    setLayout(mainLayout);
}

void RegisterWidget::SetConnect() {
    connect(registerBtn, &QPushButton::clicked, this, &RegisterWidget::OnRegisterClicked);
}

bool RegisterWidget::eventFilter(QObject *obj, QEvent *ev) {
    if(obj == usernameLE)
    {
        if(ev->type() == QEvent::FocusIn)
        {
            userIconBtn->setIcon(userSelectIcon);
            helpInfoLB->setVisible(false);
        } else if (ev->type() == QEvent::FocusOut)
        {
            userIconBtn->setIcon(userNormalIcon);
        }
    }
    if(obj == nickLE)
    {
        if(ev->type() == QEvent::FocusIn)
        {
            nickIconBtn->setIcon(nickSelectIcon);
            helpInfoLB->setVisible(false);
        } else if (ev->type() == QEvent::FocusOut)
        {
            nickIconBtn->setIcon(nickNormalIcon);
        }
    }
    if(obj == passwordLE)
    {
        if(ev->type() == QEvent::FocusIn)
        {
            pwdIconBtn->setIcon(pwdSelectIcon);
            helpInfoLB->setVisible(false);
        } else if (ev->type() == QEvent::FocusOut)
        {
            pwdIconBtn->setIcon(pwdNormalIcon);
        }
    }
    return QWidget::eventFilter(obj,ev);
}

void RegisterWidget::OnRegisterClicked() {

    if (usernameLE->text() == "") {
        userIconBtn->setIcon(userErrorIcon);
        helpInfoLB->setText("账号为空");
        helpInfoLB->setVisible(true);
    } else if(nickLE->text() == "") {
        nickIconBtn->setIcon(nickErrorIcon);
        helpInfoLB->setText("昵称为空");
        helpInfoLB->setVisible(true);
    } else if(passwordLE->text() == "") {
        pwdIconBtn->setIcon(pwdErrorIcon);
        helpInfoLB->setText("密码为空");
        helpInfoLB->setVisible(true);
    } else {
        // TODO register
//        nim::Friend::Request()

    }
}


