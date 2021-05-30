#ifndef MESSAGE_H
#define MESSAGE_H
#include<QObject>
#include<QDateTime>
#include<QPixmap>

struct Message{
    QPixmap header_pixmap;      // 用户头像
    QString name;               // 用户名
    QList<QString> msgs;        // 与该用户的聊天信息
    QDateTime date_time;        // 最新的一条信息的聊天时间
};


#endif // MESSAGE_H
