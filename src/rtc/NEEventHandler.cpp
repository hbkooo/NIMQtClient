//
// Created by 19216 on 2021/6/7.
//

#include "NEEventHandler.h"
#include "NERtcEngine.h"

NEEventHandler::NEEventHandler(NERtcEngine *engine): neRtcEngine(engine) {

}

void NEEventHandler::onJoinChannel(channel_id_t cid, nertc::uid_t uid, NERtcErrorCode result, uint64_t elapsed) {
    // 这里的回调应该是指自己加入房间之后的回调
    if (neRtcEngine == nullptr) {
        return;
    }
    qDebug() << "[info]: In " << __FUNCTION__  << ", join channel id: " << cid
                << ", uid: " << uid << ", result code: " << result;
    if (result == kNERtcNoError) {
        emit neRtcEngine->OnJoinChannelSuccessSignal(uid);
    } else {
        emit neRtcEngine->OnJoinChannelFailSignal(uid,QString::number(result));
    }
}

void NEEventHandler::onLeaveChannel(NERtcErrorCode result) {
    // 这里的回调是指自己离开房间之后的回调
    if (neRtcEngine == nullptr) {
        return;
    }

    if (result == kNERtcErrChannelKicked) {
        //Q_EMIT neRtcEngine->sigForceOffline();
    } else {
        emit neRtcEngine->OnLeaveChannelSignal();
    }
}

void NEEventHandler::onUserJoined(uid_t uid, const char *user_name) {
    if (neRtcEngine == nullptr) {
        return;
    }
    qDebug() << "[info]: In " << __FUNCTION__  << ", user joined  " << user_name;
    // VideoCommunicateWidget::OnUserJoinedSlot
    emit neRtcEngine->OnUserJoinedSignal(uid, user_name);
}

void NEEventHandler::onUserLeft(nertc::uid_t uid, NERtcSessionLeaveReason reason) {
    if (neRtcEngine == nullptr) {
        return;
    }
    // 聊天用户离开。VideoCommunicateWidget::OnUserLeftSlot
    emit neRtcEngine->OnUserLeftSignal(uid);
}

// 远端用户开启视频的回调。
void NEEventHandler::onUserVideoStart(uid_t uid, NERtcVideoProfileType max_profile) {
    if (neRtcEngine == nullptr) {
        return;
    }
    // VideoCommunicateWidget::ChangedOfUserVideoSlot
    emit neRtcEngine->ChangedOfUserVideoSignal(uid, true);
}

// 远端用户停用视频的回调。
void NEEventHandler::onUserVideoStop(uid_t uid) {
    if (neRtcEngine == nullptr) {
        return;
    }
    // VideoCommunicateWidget::ChangedOfUserVideoSlot
    emit neRtcEngine->ChangedOfUserVideoSignal(uid, false);
}

// 远端用户开启语音的回调。
void NEEventHandler::onUserAudioStart(uid_t uid) {
    if (neRtcEngine == nullptr) {
        return;
    }
    // VideoCommunicateWidget::ChangedOfUserAudioSlot
    emit neRtcEngine->ChangedOfUserAudioSignal(uid, true);
}

// 远端用户关闭语音的回调
void NEEventHandler::onUserAudioStop(uid_t uid) {
    if (neRtcEngine == nullptr) {
        return;
    }
    // VideoCommunicateWidget::ChangedOfUserAudioSlot
    emit neRtcEngine->ChangedOfUserAudioSignal(uid, false);
}