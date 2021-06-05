#include "sessionitem.h"

#include <QBitmap>
#include <QPainter>
#include <utility>


SessionItem::SessionItem(nim::SessionData data, QWidget *parent)
    :sessionData(std::move(data)) ,QWidget(parent)
{
    // 默认构造的用户好友关系中，accID为空，设置为非好友关系。用户调用 set 方法后可以获得该属性的值。
    friendProfile.SetAccId("");
    friendProfile.SetRelationship(nim::kNIMFriendFlagNotFriend);
    // 默认设置的用户信息的 accID 为空。用户调用 set 方法后可以获得该属性的值。
    userNameCard.SetAccId("");

    InitControl();
    SetLayout();
    SetConnect();

    this->setFixedHeight(68);               // 头像高48 + 上边界10 + 下边界10
    this->setStyleSheet("background:transparent;"); //只有设置了透明背景之后在hover的时候背景才可以看到，不然该item中的控件背景还是白色的

}

void SessionItem::InitControl() {

    // 用户头像
    header_label = new QLabel("头像");
    header_label->setFixedSize(48, 48);
    QPixmap map(":/default_header/dh1");
    map = PixmapToRound(map.scaled(header_label->size()), 24);
    header_label->setPixmap(map);

    // 创建用户姓名标签
    name_label = new QLabel("用户名字");
    name_label->setStyleSheet("font-size:20px;");
    name_label->adjustSize();
    name_label->setText(QString::fromStdString(sessionData.id_));

    // 创建最后一条聊天消息标签
    last_msg_label = new QLabel("最后一条消息");
    last_msg_label->setStyleSheet("font-size:14px;"
                                  "color:#6f6a6d");
    last_msg_label->setFixedHeight(14);
    last_msg_label->setText(QString::fromStdString(sessionData.msg_content_));

    // 创建最后一条聊天消息的聊天时间
    date_time_label = new QLabel("聊天时间");
    date_time_label->adjustSize();      // 自适应文本的大小
    date_time_label->setStyleSheet("font-size:14px;"
                                   "color:#6f6a6d");
    date_time_label->setText(FormatTimeInRecentSession(sessionData.msg_timetag_));

}

void SessionItem::SetLayout() {
    // 一个水平布局包括用户名和时间
    auto *name_time_layout = new QHBoxLayout();
    name_time_layout->setSpacing(0);
    name_time_layout->setMargin(0);
    name_time_layout->setContentsMargins(0, 0, 0, 0);
    name_time_layout->addWidget(name_label);
    name_time_layout->addStretch();
    name_time_layout->addSpacing(8);
    name_time_layout->addWidget(date_time_label);

    // 一个竖直布局包括上面的用户名时间布局和下面的最后一条消息控件
    auto *name_msg_time_layout = new QVBoxLayout();
    name_msg_time_layout->setSpacing(0);
    name_msg_time_layout->setMargin(0);
    name_msg_time_layout->setContentsMargins(0, 0, 0, 0);
    name_msg_time_layout->addStretch();
    name_msg_time_layout->addLayout(name_time_layout);
    name_msg_time_layout->addSpacing(6);
    name_msg_time_layout->addWidget(last_msg_label);
    name_msg_time_layout->addStretch();

    // 最终的主布局包括左边的用户头像和上面的剩下的布局
    main_layout = new QHBoxLayout();
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->setMargin(0);
    main_layout->addSpacing(16);
    main_layout->addWidget(header_label, 0, Qt::AlignVCenter);
    main_layout->addSpacing(8);
    main_layout->addLayout(name_msg_time_layout);
    main_layout->addSpacing(16);

    setLayout(main_layout);
}

void SessionItem::SetConnect() const {
    connect(this, &SessionItem::updateItemSignal, this, &SessionItem::updateItem);
}

SessionItem::~SessionItem() {
    qDebug() << "[info]: In ~SessionItem, delete session id is " << QString::fromStdString(sessionData.id_);
}

// 更新这条 item 显示的信息
void SessionItem::updateItem() {

    // 最新一条聊天消息和时间都可以从 SessionData 中获取，所以可以直接设置
    // 更新最后一条消息信息
    last_msg_label->setText(QString::fromStdString(sessionData.msg_content_));
    // 更新最后一条消息的时间
    date_time_label->setText(FormatTimeInRecentSession(sessionData.msg_timetag_));

    // 下面需要更新会话显示的头像和用户名，这两个信息根据会话聊天类型不同存储的位置也不同
    if(sessionData.type_ == nim::kNIMSessionTypeP2P) {
        // P2P的点对点双用户聊天会话
        if(userNameCard.GetAccId().empty() || userNameCard.GetAccId() != sessionData.id_) {
            // 用户信息的 accID 为空，说明没有调用 set 方法，需要重新获取该聊天用户的信息。
            // 或者用户信息的名片 accID 与会话数据的 id 不一样，说明该 userNameCard 与该会话数据不一样，所以需要重新获取该会话用户的信息。
            // 获取用户信息，然后再更新界面信息。
            GetUserNameCard(sessionData.id_);
            qDebug() << "userNameCard " << QString::fromStdString(sessionData.id_) << " 无效，重新获取 ...";
            return;
        }

        // 用户名片信息有效，首先使用该名片信息更新界面数据
        QString name = QString::fromStdString(userNameCard.GetName());
        if (name != "") {
            // 用户昵称不为空
            name_label->setText(name);
        } else {
            // 用户昵称为空，则用户名设置为用户的 accID
            name_label->setText(QString::fromStdString(userNameCard.GetAccId()));
        }

        // 不论二者是否为好友关系，聊天窗口的头像是一样的。所以现在即可更新聊天窗口的头像
        updateHeaderPhotoIcon();

        // 判断二者是否为好友关系。如果是好友关系则会话用户名设置为好友关系里设置的备注
        if(friendProfile.GetRelationship() == nim::kNIMFriendFlagNormal) {
            // 如果是好友关系
            QString alias = QString::fromStdString(friendProfile.GetAlias());
            if(alias != "") {
                // 备注不为空，则直接设置为备注信息
                name_label->setText(alias);
            }
        }
    } else if(sessionData.type_ == nim::kNIMSessionTypeTeam) {
        // 群组聊天
        // TODO

    } else {
        // 超大群组聊天
        // TODO
    }

}


// 更新聊天窗口的头像图标
void SessionItem::updateHeaderPhotoIcon() {
    if (userNameCard.GetIconUrl().empty()) {
        userNameCard.SetIconUrl(":/default_header/dh1");
    }
    QPixmap map(QString::fromStdString(userNameCard.GetIconUrl()));
    if (map.isNull()) {
        // 头像加载失败
        map.load(":/default_header/dh1");
    }
    header_label->setPixmap(PixmapToRound(map.scaled(header_label->size()), header_label->height()/2));
}


//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////根据用户 id 查询用户详细信息 ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
void SessionItem::GetUserNameCard(const std::string & account) {
    std::list<std::string> account_list;
    account_list.push_back(account);
    nim::User::GetUserNameCard(account_list,[this](auto &&PH1) {
        OnGetUserCard(std::forward<decltype(PH1)>(PH1));
    });
}

void SessionItem::GetUserNameCardOnLine(const std::string & account) {
    std::list<std::string> account_list;
    account_list.push_back(account);
    nim::User::GetUserNameCardOnline(account_list,[this](auto &&PH1) {
        OnGetUserCard(std::forward<decltype(PH1)>(PH1));
    });
}

void SessionItem::OnGetUserCard(const std::list<nim::UserNameCard> &json_result) {
    if(json_result.empty()) {
        // 如果返回的查询数据为空，说明系统里不存在该用户，即查询的 accID 是错误的。
        // 这里强制设置用户名片 id 为会话 id，结束后续的不断查询。
        userNameCard.SetAccId(sessionData.id_);
    } else {
        userNameCard = json_result.front();
    }
    emit updateItem();      // SessionItem::updateItem
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////



