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

#include "util/util.h"
#include "client.h"


class ChattingItem : public QWidget {
Q_OBJECT

public:
    explicit ChattingItem(bool isRight_, QWidget *parent = nullptr);

    ~ChattingItem() override;

public:
    void updateContent(const QString& content);
    void updateContent(const nim::IMMessage &msg);
    const nim::IMMessage& getIMMessage() const {return message;};

private:
    void InitControl();
    void SetLayout();

private:
    QLabel *messageContentLabel;
    QLabel *headPhotoLabel;

private:
    // 消息数据
    nim::IMMessage message;
private:

    bool isLeft;       // 消息是否在左边，如果消息的发送者和接收者一样，则在左边

};


#endif //NIMQTCLIENT_CHATTINGITEM_H
