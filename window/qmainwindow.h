#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QListWidget>
#include <QTabWidget>
#include <QToolButton>
#include <QStackedWidget>

#include "messageWidget/message.h"
#include "messageWidget/messageitem.h"
#include "messageWidget/recentsessionwidget.h"
#include "friendsWidget/friendlistwidget.h"
#include "toollabel.h"

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
    void InitControl();

    // 初始化消息列表控件
    void InitRecentSessionWidget();
    void InitFriendsWidget();

    void SetLayout();
    void SetConnect();

private:
    // 登录成功后注册全局回调，此回调主要是判断聊天时消息是否发送成功
    void RegisterSendMsg();
    void OnSendMsgCallback(const nim::SendMessageArc& messageArc);
    // 登录成功之后注册消息接收的全局广播通知，主要是收到其他用户发送来的消息
    void RegisterReceiveMsg();
    void OnReceiveMsgCallback(const nim::IMMessage& message);

private:

    QHBoxLayout *toolLabelLayout;               // 不同按钮选项卡的按钮的布局
    QList<ToolLabel*> toolLabels;               // 选项卡中的按钮控件列表

    QStackedWidget *mainStackedWidget;          // 主界面的堆栈窗口
    RecentSessionWidget *recentSessionWidget;   // 消息列表控件
    FriendListWidget *friendListWidget;         // 好友列表

    QVBoxLayout *layout;                        // 界面的主布局

    signals:
    void LogoutSignal();                        // 退出登录信号，发送到LoginWindow::OnLogoutSlot槽函数
    // 发送消息之后会有一个消息回调,RecentSessionWidget::sendMsgCallbackSignal
    void sendMsgCallbackSignal(const nim::SendMessageArc& messageArc);
    // APP收到一条消息，需要将消息转发给对应的聊天窗口中,RecentSessionWidget::receiveMsgSignal
    void receiveMsgSignal(const nim::IMMessage &msg);

public slots:
    void toolLabelChecked();                    // 选项卡按钮选中之后槽函数，主要更新按钮的样式、显示点击的界面窗口
};

#endif // WIDGET_H
