#include "messageitem.h"

#include <QBitmap>
#include <QPainter>
#include <utility>


MessageItem::MessageItem(nim::SessionData data, QWidget *parent)
    :sessionData(std::move(data)) ,QWidget(parent)
{
    // 用户头像
    header_label = new QLabel("头像");
    header_label->setFixedSize(48, 48);
    QPixmap map(":/default_header/dh1");
    map = PixmapToRound(map.scaled(header_label->size()), 24);
    header_label->setPixmap(map);

    // 创建用户姓名标签
    name_label = new QLabel("用户名字");
    name_label->setStyleSheet("font-size:20px;");
    name_label->adjustSize();
    name_label->setText(QString::fromStdString(sessionData.id_));

    // 创建最后一条聊天消息标签
    last_msg_label = new QLabel("最后一条消息");
    last_msg_label->setStyleSheet("font-size:14px;"
                                  "color:#6f6a6d");
    last_msg_label->setFixedHeight(14);
    last_msg_label->setText(QString::fromStdString(sessionData.msg_content_));


    // 创建最后一条聊天消息的聊天时间
    date_time_label = new QLabel("聊天时间");
    date_time_label->adjustSize();      // 自适应文本的大小
    date_time_label->setStyleSheet("font-size:14px;"
                                   "color:#6f6a6d");
    date_time_label->setText(FormatTimeInRecentSession(sessionData.msg_timetag_));

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

void MessageItem::update(const nim::SessionData &data) {
    sessionData = data;
    // 更新用户名
    name_label->setText(QString::fromStdString(sessionData.id_));
    // 更新最后一条消息信息
    last_msg_label->setText(QString::fromStdString(sessionData.msg_content_));
    // 更新最后一条消息的时间
    date_time_label->setText(FormatTimeInRecentSession(sessionData.msg_timetag_));
}



