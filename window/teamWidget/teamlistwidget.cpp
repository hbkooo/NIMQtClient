//
// Created by 19216 on 2021/5/30.
//

// You may need to build the project (run Qt uic code generator) to get "ui_FriendListWidget.h" resolved

#include "teamlistwidget.h"

TeamListWidget::TeamListWidget(QListWidget *parent) :
        QListWidget(parent) {

    this->setObjectName("MsgFriItem");      // 为了使用listWidget.css中的一些鼠标选中和hover样式
    InitControl();
    SetConnect();
    // 首先获取本地的群列表
//    GetTeamListLocal();
    // 获取所有的群 id
    GetTeamIDList();

    // 监听群变化
    ListenTeamChangeEvent();

}

TeamListWidget::~TeamListWidget() {

}

void TeamListWidget::InitControl() {
    QFile css(":/css/listWidget");
    css.open(QFile::ReadOnly);
    this->setStyleSheet(css.readAll());
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);//水平滚动条关闭
    this->setFocusPolicy(Qt::NoFocus);      // 删除选中 某一个item是产生的虚线框
    this->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);   // 让内容连续地滚动，而不是整行整行的滚动
}

void TeamListWidget::SetConnect() {
    connect(this, &TeamListWidget::AddOneTeamSignal, this, &TeamListWidget::AddOneTeam);
    connect(this, &TeamListWidget::UpdateTeamInfoSignal, this, &TeamListWidget::UpdateTeamInfo);
}

void TeamListWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    auto index = currentIndex();    // 获取当前点击的item对应的index

    QListWidgetItem *item = itemAt(event->pos());       // 获取点击的item
    if (item == nullptr) return;
    // 从item获取对应的自定义的widget
    auto *friendItem = dynamic_cast<TeamItem *>(this->itemWidget(item));
    if (friendItem == nullptr) return;
    //emit OpenChattingWindowSignal(friendItem->getUserNameCard());
//    auto sessionData = messageItem->getSessionData();
//    auto *chattingWindow = new ChattingWindow(sessionData);
    // 将最近发送的消息成功与否信号传递到聊天窗口中
//    connect(this, &RecentSessionWidget::sendMsgCallbackSignal, chattingWindow, &ChattingWindow::sendMsgCallbackSlot);
    // 当其他用户发送来新的消息后所有的聊天窗口界面都会收到该消息。
//    connect(this, &RecentSessionWidget::receiveMsgSignal, chattingWindow, &ChattingWindow::receiveMsgSlot);
//    chattingWindow->show();
//    RestUnread(sessionData.id_, sessionData.type_);
    QAbstractItemView::mouseDoubleClickEvent(event);
}

//////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// 群列表操作 /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
// 获取群聊id列表
void TeamListWidget::GetTeamIDList() {
    // 获取所有的群组 id 列表
    nim::Team::QueryAllMyTeamsAsync([this](int team_count, const std::list<std::string>& team_id_lis) {
        qDebug() << "===============================";
        for(const auto& id: team_id_lis) {
            if(!teamIDs.contains(QString::fromStdString(id))) {
                // 现在已经获取的群中不包含这个 teamID，说明需要在线获取该群的信息
                GetTeamInfoOnline(QString::fromStdString(id));
            }
            teamIDs.insert(QString::fromStdString(id));
        }
        qDebug() << "[info]: 获取所有群id：" << teamIDs;
        qDebug() << "===============================";
    });
}

// 获取本地群聊信息列表
void TeamListWidget::GetTeamListLocal() {
    // void(int team_count, const std::list<nim::TeamInfo>& team_info_list)
    nim::Team::QueryAllMyTeamsInfoAsync([this](int team_count, const std::list<nim::TeamInfo>& team_info_list) {
        qDebug() << "===============================";
        qDebug() << "[info]: get " << team_info_list.size() << " teams";
        for(const auto& team: team_info_list) {
            teamIDs.insert(QString::fromStdString(team.GetTeamID()));
            qDebug() << "[info]: team : " << QString::fromStdString(team.ToJsonString());

            // TeamListWidget::AddOneTeam
            emit AddOneTeamSignal(team);

            // TeamListWidget::UpdateTeamInfo
            // RecentSessionWidget::UpdateTeamInfoSlot.使用一条一条的发送
            emit UpdateTeamInfoSignal(team);
        }
        qDebug() << "===============================";
    });
}

// 根据群 id 在线获取该群的信息
void TeamListWidget::GetTeamInfoOnline(const QString& teamID) {
    // void(const TeamEvent& team_event)

    nim::Team::QueryTeamInfoOnlineAsync(teamID.toStdString(),[this](const nim::TeamEvent& team_event) {

        if(team_event.res_code_ == nim::kNIMResSuccess) {
            const nim::TeamInfo &info = team_event.team_info_;
            qDebug() << "[info]: In " << __FUNCTION__ << ", query team online: "
                     << QString::fromStdString(info.ToJsonString());
            teamIDs.insert(QString::fromStdString(info.GetTeamID()));

            // TeamListWidget::AddOneTeam
            emit AddOneTeamSignal(info);

            // TeamListWidget::UpdateTeamInfo
            // RecentSessionWidget::UpdateTeamInfoSlot.使用一条一条的发送
            emit UpdateTeamInfoSignal(info);

        } else {
            qDebug() << "[error]: Query team info from online error, code is " << team_event.res_code_;
        }

    });

}

// 获取群组成员
void TeamListWidget::GetTeamMembers(const QString &teamID) {
    nim::Team::QueryTeamMembersAsync(teamID.toStdString(),
                                    [this](const std::string& tid,
                                            int member_count,
                                            const std::list<nim::TeamMemberProperty>& props) {
        qDebug() << "[info]: get " << member_count << " members in " << QString::fromStdString(tid);
    });
}

// 注册群变化通知
void TeamListWidget::ListenTeamChangeEvent() {
    nim::Team::RegTeamEventCb([this](const nim::TeamEvent& team_event) {
        if(team_event.res_code_ == nim::kNIMResSuccess) {

            if (team_event.notification_id_ == nim::kNIMNotificationIdLocalCreateTeam) {

            }
            if(team_event.notification_id_ == nim::kNIMNotificationIdTeamInvite) {
                // 普通群拉人
                // 获取该群的详细信息，并添加到群列表中
                qDebug() << "[info]: 创建普通群，拉人：" << team_event.namecards_.size();
                GetTeamInfoOnline(QString::fromStdString(team_event.team_id_));
                //qDebug() << "[info]: get one change of team, notify id: "
                //         << team_event.notification_id_ << ", team id: "
                //         << QString::fromStdString(team_event.team_id_) << ", name card size: "
                //         << team_event.namecards_.size() << ", ids size: "
                //         << team_event.ids_.size() << ", "
                //         << QString::fromStdString(team_event.team_info_.ToJsonString());
            }
        } else {
            qDebug() << "[error]: In " << __FUNCTION__ << ", error code is : " << team_event.res_code_;
        }
    });
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////


// 新增一个群
void TeamListWidget::AddOneTeam(const TeamInfo &teamInfo) {

    if(teamItemsMap.contains(QString::fromStdString(teamInfo.GetTeamID()))) {
        // 列表中已经存在了该群
        qDebug() << "群列表中已经存在该群 ...";
        return;
    }

    auto *teamItem = new TeamItem(teamInfo);

    teamItemsMap.insert(QString::fromStdString(teamInfo.GetTeamID()), teamItem);
    auto *listItem = new QListWidgetItem();
    // 必须设置，设置每一个条目显示的宽、高
    listItem->setSizeHint(QSize(0, teamItem->size().height()));
    // 设置用户数据，即将item中保存该item对应的sessionID，便于以后更新item时查找到该item
    listItem->setData(Qt::UserRole, QString::fromStdString(teamInfo.GetTeamID()));
    this->addItem(listItem);
    this->setItemWidget(listItem, teamItem);
}

// 更新群信息
void TeamListWidget::UpdateTeamInfo(const TeamInfo &teamInfo) {
    // TODO 群信息变更
    // 群信息更新变化通知处理
    auto teamID = QString::fromStdString(teamInfo.GetTeamID());
    if (teamItemsMap.contains(teamID)) {
        teamItemsMap[teamID]->setTeamInfo(teamInfo);
        teamItemsMap[teamID]->updateItem();
    }
    teamInfoMap.insert(teamID, teamInfo);
}




