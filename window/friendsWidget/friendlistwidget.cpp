//
// Created by 19216 on 2021/5/30.
//

// You may need to build the project (run Qt uic code generator) to get "ui_FriendListWidget.h" resolved

#include "friendlistwidget.h"

FriendListWidget::FriendListWidget(QListWidget *parent) :
        QListWidget(parent) {

    InitFriendList();

}

FriendListWidget::~FriendListWidget() {

}


void FriendListWidget::InitControl() {
    QFile css(":/css/recentSessionWidget");
    css.open(QFile::ReadOnly);
//    qDebug() << css.readAll();
    this->setStyleSheet(css.readAll());
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);//水平滚动条关闭
    this->setFocusPolicy(Qt::NoFocus);      // 删除选中 某一个item是产生的虚线框
//    this->setMouseTracking(true);
}



void FriendListWidget::InitFriendList() {
    nim::Friend::GetList([this](auto && PH1, auto && PH2) {
        OnGetFriendList(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
    });
}

void FriendListWidget::OnGetFriendList(nim::NIMResCode res_code, const std::list<nim::FriendProfile> &user_profile_list) {
    qDebug() << "[info]: 获取 " << user_profile_list.size() << " 个好友 ";
    for (auto & friendProfile: user_profile_list) {
        qDebug() << QString::fromStdString(friendProfile.ToJsonString());
    }
}
