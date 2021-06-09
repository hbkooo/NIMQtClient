//
// Created by 19216 on 2021/5/30.
//

// You may need to build the project (run Qt uic code generator) to get "ui_FriendListWidget.h" resolved

#include "friendlistwidget.h"

FriendListWidget::FriendListWidget(QListWidget *parent) :
        QListWidget(parent) {

    this->setObjectName("MsgFriItem");      // 为了使用listWidget.css中的一些鼠标选中和hover样式
    InitControl();
    SetConnect();
    ListenFriendListChange();       // 监听好友列表变化
    ListenUserNameCardChanged();    // 监听用户信息变化
}

FriendListWidget::~FriendListWidget() {

}

// 该方法在外部调用，初始化好友列表
void FriendListWidget::InitFriendList() {
    GetFriendList();               // 初始化好友列表
}

void FriendListWidget::InitControl() {
    QFile css(":/css/listWidget");
    css.open(QFile::ReadOnly);
    this->setStyleSheet(css.readAll());
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);//水平滚动条关闭
    this->setFocusPolicy(Qt::NoFocus);      // 删除选中 某一个item是产生的虚线框
    this->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);   // 让内容连续地滚动，而不是整行整行的滚动
}

void FriendListWidget::SetConnect() {
    connect(this, &FriendListWidget::AddOneFriendSignal, this, &FriendListWidget::AddOneFriendSlot);
    connect(this, &FriendListWidget::UpdateUserNameCardSignal,
            this, &FriendListWidget::UpdateUserNameCardSlot);
    connect(this, &FriendListWidget::UpdateFriendProfileSignal,
            this, &FriendListWidget::UpdateFriendProfileSlot);
}

void FriendListWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    auto index = currentIndex();    // 获取当前点击的item对应的index

    QListWidgetItem *item = itemAt(event->pos());       // 获取点击的item
    if (item == nullptr) return;
    // 从item获取对应的自定义的widget
    auto *friendItem = dynamic_cast<FriendItem *>(this->itemWidget(item));
    if (friendItem == nullptr) return;
    emit OpenChattingWindowSignal(friendItem->getUserNameCard());
//    auto sessionData = messageItem->getSessionData();
//    auto *chattingWindow = new ChattingWindow(sessionData);
    // 将最近发送的消息成功与否信号传递到聊天窗口中
//    connect(this, &RecentSessionWidget::sendMsgCallbackSignal, chattingWindow, &ChattingWindow::sendMsgCallbackSlot);
    // 当其他用户发送来新的消息后所有的聊天窗口界面都会收到该消息。
//    connect(this, &RecentSessionWidget::receiveMsgSignal, chattingWindow, &ChattingWindow::receiveMsgSlot);
//    chattingWindow->show();
//    RestUnread(sessionData.id_, sessionData.type_);
    QAbstractItemView::mouseDoubleClickEvent(event);
}

//////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// 好友列表操作 ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
// 获取好友列表。这里是直接获取本地的好友列表。
void FriendListWidget::GetFriendList() {
    nim::Friend::GetList([this](auto &&PH1, auto &&PH2) {
        OnGetFriendList(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
    });
}

// 获取好友列表回调
void FriendListWidget::OnGetFriendList(nim::NIMResCode res_code,
                                       const std::list<nim::FriendProfile> &user_profile_list) {
    qDebug() << "===============================";
    qDebug() << "[info]: 获取 " << user_profile_list.size() << " 个好友 ";
    QList<QString> accounts;
    for (auto &friendProfile: user_profile_list) {
        //        qDebug() << "[info]: FriendProfile: " << QString::fromStdString(friendProfile.ToJsonString());
        accounts.append(QString::fromStdString(friendProfile.GetAccId()));
        // 新增一条好友关系信息
        friendProfileMap.insert(QString::fromStdString(friendProfile.GetAccId()), friendProfile);
    }
    // 将好友列表数据发送给最近会话控件中。RecentSessionWidget::InitFriendProfileMapSlot
    emit InitFriendProfileMapSignal(friendProfileMap);
    // 在初始化好友列表之后，获取好友的用户信息可以直接调用 GetUserNameCard 查询本地用户即可。
    GetUserNameCard(accounts);
    // 这个是查询服务器同步好友数据，用在好友关系监听中，当有好友添加、或者好友列表同步与更新时调用这个获取在线好友信息
    // GetUserNameCardOnLine(accounts);
    qDebug() << "===============================";
}

// 好友列表变化监听
void FriendListWidget::ListenFriendListChange() {
    //向SDK注册监听好友列表变化
    nim::Friend::RegChangeCb([this](auto &&PH1) {
        OnFriendListChange(std::forward<decltype(PH1)>(PH1));
    });
}

// 好友列表变化回调
void FriendListWidget::OnFriendListChange(const nim::FriendChangeEvent &change_event) {
    // TODO 实现具体的好友列表变化
    // TODO 用户信息变化，监听变化并修改.。需要通知修改最近会话列表和打开的聊天窗口
    switch (change_event.type_) {
        case nim::kNIMFriendChangeTypeDel: {
            nim::FriendDelEvent delete_event;
            if (nim::Friend::ParseFriendDelEvent(change_event, delete_event)) {
                qDebug() << "解析 删除 成功: " << QString::fromStdString(delete_event.accid_);
                // 删除成功，发送删除好友成功的信号
                emit DeleteFriendSuccessSignal(QString::fromStdString(delete_event.accid_));
            } else {
                qDebug() << "解析 删除 失败...";
            }
            break;
        }
        case nim::kNIMFriendChangeTypeRequest: {
            // qDebug() << "加好友/处理好友请求";
            // 别人加好友会在这里收到通知
            nim::FriendAddEvent addEvent;
            if(nim::Friend::ParseFriendAddEvent(change_event, addEvent)) {
                qDebug() << "解析 添加好友 成功: "
                        << "add accID: " << QString::fromStdString(addEvent.accid_);
                nim::FriendProfile profile(addEvent.accid_);
                profile.SetRelationship(nim::kNIMFriendFlagNormal);
                friendProfileMap.insert(QString::fromStdString(profile.GetAccId()), profile);
                // 获取用户好友名片并添加到好友列表中。需要在线获取好友信息
                // 这个是查询服务器同步好友数据，用在好友关系监听中，当有好友添加、或者好友列表同步与更新时调用这个获取在线好友信息
                GetUserNameCardOnLine({QString::fromStdString(profile.GetAccId())});
            } else {
                qDebug() << "解析 添加好友 失败...";
            }
            break;
        }
        case nim::kNIMFriendChangeTypeSyncList: {
            qDebug() << "好友列表同步与更新";
            // 登录完成之后，会访问云端好友关系，并在这里更新。可能更新后的结果与本地已有结果不同...
            nim::FriendProfileSyncEvent profileSyncEvent;
            if(nim::Friend::ParseFriendProfileSyncEvent(change_event, profileSyncEvent)) {
                qDebug() << "解析 好友列表同步与更新 成功...";
                QList<QString> accountIncreased;
                for(const auto &profile: profileSyncEvent.profiles_) {
                    auto accID = QString::fromStdString(profile.GetAccId());
                    friendProfileMap.insert(accID, profile);
                    if(userNameCardMap.contains(accID)) {
                        // 好友列表里没有新增的这些好友名片，所以需要重新获取好友名片后续并会自动考虑是否新增到好友列表中
                        accountIncreased.append(accID);
                    }
                }
                // 这个是查询服务器同步好友数据，用在好友关系监听中，当有好友添加、或者好友列表同步与更新时调用这个获取在线好友信息
                // 获取同步更新来的好友中本地没有的好友关系的好友名片，并新增到好友列表中。需要在线获取好友信息
                GetUserNameCardOnLine(accountIncreased);
                // GetUserNameCard(accountIncreased);   // 不可调用这个方法，这个方法无法在线获取好友信息，会查询不到好友
            } else {
                qDebug() << "解析 好友列表同步与更新 失败...";
            }
            break;
        }
        case nim::kNIMFriendChangeTypeUpdate: {
            qDebug() << "更新好友";
            nim::FriendProfileUpdateEvent friendProfileUpdateEvent;
            if(nim::Friend::ParseFriendProfileUpdateEvent(change_event, friendProfileUpdateEvent)) {
                qDebug() << "解析 更新好友 成功...";
                const auto &profile = friendProfileUpdateEvent.profile_;
                friendProfileMap.insert(QString::fromStdString(profile.GetAccId()), profile);
                // 更新好友关系并不需要重新获取好友的用户信息
            } else {
                qDebug() << "解析 更新好友 失败...";
            }
            break;
        }
        default:
            break;
    }
}
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////根据用户 id 查询用户详细信息 ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
// 获取本地用户信息
void FriendListWidget::GetUserNameCard(const QList<QString> &accounts) {
    std::list<std::string> account_list;
    qDebug() << accounts;
    for (const auto &account: accounts) {
        account_list.push_back(account.toStdString());
    }
    nim::User::GetUserNameCard(account_list, [this](auto &&PH1) {
        OnGetUserCard(std::forward<decltype(PH1)>(PH1));
    });
}

// 获取服务器用户信息
void FriendListWidget::GetUserNameCardOnLine(const QList<QString> &accounts) {
    std::list<std::string> account_list;
    for (const auto &account: accounts) {
        account_list.push_back(account.toStdString());
    }
    nim::User::GetUserNameCardOnline(account_list, [this](auto &&PH1) {
        OnGetUserCard(std::forward<decltype(PH1)>(PH1));
    });
}

//  获取用户信息回调
void FriendListWidget::OnGetUserCard(const std::list<nim::UserNameCard> &json_result) {
    // 如果查找的用户 accID 不存在，则还会有回调在这里，只不过不存在查询的这条用户 accID 的数据。
    qDebug() << "获取用户详细信息：" << json_result.size() << " 个";
    for (auto &info: json_result) {
        userNameCardMap.insert(QString::fromStdString(info.GetAccId()), info);      // 插入一条用户信息数据
        if(!friendItemsMap.contains(QString::fromStdString(info.GetAccId()))
            && friendProfileMap.contains(QString::fromStdString(info.GetAccId()))) {
            // 如果好友列表里不存在该用户，并且该用户 accID 在好友列表 friendProfileMap 中，
            // 则说明该用户是好友，则向好友列表中新增一个好友条目
            emit AddOneFriendSignal(info);      // 向好友列表中新增一个好友条目, FriendListWidget::AddOneFriendSlot
        }
        // RecentSessionWidget::UpdateUserNameCardSlot.使用一条一条的发送
        // FriendListWidget::UpdateUserNameCardSlot
        emit UpdateUserNameCardSignal(info);
    }
    // 将所有的用户信息数据发送给最近会话控件中。RecentSessionWidget::InitUserNameCardMapSlot
    // 不使用发送全部的map数据。因为如果在这里又有其他请求用户名片的操作，则最近会话控件里的map会被这个map所替换
    // emit InitUserNameCardMapSignal(userNameCardMap);
}

// 用户信息变化监听
void FriendListWidget::ListenUserNameCardChanged() {
    //向SDK注册监听用户名片变化
    nim::User::RegUserNameCardChangedCb([this](auto &&PH1) {
        OnUserInfoChange(std::forward<decltype(PH1)>(PH1));
    });
}

// 用户信息变化监听回调
void FriendListWidget::OnUserInfoChange(const std::list<nim::UserNameCard> &info_list) {
    // TODO 用户信息变化，监听变化并修改.。需要通知修改最近会话列表和打开的聊天窗口

    for (auto &info : info_list) {
        //用户名或头像变化了
        qDebug() << "[info]: user " <<  QString::fromStdString(info.GetAccId()) << " changed ...";
        // 发送信号，将修改的用户信息发送出去.
        // RecentSessionWidget::UpdateUserNameCardSlot  FriendListWidget::UpdateUserNameCardSlot
        emit UpdateUserNameCardSignal(info);

        //        if (info.ExistValue(nim::kUserNameCardKeyName)
        //            || info.ExistValue(nim::kUserNameCardKeyIconUrl)) {
        //
        //        }
        //        //用户其他信息变化了
        //        if (info.ExistValue(nim::kUserNameCardKeyAll) ||
        //            info.ExistValue(nim::kUserNameCardKeyName) ||
        //            info.ExistValue(nim::kUserNameCardKeyIconUrl)) {
        //
        //        }

    }
}

// 修改用户信息资料
void FriendListWidget::UpdateMyUserNameCard(const nim::UserNameCard &userNameCard) {
    nim::User::UpdateMyUserNameCard(userNameCard, [this](auto &&PH1) {
        OnUpdateMyInfo(std::forward<decltype(PH1)>(PH1));
    });
}

// 修改用户信息资料回调
void FriendListWidget::OnUpdateMyInfo(nim::NIMResCode res) {
    if (res == nim::kNIMResSuccess) {
        qDebug() << "资料修改成功！";
    }
}
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void FriendListWidget::AddOneFriendSlot(const nim::UserNameCard &userNameCard) {
    if(friendItemsMap.contains(QString::fromStdString(userNameCard.GetAccId()))) {
        return;
    }
    auto *friendItem = new FriendItem(userNameCard);

    friendItemsMap.insert(QString::fromStdString(userNameCard.GetAccId()), friendItem);
    auto *listItem = new QListWidgetItem();
    // 必须设置，设置每一个条目显示的宽、高
    listItem->setSizeHint(QSize(350, friendItem->size().height()));
    // 设置用户数据，即将item中保存该item对应的sessionID，便于以后更新item时查找到该item
    listItem->setData(Qt::UserRole, QString::fromStdString(userNameCard.GetAccId()));
    this->addItem(listItem);
    this->setItemWidget(listItem, friendItem);
}

// 更新用户信息
void FriendListWidget::UpdateUserNameCardSlot(const nim::UserNameCard &userNameCard) {
    // TODO 用户信息变更
    // 好友信息更新变化通知处理
    auto accID = QString::fromStdString(userNameCard.GetAccId());
    if (friendItemsMap.contains(accID)) {
        // 如果是该用户的好友，则需要更新好友列表的条目
        friendItemsMap[accID]->update(userNameCard);
    }
    userNameCardMap.insert(accID, userNameCard);
}

// 更新好友条目的槽函数
void FriendListWidget::UpdateFriendProfileSlot(const nim::FriendProfile &friendProfile) {

}



