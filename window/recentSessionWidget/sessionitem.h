#ifndef MESSAGEITEM_H
#define MESSAGEITEM_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QDateTime>
#include <QDebug>

#include <client.h>
#include "util/util.h"

/**
 * @brief The SessionItem class
 * 自定义的控件，即列表中每一个item的内容
 */

class SessionItem: public QWidget
{
    Q_OBJECT

public:
    explicit SessionItem(nim::SessionData data, QWidget *parent=nullptr);
    ~SessionItem() override;

    const nim::SessionData& getSessionData() const {return sessionData;}

    void setSessionData(const nim::SessionData &data) { sessionData = data; }
    void setFriendProfile(const nim::FriendProfile &profile) { friendProfile = profile; }
    void setUserNameCard(const nim::UserNameCard &nameCard) { userNameCard = nameCard; }
    // 更新该条目的显示信息。一般是调用好上面的三个set方法之后然后调用该方法，更新头控件数据
    void updateItem();

private:
    // 初始化控件
    void InitControl();
    void SetLayout();
    void SetConnect() const;
    // 更新聊天窗口的头像图标
    void updateHeaderPhotoIcon();

private:

    // 该条目显示的信息
    nim::SessionData sessionData;       // 该条目的会话数据
    nim::FriendProfile friendProfile;   // 该条目与登录的用户之间的好友关系
    nim::UserNameCard userNameCard;     // 该条目用户的名片信息

    QLabel *header_label = nullptr;         // 用户头像
    QLabel *name_label = nullptr;           // 用户姓名标签
    QLabel *last_msg_label = nullptr;       // 最后一条聊天消息标签
    QLabel *date_time_label = nullptr;      // 最后一条聊天消息的聊天时间
    QHBoxLayout *main_layout = nullptr;     // 最终的主布局包括左边的用户头像和上面的剩下的布局

private:
    /// API 获取用户信息操作
    // 获取本地用户信息
    void GetUserNameCard(const std::string & account);
    // 获取服务器用户信息
    void GetUserNameCardOnLine(const std::string & account);
    //  获取用户信息回调
    void OnGetUserCard(const std::list<nim::UserNameCard> &json_result);

signals:
    void updateItemSignal();     // SessionItem::updateItem

};

#endif // MESSAGEITEM_H
