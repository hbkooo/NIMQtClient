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
#include <QMap>

#include "recentSessionWidget/message.h"
#include "recentSessionWidget/sessionitem.h"
#include "recentSessionWidget/recentsessionwidget.h"
#include "friendsWidget/friendlistwidget.h"
#include "chattingWidget/chattingwindow.h"
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

private:
    /**
     * 在主界面中管理所有已经打开的聊天窗口。
     * 因为聊天窗口可能是从最近会话中打开，也可能从联系人中打开
     * 不过针对每一个联系人会话，只能存在一个聊天窗口。
     * 所以统一在主界面中管理所有的聊天窗口
     * 其中 QString 表示联系人的唯一  accID ，ChattingWindow* 表示与该联系人打开的聊天窗口
     */
    QMap<QString, ChattingWindow*> chattingWindows;

public slots:
    void toolLabelChecked();                    // 选项卡按钮选中之后槽函数，主要更新按钮的样式、显示点击的界面窗口

    // 从好友列表中双击某一个好友打开聊天界面
    void OpenChattingWindowFromFriendListsSlot(const nim::UserNameCard &userNameCard);
    // 从最近会话中双击某一个会话打开聊天界面
    void OpenChattingWindowFromRecentSessionSlot(const nim::SessionData &sessionData);
    // 关闭某一个聊天界面
    void CloseChattingWindowSlot(const QString& id);
};

#endif // WIDGET_H
