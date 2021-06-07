//
// Created by 19216 on 2021/6/7.
//

#ifndef NIMQTCLIENT_VIDEOWIDGET_H
#define NIMQTCLIENT_VIDEOWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "client.h"

/**
 * VideoWidget 有两个状态。当用户打开摄像头时显示视频；当用户关闭摄像头时显示用户信息
 */
class VideoWidget : public QWidget {
Q_OBJECT

public:
    explicit VideoWidget(QWidget *parent = nullptr);

    ~VideoWidget() override;

    //获取窗口句柄
    void* getVideoHwnd();
    // 设置该视频显示的用户信息
    void setUserNameCard(const nim::UserNameCard &nameCard);

private:
    void InitControl();

private:
    // 界面栈，主要存两个界面栈，一个是当用户打开摄像头时显示的界面；一个是用户关闭摄像头时显示的界面
    QStackedWidget *stackedWidget;
    // 摄像头打开时的界面
    QWidget *videoContentWidget;
    // 摄像头关闭时的界面
    QWidget *closeContentWidget;

private:

    QWidget *videoRender;

    nim::UserNameCard userNameCard;


};


#endif //NIMQTCLIENT_VIDEOWIDGET_H
