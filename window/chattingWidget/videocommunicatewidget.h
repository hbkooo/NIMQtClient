//
// Created by 19216 on 2021/6/7.
//

#ifndef NIMQTCLIENT_VIDEOCOMMUNICATEWIDGET_H
#define NIMQTCLIENT_VIDEOCOMMUNICATEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QStyle>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>

#include "rtc/NERtcEngine.h"
#include "videowidget.h"
#include "util/clickablelabel.h"


class VideoCommunicateWidget : public QWidget {
Q_OBJECT

public:
    explicit VideoCommunicateWidget(QString roomName, QWidget *parent = nullptr);

    ~VideoCommunicateWidget() override;

    void AddOneVideoCom(uid_t uid, const nim::UserNameCard &nameCard);

private:
    void InitControl();
    void SetConnect();

private:
    void JoinChannel();

private:

    // 获取服务器用户信息
    void GetUserNameCardOnLine(uid_t uid, const std::string & account);

private:

    VideoWidget *myVideoWidget{};         // 不创建这个对象，只是创建一个指向自己视频界面的指针
    VideoWidget *mainVideoWidget{};       // 中间显示的视频界面
    QHBoxLayout *videoWidgetLayout{};     // 其他好友视频界面布局

    ClickableLabel *audioLabel{};         // 是否开启语音按钮
    ClickableLabel *voiceLabel{};         // 是否关闭扬声器按钮
    ClickableLabel *videoLabel{};         // 是否开启视频按钮
    QPushButton *hangupButton{};          // 挂断通话按钮

private:

    // 视频通话管理引擎
    std::shared_ptr<NERtcEngine> neRtcEngine;

    QList<VideoWidget*> videoWidgetList;        // 所有的聊天视频窗口
    QList<nim::UserNameCard> userNameCards;     // P2P聊天用户
    QMap<uid_t, QString> chattingUserInfo;      // 加入聊天的用户 uid 和其对应的用户名
    uid_t my_uid;                               // 自己的 uid
    QString chatRoomName;                       // 聊天房间名称

    signals:
    // 关闭窗口信号
    void CloseVideoWidgetSignal();
    // 新加入一个聊天用户，查询该用户的 userCard 后插入到聊天界面中
    void AddOneUserNameCardVideoSignal(uid_t uid, const nim::UserNameCard &nameCard);

public slots:
    // 点击挂断按钮槽函数
    void ClickHangupSlot();
    // 点击关闭语音麦按钮、是否关闭视频按钮、是否关闭声音按钮槽函数
    void ClickAudioVideoVoiceLabelSlot();
    // 自己加入聊天房间成功
    void OnJoinChannelSuccessSlot(uid_t uid);
    // 自己加入聊天房间失败
    void OnJoinChannelFailSlot(uid_t uid, const QString &reason);
    // 自己离开聊天房间
    void OnLeaveChannelSlot();
    // 远程用户的视频流 开启/关闭 状态变化
    void ChangedOfUserVideoSlot(uid_t uid, bool status);
    // 远程用户的语音流 开启/关闭 状态变化
    void ChangedOfUserAudioSlot(uid_t uid, bool status);
    // 新的聊天用户添加进来
    void OnUserJoinedSlot(uid_t uid, const QString& name);
    // 聊天用户离开
    void OnUserLeftSlot(uid_t uid);
};


#endif //NIMQTCLIENT_VIDEOCOMMUNICATEWIDGET_H
