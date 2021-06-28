//
// Created by 19216 on 2021/6/7.
//

#ifndef NIMQTCLIENT_NERTCENGINE_H
#define NIMQTCLIENT_NERTCENGINE_H

#include <QObject>
#include <QDebug>

#include "nertc_audio_device_manager.h"
#include "nertc_engine_ex.h"
#include "NEEventHandler.h"
#include "client.h"

class NERtcEngine : public QObject{
Q_OBJECT

public:
    explicit NERtcEngine(QObject *parent = nullptr);

    ~NERtcEngine() override;
    // 释放Rtc
    void release();

    // 初始化Rtc
    bool init(const QString &appKey, const QString &log_dir_path="");

    // 查看是否已经初始化
    bool getIsInit() const { return is_Init; }

    // 设置本地视频渲染窗口
    int setupLocalVideo(void* hwnd);
    // 当新加入新的视频用户时，设置该远端视频渲染窗口
    int setupRemoteVideo(quint64 uid, void* hwnd);
    //加入频道
    int joinChannel(const QString& token, const QString& roomID, const QString& uid);
    //离开频道
    int leaveChannel();

    // 开启/关闭本地话筒
    int enableAudio(bool enabled);
    // 开启/关闭本地听筒
    int enableVoice(bool enabled);
    // 开启/关闭本地摄像头
    int enableVideo(bool enabled);

    // 根据用户 uid 开启订阅该用户的视频流
    void startSubscribeRemoteUserVideoStream(nertc::uid_t uid);
    // 根据用户 uid 关闭订阅该用户的视频流
    void stopSubscribeRemoteUserVideoStream(nertc::uid_t uid);
    // 根据用户 uid 开启订阅该用户的语音流
    void startSubscribeRemoteUserAudioStream(nertc::uid_t uid);
    // 根据用户 uid 关闭订阅该用户的语音流
    void stopSubscribeRemoteUserAudioStream(nertc::uid_t uid);

private:
    // 网易云通信 SDK 引擎
    nertc::IRtcEngineEx* rtcEngine = nullptr;

    // 事件处理器
    std::shared_ptr<NEEventHandler> rtcEngineEventHandler;

    // 是否已经初始化
    bool is_Init;

    signals:
    // 自己加入聊天房间成功
    void OnJoinChannelSuccessSignal(uid_t uid);
    // 自己加入聊天房间失败
    void OnJoinChannelFailSignal(uid_t uid, const QString &reason);
    // 自己离开聊天房间
    void OnLeaveChannelSignal();
    // 远程用户的视频流 开启/关闭 状态变化
    void ChangedOfUserVideoSignal(uid_t uid, bool status);
    // 远程用户的语音流 开启/关闭 状态变化
    void ChangedOfUserAudioSignal(uid_t uid, bool status);
    // 新的聊天用户添加进来
    void OnUserJoinedSignal(uid_t uid, const QString& name);
    // 聊天用户离开
    void OnUserLeftSignal(uid_t uid);

};


#endif //NIMQTCLIENT_NERTCENGINE_H
