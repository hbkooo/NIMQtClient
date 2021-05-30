#include "messageitem.h"

#include <QBitmap>
#include <QPainter>


MessageItem::MessageItem(const Message &message, QWidget *parent)
    :message(message) ,QWidget(parent)
{
    // 用户头像
    header_label = new QLabel("头像");
    header_label->setFixedSize(48, 48);
    auto map = message.header_pixmap.scaled(header_label->size());
    map = PixmapToRound(map, 24);
    header_label->setPixmap(map);

    // 创建用户姓名标签
    name_label = new QLabel("用户名字");
    name_label->setStyleSheet("font-size:20px;");
    name_label->adjustSize();
    name_label->setText(message.name);

    // 创建最后一条聊天消息标签
    last_msg_label = new QLabel("最后一条消息");
    last_msg_label->setStyleSheet("font-size:14px;"
                                  "color:#6f6a6d");
    last_msg_label->setFixedHeight(14);
    if(message.msgs.size() != 0) {
        last_msg_label->setText(message.msgs.last());
    } else {
        last_msg_label->setText("");
    }

    // 创建最后一条聊天消息的聊天时间
    date_time_label = new QLabel("聊天时间");
    date_time_label->adjustSize();      // 自适应文本的大小
    date_time_label->setStyleSheet("font-size:14px;"
                                   "color:#6f6a6d");
    date_time_label->setText(generate_last_time(message.date_time));

    // 一个水平布局包括用户名和时间
    auto *name_time_layout = new QHBoxLayout();
    name_time_layout->setSpacing(0);
    name_time_layout->setMargin(0);
    name_time_layout->setContentsMargins(0, 0, 0, 0);
    name_time_layout->addWidget(name_label);
    name_time_layout->addStretch();
    name_time_layout->addSpacing(8);
    name_time_layout->addWidget(date_time_label);

    // 一个竖直布局包括上面的用户名时间布局和下面的最后一条消息控件
    auto *name_msg_time_layout = new QVBoxLayout();
    name_msg_time_layout->setSpacing(0);
    name_msg_time_layout->setMargin(0);
    name_msg_time_layout->setContentsMargins(0, 0, 0, 0);
    name_msg_time_layout->addStretch();
    name_msg_time_layout->addLayout(name_time_layout);
    name_msg_time_layout->addSpacing(6);
    name_msg_time_layout->addWidget(last_msg_label);
    name_msg_time_layout->addStretch();

    // 最终的主布局包括左边的用户头像和上面的剩下的布局
    main_layout = new QHBoxLayout();
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->setMargin(0);
    main_layout->addSpacing(16);
    main_layout->addWidget(header_label, 0, Qt::AlignVCenter);
    main_layout->addSpacing(8);
    main_layout->addLayout(name_msg_time_layout);
    main_layout->addSpacing(16);

    setLayout(main_layout);

    this->setFixedHeight(68);               // 头像高40 + 上边界10 + 下边界10
    this->setStyleSheet("background:transparent;"); //只有设置了透明背景之后在hover的时候背景才可以看到，不然该item中的控件背景还是白色的

}

// 更新该条目的信息
void MessageItem::update(const Message &message)
{
    this->message = message;
    // 更新用户头像信息
    header_label->setPixmap(PixmapToRound(message.header_pixmap.scaled(header_label->size()), 24));
    // 更新用户名
    name_label->setText(message.name);
    // 更新最后一条消息信息
    if(message.msgs.size() > 0) {
        last_msg_label->setText(message.msgs.last());
    } else {
        last_msg_label->setText("");
    }
    // 更新最后一条消息的时间
    date_time_label->setText(generate_last_time(message.date_time));
}

// 生成会话列表的一个item中要显示的时间信息
QString MessageItem::generate_last_time(const QDateTime &time)
{
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

// 生成圆形的图片头像
QPixmap MessageItem::PixmapToRound(const QPixmap &src, int radius)
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
