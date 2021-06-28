//
// Created by 19216 on 2021/6/7.
//

#include "NERtcEngine.h"

NERtcEngine::NERtcEngine(QObject *parent) : QObject(parent), is_Init(false) {
    qDebug() << "[info]: " << __FUNCTION__ ;
}

NERtcEngine::~NERtcEngine() {
    release();
}

// 释放Rtc
void NERtcEngine::release() {
    // 同步销毁 IRtcEngine 对象
    rtcEngine->release(true);
    // 销毁 RTC 引擎对象
    destroyNERtcEngine((void* &)rtcEngine);
    rtcEngine = nullptr;
    qDebug() << "[info]: In " << __FUNCTION__ << ", release rtcEngine ...";
}

// 初始化Rtc
bool NERtcEngine::init(const QString &appKey, const QString &log_dir_path) {

    // 初始化事件回调
    rtcEngineEventHandler = std::make_shared<NEEventHandler>(this);

    // 创建 RTC 引擎对象并返回指针。
    rtcEngine = dynamic_cast<nertc::IRtcEngineEx*>(createNERtcEngine());
    // 设置已开通音视频功能的云信应用的AppKey。
    nertc::NERtcEngineContext rtcEngineContext{};
    rtcEngineContext.app_key = appKey.toStdString().c_str();
    rtcEngineContext.log_dir_path = log_dir_path.toStdString().c_str();
    // 设置SDK向应用发送回调事件的通知。
    rtcEngineContext.event_handler = rtcEngineEventHandler.get();
    // 设置日志级别，默认级别为 kNERtcLogLevelInfo。
    rtcEngineContext.log_level = nertc::kNERtcLogLevelInfo;
    // 初始化 NERTC SDK 服务。
    if(nertc::kNERtcNoError != rtcEngine->initialize(rtcEngineContext)) {
        // 加载失败
        qDebug() << "[error]: Failed to initialize NERtc Engine\n";
        return false;
    }

    is_Init = true;
    return true;
}

int NERtcEngine::setupLocalVideo(void *hwnd) {
    NERtcVideoCanvas canvas{};
    canvas.cb = nullptr;
    canvas.user_data = nullptr;
    canvas.window = hwnd;
    // 视频尺寸非等比缩放。保证视频内容全部显示，且填满视窗。
    canvas.scaling_mode = kNERtcVideoScaleCropFill ;
    int ret = rtcEngine->setupLocalVideoCanvas(&canvas);
    if (ret) {
        qDebug() << "[error]: Can not setup local video canvas! Error code is : " << ret;
    }
    // 开启本地预览。若要结束预览，或者准备加入房间时，调用 stopVideoPreview 停止预览。
    // rtcEngine->startVideoPreview();
    return ret;
}

// 当新加入新的视频用户时，设置该远端视频渲染窗口
int NERtcEngine::setupRemoteVideo(quint64 uid, void *hwnd) {
    NERtcVideoCanvas canvas{};
    canvas.cb = nullptr;
    canvas.user_data = nullptr;
    canvas.window = hwnd;
    // 适应视频，视频尺寸等比缩放。优先保证视频内容全部显示。若视频尺寸与显示视窗尺寸不一致，视窗未被填满的区域填充背景色。
    canvas.scaling_mode = kNERtcVideoScaleFit;
    int ret = rtcEngine->setupRemoteVideoCanvas(uid, &canvas);
    if (ret) {
        qDebug() << "[error]: Can not setup remote video canvas! Error code is : " << ret;
    }
    // 订阅指定远端用户的视频流。
    int ret_temp = rtcEngine->subscribeRemoteVideoStream(uid, kNERtcRemoteVideoStreamTypeHigh, true);
    if (ret_temp) {
        qDebug() << "[error]: can not subscribe remote video stream! Error code is : " << ret_temp;
    }
    // 恢复订阅指定远端用户音频流。
    ret_temp = rtcEngine->subscribeRemoteAudioStream(uid, true);
    if (ret_temp) {
        qDebug() << "[error]: can not subscribe remote audio stream! Error code is : " << ret_temp;
    }
    return ret;
}

/**
 * 加入房间。加入房间前，请确保已完成初始化相关事项
 * @param token 安全认证签名。非安全模式下可设置为 null。安全模式下必须设置为获取到的 Token。
 * @param roomID 房间名称，设置相同房间名称的用户会进入同一个通话房间。
 * @param uid 用户的唯一标识 id，房间内每个用户的 uid 必须是唯一的。
 * @return
 */
int NERtcEngine::joinChannel(const QString &token, const QString &roomID, const QString &uid) {
    int ret = kNERtcNoError;
    rtcEngine->enableLocalAudio(true);
    rtcEngine->enableLocalVideo(true);
    // 加入频道房间。之后会有一个回调函数，到NEEventHandler::onJoinChannel中，得到是否加入成功的结果。
    ret = rtcEngine->joinChannel(token.toStdString().c_str(),
                                 roomID.toStdString().c_str(), uid.toULongLong());
    if (ret == kNERtcNoError) {
        // emit sigJoiningChannel();
        qDebug() << "[info]: join channel successfully!";
    } else {
        qDebug() << "[error]: can't join channel, Error code is : " << ret;
    }
    qDebug() << "[info]: current connection state: " << rtcEngine->getConnectionState();
    return ret;
}

//离开频道
int NERtcEngine::leaveChannel() {
    int ret = kNERtcNoError;
    qDebug() << "[info]: current connection state: " << rtcEngine->getConnectionState();

    if (rtcEngine) {
        ret = rtcEngine->enableLocalAudio(false);
        ret = rtcEngine->enableLocalVideo(false);
        // 离开房间，真正退出房间后，SDK 会走入初始化时设置的 rtc_engine_context_.event_handler 回调事件通知中的 onLeaveChannel。
        ret = rtcEngine->leaveChannel();

        if (kNERtcNoError == ret) {
            // Q_EMIT sigJoiningChannel();
        } else {
            qDebug() << "[error]: Can't leave channel, Error code is : " << ret;
        }
    }
    return ret;
}

// 开启/关闭本地话筒
int NERtcEngine::enableAudio(bool enabled) {
    return rtcEngine->enableLocalAudio(enabled);
}

// 开启/关闭本地听筒
int NERtcEngine::enableVoice(bool enabled) {
//    return rtcEngine->enableVoice(enabled);
    return 0;
}

// 开启/关闭本地摄像头
int NERtcEngine::enableVideo(bool enabled) {
    return rtcEngine->enableLocalVideo(enabled);
}

// 根据用户 uid 开启订阅该用户的视频流
void NERtcEngine::startSubscribeRemoteUserVideoStream(nertc::uid_t uid) {
    // 订阅指定远端用户的视频流。
    int ret = rtcEngine->subscribeRemoteVideoStream(uid, kNERtcRemoteVideoStreamTypeHigh, true);
    if (ret) {
        qDebug() << "[error]: can not subscribe remote video stream! Error code is : " << ret;
    }

}

// 根据用户 uid 关闭订阅该用户的视频流
void NERtcEngine::stopSubscribeRemoteUserVideoStream(nertc::uid_t uid) {
    // 取消订阅指定远端用户的视频流。
    int ret = rtcEngine->subscribeRemoteVideoStream(uid, kNERtcRemoteVideoStreamTypeHigh, false);
    if (ret) {
        qDebug() << "[error]: can not stop subscribe remote video stream! Error code is : " << ret;
    }
}

// 根据用户 uid 开启订阅该用户的语音流
void NERtcEngine::startSubscribeRemoteUserAudioStream(nertc::uid_t uid) {
    // 恢复订阅指定远端用户音频流。
    int ret = rtcEngine->subscribeRemoteAudioStream(uid, true);
    if (ret) {
        qDebug() << "[error]: can not subscribe remote audio stream! Error code is : " << ret;
    }
}

// 根据用户 uid 关闭订阅该用户的语音流
void NERtcEngine::stopSubscribeRemoteUserAudioStream(nertc::uid_t uid) {
    // 取消订阅指定远端用户音频流。
    int ret = rtcEngine->subscribeRemoteAudioStream(uid, false);
    if (ret) {
        qDebug() << "[error]: can not stop subscribe remote audio stream! Error code is : " << ret;
    }
}




