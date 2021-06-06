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
#include "util/toollabel.h"
#include "util/clickablelabel.h"
#include "userinfo/userinfowidget.h"
#include "addFriend/addfriendwidget.h"

#include "client.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QString accID_, QWidget *parent = nullptr);
    ~MainWindow() override;

    void updateMyHeader();      // 更新主界面的用户头信息

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    void InitControl();
    void SetLayout();
    void SetConnect();

    // 更新用户的头像
    void updateHeaderPhotoIcon();

private:
    // 登录成功后注册全局回调，此回调主要是判断聊天时消息是否发送成功
    void RegisterSendMsg();
    void OnSendMsgCallback(const nim::SendMessageArc& messageArc);
    // 登录成功之后注册消息接收的全局广播通知，主要是收到其他用户发送来的消息
    void RegisterReceiveMsg();
    void OnReceiveMsgCallback(const nim::IMMessage& message);

private:

    ClickableLabel *headerPhotoLabel;           // 用户头像
    QLabel *nameLabel;                          // 用户昵称或 accID，如果昵称为空，则显示 accID
    QLabel *signatureLabel;                     // 用户签名
    QWidget *headerWidget;                      // 用户头信息的综合控件

    QList<ToolLabel*> toolLabels;               // 选项卡中的按钮控件列表

    QStackedWidget *mainStackedWidget;          // 主界面的堆栈窗口
    RecentSessionWidget *recentSessionWidget;   // 消息列表控件
    FriendListWidget *friendListWidget;         // 好友列表

    ClickableLabel *addFriendLabel;             // 添加好友

    QVBoxLayout *layout;                        // 界面的主布局

private:
    /**
     * 在主界面中管理所有已经打开的聊天窗口。
     * 因为聊天窗口可能是从最近会话中打开，也可能从联系人中打开
     * 不过针对每一个联系人会话，只能存在一个聊天窗口。
     * 所以统一在主界面中管理所有的聊天窗口
     * 其中 QString 表示联系人的唯一  accID ，ChattingWindow* 表示与该联系人打开的聊天窗口
     */
    QMap<QString, ChattingWindow*> chattingWindows;

    QString accID;      // 登录成功的该用户 id

    UserInfoWidget *userInfoWidget = nullptr;       // 显示、修改用户信息窗口
    AddFriendWidget *addFriendWidget = nullptr;     // 添加好友窗口

signals:
    void LogoutSignal();                        // 退出登录信号，发送到LoginWindow::OnLogoutSlot槽函数
    // 发送消息之后会有一个消息回调,RecentSessionWidget::sendMsgCallbackSignal
    void sendMsgCallbackSignal(const nim::SendMessageArc& messageArc);
    // APP收到一条消息，需要将消息转发给对应的聊天窗口中,RecentSessionWidget::receiveMsgSignal
    void receiveMsgSignal(const nim::IMMessage &msg);

public slots:

    // 点击用户头像槽函数。主要实现打开用户详细信息界面，然后用户可以修改
    void ClickHeaderPhotoSlot();
    // 点击添加好友按钮。实现打开添加好友界面，搜索添加好友
    void ClickAddFriendLabelSlot();

    // 选项卡按钮选中之后槽函数，主要更新按钮的样式、显示点击的界面窗口
    void toolLabelChecked();

    // 如果《好友名片》或者《好友关系》或者《最近会话》发生变化，需要将好友数据传递给已经打开的聊天界面中
    void UserCardChangeToChattingWindowSlot(const nim::UserNameCard &nameCard);
    void FriendProfileChangeToChattingWindowSlot(const nim::FriendProfile &friendProfile);
    void SessionChangToChattingWindowSlot(const nim::SessionData &sessionData);

    // 从好友列表中双击某一个好友打开聊天界面
    void OpenChattingWindowFromFriendListsSlot(const nim::UserNameCard &userNameCard);
    // 从最近会话中双击某一个会话打开聊天界面
    void OpenChattingWindowFromRecentSessionSlot(const nim::SessionData &sessionData);
    // 关闭某一个聊天界面
    void CloseChattingWindowSlot(const QString& id);

};

#endif // WIDGET_H
