//
// Created by 19216 on 2021/5/31.
//

#include "chattingitem.h"

/**
 * 构造函数
 * @param isRight_ 该条消息是自己发送的消息还是对方发送的消息，因为要根据这个标志来判断头像是在右边还是左边
 * @param parent 父控件
 */
ChattingItem::ChattingItem(bool isRight_, QWidget *parent) :
        isLeft(isRight_), QWidget(parent) {
    InitControl();
    SetLayout();
}

ChattingItem::~ChattingItem() {
    qDebug() << "[info]: In ~ChattingItem ...";
}

void ChattingItem::InitControl() {
    messageContentLabel = new QLabel();

//    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    QSizePolicy sizePolicy;
//    sizePolicy.setHorizontalPolicy(QSizePolicy::Expanding);
//    sizePolicy.setVerticalPolicy(QSizePolicy::Minimum);
//    sizePolicy.setHorizontalStretch(0);
//    sizePolicy.setVerticalStretch(1);
//    qDebug() << messageContentLabel->sizePolicy().hasHeightForWidth();
//    sizePolicy.setHeightForWidth(messageContentLabel->sizePolicy().hasHeightForWidth());
//    messageContentLabel->setSizePolicy(sizePolicy);

    messageContentLabel->setMaximumWidth(500);
    messageContentLabel->setContentsMargins(20, 10, 20, 10);
    messageContentLabel->setWordWrap(true);         // 设置自动换行
    messageContentLabel->setStyleSheet("color:black;"
                                       "font-size: 18px;"
                                       "background: #e1e6eb;"
                                       "border-radius: 8px;");
//    qDebug() << "messageContentLabel size : " << messageContentLabel->size();
//    qDebug() << "messageContentLabel size : " << messageContentLabel->sizeHint();

    headPhotoLabel = new QLabel();
    headPhotoLabel->setFixedSize(40, 40);
    QPixmap map(":/default_header/dh9");
    map = map.scaled(headPhotoLabel->size());
    headPhotoLabel->setPixmap(PixmapToRound(map, 20));

}

void ChattingItem::SetLayout() {

    auto *hLayout = new QHBoxLayout();
    if(isLeft) {
        // 自己发送的消息
        hLayout->addStretch();
        hLayout->addWidget(messageContentLabel);
        hLayout->addWidget(headPhotoLabel);
    } else {
        // 别人发送的消息
        hLayout->addWidget(headPhotoLabel);
        hLayout->addWidget(messageContentLabel);
        hLayout->addStretch();
    }
    setLayout(hLayout);
}

void ChattingItem::updateContent(const QString& content) {
    messageContentLabel->setText(content);
    qDebug() << "after update content messageContentLabel size : " << messageContentLabel->size();
    qDebug() << "after update content messageContentLabel size : " << messageContentLabel->sizeHint();

}

void ChattingItem::updateContent(const nim::IMMessage &msg) {
    message = msg;
    messageContentLabel->setText(QString::fromStdString(msg.content_));
}

