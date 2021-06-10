#include "qmainwindow.h"

#include <qlistwidget.h>
//#include <QGLWidget>

MainWindow::MainWindow(QString accID_, QWidget *parent)
        : accID(accID_), QWidget(parent) {
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
    qRegisterMetaType<nim::TeamInfo>("nim::TeamInfo");              // 群信息
    qRegisterMetaType<SessionData>("SessionData");                  // 注册消息传递的数据类型
    qRegisterMetaType<SendMessageArc>("SendMessageArc");            // 发送消息回调结果
    qRegisterMetaType<IMMessage>("IMMessage");                      // 收发消息
    qRegisterMetaType<UserNameCard>("UserNameCard");                // 用户个人信息
    qRegisterMetaType<FriendProfile>("FriendProfile");              // 好友关系信息
    qRegisterMetaType<TeamInfo>("TeamInfo");                        // 群信息
    qRegisterMetaType<QMap<QString, nim::UserNameCard>>("QMap<QString, nim::UserNameCard>");      // 用户个人信息
    qRegisterMetaType<QMap<QString, nim::FriendProfile>>("QMap<QString, nim::FriendProfile>");      // 用户个人信息

    // 注册消息发送成功与否回调
    RegisterSendMsg();
    // 注册接收消息回调
    RegisterReceiveMsg();

    InitControl();
    SetConnect();
    SetLayout();

    updateMyHeader();

    // 首先初始化好友列表，再初始化最近会话列表
    friendListWidget->InitFriendList();
    recentSessionWidget->InitSessionList();
}

MainWindow::~MainWindow() {
    qDebug() << "[info]: in ~MainWindow. Opened chatting windows number is " << chattingWindows.size();
    for (auto *chattingWindow: chattingWindows) {
        if (chattingWindow) {
            chattingWindow->hide();
            delete chattingWindow;
        }
    }
    // 释放修改个人信息窗口资源
    if (userInfoWidget != nullptr) {
        delete userInfoWidget;
        userInfoWidget = nullptr;
    }
    // 释放添加好友窗口资源
    if (addFriendWidget != nullptr) {
        delete addFriendWidget;
        addFriendWidget = nullptr;
    }
    // 释放创建群聊窗口资源
    if (createTeamWidget != nullptr) {
        delete createTeamWidget;
        createTeamWidget = nullptr;
    }
}

void MainWindow::updateMyHeader() {
    // 更新头像
    updateHeaderPhotoIcon();
    // 更新用户名
    if (!SELF_USER_NAME_CARD.GetName().empty()) {
        nameLabel->setText(QString::fromStdString(SELF_USER_NAME_CARD.GetName()));
    } else {
        nameLabel->setText(QString::fromStdString(SELF_USER_NAME_CARD.GetAccId()));
    }
    // 更新签名
    if (!SELF_USER_NAME_CARD.GetSignature().empty()) {
        signatureLabel->setText(QString::fromStdString(SELF_USER_NAME_CARD.GetSignature()));
    } else {
        signatureLabel->setText("设置签名");
    }
}

void MainWindow::InitControl() {

    headerPhotoLabel = new ClickableLabel("头像");
    headerPhotoLabel->setFixedSize(68, 68);
    headerPhotoLabel->setToolTip("查看、修改个人信息");
    // 鼠标移上去变手型
    headerPhotoLabel->setCursor(QCursor(Qt::PointingHandCursor));

    nameLabel = new QLabel("用户名");
    nameLabel->setStyleSheet("font-size:24px;"
                             "font-weight: bold;");

    signatureLabel = new QLabel("设置签名");
    signatureLabel->setStyleSheet("font-size: 18px");

    auto vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);
    vLayout->addStretch();
    vLayout->addWidget(nameLabel);
    vLayout->addSpacing(12);
    vLayout->addWidget(signatureLabel);
    vLayout->addStretch();

    auto *headerLayout = new QHBoxLayout();
    headerLayout->setContentsMargins(0, 0, 0, 0);
    headerLayout->setSpacing(0);
    headerLayout->addSpacing(16);
    headerLayout->addWidget(headerPhotoLabel, 0, Qt::AlignVCenter);
    headerLayout->addSpacing(16);
    headerLayout->addLayout(vLayout);
    headerLayout->addSpacing(16);

    headerWidget = new QWidget();
    headerWidget->setFixedHeight(100);
    headerWidget->setLayout(headerLayout);

    // 最近会话列表控件
    recentSessionWidget = new RecentSessionWidget();
    // 好友列表控件
    friendListWidget = new FriendListWidget();
    // 群聊列表控件
    teamListWidget = new TeamListWidget();

    // 新建堆栈窗口，并将两个窗口添加进去，设置当前显示的窗口为“最近会话”窗口
    mainStackedWidget = new QStackedWidget();
    mainStackedWidget->addWidget(friendListWidget);
    mainStackedWidget->addWidget(recentSessionWidget);
    mainStackedWidget->addWidget(teamListWidget);
    mainStackedWidget->setCurrentIndex(1);

    // 创建与上面窗口对应的选项卡按钮，点击不同的选项卡切换到不同的窗口
    QStringList stringListTool = {"联系人", "消息", "群聊"};
    for (int i = 0; i < stringListTool.size(); ++i) {
        auto *toolLabel = new ToolLabel(stringListTool.at(i));
        toolLabel->setObjectName(QString::number(i));
        toolLabels.append(toolLabel);
        connect(toolLabel, &ToolLabel::clicked, this, &MainWindow::toolLabelChecked);
    }
    toolLabels[1]->setChecked();

    // 添加好友
    addFriendLabel = new ClickableLabel("添加好友");
    addFriendLabel->setContentsMargins(8, 16, 8, 16);
    addFriendLabel->setFixedSize(46, 62);
    addFriendLabel->setToolTip("添加好友");
    QPixmap addFriendPixmap(":/res/add_friend");
    addFriendLabel->setPixmap(addFriendPixmap.scaled(30, 30));
    addFriendLabel->setStyleSheet("QLabel:hover {"
                                  "background:rgb(213,203,208);"
                                  "}");

    // 创建群聊
    createTeamLabel = new ClickableLabel("创建群聊");
    createTeamLabel->setContentsMargins(8, 16, 8, 16);
    createTeamLabel->setFixedSize(46, 62);
    createTeamLabel->setToolTip("创建群聊");
    QPixmap createTeamPixmap(":/res/create_team");
    createTeamLabel->setPixmap(createTeamPixmap.scaled(30, 30));
    createTeamLabel->setStyleSheet("QLabel:hover {"
                                   "background:rgb(213,203,208);"
                                   "}");

    // 搜索群聊
    searchTeamLabel = new ClickableLabel("搜索群聊");
    searchTeamLabel->setContentsMargins(8, 16, 8, 16);
    searchTeamLabel->setFixedSize(46, 62);
    searchTeamLabel->setToolTip("搜索群聊");
    QPixmap searchTeamPixmap(":/res/search_team");
    searchTeamLabel->setPixmap(searchTeamPixmap.scaled(30, 30));
    searchTeamLabel->setStyleSheet("QLabel:hover {"
                                   "background:rgb(213,203,208);"
                                   "}");

}

void MainWindow::SetLayout() {

    // 选项卡按钮布局
    auto *toolLabelLayout = new QHBoxLayout();
    for (auto *toolLabel: toolLabels) {
        toolLabelLayout->addWidget(toolLabel);
    }

    auto *bottomToolLayout = new QHBoxLayout();
    bottomToolLayout->setContentsMargins(8, 0, 8, 0);
    bottomToolLayout->addWidget(addFriendLabel, 0, Qt::AlignVCenter);
    bottomToolLayout->addWidget(createTeamLabel, 0, Qt::AlignVCenter);
    bottomToolLayout->addWidget(searchTeamLabel, 0, Qt::AlignVCenter);
    bottomToolLayout->addStretch();

    layout = new QVBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setMargin(0);
    layout->addWidget(headerWidget);
    layout->addWidget(MakeSplitWidget("#d0c9cc", 1));
    layout->addLayout(toolLabelLayout);
    layout->addWidget(MakeSplitWidget("#d0c9cc", 1));
    layout->addWidget(mainStackedWidget);
    layout->addWidget(MakeSplitWidget("#d0c9cc", 1));
    layout->addLayout(bottomToolLayout);
    setLayout(layout);
}

void MainWindow::SetConnect() {

    // 点击头像，打开修改个人信息界面
    connect(headerPhotoLabel, &ClickableLabel::clicked, this, &MainWindow::ClickHeaderPhotoSlot);

    // 点击添加好友按钮。实现打开添加好友界面，搜索添加好友
    connect(addFriendLabel, &ClickableLabel::clicked, this, &MainWindow::ClickAddFriendLabelSlot);
    // 点击创建群聊按钮。
    connect(createTeamLabel, &ClickableLabel::clicked, this, &MainWindow::ClickCreateTeamLabelSlot);
    // 点击搜索群聊按钮。
    connect(searchTeamLabel, &ClickableLabel::clicked, this, &MainWindow::ClickSearchTeamLabelSlot);

    // 连接最近会话变化时的信号传递到本类中，以将最新的会话数据传递给打开的聊天界面
    connect(recentSessionWidget, &RecentSessionWidget::UpdateSessionSignal,
            this, &MainWindow::SessionChangToChattingWindowSlot);

    // 连接最近会话中打开聊天窗口的信号到本类中打开聊天界面
    connect(recentSessionWidget, &RecentSessionWidget::OpenChattingWindowSignal,
            this, &MainWindow::OpenChattingWindowFromRecentSessionSlot);
    // 连接好友列表中打开聊天窗口的信号到本类中打开聊天界面
    connect(friendListWidget, &FriendListWidget::OpenChattingWindowSignal,
            this, &MainWindow::OpenChattingWindowFromFriendListsSlot);
    // 连接群列表中打开聊天窗口的信号到本类中打开聊天界面
    connect(teamListWidget, &TeamListWidget::OpenChattingWindowSignal,
            this, &MainWindow::OpenChattingWindowFromTeamInfoListSlot);

    // 当在好友列表控件中加载完毕好友数据和用户数据后，将这些数据发送给最近会话窗口中，方便最近会话的每一个条目的显示更新
    connect(friendListWidget, &FriendListWidget::InitFriendProfileMapSignal,
            recentSessionWidget, &RecentSessionWidget::InitFriendProfileMapSlot);
    connect(friendListWidget, &FriendListWidget::InitUserNameCardMapSignal,
            recentSessionWidget, &RecentSessionWidget::InitUserNameCardMapSlot);
    // 好友列表控件中好友信息变化、或者用户数据发生变化，通知信号到最近会话控件和已经打开的聊天界面中
    connect(friendListWidget, &FriendListWidget::UpdateFriendProfileSignal,
            recentSessionWidget, &RecentSessionWidget::UpdateFriendProfileSlot);
    connect(friendListWidget, &FriendListWidget::UpdateUserNameCardSignal,
            recentSessionWidget, &RecentSessionWidget::UpdateUserNameCardSlot);
    // 群消息发生变化
    connect(teamListWidget, &TeamListWidget::UpdateTeamInfoSignal,
            recentSessionWidget, &RecentSessionWidget::UpdateTeamInfoSlot);

    connect(friendListWidget, &FriendListWidget::UpdateUserNameCardSignal,
            this, &MainWindow::UserCardChangeToChattingWindowSlot);
    connect(friendListWidget, &FriendListWidget::UpdateFriendProfileSignal,
            this, &MainWindow::FriendProfileChangeToChattingWindowSlot);
    // TODO 打开的群消息聊天界面
}

// 设置用户头像
void MainWindow::updateHeaderPhotoIcon() {
    if (SELF_USER_NAME_CARD.GetIconUrl().empty()) {
        SELF_USER_NAME_CARD.SetIconUrl(":/default_header/dh9");
    }
    QPixmap map(QString::fromStdString(SELF_USER_NAME_CARD.GetIconUrl()));
    if (map.isNull()) {
        // 头像加载失败
        map.load(":/default_header/dh9");
    }
    headerPhotoLabel->setPixmap(
            PixmapToRound(
                    map.scaled(headerPhotoLabel->size()),
                    headerPhotoLabel->height() / 2)
    );
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
void MainWindow::OnSendMsgCallback(const nim::SendMessageArc &messageArc) {
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

// 点击用户头像槽函数。主要实现打开用户详细信息界面，然后用户可以修改
void MainWindow::ClickHeaderPhotoSlot() {
    if (userInfoWidget == nullptr) {
        userInfoWidget = new UserInfoWidget(SELF_USER_NAME_CARD);
        connect(userInfoWidget, &UserInfoWidget::ChangeUserCardSuccessSignal, this, &MainWindow::updateMyHeader);
    }
    userInfoWidget->ShowNormal();
    userInfoWidget->raise();
}

// 点击添加好友按钮。实现打开添加好友界面，搜索添加好友
void MainWindow::ClickAddFriendLabelSlot() {
    // qDebug() << "打开添加好友控件 ...";
    if (addFriendWidget == nullptr) {
        addFriendWidget = new AddFriendWidget();
    }
    addFriendWidget->showNormal();
    addFriendWidget->raise();
}

// 点击创建群聊按钮。
void MainWindow::ClickCreateTeamLabelSlot() {
     // qDebug() << "打开创建群聊控件 ...";
    if (createTeamWidget == nullptr) {
        createTeamWidget = new CreateTeamWidget();
    }
    createTeamWidget->setFriendProfileMap(friendListWidget->getFriendProfileMap());
    createTeamWidget->setUserNameCardMap(friendListWidget->getUserNameCardMap());
    createTeamWidget->updateWindow();

    createTeamWidget->showNormal();
    createTeamWidget->raise();
}

// 点击搜索群聊按钮。
void MainWindow::ClickSearchTeamLabelSlot() {
     qDebug() << "打开搜索群聊控件 ...";

}

// 选项卡按钮选中之后槽函数，主要更新按钮的样式、显示点击的界面窗口
void MainWindow::toolLabelChecked() {
    auto *label = (ToolLabel *) sender();
            foreach(ToolLabel *toolLabel, toolLabels) {
            toolLabel->setUnChecked();
            toolLabel->style()->polish(toolLabel);      // 自定义属性在调用后必须调用刷新样式的操作!!!
        }
    label->setChecked();
    label->style()->polish(label);
    mainStackedWidget->setCurrentIndex(label->objectName().toInt());
//    qDebug() << "checked ...";
}

void MainWindow::UserCardChangeToChattingWindowSlot(const nim::UserNameCard &nameCard) {
    QString accId = QString::fromStdString(nameCard.GetAccId());
    if (chattingWindows.contains(accId)) {
        // 如果存在已经打开的该聊天窗口，则更新需要更新的信息
        chattingWindows[accId]->setUserNameCard(nameCard);
        chattingWindows[accId]->updateChattingWindow();
    }
}

void MainWindow::FriendProfileChangeToChattingWindowSlot(const nim::FriendProfile &friendProfile) {
    QString accId = QString::fromStdString(friendProfile.GetAccId());
    if (chattingWindows.contains(accId)) {
        // 如果存在已经打开的该聊天窗口，则更新需要更新的信息
        chattingWindows[accId]->setFriendProfile(friendProfile);
        chattingWindows[accId]->updateChattingWindow();
    }
}

// 最近会话变动，需要将会话数据传递给聊天界面中
void MainWindow::SessionChangToChattingWindowSlot(const nim::SessionData &sessionData) {
    if (chattingWindows.contains(QString::fromStdString(sessionData.id_))) {
        chattingWindows[QString::fromStdString(sessionData.id_)]->setSessionData(sessionData);
    }
}

// 从好友列表中双击某一个好友打开聊天界面
void MainWindow::OpenChattingWindowFromFriendListsSlot(const nim::UserNameCard &userNameCard) {
    if (chattingWindows.contains(QString::fromStdString(userNameCard.GetAccId()))) {
        // 如果与该好友的聊天界面已经存在，则直接打开
        chattingWindows[QString::fromStdString(userNameCard.GetAccId())]->showNormal();     // 让最小化的窗口显示出来
        chattingWindows[QString::fromStdString(userNameCard.GetAccId())]->raise();          // 让该聊天窗口置顶显示
        return;
    }
    // 如果从好友列表里打开与该用户的聊天窗口，则需要向最近会话列表里插入与该好友的会话记录（如果最近的会话列表里没有该用户的话），
    // 创建一个会话数据；
    // 如果最近会话列表里有与该用户的会话记录，则获取到该会话数据。
    auto sessionItemMap = recentSessionWidget->getAllSessionItemMap();
    if (sessionItemMap.contains(QString::fromStdString(userNameCard.GetAccId()))) {
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

// 从群聊列表中双击某一个群打开聊天界面
void MainWindow::OpenChattingWindowFromTeamInfoListSlot(const nim::TeamInfo &teamInfo) {
    if (chattingWindows.contains(QString::fromStdString(teamInfo.GetTeamID()))) {
        // 如果与该群的聊天界面已经存在，则直接打开
        chattingWindows[QString::fromStdString(teamInfo.GetTeamID())]->showNormal();     // 让最小化的窗口显示出来
        chattingWindows[QString::fromStdString(teamInfo.GetTeamID())]->raise();          // 让该聊天窗口置顶显示
        return;
    }
    // 如果从群列表里打开该群的聊天窗口，则需要向最近会话列表里插入该群的会话记录（如果最近的会话列表里没有该群的话），
    // 创建一个会话数据；
    // 如果最近会话列表里有与该群的会话记录，则获取到该会话数据。
    auto sessionItemMap = recentSessionWidget->getAllSessionItemMap();
    if (sessionItemMap.contains(QString::fromStdString(teamInfo.GetTeamID()))) {
        // 如果最近会话里有与该用户的会话，则获取到该会话数据，并使用该会话数据打开聊天窗口。然后直接返回即可。
        OpenChattingWindowFromRecentSessionSlot(
                sessionItemMap[QString::fromStdString(teamInfo.GetTeamID())]->getSessionData()
        );
        return;
    }
    // 说明最近会话列表里没有与该用户的会话，则需要自己创建一个新的会话并创建聊天窗口。
    nim::SessionData session;
    session.id_ = teamInfo.GetTeamID();
    session.type_ = nim::kNIMSessionTypeTeam;
    session.msg_timetag_ = ((int64_t) (QDateTime::currentDateTimeUtc().toTime_t())) * 1000;
    recentSessionWidget->AddSessionItem(session, 0);
    OpenChattingWindowFromRecentSessionSlot(session);

}

// 从最近会话中双击某一个会话打开聊天界面
void MainWindow::OpenChattingWindowFromRecentSessionSlot(const nim::SessionData &sessionData) {

    if (chattingWindows.contains(QString::fromStdString(sessionData.id_))) {
        // 如果与该好友的聊天界面已经存在，则直接打开
        chattingWindows[QString::fromStdString(sessionData.id_)]->showNormal();     // 让最小化的窗口显示出来
        chattingWindows[QString::fromStdString(sessionData.id_)]->raise();  // 让该聊天窗口置顶显示
        return;
    }
    // 用户的唯一账号 accID 或者是群聊下的 teamID
    QString accId = QString::fromStdString(sessionData.id_);

    // 与该好友的聊天界面不存在，则新建聊天界面并打开
    auto *chattingWindow = new ChattingWindow(sessionData);

    // 获取所有的好友关系列表
    auto &profiles = friendListWidget->getFriendProfileMap();
    if (profiles.contains(accId)) {
        // 二者是好友关系
        qDebug() << "[info]: " << __FUNCTION__ << ", is friend ...";
        chattingWindow->setFriendProfile(profiles[accId]);
    }

    // 获取所有的用户信息
    auto &userCards = friendListWidget->getUserNameCardMap();

    if (userCards.contains(accId)) {
        // 已经存在该用户信息
        chattingWindow->setUserNameCard(userCards[accId]);
    }

    // 获取所有的群聊信息
    auto &teamInfos = teamListWidget->getTeamInfoMap();
    if (teamInfos.contains(accId)) {
        chattingWindow->setTeamInfo(teamInfos[accId]);
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
void MainWindow::CloseChattingWindowSlot(const QString &id) {
    qDebug() << "[info]: close chatting window : " << id;
    if (!chattingWindows.contains(id)) {
        qDebug() << "[error]: close window error, the closed window '" << id << "' not in all opened windows: "
                 << chattingWindows.keys();
        return;
    }
    // 删除该聊天窗口
    auto *window = chattingWindows.take(id);
    if (window) {
        window->hide();
        delete window;
    }
}




