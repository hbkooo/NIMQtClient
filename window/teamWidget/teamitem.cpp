//
// Created by 19216 on 2021/6/8.
//

#include "teamitem.h"


TeamItem::TeamItem(const TeamInfo &info, QWidget *parent) :
        teamInfo(info), QWidget(parent) {
    this->setFixedHeight(68);               // 头像高40 + 上边界10 + 下边界10
    this->setStyleSheet("background:transparent;"); //只有设置了透明背景之后在hover的时候背景才可以看到，不然该item中的控件背景还是白色的

    InitControl();
    updateItem();       // 更新界面数据
}

TeamItem::~TeamItem() {
    qDebug() << "[info]: In " << __FUNCTION__ << ", delete team item ...";
}

void TeamItem::InitControl() {
    // 用户头像GetIcon
    teamPhotoLabel = new QLabel("头像");
    teamPhotoLabel->setFixedSize(48, 48);

    // 创建用户姓名标签
    nameLabel = new QLabel("用户名字");
    nameLabel->setStyleSheet("font-size:20px;");
    nameLabel->adjustSize();

    auto *mainLayout = new QHBoxLayout();
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setMargin(0);
    mainLayout->addSpacing(16);
    mainLayout->addWidget(teamPhotoLabel, 0, Qt::AlignVCenter);
    mainLayout->addSpacing(8);
    mainLayout->addWidget(nameLabel, 0, Qt::AlignVCenter);
    mainLayout->addSpacing(16);

    setLayout(mainLayout);

}

void TeamItem::setTeamInfo(const TeamInfo &info) {
    teamInfo = info;
}

// 更新这一个item信息
void TeamItem::updateItem() {
    if (teamInfo.GetIcon().empty()) {
        teamInfo.SetIcon(":/default_header/default_team");
    }
    QPixmap map(QString::fromStdString(teamInfo.GetIcon()));
    if (map.isNull()) {
        // 头像加载失败
        map.load(":/default_header/default_team");
    }
    teamPhotoLabel->setPixmap(PixmapToRound(
            map.scaled(teamPhotoLabel->size()),
            teamPhotoLabel->height() / 2));

    if (teamInfo.GetName().empty()) {
        nameLabel->setText(QString::fromStdString(teamInfo.GetTeamID()));
    } else {
        nameLabel->setText(QString::fromStdString(teamInfo.GetName()));
    }
}