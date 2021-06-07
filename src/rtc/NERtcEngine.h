//
// Created by 19216 on 2021/6/7.
//

#ifndef NIMQTCLIENT_NERTCENGINE_H
#define NIMQTCLIENT_NERTCENGINE_H

#include <QObject>
#include <QDebug>

#include "NEEventHandler.h"
#include "nertc_engine.h"
#include "client.h"

class NERtcEngine : public QObject{
Q_OBJECT

public:
    explicit NERtcEngine(QObject *parent = nullptr);

    // 初始化Rtc
    bool init(const QString &appKey, const QString &log_dir_path="");

    // 查看是否已经初始化
    bool getIsInit() const { return is_Init; }

    //设置本地视频渲染窗口
    int setupLocalVideo(void* hwnd);
    //设置远端视频渲染窗口
    int setupRemoteVideo(quint64 uid, void* hwnd);

private:
    // 网易云通信 SDK 引擎
    nertc::IRtcEngine* rtcEngine = nullptr;

    // 事件处理器
    std::shared_ptr<NEEventHandler> rtcEngineEventHandler;

    // 是否已经初始化
    bool is_Init;
};


#endif //NIMQTCLIENT_NERTCENGINE_H
