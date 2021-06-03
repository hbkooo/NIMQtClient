//
// Created by 19216 on 2021/5/31.
//

#include "chattingwindow.h"

ChattingWindow::ChattingWindow(const nim::SessionData &data, QWidget *parent) :
        sessionData(data), QWidget(parent) {
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

}

ChattingWindow::~ChattingWindow() {

}

void ChattingWindow::InitHeader() {

    headerPhotoLabel = new QLabel("头像");
    headerPhotoLabel->setFixedSize(48, 48);
    QPixmap map(":/default_header/dh1");
    headerPhotoLabel->setPixmap(PixmapToRound(map.scaled(headerPhotoLabel->size()), 24));

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
    connect(sendButton, &QPushButton::clicked, this, &ChattingWindow::sendMessageSlot);
    connect(this, &ChattingWindow::updateMsgListWidgetSignal, this, &ChattingWindow::updateMsgListWidgetSlot);
    connect(verticalScrollBar, &QScrollBar::valueChanged, this, &ChattingWindow::valueChangeSlot);
    connect(this, &ChattingWindow::noMoreMessageSignal, this, &ChattingWindow::noMoreMessageSlot);
}

/**
 * 在消息列表头部插入一条消息
 * @param msg 消息
 * @param extIndex msg 消息在全部消息列表 chattingMsg 中的序号，扩展位，可以不使用
 */
void ChattingWindow::AddOneMsgFront(const nim::IMMessage &msg, int extIndex) {
    bool isRight;
    if(msg.sender_accid_.empty()) {
        // 从msg_json构造的 IMMessage 消息发送者为空；所以可以知道是用户点击发送发送的消息
        isRight = true;
    } else {
        // 有发送者id，则判断发送者id和当前的聊天窗口id是否一致，如果不一致则说明消息在右边，是自己发送的；
        // 如果一致则说明消息在左边，是好友发送给自己的消息
        isRight = (msg.sender_accid_!=sessionData.id_);
    }

    // 首先插入聊天消息
    auto *item = new ChattingItem(sessionData.id_ != msg.sender_accid_);
    item->updateContent(msg);
    auto *listItem = new QListWidgetItem();
    listItem->setSizeHint(QSize(0, item->sizeHint().height()));
    chattingListWidget->insertItem(0, listItem);
    chattingListWidget->setItemWidget(listItem, item);
//    chattingListWidget->scrollToItem(listItem);

    if (extIndex != -1) {
        if(chattingMsg.size() == extIndex+1) {
            // 最后一条消息，则一定添加时间提示
            AddPromptTimeInfo(msg.timetag_, false);
        } else {
            // 不是最后一条消息，需要判断当前消息与下一条消息之间的时间差。
            // 这里的下一条是指在 chattingMsg 的列表中存储的下一条。
            if(IsInsertTimePromptInfo(msg.timetag_, chattingMsg[extIndex+1].timetag_)) {
                AddPromptTimeInfo(msg.timetag_, false);
            }
        }
    }

}

// 在消息列表尾部插入一条消息
void ChattingWindow::AddOneMsgEnd(const nim::IMMessage &msg) {
    bool isRight;
    if(msg.sender_accid_.empty()) {
        // 从msg_json构造的 IMMessage 消息发送者为空；所以可以知道是用户点击发送发送的消息
        isRight = true;
    } else {
        // 有发送者id，则判断发送者id和当前的聊天窗口id是否一致，如果不一致则说明消息在右边，是自己发送的；
        // 如果一致则说明消息在左边，是好友发送给自己的消息
        isRight = (msg.sender_accid_!=sessionData.id_);
    }

    // 判断插入时间提示信息
    if(chattingListWidget->count() == 0) {
        // 第一条消息，则直接插入时间
        AddPromptTimeInfo(msg.timetag_);
    } else {
        auto *lastItem = chattingListWidget->item(chattingListWidget->count()-1);
        auto *lastChattingItem = dynamic_cast<ChattingItem*>(chattingListWidget->itemWidget(lastItem));
        if(IsInsertTimePromptInfo(msg.timetag_, lastChattingItem->getIMMessage().timetag_)) {
            // 此消息与上一条记录消息相差5分钟之多，需要插入此消息的时间提示
            AddPromptTimeInfo(msg.timetag_);
        }
    }

    // 插入具体的聊天消息
    auto *item = new ChattingItem(sessionData.id_ != msg.sender_accid_);
    item->updateContent(msg);
    auto *listItem = new QListWidgetItem();
    listItem->setSizeHint(QSize(0, item->sizeHint().height()));
    chattingListWidget->addItem(listItem);
    chattingListWidget->setItemWidget(listItem, item);
    chattingListWidget->scrollToItem(listItem);
}

// 发送消息
void ChattingWindow::sendMessageSlot() {

    QString msg = messageTextEdit->toPlainText();
    if(msg == "") {
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
        if(chattingMsg.empty()) {
            QueryMsgOnline();
        } else {
            QueryMsgOnline(0, chattingMsg.last().timetag_, chattingMsg.last().readonly_server_id_);
        }
    }
    QWidget::wheelEvent(event);
}

bool ChattingWindow::eventFilter(QObject *watched, QEvent *event) {
    if (watched == messageTextEdit) {
        if(event->type() == QEvent::KeyPress) {
            auto *k = dynamic_cast<QKeyEvent*>(event);
            if(k->key() == Qt::Key_Enter || k->key() == Qt::Key_Return) {
                if(k->modifiers() & Qt::ControlModifier) {
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
    if((event->buttons() == Qt::LeftButton) && isMoving) {
        int dx = event->globalX() - pressPoint.x();
        int dy = event->globalY() - pressPoint.y();
        move(this->x()+dx,this->y()+dy);
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
    emit closeChattingWindowSignal(QString::fromStdString(sessionData.id_));    // MainWindow::CloseChattingWindowSlot
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

void ChattingWindow::OnQueryMsgCallback(nim::NIMResCode res_code, const std::string& id,
                                        nim::NIMSessionType to_type, const nim::QueryMsglogResult& result) {
    //    qDebug() << __FILE__ << ":" << __LINE__ << " ==> res_code: " << res_code;
    //    qDebug() << __FILE__ << ":" << __LINE__ << " ==> id: " << QString::fromStdString(id);
    //    qDebug() << __FILE__ << ":" << __LINE__ << " ==> to_type: " << to_type;
    if (result.msglogs_.empty()){
        hasMoreMessage = false;
        emit noMoreMessageSignal();     // 没有更多的聊天消息了
        return;
    }
    //    qDebug() << "\nmsg: " << QString::fromStdString(result.msglogs_.front().ToJsonString(false));
    for(const auto& msg: result.msglogs_) {
        // 将消息添加进所有的消息列表中。
        // 这里消息的顺序是按时间逆序排列的，也就是说最新的一条消息在数组的第一条，最久远的消息在数组的最后一条
        chattingMsg.append(msg);
        //        qDebug() << "time: " << QDateTime::fromTime_t(msg.timetag_/1000)
        //                << ", content: " << QString::fromStdString(msg.content_);
    }
    emit updateMsgListWidgetSignal(result.msglogs_.size());
}

// 每次从云端获取完新的聊天消息时都更新聊天界面，将聊天消息插入到聊天界面中显示
void ChattingWindow::updateMsgListWidgetSlot(int msgNumber) {
    qDebug() << "[info]: get " << msgNumber << " messages ...";
    for(int i = chattingMsg.size() - msgNumber; i < chattingMsg.size(); ++i) {
        const auto &msg = chattingMsg.at(i);
        AddOneMsgFront(msg, i);
    }
    if(chattingMsg.size() == msgNumber){
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
}

// 消息发送之后会有一个发送回调，通知发送的结果。该槽函数来自于信号RecentSessionWidget::sendMsgCallbackSignal
void ChattingWindow::sendMsgCallbackSlot(const nim::SendMessageArc& messageArc) {
    if(messageArc.rescode_ == nim::kNIMResSuccess) {
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
    if(msg.feature_ == nim::kNIMMessageFeatureDefault) {
        qDebug() << "\n[info]: 收到默认消息：" << QString::fromStdString(msg.ToJsonString(true));

    } else if(msg.feature_ == nim::kNIMMessageFeatureSyncMsg
              || msg.feature_ == nim::kNIMMessageFeatureRoamMsg) {
        qDebug() << "\n[info]: 收到同步或漫游消息：" << QString::fromStdString(msg.ToJsonString(true));

    } else if(msg.feature_ == nim::kNIMMessageFeatureCustomizedMsg) {
        qDebug() << "\n[info]: 收到透传消息：" << QString::fromStdString(msg.ToJsonString(true));

    } else if(msg.feature_ == nim::kNIMMessageFeatureLeaveMsg) {
        qDebug() << "\n[info]: 收到离线消息：" << QString::fromStdString(msg.ToJsonString(true));
    }
}

// 当聊天消息ListWidget滑动时触发滑动到的位置信息。以此来处理滑动到到最顶端的时候加载更多的聊天信息
void ChattingWindow::valueChangeSlot(int position) {
    currentTopIndex = position;
    if(position == verticalScrollBar->minimum() && !isQuerying && hasMoreMessage) {
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
    listItem->setData(Qt::UserRole, "timeInfo");        // 添加一个标记，区分是消息还是提示时间
    listItem->setSizeHint(QSize(0, label->sizeHint().height()));
    if(end) {
        chattingListWidget->addItem(listItem);
    } else {
        chattingListWidget->insertItem(0, listItem);
    }
    chattingListWidget->setItemWidget(listItem, label);
}



