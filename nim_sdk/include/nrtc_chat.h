/** @file nrtc_chat.h
 * @brief nrtc提供的音视频通话控制接口，使用前请先调用nrtc_init.h中nrtc_init
 * @copyright (c) 2015-2016, NetEase Inc. All rights reserved
 * @author gq
 * @date 2015/4/30
 */

#ifndef NRTC_CHAT_API_CLIENT_H_
#define NRTC_CHAT_API_CLIENT_H_

#include "nrtc_chat_def.h"
#include "nrtc_sdk_dll.h"

extern "C" {

/** @fn bool nrtc_chat_join_channel(NRTCChatMode mode, const char* token, const char* channel_name, __int64 uid, const char* json_info,
 * nrtc_chat_session_status_cb_func cb, const void *user_data) NRTC 加入通话
 * @param[in] mode NRTCChatMode 见nrtc_chat_def.h
 * @param[in] token 如果token为空则以非安全模式发起通话
 * @param[in] channel_name 通话的通道名称
 * @param[in] uid 本人的用户id，和加入通话的其他人必须不同，且不许为0
 * @param[in] json_info 为一些参数定义，见nrtc_chat_def.h
 * @param[in] cb 结果回调见nrtc_chat_def.h
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return bool true 调用成功，false 调用失败
 */
NRTC_SDK_DLL_API bool nrtc_chat_join_channel(NRTCChatMode mode,
                                             const char* token,
                                             const char* channel_name,
                                             __int64 uid,
                                             const char* json_info,
                                             nrtc_chat_session_status_cb_func cb,
                                             const void* user_data);

/** @fn void nrtc_chat_set_channel_mode(NRTCChatMode mode)
 * NRTC 设置通话模式，非视频模式时不会传输视频数据，异步设置
 * @param[in] mode NRTCChatMode 见nrtc_chat_def.h
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_set_channel_mode(NRTCChatMode mode);

/** @fn int nrtc_chat_get_channel_mode()
 * NRTC 获取当前通话模式
 * @return int 通话模式NRTCChatMode
 */
NRTC_SDK_DLL_API int nrtc_chat_get_channel_mode();

/** @fn void nrtc_chat_set_viewer_mode(bool viewer)
 * NRTC 设置观众模式（多人模式下），全局有效（重新发起时也生效），观众模式能减少运行开销
 * @param[in] viewer 是否观众模式
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_set_viewer_mode(bool viewer);

/** @fn bool nrtc_chat_get_viewer_mode()
 * NRTC 获取当前是否是观众模式
 * @return bool true 观众模式，false 非观众模式
 */
NRTC_SDK_DLL_API bool nrtc_chat_get_viewer_mode();

/** @fn int nrtc_chat_get_connect_status()
 * NRTC 获取当前通话状态
 * @return int 通话状态NRTCChatConnectStatus
 */
NRTC_SDK_DLL_API int nrtc_chat_get_connect_status();

/** @fn void nrtc_chat_set_audio_mute(bool muted)
 * NRTC CHAT 设置发送音频静音，全局有效（重新发起时也生效）；此开关打开音频只发静音包
 * @param[in] muted true 静音，false 不静音
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_set_audio_mute(bool muted);

/** @fn bool nrtc_chat_audio_mute_enabled()
 * NRTC CHAT 获取发送音频静音状态
 * @return bool true 静音，false 不静音
 */
NRTC_SDK_DLL_API bool nrtc_chat_audio_mute_enabled();

/** @fn void nrtc_chat_set_audio_play_mute(bool muted)
 * NRTC CHAT 设置播放对端音频静音，全局有效（重新发起时也生效）；此开关打开不播放，但不影响解码及录制
 * @param[in] muted true 静音，false 不静音
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_set_audio_play_mute(bool muted);

/** @fn bool nrtc_chat_audio_play_mute_enabled()
 * NRTC CHAT 获取播放对端音频静音状态
 * @return bool true 静音，false 不静音
 */
NRTC_SDK_DLL_API bool nrtc_chat_audio_play_mute_enabled();

/** @fn void nrtc_chat_set_rotate_remote_video(bool rotate)
 * NRTC CHAT 设置不自动旋转对方画面，默认打开，全局有效（重新发起时也生效）
 * @param[in] rotate true 自动旋转，false 不旋转
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_set_rotate_remote_video(bool rotate);

/** @fn bool nrtc_chat_rotate_remote_video_enabled()
 * NRTC CHAT 获取自动旋转对方画面设置状态
 * @return bool true 自动旋转，false 不旋转
 */
NRTC_SDK_DLL_API bool nrtc_chat_rotate_remote_video_enabled();

/** @fn void nrtc_chat_set_video_frame_scale(NRTCChatVideoFrameScaleType type)
 * NRTC CHAT 设置发送时视频画面的长宽比例裁剪模式，裁剪的时候不改变横竖屏（重新发起时也生效）
 * @param[in] type 裁剪模式NRTCChatVideoFrameScaleType
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_set_video_frame_scale(NRTCChatVideoFrameScaleType type);

/** @fn int nrtc_chat_get_video_frame_scale_type()
 * NRTC CHAT 获取视频画面的裁剪模式
 * @return int 当前的裁剪模式NRTCChatVideoFrameScaleType
 */
NRTC_SDK_DLL_API int nrtc_chat_get_video_frame_scale_type();

/** @fn void nrtc_chat_leave_channel()
 * NRTC 结束通话
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_leave_channel();

/** @fn void nrtc_chat_relogin_channel(const char *json_extension, nrtc_chat_opt_cb_func cb, const void *user_data)
 * NRTC 通话重连，在上层（app）得知网络变化（切换）时，主动重连
 * @param[in] json_extension 无效扩展字段
 * @param[in] cb 结果回调见nrtc_chat_def.h，返回的json_extension无效
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_relogin_channel(const char* json_extension, nrtc_chat_opt_cb_func cb, const void* user_data);

/** @fn void nrtc_chat_start_record(const char *path, const char *json_extension, nrtc_chat_mp4_record_opt_cb_func cb, const void *user_data)
 * NRTC 开始录制MP4文件，同一个成员一次只允许一个MP4录制文件，在通话开始的时候才有实际数据
 * @param[in] path 文件录制路径
 * @param[in] json_extension
 * kNRTCChatId录制的成员，如果是自己填空(录制时允许同时混音对端声音，需要填kNRTCChatMp4AudioType)；kNRTCChatMp4Recode标识是否重编码（默认打开，打开后kNRTCChatMp4Width和kNRTCChatMp4Height有效,[16-1280有效]）
 * @param[in] cb 结果回调见nrtc_chat_def.h
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_start_record(const char* path,
                                             const char* json_extension,
                                             nrtc_chat_mp4_record_opt_cb_func cb,
                                             const void* user_data);

/** @fn void nrtc_chat_stop_record(const char *json_extension, nrtc_chat_mp4_record_opt_cb_func cb, const void *user_data)
 * NRTC 停止录制MP4文件
 * @param[in] json_extension kNRTCChatId录制的成员，如果是自己填空
 * @param[in] cb 结果回调见nrtc_chat_def.h
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_stop_record(const char* json_extension, nrtc_chat_mp4_record_opt_cb_func cb, const void* user_data);

/** @fn void nrtc_chat_start_audio_record(const char *path, const char *json_extension, nrtc_chat_audio_record_opt_cb_func cb, const void *user_data)
 * NRTC 开始录制音频文件，一次只允许一个音频录制文件
 * @param[in] path 文件录制路径
 * @param[in] json_extension 无效扩展字段
 * @param[in] cb 结果回调见nrtc_chat_def.h
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_start_audio_record(const char* path,
                                                   const char* json_extension,
                                                   nrtc_chat_audio_record_opt_cb_func cb,
                                                   const void* user_data);

/** @fn void nrtc_chat_stop_audio_record(const char *json_extension, nrtc_chat_audio_record_opt_cb_func cb, const void *user_data)
 * NRTC 停止录制音频文件
 * @param[in] json_extension 无效扩展字段
 * @param[in] cb 结果回调见nrtc_chat_def.h
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_stop_audio_record(const char* json_extension, nrtc_chat_audio_record_opt_cb_func cb, const void* user_data);

/** @fn bool nrtc_chat_custom_audio_data(unsigned __int64 time, const char *data, unsigned int size, const char *json_extension);
 * NRTC 自定义音频数据接口, 采样时间必须为10ms的整数倍, 采样位深只支持16或32, kNRTCDeviceSampleRate支持8000，16000，32000，44100
 * @param[in] time 时间毫秒级
 * @param[in] data 音频数据pcm格式单声道
 * @param[in] size data的数据长度
 * @param[in] json_extension 扩展Json string kNRTCDeviceSampleRate采样频和kNRTCDeviceSampleBit采样位深 默认如{"sample_rate":16000, "sample_bit":16}
 * @return bool true 调用成功，false 调用失败
 */
NRTC_SDK_DLL_API bool nrtc_chat_custom_audio_data(unsigned __int64 time, const char* data, unsigned int size, const char* json_extension);

/** @fn bool nrtc_chat_accompanying_sound(unsigned char id, unsigned __int64 time, const char *data, unsigned int size, unsigned int rate, unsigned
 * int channels, const char *json_extension); NRTC 自定义音频伴音数据接口，不需要打开自定义数据开关, 采样时间必须为10ms的整数倍, 采样位深只支持16
 * @param[in] id 伴音数据id
 * @param[in] time 时间毫秒级
 * @param[in] data 音频数据pcm格式
 * @param[in] size data的数据长度
 * @param[in] rate 音频采样频
 * @param[in] channels 声道数
 * @param[in] json_extension 无效扩展
 * @return bool true 调用成功，false 调用失败
 */
NRTC_SDK_DLL_API bool nrtc_chat_accompanying_sound(unsigned char id,
                                                   unsigned __int64 time,
                                                   const char* data,
                                                   unsigned int size,
                                                   unsigned int rate,
                                                   unsigned int channels,
                                                   const char* json_extension);

/** @typedef bool nrtc_chat_custom_video_data(unsigned __int64 time, const char *data, unsigned int size, unsigned int width, unsigned int height,
 * const char *json_extension) NRTC 自定义视频数据接口
 * @param[in] time 时间毫秒级
 * @param[in] data 视频数据，默认为yuv420格式
 * @param[in] size data的数据长度
 * @param[in] width  画面宽度，必须是偶数
 * @param[in] height  画面高度，必须是偶数
 * @param[in] json_extension 扩展Json string，kNRTCVideoSubType视频数据格式（缺省为kNRTCVideoSubTypeI420），见nrtc_device_def.h
 * @return bool true 调用成功，false 调用失败
 */
NRTC_SDK_DLL_API bool nrtc_chat_custom_video_data(unsigned __int64 time,
                                                  const char* data,
                                                  unsigned int size,
                                                  unsigned int width,
                                                  unsigned int height,
                                                  const char* json_extension);

/** @fn void nrtc_chat_set_member_in_blacklist(__int64 id, bool add, bool audio, const char *json_extension, nrtc_chat_opt_cb_func cb, const void
 * *user_data) NRTC 设置单个成员的黑名单状态，当前通话有效
 * @param[in] id 成员id
 * @param[in] add true表示添加到黑名单，false表示从黑名单移除
 * @param[in] audio true表示音频黑名单，false表示视频黑名单
 * @param[in] json_extension 无效扩展字段
 * @param[in] cb 结果回调见nrtc_chat_def.h，返回的json_extension无效
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_set_member_in_blacklist(__int64 id,
                                                        bool add,
                                                        bool audio,
                                                        const char* json_extension,
                                                        nrtc_chat_opt_cb_func cb,
                                                        const void* user_data);

/** @fn void nrtc_chat_set_members_in_blacklist(bool add, bool audio, const char *json_extension, nrtc_chat_opt_cb_func cb, const void *user_data)
 * NRTC 设置多个成员的黑名单状态，当前通话有效
 * @param[in] add true表示添加到黑名单，false表示从黑名单移除
 * @param[in] audio true表示音频黑名单，false表示视频黑名单
 * @param[in] json_extension Json扩展字段，kNRTCChatIds成员列表，例：{"ids":[1,2,3]}
 * @param[in] cb 结果回调见nrtc_chat_def.h，返回的json_extension无效
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_set_members_in_blacklist(bool add,
                                                         bool audio,
                                                         const char* json_extension,
                                                         nrtc_chat_opt_cb_func cb,
                                                         const void* user_data);

/** @fn void nrtc_chat_get_blacklist(const char *json_extension, nrtc_chat_opt_cb_func cb, const void *user_data)
 * NRTC 获取当期通话的黑名单列表
 * @param[in] json_extension 无效扩展字段
 * @param[in] cb 结果回调见nrtc_chat_def.h，返回的json_extension带黑名单列表，例：{"audio":[1,2,3], "video":[1,2]}
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_get_blacklist(const char* json_extension, nrtc_chat_opt_cb_func cb, const void* user_data);

/** @fn void nrtc_chat_set_video_quality(int video_quality, const char *json_extension, nrtc_chat_opt_cb_func cb, const void *user_data)
 * NRTC 通话中修改发送画面的分辨率，发送的分辨率限制只对上限限制，如果数据源小于发送分辨率，不会进行放大
 * @param[in] video_quality 分辨率模式 见NRTCChatVideoQuality定义
 * @param[in] json_extension 无效扩展字段
 * @param[in] cb 结果回调见nrtc_chat_def.h，返回的json_extension无效
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_set_video_quality(int video_quality, const char* json_extension, nrtc_chat_opt_cb_func cb, const void* user_data);

/** @fn void nrtc_chat_set_frame_rate(NRTCChatVideoFrameRate frame_rate, const char* json_extension, nrtc_chat_opt_cb_func cb, const void *user_data)
 * NRTC 实时设置视频发送帧率上限
 * @param[in] frame_rate  帧率类型 见NRTCChatVideoFrameRate定义
 * @param[in] json_extension  无效备用
 * @param[in] cb 结果回调见nrtc_chat_def.h
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_set_frame_rate(NRTCChatVideoFrameRate frame_rate,
                                               const char* json_extension,
                                               nrtc_chat_opt_cb_func cb,
                                               const void* user_data);

/** @fn void nrtc_chat_set_video_bitrate(int video_bitrate, const char *json_extension, nrtc_chat_opt_cb_func cb, const void *user_data)
 * NRTC 通话中修改视频码率，有效区间[100kb,5000kb]，如果设置video_bitrate为0则取默认码率
 * @param[in] video_bitrate 视频码率值
 * @param[in] json_extension 无效扩展字段
 * @param[in] cb 结果回调见nrtc_chat_def.h，返回的json_extension无效
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_set_video_bitrate(int video_bitrate, const char* json_extension, nrtc_chat_opt_cb_func cb, const void* user_data);

/** @fn void nrtc_chat_set_custom_data(bool custom_audio, bool custom_video, const char *json_extension, nrtc_chat_opt_cb_func cb, const void
 * *user_data) NRTC 通话中修改自定义音视频数据模式
 * @param[in] custom_audio true表示使用自定义的音频数据，false表示不使用
 * @param[in] custom_video true表示使用自定义的视频数据，false表示不使用
 * @param[in] json_extension 无效扩展字段
 * @param[in] cb 结果回调见nrtc_chat_def.h，返回的json_extension无效
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_set_custom_data(bool custom_audio,
                                                bool custom_video,
                                                const char* json_extension,
                                                nrtc_chat_opt_cb_func cb,
                                                const void* user_data);

/** @fn void nrtc_chat_update_rtmp_url(const char *rtmp_url, const char *json_extension, nrtc_chat_opt_cb_func cb, const void *user_data)
 * NRTC 通话中修改直播推流地址（主播有效）
 * @param[in] rtmp_url 新的rtmp推流地址
 * @param[in] json_extension 无效扩展字段
 * @param[in] cb 结果回调见nrtc_chat_def.h，返回的json_extension无效
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_update_rtmp_url(const char* rtmp_url, const char* json_extension, nrtc_chat_opt_cb_func cb, const void* user_data);

/** @fn void nrtc_chat_select_video_adaptive_strategy(NRTCChatVideoEncodeMode mode, const char *json_extension, nrtc_chat_opt_cb_func cb, const void
 * *user_data) NRTC 通话中修改视频编码模式
 * @param[in] mode 选用的策略模式
 * @param[in] json_extension 无效扩展字段
 * @param[in] cb 结果回调见nrtc_chat_def.h，返回的json_extension无效
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_select_video_adaptive_strategy(NRTCChatVideoEncodeMode mode,
                                                               const char* json_extension,
                                                               nrtc_chat_opt_cb_func cb,
                                                               const void* user_data);

/** @fn void nrtc_chat_set_uid_picture_as_main(__int64 uid,const char *json_extension, nrtc_chat_opt_cb_func cb, const void *user_data)
 * NRTC 互动直播设置uid为房间的主画面（主播有效）
 * @param[in] uid 用户uid
 * @param[in] json_extension 无效扩展字段
 * @param[in] cb 结果回调见nrtc_chat_def.h，返回的json_extension无效。返回的code参考NRTCChatMainPictureOptCode。
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_set_uid_picture_as_main(__int64 uid, const char* json_extension, nrtc_chat_opt_cb_func cb, const void* user_data);

/** @fn bool nrtc_chat_set_auto_publish(bool auto_pub, bool auto_sub)
 * NRTC
 * 设置通话中自动订阅对端新加入成员音视频数据，及通话开启后自动发布视频数据的逻辑；音频发布由sdk控制，如果要不发音频单独使用静音接口。该接口仅限于多人通话模式，且需要在通话前设置，通话中设置失败。
 * @param[in] auto_pub 是否自动发布视频数据，默认开启；其中音频不支持设置自动发布功能，强制发布。自动发布时，nrtc_chat_publish_video接口会调用失败。
 * @param[in] auto_sub 是否自动订阅音视频数据，默认开启；自动订阅时nrtc_chat_subscribe_video、nrtc_chat_subscribe_audio会调用失败。
 * @return bool 是否调用成功
 */
NRTC_SDK_DLL_API bool nrtc_chat_set_auto_publish(bool auto_pub, bool auto_sub);

/** @fn bool nrtc_chat_is_auto_publish_video()
 * NRTC 获取通话设置中是否自动发布视频数据
 * @return bool 是否自动发布
 */
NRTC_SDK_DLL_API bool nrtc_chat_is_auto_publish_video();

/** @fn bool nrtc_chat_is_auto_subscribe_video()
 * NRTC 获取通话设置中是否自动订阅视频数据
 * @return bool 是否自动订阅
 */
NRTC_SDK_DLL_API bool nrtc_chat_is_auto_subscribe_video();

/** @fn bool nrtc_chat_is_auto_subscribe_audio()
 * NRTC 获取通话设置中是否自动订阅音频数据
 * @return bool 是否自动订阅
 */
NRTC_SDK_DLL_API bool nrtc_chat_is_auto_subscribe_audio();

/** @fn bool nrtc_chat_set_local_video_simulcast_mode(enum NRTCChatPublishVideoStreamMode video_stream_mode)
 * NRTC 设置本地默认发布的视频流模式，默认为双流（自动发布模式下有效）
 * @param[in] video_stream_mode 目前仅支持单/双流模式。
 * @return bool 是否调用成功
 */
NRTC_SDK_DLL_API bool nrtc_chat_set_local_video_simulcast_mode(enum NRTCChatPublishVideoStreamMode video_stream_mode);

/** @fn nrtc_chat_publish_video(const char *json_extension, nrtc_chat_opt_cb_func cb, const void *user_data)
 * NRTC 通话中设置自己的视频数据发布接口。该接口仅限于多人通话模式，且通话未发起时设置失败。
 * 回调结果只代表本地的操作结果，远端是否成功等对应的通知kNRTCChatNotifyPublishVideoRet及kNRTCChatNotifyUnpublishVideoRet
 * @param[in] json_extension 无效扩展字段
 * @param[in] cb 结果回调见nrtc_chat_def.h，返回的json_extension无效。
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！错误码见NRTCChatPubSubErrorCode。
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_publish_video(const char* json_extension, nrtc_chat_opt_cb_func cb, const void* user_data);

/** @fn void nrtc_chat_unpublish_video(const char *json_extension, nrtc_chat_opt_cb_func cb, const void *user_data)
 * NRTC 通话中设置自己的视频数据取消发布接口。该接口仅限于多人通话模式，且通话未发起时设置失败。
 * 回调结果只代表本地的操作结果，远端是否成功等对应的通知kNRTCChatNotifyPublishVideoRet及kNRTCChatNotifyUnpublishVideoRet
 * @param[in] json_extension 无效扩展字段
 * @param[in] cb 结果回调见nrtc_chat_def.h，返回的json_extension无效。
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！错误码见NRTCChatPubSubErrorCode。
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_unpublish_video(const char* json_extension, nrtc_chat_opt_cb_func cb, const void* user_data);

/** @fn nrtc_chat_subscribe_video(__int64 uid, enum NRTCChatPublishVideoSimulcastRes video_simulcast_res, const char *json_extension,
 * nrtc_chat_opt_cb_func cb, const void *user_data) NRTC 通话中设置订阅某一方的视频数据，该接口仅限于多人通话模式，且通话未发起时设置失败。
 * 回调结果只代表本地的操作结果，远端是否成功等对应的通知kNRTCChatNotifySubscribeVideoRet及kNRTCChatNotifyUnsubscribeVideoRet
 * @param[in] uid 用户uid
 * @param[in] video_simulcast_res 订阅的数据流类型
 * @param[in] json_extension 无效扩展字段
 * @param[in] cb 结果回调见nrtc_chat_def.h，返回的json_extension带有kNRTCChatId，即调用时传入的uid；错误码见NRTCChatPubSubErrorCode。
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_subscribe_video(__int64 uid,
                                                enum NRTCChatPublishVideoSimulcastRes video_simulcast_res,
                                                const char* json_extension,
                                                nrtc_chat_opt_cb_func cb,
                                                const void* user_data);

/** @fn nrtc_chat_unsubscribe_video(__int64 uid, const char *json_extension, nrtc_chat_opt_cb_func cb, const void *user_data)
 * NRTC 通话中设置订阅某一方的视频数据，该接口仅限于多人通话模式，且通话未发起时设置失败。
 * 回调结果只代表本地的操作结果，远端是否成功等对应的通知kNRTCChatNotifySubscribeVideoRet及kNRTCChatNotifyUnsubscribeVideoRet
 * @param[in] uid 用户uid
 * @param[in] json_extension 无效扩展字段
 * @param[in] cb 结果回调见nrtc_chat_def.h，返回的json_extension带有kNRTCChatId，即调用时传入的uid；错误码见NRTCChatPubSubErrorCode。
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_unsubscribe_video(__int64 uid, const char* json_extension, nrtc_chat_opt_cb_func cb, const void* user_data);

/** @fn void nrtc_chat_subscribe_audio(bool sub, const char *json_extension, nrtc_chat_opt_cb_func cb, const void *user_data)
 * NRTC 通话中设置订阅音频数据，默认自动订阅。音频数据没有单独订阅某一成员的接口。该接口仅限于多人通话模式，且通话未发起时设置失败。
 * 回调结果只代表本地的操作结果，远端是否成功等对应的通知kNRTCChatNotifySubscribeAudioRet及kNRTCChatNotifyUnsubscribeAudioRet
 * @param[in] sub 是否订阅音频数据
 * @param[in] json_extension 无效扩展字段
 * @param[in] cb 结果回调见nrtc_chat_def.h，返回的json_extension无效。错误码见NRTCChatPubSubErrorCode。
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_subscribe_audio(bool sub, const char* json_extension, nrtc_chat_opt_cb_func cb, const void* user_data);

/** @fn void nrtc_chat_set_remote_audio_data_cb(__int64 id, nrtc_chat_remote_audio_data_cb_func remote_data_cb, const void *remote_data_cb_user_data,
 * const char *json_extension, nrtc_chat_opt_cb_func cb, const void *user_data) NRTC DEVICE
 * 监听远端音频数据扩展接口，成员进入后才能设置，成员退出后设置失效
 * @param[in] id 远端用户id
 * @param[in] remote_data_cb 数据回调见nrtc_chat_def.h。该数据回调为同步回调，需要保证快速处理，防止影响音频播放。
 * @param[in] remote_data_cb_user_data APP的自定义用户数据，SDK只负责传回给回调函数remote_data_cb，不做任何处理！
 * @param[in] json_extension 扩展
 * @param[in] cb 结果回调见nrtc_chat_def.h，返回的code及json_extension无效
 * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
NRTC_SDK_DLL_API void nrtc_chat_set_remote_audio_data_cb(__int64 id,
                                                         nrtc_chat_remote_audio_data_cb_func remote_data_cb,
                                                         const void* remote_data_cb_user_data,
                                                         const char* json_extension,
                                                         nrtc_chat_opt_cb_func cb,
                                                         const void* user_data);
};
#endif  // NRTC_CHAT_API_CLIENT_H_