//
// Created by 19216 on 2021/6/7.
//

// You may need to build the project (run Qt uic code generator) to get "ui_VideoWidget.h" resolved

#include "videowidget.h"


VideoWidget::VideoWidget(QWidget *parent) :
        QWidget(parent) {

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

    videoContentWidget = new QWidget();
    videoContentWidget->setObjectName("videoContentWidget");
    videoContentWidget->setStyleSheet("QWidget#videoContentWidget{"
                                    "border:1px solid #292933;"
                                    "background-color: #292933;"
                                    "}");

    closeContentWidget = new QWidget();
    closeContentWidget->setStyleSheet("background: red;");

    stackedWidget = new QStackedWidget();
    stackedWidget->addWidget(closeContentWidget);
    stackedWidget->addWidget(videoContentWidget);

    // 默认关闭摄像头
    stackedWidget->setCurrentIndex(0);

    auto *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(stackedWidget);
    this->setLayout(mainLayout);
}

//获取窗口句柄
void *VideoWidget::getVideoHwnd() {
    return (void *) videoRender->winId();
}

// 设置该视频显示的用户信息
void VideoWidget::setUserNameCard(const nim::UserNameCard &nameCard) {
    userNameCard = nameCard;
}

