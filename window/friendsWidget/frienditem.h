//
// Created by 19216 on 2021/6/2.
//

#ifndef NIMQTCLIENT_FRIENDITEM_H
#define NIMQTCLIENT_FRIENDITEM_H

#include <QWidget>
#include <QObject>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QDateTime>
#include <QDebug>

#include <client.h>
#include "util/util.h"

class FriendItem : public QWidget {
Q_OBJECT

public:
    explicit FriendItem(nim::UserNameCard nameCard, QWidget *parent = nullptr);

    ~FriendItem() override;

    const nim::UserNameCard& getUserNameCard() const {return userNameCard;}

    // 更新用户信息
    void update(const nim::UserNameCard &nameCard);

private:
    void InitControl();
    void SetLayout();

private:
    // 控件信息
    QLabel *header_label = nullptr;         // 用户头像
    QLabel *name_label = nullptr;           // 用户姓名标签
    QLabel *signature_label = nullptr;      // 用户个性签名
    QHBoxLayout *main_layout = nullptr;     // 最终的主布局包括左边的用户头像和上面的剩下的布局

private:
    // 数据信息
    nim::UserNameCard userNameCard;

};


#endif //NIMQTCLIENT_FRIENDITEM_H
