//
// Created by 19216 on 2021/5/31.
//
#include <QBitmap>
#include <QPainter>
#include <QDateTime>
#include "util.h"

/**
 * 生成圆形的图片头像
 * @param src 原图像，QPixmap
 * @param radius 原方形图像边长的一半
 * @return
 */
QPixmap PixmapToRound(const QPixmap &src, int radius)
{
    if (src.isNull()) {
        return QPixmap();
    }
    QSize size(2*radius, 2*radius);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), 99, 99);
    QPixmap image = src.scaled(size);
    image.setMask(mask);
    return image;
}

/**
 * 判断是否插入时间提示。只有当前消息记录与上一条消息记录相差5分钟时，即插入当前消息的具体时间提示信息。
 * @param current_time 前一条消息的时间
 * @param last_time 后一条消息的时间
 * @return
 */
bool IsInsertTimePromptInfo(int64_t current_time, int64_t last_time) {
    //    qDebug() << "current time: " << QDateTime::fromTime_t(current_time/1000);
    //    qDebug() << "last time: " << QDateTime::fromTime_t(last_time/1000);
    if ((current_time - last_time) >= 5 * 60 * 1000) return true;
    return false;
}

/**
 * 在聊天窗口界面中，要显示某一条消息是发送时间，格式化输出的时间信息
 * @param time 时间，距离1970年的毫秒数。（注意：不是秒数）
 * @return 返回格式化后显示的字符串
 */
QString FormatTimeInfoInChattingWindow(int64_t msg_time_tag) {
    QDateTime time = QDateTime::fromTime_t(msg_time_tag/1000);
    QDateTime current = QDateTime::currentDateTime();
    if(time.date().year() != current.date().year()){
        // 如果聊天时间的年份与当前年份不一样，则直接显示聊天时间的年月日 时分
        return time.toString("yyyy-MM-dd hh:mm");
    }
    if(time.date() == current.date()) {
        // 聊天时间的日期与当前的日期一样，则返回聊天的时间
        return time.time().toString("hh:mm");
    }
    if(time.addDays(1).date() == current.date()) {
        // 如果聊天日期加一天之后与当前日期一样，则证明聊天时间是昨天，返回“昨天”
        return time.time().toString("昨天 hh:mm");
    }
    // 不是上面的几种情况，则返回月份和日期
    return time.toString("MM-dd hh:mm");
}

/**
 * 在会话列表的一个item中要显示的时间信息
 * @param msg_time_tag 时间，距离1970年的毫秒数。（注意：不是秒数）
 * @return 返回格式化后的时间字符串
 */
QString FormatTimeInRecentSession(int64_t msg_time_tag)
{
    QDateTime time = QDateTime::fromTime_t(msg_time_tag/1000);
    QDateTime current = QDateTime::currentDateTime();
    if(time.date().year() != current.date().year()){
        // 如果聊天时间的年份与当前年份不一样，则直接显示聊天时间的年月日
        return time.date().toString("yyyy-MM-dd");
    }
    if(time.date() == current.date()) {
        // 聊天时间的日期与当前的日期一样，则返回聊天的时间
        return time.time().toString("hh:mm");
    }
    if(time.addDays(1).date() == current.date()) {
        // 如果聊天日期加一天之后与当前日期一样，则证明聊天时间是昨天，返回“昨天”
        return "昨天";
    }
    // 不是上面的几种情况，则返回月份和日期
    return time.date().toString("MM-dd");
}