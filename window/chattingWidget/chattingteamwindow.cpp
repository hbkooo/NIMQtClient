//
// Created by 19216 on 2021/5/31.
//

#include "chattingteamwindow.h"

QString ChattingTeamWindow::NO_MORE_MSG_TAG = "noMoreInfo";
QString ChattingTeamWindow::TIME_INFO_TAG = "timeInfo";
QString ChattingTeamWindow::NORMAL_MSG_TAG = "normalMsg";

ChattingTeamWindow::ChattingTeamWindow(const nim::SessionData &data, QWidget *parent) :
        sessionData(data), QWidget(parent) {

    // 默认构造的用户好友关系中，accID为空，设置为非好友关系。用户调用 set 方法后可以获得该属性的值。
    friendProfile.SetAccId("");
    friendProfile.SetRelationship(nim::kNIMFriendFlagNotFriend);
    // 默认设置的用户信息的 accID 为空。用户调用 set 方法后可以获得该属性的值。
    userNameCard.SetAccId("");

    setWindowTitle(QString::fromStdString(data.id_));
    setMinimumSize(790, 900);
    setStyleSheet("background:#ffffff");

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

ChattingTeamWindow::~ChattingTeamWindow() {
    qDebug() << "[info]: In ~ChattingTeamWindow delete chatting window of " << QString::fromStdString(sessionData.id_);
}

void ChattingTeamWindow::InitHeader() {

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

void ChattingTeamWindow::InitCenterMessage() {
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

void ChattingTeamWindow::InitBottomEnterMessage() {

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

void ChattingTeamWindow::SetLayout() {

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

void ChattingTeamWindow::SetConnect() {
    // 点击聊天窗口的头像
    connect(headerPhotoLabel, &ClickableLabel::clicked, this, &ChattingTeamWindow::ClickedHeaderPhotoLabelSlot);
    // 点击发送信息按钮
    connect(sendButton, &QPushButton::clicked, this, &ChattingTeamWindow::sendMessageSlot);
    // 每次从云端获取完新的聊天消息时都更新聊天界面，将聊天消息插入到聊天界面中显示
    connect(this, &ChattingTeamWindow::updateMsgListWidgetSignal, this, &ChattingTeamWindow::updateMsgListWidgetSlot);
    // 主要监听聊天记录中垂直滚动条滑动到最上端之后继续从云端获取加载聊天记录
    connect(verticalScrollBar, &QScrollBar::valueChanged, this, &ChattingTeamWindow::valueChangeSlot);
    // 云端已经没有聊天记录了，更新界面显示“已加载全部聊天记录”提示
    connect(this, &ChattingTeamWindow::noMoreMessageSignal, this, &ChattingTeamWindow::noMoreMessageSlot);
    // 更新聊天界面的显示信息。主要是聊天界面的头部控件信息。
    connect(this, &ChattingTeamWindow::updateChattingTeamWindowSignal, this, &ChattingTeamWindow::updateChattingTeamWindow);
}

// 更新聊天窗口的头像图标
void ChattingTeamWindow::updateHeaderPhotoIcon() {
    if (userNameCard.GetIconUrl().empty()) {
        userNameCard.SetIconUrl(":/default_header/dh1");
    }
    QPixmap map(QString::fromStdString(userNameCard.GetIconUrl()));
    if (map.isNull()) {
        // 头像加载失败
        map.load(":/default_header/dh1");
    }
    headerPhotoLabel->setPixmap(PixmapToRound(map.scaled(headerPhotoLabel->size()), headerPhotoLabel->height() / 2));
}

// 更新聊天界面的显示信息。主要是聊天界面的头部控件信息。一般是调用好上面的三个set方法之后然后调用该方法，更新头控件数据
void ChattingTeamWindow::updateChattingTeamWindow() {
    /**
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

    // 不论二者是否为好友关系，聊天窗口的头像是一样的。所以现在即可更新聊天窗口的头像
    updateHeaderPhotoIcon();

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

}

/**
 * 在消息列表头部插入一条消息
 * @param msg 消息
 * @param extIndex msg 消息在全部消息列表 chattingMsg 中的序号，扩展位，可以不使用
 */
void ChattingTeamWindow::AddOneMsgFront(const nim::IMMessage &msg, int extIndex) {
    bool isRight;
    if (msg.sender_accid_.empty()) {
        // 从msg_json构造的 IMMessage 消息发送者为空；所以可以知道是用户点击发送发送的消息
        isRight = true;
    } else {
        // 有发送者id，则判断发送者id和当前的聊天窗口id是否一致，如果不一致则说明消息在右边，是自己发送的；
        // 如果一致则说明消息在左边，是好友发送给自己的消息
        isRight = (msg.sender_accid_ != sessionData.id_);
    }

    // 首先插入聊天消息
    // 插入具体的聊天消息
    ChattingItem *item;
    if (sessionData.id_ == msg.sender_accid_) {
        // 会话id与消息的发送者id一致，则说明该条消息是好友发来的。
        item = new ChattingItem(true, userNameCard);
    } else {
        // 否则说明该消息是自己发送给好友的
        item = new ChattingItem(false, SELF_USER_NAME_CARD);
    }
    // 这里主要为了当点击某一个聊天消息的头像时，显示该用户的详细信息
    connect(item, &ChattingItem::ShowHeaderPhotoLabelSignal, this, &ChattingTeamWindow::ShowHeaderPhotoLabelSlot);
    item->updateContent(msg);
    auto *listItem = new QListWidgetItem();
    listItem->setData(Qt::UserRole, NORMAL_MSG_TAG);
    listItem->setSizeHint(QSize(0, item->sizeHint().height()));
    chattingListWidget->insertItem(0, listItem);
    chattingListWidget->setItemWidget(listItem, item);
//    chattingListWidget->scrollToItem(listItem);

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
void ChattingTeamWindow::AddOneMsgEnd(const nim::IMMessage &msg) {
    bool isRight;
    if (msg.sender_accid_.empty()) {
        // 从msg_json构造的 IMMessage 消息发送者为空；所以可以知道是用户点击发送发送的消息
        isRight = true;
    } else {
        // 有发送者id，则判断发送者id和当前的聊天窗口id是否一致，如果不一致则说明消息在右边，是自己发送的；
        // 如果一致则说明消息在左边，是好友发送给自己的消息
        isRight = (msg.sender_accid_ != sessionData.id_);
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
    ChattingItem *item;
    if (sessionData.id_ == msg.sender_accid_) {
        // 会话id与消息的发送者id一致，则说明该条消息是好友发来的。
        item = new ChattingItem(true, userNameCard);
    } else {
        // 否则说明该消息是自己发送给好友的
        item = new ChattingItem(false, SELF_USER_NAME_CARD);
    }
    // 这里主要为了当点击某一个聊天消息的头像时，显示该用户的详细信息
    connect(item, &ChattingItem::ShowHeaderPhotoLabelSignal, this, &ChattingTeamWindow::ShowHeaderPhotoLabelSlot);
    item->updateContent(msg);
    auto *listItem = new QListWidgetItem();
    listItem->setData(Qt::UserRole, NORMAL_MSG_TAG);
    listItem->setSizeHint(QSize(0, item->sizeHint().height()));
    chattingListWidget->addItem(listItem);
    chattingListWidget->setItemWidget(listItem, item);
    chattingListWidget->scrollToItem(listItem);
}

// 点击聊天窗口的头像显示信息槽函数
void ChattingTeamWindow::ClickedHeaderPhotoLabelSlot() {
    ShowHeaderPhotoLabelSlot(userNameCard);
}

// 传递过来一个用户名片，显示用户名片。主要用在当点击聊天消息中的一条消息中的用户头像时，显示该用户的详细信息
void ChattingTeamWindow::ShowHeaderPhotoLabelSlot(const nim::UserNameCard &nameCard) {
    if (userInfoWidget == nullptr) {
        userInfoWidget = new UserInfoWidget(nameCard);
    }
    // 需要设置显示的名片信息
    userInfoWidget->setUserNameCard(nameCard);
    userInfoWidget->ShowNormal();
}

// 发送消息
void ChattingTeamWindow::sendMessageSlot() {

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
void ChattingTeamWindow::wheelEvent(QWheelEvent *event) {
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

bool ChattingTeamWindow::eventFilter(QObject *watched, QEvent *event) {
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

void ChattingTeamWindow::mousePressEvent(QMouseEvent *event) {
    if (headerWidget && headerWidget->contentsRect().contains(event->pos())) {
        pressPoint = event->globalPos();
        isMoving = true;
    }
    QWidget::mousePressEvent(event);
}

void ChattingTeamWindow::mouseMoveEvent(QMouseEvent *event) {
    if ((event->buttons() == Qt::LeftButton) && isMoving) {
        int dx = event->globalX() - pressPoint.x();
        int dy = event->globalY() - pressPoint.y();
        move(this->x() + dx, this->y() + dy);
        pressPoint = event->globalPos();
    }
    QWidget::mouseMoveEvent(event);
}

void ChattingTeamWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (isMoving) {
        isMoving = false;
    }
    QWidget::mouseReleaseEvent(event);
}

void ChattingTeamWindow::closeEvent(QCloseEvent *event) {
//    qDebug() << "ChattingTeamWindow : get close event...";
    emit closeChattingTeamWindowSignal(QString::fromStdString(sessionData.id_));    // MainWindow::CloseChattingTeamWindowSlot
//    event->ignore();
    QWidget::closeEvent(event);
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void ChattingTeamWindow::QueryMsg() {
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
void ChattingTeamWindow::QueryMsgOnline(int64_t from_time,
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

void ChattingTeamWindow::OnQueryMsgCallback(nim::NIMResCode res_code, const std::string &id,
                                        nim::NIMSessionType to_type, const nim::QueryMsglogResult &result) {
    //    qDebug() << __FILE__ << ":" << __LINE__ << " ==> res_code: " << res_code;
    //    qDebug() << __FILE__ << ":" << __LINE__ << " ==> id: " << QString::fromStdString(id);
    //    qDebug() << __FILE__ << ":" << __LINE__ << " ==> to_type: " << to_type;
    if (result.msglogs_.empty()) {
        hasMoreMessage = false;
        emit noMoreMessageSignal();     // 没有更多的聊天消息了,ChattingTeamWindow::noMoreMessageSlot
        return;
    }
    for (const auto &msg: result.msglogs_) {
        // 将消息添加进所有的消息列表中。
        // 这里消息的顺序是按时间逆序排列的，也就是说最新的一条消息在数组的第一条，最久远的消息在数组的最后一条
        chattingMsg.append(msg);
        if (msg.sender_accid_ == "hbk5") {
            qDebug() << "[info]: IMMessage: " << QString::fromStdString(result.msglogs_.front().ToJsonString(false));
        }
        //        qDebug() << "time: " << QDateTime::fromTime_t(msg.timetag_/1000)
        //                << ", content: " << QString::fromStdString(msg.content_);
    }
    emit updateMsgListWidgetSignal(result.msglogs_.size());     // ChattingTeamWindow::updateMsgListWidgetSlot
}

// 每次从云端获取完新的聊天消息时都更新聊天界面，将聊天消息插入到聊天界面中显示
void ChattingTeamWindow::updateMsgListWidgetSlot(int msgNumber) {
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
void ChattingTeamWindow::sendTextMsgToReceiver(const std::string &content, nim::IMMessage &message) {

    std::string msg_json = nim::Talk::CreateTextMessage(sessionData.id_, sessionData.type_,
                                                        nim::Tool::GetUuid(),
                                                        content,
                                                        nim::MessageSetting());
    nim::Talk::SendMsg(msg_json);
    // 构造一个消息对象
    message = std::move(nim::IMMessage(msg_json));
    message.timetag_ = QDateTime::currentDateTimeUtc().toTime_t();  // 秒数
    message.timetag_ *= 1000;       // 需要×1000转化为毫秒数
}

// 消息发送之后会有一个发送回调，通知发送的结果。该槽函数来自于信号RecentSessionWidget::sendMsgCallbackSignal
void ChattingTeamWindow::sendMsgCallbackSlot(const nim::SendMessageArc &messageArc) {
    if (messageArc.rescode_ == nim::kNIMResSuccess) {
        qDebug() << "[info]: 消息回执：消息发送成功...";
    } else {
        qDebug() << "[error]: 消息发送失败，code : " << messageArc.rescode_;
    }
}

// 当其他用户发送来新的消息后所有的聊天窗口界面都会收到该消息。该槽函数来自于信号RecentSessionWidget::receiveMsgSignal
void ChattingTeamWindow::receiveMsgSlot(const nim::IMMessage &msg) {
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
void ChattingTeamWindow::valueChangeSlot(int position) {
    currentTopIndex = position;
    if (position == verticalScrollBar->minimum() && !isQuerying && hasMoreMessage) {
        qDebug() << "[info]: 滑动到最顶端，需要加载更多记录 ...";
        QueryMsgOnline(0, chattingMsg.last().timetag_, chattingMsg.last().readonly_server_id_);
    }
}

// 当获取消息时，没有更多的聊天消息处理槽函数
void ChattingTeamWindow::noMoreMessageSlot() {
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
void ChattingTeamWindow::AddPromptTimeInfo(int64_t time, bool end) {

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
void ChattingTeamWindow::GetUserNameCard(const std::string &account) {
    std::list<std::string> account_list;
    account_list.push_back(account);
    nim::User::GetUserNameCard(account_list, [this](auto &&PH1) {
        OnGetUserCard(std::forward<decltype(PH1)>(PH1));
    });
}

void ChattingTeamWindow::GetUserNameCardOnLine(const std::string &account) {
    std::list<std::string> account_list;
    account_list.push_back(account);
    nim::User::GetUserNameCardOnline(account_list, [this](auto &&PH1) {
        OnGetUserCard(std::forward<decltype(PH1)>(PH1));
    });
}

void ChattingTeamWindow::OnGetUserCard(const std::list<nim::UserNameCard> &json_result) {
    if (json_result.empty()) {
        // 如果返回的查询数据为空，说明系统里不存在该用户，即查询的 accID 是错误的。
        // 这里强制设置用户名片 id 为会话 id，结束后续的不断查询。
        userNameCard.SetAccId(sessionData.id_);
    } else {
        userNameCard = json_result.front();
    }
    emit updateChattingTeamWindowSignal();      // ChattingTeamWindow::updateChattingTeamWindow
}
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////





