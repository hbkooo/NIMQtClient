//
// Created by 19216 on 2021/5/31.
//

#ifndef NIMQTCLIENT_CHATTINGITEM_H
#define NIMQTCLIENT_CHATTINGITEM_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QDebug>

#include "util/clickablelabel.h"
#include "util/util.h"
#include "client.h"


class ChattingItem : public QWidget {
Q_OBJECT

public:
    explicit ChattingItem(bool isLeft_, const nim::UserNameCard &nameCard, bool showName = false, QWidget *parent = nullptr);

    ~ChattingItem() override;

public:
    void updateContent(const QString& content);
    void updateContent(const nim::IMMessage &msg);
    const nim::IMMessage& getIMMessage() const {return message;};

    void setUserNameCard(const nim::UserNameCard &nameCard) { userNameCard = nameCard; }
    // 更新显示的用户名和头像，主要用在当用户的个人信息修改之后需要修改每一个聊天记录的 item
    void updateNamePhoto();

    // 更新消息显示的用户名
    void updateUserName();
    // 更新消息的头像图标
    void updateHeaderPhotoIcon();

private:
    void InitControl();
    void SetConnect();
    void SetLayout();

private:
    ClickableLabel *headPhotoLabel;
    QLabel *nameLabel;
    QLabel *messageContentLabel;

private:
    // 消息数据
    nim::IMMessage message;
    nim::UserNameCard userNameCard;        // 该消息所属用户名片
private:

    bool isLeft;        // 消息是否在左边，如果消息的发送者和接收者一样，则在左边
    bool showName;      // 是否展示该消息所属的用户名

    signals:
    void ShowHeaderPhotoLabelSignal(const nim::UserNameCard &nameCard);

public slots:
    // 点击聊天消息的头像显示信息槽函数
    void ClickedHeaderPhotoLabelSlot();

};


#endif //NIMQTCLIENT_CHATTINGITEM_H
