/** @file nrtc_init_def.h
 * @brief NRTC提供的全局接口定义，
 * @copyright (c) 2015-2016, NetEase Inc. All rights reserved
 * @author gq
 * @date 2016/12/29
 */

#ifndef NRTC_API_INIT_DEF_H_
#define NRTC_API_INIT_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @enum NRTCNetDetectType 探测类型  */
enum NRTCNetDetectType {
    kNRTCNetDetectTypeAudio = 0, /**< 默认值，音频探测 */
    kNRTCNetDetectTypeVideo = 1, /**< 视频探测 */
};

/** @enum NRTCNetDetectVideoQuality 视频探测类型  */
enum NRTCNetDetectVideoQuality {
    kNRTCNDVideoQualityDefault = 0, /**< 480P */
    kNRTCNDVideoQualityLow = 1,     /**< 256*144 */
    kNRTCNDVideoQualityMedium = 2,  /**< 352*288 */
    kNRTCNDVideoQualityHigh = 3,    /**< 480*360 */
    kNRTCNDVideoQuality480p = 4,    /**< 640*480 */
    kNRTCNDVideoQuality540p = 5,    /**< 960*540 */
    kNRTCNDVideoQuality720p = 6,    /**< 1280*720 */
};

/** @name 初始化 内容Json key for nrtc_init
 * @{
 */
static const char* kNRTCServerSettingPath = "server_setting_path"; /**< string 服务器配置文件路径 */
/** @}*/                                                           //初始化 内容Json key

/** @name 网络探测 内容Json key for nrtc_net_detect
 * @{
 */
static const char* kNRTCAppKey = "app_key";          /**< string 用户的app key */
static const char* kNRTCNetDetectTimeLimit = "time"; /**< int32 毫秒级的探测时长限制 */
static const char* kNRTCNetDetectType = "type";      /**< int32 探测类型NRTCNetDetectType */
static const char* kNRTCNetDetectQualityType =
    "quality_type"; /**< int32 kNRTCNetDetectTypeVideo时有效，默认为0，视频探测类型NRTCNetDetectVideoQuality */
/** @}*/            //网络探测 内容Json key

/** @name 网络探测回调 内容Json key for nrtc_net_detect_cb_func
 * @{
 */
static const char* kNRTCNetDetectTaskId = "task_id";    /**< uint64 任务id */
static const char* kNRTCNetDetectLoss = "loss";         /**< int 丢包率百分比 */
static const char* kNRTCNetDetectRttmax = "rttmax";     /**< int rtt 最大值 */
static const char* kNRTCNetDetectRttmin = "rttmin";     /**< int rtt 最小值 */
static const char* kNRTCNetDetectRttavg = "rttavg";     /**< int rtt 平均值 */
static const char* kNRTCNetDetectRttmdev = "rttmdev";   /**< int rtt 偏差值 mdev */
static const char* kNRTCNetDetectDetail = "detailinfo"; /**< string 扩展信息 */
/** @}*/                                                //网络探测回调 内容Json key

/** @typedef void (*nrtc_net_detect_cb_func)(int rescode, const char *json_extension, const void *user_data)
 * 网络探测回调
 * @param[out] rescode
 * @param[out] json_extension	json数据
 * @param[out] user_data APP的自定义用户数据，SDK只负责传回给回调函数，不做任何处理！
 * @return void 无返回值
 */
typedef void (*nrtc_net_detect_cb_func)(int rescode, const char* json_extension, const void* user_data);

/** @typedef void(*nrtc_rate_callback)(bool ret, int response_code,const char* json_extension,const void* user_data);
 * 用户反馈回调
 * @param[out] ret	反馈结果
 * @param[out] response_code HTTP错误码
 * @param[out] json_extension	json数据
 * @param[out] user_data APP的自定义用户数据，SDK只负责传回给回调函数，不做任何处理！
 * @return void 无返回值
 */
typedef void (*nrtc_rate_callback)(bool ret, int response_code, const char* json_extension, const void* user_data);
#ifdef __cplusplus
};
#endif  //__cplusplus
#endif  // NRTC_API_INIT_DEF_H_