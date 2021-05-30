#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QListWidget>
#include "messageWidget/message.h"
#include "messageWidget/messageitem.h"
#include "messageWidget/recentsessionwidget.h"
#include "friendsWidget/friendlistwidget.h"

#include "client.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    // 初始化消息列表控件
    void InitRecentSessionWidget();
    void InitFriendsWidget();
    void SetLayout();
    void SetConnect();

private:
    QVBoxLayout *layout;                    // 界面的主布局

    RecentSessionWidget *recentSessionWidget;   // 消息列表控件
    FriendListWidget *friendListWidget;         // 好友列表

    signals:
    void LogoutSignal();        // 退出登录信号，发送到LoginWindow::OnLogoutSlot槽函数

};

#endif // WIDGET_H
