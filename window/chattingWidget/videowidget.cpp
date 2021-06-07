//
// Created by 19216 on 2021/6/7.
//

// You may need to build the project (run Qt uic code generator) to get "ui_VideoWidget.h" resolved

#include "videowidget.h"


VideoWidget::VideoWidget(QWidget *parent) :
        QWidget(parent) {

    InitControl();

    videoRender = new QWidget(videoContentView);
    videoRender->setStyleSheet("QWidget{background-color: #292933;}");
//    videoRender->stackUnder(ui->frame);
//    videoRender->stackUnder(ui->btnZoom);
    videoRender->setVisible(false);

}

VideoWidget::~VideoWidget() {

}

void VideoWidget::InitControl() {

    videoContentView = new QWidget();
    videoContentView->setObjectName("videoContentView");
    videoContentView->setStyleSheet("QWidget#videoContentView{"
                                    "border:1px solid #292933;"
                                    "background-color: #292933;"
                                    "}");

}

//获取窗口句柄
void *VideoWidget::getVideoHwnd() {
    return (void *) videoRender->winId();
}

