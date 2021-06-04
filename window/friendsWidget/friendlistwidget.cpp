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
    InitFriendList();               // 初始化好友列表
    ListenFriendListChange();       // 监听好友列表变化
}

FriendListWidget::~FriendListWidget() {

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
    connect(this, &FriendListWidget::UpdateFriendSignal, this, &FriendListWidget::UpdateFriendSignal);
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
void FriendListWidget::InitFriendList() {
    nim::Friend::GetList([this](auto && PH1, auto && PH2) {
        OnGetFriendList(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
    });
}

// 获取好友列表回调
void FriendListWidget::OnGetFriendList(nim::NIMResCode res_code, const std::list<nim::FriendProfile> &user_profile_list) {
    qDebug() << "[info]: 获取 " << user_profile_list.size() << " 个好友 ";
    QList<QString> accounts;
    for (auto & friendProfile: user_profile_list) {
        qDebug() << "[info]: FriendProfile: " << QString::fromStdString(friendProfile.ToJsonString());
        accounts.append(QString::fromStdString(friendProfile.GetAccId()));
        friendProfileMap.insert(QString::fromStdString(friendProfile.GetAccId()), friendProfile);       // 新增一条好友关系信息
    }
    GetUserNameCard(accounts);
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
    switch (change_event.type_)
    {
        case nim::kNIMFriendChangeTypeDel:
        {
            nim::FriendDelEvent delete_event;
            if(nim::Friend::ParseFriendDelEvent(change_event, delete_event)) {
                qDebug() << "解析删除成功...";
            }
            break;
        }
        case nim::kNIMFriendChangeTypeRequest:
        {
            qDebug() << "加好友/处理好友请求";
            // 别人加好友会在这里收到通知
            break;
        }
        case nim::kNIMFriendChangeTypeSyncList:
        {
            qDebug() << "好友列表同步与更新";
            // 登录完成之后，会访问云端好友关系，并在这里更新。可能更新后的结果与本地已有结果不同...
            break;
        }
        case nim::kNIMFriendChangeTypeUpdate:
        {
            qDebug() << "更新好友";
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
void FriendListWidget::GetUserNameCard(const QList<QString>& accounts) {
    std::list<std::string> account_list;
    qDebug() << accounts;
    for(const auto& account: accounts){
        account_list.push_back(account.toStdString());
    }
    nim::User::GetUserNameCard(account_list,[this](auto &&PH1) {
        OnGetUserCard(std::forward<decltype(PH1)>(PH1));
    });
}

// 获取服务器用户信息
void FriendListWidget::GetUserNameCardOnLine(const QList<QString>& accounts) {
    std::list<std::string> account_list;
    for(const auto& account: accounts){
        account_list.push_back(account.toStdString());
    }
    nim::User::GetUserNameCardOnline(account_list,[this](auto &&PH1) {
        OnGetUserCard(std::forward<decltype(PH1)>(PH1));
    });
}

//  获取用户信息回调
void FriendListWidget::OnGetUserCard(const std::list<nim::UserNameCard> &json_result) {
    // 如果查找的用户 accID 不存在，则还会有回调在这里，只不过不存在查询的这条用户 accID 的数据。
    qDebug() << "获取用户详细信息：" << json_result.size() << " 个";
    for(auto &info: json_result) {
//        qDebug() << QString::fromStdString(info.ToJsonString())
//                << ", icon: " << QString::fromStdString(info.GetIconUrl());
//        if (info.GetAccId() == "hbk5") {
//            qDebug() << "[info]: hbk5's UserNameCard: " << QString::fromStdString(info.ToJsonString());
//        }
        userNameCardMap.insert(QString::fromStdString(info.GetAccId()), info);      // 插入一条用户信息数据

        if(friendProfileMap.contains(QString::fromStdString(info.GetAccId()))) {
            // 如果该用户 accID在好友列表 friendProfileMap 中，则说明该用户是好友，则向好友列表中新增一个好友条目
            emit AddOneFriendSignal(info);      // 向好友列表中新增一个好友条目, FriendListWidget::AddOneFriendSlot
        }

    }
}

// 用户信息变化监听
void FriendListWidget::ListenUserNameCardChanged() {
    //向SDK注册监听用户名片变化
    nim::User::RegUserNameCardChangedCb([this](auto && PH1) {
                OnUserInfoChange(std::forward<decltype(PH1)>(PH1));
    });
}

// 用户信息变化监听回调
void FriendListWidget::OnUserInfoChange(const std::list<nim::UserNameCard> &info_list) {
    // TODO 用户信息变化，监听变化并修改
    for (auto& info : info_list)
    {
        //用户名或头像变化了
        if (info.ExistValue(nim::kUserNameCardKeyName)
            || info.ExistValue(nim::kUserNameCardKeyIconUrl)){

        }
        //用户其他信息变化了
        if (info.ExistValue(nim::kUserNameCardKeyAll) ||
                info.ExistValue(nim::kUserNameCardKeyName) ||
                info.ExistValue(nim::kUserNameCardKeyIconUrl)) {

        }

    }
}

// 修改用户信息资料
void FriendListWidget::UpdateMyUserNameCard(const nim::UserNameCard& userNameCard) {
    nim::User::UpdateMyUserNameCard(userNameCard, [this](auto && PH1) {
        OnUpdateMyInfo(std::forward<decltype(PH1)>(PH1));
    });
}

// 修改用户信息资料回调
void FriendListWidget::OnUpdateMyInfo(nim::NIMResCode res) {
    if(res == nim::kNIMResSuccess) {
        qDebug() << "资料修改成功！";
    }
}
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void FriendListWidget::AddOneFriendSlot(const nim::UserNameCard &userNameCard) {
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
    if(friendItemsMap.contains(accID)) {
        // 如果是该用户的好友，则需要更新好友列表的条目
        friendItemsMap[accID]->update(userNameCard);
    }
    userNameCardMap.insert(accID, userNameCard);
}


