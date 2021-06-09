//
// Created by 19216 on 2021/6/9.
//

#ifndef NIMQTCLIENT_CREATETEAMITEM_H
#define NIMQTCLIENT_CREATETEAMITEM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QRadioButton>

#include <QDebug>

#include "client.h"
#include "util/util.h"

using namespace nim;

class CreateTeamItem : public QWidget {
Q_OBJECT

public:
    explicit CreateTeamItem(UserNameCard nameCard, FriendProfile profile, QWidget *parent = nullptr);

    ~CreateTeamItem() override;

    bool getChecked() { return radioButton->isChecked(); }
    const UserNameCard& getUserNameCard() const { return userNameCard; }

private:
    void InitControl();
    void updateHeaderPhotoIcon();

private:
    // 界面控件
    QRadioButton *radioButton;          // 是否选中
    QLabel *headerPhotoLabel;           // 头像
    QLabel *nameLabel;                  // 用户名

private:
    // 存储数据
    UserNameCard userNameCard;
    FriendProfile friendProfile;

protected:
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void clicked();

};


#endif //NIMQTCLIENT_CREATETEAMITEM_H
