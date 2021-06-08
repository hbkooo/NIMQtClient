//
// Created by 19216 on 2021/5/30.
//

#ifndef NIMQTCLIENT_FRIENDLISTWIDGET_H
#define NIMQTCLIENT_FRIENDLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QFile>
#include <QMap>
#include <QMouseEvent>
#include <QDebug>

#include "client.h"
#include "teamitem.h"

class TeamListWidget : public QListWidget {
Q_OBJECT

public:
    explicit TeamListWidget(QListWidget *parent = nullptr);
    ~TeamListWidget() override;

    void InitTeamList();


private:
    void InitControl();
    void SetConnect();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;     //鼠标双击事件

private:
    ///////////////////////////////////////////////////////////////////////
    //////////////////////////// 群列表操作 ////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    // 获取群聊id列表
    void GetTeamIDList();
    // 获取本地群聊信息列表
    void GetTeamListLocal();
    // 根据群 id 在线获取该群的信息
    void GetTeamListOnline(const QString& teamID);

    // 创建群聊
    void CreateTeam(const nim::TeamInfo &teamInfo, const QList<std::string> &ids, const QString& description="");

    // 获取群组成员
    void GetTeamMembers(const QString &teamID);

    // 注册群变化通知
    void ListenTeamChangeEvent();

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////


private:
    // 键都是用户的唯一标识符，accID。来判断该用户信息是否已经保存，或者可以立即更新该用户的信息
    QMap<QString, TeamItem*> friendItemsMap;              // 好友列表中的每一个好友条目信息
    QMap<QString, nim::UserNameCard> userNameCardMap;       // 所有的用户的详细信息，可能并不是该用户的好友
    QMap<QString, nim::FriendProfile> friendProfileMap;     // 该用户的好友关系列表

public:
    signals:


public slots:

};


#endif //NIMQTCLIENT_FRIENDLISTWIDGET_H
