//
// Created by 19216 on 2021/5/30.
//

#ifndef NIMQTCLIENT_FRIENDLISTWIDGET_H
#define NIMQTCLIENT_FRIENDLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QFile>
#include <QMap>
#include <QDebug>

#include "client.h"
#include "frienditem.h"

class FriendListWidget : public QListWidget {
Q_OBJECT

public:
    explicit FriendListWidget(QListWidget *parent = nullptr);
    ~FriendListWidget() override;

    void InitFriendList();

    const QMap<QString, nim::UserNameCard>& getUserNameCardMap() const { return userNameCardMap; }
    const QMap<QString, nim::FriendProfile>& getFriendProfileMap() const { return friendProfileMap; }

private:
    void InitControl();
    void SetConnect();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;     //鼠标双击事件

private:
    ///////////////////////////////////////////////////////////////////////
    //////////////////////////// 好友列表操作 ///////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    // 获取好友列表
    void GetFriendList();

    // 获取好友列表回调
    void OnGetFriendList(nim::NIMResCode res_code, const std::list<nim::FriendProfile>& user_profile_list);

    // 好友列表变化监听
    void ListenFriendListChange();
    // 好友列表变化回调
    void OnFriendListChange(const nim::FriendChangeEvent& change_event);
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////


    ///////////////////////////////////////////////////////////////////////
    //////////////////////////// 用户信息操作 ///////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    // 获取本地用户信息
    void GetUserNameCard(const QList<QString>& accounts);
    // 获取服务器用户信息
    void GetUserNameCardOnLine(const QList<QString>& accounts);
    //  获取用户信息回调
    void OnGetUserCard(const std::list<nim::UserNameCard> &json_result);

    // 用户信息变化监听
    void ListenUserNameCardChanged();
    // 用户信息变化监听回调
    void OnUserInfoChange(const std::list<nim::UserNameCard> &info_list);

    // 修改用户信息资料
    void UpdateMyUserNameCard(const nim::UserNameCard& info);
    // 修改用户信息资料回调
    void OnUpdateMyInfo(nim::NIMResCode res);
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////

private:
    // 键都是用户的唯一标识符，accID。来判断该用户信息是否已经保存，或者可以立即更新该用户的信息
    QMap<QString, FriendItem*> friendItemsMap;              // 好友列表中的每一个好友条目信息
    QMap<QString, nim::UserNameCard> userNameCardMap;       // 所有的用户的详细信息，可能并不是该用户的好友
    QMap<QString, nim::FriendProfile> friendProfileMap;     // 该用户的好友关系列表

public:
    signals:
    void AddOneFriendSignal(const nim::UserNameCard &userNameCard);         // 新增一个好友条目信号

    void OpenChattingWindowSignal(const nim::UserNameCard &userNameCard);         // 双击某一个好友 item ，需要打开与该好友的聊天界面

    // 初始化加载完毕用户名片和好友列表后发送信号
    void InitUserNameCardMapSignal(const QMap<QString, nim::UserNameCard> &userNameMap);
    void InitFriendProfileMapSignal(const QMap<QString, nim::FriendProfile> &friendProMap);
    // 用户名片发生变化或者好友关系发生变化后发送信号
    // FriendListWidget::UpdateUserNameCardSlot、RecentSessionWidget::UpdateUserNameCardSlot
    void UpdateUserNameCardSignal(const nim::UserNameCard &userNameCard);
    // FriendListWidget::UpdateFriendProfileSlot、RecentSessionWidget::UpdateFriendProfileSlot、
    void UpdateFriendProfileSignal(const nim::FriendProfile &friendProfile);

public slots:
    void AddOneFriendSlot(const nim::UserNameCard &userNameCard);               // 新增一个好友条目槽函数
    void UpdateUserNameCardSlot(const nim::UserNameCard &userNameCard);         // 更新用户信息的槽函数
    void UpdateFriendProfileSlot(const nim::FriendProfile &friendProfile);      // 更新好友条目的槽函数
};


#endif //NIMQTCLIENT_FRIENDLISTWIDGET_H
