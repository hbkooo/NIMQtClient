#ifndef MESSAGEITEM_H
#define MESSAGEITEM_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QDateTime>
#include <QDebug>

#include <client.h>
#include "util/util.h"

/**
 * @brief The SessionItem class
 * 自定义的控件，即列表中每一个item的内容
 */

class SessionItem: public QWidget
{
    Q_OBJECT

public:
    explicit SessionItem(nim::SessionData data, QWidget *parent=nullptr);
    ~SessionItem() override;

    const nim::SessionData& getSessionData() const {return sessionData;}

    // 更新该条目的信息
    void update(const nim::SessionData &data);

private:
    // 根据一条消息记录创建一个会话列表的item
    // QWidget* make_one_item(const Message &msg);

private:

    // 该条目显示的信息
    nim::SessionData sessionData;

    QLabel *header_label = nullptr;         // 用户头像
    QLabel *name_label = nullptr;           // 用户姓名标签
    QLabel *last_msg_label = nullptr;       // 最后一条聊天消息标签
    QLabel *date_time_label = nullptr;      // 最后一条聊天消息的聊天时间
    QHBoxLayout *main_layout = nullptr;     // 最终的主布局包括左边的用户头像和上面的剩下的布局

signals:

};

#endif // MESSAGEITEM_H
