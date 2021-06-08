//
// Created by 19216 on 2021/6/7.
//

// You may need to build the project (run Qt uic code generator) to get "ui_VideoWidget.h" resolved

#include "videowidget.h"


VideoWidget::VideoWidget(QWidget *parent) :
        QWidget(parent) {

//    setMinimumSize(500, 400);
    InitControl();

    videoRender = new QWidget(videoContentWidget);
    videoRender->setStyleSheet("QWidget{background-color: #292933;}");
//    videoRender->stackUnder(ui->frame);
//    videoRender->stackUnder(ui->btnZoom);
    videoRender->setVisible(false);

}

VideoWidget::~VideoWidget() {

}

void VideoWidget::InitControl() {

    // 开启摄像头显示视频界面
    videoContentWidget = new QWidget();
    videoContentWidget->setObjectName("videoContentWidget");
    videoContentWidget->setStyleSheet("QWidget#videoContentWidget{"
                                    "border:1px solid #292933;"
                                    "background-color: #292933;"
                                    "}");

    // 关闭摄像头显示的界面
    headerPhotoLabel = new QLabel("头像");
    userNameLabel = new QLabel("用户名");
    userNameLabel->setStyleSheet("font-weight: bold;");
    auto *vLayout = new QVBoxLayout();
    vLayout->addStretch();
    vLayout->addWidget(headerPhotoLabel, 0, Qt::AlignHCenter);
    vLayout->addSpacing(8);
    vLayout->addWidget(userNameLabel, 0, Qt::AlignHCenter);
    vLayout->addStretch();
    closeContentWidget = new QWidget();
    closeContentWidget->setStyleSheet("background: #3C4147;");
    closeContentWidget->setLayout(vLayout);

    stackedWidget = new QStackedWidget();
    stackedWidget->addWidget(closeContentWidget);
    stackedWidget->addWidget(videoContentWidget);

    // 默认关闭摄像头
    stackedWidget->setCurrentIndex(0);

    auto *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(stackedWidget);
    this->setLayout(mainLayout);
}

// 更新关闭摄像头时显示的内容，包括头像和用户名
void VideoWidget::updateCloseVideoWidgetContent() {
    if (userNameCard.GetIconUrl().empty()) {
        userNameCard.SetIconUrl(":/default_header/dh9");
    }
    QPixmap map(QString::fromStdString(SELF_USER_NAME_CARD.GetIconUrl()));
    if (map.isNull()) {
        // 头像加载失败
        map.load(":/default_header/dh9");
    }
    auto widgetSize = this->size();
    headerPhotoLabel->setPixmap(
            PixmapToRound(
                    map.scaled(widgetSize.width()/3, widgetSize.height()/3),
                    widgetSize.height()/3 / 2)
    );
    // 更新用户昵称
    if (!userNameCard.GetName().empty()) {
        userNameLabel->setText(QString::fromStdString(userNameCard.GetName()));
    } else {
        userNameLabel->setText(QString::fromStdString(userNameCard.GetAccId()));
    }
}

//获取窗口句柄
void *VideoWidget::getVideoHwnd() {
    return (void *) videoRender->winId();
}

// 设置该视频显示的用户信息
void VideoWidget::setUserNameCard(const nim::UserNameCard &nameCard) {
    userNameCard = nameCard;
    updateCloseVideoWidgetContent();
}

// 设置是否打开麦克风
void VideoWidget::setIsOpenAudio(bool open) {

}

// 设置是否打开摄像头
void VideoWidget::setIsOpenVideo(bool open) {
    // 界面栈，主要存两个界面栈，一个是用户关闭摄像头时显示的界面；一个是当用户打开摄像头时显示的界面。
    if(open) {
        // 打开摄像头
        stackedWidget->setCurrentIndex(1);
    } else {
        // 关闭摄像头
        stackedWidget->setCurrentIndex(0);
    }
}

// 设置是否打开听筒
void VideoWidget::setIsOpenVoice(bool open) {

}

