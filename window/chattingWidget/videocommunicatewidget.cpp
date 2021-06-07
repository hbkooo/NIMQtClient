//
// Created by 19216 on 2021/6/7.
//

#include "videocommunicatewidget.h"


VideoCommunicateWidget::VideoCommunicateWidget(QWidget *parent) :
        QWidget(parent) {

    // 初始化界面效果
    InitControl();
    SetLayout();
    SetConnect();

    neRtcEngine = std::make_shared<NERtcEngine>();
    JoinChannel();
}

VideoCommunicateWidget::~VideoCommunicateWidget() {

}

void VideoCommunicateWidget::InitControl() {
    InitVideoWidgetList();
}

void VideoCommunicateWidget::SetLayout() {

}

void VideoCommunicateWidget::SetConnect() {

}

void VideoCommunicateWidget::InitVideoWidgetList() {
    auto *videoWidget1 = new VideoWidget(this);
    videoWidget1->setMinimumSize(160, 90);
    videoWidgetList.append(videoWidget1);
}

void VideoCommunicateWidget::JoinChannel() {

    if(!neRtcEngine->getIsInit()) {
        if(!neRtcEngine->init(QString::fromStdString(app_key))) {
            qDebug() << "[error]: Failed to initialize NERtc engine! NERtc SDK can't work!";
            return ;
        }
    }

    setWindowFlags(Qt::Window);
    this->showNormal();
    this->resize(1184, 666);

    // 设置自己的渲染窗口
    void *hwnd = videoWidgetList[0]->getVideoHwnd();
    neRtcEngine->setupLocalVideo(hwnd);



}



