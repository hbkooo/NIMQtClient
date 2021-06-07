//
// Created by 19216 on 2021/6/7.
//

#ifndef NIMQTCLIENT_VIDEOCOMMUNICATEWIDGET_H
#define NIMQTCLIENT_VIDEOCOMMUNICATEWIDGET_H

#include <QWidget>

#include "rtc/NERtcEngine.h"
#include "videowidget.h"


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

    // 视频通话管理引擎
    std::shared_ptr<NERtcEngine> neRtcEngine;

    QList<VideoWidget*> videoWidgetList;        // 所有已经加入聊天的视频窗口

};


#endif //NIMQTCLIENT_VIDEOCOMMUNICATEWIDGET_H
