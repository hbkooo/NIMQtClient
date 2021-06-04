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
#include "sessionitem.h"
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

    /**
     * 新增一条最近会话 item
     * @param data 最近会话数据
     * @param row 插入的行数，如果是-1则插入到最后，否则插入到第 row 行
     */
    void AddSessionItem(const nim::SessionData &data, int row= -1);  // 向列表中新增一个item消息
    void removeOneItem(int row);          // 删除列表中第row行的item消息
    void UpdateSessionItem(const nim::SessionData &sessionData);      //向某个位置添加一个条目

    const QList<SessionItem*> & getAllSessionItems() const { return sessionItems; }

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

private:
    QList<SessionItem*> sessionItems;                   // 所有的条目信息

signals:
    void UpdateSessionListSignal();
    // 新增一个会话，调用槽函数为 RecentSessionWidget::AddSessionItem
    void AddOneSessionSignal(const nim::SessionData &data, int row);
    // 更新某一个会话,调用槽函数为 RecentSessionWidget::UpdateSessionItem, MainWindow::SessionChangedSlot
    void UpdateSessionSignal(const nim::SessionData &sessionData);

    // 双击某一个会话 item ，需要打开与该好友的聊天界面
    void OpenChattingWindowSignal(const nim::SessionData &sessionData);

public slots:
//    void UpdateSessionListSlot();

};

#endif // MESSAGELISTWIDGET_H
