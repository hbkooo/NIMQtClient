//
// Created by 19216 on 2021/6/7.
//

#include "videocommunicatewidget.h"


VideoCommunicateWidget::VideoCommunicateWidget(QWidget *parent) :
        QWidget(parent) {

    setStyleSheet("background:black;");
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

    myVideoWidget = new VideoWidget();
    otherVideoWidget = new VideoWidget();

    QSize size1(28, 28);

    audioLabel = new ClickableLabel("");
    audioLabel->setStyleSheet(
            // 自定义checked属性，根据设置的不同属性值显示不同的css样式
            "QLabel[open=true] {"
            "border-image:url(:/res/open_audio) 4 4 4 4 stretch stretch;}"
            "QLabel[open=false] {"
            "border-image:url(:/res/close_audio) 4 4 4 4 stretch stretch;}");
    audioLabel->setFixedSize(size1);
    audioLabel->setProperty("open", true);
    connect(audioLabel, &ClickableLabel::clicked, this, [this]() {
        auto label = (ClickableLabel *) sender();
        label->setProperty("open", !(label->property("open").toBool()));
        label->style()->polish(label);
    });

    voiceLabel = new ClickableLabel("");
    voiceLabel->setStyleSheet("QLabel[open=true] {"
                              "border-image:url(:/res/open_voice) 4 4 4 4 stretch stretch;}"
                              "QLabel[open=false] {"
                              "border-image:url(:/res/close_voice) 4 4 4 4 stretch stretch;}");

    voiceLabel->setFixedSize(size1);
    voiceLabel->setProperty("open", true);
    connect(voiceLabel, &ClickableLabel::clicked, this, [this]() {
        auto label = (ClickableLabel *) sender();
        label->setProperty("open", !(label->property("open").toBool()));
        label->style()->polish(label);
    });

    videoLabel = new ClickableLabel("");
    videoLabel->setStyleSheet("QLabel[open=true] {"
                              "border-image:url(:/res/open_video) 4 4 4 4 stretch stretch;}"
                              "QLabel[open=false] {"
                              "border-image:url(:/res/close_video) 4 4 4 4 stretch stretch;}");

    videoLabel->setFixedSize(size1);
    videoLabel->setProperty("open", true);
    connect(videoLabel, &ClickableLabel::clicked, this, [this]() {
        auto label = (ClickableLabel *) sender();
        label->setProperty("open", !(label->property("open").toBool()));
        label->style()->polish(label);
    });

    auto *hLayout = new QHBoxLayout();
    hLayout->addWidget(audioLabel);
    hLayout->addWidget(voiceLabel);
    hLayout->addWidget(videoLabel);
    hLayout->addStretch();

    auto *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(myVideoWidget);
    mainLayout->addLayout(hLayout);
    setLayout(mainLayout);

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

    if (!neRtcEngine->getIsInit()) {
        if (!neRtcEngine->init(QString::fromStdString(app_key))) {
            qDebug() << "[error]: Failed to initialize NERtc engine! NERtc SDK can't work!";
            return;
        }
    }

    setWindowFlags(Qt::Window);
    this->showNormal();
    this->resize(1184, 666);

    // 设置自己的渲染窗口
    void *hwnd = videoWidgetList[0]->getVideoHwnd();
    neRtcEngine->setupLocalVideo(hwnd);


}



