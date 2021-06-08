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
#include <QDebug>

#include "client.h"
#include "util/util.h"

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
    // 获取该视频显示的用户信息
    const nim::UserNameCard & getUserNameCard() const { return userNameCard; }
    // 设置是否打开麦克风
    void setIsOpenAudio(bool open);
    // 设置是否打开摄像头
    void setIsOpenVideo(bool open);
    // 设置是否打开听筒
    void setIsOpenVoice(bool open);

private:
    void InitControl();
    // 更新关闭摄像头时显示的内容，包括头像和用户名
    void updateCloseVideoWidgetContent();

private:
    // 界面栈，主要存两个界面栈，一个是用户关闭摄像头时显示的界面；一个是当用户打开摄像头时显示的界面。
    QStackedWidget *stackedWidget;
    // 摄像头打开时的界面
    QWidget *videoContentWidget;
    // 摄像头关闭时的界面
    QLabel *headerPhotoLabel;       // 关闭摄像头时显示用户的头像
    QLabel *userNameLabel;          // 关闭摄像头时显示用户名
    QWidget *closeContentWidget;    // 关闭摄像头时的整体界面

private:

    QWidget *videoRender;

    nim::UserNameCard userNameCard;


};


#endif //NIMQTCLIENT_VIDEOWIDGET_H
