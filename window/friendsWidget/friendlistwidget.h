//
// Created by 19216 on 2021/5/30.
//

#ifndef NIMQTCLIENT_FRIENDLISTWIDGET_H
#define NIMQTCLIENT_FRIENDLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QFile>
#include <QDebug>

#include "client.h"
#include "frienditem.h"

class FriendListWidget : public QListWidget {
Q_OBJECT

public:
    explicit FriendListWidget(QListWidget *parent = nullptr);

    ~FriendListWidget() override;

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
    void InitFriendList();
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
    void OnUserInfoChange(const std::list<nim::UserNameCard> &user_name_card_list);


    // 修改用户信息资料
    void UpdateMyUserNameCard(const nim::UserNameCard& info);
    // 修改用户信息资料回调
    void OnUpdateMyInfo(nim::NIMResCode res);
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////


public:


    signals:
    void AddOneFriendSignal(const nim::UserNameCard &userNameCard);         // 新增一个好友条目信号
    void UpdateFriendSignal(const nim::UserNameCard &userNameCard);         // 更新好友条目的信息信号

    void OpenChattingWindowSignal(const nim::UserNameCard &userNameCard);         // 双击某一个好友 item ，需要打开与该好友的聊天界面

public slots:
    void AddOneFriendSlot(const nim::UserNameCard &userNameCard);       // 新增一个好友条目槽函数
    void UpdateFriendSlot(const nim::UserNameCard &userNameCard);       // 更新好友条目的槽函数
};


#endif //NIMQTCLIENT_FRIENDLISTWIDGET_H
