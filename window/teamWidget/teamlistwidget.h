//
// Created by 19216 on 2021/5/30.
//

#ifndef NIMQTCLIENT_TEAMLISTWIDGET_H
#define NIMQTCLIENT_TEAMLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QFile>
#include <QMap>
#include <QMouseEvent>
#include <QSet>
#include <QDebug>

#include "client.h"
#include "teamitem.h"

class TeamListWidget : public QListWidget {
Q_OBJECT

public:
    explicit TeamListWidget(QListWidget *parent = nullptr);
    ~TeamListWidget() override;

    const QMap<QString, TeamInfo>& getTeamInfoMap() const { return teamInfoMap; }

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
    void GetTeamInfoOnline(const QString& teamID);

    // 获取群组成员
    void GetTeamMembers(const QString &teamID);

    // 注册群变化通知
    void ListenTeamChangeEvent();
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////

    // 新增一个群
    void AddOneTeam(const TeamInfo &teamInfo);
    void UpdateTeamInfo(const TeamInfo &teamInfo);


private:
    QMap<QString, TeamItem*> teamItemsMap;      // 当前显示的所有的群 item 控件
    QMap<QString, TeamInfo> teamInfoMap;        // 群小信息
    QSet<QString> teamIDs;                      // 所有的群 id 号

public:
    signals:
    void AddOneTeamSignal(const TeamInfo &teamInfo);

    void UpdateTeamInfoSignal(const nim::TeamInfo &teamInfo);

    // 双击某一个群 item ，需要打开与该群的聊天界面
    void OpenChattingWindowSignal(const nim::TeamInfo &teamInfo);

public slots:

};


#endif //NIMQTCLIENT_TEAMLISTWIDGET_H
