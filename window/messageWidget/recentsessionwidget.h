#ifndef MESSAGELISTWIDGET_H
#define MESSAGELISTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QListWidget>
#include <QFile>
#include <QMouseEvent>
#include <QDebug>

#include <algorithm>

#include "client.h"
#include "messageitem.h"
#include "chattingWidget/chattingwindow.h"

/**
 * @brief The RecentSessionWidget class
 * 自定义列表控件，主要显示多个item消息
 */

class RecentSessionWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit RecentSessionWidget(QListWidget *parent = nullptr);

    void addOneItem(const nim::SessionData &data);  // 向列表中新增一个item消息
    void removeOneItem(int row);          // 删除列表中第row行的item消息
    void UpdateItem(const nim::SessionData &sessionData, int total_unread_counts);      //向某个位置添加一个条目

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;     //鼠标双击事件

private:
    // 初始化
    void InitControl();
    // 请求最近的所有会话
    void QueryAllRecentSession();
    // 最近会话请求回调
    void OnQuerySessionListCallback(int unread_count, const nim::SessionDataList& session_list);

    // 监听最近会话变更
    void ListenRecentSessionChange();
    // 最近会话变更回调
    void OnRecentSessionChangeCallback(nim::NIMResCode, const nim::SessionData&, int);

    // 删除最近会话
    void DeleteRecentSessionItem(const nim::SessionData &msg);
    void DeleteAllRecentSession();
    void OnDeleteRecentSessionCallback(nim::NIMResCode code, const nim::SessionData &result, int total_unread_counts);

    // 未读数清零
    void RestUnread(const std::string &id, nim::NIMSessionType type);

//private:
//    QList<MessageItem*> messageItems;                   // 所有的条目信息

signals:
    void UpdateSessionListSignal();
    void AddOneMsg(const nim::SessionData &data);
    void UpdateMsg(const nim::SessionData &sessionData, int total_unread_counts);

    // 发送消息之后会有一个消息回调。发送到ChattingWindow::sendMsgCallbackSlot中。其实该信号触发于MainWindow::sendMsgCallbackSlot。
    void sendMsgCallbackSignal(const nim::SendMessageArc& messageArc);
    // APP收到一条消息，需要将消息转发给对应的聊天窗口中。发送到ChattingWindow::receiveMsgSlot中。其实该信号触发于MainWindow::receiveMsgSlot中。
    void receiveMsgSignal(const nim::IMMessage &msg);

public slots:
//    void UpdateSessionListSlot();

};

#endif // MESSAGELISTWIDGET_H
