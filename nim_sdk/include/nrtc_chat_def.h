/** @file nrtc_chat_def.h
 * @brief NRTC提供的音视频接口定义，
 * @copyright (c) 2015-2016, NetEase Inc. All rights reserved
 * @author gq
 * @date 2015/5/5
 */

#ifndef NRTC_API_CHAT_DEF_H_
#define NRTC_API_CHAT_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @enum NRTCChatMode 音视频通话类型 */
enum NRTCChatMode {
    kNRTCChatModeAudio = 1, /**< 音频 */
    kNRTCChatModeVideo = 2, /**< 视频 */
};

/** @enum NRTCChatConnectStatus 视频通话连接状态 */
enum NRTCChatConnectStatus {
    kNRTCChatConnectNone = 0,  /**< 不在通话中 */
    kNRTCChatConnecting = 1,   /**< 正在连接中 */
    kNRTCChatConnected = 2,    /**< 正在通话中 */
    kNRTCChatReConnecting = 3, /**< 正在重新连接中 */
    kNRTCChatDisconnect = 4,   /**< 连接断开 */
};

/** @enum NRTCChatVideoQuality 视频通话分辨率 */
enum NRTCChatVideoQuality {
    kNRTCChatVideoQualityNormal = 0, /**< 视频默认分辨率 480x360 */
    kNRTCChatVideoQualityLow = 1,    /**< 视频低分辨率 256x144 */
    kNRTCChatVideoQualityMedium = 2, /**< 视频中分辨率 352x288 */
    kNRTCChatVideoQualityHigh = 3,   /**< 视频高分辨率 480x360 */
    kNRTCChatVideoQuality480p = 4,   /**< 视频480p分辨率 640x480 */
    kNRTCChatVideoQuality540p = 5,   /**< 介于720P与480P之间的类型，默认 960*540 */
    kNRTCChatVideoQuality720p = 6, /**< 用于桌面分享级别的分辨率1280x720，需要使用高清摄像头并指定对应的分辨率，或者自定义通道传输 */
};

/** @enum NRTCChatVideoFrameRate 视频通话帧率，实际帧率因画面采集频率和机器性能限制可能达不到期望值 */
enum NRTCChatVideoFrameRate {
    kNRTCChatVideoFrameRateNormal = 0, /**< 视频通话帧率默认值,最大取每秒15帧 */
    kNRTCChatVideoFrameRate5 = 1,      /**< 视频通话帧率 最大取每秒5帧 */
    kNRTCChatVideoFrameRate10 = 2,     /**< 视频通话帧率 最大取每秒10帧 */
    kNRTCChatVideoFrameRate15 = 3,     /**< 视频通话帧率 最大取每秒15帧 */
    kNRTCChatVideoFrameRate20 = 4,     /**< 视频通话帧率 最大取每秒20帧 */
    kNRTCChatVideoFrameRate25 = 5,     /**< 视频通话帧率 最大取每秒25帧 */
};

/** @enum NRTCChatUserLeftType 成员退出类型 */
enum NRTCChatUserLeftType {
    kNRTCChatUserLeftTimeout = -1, /**< 成员超时掉线 */
    kNRTCChatUserLeftNormal = 0,   /**< 成员离开 */
};

/** @enum NRTCChatNetStatus 网络状态类型 */
enum NRTCChatNetStatus {
    kNRTCChatNetStatusVideoClose = -1, /**< 网络状态极差，视频强制关闭 */
    kNRTCChatNetStatusGood = 0,        /**< 网络状态较好 */
    kNRTCChatNetStatusPoor = 1,        /**< 网络状态较差 */
    kNRTCChatNetStatusBad = 2,         /**< 网络状态很差 */
};

/** @enum NRTCChatMp4RecordCode mp4录制状态 */
enum NRTCChatMp4RecordCode {
    kNRTCChatMp4RecordClose = 0,          /**< MP4结束 */
    kNRTCChatMp4RecordVideoSizeError = 1, /**< MP4结束，视频画面大小变化 */
    kNRTCChatMp4RecordOutDiskSpace = 2,   /**< MP4结束，磁盘空间不足 */
    kNRTCChatMp4RecordThreadBusy = 3,     /**< MP4结束，录制线程繁忙 */
    kNRTCChatMp4RecordCreate = 200,       /**< MP4文件创建 */
    kNRTCChatMp4RecordStart = 201,        /**< MP4文件创建 */
    kNRTCChatMp4RecordExsit = 400,        /**< MP4文件已经存在 */
    kNRTCChatMp4RecordCreateError = 403,  /**< MP4文件创建失败 */
    kNRTCChatMp4RecordInvalid = 404,      /**< 通话不存在 */
};

/** @enum NRTCChatAudioRecordCode 音频录制状态 */
enum NRTCChatAudioRecordCode {
    kNRTCChatAudioRecordClose = 0,         /**< 录制正常结束 */
    kNRTCChatAudioRecordOutDiskSpace = 2,  /**< 录制结束，磁盘空间不足 */
    kNRTCChatAudioRecordCreate = 200,      /**< 文件创建成功 */
    kNRTCChatAudioRecordExsit = 400,       /**< 已经存在 */
    kNRTCChatAudioRecordCreateError = 403, /**< 文件创建失败 */
    kNRTCChatAudioRecordInvalid = 404,     /**< 通话不存在 */
};

/** @enum NRTCChatConnectEventType 音视频服务器连接状态类型 */
enum NRTCChatConnectEventType {
    kNRTCChatConnectEventReserve = 1, /**< 获取服务器错误 NRTCChatReserveErrorCode */
    kNRTCChatConnectEventJoin = 2,    /**< 连接服务器错误 NRTCChatJoinErrorCode */
    kNRTCChatConnectEventLocal = 3,   /**< 本地错误 NRTCChatLocalErrorCode */
};

/** @enum NRTCChatReserveErrorCode 获取服务器错误 （正常请求时不会有此类错误返回） */
enum NRTCChatReserveErrorCode {
    kNRTCChatReserveDataError = 0,         /**< 数据错误 */
    kNRTCChatReserveTimeOut = 101,         /**< 请求超时 */
    kNRTCChatReserveErrorParam = 414,      /**< 服务器请求参数错误 */
    kNRTCChatReserveMoreThanTwoUser = 600, /**< 只支持两个用户, 有第三个人试图使用相同的频道名分配频道 */
    kNRTCChatReserveServerFail = 601,      /**< 分配频道服务器出错 */
};

/** @enum NRTCChatJoinErrorCode 连接服务器错误 */
enum NRTCChatJoinErrorCode {
    kNRTCChatJoinTimeout = 101,          /**< 超时 */
    kNRTCChatJoinMeetingModeError = 102, /**< 会议模式错误 */
    kNRTCChatJoinRtmpModeError = 103,    /**< rtmp用户加入非rtmp频道 */
    kNRTCChatJoinRtmpNodesError = 104,   /**< 超过频道最多rtmp人数限制 */
    kNRTCChatJoinRtmpHostError = 105,    /**< 已经存在一个主播 */
    kNRTCChatJoinRtmpCreateError = 106,  /**< 需要旁路直播, 但频道创建者非主播 */
    kNRTCChatJoinServerValidError = 107, /**< 服务器验证内部错误 */
    kNRTCChatJoinChannelClosed = 108,    /**< 频道已经关闭 */
    kNRTCChatJoinSuccess = 200,          /**< 连接成功 */
    kNRTCChatJoinLayoutError = 208,      /**< 主播自定义布局错误 */
    kNRTCChatJoinInvalidParam = 400,     /**< 错误参数 */
    kNRTCChatJoinDesKey = 401,           /**< 密码加密错误 */
    kNRTCChatJoinInvalidRequst = 417,    /**< 错误请求 */
    kNRTCChatJoinServerUnknown = 500,    /**< 服务器内部错误 */
    kNRTCChatJoinChannelBusy = 9104,     /**< 通道繁忙 */
};

/** @enum NRTCChatLocalErrorCode 本地错误  */
enum NRTCChatLocalErrorCode {
    kNRTCChatLocalChannelStartFail = 11000,    /**< 通道发起失败 */
    kNRTCChatLocalChannelDisconnected = 11001, /**< 断开连接 */
    kNRTCChatLocalVersionSelfLow = 11002,      /**< 本人SDK版本太低不兼容 */
    kNRTCChatLocalVersionRemoteLow = 11003,    /**< 对方SDK版本太低不兼容 */
    kNRTCChatLocalChannelClosed = 11004,       /**< 通道被关闭 */
    kNRTCChatLocalChannelKicked = 11005,       /**< 账号被踢 */
    kNRTCChatLocalInvalid = 11403,             /**< 无效的操作 */
};

/** @enum NRTCChatVideoSplitMode 主播设置的直播分屏模式  */
enum NRTCChatVideoSplitMode {
    kNRTCSplitBottomHorFloating = 0,  /**< 底部横排浮窗 */
    kNRTCSplitTopHorFloating = 1,     /**< 顶部横排浮窗 */
    kNRTCSplitLatticeTile = 2,        /**< 平铺 */
    kNRTCSplitLatticeCuttingTile = 3, /**< 裁剪平铺 */
    kNRTCSplitCustomLayout = 4,       /**< 自定义布局 */
    kNRTCSplitAudioLayout = 5,        /**< 纯音频布局 */
};

/** @enum NRTCChatVideoFrameScaleType 视频画面长宽比，裁剪时不改变横竖屏，如4：3，代表宽高横屏4：3或者竖屏3：4  */
enum NRTCChatVideoFrameScaleType {
    kNRTCChatVideoFrameScaleNone = 0, /**< 默认，不裁剪 */
    kNRTCChatVideoFrameScale1x1 = 1,  /**< 裁剪成1：1的形状 */
    kNRTCChatVideoFrameScale4x3 = 2,  /**< 裁剪成4：3的形状，如果是 */
    kNRTCChatVideoFrameScale16x9 = 3, /**< 裁剪成16：9的形状 */
};

/** @enum NRTCChatLiveStateCode 直播时的状态码。服务器定时更新，一些存在时间短的状态会获取不到  */
enum NRTCChatLiveStateCode {
    kNRTCChatLiveStateInitial = 500,
    kNRTCChatLiveStateLayoutError = 501,     /**< 主播设置定制布局，布局参数错误 */
    kNRTCChatLiveStateStartConnecting = 502, /**< 开始连接 */
    kNRTCChatLiveStateConnectted = 503,      /**< 连接成功 */
    kNRTCChatLiveStateConnectFail = 504,     /**< 连接失败 */
    kNRTCChatLiveStatePushing = 505,         /**< 推流中 */
    kNRTCChatLiveStatePushFail = 506,        /**< 互动直播推流失败 */
    kNRTCChatLiveStateInnerError = 507,      /**< 内部错误 */
    kNRTCChatLiveStatePeopleLimit = 508,     /**< 人数超出限制 */
};

/** @enum NRTCChatVideoEncodeMode 视频编码策略  */
enum NRTCChatVideoEncodeMode {
    kNRTCChatVEModeNormal = 0,    /**< 默认值，清晰优先 */
    kNRTCChatVEModeFramerate = 1, /**< 流畅优先 */
    kNRTCChatVEModeQuality = 2,   /**< 清晰优先 */
    kNRTCChatVEModeScreen = 3,    /**< 屏幕共享场景调控策略，sdk不会根据网络调整分辨率 */
};

/** @enum NRTCChatAudioMode 音频模式  */
enum NRTCChatAudioMode {
    kNRTCChatAdModeDefault = 0,  /**< 默认值 为kNRTCChatAdModeHighVoip */
    kNRTCChatAdModeNormal = 1,   /**< 窄带语音 */
    kNRTCChatAdModeHighVoip = 2, /**< 高清语音 */
    kNRTCChatAdModeHighMusic = 3, /**< 高清音乐。注意：高清音乐模式仅限耳机场景下使用，其他场景可能导致音频质量不佳 */
};

/** @enum NRTCChatMainPictureOptCode 房间主画面设置返回码 */
enum NRTCChatMainPictureOptCode {
    kNRTCMainPictureOptSucess = 200,       /**< 操作成功 */
    kNRTCMainPictureOptAuthError = 401,    /**< 认证错误 */
    kNRTCMainPictureOptRoomNotExist = 404, /**< 房间不存在 */
    kNRTCMainPictureOptUidNotExist = 405,  /**< 房间下的uid不存在 */
    kNRTCMainPictureOptDataError = 417,    /**< 请求数据不对 */
    kNRTCMainPictureOptError = 500,        /**< 内部错误 */
    kNRTCMainPictureOptServerError = 600,  /**< 服务器内部错误 */
    kNRTCMainPictureOptInvalid = 11403,    /**< 无效的操作 */
};

/** @enum NRTCChatServRecordType 服务器录制模式，用于指定本人数据录制选择 */
enum NRTCChatServRecordType {
    kNRTCChatServRecordMixedSingle = 0, /**< 服务器录制混录并带单人文件 */
    kNRTCChatServRecordMixed = 1,       /**< 服务器录制只混录 */
    kNRTCChatServRecordSingle = 2,      /**< 服务器录制只录本人单人文件 */
};

/** @enum NRTCChatPubSubNotifyType 订阅及发布相关通知类型 */
enum NRTCChatPubSubNotifyType {
    kNRTCChatNotifyPublishVideoRet = 0,      /**< 本地视频发布操作的结果返回通知 */
    kNRTCChatNotifyUnpublishVideoRet = 1,    /**< 本地取消视频发布操作的结果返回通知 */
    kNRTCChatNotifyRemotePublishVideo = 2,   /**< 远端视频发布通知 */
    kNRTCChatNotifyRemoteUnpublishVideo = 3, /**< 远端视频停止发布通知 */
    kNRTCChatNotifySubscribeVideoRet = 4,    /**< 本地订阅远端视频操作的结果返回通知 */
    kNRTCChatNotifyUnsubscribeVideoRet = 5,  /**< 本地取消订阅远端视频操作的结果返回通知 */
    kNRTCChatNotifySubscribeAudioRet = 6,    /**< 本地订阅远端音频操作的结果返回通知 */
    kNRTCChatNotifyUnsubscribeAudioRet = 7,  /**< 本地取消订阅远端音频操作的结果返回通知 */
};
/** @enum NRTCChatPublishVideoStreamMode 发布视频流模式 */
enum NRTCChatPublishVideoStreamMode {
    kNRTCChatPublishVideoSingleStream = 0, /**< 发布单流模式（默认） */
    kNRTCChatPublishVideoDualStream = 1,   /**< 发布双流模式 */
};
/** @enum NRTCChatPublishVideoSimulcastRes 视频流类型 */
enum NRTCChatPublishVideoSimulcastRes {
    kNRTCChatPublishVideoSimulcastResHigh = 0, /**< 高分辨率视频流 */
    kNRTCChatPublishVideoSimulcastResLow = 2,  /**< 低分辨率视频流 */
};

/** @enum NRTCChatPubSubErrorCode 订阅及发布相关通知类型 */
enum NRTCChatPubSubErrorCode {
    kNRTCChatPSErrCodeSuccess = 0,       /**< 成功 */
    kNRTCChatPSErrCodeFail = -1,         /**< 失败 */
    kNRTCChatPSErrCodeViewerMode = -200, /**< 发布操作失败，当前为观众模式 */
    kNRTCChatPSErrCodeAudioMode = -300,  /**< 视频发布操作失败，当前为音频模式 */
    kNRTCChatPSErrCodeOptBusy = -400,    /**< 操作繁忙 */
    kNRTCChatPSErrCodeAutoMode = -500,   /**< 模式互斥 （当前是自动发布） */
    kNRTCChatPSErrCodeForbid = -600,     /**< 操作无效，对点对模式不支持订阅相关功能 */
    kNRTCChatPSErrCodeSubscribed = -700, /**< 操作无效，视频类型冲突，需要取消之前订阅的流 */
};
/** @enum NRTCChatStreamEncryptType 流媒体加密类型 */
enum NRTCChatStreamEncryptType {
    kNRTCChatStreamEncryptTypeNone = 0,      /**< 默认不加密 */
    kNRTCChatStreamEncryptTypeAES128ECB = 2, /**< AES 128位ECB模式加密 */
    kNRTCChatStreamEncryptTypeAES256CBC = 3, /**< AES 256位CBC模式加密 */
    kNRTCChatStreamEncryptTypeAES256CTR = 4, /**< AES 256位CTR模式加密 */
    kNRTCChatStreamEncryptTypeAES128XTS = 5, /**< AES 128位XTS模式加密 */
    kNRTCChatStreamEncryptTypeAES256XTS = 6, /**< AES 256位XTS模式加密 */
};

/** @enum NRTCChatServerSubscribeFallbackStrategy 服务器在下行弱网的时候切流策略 */
enum NRTCChatServerSubscribeFallbackStrategy {
    kNRTCChatSteamFallbackStrategyDisabled = 0,  /**< 禁用服务器弱网切流策略 */
    kNRTCChatSteamFallbackStrategyAudioOnly = 2, /**< 默认策略允许服务器切小流、关视频 */
};

/** @name json extension params for nrtc_chat_join_channel
 * 开始通话参数,默认为空或0，可以选填
 * @{
 */
static const char* kNRTCChatCustomVideo = "custom_video";    /**< int 是否使用自定义视频数据 >0表示是 */
static const char* kNRTCChatCustomAudio = "custom_audio";    /**< int 是否使用自定义音频数据 >0表示是 */
static const char* kNRTCChatMaxVideoRate = "max_video_rate"; /**< int 视频发送编码码率上限 >=100000 <=5000000有效 */
static const char* kNRTCChatRecord = "record"; /**< int 是否需要录制音频数据 >0表示是 （需要服务器配置支持，本地录制直接调用接口函数） */
static const char* kNRTCChatVideoRecord = "video_record"; /**< int 是否需要录制视频数据 >0表示是 （需要服务器配置支持，本地录制直接调用接口函数） */
static const char* kNRTCChatRecordType = "record_type"; /**< int 服务器录制模式NRTCChatServRecordType，默认为0
                                                           （需要服务器配置支持，并且开kNRTCChatRecord，kNRTCChatVideoRecord其中一个） */
static const char* kNRTCChatRHostSpeaker =
    "r_host_speaker";                                       /**< int 服务器混录时指定本人主画面，默认为0,
                                                               非0表示打开（需要服务器配置支持，及录制模式打开混录，并且为多人中的第一个主画面配置） */
static const char* kNRTCChatVideoQuality = "video_quality"; /**< int 视频聊天分辨率选择 NRTCChatVideoQuality */
static const char* kNRTCChatVideoFrameRate = "frame_rate";  /**< int 视频画面帧率 NRTCChatVideoFrameRate */
static const char* kNRTCChatAudioMode = "audio_mode";       /**< int 音频模式选择 */
static const char* kNRTCChatMeetingMode = "meeting_mode";   /**< int 是否使用多人模式 >0表示是 */
static const char* kNRTCChatRtmpUrl =
    "rtmp_url"; /**< string 直播推流地址(加入多人时有效)，非空代表主播旁路直播， kNRTCChatBypassRtmp决定是否开始推流 */
static const char* kNRTCChatBypassRtmp = "bypass_rtmp"; /**< int 是否旁路推流（如果rtmpurl为空是连麦观众，非空是主播的推流控制）， >0表示是 */
static const char* kNRTCChatRtmpRecord = "rtmp_record"; /**< int 是否开启服务器对直播推流录制（需要开启服务器能力）， >0表示是 */
static const char* kNRTCChatSplitMode = "split_mode"; /**< int 主播控制的直播推流时的分屏模式，见NRTCChatVideoSplitMode */
static const char* kNRTCChatCustomLayout =
    "custom_layout"; /**< string 自定义布局，当主播选择kNRTCSplitCustomLayout和kNRTCSplitAudioLayout模式时生效 */
static const char* kNRTCChatVEncodeMode = "v_encode_mode"; /**< int, 使用的视频编码策略NRTCChatVideoEncodeMode， 默认kNRTCChatVEModeNormal */
static const char* kNRTCChatServerSubscribeFallbackStrategy =
    "server_sub_fb_stategy"; /**< int,服务器在下行弱网的时候切流策略NRTCChatServerSubscribeFallbackStrategy，
                                默认kNRTCChatSteamFallbackStrategyAudioOnly */

/** @}*/  // json extension params

/** @name json extension params for nrtc_chat_session_status_cb_func
 * @{
 */
static const char* kNRTCChatLogin = "login"; /**< key 登录成功 kNRTCChatChannelID kNRTCChatVideoRecordFile kNRTCChatRecordFile */
static const char* kNRTCChatLogout =
    "logout"; /**< key 退出 kNRTCChatTrafficStatRX kNRTCChatTrafficStatTX kNRTCChatTime(估计的通话时长，以服务器抄送为准) */
static const char* kNRTCChatLiveState = "live_state";   /**< key 直播状态 kNRTCChatStatus(NRTCChatLiveStateCode) */
static const char* kNRTCChatError = "error";            /**< key 错误通知 kNRTCChatType(NRTCChatConnectEventType) kNRTCChatStatus */
static const char* kNRTCChatUserJoined = "user_joined"; /**< key 成员进入 kNRTCChatId */
static const char* kNRTCChatUserLeft = "user_left";     /**< key 成员离开 kNRTCChatId kNRTCChatStatus(NRTCChatUserLeftType) */
static const char* kNRTCChatNetStatus = "net";          /**< key 网络状态 kNRTCChatId kNRTCChatStatus(NRTCChatNetStatus) */
static const char* kNRTCChatControlNotify = "control_notify"; /**< key （废弃）成员通知状态 kNRTCChatMute kNRTCChatCamera kNRTCChatMode，可缺省通知 */
static const char* kNRTCChatMp4Start = "mp4_start"; /**< key Mp4写入数据开始 kNRTCChatMp4File kNRTCChatTime，如果非本人带kNRTCChatId */
static const char* kNRTCChatMp4Close = "mp4_close"; /**< key 结束Mp4录制，返回时长及原因 kNRTCChatStatus(NRTCChatMp4RecordCode) kNRTCChatTime
                                                       kNRTCChatMp4File，如果非本人带kNRTCChatId */
static const char* kNRTCChatAuRecordStart = "audio_record_start"; /**< key 音频录制写入数据开始 kNRTCChatFile kNRTCChatTime */
static const char* kNRTCChatAuRecordClose =
    "audio_record_close"; /**< key 结束音频录制，返回时长及原因 kNRTCChatStatus(NRTCChatAudioRecordCode) kNRTCChatTime kNRTCChatFile */
static const char* kNRTCChatIds = "ids";                    /**< key 成员id列表 */
static const char* kNRTCChatVideo = "video";                /**< key 视频 */
static const char* kNRTCChatVideoType = "v_type";           /**< key NRTCChatPublishVideoSimulcastRes 视频流类型 */
static const char* kNRTCChatAudio = "audio";                /**< key 音频 */
static const char* kNRTCChatStaticInfo = "static_info";     /**< key 音视频实时状态 */
static const char* kNRTCChatAudioVolume = "audio_volume";   /**< key
                                                               音频实时音量通知，包含发送的音量kNRTCChatSelf和接收音量kNRTCChatReceiver，kNRTCChatStatus的音量值是pcm的平均值最大为int16_max
                                                             */
static const char* kNRTCChatSelf = "self";                  /**< key 本人信息 */
static const char* kNRTCChatReceiver = "receiver";          /**< key 接收信息 */
static const char* kNRTCChatCpu = "cpu";                    /**< key cpu使用情况 */
static const char* kNRTCChatMemInfo = "meminfo";            /**< key 内存使用情况 */
static const char* kNRTCChatPubSubNotify = "pubsub_notify"; /**< key 订阅及发布相关的通知，包含kNRTCChatType(NRTCChatSubscribeNotifyType)
                                                               kNRTCChatStatus(NRTCChatPubSubErrorCode),远端视频额外带有kNRTCChatId */
static const char* kNRTCChatPubSubNotifyData = "pubsub_notify_data";   /**< json string 订阅发布相关通知内容 */
static const char* kNRTCChatVideoSimulcastRes = "video_simulcast_res"; /**< json int 订阅发布视频分辨率类型 */
static const char* kNRTCChatStatus = "status";                         /**< int 状态 */
static const char* kNRTCChatType = "type";                             /**< int 类型 */
static const char* kNRTCChatId = "id";                                 /**< int64 成员id */
static const char* kNRTCChatChannelID = "cid";                         /**< uint64 channel_id */
static const char* kNRTCChatRecordAddr = "record_addr";                /**< string 录制地址（服务器开启录制时有效） */
static const char* kNRTCChatRecordFile = "record_file";            /**< string 服务器音频录制文件名（服务器开启录制时有效） */
static const char* kNRTCChatVideoRecordFile = "video_record_file"; /**< string 服务器视频录制文件名（服务器开启录制时有效） */
static const char* kNRTCChatTrafficStatRX = "trafficstat_rx";      /**< uint64 下行流量（字节） */
static const char* kNRTCChatTrafficStatTX = "trafficstat_tx";      /**< uint64 上行流量（字节） */
static const char* kNRTCChatMute = "mute";                         /**< bool 成员通知静音状态 */
static const char* kNRTCChatCamera = "camera";                     /**< bool 成员通知摄像头是否工作 */
static const char* kNRTCChatMode = "mode";                         /**< int 成员通知通话模式（NRTCChatMode） */
static const char* kNRTCChatRecordMode = "record";                 /**< bool 录制状态 */
static const char* kNRTCChatTime = "time";                         /**< int64 时间 毫秒级 */
static const char* kNRTCChatMp4File = "mp4_file";                  /**< string mp4录制地址 */
static const char* kNRTCChatFile = "file";                         /**< string 文件地址 */
static const char* kNRTCChatFPS = "fps";                           /**< int 每秒帧率或者每秒发包数 */
static const char* kNRTCChatKBPS = "KBps";                         /**< int 每秒流量，单位为“千字节” */
static const char* kNRTCChatLostRate = "lost_rate";                /**< int 丢包率，单位是百分比 */
static const char* kNRTCChatRtt = "rtt";                           /**< int rtt 网络延迟 */
static const char* kNRTCChatTotalPercent = "total_percent";        /**< int 总占用0-100百分比 */
static const char* kNRTCChatSelfPercent = "self_percent";          /**< int 本进程占用0-100百分比 */
static const char* kNRTCChatMemorySize = "memory_size";            /**< int 内存使用情况kB */
static const char* kNRTCChatMp4AudioType =
    "mp4_audio"; /**< int mp4录制时音频情况，0标识只录制当前成员，1标识录制通话全部混音（等同音频文件录制的声音） */
static const char* kNRTCChatMp4Recode = "mp4_recode"; /**< bool mp4录制时重新编码开关 */
static const char* kNRTCChatMp4Width = "mp4_width";   /**< int 录制的mp4的宽度，默认为0，小于16无效，无效时取视频默认大小 */
static const char* kNRTCChatMp4Height = "mp4_height"; /**< int 录制的mp4的高度，默认为0，小于16无效，无效时取视频默认大小 */
/** @}*/                                              // json extension params

/** @typedef void(*nrtc_chat_session_status_cb_func)(const char *json, const void *user_data)
 * NRTC 通话状态返回接口\n
 * json for example: \n
 * 	成功连接
 *{"login":{"video_record_file":"84849-6203579135172813608.mp4","record_file":"84849-6203579135172813608.aac","cid":6203579135172813608 }} \n 退出通知
 *{"logout":{"trafficstat_rx":134634, "trafficstat_tx":164645, "time":15223 }} \n 直播状态	{"live_state":{"status":505 }} \n 错误通知
 *{"error":{"status":408, "type":1 }} \n 成员进入 	{"user_joined":{"id":84834 }} \n 成员退出 	{"user_left":{"id":84834,"status":0}} \n
 *		网络状态 	{"net":{"id":84834,"status":1}} \n
 *		(废弃)成员通知 	{"control_notify":{ "camera": true, "mute": true, "mode": 2, "record": true }} \n
 *		MP4开始 	{"mp4_start":{ "mp4_file": "d:\\test.mp4", "time": 14496477000000, "id":84834 }} \n
 *		MP4结束 	{"mp4_close":{ "mp4_file": "d:\\test.mp4", "time": 120000, "status": 0, "id":84834 }} \n
 *		音频录制开始	{"audio_record_start":{ "file": "d:\\test.aac", "time": 14496477000000 }} \n
 *		音频录制结束	{"audio_record_close":{ "file": "d:\\test.aac", "time": 120000, "status": 0 }} \n
 *		实时状态 	{"static_info":{"cpu":{"self_percent":4,"total_percent":27},"meminfo":{"memory_size":32376}, "rtt":20, "video":
 *[{"v_type":0, "fps":20, "KBps":200, "lost_rate":5, "width":1280,"height":720}, {...}], "audio": {"fps":17, "KBps":3", lost_rate":3 }}} \n 音量状态
 *{"audio_volume":{ "self": {"status":600}, "receiver": [{"id":123,"status":1000},{"id":456,"status":222}] }} \n 订阅及发布
 *{"pubsub_notify":{"status":0, "type":2, "id":84834},"pubsub_notify_data":[0,2]} 或者 {"pubsub_notify":{"status":0, "type":2,
 *"id":84834},"pubsub_notify_data":{"video_simulcast_res":0}} \n
 * @param[out] json 返回的json，见上面示例
 * @param[out] user_data APP的自定义用户数据，SDK只负责传回给回调函数，不做任何处理！
 * @return void 无返回值
 */
typedef void (*nrtc_chat_session_status_cb_func)(const char* json, const void* user_data);

/** @typedef void (*nrtc_chat_mp4_record_opt_cb_func)(bool ret, int code, const char *file, __int64 time, const char *json_extension, const void
 * *user_data) NRTC MP4操作回调，实际的开始录制和结束都会在nrtc_chat_session_status_cb_func中返回
 * @param[out] ret 结果代码，true表示成功
 * @param[out] code 对应NRTCChatMp4RecordCode，用于获得失败时的错误原因
 * @param[out] file 文件路径
 * @param[out] time 录制结束时有效，对应毫秒级的录制时长
 * @param[out] json_extension Json string 无效扩展字段
 * @param[out] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
typedef void (
    *nrtc_chat_mp4_record_opt_cb_func)(bool ret, int code, const char* file, __int64 time, const char* json_extension, const void* user_data);

/** @typedef void (*nrtc_chat_audio_record_opt_cb_func)(bool ret, int code, const char *file, __int64 time, const char *json_extension, const void
 * *user_data) NRTC 音频录制操作回调，实际的开始录制和结束都会在nrtc_chat_session_status_cb_func中返回
 * @param[out] ret 结果代码，true表示成功
 * @param[out] code 对应NRTCChatAudioRecordCode，用于获得失败时的错误原因
 * @param[out] file 文件路径
 * @param[out] time 录制结束时有效，对应毫秒级的录制时长
 * @param[out] json_extension Json string 无效扩展字段
 * @param[out] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
typedef void (
    *nrtc_chat_audio_record_opt_cb_func)(bool ret, int code, const char* file, __int64 time, const char* json_extension, const void* user_data);

/** @typedef void (*nrtc_chat_opt_cb_func)(bool ret, int code, const char *json_extension, const void *user_data)
 * NRTC 操作回调，通用的操作回调接口
 * @param[out] ret 结果代码，true表示成功
 * @param[out] code 用于获得失败时的错误原因；无特殊说明对应NRTCChatLocalErrorCode。
 * @param[out] json_extension Json string 扩展字段
 * @param[out] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
 * @return void 无返回值
 */
typedef void (*nrtc_chat_opt_cb_func)(bool ret, int code, const char* json_extension, const void* user_data);

/** @typedef void (*nrtc_chat_remote_audio_data_cb_func)(unsigned __int64 time, const char *data, unsigned int size, int channels, int rate, const
 * char *json_extension, const void *user_data) NRTC Device 远端音频数据监听接口
 * @param[out] time 时间毫秒级，暂时无效
 * @param[out] data 音频数据pcm格式
 * @param[out] size data的数据长度
 * @param[out] channels 通道数
 * @param[out] rate 采样频
 * @param[out] json_extension Json 扩展，返回kNRTCChatId（远端用户id）
 * @param[out] user_data APP的自定义用户数据，SDK只负责传回给回调函数，不做任何处理！
 * @return void 无返回值
 */
typedef void (*nrtc_chat_remote_audio_data_cb_func)(unsigned __int64 time,
                                                    const char* data,
                                                    unsigned int size,
                                                    int channels,
                                                    int rate,
                                                    const char* json_extension,
                                                    const void* user_data);

#ifdef __cplusplus
};
#endif  //__cplusplus
#endif  // NRTC_API_CHAT_DEF_H_