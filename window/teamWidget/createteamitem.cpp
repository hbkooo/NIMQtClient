//
// Created by 19216 on 2021/6/9.
//


#include "createteamitem.h"

#include <utility>


CreateTeamItem::CreateTeamItem(UserNameCard nameCard, FriendProfile profile, QWidget *parent) :
        userNameCard(std::move(nameCard)), friendProfile(std::move(profile)), QWidget(parent) {
    qDebug() << QString::fromStdString(friendProfile.ToJsonString());
    this->setFixedHeight(58);
    InitControl();

}

CreateTeamItem::~CreateTeamItem() {
    qDebug() << "[info]: In " << __FUNCTION__ << ", delete create team item ...";
}

void CreateTeamItem::InitControl() {

    radioButton = new QRadioButton();
    radioButton->setStyleSheet("QRadioButton::indicator {"
                               "    width: 22px;"
                               "    height: 22px;"
                               "}"
                               "QRadioButton::indicator:unchecked {"
                               "     image: url(:/res/rb_unchecked);}"
                               "QRadioButton::indicator:checked {"
                               "     image: url(:/res/rb_checked);"
                               "}");

    headerPhotoLabel = new QLabel("头像");
    headerPhotoLabel->setFixedSize(44, 44);
    updateHeaderPhotoIcon();

    nameLabel = new QLabel("用户名");
    nameLabel->setStyleSheet("font-size:18px;");
    QString name;
    if (!friendProfile.GetAlias().empty()) {
        // 用户的备注不为空
        name = QString::fromStdString(friendProfile.GetAlias());
    } else if (!userNameCard.GetName().empty()) {
        // 用户的名片昵称不为空
        name = QString::fromStdString(userNameCard.GetName());
    } else {
        // 都为空，则直接设置为 accID
        name = QString::fromStdString(friendProfile.GetAccId());
    }
    name = name + " (" + QString::fromStdString(friendProfile.GetAccId()) + ")";
    nameLabel->setText(name);

    auto *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(radioButton);
    mainLayout->addWidget(headerPhotoLabel);
    mainLayout->addWidget(nameLabel);
    mainLayout->addStretch();
    setLayout(mainLayout);

}

// 设置用户头像
void CreateTeamItem::updateHeaderPhotoIcon() {
    if (userNameCard.GetIconUrl().empty()) {
        userNameCard.SetIconUrl(":/default_header/dh9");
    }
    QPixmap map(QString::fromStdString(userNameCard.GetIconUrl()));
    if (map.isNull()) {
        // 头像加载失败
        map.load(":/default_header/dh9");
    }
    headerPhotoLabel->setPixmap(
            PixmapToRound(
                    map.scaled(headerPhotoLabel->size()),
                    headerPhotoLabel->height() / 2)
    );
}

void CreateTeamItem::mousePressEvent(QMouseEvent *event) {
    if (radioButton->isChecked()) {
        radioButton->setChecked(false);
    } else {
        radioButton->setChecked(true);
    }
}


