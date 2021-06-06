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
    explicit ChattingItem(bool isLeft_, const nim::UserNameCard &nameCard, QWidget *parent = nullptr);

    ~ChattingItem() override;

public:
    void updateContent(const QString& content);
    void updateContent(const nim::IMMessage &msg);
    const nim::IMMessage& getIMMessage() const {return message;};

    void updateHeaderPhotoIcon();           // 更新消息的头像图标

private:
    void InitControl();
    void SetConnect();
    void SetLayout();

private:
    QLabel *messageContentLabel;
    ClickableLabel *headPhotoLabel;

private:
    // 消息数据
    nim::IMMessage message;
    const nim::UserNameCard &userNameCard;        // 该消息所属用户名片
private:

    bool isLeft;       // 消息是否在左边，如果消息的发送者和接收者一样，则在左边

    signals:
    void ShowHeaderPhotoLabelSignal(const nim::UserNameCard &nameCard);

public slots:
    // 点击聊天消息的头像显示信息槽函数
    void ClickedHeaderPhotoLabelSlot();

};


#endif //NIMQTCLIENT_CHATTINGITEM_H
