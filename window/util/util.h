//
// Created by 19216 on 2021/5/31.
//

#ifndef NIMQTCLIENT_UTIL_H
#define NIMQTCLIENT_UTIL_H
#include "QPixmap"

/**
 * 生成圆形的图片头像
 * @param src 原图像，QPixmap
 * @param radius 原方形图像边长的一半
 * @return
 */
QPixmap PixmapToRound(const QPixmap &src, int radius);

/**
 * 判断是否插入时间提示。只有当前消息记录与上一条消息记录相差5分钟时，即插入当前消息的具体时间提示信息。
 * @param current_time 前一条消息的时间
 * @param last_time 后一条消息的时间
 * @return
 */
bool IsInsertTimePromptInfo(int64_t current_time, int64_t last_time);

/**
 * 在聊天窗口界面中，要显示某一条消息是发送时间，格式化输出的时间信息
 * @param msg_time_tag 时间，距离1970年的毫秒数。（注意：不是秒数）
 * @return 返回格式化后显示的字符串
 */
QString FormatTimeInfoInChattingWindow(int64_t msg_time_tag);

/**
 * 在会话列表的一个item中要显示的时间信息
 * @param msg_time_tag 时间，距离1970年的毫秒数。（注意：不是秒数）
 * @return 返回格式化后的时间字符串
 */
QString FormatTimeInRecentSession(int64_t msg_time_tag);

#endif //NIMQTCLIENT_UTIL_H
