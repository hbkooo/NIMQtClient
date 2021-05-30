#ifndef MESSAGELISTWIDGET_H
#define MESSAGELISTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QListWidget>
#include <QFile>
#include <QMouseEvent>
#include <QDebug>

#include "client.h"
#include "message.h"
#include "messageitem.h"

/**
 * @brief The RecentSessionWidget class
 * 自定义列表控件，主要显示多个item消息
 */

class RecentSessionWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit RecentSessionWidget(QListWidget *parent = nullptr);

    void add_item(const Message &msg);  // 向列表中新增一个item消息
    void remove_item(int row);          // 删除列表中第row行的item消息

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);     //鼠标双击事件

private:
    // 初始化
    void InitControl();
    // 请求最近的所有会话
    void QueryAllRecentSession();
    // 最近会话请求回调
    void OnQuerySessionListCallback(int unread_count, const nim::SessionDataList& session_list);


private:
    QList<MessageItem*> messageItems;                   // 所有的条目信息

signals:
    void UpdateSessionListSignal();
    void AddOneMsg(const Message &message);

public slots:
//    void UpdateSessionListSlot();

};

#endif // MESSAGELISTWIDGET_H
