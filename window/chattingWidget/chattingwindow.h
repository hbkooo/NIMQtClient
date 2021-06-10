//
// Created by 19216 on 2021/5/31.
//

#ifndef NIMQTCLIENT_CHATTINGWINDOW_H
#define NIMQTCLIENT_CHATTINGWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QIcon>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTextEdit>
#include <QPushButton>
#include <QMouseEvent>
#include <QPoint>
#include <QMessageBox>
#include <QEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QScrollBar>
#include <QDateTime>
#include <QDebug>
#include <QDate>

#include "chattingitem.h"
#include "teamWidget/teaminfowidget.h"
#include "userinfo/userinfowidget.h"
#include "videocommunicatewidget.h"
#include "util/util.h"
#include "util/clickablelabel.h"
#include "client.h"

/**
 * 聊天窗口。可以是 P2P 双向用户聊天，或者是 team 的多人群聊
 * 设置聊天窗口的标题，对好友的备注或者是好友自己创建账号时的昵称
 * 首先判断是否为好友关系，即获取好友列表里的每一项 FriendProfile，判断是存在该用户，如果有该用户则与其为好友关系；
 * 是好友关系的话则获取 FriendProfile 的 alias_ 字段获取对好友的备注昵称。
 * 如果昵称备注为空，则需要获取用户 UserNameCard 的 nickname_ 昵称字段。
 * 如果用户的昵称字段 nickname_ 也为空，则直接显示用户的 accID。
 */
class ChattingWindow : public QWidget {
Q_OBJECT

public:
    explicit ChattingWindow(const nim::SessionData &data, QWidget *parent = nullptr);

    ~ChattingWindow() override;

    void setSessionData(const nim::SessionData &data) { sessionData = data; }
    void setFriendProfile(const nim::FriendProfile &profile) { friendProfile = profile; }
    void setUserNameCard(const nim::UserNameCard &nameCard) { userNameCard = nameCard; }
    void setTeamInfo(const nim::TeamInfo &info) { teamInfo = info; }
    // 更新聊天界面的显示信息。主要是聊天界面的头部控件信息。一般是调用好上面的三个set方法之后然后调用该方法，更新头控件数据
    void updateChattingWindow();

private:
    void InitHeader();
    void InitCenterMessage();
    void InitBottomEnterMessage();

    void SetLayout();
    void SetConnect();

    // 更新聊天窗口的头像图标
    void updateHeaderPhotoIcon();

    // 更新中间聊天消息
    void AddOneMsgFront(const nim::IMMessage &msg, int extIndex=-1); // 在消息列表头部插入一条消息
    void AddOneMsgEnd(const nim::IMMessage &msg);    // 在消息列表尾部插入一条消息
    // 添加一条提示消息，比如时间、已显示全部消息等提示信息
    void AddPromptTimeInfo(int64_t msg_time_tag, bool end=true);

    // 展示群聊详细信息界面
    void ShowTeamInfoWidget();

private:
    /// API 获取用户信息操作
    // 获取本地用户信息
    void GetUserNameCard(const std::string & account);
    // 获取服务器用户信息
    void GetUserNameCardOnLine(const std::string & account);
    //  获取用户信息回调
    void OnGetUserCard(const std::list<nim::UserNameCard> &json_result);

    /// API 获取群成员信息操作
    void GetTeamMembers(const std::string &teamID);

private:
    // 主要是查询历史聊天记录
    QList<nim::IMMessage> chattingMsg;              // 当前显示的所有消息。这里消息的顺序是按时间逆序排列的，也就是说最新的一条消息在数组的第一条，最久远的消息在数组的最后一条
    bool hasMoreMessage = true;                     // 是否还有更多消息
    bool isQuerying = false;                        // 当前是否正在请求历史消息
    int currentTopIndex = 0;                        // 当前聊天消息的ListWidget滑动的位置，主要用来判断是否滑动到顶部
    int LIMIT_COUNT_PER_REQ = 20;                   // 每次请求消息时的最大请求数量

    // 设置消息条目中每一个消息条目的类型
    static QString NO_MORE_MSG_TAG;                 // 没有更多消息的提示信息
    static QString TIME_INFO_TAG;                   // 聊天消息的时间提示信息
    static QString NORMAL_MSG_TAG;                  // 正常的聊天消息

    // 获取聊天对象的消息记录
    void QueryMsg();
    void QueryMsgOnline(int64_t from_time=0, int64_t end_time=0, int64_t end_msg_id=0);
    void OnQueryMsgCallback(nim::NIMResCode res_code, const std::string& id,
                            nim::NIMSessionType to_type, const nim::QueryMsglogResult& result);

private:
    // 发送消息函数
    void sendTextMsgToReceiver(const std::string &msg, nim::IMMessage &message);

private:
    // 头部控件
    ClickableLabel *headerPhotoLabel;   // 头像
    QLabel *accountLabel;               // 用户名
    QLabel *stateLabel;                 // 用户在线状态

private:
    // 中间控件
    QListWidget *chattingListWidget;    // 中间聊天消息列表
    QScrollBar *verticalScrollBar;      // 垂直的滚动条
    // 键为每一个用户的唯一 accID，值为该用户的所有聊天消息 item
    QMap<std::string, QList<ChattingItem*>> usersChattingItems;

private:
    // 底部输入消息、发送消息控件
    QPushButton *audioComButton;        // 语音通话按钮
    QPushButton *videoComButton;         // 视频通话按钮
    QTextEdit *messageTextEdit;         // 输入文本消息编辑框
    QPushButton *sendButton;            // 发送消息按钮

private:
    QWidget *headerWidget;              // 聊天界面标题头总控件
    QVBoxLayout *messageLayout;         // 聊天界面中间消息列表布局
    QWidget *enterMessageWidget;        // 聊天界面输入消息总控件
    QVBoxLayout *mainLayout;            // 界面主布局

private:
    // 实际的数据存储位置在 SessionItem 类中存储
    nim::SessionData sessionData;

    // 如果是P2P的好友聊天，则需要获取二者的好友关系。
    // 默认是不存在好友关系，即没有调用该数据的 set 方法。
    nim::FriendProfile friendProfile;
    // 如果是P2P的好友聊天，还需要获取该好友的信息。userNameCard 的 accID 必须与 sessionData 的 id 是一样的。
    // 默认构造的userNameCard 的accID为空，所以如果使用时为空，则说明创建窗口时没有调用set方法，需要在这聊天窗口中重新获取用户信息
    nim::UserNameCard userNameCard;
    // 如果是群聊界面，则需要获取该群聊的消息
    nim::TeamInfo teamInfo;
    QMap<std::string, nim::UserNameCard> userNameCardMap;   // 该窗口涉及到的用户名片信息

    UserInfoWidget *userInfoWidget = nullptr;               // 查看用户详细信息界面
    TeamInfoWidget *teamInfoWidget = nullptr;               // 查看群详细信息界面


private:
    // 拖动头部可以移动窗口
    QPoint pressPoint;
    bool isMoving = false;

protected:

    void wheelEvent(QWheelEvent *event) override;       // 鼠标滚轮事件
    bool eventFilter(QObject *watched, QEvent *event) override;     // 为消息输入文本框注册事件监听
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void closeEvent(QCloseEvent* event) override;                   // 关闭窗口消息事件

    signals:
    void updateChattingWindowSignal();  // 获取完用户信息 userNameCard 之后发送信号更新聊天窗口的 header 控件。ChattingWindow::updateChattingWindow
    void updateMsgListWidgetSignal(int);
    void noMoreMessageSignal();         // 发送没有更多的聊天消息信息
    void closeChattingWindowSignal(QString id);     // 关闭该聊天界面窗口


public slots:
    // 点击聊天窗口的头像显示信息槽函数
    void ClickedHeaderPhotoLabelSlot();
    // 传递过来一个用户名片，显示用户名片。主要用在当点击聊天消息中的一条消息中的用户头像时，显示该用户的详细信息
    void ShowHeaderPhotoLabelSlot(const nim::UserNameCard &nameCard);
    // 点击语音通话按钮槽函数
    void AudioCommunicateLabelSlot();
    // 点击视频通话按钮槽函数
    void VideoCommunicateLabelSlot();
    // 点击发送按钮后发送消息槽函数
    void sendMessageSlot();
    // 刚进入聊天界面后，当从服务端获取消息记录后更新聊天界面
    void updateMsgListWidgetSlot(int msgNumber);
    // 消息发送之后会有一个发送回调，通知发送的结果。该槽函数来自于信号RecentSessionWidget::sendMsgCallbackSignal
    void sendMsgCallbackSlot(const nim::SendMessageArc& messageArc);
    // 当其他用户发送来新的消息后所有的聊天窗口界面都会收到该消息。该槽函数来自于信号RecentSessionWidget::receiveMsgSignal
    void receiveMsgSlot(const nim::IMMessage &msg);
    // 当聊天消息ListWidget滑动时触发滑动到的位置信息。以此来处理滑动到到最顶端的时候加载更多的聊天信息
    void valueChangeSlot(int position);
    // 当获取消息时，没有更多的聊天消息处理槽函数
    void noMoreMessageSlot();
};


#endif //NIMQTCLIENT_CHATTINGWINDOW_H
