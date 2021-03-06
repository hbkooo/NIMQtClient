#include "recentsessionwidget.h"

RecentSessionWidget::RecentSessionWidget(QListWidget *parent) : QListWidget(parent) {

    this->setObjectName("MsgFriItem");          // 为了使用listWidget.css中的一些鼠标选中和hover样式
    InitControl();

    connect(this, &RecentSessionWidget::AddOneSessionSignal, this, &RecentSessionWidget::AddSessionItem);
    connect(this, &RecentSessionWidget::UpdateSessionSignal, this, &RecentSessionWidget::UpdateSessionItem);

//    // 获取当前所有的最近会话列表
//    QueryAllRecentSession();
    // 监听最近会话状态的变化
    ListenRecentSessionChange();

}

void RecentSessionWidget::InitControl() {
    QFile css(":/css/listWidget");
    css.open(QFile::ReadOnly);
    this->setStyleSheet(css.readAll());
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);//水平滚动条关闭
    this->setFocusPolicy(Qt::NoFocus);      // 删除选中 某一个item是产生的虚线框
    this->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);   // 让内容连续地滚动，而不是整行整行的滚动
}

void RecentSessionWidget::InitSessionList() {
    // 获取当前所有的最近会话列表
    QueryAllRecentSession();
}

void RecentSessionWidget::UpdateSessionItem(const nim::SessionData &sessionData) {
    qDebug() << "[info]: session of '" << QString::fromStdString(sessionData.id_) << "' has changed!";
    //<< QString::fromStdString(nim::SessionData::ToJsonString(sessionData));

    for (int i = 0; i < this->count(); ++i) {
        auto *item = this->item(i);
        if (item->data(Qt::UserRole).toString().toStdString() == sessionData.id_) {

            if (i == 0) {
                // 如果已经在第一个了，则直接更新界面信息即可
                auto *sessionItem = dynamic_cast<SessionItem *>(this->itemWidget(item));
                sessionItem->setSessionData(sessionData);
                sessionItem->updateItem();
                return;
            }
            // 将item从ListWidget中取出，这时listWidget的数量会少一。
            // 取出item后，与item关联绑定的自定义widget也会调用析构函数，所以下面需要重新新建一个自定义的widget，重新将其与item绑定。
            item = takeItem(i);

            // 重新新建一个item对象
            auto *sessionItem = new SessionItem(sessionData);
            QString accID = QString::fromStdString(sessionData.id_);
            if(userNameCardMap.contains(accID)) {
                sessionItem->setUserNameCard(userNameCardMap[accID]);
            }
            if(friendProfileMap.contains(accID)) {
                sessionItem->setFriendProfile(friendProfileMap[accID]);
            }
            if(teamInfoMap.contains(accID)) {
                sessionItem->setTeamInfo(teamInfoMap[accID]);
            }
            sessionItem->updateItem();

            this->insertItem(0, item);
            this->setItemWidget(item, sessionItem);

            // 更新保存的所有 sessionItemMap 列表
            sessionItemMap.insert(QString::fromStdString(sessionData.id_), sessionItem);
            return;
        }
    }
}

/**
 * 新增一条最近会话 item
 * @param data 最近会话数据
 * @param row 插入的行数，如果是-1则插入到最后，否则插入到第 row 行
 */
void RecentSessionWidget::AddSessionItem(const nim::SessionData &data, int row) {
    qDebug() << "[info]: add one session of: " << QString::fromStdString(data.id_);
    //    if (data.id_ == "hbk5") {
    //        qDebug() << "[info]: SessionData: " << QString::fromStdString(nim::SessionData::ToJsonString(data));
    //    }
    auto *sessionItem = new SessionItem(data);
    QString accID = QString::fromStdString(data.id_);
    if(userNameCardMap.contains(accID)) {
        sessionItem->setUserNameCard(userNameCardMap[accID]);
    }
    if(friendProfileMap.contains(accID)) {
        sessionItem->setFriendProfile(friendProfileMap[accID]);
    }
    if(teamInfoMap.contains(accID)) {
        sessionItem->setTeamInfo(teamInfoMap[accID]);
    }
    sessionItem->updateItem();

    auto *listItem = new QListWidgetItem();
    // 必须设置，设置每一个条目显示的宽、高
    listItem->setSizeHint(QSize(350, sessionItem->size().height()));
    // 设置用户数据，即将item中保存该item对应的sessionID，便于以后更新item时查找到该item
    listItem->setData(Qt::UserRole, QString::fromStdString(data.id_));
    if(row == -1 || row >= count()) {
        this->addItem(listItem);
    } else {
        this->insertItem(row, listItem);
    }
    sessionItemMap.insert(QString::fromStdString(data.id_), sessionItem);

    this->setItemWidget(listItem, sessionItem);

}

// 删除列表中第row行的item消息
void RecentSessionWidget::removeOneItem(int row) {
    if (row >= count()) {
        qDebug() << "删除的行数:" << row << "大于已有的数目：" << count();
        return;
    }
    // 删除某一行，即删除某一个item.与之绑定的自定义widget并不会立即调用析构函数，应该是调用了deleteLater之后析构
    QListWidgetItem *item = takeItem(row);
    if (item != nullptr) {
        auto *msgItem = dynamic_cast<SessionItem *>(itemWidget(item));
//        qDebug() << "get messageItem ..., rest count is " << this->count();
        if (msgItem != nullptr)
            delete msgItem;
        sessionItemMap.remove(item->data(Qt::UserRole).toString());
    }
    delete item;

}

//鼠标双击事件
void RecentSessionWidget::mouseDoubleClickEvent(QMouseEvent *event) {

    QListWidgetItem *item = itemAt(event->pos());       // 获取点击的item
    if (item == nullptr) return;
    // 从item获取对应的自定义的widget
    auto *sessionItem = dynamic_cast<SessionItem *>(this->itemWidget(item));
    if (sessionItem == nullptr) return;
    auto sessionData = sessionItem->getSessionData();

    emit OpenChattingWindowSignal(sessionData);         // MainWindow::OpenChattingWindowFromRecentSessionSlot
    RestUnread(sessionData.id_, sessionData.type_);
}

void RecentSessionWidget::QueryAllRecentSession() {
    nim::Session::QueryAllRecentSessionAsync([this](auto &&PH1, auto &&PH2) {
        OnQuerySessionListCallback(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
    });
}

void RecentSessionWidget::OnQuerySessionListCallback(int unread_count, const nim::SessionDataList &session_list) {
    qDebug() << "===============================";
    qDebug() << "[info]: 最近会话一共有 " << session_list.sessions_.size() << " 条";
    auto sessions = session_list.sessions_;
    // 按时间降序排列
    sessions.sort([](const nim::SessionData &data1, const nim::SessionData &data2) {
        return data1.msg_timetag_ > data2.msg_timetag_;
    });
    for (auto &session_data: sessions) {
        //        qDebug() << "\n" << QString::fromStdString(nim::SessionData::ToJsonString(session_data));
        // 这里应该是id_,不是msg_sender_accid_
        // id_是会话id，不管这条消息是谁发送的，这个id就是该会话的accid。
        // msg_sender_accid_是这条消息的发送者accid，这个id可能是本地已经登录的用户，因为这条消息可能是本地用户发送给远程用户的。
        // eg. 本地登录用户hbk，正在与远程的用户hbk1聊天
        //      id_ = hbk1, msg_sender_accid_=hbk1  ==>     表示这条消息是hbk1发送给hbk的
        //      id_ = hbk1, msg_sender_accid_=hbk  ==>     表示这条消息是hbk发送给hbk1的
        //      所以不管谁发给谁，会话 id_ 都是相较于本地用户的远程用户的accid
        emit AddOneSessionSignal(session_data, -1);     // RecentSessionWidget::AddSessionItem
    }
    qDebug() << "===============================";
}

void RecentSessionWidget::ListenRecentSessionChange()
{
    nim::Session::RegChangeCb([this](auto &&PH1, auto &&PH2, auto &&PH3) {
        OnRecentSessionChangeCallback(std::forward<decltype(PH1)>(PH1),
                                      std::forward<decltype(PH2)>(PH2), std::forward<decltype(PH3)>(PH3));
    });
}

void RecentSessionWidget::OnRecentSessionChangeCallback(nim::NIMResCode resCode,
                                                        const nim::SessionData &sessionData, int total_unread_counts) {
    if (resCode == nim::kNIMResSuccess) {
        // 最近会话更新变动，有可能是之前的会话聊天信息变动，也有可能是有了新的好友聊天，产生了新的会话
        // 或者是创建了新的群，或者是有群消息
        if(sessionItemMap.contains(QString::fromStdString(sessionData.id_))) {
            // RecentSessionWidget::UpdateSessionItem 和 MainWindow::SessionChangToChattingWindowSlot
            emit UpdateSessionSignal(sessionData);
        } else {
            emit AddOneSessionSignal(sessionData, 0);       // RecentSessionWidget::AddSessionItem
        }
    }
}

void RecentSessionWidget::DeleteRecentSessionItem(const nim::SessionData &msg) {
    nim::Session::DeleteRecentSession(msg.type_, msg.id_, [this](auto &&PH1, auto &&PH2, auto &&PH3) {
        OnDeleteRecentSessionCallback(std::forward<decltype(PH1)>(PH1),
                                      std::forward<decltype(PH2)>(PH2),
                                      std::forward<decltype(PH3)>(PH3));
    });
}

void RecentSessionWidget::DeleteAllRecentSession() {
    nim::Session::DeleteAllRecentSession([this](auto &&PH1, auto &&PH2, auto &&PH3) {
        OnDeleteRecentSessionCallback(std::forward<decltype(PH1)>(PH1),
                                      std::forward<decltype(PH2)>(PH2),
                                      std::forward<decltype(PH3)>(PH3));
    });
}

void RecentSessionWidget::OnDeleteRecentSessionCallback(nim::NIMResCode code, const nim::SessionData &result,
                                                        int total_unread_counts) {
    qDebug() << "\ndelete session: " << QString::fromStdString(nim::SessionData::ToJsonString(result));
}

// 未读数清零
void RecentSessionWidget::RestUnread(const std::string &id, nim::NIMSessionType type) {
    nim::Session::SetUnreadCountZeroAsync(type, id, nim::Session::SetUnreadCountZeroCallback());
    nim::MsgLog::BatchStatusReadAsync(id, type, nim::MsgLog::BatchStatusReadCallback());
}

void RecentSessionWidget::InitUserNameCardMapSlot(const QMap<QString, nim::UserNameCard> &userNameMap) {
    qDebug() << "[info]: receive All user name card in " << __FUNCTION__ ;
    userNameCardMap = userNameMap;
}

void RecentSessionWidget::InitFriendProfileMapSlot(const QMap<QString, nim::FriendProfile> &friendProMap) {
    qDebug() << "[info]: receive All friend profile in " << __FUNCTION__ ;
    friendProfileMap = friendProMap;
}

// 更新最近会话中的该用户的条目
void RecentSessionWidget::UpdateUserNameCardSlot(const nim::UserNameCard &userNameCard) {
    QString accID = QString::fromStdString(userNameCard.GetAccId());
    userNameCardMap.insert(accID, userNameCard);
    if(sessionItemMap.contains(accID)) {

        qDebug() << "[info]: update recent user name card session of "
                    << accID << ". In " << __FUNCTION__ ;
        // 如果当前的会话列表里有该用户，则更新该会话条目的显示信息
        auto *session = sessionItemMap[accID];
        session->setUserNameCard(userNameCard);
        if(friendProfileMap.contains(accID)) {
            session->setFriendProfile(friendProfileMap[accID]);
        }
        session->updateItem();
    }
}

// 更新最近会话中的该用户的条目
void RecentSessionWidget::UpdateFriendProfileSlot(const nim::FriendProfile &friendProfile) {
    QString accID = QString::fromStdString(friendProfile.GetAccId());
    friendProfileMap.insert(accID, friendProfile);
    if(sessionItemMap.contains(accID)) {
        qDebug() << "[info]: update recent friend session of "
                    << QString::fromStdString(friendProfile.GetAccId()) << ". In " << __FUNCTION__ ;
        // 如果当前的会话列表里有该用户，则更新该会话条目的显示信息
        auto *session = sessionItemMap[accID];
        session->setFriendProfile(friendProfile);
        if(userNameCardMap.contains(accID)) {
            session->setUserNameCard(userNameCardMap[accID]);
        }
        session->updateItem();
    }
}

// 更新最近会话中的该群的条目
void RecentSessionWidget::UpdateTeamInfoSlot(const nim::TeamInfo &teamInfo) {
    // 在teamList中首先获取群消息也会发送到这里，因为在初始化的时候最近会话列表中并没有最近会话的群聊信息，
    // 所以这样最近会话列表中显示的群聊信息就只有群号（也是从session.id_中获取的）GetUserNameCardOnline，并没有群的名称等信息。
    // qDebug() << "[info]: receive update team info in " << __FUNCTION__ ;
    // TODO
    QString teamID = QString::fromStdString(teamInfo.GetTeamID());
    teamInfoMap.insert(teamID, teamInfo);
    if(sessionItemMap.contains(teamID)) {
        qDebug() << "[info]: update recent team session of "
                    << QString::fromStdString(teamInfo.GetName()) << ". In " << __FUNCTION__ ;
        // 如果当前的会话列表里有该用户，则更新该会话条目的显示信息
        auto *session = sessionItemMap[teamID];
        session->setTeamInfo(teamInfo);
        session->updateItem();
    }
}







