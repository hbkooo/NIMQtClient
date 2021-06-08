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

}

TeamListWidget::~TeamListWidget() {

}

// 该方法在外部调用，初始化好友列表
void TeamListWidget::InitTeamList() {
    GetTeamIDList();               // 初始化好友列表
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

    });
}

// 获取本地群聊信息列表
void TeamListWidget::GetTeamListLocal() {
    // void(int team_count, const std::list<nim::TeamInfo>& team_info_list)
    nim::Team::QueryAllMyTeamsInfoAsync([this](int team_count, const std::list<nim::TeamInfo>& team_info_list) {
        qDebug() << "[info]: get " << team_info_list.size() << " teams";
        for(const auto& team: team_info_list) {
            qDebug() << "[info]: team : " << QString::fromStdString(team.ToJsonString());
        }
    });
}

// 根据群 id 在线获取该群的信息
void TeamListWidget::GetTeamListOnline(const QString& teamID) {
    // void(const TeamEvent& team_event)

    nim::Team::QueryTeamInfoOnlineAsync(teamID.toStdString(),[this](const nim::TeamEvent& team_event) {

        if(team_event.res_code_ == nim::kNIMResSuccess) {
            nim::TeamInfo info = team_event.team_info_;
            qDebug() << "[info]: In " << __FUNCTION__ << ", query team online: "
                     << QString::fromStdString(info.ToJsonString());
        } else {
            qDebug() << "[error]: Query team info from online error, code is " << team_event.res_code_;
        }

    });

}

// 创建群聊
void TeamListWidget::CreateTeam(const nim::TeamInfo &teamInfo,
                                const QList<std::string> &ids,
                                const QString& description) {

    std::list<std::string> id_list;

    nim::Team::CreateTeamAsync(teamInfo, id_list, description.toStdString(),
                               [this](const nim::TeamEvent& team_event) {
        if(team_event.res_code_ == nim::kNIMResSuccess) {

        } else {
            qDebug() << "[error]: Create team error, code is " << team_event.res_code_;
        }
    });

}

// 获取群组成员
void TeamListWidget::GetTeamMembers(const QString &teamID) {
    nim::Team::QueryTeamMembersAsync(teamID.toStdString(),
                                    [this](const std::string& tid,
                                            int member_count,
                                            const std::list<nim::TeamMemberProperty>& props) {
        qDebug() << "[info]: get " << member_count << " members in " << tid;
    });
}

// 注册群变化通知
void TeamListWidget::ListenTeamChangeEvent() {
    nim::Team::RegTeamEventCb([this](const nim::TeamEvent& team_event) {
        if(team_event.res_code_ == nim::kNIMResSuccess) {

        } else {
            qDebug() << "[error]: In " << __FUNCTION__ << ", error code is : " << team_event.res_code_;
        }
    });
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////





