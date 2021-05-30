/**
 * @file nrtc_ls_def.h
 * @brief NRTC 直播定义头文件
 * @date 2021-04-25
 * @copyright Copyright (c) 2021
 *
 */

#ifndef NRTC_LIVESTREAM_DEF_H_
#define NRTC_LIVESTREAM_DEF_H_

#include "nrtc_device_def.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@enum NRTCAudioSourceType 音频数据源类型 */
enum NRTCAudioSourceType {
    kNRTCAudioSourceTypeCapture = 0x1,
    kNRTCAudioSourceTypeAudioOut = 0x2,
    kNRTCAudioSourceTypeCustom = 0x4,
    kNRTCAudioSourceTypeHook = 0x8,
    kNRTCAudioSourceTypeAccompay = 0x100,
};

/**@enum LiveSteamCode 直播返回码说明 */
enum LiveSteamCode {
    kNetFail = 100,              /**< 网络异常 */
    kUrlError = 101,             /**< url错误 */
    kObjectNotExist = 102,       /**< 操作对象不存在 */
    kSucess = 200,               /**< 操作成功 */
    kLiving = 201,               /**< 当前会话正在操作 */
    kConnectTimeout = 404,       /**< 连接超时 */
    kKeepAliveTimeout = 405,     /**< 心跳超时 */
    kReUseError = 500,           /**< 参数基本格式错误（错误类型、空值） */
    kCodeError = 501,            /**< 认证失败 */
    kForbidden = 502,            /**< 防盗链校验失败，频道禁用，域名失效 */
    kStreamChainFailed = 503,    /**< 参数解析错误 */
    kBadRequest = 504,           /**< 参数基本格式错误（错误类型、空值） */
    kDrawStreamNotExist = 505,   /**< 频道(包含自定义频道),用户，域名信息不存在 */
    kDrawStreamOtherError = 506, /**< 其他错误 */
    kSourceNotFound = 507,       /**< 创建或者获取source失败，可能是推流地址重复等 */
    kForwaderFailed = 508,       /**< forwar失败，srs内部报错 */

};

/**@struct WaterMarkParam 水印参数 */
struct WaterMarkParam {
    const char* file_path_;   /**< 文件路径,暂时仅支持png格式图片 */
    unsigned int position_x_; /**< 起始x坐标 */
    unsigned int position_y_; /**< 起始y坐标 */
};

/***@struct VideoLayout 视频布局参数 */
struct VideoLayout {
    unsigned int position_x_; /**< 起始x坐标 */
    unsigned int position_y_; /**< 起始y坐标 */
    unsigned int width_;      /**< 布局宽度 */
    unsigned int height_;     /**< 布局高度 */
};

/** @enum NRTCChatVideoEncodeMode 视频编码策略  */
enum NRTCLsVideoEncodeMode {
    kNRTCLsVEModeNormal = 0,    /**< 默认值，清晰优先 */
    kNRTCLsVEModeFramerate = 1, /**< 流畅优先 */
    kNRTCLsVEModeQuality = 2,   /**< 清晰优先 */
};

/***@struct VideoParam 视频参数 */
struct VideoParam {
    NRTCLsVideoEncodeMode mode_;
    int fps_;         /**<视频的帧率 */
    int bitrate_;     /**<视频的码率 */
    int send_width_;  /**<视频发送宽度 */
    int send_height_; /**<视频发送高度 */
};

/***@enum LiveCallBackType 回调类型 */
enum LiveCallBackType {
    kUdpStart, /**< 直播开启 */
    kUdpStop,  /**< 直播停止 */
    kUdpLive,  /**< 正在直播 */
};

/***@enum LiveType 直播类型 */
enum LiveType {
    kAudio,         /**< 纯音频直播 */
    kVideo,         /**< 纯视频直播 */
    kAudioAndVideo, /**< 音视频直播 */
};

/** @typedef void(*nrtc_ls_get_session_cb)(bool ret, const char* json_info, void* user_data)
 * 获取当前直播session的回调
 * @param[out] ret 回调结果
 * @param[out] json_info 包含session的json串
 * @param[out] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 */
typedef void (*nrtc_ls_get_session_cb)(bool ret, const char* json_info, void* user_data);

/** @typedef void(*nrtc_ls_opt_cb)(const char* session_id, bool ret, const char* json_info, void* user_data)
 * 通用的操作回调函数
 * @param[out] session_id	udp推流会话id
 * @param[out] ret			操作结果,true:成功 false:失败
 * @param[out] json_info	json拓展参数,暂时不起作用
 * @param[out] user_data	APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 */
typedef void (*nrtc_ls_opt_cb)(const char* session_id, bool ret, const char* json_info, void* user_data);

/** @typedef void(*nrtc_ls_mp4_record_opt_cb_func)(const char* session_id,bool ret, int code, const char *file, __int64 time, const char
 * *json_extension, const void *user_data); mp4录制回调函数
 * @param[out] session_id	udp推流会话id
 * @param[out] ret			操作结果
 * @param[out] code		操作码信息
 * @param[out] file		文件名
 * @param[out] time		时长
 * @param[out] json_extension	json拓展参数，暂时不起作用
 * @param[out] user_data		APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 */
typedef void (*nrtc_ls_mp4_record_opt_cb_func)(const char* session_id,
                                               bool ret,
                                               int code,
                                               const char* file,
                                               __int64 time,
                                               const char* json_extension,
                                               const void* user_data);

/** @typedef void(*nrtc_ls_video_device_opt_cb)(const char* session_id, const char* device_id, bool ret, const char* json_info, void* user_data)
 * 操作视频源回调函数
 * @param[out] session_id	udp推流会话id
 * @param[out] device_id	视频源所标识的device_id
 * @param[out] ret			操作结果，true:成功,false:失败
 * @param[out] json_info	json数据，暂时不起作用
 * @param[out] user_data	APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 */
typedef void (*nrtc_ls_video_device_opt_cb)(const char* session_id, const char* device_id, bool ret, const char* json_info, void* user_data);

/** @typedef void(*nrtc_ls_audio_device_opt_cb)(NRTCAudioSourceType type, const char* session_id, const char* device_id, bool ret, const char*
 * json_info, void* user_data) 操作音频源回调函数
 * @param[out] type		音频源类型
 * @param[out] session_id	udp推流会话id
 * @param[out] ret			操作结果
 * @param[out] json_info	json数据，暂时不起作用
 * @param[out] user_data	APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 */
typedef void (*nrtc_ls_audio_device_opt_cb)(NRTCAudioSourceType type, const char* session_id, bool ret, const char* json_info, void* user_data);

/** @typedef void(*nrtc_ls_stream_cb)(LiveCallBackType type, const char* session_id, unsigned int code, const char* json_info, void* user_data)
 * 直播操作回调
 * @param[out]	type		直播回调的类型
 * @param[out] session_id	会话id
 * @param[out] code		操作码
 * @param[out] json_info	json数据,暂时不起作用
 * @param[out] user_data	APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 */
typedef void (*nrtc_ls_stream_cb)(LiveCallBackType type, const char* session_id, unsigned int code, const char* json_info, void* user_data);

/** @typedef void (*nrtc_dev_video_data_cb_func)(unsigned __int64 time, const char *data, unsigned int size, unsigned int width, unsigned int height,
 * const char *json_extension, const void *user_data) NRTC Device	视频数据监听接口
 * @param[out] time			时间毫秒级
 * @param[out] data			视频数据，默认为ARGB格式
 * @param[out] size			data的数据长度
 * @param[out] width			画面宽度
 * @param[out] height			画面高度
 * @param[out] json_extension	json数据,暂时不起作用
 * @param[out] user_data		APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
typedef void (*nrtc_ls_preview_video_data_cb_func)(unsigned __int64 time,
                                                   const char* session_id,
                                                   const char* data,
                                                   unsigned int size,
                                                   unsigned int width,
                                                   unsigned int height,
                                                   const char* json_extension,
                                                   const void* user_data);

/***@enum LiveStreamParam 直播参数 */
struct LiveStreamParam {
    char* url;              /**<直播url地址 */
    LiveType live_type;     /**<直播类型 */
    VideoParam video_param; /**<视频的相关参数设置 */
    nrtc_ls_stream_cb cb;   /**<直播回调 */
    void* user_data;        /**<APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！ */
};
#ifdef __cplusplus
}
#endif
#endif
