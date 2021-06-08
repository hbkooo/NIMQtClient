//
// Created by 19216 on 2021/6/7.
//

#include "videocommunicatewidget.h"

#include <utility>


VideoCommunicateWidget::VideoCommunicateWidget(QString roomName, QWidget *parent) :
        my_uid(1), chatRoomName(std::move(roomName)), QWidget(parent) {
    qDebug() << "[info]: " << __FUNCTION__ ;
    setStyleSheet("background:black;");
    setMinimumSize(600, 500);
    setAttribute(Qt::WA_DeleteOnClose);     // 设置调用close()方法释放资源，即之后调用析构函数

    neRtcEngine = std::make_shared<NERtcEngine>();

    // 初始化界面效果
    InitControl();
    SetConnect();
    JoinChannel();
}

VideoCommunicateWidget::~VideoCommunicateWidget() {
    qDebug() << "[info]: In " << __FUNCTION__ ;
    emit CloseVideoWidgetSignal();
}

void VideoCommunicateWidget::AddOneVideoCom(uid_t uid, const nim::UserNameCard &nameCard) {
    auto *otherVideo = new VideoWidget();
    otherVideo->setMinimumSize(100, 90);
    otherVideo->setMaximumSize(200, 150);
    otherVideo->setUserNameCard(nameCard);
    neRtcEngine->setupRemoteVideo(uid, otherVideo->getVideoHwnd());
    chattingUserInfo[uid] = QString::fromStdString(nameCard.GetAccId());
    userNameCards.append(nameCard);
    videoWidgetLayout->addWidget(otherVideo);
}

void VideoCommunicateWidget::InitControl() {
    mainVideoWidget = new VideoWidget();
    mainVideoWidget->setUserNameCard(SELF_USER_NAME_CARD);
    mainVideoWidget->setMinimumSize(400, 300);
    myVideoWidget = mainVideoWidget;        // 刚开始默认自己的视频界面显示到中间主界面中
    myVideoWidget->setIsOpenVideo(true);

    videoWidgetLayout = new QHBoxLayout();
    videoWidgetLayout->addStretch();

    QSize labelSize(24, 24);
    audioLabel = new ClickableLabel("");
    audioLabel->setObjectName("audio");
    audioLabel->setStyleSheet(
            // 自定义checked属性，根据设置的不同属性值显示不同的css样式
            "QLabel[open=true] {"
            "border-image:url(:/res/open_audio) 4 4 4 4 stretch stretch;}"
            "QLabel[open=false] {"
            "border-image:url(:/res/close_audio) 4 4 4 4 stretch stretch;}");
    audioLabel->setFixedSize(labelSize);
    audioLabel->setProperty("open", true);

    voiceLabel = new ClickableLabel("");
    voiceLabel->setObjectName("voice");
    voiceLabel->setStyleSheet("QLabel[open=true] {"
                              "border-image:url(:/res/open_voice) 4 4 4 4 stretch stretch;}"
                              "QLabel[open=false] {"
                              "border-image:url(:/res/close_voice) 4 4 4 4 stretch stretch;}");
    voiceLabel->setFixedSize(labelSize);
    voiceLabel->setProperty("open", true);

    videoLabel = new ClickableLabel("");
    videoLabel->setObjectName("video");
    videoLabel->setStyleSheet("QLabel[open=true] {"
                              "border-image:url(:/res/open_video) 4 4 4 4 stretch stretch;}"
                              "QLabel[open=false] {"
                              "border-image:url(:/res/close_video) 4 4 4 4 stretch stretch;}");

    videoLabel->setFixedSize(labelSize);
    videoLabel->setProperty("open", true);

    hangupButton = new QPushButton("挂断");
    hangupButton->setFixedSize(90, 30);
    hangupButton->setStyleSheet("QPushButton { font-size:20px;"
                                "color:white;"
                                "border: none;"
                                "border-radius: 3px;"
                                "background-color:#D81E06;}"// DA4F47
                                "QPushButton:hover {"
                                "background-color:#F3564D;}"
                                "QPushButton:pressed {"
                                "background-color:#C4413A;}"
                                "QPushButton:focus{outline: none;}");

    // 下方是否关闭语音麦按钮、是否关闭视频按钮、是否关闭声音按钮、挂断通话按钮布局
    auto *toolLayout = new QHBoxLayout();
    toolLayout->addWidget(audioLabel);
    toolLayout->addSpacing(4);
    toolLayout->addWidget(voiceLabel);
    toolLayout->addSpacing(8);
    toolLayout->addWidget(videoLabel);
    toolLayout->addStretch();
    toolLayout->addWidget(hangupButton);

    auto *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(mainVideoWidget);
    mainLayout->addLayout(videoWidgetLayout);
    mainLayout->addLayout(toolLayout);
    setLayout(mainLayout);

}

void VideoCommunicateWidget::SetConnect() {
    // 主要是当有新的用户加入时，首先查询该用户的 userNameCard，查找到后再加入 video 界面
    connect(this, &VideoCommunicateWidget::AddOneUserNameCardVideoSignal,
            this, &VideoCommunicateWidget::AddOneVideoCom);

    // 点击关闭语音麦按钮、是否关闭视频按钮、是否关闭声音按钮槽函数
    connect(audioLabel, &ClickableLabel::clicked, this, &VideoCommunicateWidget::ClickAudioVideoVoiceLabelSlot);
    connect(voiceLabel, &ClickableLabel::clicked, this, &VideoCommunicateWidget::ClickAudioVideoVoiceLabelSlot);
    connect(videoLabel, &ClickableLabel::clicked, this, &VideoCommunicateWidget::ClickAudioVideoVoiceLabelSlot);
    // 挂断通话按钮
    connect(hangupButton, &QPushButton::clicked, this, &VideoCommunicateWidget::ClickHangupSlot);

    // 自己加入聊天房间成功
    connect(neRtcEngine.get(), &NERtcEngine::OnJoinChannelSuccessSignal,
            this, &VideoCommunicateWidget::OnJoinChannelSuccessSlot);
    // 自己加入聊天房间失败
    connect(neRtcEngine.get(), &NERtcEngine::OnJoinChannelFailSignal,
            this, &VideoCommunicateWidget::OnJoinChannelFailSlot);
    // 自己离开聊天房间
    connect(neRtcEngine.get(), &NERtcEngine::OnLeaveChannelSignal,
            this, &VideoCommunicateWidget::OnLeaveChannelSlot);
    // 远程用户的视频流 开启/关闭 信号回调
    connect(neRtcEngine.get(), &NERtcEngine::ChangedOfUserVideoSignal,
            this, &VideoCommunicateWidget::ChangedOfUserVideoSlot);
    // 远程用户的语音流 开启/关闭 信号回调
    connect(neRtcEngine.get(), &NERtcEngine::ChangedOfUserAudioSignal,
            this, &VideoCommunicateWidget::ChangedOfUserAudioSlot);
    // 新的聊天用户添加进来
    connect(neRtcEngine.get(), &NERtcEngine::OnUserJoinedSignal,
            this, &VideoCommunicateWidget::OnUserJoinedSlot);
    // 聊天用户离开
    connect(neRtcEngine.get(), &NERtcEngine::OnUserLeftSignal,
            this, &VideoCommunicateWidget::OnUserLeftSlot);

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

    // 设置自己的渲染窗口
    void *hwnd = myVideoWidget->getVideoHwnd();
    neRtcEngine->setupLocalVideo(hwnd);

    // 加入房间。会有回调结果 NEEventHandler::onJoinChannel
    neRtcEngine->joinChannel("", chatRoomName, QString::number(my_uid));
    chattingUserInfo[my_uid] = QString::fromStdString(SELF_USER_NAME_CARD.GetAccId());

}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void VideoCommunicateWidget::GetUserNameCardOnLine(uid_t uid, const std::string &account) {
    std::list<std::string> account_list;
    account_list.push_back(account);
    qDebug() << "[info]: In " << __FUNCTION__ << ", query account: " << QString::fromStdString(account);
    nim::User::GetUserNameCardOnline(account_list, [this, &uid, &account](const std::list<nim::UserNameCard> &json_result) {
        nim::UserNameCard nameCard;
        if (json_result.empty()) {
            // 如果返回的查询数据为空，说明系统里不存在该用户，即查询的 accID 是错误的。
            nameCard.SetAccId(account);
            qDebug() << "[error]: not found account : " << QString::fromStdString(account);
        } else {
            nameCard = json_result.front();
            qDebug() << "[info]: found account : " << QString::fromStdString(account);
        }
        emit AddOneUserNameCardVideoSignal(uid, nameCard);       // VideoCommunicateWidget::AddOneVideoCom
    });
}
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

// 点击挂断按钮槽函数
void VideoCommunicateWidget::ClickHangupSlot() {
    qDebug() << "[info]: 挂断通话 ...";
    // TODO 释放各种聊天视频资源
    // 退出聊天，之后会有回调结果到 NEEventHandler::onLeaveChannel
    neRtcEngine->leaveChannel();
    close();        // 关闭窗口
}

// 点击关闭语音麦按钮、是否关闭视频按钮、是否关闭声音按钮槽函数
void VideoCommunicateWidget::ClickAudioVideoVoiceLabelSlot() {
    auto label = (ClickableLabel *) sender();
    label->setProperty("open", !(label->property("open").toBool()));
    label->style()->polish(label);
    auto objectName = label->objectName();
    bool open = label->property("open").toBool();
    if(objectName == "audio") {
        // 开启或关闭语音麦
        myVideoWidget->setIsOpenAudio(open);
        neRtcEngine->enableAudio(open);
    } else if(objectName == "voice") {
        // 开启或关闭声音
        myVideoWidget->setIsOpenVoice(open);
        neRtcEngine->enableVoice(open);
    } else if(objectName == "video") {
        // 开启或关闭视频
        myVideoWidget->setIsOpenVideo(open);
        neRtcEngine->enableVideo(open);
    }
}

// 自己加入聊天房间成功
void VideoCommunicateWidget::OnJoinChannelSuccessSlot(uid_t uid) {

}

// 自己加入聊天房间失败
void VideoCommunicateWidget::OnJoinChannelFailSlot(uid_t uid, const QString &reason) {

}

// 自己离开聊天房间
void VideoCommunicateWidget::OnLeaveChannelSlot() {
    neRtcEngine->setupLocalVideo(nullptr);
}

// 远程用户的视频流 开启/关闭 状态变化
void VideoCommunicateWidget::ChangedOfUserVideoSlot(uid_t uid, bool status) {
    // 如果远程用户开启了视频流。这里没有考虑关闭的状态，即是关闭了，客户端并没有取消订阅视频流
    if(status) {
        neRtcEngine->startSubscribeRemoteUserVideoStream(uid);
    }

    for(auto video: videoWidgetList) {
        if(QString::fromStdString(video->getUserNameCard().GetAccId()) == QString::number(uid)) {
            video->setIsOpenVideo(status);
        }
    }

}

// 远程用户的语音流 开启/关闭 状态变化
void VideoCommunicateWidget::ChangedOfUserAudioSlot(uid_t uid, bool status) {
    // 如果远程用户开启了语音流。这里没有考虑关闭的状态，即是关闭了，客户端并没有取消订阅语音流
    if(status) {
        neRtcEngine->startSubscribeRemoteUserAudioStream(uid);
    }


}

// 新的聊天用户添加进来
void VideoCommunicateWidget::OnUserJoinedSlot(uid_t uid, const QString& name) {
    qDebug() << "[info]: In " << __FUNCTION__  << ", uid: " << uid << ", name : " << name;
    chattingUserInfo.insert(uid, name);
    GetUserNameCardOnLine(uid, name.toStdString());
}

// 聊天用户离开
void VideoCommunicateWidget::OnUserLeftSlot(uid_t uid) {
    QString accID = chattingUserInfo[uid];
    for(int i = 0; i < userNameCards.count(); ++i) {
        if(accID.toStdString() == userNameCards[i].GetAccId()) {
            userNameCards.removeAt(i);
            break;
        }
    }
    for(int i = 0; i < videoWidgetList.count(); ++i) {
        auto *videoWidget = videoWidgetList[i];
        if(accID.toStdString() == videoWidget->getUserNameCard().GetAccId()) {
            videoWidgetList.removeAt(i);
            //videoWidgetLayout->removeWidget(videoWidget);
            //delete videoWidget;
        }
    }
}



