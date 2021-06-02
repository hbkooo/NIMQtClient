#ifndef MESSAGE_H
#define MESSAGE_H
#include<QObject>
#include<QDateTime>
#include<QPixmap>

struct Message{
    QPixmap header_pixmap;      // 用户头像
    QString name;               // 用户名
    QList<QString> msgs;        // 与该用户的聊天信息
    int64_t msg_time_tag;       // 当前会话最新一条消息时间戳（毫秒）
};


#endif // MESSAGE_H
