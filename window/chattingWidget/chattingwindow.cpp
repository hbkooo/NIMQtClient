//
// Created by 19216 on 2021/5/31.
//

#include "chattingwindow.h"

QString ChattingWindow::NO_MORE_MSG_TAG = "noMoreInfo";
QString ChattingWindow::TIME_INFO_TAG = "timeInfo";
QString ChattingWindow::NORMAL_MSG_TAG = "normalMsg";

ChattingWindow::ChattingWindow(const nim::SessionData &data, QWidget *parent) :
        sessionData(data), QWidget(parent) {

    // 默认构造的用户好友关系中，accID为空，设置为非好友关系。用户调用 set 方法后可以获得该属性的值。
    friendProfile.SetAccId("");
    friendProfile.SetRelationship(nim::kNIMFriendFlagNotFriend);
    // 默认设置的用户信息的 accID 为空。用户调用 set 方法后可以获得该属性的值。
    userNameCard.SetAccId("");

    setWindowTitle(QString::fromStdString(data.id_));
    setMinimumSize(790, 900);
    setStyleSheet("background:#ffffff");

    if (sessionData.type_ != nim::kNIMSessionTypeP2P) {
        // 如果不是 P2P 的双向用户聊天类型，则一定是群聊类型。则可以获取群成员信息
        GetTeamMembers(sessionData.id_);
    }

//    QueryMsg();
    QueryMsgOnline();

    InitHeader();
    InitCenterMessage();
    InitBottomEnterMessage();
    SetConnect();
    SetLayout();
    messageTextEdit->installEventFilter(this);

    // Qt窗口在Close()指令后调用CloseEven()，最后判断是否关闭
    // 若关闭，则Hide()窗口，并不是真正的释放内存。若不关闭则不作任何操作
    setAttribute(Qt::WA_QuitOnClose);       // 实现窗口在Close()后自动释放内存需要设置该属性。

}

ChattingWindow::~ChattingWindow() {
    qDebug() << "[info]: In ~ChattingWindow delete chatting window of " << QString::fromStdString(sessionData.id_);
}

void ChattingWindow::InitHeader() {

    headerPhotoLabel = new ClickableLabel("头像");
    headerPhotoLabel->setCursor(QCursor(Qt::PointingHandCursor));       // 鼠标移上去变手型
    headerPhotoLabel->setToolTip("查看详细信息");
    headerPhotoLabel->setFixedSize(48, 48);
    QPixmap map(":/default_header/dh1");
    headerPhotoLabel->setPixmap(PixmapToRound(map.scaled(headerPhotoLabel->size()),
                                              headerPhotoLabel->height() / 2));

    accountLabel = new QLabel("用户名");
    accountLabel->setText(QString::fromStdString(sessionData.id_));
    accountLabel->setStyleSheet("color:#353535;"
                                "font-size:20px;");

    stateLabel = new QLabel("在线");
    stateLabel->setStyleSheet("color:#888888;"
                              "font-size:14px;");

    auto *vLayout = new QVBoxLayout();
    vLayout->addStretch();
    vLayout->addWidget(accountLabel, 0, Qt::AlignLeft);
    vLayout->addWidget(stateLabel, 0, Qt::AlignLeft);
    vLayout->addStretch();

    auto *headerLayout = new QHBoxLayout();
    headerLayout->setContentsMargins(10, 0, 0, 0);
    headerLayout->addWidget(headerPhotoLabel);
    headerLayout->addLayout(vLayout);
    headerLayout->addStretch();

    headerWidget = new QWidget();
    headerWidget->setStyleSheet("background:#eae9eb;");
    headerWidget->setFixedHeight(70);
    headerWidget->setLayout(headerLayout);

}

void ChattingWindow::InitCenterMessage() {
    chattingListWidget = new QListWidget();
    QFile css(":/css/listWidget");
    css.open(QFile::ReadOnly);
    chattingListWidget->setStyleSheet(css.readAll());
    chattingListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);//水平滚动条关闭
    chattingListWidget->setFocusPolicy(Qt::NoFocus);      // 删除选中 某一个item是产生的虚线框
    chattingListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);   // 让内容连续地滚动，而不是整行整行的滚动
    chattingListWidget->setAutoScroll(false);
    verticalScrollBar = chattingListWidget->verticalScrollBar();        // 获取垂直滚动条

    messageLayout = new QVBoxLayout();
    messageLayout->addWidget(chattingListWidget);
}

void ChattingWindow::InitBottomEnterMessage() {

    messageTextEdit = new QTextEdit();
    messageTextEdit->setContentsMargins(20, 20, 40, 20);
    messageTextEdit->setStyleSheet("border: none;"
                                   "font-size: 18px;"
                                   "color: black;");
    messageTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);    // 隐藏右侧的滚动条
    messageTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);    // 隐藏右侧的滚动条
    messageTextEdit->setLineWidth(30);
    // 设置行间距
    QTextBlockFormat blockFormat;
    blockFormat.setLineHeight(10, QTextBlockFormat::LineDistanceHeight);
    auto textCursor = messageTextEdit->textCursor();
    textCursor.setBlockFormat(blockFormat);
    messageTextEdit->setTextCursor(textCursor);


    sendButton = new QPushButton("发送");
    sendButton->setFixedSize(120, 40);
    sendButton->setStyleSheet("QPushButton { font-size:20px;"
                              "color:white;"
                              "border: none;"
                              "background-color:#238efa;}"
                              "QPushButton:hover {"
                              "background-color:#4ca6ff;}"
                              "QPushButton:pressed {"
                              "background-color:#1f7ddb;}"
                              "QPushButton:focus{outline: none;}" // 获取焦点时不显示虚线框
    );

    auto vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(10, 10, 10, 10);
    vLayout->setSpacing(10);
    vLayout->addWidget(messageTextEdit);
    vLayout->addWidget(sendButton, 0, Qt::AlignRight);

    enterMessageWidget = new QWidget();
    enterMessageWidget->setFixedHeight(220);
    enterMessageWidget->setLayout(vLayout);
}

void ChattingWindow::SetLayout() {

    auto splitWidget = new QWidget();
    splitWidget->setStyleSheet("background:#d2d4d6;");
    splitWidget->setFixedHeight(2);

    mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(headerWidget);
    mainLayout->addLayout(messageLayout);
    mainLayout->addWidget(splitWidget);
    mainLayout->addWidget(enterMessageWidget);
    this->setLayout(mainLayout);
}

void ChattingWindow::SetConnect() {
    // 点击聊天窗口的头像
    connect(headerPhotoLabel, &ClickableLabel::clicked, this, &ChattingWindow::ClickedHeaderPhotoLabelSlot);
    // 点击发送信息按钮
    connect(sendButton, &QPushButton::clicked, this, &ChattingWindow::sendMessageSlot);
    // 每次从云端获取完新的聊天消息时都更新聊天界面，将聊天消息插入到聊天界面中显示
    connect(this, &ChattingWindow::updateMsgListWidgetSignal,
            this, &ChattingWindow::updateMsgListWidgetSlot);
    // 主要监听聊天记录中垂直滚动条滑动到最上端之后继续从云端获取加载聊天记录
    connect(verticalScrollBar, &QScrollBar::valueChanged, this, &ChattingWindow::valueChangeSlot);
    // 云端已经没有聊天记录了，更新界面显示“已加载全部聊天记录”提示
    connect(this, &ChattingWindow::noMoreMessageSignal,
            this, &ChattingWindow::noMoreMessageSlot);
    // 更新聊天界面的显示信息。主要是聊天界面的头部控件信息。触发事件为：P2P下用户名片修改；team下，群数据更改。
    connect(this, &ChattingWindow::updateChattingWindowSignal, this,
            &ChattingWindow::updateChattingWindow);
}

// 更新聊天窗口的头像图标
void ChattingWindow::updateHeaderPhotoIcon() {
    // TODO 更新聊天窗口的头像，需要判断该聊天窗口是 P2P 的双向好友聊天，还是群聊
    QPixmap map;
    if (sessionData.type_ == nim::kNIMSessionTypeP2P) {
        // P2P 双向用户聊天
        if (userNameCard.GetIconUrl().empty()) {
            userNameCard.SetIconUrl(":/default_header/dh1");
        }
        map.load(QString::fromStdString(userNameCard.GetIconUrl()));
        if (map.isNull()) {
            // 头像加载失败
            map.load(":/default_header/dh1");
        }
    } else if (sessionData.type_ == nim::kNIMSessionTypeTeam) {
        // 群聊
        if (teamInfo.GetIcon().empty()) {
            teamInfo.SetIcon(":/default_header/default_team");
        }
        map.load(QString::fromStdString(teamInfo.GetIcon()));
        if (map.isNull()) {
            // 头像加载失败
            map.load(":/default_header/default_team");
        }
    } else {
        // TODO 超级群聊
    }
    headerPhotoLabel->setPixmap(PixmapToRound(map.scaled(headerPhotoLabel->size()), headerPhotoLabel->height() / 2));
}

// 更新聊天界面的显示信息。主要是聊天界面的头部控件信息。一般是调用好上面的三个set方法之后然后调用该方法，更新头控件数据
void ChattingWindow::updateChattingWindow() {
    // TODO 需要判断该聊天窗口是 P2P 的双向好友聊天，还是群聊

    if (sessionData.type_ == nim::kNIMSessionTypeP2P) {
        /** P2P 双向用户聊天
         * 设置聊天窗口的标题，对好友的备注或者是好友自己创建账号时的昵称
         * 首先判断是否为好友关系，即获取好友列表里的每一项 FriendProfile，判断是存在该用户，如果有该用户则与其为好友关系；
         * 是好友关系的话则获取 FriendProfile 的 alias_ 字段获取对好友的备注昵称。
         * 如果昵称备注为空，则需要获取用户 UserNameCard 的 nickname_ 昵称字段。
         * 如果用户的昵称字段 nickname_ 也为空，则直接显示用户的 accID。
         */
        if (userNameCard.GetAccId().empty() || userNameCard.GetAccId() != sessionData.id_) {
            // 用户信息的 accID 为空，说明没有调用 set 方法，需要重新获取该聊天用户的信息。
            // 或者用户信息的名片 accID 与会话数据的 id 不一样，说明该 userNameCard 与该会话数据不一样，所以需要重新获取该会话用户的信息。
            // 获取用户信息，然后再更新界面信息。
            GetUserNameCardOnLine(sessionData.id_);
            qDebug() << "userNameCard 无效，重新获取 ...";
            return;
        }

        // 用户名片信息有效，首先使用该名片信息更新界面数据
        QString name = QString::fromStdString(userNameCard.GetName());
        if (name != "") {
            // 用户昵称不为空
            accountLabel->setText(name);
        } else {
            // 用户昵称为空，则用户名设置为用户的 accID
            accountLabel->setText(QString::fromStdString(userNameCard.GetAccId()));
        }
        // 用户状态设置为用户的签名信息
        stateLabel->setText(QString::fromStdString(userNameCard.GetSignature()));

        // 首先判断是否为好友关系。如果是好友关系则聊天窗口标题设置为好友关系里设置的备注
        if (friendProfile.GetRelationship() == nim::kNIMFriendFlagNormal) {
            qDebug() << "二者是好友关系: " << QString::fromStdString(friendProfile.GetAccId());
            // 如果是好友关系
            QString alias = QString::fromStdString(friendProfile.GetAlias());
            if (alias != "") {
                // 备注不为空，则直接设置为备注信息
                accountLabel->setText(alias);
            }
        } else {
            // 非好友关系
            stateLabel->setText("非好友");     // 状态设置为非好友
            qDebug() << "二者不是好友关系: " << QString::fromStdString(friendProfile.GetAccId());
        }
    } else if (sessionData.type_ == nim::kNIMSessionTypeTeam) {
        // 群聊
        // 状态标签显示群聊的 teamID
        stateLabel->setText(QString::fromStdString(teamInfo.GetTeamID()));
        // 账号信息显示群聊的名称
        accountLabel->setText(QString::fromStdString(teamInfo.GetName()));
    } else {
        // TODO 超级群聊
    }

    // 更新聊天窗口的头像
    updateHeaderPhotoIcon();

}

/**
 * 在消息列表头部插入一条消息
 * @param msg 消息
 * @param extIndex msg 消息在全部消息列表 chattingMsg 中的序号，扩展位，可以不使用。默认为-1，即表示不使用该位信息
 */
void ChattingWindow::AddOneMsgFront(const nim::IMMessage &msg, int extIndex) {
    // 判断聊天的每一条消息是否显示用户名。如果是P2P的双向用户聊天，则不显示；否则显示。
    bool showName = false;
    if (sessionData.type_ == nim::kNIMSessionTypeP2P) {
        showName = false;
    } else {
        showName = true;
    }
    // 首先插入聊天消息
    // 插入具体的聊天消息
    ChattingItem *chattingItem;
    if (SELF_USER_NAME_CARD.GetAccId() == msg.sender_accid_) {
        // 消息发送者 id 与已经登录成功的用户 id 一样，则说明是自己发送的消息
        chattingItem = new ChattingItem(false, SELF_USER_NAME_CARD, showName);
    } else {
        // 否则说明该条消息是好友发来的。
        // 首先构造该好友的用户名片，默认只先构造名片数据只包含用户的唯一标识 accID
        nim::UserNameCard nameCard(msg.sender_accid_);
        if (userNameCardMap.contains(msg.sender_accid_)) {
            // 已经获取到了该用户的名片信息
            nameCard = userNameCardMap[msg.sender_accid_];
        } else {
            // 如果目前没有该用户的名片信息。需要重新获取该用户的名片
            GetUserNameCardOnLine(msg.sender_accid_);
        };
        chattingItem = new ChattingItem(true, nameCard, showName);
    }
    // 这里主要为了当点击某一个聊天消息的头像时，显示该用户的详细信息
    connect(chattingItem, &ChattingItem::ShowHeaderPhotoLabelSignal, this,
            &ChattingWindow::ShowHeaderPhotoLabelSlot);
    chattingItem->updateContent(msg);
    auto *listItem = new QListWidgetItem();
    listItem->setData(Qt::UserRole, NORMAL_MSG_TAG);
    listItem->setSizeHint(QSize(0, chattingItem->sizeHint().height()));
    chattingListWidget->insertItem(0, listItem);
    chattingListWidget->setItemWidget(listItem, chattingItem);
//    chattingListWidget->scrollToItem(listItem);

    // 把该消息记录添加到对应用户的所有条目中
    if (usersChattingItems.contains(msg.sender_accid_)) {
        // 在该聊天界面中已经有该用户的发言记录
        usersChattingItems[msg.sender_accid_].append(chattingItem);
    } else {
        // 在该聊天界面中暂时没有该用户的发言记录，则直接将该聊天条目插入进去
        usersChattingItems.insert(msg.sender_accid_, {chattingItem});
    }

    if (extIndex != -1) {
        // chattingMsg 是按时间倒序排序的消息列表
        if (chattingMsg.size() == extIndex + 1) {
            // 最后一条消息，则一定添加时间提示
            AddPromptTimeInfo(msg.timetag_, false);
        } else {
            // 不是最后一条消息，需要判断当前消息与下一条消息之间的时间差。
            // 这里的下一条是指在 chattingMsg 的列表中存储的下一条。
            if (IsInsertTimePromptInfo(msg.timetag_, chattingMsg[extIndex + 1].timetag_)) {
                AddPromptTimeInfo(msg.timetag_, false);
            }
        }
    }

}

// 在消息列表尾部插入一条消息
void ChattingWindow::AddOneMsgEnd(const nim::IMMessage &msg) {
    // 判断聊天的每一条消息是否显示用户名。如果是P2P的双向用户聊天，则不显示；否则显示。
    bool showName = false;
    if (sessionData.type_ == nim::kNIMSessionTypeP2P) {
        showName = false;
    } else {
        showName = true;
    }

    // 判断插入时间提示信息
    if (chattingListWidget->count() == 0) {
        // 第一条消息，则直接插入时间
        AddPromptTimeInfo(msg.timetag_);
    } else {
        auto *lastItem = chattingListWidget->item(chattingListWidget->count() - 1);
        if (lastItem->data(Qt::UserRole).toString() == NORMAL_MSG_TAG) {
            // 如果上一条消息是正常的收发消息，则可以将 itemWidget 转化为 ChattingItem 控件
            auto *lastChattingItem = dynamic_cast<ChattingItem *>(chattingListWidget->itemWidget(lastItem));
            if (IsInsertTimePromptInfo(msg.timetag_, lastChattingItem->getIMMessage().timetag_)) {
                // 此消息与上一条记录消息相差5分钟之多，需要插入此消息的时间提示
                AddPromptTimeInfo(msg.timetag_);
            }
        } else if (lastItem->data(Qt::UserRole).toString() == NO_MORE_MSG_TAG) {
            // 上一条消息是一个 “没有更多聊天记录” 的提示信息，说明这是发送的第一条消息，所以首先需要插入聊天时间
            AddPromptTimeInfo(msg.timetag_);
        }
    }

    // 插入具体的聊天消息
    ChattingItem *chattingItem;
    if (SELF_USER_NAME_CARD.GetAccId() == msg.sender_accid_) {
        // 消息发送者 id 与已经登录成功的用户 id 一样，则说明是自己发送的消息
        chattingItem = new ChattingItem(false, SELF_USER_NAME_CARD, showName);
    } else {
        // 否则说明该条消息是好友发来的。
        // 首先构造该好友的用户名片，默认只先构造名片数据只包含用户的唯一标识 accID
        nim::UserNameCard nameCard(msg.sender_accid_);
        if (userNameCardMap.contains(msg.sender_accid_)) {
            // 已经获取到了该用户的名片信息
            nameCard = userNameCardMap[msg.sender_accid_];
        } else {
            // 如果目前没有该用户的名片信息。需要重新获取该用户的名片
            GetUserNameCardOnLine(msg.sender_accid_);
        }
        chattingItem = new ChattingItem(true, nameCard, showName);
    }
    // 这里主要为了当点击某一个聊天消息的头像时，显示该用户的详细信息
    connect(chattingItem, &ChattingItem::ShowHeaderPhotoLabelSignal, this,
            &ChattingWindow::ShowHeaderPhotoLabelSlot);
    chattingItem->updateContent(msg);
    auto *listItem = new QListWidgetItem();
    listItem->setData(Qt::UserRole, NORMAL_MSG_TAG);
    listItem->setSizeHint(QSize(0, chattingItem->sizeHint().height()));
    chattingListWidget->addItem(listItem);
    chattingListWidget->setItemWidget(listItem, chattingItem);
    chattingListWidget->scrollToItem(listItem);

    // 把该消息记录添加到对应用户的所有条目中
    if (usersChattingItems.contains(msg.sender_accid_)) {
        // 在该聊天界面中已经有该用户的发言记录
        usersChattingItems[msg.sender_accid_].append(chattingItem);
    } else {
        // 在该聊天界面中暂时没有该用户的发言记录，则直接将该聊天条目插入进去
        usersChattingItems.insert(msg.sender_accid_, {chattingItem});
    }
}

// 点击聊天窗口的头像显示信息槽函数
void ChattingWindow::ClickedHeaderPhotoLabelSlot() {
    // TODO 修改点击聊天窗口的头像时，显示的界面窗口。
    // 如果该会话是 P2P 的聊天界面，则点击聊天窗口头像直接显示该用于的具体信息
    // 如果该会话是群聊的聊天界面，则点击聊天窗口头像显示的是该群的具体信息
    if (sessionData.type_ == nim::kNIMSessionTypeP2P) {
        // P2P 双向用户聊天
        ShowHeaderPhotoLabelSlot(userNameCard);
    } else if (sessionData.type_ == nim::kNIMSessionTypeTeam) {
        // TODO 普通群聊
        ShowTeamInfoWidget();
    } else {
        // TODO 高级群聊

    }
}

// 传递过来一个用户名片，显示用户名片。主要用在当点击聊天消息中的一条消息中的用户头像时，显示该用户的详细信息
void ChattingWindow::ShowHeaderPhotoLabelSlot(const nim::UserNameCard &nameCard) {
    if (userInfoWidget == nullptr) {
        userInfoWidget = new UserInfoWidget(nameCard);
    }
    // 需要设置显示的名片信息
    userInfoWidget->setUserNameCard(nameCard);
    userInfoWidget->ShowNormal();
}

// 展示群聊详细信息界面
void ChattingWindow::ShowTeamInfoWidget() {
    if (teamInfoWidget == nullptr) {
        teamInfoWidget = new TeamInfoWidget(teamInfo);
    }
    teamInfoWidget->setTeamInfo(teamInfo);
    teamInfoWidget->ShowNormal();
}

// 发送消息
void ChattingWindow::sendMessageSlot() {

    QString msg = messageTextEdit->toPlainText();
    if (msg == "") {
        QMessageBox::information(this, "提示", "请输入内容后再发送", QMessageBox::Ok);
        return;
    }
    // qDebug() << "[info]: 发送消息：" << msg;
    nim::IMMessage message;
    sendTextMsgToReceiver(msg.toStdString(), message);
    AddOneMsgEnd(message);
    chattingMsg.insert(0, message);     // 将该聊天记录添加进所有的记录中
    messageTextEdit->clear();
}

//////////////////////////////////////////////////////////////////////////
////////////////////////// 系统事件监听 ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void ChattingWindow::wheelEvent(QWheelEvent *event) {
    if (currentTopIndex == verticalScrollBar->minimum() && !isQuerying && hasMoreMessage && event->delta() > 0) {
        qDebug() << "[info]: at top and still move ...";
        if (chattingMsg.empty()) {
            QueryMsgOnline();
        } else {
            QueryMsgOnline(0, chattingMsg.last().timetag_, chattingMsg.last().readonly_server_id_);
        }
    }
    QWidget::wheelEvent(event);
}

bool ChattingWindow::eventFilter(QObject *watched, QEvent *event) {
    if (watched == messageTextEdit) {
        if (event->type() == QEvent::KeyPress) {
            auto *k = dynamic_cast<QKeyEvent *>(event);
            if (k->key() == Qt::Key_Enter || k->key() == Qt::Key_Return) {
                if (k->modifiers() & Qt::ControlModifier) {
                    // qDebug() << "[info]: ctrl + enter";
                    messageTextEdit->append("");
                } else {
                    sendMessageSlot();
                }
                return true;
            }
        }
    }
    return QObject::eventFilter(watched, event);
}

void ChattingWindow::mousePressEvent(QMouseEvent *event) {
    if (headerWidget && headerWidget->contentsRect().contains(event->pos())) {
        pressPoint = event->globalPos();
        isMoving = true;
    }
    QWidget::mousePressEvent(event);
}

void ChattingWindow::mouseMoveEvent(QMouseEvent *event) {
    if ((event->buttons() == Qt::LeftButton) && isMoving) {
        int dx = event->globalX() - pressPoint.x();
        int dy = event->globalY() - pressPoint.y();
        move(this->x() + dx, this->y() + dy);
        pressPoint = event->globalPos();
    }
    QWidget::mouseMoveEvent(event);
}

void ChattingWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (isMoving) {
        isMoving = false;
    }
    QWidget::mouseReleaseEvent(event);
}

void ChattingWindow::closeEvent(QCloseEvent *event) {
//    qDebug() << "ChattingWindow : get close event...";
    emit closeChattingWindowSignal(
            QString::fromStdString(sessionData.id_));    // MainWindow::CloseChattingWindowSlot
//    event->ignore();
    QWidget::closeEvent(event);
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void ChattingWindow::QueryMsg() {
    isQuerying = true;          // 当前正在请求，防止再次发送相同的请求
    nim::MsgLog::QueryMsgAsync(sessionData.id_, sessionData.type_, LIMIT_COUNT_PER_REQ, sessionData.msg_timetag_,
                               [this](auto &&PH1, auto &&PH2, auto &&PH3, auto &&PH4) {
                                   OnQueryMsgCallback(std::forward<decltype(PH1)>(PH1),
                                                      std::forward<decltype(PH2)>(PH2),
                                                      std::forward<decltype(PH3)>(PH3),
                                                      std::forward<decltype(PH4)>(PH4));
                               });
}

/**
 * 查询聊天记录。倒序查询，即从结束时间往前查找，找到指定的消息条数后结束本次查找。
 * @param from_time 开始时间，1970年到开始时间的毫秒数，如果为0则是1970年1月1日8:00
 * @param end_time 结束时间，1970年到结束时间的毫秒数，如果为0则是1970年1月1日8:00
 * @param end_msg_id 最后一条消息的服务器消息id，在 IMMessage 中的 readonly_server_id_ 字段中
 */
void ChattingWindow::QueryMsgOnline(int64_t from_time,
                                        int64_t end_time,
                                        int64_t end_msg_id) {
    isQuerying = true;          // 当前正在请求，防止再次发送相同的请求
    nim::MsgLog::QueryMsgOnlineAsync(sessionData.id_, sessionData.type_, LIMIT_COUNT_PER_REQ,
                                     from_time, end_time, end_msg_id,
                                     false, // false表示按时间逆序查询，从最近依次往之前查询，得到的结果也是按时间逆序的。True表示按时间顺序查询，得到的结果也是按时间顺序的。
                                     true,
                                     [this](auto &&PH1, auto &&PH2, auto &&PH3, auto &&PH4) {
                                         OnQueryMsgCallback(std::forward<decltype(PH1)>(PH1),
                                                            std::forward<decltype(PH2)>(PH2),
                                                            std::forward<decltype(PH3)>(PH3),
                                                            std::forward<decltype(PH4)>(PH4));
                                     });

}

void ChattingWindow::OnQueryMsgCallback(nim::NIMResCode res_code, const std::string &id,
                                            nim::NIMSessionType to_type, const nim::QueryMsglogResult &result) {
    //    qDebug() << __FILE__ << ":" << __LINE__ << " ==> res_code: " << res_code;
    //    qDebug() << __FILE__ << ":" << __LINE__ << " ==> id: " << QString::fromStdString(id);
    //    qDebug() << __FILE__ << ":" << __LINE__ << " ==> to_type: " << to_type;
    if (result.msglogs_.empty()) {
        hasMoreMessage = false;
        emit noMoreMessageSignal();     // 没有更多的聊天消息了,ChattingWindow::noMoreMessageSlot
        return;
    }
    for (const auto &msg: result.msglogs_) {
        // 将消息添加进所有的消息列表中。
        // 这里消息的顺序是按时间逆序排列的，也就是说最新的一条消息在数组的第一条，最久远的消息在数组的最后一条
        chattingMsg.append(msg);
    }
    emit updateMsgListWidgetSignal(result.msglogs_.size());     // ChattingWindow::updateMsgListWidgetSlot
}

// 每次从云端获取完新的聊天消息时都更新聊天界面，将聊天消息插入到聊天界面中显示。其中msgNumber是最新获取的消息条目数量
void ChattingWindow::updateMsgListWidgetSlot(int msgNumber) {
    qDebug() << "[info]: get " << msgNumber << " messages ...";
    for (int i = chattingMsg.size() - msgNumber; i < chattingMsg.size(); ++i) {
        const auto &msg = chattingMsg.at(i);
        AddOneMsgFront(msg, i);
    }
    if (chattingMsg.size() == msgNumber) {
        // 第一次初始化聊天界面时，则需要滚动到最下面最新的聊天消息中
        // 当后面往上翻滚查看更多聊天消息并且加载了更多的聊天消息时，则不用再滚动到最下面，直接保持不动
        chattingListWidget->scrollToBottom();
    }
    // else {
    // 后面继续获取消息
    //    chattingListWidget->scrollToItem(chattingListWidget->item(msgNumber));
    // }
    isQuerying = false;             // 聊天消息请求结束，可以进行下一步的请求
}

// 调用nim接口将消息发送给该聊天界面的用户
void ChattingWindow::sendTextMsgToReceiver(const std::string &content, nim::IMMessage &message) {

    std::string msg_json = nim::Talk::CreateTextMessage(sessionData.id_, sessionData.type_,
                                                        nim::Tool::GetUuid(),
                                                        content,
                                                        nim::MessageSetting());
    nim::Talk::SendMsg(msg_json);
    // 构造一个消息对象
    message = std::move(nim::IMMessage(msg_json));
    message.timetag_ = QDateTime::currentDateTimeUtc().toTime_t();  // 秒数
    message.timetag_ *= 1000;       // 需要×1000转化为毫秒数
    message.sender_accid_ = SELF_USER_NAME_CARD.GetAccId();         // 设置该消息的发送者为自己
}

// 消息发送之后会有一个发送回调，通知发送的结果。该槽函数来自于信号RecentSessionWidget::sendMsgCallbackSignal
void ChattingWindow::sendMsgCallbackSlot(const nim::SendMessageArc &messageArc) {
    if (messageArc.rescode_ == nim::kNIMResSuccess) {
        qDebug() << "[info]: 消息回执：消息发送成功...";
    } else {
        qDebug() << "[error]: 消息发送失败，code : " << messageArc.rescode_;
    }
}

// 当其他用户发送来新的消息后所有的聊天窗口界面都会收到该消息。该槽函数来自于信号RecentSessionWidget::receiveMsgSignal
void ChattingWindow::receiveMsgSlot(const nim::IMMessage &msg) {
    std::string id = msg.local_talk_id_;
    if (id != sessionData.id_) {
        // 该消息不属于该聊天界面窗口，直接放弃
        return;
    }
    AddOneMsgEnd(msg);
    if (msg.feature_ == nim::kNIMMessageFeatureDefault) {
        qDebug() << "\n[info]: 收到默认消息：" << QString::fromStdString(msg.ToJsonString(true));

    } else if (msg.feature_ == nim::kNIMMessageFeatureSyncMsg
               || msg.feature_ == nim::kNIMMessageFeatureRoamMsg) {
        qDebug() << "\n[info]: 收到同步或漫游消息：" << QString::fromStdString(msg.ToJsonString(true));

    } else if (msg.feature_ == nim::kNIMMessageFeatureCustomizedMsg) {
        qDebug() << "\n[info]: 收到透传消息：" << QString::fromStdString(msg.ToJsonString(true));

    } else if (msg.feature_ == nim::kNIMMessageFeatureLeaveMsg) {
        qDebug() << "\n[info]: 收到离线消息：" << QString::fromStdString(msg.ToJsonString(true));
    }
}

// 当聊天消息ListWidget滑动时触发滑动到的位置信息。以此来处理滑动到到最顶端的时候加载更多的聊天信息
void ChattingWindow::valueChangeSlot(int position) {
    currentTopIndex = position;
    if (position == verticalScrollBar->minimum() && !isQuerying && hasMoreMessage) {
        qDebug() << "[info]: 滑动到最顶端，需要加载更多记录 ...";
        QueryMsgOnline(0, chattingMsg.last().timetag_, chattingMsg.last().readonly_server_id_);
    }
}

// 当获取消息时，没有更多的聊天消息处理槽函数
void ChattingWindow::noMoreMessageSlot() {
    qDebug() << "[info]: 没有更多的聊天消息了";
    isQuerying = false;             // 聊天消息请求结束，可以进行下一步的请求

    // 插入提示信息，提示已经显示了全部的历史消息
    auto *label = new QLabel("已显示全部历史消息");
    label->setAlignment(Qt::AlignHCenter);
    label->setContentsMargins(0, 10, 0, 10);
    label->setStyleSheet("font-size:14px;"
                         "color:#898989;");
    auto *listItem = new QListWidgetItem();
    listItem->setData(Qt::UserRole, NO_MORE_MSG_TAG);
    listItem->setSizeHint(QSize(0, label->sizeHint().height()));
    chattingListWidget->insertItem(0, listItem);
    chattingListWidget->setItemWidget(listItem, label);
}

/**
 * 向ListWidget中添加一条提示消息
 * @param time 插入的时间，毫秒数
 * @param end 是否插入到末尾，true 则插入到 ListWidget 的末尾； false 则插入到头部。默认是 true ，插入到末尾。
 */
void ChattingWindow::AddPromptTimeInfo(int64_t time, bool end) {

    auto *label = new QLabel(FormatTimeInfoInChattingWindow(time));
    label->setAlignment(Qt::AlignHCenter);
    label->setContentsMargins(0, 10, 0, 10);
    label->setStyleSheet("font-size:14px;"
                         "color:#898989;");
    auto *listItem = new QListWidgetItem();
    listItem->setData(Qt::UserRole, TIME_INFO_TAG);        // 添加一个标记，区分是消息还是提示时间
    listItem->setSizeHint(QSize(0, label->sizeHint().height()));
    if (end) {
        chattingListWidget->addItem(listItem);
    } else {
        chattingListWidget->insertItem(0, listItem);
    }
    chattingListWidget->setItemWidget(listItem, label);
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////根据用户 id 查询用户详细信息 ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
void ChattingWindow::GetUserNameCard(const std::string &account) {
    std::list<std::string> account_list;
    account_list.push_back(account);
    nim::User::GetUserNameCard(account_list, [this](auto &&PH1) {
        OnGetUserCard(std::forward<decltype(PH1)>(PH1));
    });
}

void ChattingWindow::GetUserNameCardOnLine(const std::string &account) {
    std::list<std::string> account_list;
    account_list.push_back(account);
    nim::User::GetUserNameCardOnline(account_list, [this](auto &&PH1) {
        OnGetUserCard(std::forward<decltype(PH1)>(PH1));
    });
}

void ChattingWindow::OnGetUserCard(const std::list<nim::UserNameCard> &json_result) {
    if (json_result.empty()) {
        if (sessionData.type_ == nim::kNIMSessionTypeP2P) {
            // 如果是 P2P 的双向用户聊天，则查询好友的操作只存在于 ChattingWindow::updateChattingWindow()中，
            // 而且是 userNameCard accID 为空或者 accID 与sessionData.id_不同导致
            // 如果返回的查询数据为空，说明系统里不存在该用户，即查询的 accID 是错误的。
            // 这里强制设置用户名片 id 为会话 id，结束后续的不断查询。
            userNameCard.SetAccId(sessionData.id_);
        }
    } else {
        for(const auto &nameCard: json_result) {
            userNameCardMap.insert(nameCard.GetAccId(), nameCard);
            if (usersChattingItems.contains(nameCard.GetAccId())) {
                // 如果已经存在的聊天记录中有该用户已经发送的消息，则需要更新这些用户的消息条目中的数据。比如头像、名片等。
                for(const auto &chattingItem: usersChattingItems[nameCard.GetAccId()]) {
                    // 正好这里可以更新前面创建聊天 item 时，自行只设置了accID的名片。
                    chattingItem->setUserNameCard(nameCard);
                    chattingItem->updateNamePhoto();
                }
            }

        }
    }
    if (sessionData.type_ == nim::kNIMSessionTypeP2P) {
        // 如果是P2P的双向用户聊天，则被聊天的对象名片发生变化时，则需要更新该聊天界面的信息。
        // 如果是群聊的话，只有修改了群的相关信息才会更新聊天界面信息。
        emit updateChattingWindowSignal();      // 更新聊天界面标题。ChattingWindow::updateChattingWindow
    }

}
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////


// 获取群组成员
void ChattingWindow::GetTeamMembers(const std::string &teamID) {
    nim::Team::QueryTeamMembersAsync(teamID,
                                     [this](const std::string &tid,
                                            int member_count,
                                            const std::list<nim::TeamMemberProperty> &props) {
                                         qDebug() << "[info]: get " << member_count << " members in "
                                                  << QString::fromStdString(tid);
                                     });
}



