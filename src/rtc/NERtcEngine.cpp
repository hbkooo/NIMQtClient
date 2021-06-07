//
// Created by 19216 on 2021/6/7.
//

#include "NERtcEngine.h"

NERtcEngine::NERtcEngine(QObject *parent) : QObject(parent), is_Init(false) {

}

// 初始化Rtc
bool NERtcEngine::init(const QString &appKey, const QString &log_dir_path) {

    // 初始化事件回调
    rtcEngineEventHandler = std::make_shared<NEEventHandler>(this);

    // 创建 RTC 引擎对象并返回指针。
    rtcEngine = dynamic_cast<nertc::IRtcEngine*>(createNERtcEngine());
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
    canvas.scaling_mode = kNERtcVideoScaleCropFill ;
    int ret = rtcEngine->setupLocalVideoCanvas(&canvas);
    if (ret) {
        qDebug() << "[error]: Can not setup local video canvas! Error code is : " <<  ret;
    }

    // 开启本地预览。若要结束预览，或者准备加入房间时，调用 stopVideoPreview 停止预览。
    // rtcEngine->startVideoPreview();

    return ret;
}
