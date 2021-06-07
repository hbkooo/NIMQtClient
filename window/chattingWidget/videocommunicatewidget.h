//
// Created by 19216 on 2021/6/7.
//

#ifndef NIMQTCLIENT_VIDEOCOMMUNICATEWIDGET_H
#define NIMQTCLIENT_VIDEOCOMMUNICATEWIDGET_H

#include <QLabel>
#include <QStyle>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>

#include "rtc/NERtcEngine.h"
#include "videowidget.h"
#include "util/clickablelabel.h"


class VideoCommunicateWidget : public QWidget {
Q_OBJECT

public:
    explicit VideoCommunicateWidget(QWidget *parent = nullptr);

    ~VideoCommunicateWidget() override;

private:
    void InitControl();
    void SetLayout();
    void SetConnect();

    void InitVideoWidgetList();

private:
    void JoinChannel();

private:

    VideoWidget *myVideoWidget;         // 中间显示的视频界面
    VideoWidget *otherVideoWidget;      // 其他好友视频界面

    ClickableLabel *audioLabel;         // 是否开启语音按钮
    ClickableLabel *voiceLabel;         // 是否关闭扬声器按钮
    ClickableLabel *videoLabel;         // 是否开启视频按钮

private:

    // 视频通话管理引擎
    std::shared_ptr<NERtcEngine> neRtcEngine;

    QList<VideoWidget*> videoWidgetList;        // 所有已经加入聊天的视频窗口

};


#endif //NIMQTCLIENT_VIDEOCOMMUNICATEWIDGET_H
