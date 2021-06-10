//
// Created by 19216 on 2021/5/31.
//

#include "chattingitem.h"

/**
 * 构造函数
 * @param isRight_ 该条消息是自己发送的消息还是对方发送的消息，因为要根据这个标志来判断头像是在右边还是左边
 * @param parent 父控件
 */
ChattingItem::ChattingItem(bool isLeft_, const nim::UserNameCard &nameCard, bool showName, QWidget *parent) :
        userNameCard(nameCard), isLeft(isLeft_), showName(showName), QWidget(parent) {

    InitControl();
    SetConnect();
    SetLayout();
}

ChattingItem::~ChattingItem() {
//    qDebug() << "[info]: In ~ChattingItem ...";
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
    messageContentLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    messageContentLabel->setMaximumWidth(500);
    messageContentLabel->setContentsMargins(20, 10, 20, 10);
    messageContentLabel->setWordWrap(true);         // 设置自动换行
    messageContentLabel->setStyleSheet("color:black;"
                                       "font-size: 18px;"
                                       "background: #e1e6eb;"
                                       "border-radius: 8px;");
//    qDebug() << "messageContentLabel size : " << messageContentLabel->size();
//    qDebug() << "messageContentLabel size : " << messageContentLabel->sizeHint();

    nameLabel = new QLabel("用户名");
    nameLabel->setStyleSheet("color:black;"
                             "font-size: 14px;");
    updateUserName();

    headPhotoLabel = new ClickableLabel();
    headPhotoLabel->setCursor(QCursor(Qt::PointingHandCursor));
    headPhotoLabel->setFixedSize(40, 40);
    updateHeaderPhotoIcon();

}

void ChattingItem::SetConnect() {
    // 点击聊天消息的头像显示信息槽函数
    connect(headPhotoLabel, &ClickableLabel::clicked, this, &ChattingItem::ClickedHeaderPhotoLabelSlot);
}

void ChattingItem::SetLayout() {

    auto *vLayout = new QVBoxLayout();
    vLayout->addWidget(nameLabel);
    vLayout->addWidget(messageContentLabel);

    auto *hLayout = new QHBoxLayout();
    if(isLeft) {
        // 别人发送的消息
        hLayout->addWidget(headPhotoLabel);
        hLayout->addLayout(vLayout);
        //hLayout->addWidget(messageContentLabel);
        hLayout->addStretch();
    } else {
        // 自己发送的消息
        hLayout->addStretch();
        hLayout->addLayout(vLayout);
        //hLayout->addWidget(messageContentLabel);
        hLayout->addWidget(headPhotoLabel);
        nameLabel->setVisible(false);
    }
    setLayout(hLayout);
}

void ChattingItem::updateUserName() {
    if(showName) {
        if(!userNameCard.GetName().empty()) {
            nameLabel->setText(QString::fromStdString(userNameCard.GetName()));
        } else {
            nameLabel->setText(QString::fromStdString(userNameCard.GetAccId()));
        }
    } else {
        nameLabel->setVisible(false);
    }
}

// 更新消息的头像图标
void ChattingItem::updateHeaderPhotoIcon() {
    QPixmap map(QString::fromStdString(userNameCard.GetIconUrl()));
    if (map.isNull()) {
        // 头像加载失败
        map.load(":/default_header/dh1");
    }
    headPhotoLabel->setPixmap(PixmapToRound(map.scaled(headPhotoLabel->size()), headPhotoLabel->height()/2));
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

// 点击聊天消息的头像显示信息槽函数
void ChattingItem::ClickedHeaderPhotoLabelSlot() {
    // 发送信号提示显示用户的名片信息。ChattingWindow::ShowHeaderPhotoLabelSlot
    emit ShowHeaderPhotoLabelSignal(userNameCard);
}
