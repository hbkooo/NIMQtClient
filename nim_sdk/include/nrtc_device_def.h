/** @file nrtc_device_def.h
 * @brief NRTC提供的设备相关接口定义
 * @copyright (c) 2015-2016, NetEase Inc. All rights reserved
 * @author gq
 * @date 2015/4/24
 */

#ifndef NRTC_API_DEVICE_DEF_H_
#define NRTC_API_DEVICE_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @enum NRTCDeviceType 设备类型 */
enum NRTCDeviceType {
    kNRTCDeviceTypeAudioIn = 0,      /**< 麦克风设备 */
    kNRTCDeviceTypeAudioOut = 1,     /**< 听筒设备用于播放本地采集音频数据，麦克风试音 */
    kNRTCDeviceTypeAudioOutChat = 2, /**< 听筒设备用于通话音频数据（nrtc_dev_start_device和nrtc_dev_end_device中使用） */
    kNRTCDeviceTypeVideo = 3,        /**< 摄像头 */
    kNRTCDeviceTypeSoundcardCapturer = 4, /**< 声卡声音采集，得到的数据混音到发送的通话声音中(此模式使用条件苛刻不建议使用) */
    kNRTCDeviceTypeAudioHook = 5, /**< 伴音，启动第三方播放器并获取音频数据（只允许存在一个进程钩子）,只混音到发送的通话声音中 */
};

/** @enum NRTCDeviceStatus 设备状态类型 */
enum NRTCDeviceStatus {
    kNRTCDeviceStatusNoChange = 0x0,   /**< 设备没有变化 */
    kNRTCDeviceStatusChange = 0x1,     /**< 设备有变化 */
    kNRTCDeviceStatusWorkRemove = 0x2, /**< 工作设备被移除 */
    kNRTCDeviceStatusReset = 0x4,      /**< 设备重新启动 */
    kNRTCDeviceStatusStart = 0x8,      /**< 设备开始工作 */
    kNRTCDeviceStatusEnd = 0x10,       /**< 设备停止工作 */
};

/** @enum NRTCVideoSubType 视频格式类型 */
enum NRTCVideoSubType {
    kNRTCVideoSubTypeARGB = 0, /**< 32位位图格式 存储 (B,G,R,A)... */
    kNRTCVideoSubTypeRGB = 1,  /**< 24位位图格式 存储 (B,G,R)... */
    kNRTCVideoSubTypeI420 = 2, /**< YUV格式，存储 yyyyyyyy...uu...vv... */
};
/** @enum NRTCAudioDataCbType 音频数据监听类型 */
enum NRTCAudioDataCbType {
    kNRTCAudioDataCbTypeHook = 1, /**< 实时返回伴音数据，伴音数据保留原始的格式，伴音不再混音到通话数据中，如果还需要可以通过伴音数据通道再回传 */
    kNRTCAudioDataCbTypeHookAndMic =
        2, /**< 定时返回伴音和麦克风、声卡的混音数据，允许重采样（json中带kNRTCDeviceSampleRate和kNRTCVolumeWork），返回单声道数据 */
};

/** @name json extension params for nrtc device key
 * @{
 */
static const char* kNRTCDeviceName = "name";              /**< string 设备名称 */
static const char* kNRTCDevicePath = "path";              /**< string 设备路径 */
static const char* kNRTCDeviceSampleRate = "sample_rate"; /**< int32 采样频率 */
static const char* kNRTCDeviceSampleBit = "sample_bit";   /**< int32 采样位深 */
static const char* kNRTCDeviceDataUid = "uid";            /**< int64 用户id */
static const char* kNRTCDeviceWidth = "width";            /**< int32 画面宽 */
static const char* kNRTCDeviceHeight = "height";          /**< int32 画面高 */
static const char* kNRTCVideoSubType = "subtype";         /**< int32 视频数据类型，NRTCVideoSubType */
static const char* kNRTCDeviceId = "id";                  /**< string 标识ID */
static const char* kNRTCVolumeWork = "volume_work"; /**< int32 大于0标识数据将使用音量参数进行换算(暂时只针对伴音数据) */
static const char* kNRTCDeviceDecklinkModeName = "mode_name";   /**< DeckLink设备mode name */
static const char* kNRTCDeviceDecklinkMode = "mode";            /**< DeckLink设备mode */
static const char* kNRTCDeviceDecklinkModeInfo = "mode_info";   /**< json array DeckLink设备mode info */
static const char* kNRTCDeviceDecklinkVideo = "decklink_video"; /**< int 大于0时DeckLink设备开启视频 */
static const char* kNRTCDeviceDecklinkAudio = "decklink_audio"; /**< int 大于0时DeckLink设备开启音频 */
static const char* kNRTCDeviceDeckLink = "is_dicklink";
static const char* kNRTCDeviceHeadphone = "headphone"; /**< int 大于0时标记为耳机设备 */
/** @}*/                                               // json extension params for vchat device key

/** @typedef void (*nrtc_dev_enum_device_path_sync_cb_func)(bool ret, NRTCDeviceType type, const char *json_extension, const void *user_data)
 * NRTC Device 枚举设备返回回调同步接口
 * @param[out] ret 结果代码，true表示成功
 * @param[out] type 设备类型NRTCDeviceType，其中kNRTCDeviceTypeAudioOut和kNRTCDeviceTypeAudioOutChat等效
 * @param[out] json_extension Json string 设备列表，可能为空"", 例：json_extension =
 * "[{"name":"Webcam","path":"\\\\?\\usb......"},{"name":"Webcam2","path":"\\\\?\\usb......"}]"
 * @param[out] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
typedef void (*nrtc_dev_enum_device_path_sync_cb_func)(bool ret, NRTCDeviceType type, const char* json_extension, const void* user_data);

/** @typedef void (*nrtc_dev_start_device_cb_func)(NRTCDeviceType type, bool ret, const char *json_extension, const void *user_data)
 * NRTC Device 启动设备异步返回接口
 * @param[out] type 设备类型NRTCDeviceType
 * @param[out] ret 启动结果，true表示成功
 * @param[out] json_extension 无效的扩展字段
 * @param[out] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
typedef void (*nrtc_dev_start_device_cb_func)(NRTCDeviceType type, bool ret, const char* json_extension, const void* user_data);

/** @typedef void (*nrtc_dev_device_status_cb_func)(NRTCDeviceType type, unsigned int status, const char *device_path, const char *json_extension,
 * const void *user_data) NRTC Device 设备状态监听返回接口
 * @param[out] type 设备类型NRTCDeviceType，其中kNRTCDeviceTypeAudioIn和kNRTCDeviceTypeVideo、kNRTCDeviceTypeAudioHook有效
 * @param[out] status 为NRTCDeviceStatus的多状态
 * @param[out] device_path
 * 当kNRTCDeviceStatusReset状态时需要关注此参数，kNRTCDeviceStatusReset时有可能选用了非用户选定的设备，这里返回的是重新启动的设备地址
 * @param[out] json_extension 无效的扩展字段
 * @param[out] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
typedef void (*nrtc_dev_device_status_cb_func)(NRTCDeviceType type,
                                               unsigned int status,
                                               const char* device_path,
                                               const char* json_extension,
                                               const void* user_data);

/** @typedef void (*nrtc_dev_audio_data_cb_func)(unsigned __int64 time, const char *data, unsigned int size, const char *json_extension, const void
 * *user_data) NRTC Device 音频数据监听接口
 * @param[out] time 时间毫秒级
 * @param[out] data 音频数据pcm格式
 * @param[out] size data的数据长度
 * @param[out] json_extension Json string 返回kNRTCDeviceSampleRate
 * @param[out] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
typedef void (
    *nrtc_dev_audio_data_cb_func)(unsigned __int64 time, const char* data, unsigned int size, const char* json_extension, const void* user_data);

/** @typedef void(*nrtc_dev_audio_data_cb_func_ex)(unsigned __int64 time, const char *data, unsigned int size, int channels, int rate, int volume,
 * const char *json_extension, const void *user_data) NRTC Device 音频数据监听接口
 * @param[out] time 时间毫秒级，暂时无效
 * @param[out] data 音频数据pcm格式
 * @param[out] size data的数据长度
 * @param[out] channels 通道数
 * @param[out] rate 采样频
 * @param[out] volume 音量值0-100
 * @param[out] json_extension 扩展
 * @param[out] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
typedef void (*nrtc_dev_audio_data_cb_func_ex)(unsigned __int64 time,
                                               const char* data,
                                               unsigned int size,
                                               int channels,
                                               int rate,
                                               int volume,
                                               const char* json_extension,
                                               const void* user_data);

/** @typedef void (*nrtc_dev_video_data_cb_func)(unsigned __int64 time, const char *data, unsigned int size, unsigned int width, unsigned int height,
 * const char *json_extension, const void *user_data) NRTC Device 视频数据监听接口
 * @param[out] time 时间毫秒级
 * @param[out] data 视频数据，默认为ARGB格式
 * @param[out] size data的数据长度
 * @param[out] width  画面宽度
 * @param[out] height  画面高度
 * @param[out] json_extension Json string
 * 返回kNRTCDeviceDataUid，kNRTCVideoSubType（缺省为kNRTCVideoSubTypeARGB），如果是辅助摄像头数据则返回kNRTCDeviceId
 * @param[out] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
typedef void (*nrtc_dev_video_data_cb_func)(unsigned __int64 time,
                                            const char* data,
                                            unsigned int size,
                                            unsigned int width,
                                            unsigned int height,
                                            const char* json_extension,
                                            const void* user_data);

/** @typedef void(*nrtc_dev_audio_effect_opt_cb_func)(int id, bool ret, int code, const char *json_extension, const void *user_data)
 * NRTC Device 音效操作结果回调
 * @param[out] id 音效id
 * @param[out] ret 操作结果
 * @param[out] code 错误码
 * @param[out] json_extension 扩展
 * @param[out] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
typedef void (*nrtc_dev_audio_effect_opt_cb_func)(int id, bool ret, int code, const char* json_extension, const void* user_data);

#ifdef __cplusplus
};
#endif  //__cplusplus
#endif  // NRTC_API_DEVICE_DEF_H_
