#include "qmainwindow.h"

#include <qlistwidget.h>
//#include <QGLWidget>

MainWindow::MainWindow(QString accID_, QWidget *parent)
    : accID(accID_), QWidget(parent)
{
    this->resize(360, 700);
    this->setMinimumSize(360, 700);
    this->setMaximumWidth(800);
    this->setStyleSheet("background:#ded5da;");

    // 注册信号槽传递时可能传递的数据
    qRegisterMetaType<Message>("Message");                          // 注册消息传递的数据类型
    qRegisterMetaType<nim::SessionData>("nim::SessionData");        // 注册消息传递的数据类型
    qRegisterMetaType<nim::SendMessageArc>("nim::SendMessageArc");  // 发送消息回调结果
    qRegisterMetaType<nim::IMMessage>("nim::IMMessage");            // 收发消息
    qRegisterMetaType<nim::UserNameCard>("nim::UserNameCard");      // 用户个人信息
    qRegisterMetaType<nim::FriendProfile>("nim::FriendProfile");    // 好友关系信息
    qRegisterMetaType<QMap<QString, nim::UserNameCard>>("QMap<QString, nim::UserNameCard>");      // 用户个人信息
    qRegisterMetaType<QMap<QString, nim::FriendProfile>>("QMap<QString, nim::FriendProfile>");      // 用户个人信息

    // 注册消息发送成功与否回调
    RegisterSendMsg();
    // 注册接收消息回调
    RegisterReceiveMsg();

    InitControl();
    SetConnect();
    SetLayout();

    // 首先初始化好友列表，再初始化最近会话列表
    friendListWidget->InitFriendList();
    recentSessionWidget->InitSessionList();
}

MainWindow::~MainWindow()
{
    qDebug() << "[info]: in ~MainWindow. Opened chatting windows number is " << chattingWindows.size();
    for(auto * chattingWindow: chattingWindows) {
        if(chattingWindow) {
            chattingWindow->hide();
            delete chattingWindow;
        }
    }
}

void MainWindow::InitControl() {

    recentSessionWidget = new RecentSessionWidget();
    friendListWidget = new FriendListWidget();

    // 新建堆栈窗口，并将两个窗口添加进去，设置当前显示的窗口为“最近会话”窗口
    mainStackedWidget = new QStackedWidget();
    mainStackedWidget->addWidget(friendListWidget);
    mainStackedWidget->addWidget(recentSessionWidget);
    mainStackedWidget->setCurrentIndex(1);

    // 创建与上面窗口对应的选项卡按钮，点击不同的选项卡切换到不同的窗口
    toolLabelLayout = new QHBoxLayout();
    QStringList stringListTool = {"联系人", "消息"};
    for(int i = 0; i < stringListTool.size(); ++i) {
        auto *toolLabel = new ToolLabel(stringListTool.at(i));
        toolLabel->setObjectName(QString::number(i));
        toolLabelLayout->addWidget(toolLabel);
        toolLabels.append(toolLabel);
        connect(toolLabel, &ToolLabel::clicked, this, &MainWindow::toolLabelChecked);
    }
    toolLabels[1]->setChecked();

}

void MainWindow::SetLayout() {
    layout = new QVBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setMargin(0);
    layout->addLayout(toolLabelLayout);
    layout->addWidget(mainStackedWidget);
    setLayout(layout);
}

void MainWindow::SetConnect() {
    // 连接最近会话变化时的信号传递到本类中，以将最新的会话数据传递给打开的聊天界面
    connect(recentSessionWidget, &RecentSessionWidget::UpdateSessionSignal,
            this, &MainWindow::SessionChangedSlot);

    // 连接最近会话中打开聊天窗口的信号到本类中打开聊天界面
    connect(recentSessionWidget, &RecentSessionWidget::OpenChattingWindowSignal,
            this, &MainWindow::OpenChattingWindowFromRecentSessionSlot);
    // 连接好友列表中打开聊天窗口的信号到本类中打开聊天界面
    connect(friendListWidget, &FriendListWidget::OpenChattingWindowSignal,
            this, &MainWindow::OpenChattingWindowFromFriendListsSlot);

    // 当在好友列表控件中加载完毕好友数据和用户数据后，将这些数据发送给最近会话窗口中，方便最近会话的每一个条目的显示更新
    connect(friendListWidget, &FriendListWidget::InitFriendProfileMapSignal,
            recentSessionWidget, &RecentSessionWidget::InitFriendProfileMapSlot);
    connect(friendListWidget, &FriendListWidget::InitUserNameCardMapSignal,
            recentSessionWidget, &RecentSessionWidget::InitUserNameCardMapSlot);
    // 好友列表控件中好友信息变化、或者用户数据发生变化，通知信号到最近会话控件中
    connect(friendListWidget, &FriendListWidget::UpdateFriendProfileSignal,
            recentSessionWidget, &RecentSessionWidget::UpdateFriendProfileSlot);
    connect(friendListWidget, &FriendListWidget::UpdateUserNameCardSignal,
            recentSessionWidget, &RecentSessionWidget::UpdateUserNameCardSlot);
}

// 关闭窗口事件处理，这里处理为退出登录，到登录界面
void MainWindow::closeEvent(QCloseEvent *event) {
    qDebug() << "[info]: in MainWindow closeEvent ...";
    nim::Client::Logout(nim::kNIMLogoutChangeAccout, [this](nim::NIMResCode res_code) {
        qDebug() << "[info]: 退出登录 ...";
        emit LogoutSignal();                // 退出登录信号，发送到LoginWindow::OnLogoutSlot槽函数
    });
    event->ignore();
}

void MainWindow::toolLabelChecked() {
    auto *label = (ToolLabel*) sender();
    foreach(ToolLabel* toolLabel, toolLabels) {
        toolLabel->setUnChecked();
        toolLabel->style()->polish(toolLabel);      // 自定义属性在调用后必须调用刷新样式的操作!!!
    }
    label->setChecked();
    label->style()->polish(label);
    mainStackedWidget->setCurrentIndex(label->objectName().toInt());
//    qDebug() << "checked ...";
}

////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// 发送消息回调结果 /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// 登录成功后注册全局回调，此回调主要是判断聊天时消息是否发送成功
void MainWindow::RegisterSendMsg() {
    nim::Talk::RegSendMsgCb([this](auto &&PH1) {
        OnSendMsgCallback(std::forward<decltype(PH1)>(PH1));
    });
}
// 消息发送成功与否回调函数
void MainWindow::OnSendMsgCallback(const nim::SendMessageArc& messageArc) {
    emit sendMsgCallbackSignal(messageArc);     // ChattingWindow::sendMsgCallbackSlot
}
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// 接收消息 ///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// 登录成功之后注册消息接收的全局广播通知，主要是收到其他用户发送来的消息
void MainWindow::RegisterReceiveMsg() {
    nim::Talk::RegReceiveCb([this](auto &&PH1) {
        OnReceiveMsgCallback(std::forward<decltype(PH1)>(PH1));
    });
}
// 接收消息回调函数
void MainWindow::OnReceiveMsgCallback(const nim::IMMessage &message) {
    emit receiveMsgSignal(message);     // ChattingWindow::receiveMsgSlot
}
////////////////////////////////////////////////////////////////////////////////////

// 最近会话变动，需要将会话数据传递给聊天界面中
void MainWindow::SessionChangedSlot(const nim::SessionData &sessionData) {
    if(chattingWindows.contains(QString::fromStdString(sessionData.id_))) {
        chattingWindows[QString::fromStdString(sessionData.id_)]->setSessionData(sessionData);
    }
}

// 从好友列表中双击某一个好友打开聊天界面
void MainWindow::OpenChattingWindowFromFriendListsSlot(const nim::UserNameCard &userNameCard) {
    if(chattingWindows.contains(QString::fromStdString(userNameCard.GetAccId()))) {
        // 如果与该好友的聊天界面已经存在，则直接打开
        chattingWindows[QString::fromStdString(userNameCard.GetAccId())]->showNormal();     // 让最小化的窗口显示出来
        chattingWindows[QString::fromStdString(userNameCard.GetAccId())]->raise();          // 让该聊天窗口置顶显示
        return;
    }
    // 如果从好友列表里打开与该用户的聊天窗口，则需要向最近会话列表里插入与该好友的会话记录（如果最近的会话列表里没有该用户的话），
    // 创建一个会话数据；
    // 如果最近会话列表里有与该用户的会话记录，则获取到该会话数据。
    auto sessionItemMap = recentSessionWidget->getAllSessionItemMap();
    if(sessionItemMap.contains(QString::fromStdString(userNameCard.GetAccId()))) {
        // 如果最近会话里有与该用户的会话，则获取到该会话数据，并使用该会话数据打开聊天窗口。然后直接返回即可。
        OpenChattingWindowFromRecentSessionSlot(
                sessionItemMap[QString::fromStdString(userNameCard.GetAccId())]->getSessionData()
                );
        return;
    }
    // 说明最近会话列表里没有与该用户的会话，则需要自己创建一个新的会话并创建聊天窗口。
    nim::SessionData session;
    session.id_ = userNameCard.GetAccId();
    session.type_ = nim::kNIMSessionTypeP2P;
    session.msg_timetag_ = ((int64_t) (QDateTime::currentDateTimeUtc().toTime_t())) * 1000;
    recentSessionWidget->AddSessionItem(session, 0);
    OpenChattingWindowFromRecentSessionSlot(session);
}

// 从最近会话中双击某一个会话打开聊天界面
void MainWindow::OpenChattingWindowFromRecentSessionSlot(const nim::SessionData &sessionData) {

    if(chattingWindows.contains(QString::fromStdString(sessionData.id_))) {
        // 如果与该好友的聊天界面已经存在，则直接打开
        chattingWindows[QString::fromStdString(sessionData.id_)]->showNormal();     // 让最小化的窗口显示出来
        chattingWindows[QString::fromStdString(sessionData.id_)]->raise();  // 让该聊天窗口置顶显示
        return;
    }

    QString accID = QString::fromStdString(sessionData.id_);

    // 与该好友的聊天界面不存在，则新建聊天界面并打开
    auto *chattingWindow = new ChattingWindow(sessionData);

    // 获取所有的好友关系列表
    auto &profiles = friendListWidget->getFriendProfileMap();
    if(profiles.contains(accID)) {
        // 二者是好友关系
        chattingWindow->setFriendProfile(profiles[accID]);
    }

    // 获取所有的用户信息
    auto &userCards = friendListWidget->getUserNameCardMap();
    if(userCards.contains(accID)) {
        // 已经存在该用户信息
        chattingWindow->setUserNameCard(userCards[accID]);
    }
    // 调用好set方法后，需要重新更新界面数据
    chattingWindow->updateChattingWindow();

    // 将最近发送的消息成功与否信号传递到聊天窗口中
    connect(this, &MainWindow::sendMsgCallbackSignal, chattingWindow, &ChattingWindow::sendMsgCallbackSlot);
    // 当其他用户发送来新的消息后所有的聊天窗口界面都会收到该消息。
    connect(this, &MainWindow::receiveMsgSignal, chattingWindow, &ChattingWindow::receiveMsgSlot);
    // 当聊天窗口主动关闭时，需要通知该界面，将该聊天窗口从所有已经打开的聊天窗口列表中删除
    connect(chattingWindow, &ChattingWindow::closeChattingWindowSignal, this, &MainWindow::CloseChattingWindowSlot);
    chattingWindow->show();
    chattingWindows.insert(QString::fromStdString(sessionData.id_), chattingWindow);
    qDebug() << "[info]: opened chatting window size is: " << chattingWindows.size();
}

// 关闭聊天窗口
void MainWindow::CloseChattingWindowSlot(const QString& id) {
    qDebug() << "[info]: close chatting window : " << id;
    if (!chattingWindows.contains(id)) {
        qDebug() << "[error]: close window error, the closed window '" << id << "' not in all opened windows: " << chattingWindows.keys();
        return;
    }
    // 删除该聊天窗口
    auto *window = chattingWindows.take(id);
    if(window) {
        window->hide();
        delete window;
    }
}





