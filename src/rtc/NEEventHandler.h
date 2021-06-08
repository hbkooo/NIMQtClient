//
// Created by 19216 on 2021/6/7.
//

#ifndef NIMQTCLIENT_NEEVENTHANDLER_H
#define NIMQTCLIENT_NEEVENTHANDLER_H

#include <QObject>
#include <QPointer>

#include "nertc_base.h"
#include "nertc_engine_ex.h"
#include "nertc_engine_event_handler_ex.h"

using namespace nertc;

class NERtcEngine;

class NEEventHandler : public QObject, public IRtcEngineEventHandlerEx{
Q_OBJECT

public:
    explicit NEEventHandler(NERtcEngine *engine);

    ~NEEventHandler() = default;

    // 加入房间回调，表示客户端已经登入服务器。
    void onJoinChannel(channel_id_t cid, nertc::uid_t uid, NERtcErrorCode result, uint64_t elapsed) override;
    // 用户离开房间回调。
    void onLeaveChannel(NERtcErrorCode result) override;
    // 监听远端用户加入通话房间的事件，并抛出对方的 uid。
    void onUserJoined(uid_t uid, const char *user_name) override;
    // 远端用户离开当前房间的回调。
    void onUserLeft(nertc::uid_t uid, NERtcSessionLeaveReason reason) override;
    // 远端用户开启视频的回调。
    void onUserVideoStart(uid_t uid, NERtcVideoProfileType max_profile) override;
    // 远端用户停用视频的回调。
    void onUserVideoStop(uid_t uid) override;
    // 远端用户开启语音的回调。
    void onUserAudioStart(uid_t uid) override;
    // 远端用户关闭语音的回调
    void onUserAudioStop(uid_t uid) override;


private:
    NERtcEngine* neRtcEngine;
};


#endif //NIMQTCLIENT_NEEVENTHANDLER_H
