//
// Created by 19216 on 2021/6/2.
//

#include "frienditem.h"

FriendItem::FriendItem(nim::UserNameCard nameCard, QWidget *parent) :
        userNameCard(std::move(nameCard)), QWidget(parent) {

    this->setFixedHeight(68);               // 头像高40 + 上边界10 + 下边界10
    this->setStyleSheet("background:transparent;"); //只有设置了透明背景之后在hover的时候背景才可以看到，不然该item中的控件背景还是白色的

    InitControl();
    SetLayout();

}

FriendItem::~FriendItem() {
    qDebug() << "[info]: In FriendItem::~FriendItem";
}

void FriendItem::InitControl() {
// 用户头像
    header_label = new QLabel("头像");
    header_label->setFixedSize(48, 48);
    if (userNameCard.GetIconUrl().empty()) {
        userNameCard.SetIconUrl(":/default_header/dh1");
    }
    QPixmap map(QString::fromStdString(userNameCard.GetIconUrl()));
    if (map.isNull()) {
        // 头像加载失败
        map.load(":/default_header/dh1");
    }
    map = PixmapToRound(map.scaled(header_label->size()), 24);
    header_label->setPixmap(map);

    // 创建用户姓名标签
    name_label = new QLabel("用户名字");
    name_label->setStyleSheet("font-size:20px;");
    name_label->adjustSize();
    if(userNameCard.GetName().empty()) {
        name_label->setText(QString::fromStdString(userNameCard.GetAccId()));
    } else {
        name_label->setText(QString::fromStdString(userNameCard.GetName()));
    }


    // 创建最后一条聊天消息标签
    signature_label = new QLabel("签名");
    signature_label->setStyleSheet("font-size:14px;"
                                  "color:#6f6a6d");
    signature_label->setFixedHeight(14);
    signature_label->setText(QString::fromStdString(userNameCard.GetSignature()));

}

void FriendItem::SetLayout() {

    // 一个竖直布局包括上面的用户名时间布局和下面的最后一条消息控件
    auto *vLayout = new QVBoxLayout();
    vLayout->setSpacing(0);
    vLayout->setMargin(0);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->addStretch();
    vLayout->addWidget(name_label);
    vLayout->addSpacing(6);
    vLayout->addWidget(signature_label);
    vLayout->addStretch();

    // 最终的主布局包括左边的用户头像和上面的剩下的布局
    main_layout = new QHBoxLayout();
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->setMargin(0);
    main_layout->addSpacing(16);
    main_layout->addWidget(header_label, 0, Qt::AlignVCenter);
    main_layout->addSpacing(8);
    main_layout->addLayout(vLayout);
    main_layout->addSpacing(16);

    setLayout(main_layout);
}

void FriendItem::update(const nim::UserNameCard &nameCard) {

    userNameCard = nameCard;

    if (userNameCard.GetIconUrl().empty()) {
        userNameCard.SetIconUrl(":/default_header/dh1");
    }
    QPixmap map(QString::fromStdString(userNameCard.GetIconUrl()));
    if (map.isNull()) {
        // 头像加载失败
        map.load(":/default_header/dh1");
    }
    header_label->setPixmap(PixmapToRound(map.scaled(header_label->size()), 24));

    if(userNameCard.GetName().empty()) {
        name_label->setText(QString::fromStdString(userNameCard.GetAccId()));
    } else {
        name_label->setText(QString::fromStdString(userNameCard.GetName()));
    }
    signature_label->setText(QString::fromStdString(userNameCard.GetSignature()));

}


