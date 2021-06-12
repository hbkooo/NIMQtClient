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
#include <QEvent>
#include <QKeyEvent>
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
    QLabel *infoLabel;                  // 操作提示信息
    QPushButton *createButton;

private:
    // 键都是用户的唯一标识符，accID。来判断该用户信息是否已经保存，或者可以立即更新该用户的信息
    QMap<QString, nim::FriendProfile> friendProfileMap;     // 该用户的好友关系列表
    QMap<QString, nim::UserNameCard> userNameCardMap;       // 所有的用户的详细信息，可能并不是该用户的好友


protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;

signals:
    // 显示创建群的提示信息结果
    void ShowResultOfCreateTeamSignal(const QString &resultInfo);

public slots:
    void ClickedCreateTeamButtonSlot();
    // 显示创建群的提示信息结果
    void ShowResultOfCreateTeamSlot(const QString &resultInfo);

};



#endif //NIMQTCLIENT_CREATETEAMWIDGET_H
