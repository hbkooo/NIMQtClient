/** @file nrtc_chat_for_yunxin.h
 * @brief nrtc提供的音视频通话控制接口(只为云信sdk调用，不暴露给独立nrtc的用户使用)，使用前请先调用nrtc_init.h中nrtc_init
 * @copyright (c) 2015-2016, NetEase Inc. All rights reserved
 * @author gq
 * @date 2015/4/30
 */

#ifndef NRTC_CHAT_FOR_YUNXIN_API_CLIENT_H_
#define NRTC_CHAT_FOR_YUNXIN_API_CLIENT_H_

#include "nrtc_chat_def.h"
#include "nrtc_init_def.h"
#include "nrtc_sdk_dll.h"

extern "C" {
// nim sdk专用的key
static const char* kNRTCChatTurnSer = "turn_ser";
static const char* kNRTCChatSturnSer = "sturn_ser";
static const char* kNRTCChatProxySer = "proxy_ser";
static const char* kNRTCChatDispatch = "dispatch";
static const char* kNRTCChatSessionKey = "session_key";
static const char* kNRTCChatAecTime = "aec_time";           /**< int 回音消除延迟参数 >=0有效 */
static const char* kNRTCChatConfig = "config";              /**< string 服务器下发的配置信息 */
static const char* kNRTCChatP2pConnect = "p2p_connect";     /**< int 是否p2p直连 >0表示是 */
static const char* kNRTCDeviceDataAccount = "account";      /**< string 用户账号 */
static const char* kNRTCUidAccount = "uid_account";         /**< key 用户账号对应关系 */
static const char* kNRTCSignallingTime = "signalling_time"; /**< int64 yuxin的上层信令的时间 */
static const char* kNRTCRtsFlag = "rts_flag";               /**< int yuxin的白板中音视频的标记 */

static const char* kNRTCChatStreamEncryptType =
    "stream_encrypt_type"; /**< int, 使用的流媒体加密类型NRTCChatStreamEncryptType， 默认kNRTCChatStreamEncryptTypeNone */
static const char* kNRTCChatStreamEncryptToken = "stream_encrypt_token"; /**< string, 流媒体加密密钥 */

static const char* kNRTCChatCallRejoin = "call_rejoin"; /**< key, 需要请求重连 */

/** @fn bool nrtc_chat_start_client(NRTCChatMode mode, bool creater, const char* json_info, nrtc_chat_session_status_cb_func cb, const void
 * *user_data) NRTC 开始通话
 * @param[in] mode NRTCChatMode 见nrtc_chat_def.h
 * @param[in] creater 是否为发起方
 * @param[in] json_info 为一些参数定义，见nrtc_chat_def.h
 * @param[in] cb 结果回调见nrtc_chat_def.h
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return bool true 调用成功，false 调用失败
 */
NRTC_SDK_DLL_API bool nrtc_chat_start_client(NRTCChatMode mode,
                                             bool creater,
                                             const char* json_info,
                                             nrtc_chat_session_status_cb_func cb,
                                             const void* user_data);

/** @fn bool nrtc_chat_add_uid_account(const char* json_info, nrtc_chat_opt_cb_func cb, const void *user_data)
 * NRTC 对当前通话添加成员的对应关系
 * @param[in] json_info  {"uid_account":[{"uid":1,"account":"a"},{"uid":2,"account":"b"}]}
 * @param[in] cb 结果回调见nrtc_chat_def.h
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return bool true 调用成功，false 调用失败
 */
NRTC_SDK_DLL_API bool nrtc_chat_add_uid_account(const char* json_info, nrtc_chat_opt_cb_func cb, const void* user_data);

/** @fn void nrtc_chat_set_video_encode_type(int rate_type, const char* json_info, nrtc_chat_opt_cb_func cb, const void *user_data)
 * NRTC 实时视频编码控制
 * @param[in] rate_type  默认0，码率特性，取值0、1、2，值越高越注重码率（当取2时，在码率无法控制时会丢帧处理，严重时会明显卡顿）
 * @param[in] json_extension  无效备用
 * @param[in] cb 结果回调见nrtc_chat_def.h
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_set_video_encode_type(int rate_type, const char* json_extension, nrtc_chat_opt_cb_func cb, const void* user_data);

/** @fn unsigned __int64 nrtc_net_detect_ex(int type, const char *ip, const char *proxy, const char *json_extension, nrtc_net_detect_cb_func cb, const
 *void *user_data) 网络探测接口
 * @param[in] type 探测类型
 * @param[in] ip 探测ip
 * @param[in] proxy 代理地址
 * @param[in] json_extension json扩展参数（备用，目前不需要）
 * @param[in] cb 操作结果的回调函数
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return unsigned __int64 探测任务id
 * @note 错误码	200:成功
 *				0:流程错误
 *				400:非法请求格式
 *				417:请求数据不对
 *				606:ip为内网ip
 *				607:频率超限
 *				20001:探测类型错误
 *				20002:ip错误
 *				20003:sock错误
 */
NRTC_SDK_DLL_API unsigned __int64 nrtc_net_detect_ex(int type,
                                                     const char* ip,
                                                     const char* proxy,
                                                     const char* json_extension,
                                                     nrtc_net_detect_cb_func cb,
                                                     const void* user_data);

/** @typedef void (*nrtc_nos_upload_cb_func)(int rescode, const char *url, const char *json_extension, const void *user_data)
 * nrtc callback function for nos http upload
 * @param[out] rescode 			上传结果，一切正常200
 * @param[out] url					url
 * @param[out] json_extension		json扩展数据
 * @param[out] user_data			APP的自定义用户数据，SDK只负责传回给回调函数，不做任何处理！
 * @return void 无返回值
 */
typedef void (*nrtc_nos_upload_cb_func)(int rescode, const char* url, const char* json_extension, const void* user_data);

/** @fn void nrtc_upload_file(const char *file, const char* json_extension, nrtc_chat_opt_cb_func cb, const void *user_data)
 * NRTC 通过nos上传文件
 * @param[in] file  文件路径
 * @param[in] json_extension  带上传参数
 * @param[in] cb 结果回调见nrtc_chat_def.h
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_upload_file(const char* file, const char* json_extension, nrtc_nos_upload_cb_func cb, const void* user_data);

/** @fn void nrtc_nim_control(__int64 channel_id, int type, const char* json_extension, nrtc_chat_opt_cb_func cb, const void *user_data)
 * NRTC 透传音视频nim的通知控制信息
 * @param[in] channel_id  通道号
 * @param[in] type  通知信息NIMVChatControlType
 * @param[in] json_extension  无效
 * @param[in] cb 无效
 * @param[in] user_data 无效
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_nim_control(__int64 channel_id, int type, const char* json_extension, nrtc_chat_opt_cb_func cb, const void* user_data);

/** @enum NRTCChatSetStreamingModeCode 设置推流模式返回码  */
enum NRTCChatSetStreamingModeCode {
    kNRTCBypassStreamingInvalid = 0,              /**< 无效的操作 */
    kNRTCBypassStreamingSuccess = 200,            /**< 设置成功 */
    kNRTCBypassStreamingErrorExceedMax = 202,     /**< 超过最大允许直播节点数量 */
    kNRTCBypassStreamingErrorHostNotJoined = 203, /**< 必须由主播第一个开启直播 */
    kNRTCBypassStreamingErrorServerError = 204,   /**< 互动直播服务器错误 */
    kNRTCBypassStreamingErrorOtherError = 205,    /**< 互动直播其他错误 */
    kNRTCBypassStreamingErrorNoResponse = 404,    /**< 互动直播服务器没有响应 */
    kNRTCBypassStreamingErrorReconnecting = 405,  /**< 重连过程中无法进行相关操作，稍后再试 */
    kNRTCBypassStreamingErrorTimeout = 408,       /**< 互动直播设置超时 */
};
/** @fn void nrtc_chat_set_streaming_mode(bool streaming, const char* json_info, nrtc_chat_opt_cb_func cb, const void *user_data)
 * NRTC 推流开关
 * @param[in] streaming  是否加入推流
 * @param[in] json_info  无效备用
 * @param[in] cb 结果回调见nrtc_chat_def.h， code返回参见NRTCChatSetStreamingModeCode
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
/*NRTC_SDK_DLL_API*/ void nrtc_chat_set_streaming_mode(bool streaming, const char* json_info, nrtc_chat_opt_cb_func cb, const void* user_data);

/** @fn void nrtc_chat_audio_process_test(const char* src_path, const char* dest_file, int rate, const char* json_extension, nrtc_chat_opt_cb_func cb,
 * const void *user_data) NRTC 前处理测试
 * @param[in] src_path  原始pcm文件源
 * @param[in] dest_file  处理完的保存文件名PCM文件
 * @param[in] rate  pcm的采样率
 * @param[in] json_extension  无效备用
 * @param[in] cb 结果回调见nrtc_chat_def.h
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_audio_process_test(const char* src_path,
                                                   const char* dest_file,
                                                   int rate,
                                                   const char* json_extension,
                                                   nrtc_chat_opt_cb_func cb,
                                                   const void* user_data);

/** @fn void nrtc_chat_enable_trace_log(bool enabled);

* NRTC 开启/关闭引擎库的trace详细日志，用于通话中修改开启或关闭，每一次通话都需要重新设置，默认读取session_mock_config.json
* @param[in] enabled  true:开启，false:关闭
* @return void 无返回值
*/
NRTC_SDK_DLL_API void nrtc_chat_enable_trace_log(bool enabled);

/** @fn void nrtc_chat_set_video_hw_encode(bool enable, const char* json_extension)
 * NRTC 设置视频硬编编码优先
 * @param[in] enable  是否硬编编码优先
 * @param[in] json_extension  无效备用
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_set_video_hw_encode(bool enable, const char* json_extension);

/** @fn void nrtc_chat_set_video_hw_decode(bool enable, const char* json_extension)
 * NRTC 设置视频硬解优先
 * @param[in] enable  是否视频硬解优先
 * @param[in] json_extension  无效备用
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_set_video_hw_decode(bool enable, const char* json_extension);
};
#endif  // NRTC_CHAT_FOR_YUNXIN_API_CLIENT_H_