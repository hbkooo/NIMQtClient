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

class FriendListWidget : public QListWidget {
Q_OBJECT

public:
    explicit FriendListWidget(QListWidget *parent = nullptr);

    ~FriendListWidget() override;

private:
    void InitControl();

    void InitFriendList();      // 获取好友列表
    void OnGetFriendList(nim::NIMResCode res_code, const std::list<nim::FriendProfile>& user_profile_list);

private:
};


#endif //NIMQTCLIENT_FRIENDLISTWIDGET_H
