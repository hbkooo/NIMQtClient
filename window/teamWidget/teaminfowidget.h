//
// Created by 19216 on 2021/6/10.
//

#ifndef NIMQTCLIENT_TEAMINFOWIDGET_H
#define NIMQTCLIENT_TEAMINFOWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMap>
#include <QFile>
#include <QDebug>

#include <iostream>
#include "client.h"
#include "util/util.h"

class TeamInfoWidget : public QWidget {
Q_OBJECT

public:
    explicit TeamInfoWidget(nim::TeamInfo info, QWidget *parent = nullptr);

    ~TeamInfoWidget() override;
    // 设置界面显示的群数据
    void setTeamInfo(const nim::TeamInfo &info) { teamInfo = info; }
    // 显示界面
    void ShowNormal();

private:
    void InitControl();
    // 初始化下方群信息控件
    void InitBaseTeamInfoControl();
    // 向成员列表中添加一行成员信息
    void AddOneLineMemberInListWidget(QWidget *lineWidget);

    // 创建一个用户成员的显示控件
    QWidget *createOneMemberWidget(const nim::TeamMemberProperty &memberProperty);

    /// API
    // 获取群组成员
    void GetTeamMembers(const QString &teamID);

    // 获取本地用户信息
    void GetUserNameCard(const QList<QString> &accounts);
    // 获取服务器用户信息
    void GetUserNameCardOnLine(const QList<QString>& accounts);

private:
    QListWidget *memberListWidget;                              // 显示成员信息的列表
    QMap<std::string, QWidget*> memberWidget;                   // 创建的每一个成员显示的控件

    QListWidget *baseTeamInfoListWidget;                        // 群的其他消息列表
    QLabel *teamHeaderPhotoLabel;                               // 群头像
    QLabel *teamIdLabel;                                        // 群id
    QLabel *teamNameLabel;                                      // 群名称
    QLabel *teamDescriptionLabel;                               // 群介绍

private:
    nim::TeamInfo teamInfo;
    QList<nim::TeamMemberProperty> teamMembers;                 // 该群的所有用户成员
    QMap<std::string, nim::UserNameCard> userNameCardsMap;      // 所有成员的名片


    signals:
    // 获取完群成员信息之后，发送信号，来更新界面显示的群成员信息
    void updateWindowMembersSignal();
    // 当获取一条用户的名片时，需要更新显示的成员列表中成员的信息
    void updateOneMemberByUserNameCardSignal(const nim::UserNameCard &userNameCard);

public slots:
    // 更新界面显示的群成员信息
    void updateWindowMemberSlot();
    // 当获取一条用户的名片时，需要更新显示的成员列表中成员的信息
    void updateOneMemberByUserNameCardSlot(const nim::UserNameCard &userNameCard);

};


#endif //NIMQTCLIENT_TEAMINFOWIDGET_H
