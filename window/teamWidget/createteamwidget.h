//
// Created by 19216 on 2021/6/9.
//

#ifndef NIMQTCLIENT_CREATETEAMWIDGET_H
#define NIMQTCLIENT_CREATETEAMWIDGET_H

#include <QWidget>
#include <QMap>
#include <QListWidget>
#include <QListWidgetItem>
#include <QFile>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QDebug>

#include "client.h"
#include "createteamitem.h"

class CreateTeamWidget : public QWidget {
Q_OBJECT

public:
    explicit CreateTeamWidget(QWidget *parent = nullptr);

    ~CreateTeamWidget() override;

    void setFriendProfileMap(const QMap<QString, nim::FriendProfile> &friendMap) { friendProfileMap = friendMap; }
    void setUserNameCardMap(const QMap<QString, nim::UserNameCard>& userCard) { userNameCardMap = userCard; }
    // 更新显示的好友列表
    void updateWindow();

private:
    void InitControl();

private:
    // 创建群聊
    void CreateTeam(const nim::TeamInfo &teamInfo, const QList<std::string> &ids, const QString& description="");


private:
    QLineEdit *teamNameLineEdit;        //  群名称
    QListWidget *userInfoListWidget;
    QTextEdit *teamDescriptionTextEdit; // 群描述
    QPushButton *createButton;

private:
    // 键都是用户的唯一标识符，accID。来判断该用户信息是否已经保存，或者可以立即更新该用户的信息
    QMap<QString, nim::FriendProfile> friendProfileMap;     // 该用户的好友关系列表
    QMap<QString, nim::UserNameCard> userNameCardMap;       // 所有的用户的详细信息，可能并不是该用户的好友

public slots:
    void ClickedCreateTeamButtonSlot();

};



#endif //NIMQTCLIENT_CREATETEAMWIDGET_H
