//
// Created by 19216 on 2021/6/5.
//


#include "addfriendwidget.h"


AddFriendWidget::AddFriendWidget(QWidget *parent) :
        QWidget(parent) {
//    qDebug() << "[info]: create add friend widget ...";
    this->setWindowTitle("添加好友");
    this->setFixedSize(520, 300);
    this->setStyleSheet("background:#F0F2F5;");

    InitControl();
    SetLayout();
    SetConnect();
}

AddFriendWidget::~AddFriendWidget() {
    qDebug() << "[info]: delete add friend widget in " << __FUNCTION__;
}

void AddFriendWidget::InitControl() {

    int EditHeight = 46;
    QMargins EditMargins(12, 6, 12, 6);

    accIDLabel = new QLabel("账户");
    accIDLabel->setAlignment(Qt::AlignRight);
    accIDLabel->setFixedWidth(68);
    accIDLineEdit = new QLineEdit();
    accIDLineEdit->installEventFilter(this);
    accIDLineEdit->setFixedHeight(EditHeight);
    accIDLineEdit->setTextMargins(EditMargins);
    accIDLineEdit->setPlaceholderText("请输入账号");
    accIDLineEdit->setStyleSheet("QLineEdit { border: 1px solid #6C757D;"
                                 "border-radius: 6px;"
                                 "font-size:18px;"
                                 "color:#2c2c2c; }"
                                 "QLineEdit:focus {"
                                 "border-color:#238efa;}");

    requestMsgLabel = new QLabel("验证消息");
    requestMsgLabel->setAlignment(Qt::AlignRight);
    requestMsgLabel->setFixedWidth(68);
    requestMsgLineEdit = new QLineEdit();
    requestMsgLineEdit->installEventFilter(this);
    requestMsgLineEdit->setFixedHeight(EditHeight);
    requestMsgLineEdit->setTextMargins(EditMargins);
    requestMsgLineEdit->setPlaceholderText("输入验证消息...");
    requestMsgLineEdit->setStyleSheet("QLineEdit { border: 1px solid #6C757D;"
                                      "border-radius: 6px;"
                                      "font-size:18px;"
                                      "color:#2c2c2c; }"
                                      "QLineEdit:focus {"
                                      "border-color:#238efa;}");

    infoLabel = new QLabel("提示消息");
    infoLabel->setContentsMargins(0, 8, 0, 0);
    infoLabel->setStyleSheet("color:red;");
    infoLabel->setVisible(false);

    // 取消按钮
    cancelButton = new QPushButton("取消");
    cancelButton->setFixedSize(120, 40);
    cancelButton->setStyleSheet("QPushButton { font-size:20px;"
                                "color:white;"
                                "border: none;"
                                "border-radius: 6px;"
                                "background-color:#6C757D;}"
                                "QPushButton:hover {"
                                "background-color:#5A6268;}"
                                "QPushButton:pressed {"
                                "background-color:#545B62;"
                                "border: 2px solid #B6BABE;}"
                                "QPushButton:focus{outline: none;}"); // 获取焦点时不显示虚线框

    // 修改按钮
    searchButton = new QPushButton("添加");
    searchButton->setFixedSize(120, 40);
    searchButton->setStyleSheet("QPushButton { font-size:20px;"
                                "color:white;"
                                "border: none;"
                                "border-radius: 6px;"
                                "background-color:#4ca6ff;}"
                                "QPushButton:hover {"
                                "background-color:#238efa;}"
                                "QPushButton:pressed {"
                                "background-color:#1f7ddb;"
                                "border: 2px solid #80BDFF;}"
                                "QPushButton:focus{outline: none;}"); // 获取焦点时不显示虚线框

}

void AddFriendWidget::SetLayout() {

    auto accIDLayout = new QHBoxLayout();
    accIDLayout->setContentsMargins(0, 0, 0, 0);
    accIDLayout->addWidget(accIDLabel, 0, Qt::AlignVCenter);
    accIDLayout->addSpacing(8);
    accIDLayout->addWidget(accIDLineEdit, 0, Qt::AlignVCenter);

    auto requestMsgLayout = new QHBoxLayout();
    requestMsgLayout->setContentsMargins(0, 0, 0, 0);
    requestMsgLayout->addWidget(requestMsgLabel, 0, Qt::AlignVCenter);
    requestMsgLayout->addSpacing(8);
    requestMsgLayout->addWidget(requestMsgLineEdit, 0, Qt::AlignVCenter);

    auto btnLayout = new QHBoxLayout();
    btnLayout->setContentsMargins(0, 0, 0, 0);
    btnLayout->addStretch();
    btnLayout->addWidget(cancelButton, 0, Qt::AlignVCenter);
    btnLayout->addSpacing(16);
    btnLayout->addWidget(searchButton, 0, Qt::AlignVCenter);

    mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(16, 0, 32, 0);
    mainLayout->addStretch();
    mainLayout->addLayout(accIDLayout);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(requestMsgLayout);
    mainLayout->addWidget(infoLabel, 0, Qt::AlignHCenter);
    mainLayout->addStretch();
    mainLayout->addLayout(btnLayout);
    mainLayout->addSpacing(32);

    setLayout(mainLayout);
}

void AddFriendWidget::SetConnect() {
    // 取消按钮处理
    connect(cancelButton, &QPushButton::clicked, this, [this]() {
        this->hide();
    });
    // 链接搜索按钮处理槽函数
    connect(searchButton, &QPushButton::clicked, this, &AddFriendWidget::ClickedSearchButtonSlot);

    // 显示添加好友的提示信息结果
    connect(this, &AddFriendWidget::ShowResultOfAddFriendSignal, this, &AddFriendWidget::ShowResultOfAddFriendSlot);

}

// 搜索好友按钮槽函数
void AddFriendWidget::ClickedSearchButtonSlot() {
    infoLabel->setVisible(false);
    if(accIDLineEdit->text() == "") {
        ShowResultOfAddFriendSlot("账户为空");
        return;
    }
    if(!IsFriend(accIDLineEdit->text().toStdString())) {
        AddFriendRequest(accIDLineEdit->text(), requestMsgLineEdit->text());
    } else {
        ShowResultOfAddFriendSlot("你与 “"+accIDLineEdit->text()+"” 已经是好友！");
    }

}

// 判断是否为好友关系。该接口为同步接口，会堵塞SDK线程，谨慎使用
bool AddFriendWidget::IsFriend(const std::string& accID) {
    // 该接口为同步接口，会堵塞SDK线程，谨慎使用
    return nim::Friend::QueryFriendshipBlock(accID);
}

// 请求添加好友
void AddFriendWidget::AddFriendRequest(const QString &accID, const QString& msg) {
    nim::Friend::Request(accID.toStdString(), nim::kNIMVerifyTypeAdd, msg.toStdString(),
                         [this](auto &&PH1) {
                             OnFriendRequest(std::forward<decltype(PH1)>(PH1));
                         });
}

void AddFriendWidget::OnFriendRequest(nim::NIMResCode res_code) {
    if (res_code == nim::kNIMResSuccess) {
        // qDebug() << "请求添加好友成功！";
        emit ShowResultOfAddFriendSignal("添加好友成功！");
    } else if(res_code == nim::kNIMResNotExist) {
        emit ShowResultOfAddFriendSignal("好友不存在 ...");
    } else {
        qDebug() << "请求添加好友失败, result code is : " << res_code;
        emit ShowResultOfAddFriendSignal("添加好友失败 ...");
    }
}

// 显示添加好友的提示信息结果
void AddFriendWidget::ShowResultOfAddFriendSlot(const QString &resultInfo) {
    infoLabel->setVisible(true);
    infoLabel->setText(resultInfo);
}

bool AddFriendWidget::eventFilter(QObject *obj, QEvent *ev) {
    if(obj == accIDLineEdit) {
        if(ev->type() == QEvent::FocusIn) {
            infoLabel->setVisible(false);
        }
    }
    if(obj == requestMsgLineEdit) {
        if(ev->type() == QEvent::FocusIn) {
            infoLabel->setVisible(false);
        }  else if(ev->type() == QEvent::KeyPress) {
            // 在验证消息框内回车按键则直接搜索添加好友
            auto *key = dynamic_cast<QKeyEvent *>(ev);
            if (key->key() == Qt::Key_Enter || key->key() == Qt::Key_Return) {
                ClickedSearchButtonSlot();
            }
        }
    }
    return QWidget::eventFilter(obj,ev);
}
