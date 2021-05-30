//
// Created by 19216 on 2021/5/28.
//

// You may need to build the project (run Qt uic code generator) to get "ui_LoginWindow.h" resolved

#include "loginwindow.h"


LoginWindow::LoginWindow(QWidget *parent) :
        QWidget(parent){

    this->setFixedSize(340, 420);
    setWindowTitle("登录");
    setStyleSheet("background:#fafbfc;");

    InitControl();
    SetLayout();
    SetConnect();

    LoadPwd();

}

LoginWindow::~LoginWindow() {
    qDebug() << "[info]: in ~LoginWindow ...";
    if(mainWindow != nullptr) {
        delete mainWindow;
    }
    nim::Client::Logout(nim::kNIMLogoutAppExit, [](nim::NIMResCode res_code){
        qDebug() << "[info]: exit APP, logout callback, result code is " << res_code;
        // 退出程序
        nim::Client::Cleanup();
    });
}

void LoginWindow::InitControl() {

    registerBtn = new QPushButton("注册");
    registerBtn->setCursor(QCursor(Qt::PointingHandCursor));        // 鼠标移上去变手型
    registerBtn->setStyleSheet("border: none;"
                               "color:#23c7a6;");
    registerBtn->setFlat(true);

    // 用户名输入框样式
    usernameLE = new QLineEdit();
    usernameLE->setPlaceholderText("账号");
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

    // 密码输入框样式
    passwordLE = new QLineEdit();
    passwordLE->setPlaceholderText("密码");
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

    auto *user_pwd_layout = new QVBoxLayout();
    user_pwd_layout->setMargin(0);
    user_pwd_layout->setContentsMargins(10, 10, 10, 10);
    user_pwd_layout->setSpacing(0);
    user_pwd_layout->addWidget(usernameLE, 0, Qt::AlignHCenter);
    user_pwd_layout->addWidget(passwordLE, 0, Qt::AlignHCenter);
    user_pwd_widget = new QWidget();
    // .QWidget仅将CSS应用于完全QWidget且不继承QWidget的类 您还可以使用对象名称选择器
    user_pwd_widget->setStyleSheet(".QWidget { "
                                   "border: 1px solid #ced2d6; "
                                   "background-color: #ffffff;"
                                   "}");
    user_pwd_widget->setLayout(user_pwd_layout);

    // 记住密码复选框
    rememberCB = new QCheckBox("记住密码");
    rememberCB->setStyleSheet("QCheckBox { "
                              "     font-size:16px;"
                              "     color:#2c2c2c;"
                              "}"
                              "QCheckBox::indicator {"
                              "    width: 18px;"
                              "    height: 18px;"
                              "}"
                              "QCheckBox::indicator:unchecked {"
                              "     image: url(:/res/cb_unchecked);}"
                              "QCheckBox::indicator:checked {"
                              "     image: url(:/res/cb_checked);"
                              "}");

    // 帮助信息标签
    helpInfoLB = new QLabel("提示信息");
    helpInfoLB->setContentsMargins(0, 0, 0, 20);
    helpInfoLB->setStyleSheet("color:red;");
    helpInfoLB->setVisible(false);

    // 登录按钮
    loginBtn = new QPushButton("登 录");
    loginBtn->setFixedSize(300,50);
    loginBtn->setStyleSheet("QPushButton { font-size:20px;"
                            "color:white;"
                            "background-color:#238efa;}"
                            "QPushButton:hover {"
                            "background-color:#4ca6ff;}"
                            "QPushButton:pressed {"
                            "background-color:#1f7ddb;}"
                            "QPushButton:focus{outline: none;}" // 获取焦点时不显示虚线框
                            );

    loginWidget = new QWidget();
    auto *loginLayout = new QVBoxLayout();
    loginLayout = new QVBoxLayout();
    loginLayout->setSpacing(0);
    loginLayout->setMargin(0);
    loginLayout->setContentsMargins(0, 0, 0, 0);
    loginLayout->addWidget(user_pwd_widget, 0, Qt::AlignHCenter);
    loginLayout->addSpacing(20);
    loginLayout->addWidget(rememberCB);
    loginLayout->addSpacing(20);
    loginLayout->addWidget(helpInfoLB);
    loginLayout->addWidget(loginBtn, 0, Qt::AlignHCenter);
    loginWidget->setLayout(loginLayout);

    registerWidget = new RegisterWidget();
    registerWidget->setVisible(false);

}

void LoginWindow::SetLayout() {
    mainLayout = new QVBoxLayout();
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->setContentsMargins(20, 0, 20, 0);

    mainLayout->addSpacing(60);
    mainLayout->addWidget(registerBtn, 0, Qt::AlignRight);
    mainLayout->addSpacing(15);

    mainLayout->addWidget(loginWidget);
    mainLayout->addWidget(registerWidget);

    mainLayout->addStretch();

    setLayout(mainLayout);
}

void LoginWindow::SetConnect() {
    connect(this, &LoginWindow::LoginSuccessSignal, this, &LoginWindow::LoginSuccessSlot);
    connect(this, &LoginWindow::LoginFailedSignal, this, &LoginWindow::LoginFailedSlot);
    connect(loginBtn, &QPushButton::clicked, this, &LoginWindow::OnLoginClicked);
    connect(registerBtn, &QPushButton::clicked, this, &LoginWindow::OnRegisterClicked);
}

bool LoginWindow::eventFilter(QObject *obj, QEvent *ev) {
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

void LoginWindow::OnRegisterClicked() {
//    qDebug() << "clicked register ...";
    if (registerBtn->text() == "注册") {
        // 当前点击的是注册按钮，则显示注册界面
        registerBtn->setText("直接登录");
        loginWidget->setVisible(false);
        registerWidget->setVisible(true);
    } else {
        // 当前点击的是直接登录，则返回登录界面
        registerBtn->setText("注册");
        loginWidget->setVisible(true);
        registerWidget->setVisible(false);
    }
}

void LoginWindow::OnLoginClicked() {
//    qDebug() << "clicked login button";
//    qDebug() << "username: " << usernameLE->text()
//        <<"\npassword: " << passwordLE->text();

    if (usernameLE->text() == "") {
        userIconBtn->setIcon(userErrorIcon);
        helpInfoLB->setText("账号为空");
        helpInfoLB->setVisible(true);
    } else if(passwordLE->text() == "") {
        pwdIconBtn->setIcon(pwdErrorIcon);
        helpInfoLB->setText("密码为空");
        helpInfoLB->setVisible(true);
    } else {
        std::cout << "window thread id : " << std::this_thread::get_id() << std::endl;
        loginBtn->setText("正在登录...");
        nim::Client::Login(app_key, usernameLE->text().toStdString(), passwordLE->text().toStdString(),
                           [this](auto && PH1) { OnLoginCallback(std::forward<decltype(PH1)>(PH1)); });
    }
}

void LoginWindow::OnLoginCallback(const nim::LoginRes& login_res) {
    // 回调函数运行在新的线程中，与主线程不在同一线程
    if(login_res.login_step_ == nim::kNIMLoginStepLogin) {
        if(login_res.res_code_ == nim::kNIMResSuccess) {
            emit LoginSuccessSignal();
        } else {
            emit LoginFailedSignal("用户名或密码错误");
            qDebug() << "[info]: Login result code is " << login_res.res_code_ << ", login failed ...";
        }
    } else {
//        qDebug() << "[info]: Login " << login_res.login_step_ << " step ...";
    }
}

void LoginWindow::LoginSuccessSlot() {
//    std::cout << "[info]: login callback thread id : " << std::this_thread::get_id() << std::endl;
//    helpInfoLB->setText("登录成功");
//    helpInfoLB->setVisible(true);

    SavePwd();
    loginBtn->setText("登 录");
    if (mainWindow == nullptr) {
        mainWindow = new MainWindow();
        connect(mainWindow, &MainWindow::LogoutSignal, this, &LoginWindow::OnLogoutSlot);
    }
    mainWindow->show();
    this->hide();
}

// 在主界面退出登录时回调到这里的槽函数
void LoginWindow::OnLogoutSlot() {
    qDebug() << "[info]: receive signal from mainWindow of logout, and now in LoginWindow::OnLogoutSlot";
    LoadPwd();      // 加载用户名和密码
    this->show();
    mainWindow->hide();
    mainWindow->deleteLater();
    mainWindow = nullptr;
}

void LoginWindow::closeEvent(QCloseEvent *event) {

}

void LoginWindow::LoginFailedSlot(const QString& errorInfo) {
    helpInfoLB->setText(errorInfo);
    helpInfoLB->setVisible(true);
    loginBtn->setText("登 录");
}

void LoginWindow::SavePwd() {
    QSettings cfg("user.ini", QSettings::IniFormat);
    bool remembered = rememberCB->isChecked();
    cfg.setValue("username", usernameLE->text());
    if (remembered) {
        cfg.setValue("password", passwordLE->text());
    } else {
        cfg.setValue("password", "");
    }
    cfg.setValue("remembered", remembered);
    cfg.sync();
}

void LoginWindow::LoadPwd() {
    QSettings cfg("user.ini", QSettings::IniFormat);
    usernameLE->setText(cfg.value("username", "").toString());
    passwordLE->setText(cfg.value("password", "").toString());
    if (cfg.value("remembered", false).toBool()) {
        rememberCB->setChecked(true);
    } else {
        rememberCB->setChecked(false);
    }
}

