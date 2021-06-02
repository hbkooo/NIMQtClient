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
#include "util/util.h"
#include "client.h"

class ChattingWindow : public QWidget {
Q_OBJECT

public:
    explicit ChattingWindow(const nim::SessionData &data, QWidget *parent = nullptr);

    ~ChattingWindow() override;
    void setSessionData(const nim::SessionData &data) {sessionData = data;}

private:
    void InitHeader();
    void InitCenterMessage();
    void InitBottomEnterMessage();

    void SetLayout();
    void SetConnect();

    // 更新中间聊天消息
    void AddOneMsgFront(const nim::IMMessage &msg, int extIndex=-1); // 在消息列表头部插入一条消息
    void AddOneMsgEnd(const nim::IMMessage &msg);    // 在消息列表尾部插入一条消息
    // 添加一条提示消息，比如时间、已显示全部消息等提示信息
    void AddPromptTimeInfo(int64_t msg_time_tag, bool end=true);

private:

    QList<nim::IMMessage> chattingMsg;              // 当前显示的所有消息。这里消息的顺序是按时间逆序排列的，也就是说最新的一条消息在数组的第一条，最久远的消息在数组的最后一条
    bool hasMoreMessage = true;                     // 是否还有更多消息
    bool isQuerying = false;                        // 当前是否正在请求历史消息
    int currentTopIndex = 0;                        // 当前聊天消息的ListWidget滑动的位置，主要用来判断是否滑动到顶部
    int LIMIT_COUNT_PER_REQ = 20;                   // 每次请求消息时的最大请求数量

    // 获取聊天对象的消息记录
    void QueryMsg();
    void QueryMsgOnline(int64_t from_time=0, int64_t end_time=0, int64_t end_msg_id=0);
    void OnQueryMsgCallback(nim::NIMResCode res_code, const std::string& id,
                            nim::NIMSessionType to_type, const nim::QueryMsglogResult& result);


private:
    // 发送消息相关函数
    void sendTextMsgToReceiver(const std::string &msg, nim::IMMessage &message);

private:
    // 头部控件
    QLabel *headerPhotoLabel;           // 头像
    QLabel *accountLabel;               // 用户名
    QLabel *stateLabel;                 // 用户在线状态

private:
    // 中间控件
    QListWidget *chattingListWidget;    // 中间聊天消息列表
    QScrollBar *verticalScrollBar;      // 垂直的滚动条

private:
    // 底部输入消息、发送消息控件
    QTextEdit *messageTextEdit;         // 输入文本消息编辑框
    QPushButton *sendButton;            // 发送消息按钮

private:
    QWidget *headerWidget;              // 聊天界面标题头总控件
    QVBoxLayout *messageLayout;         // 聊天界面中间消息列表布局
    QWidget *enterMessageWidget;        // 聊天界面输入消息总控件
    QVBoxLayout *mainLayout;            // 界面主布局

private:
    nim::SessionData sessionData;

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

    signals:
    void updateMsgListWidgetSignal(int);
    void noMoreMessageSignal();         // 发送没有更多的聊天消息信息

public slots:
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
