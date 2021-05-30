#include "recentsessionwidget.h"

RecentSessionWidget::RecentSessionWidget(QListWidget *parent) : QListWidget(parent)
{

    InitControl();

    qRegisterMetaType<Message>("Message");      // 注册消息传递的数据类型
    connect(this, &RecentSessionWidget::AddOneMsg, this, &RecentSessionWidget::add_item);

    // 获取当前所有的最近会话列表
    QueryAllRecentSession();

}

void RecentSessionWidget::InitControl() {
    QFile css(":/css/recentSessionWidget");
    css.open(QFile::ReadOnly);
//    qDebug() << css.readAll();
    this->setStyleSheet(css.readAll());
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);//水平滚动条关闭
    this->setFocusPolicy(Qt::NoFocus);      // 删除选中 某一个item是产生的虚线框
//    this->setMouseTracking(true);
}

// 向列表中新增一个item消息
void RecentSessionWidget::add_item(const Message &msg)
{
    auto *msgItem = new MessageItem(msg);
    messageItems.append(msgItem);
    auto *listItem = new QListWidgetItem();
    // 必须设置，设置每一个条目显示的宽、高
    listItem->setSizeHint(QSize(350, msgItem->size().height()));
    this->addItem(listItem);
    this->setItemWidget(listItem, msgItem);
//    auto *w = new QWidget(nullptr);
//    w->setAttribute(Qt::WA_DeleteOnClose);
}

// 删除列表中第row行的item消息
void RecentSessionWidget::remove_item(int row)
{
    if(row >= count()) {
        qDebug() << "删除的行数:" << row << "大于已有的数目：" << count();
        return;
    }
    QListWidgetItem *item = takeItem(row);      // 删除某一行，即删除某一个item
    if(item != nullptr) {
        auto *msgItem = static_cast<MessageItem*>(itemWidget(item));
        if(msgItem != nullptr)
            delete msgItem;
    }
    delete item;
}

//鼠标双击事件
void RecentSessionWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug () << "double clicked ..." << event->pos();
    QListWidgetItem *item = itemAt(event->pos());       // 获取点击的item
    if(item == nullptr) return;
    // 从item获取对应的自定义的widget
    auto *messageItem = static_cast<MessageItem*>(this->itemWidget(item));
    qDebug() << messageItem->getMessage().name;

    auto index = currentIndex();    // 获取当前点击的item对应的index

//    qDebug() << index << ", " << index.row();
//    this->takeItem(index.row());

}

void RecentSessionWidget::QueryAllRecentSession() {;
//    nim::Session::QueryAllRecentSessionAsync(std::bind(&RecentSessionWidget::OnQuerySessionListCallback,
//                                                       this, std::placeholders::_1, std::placeholders::_2));
    nim::Session::QueryAllRecentSessionAsync([this](auto &&PH1, auto &&PH2) {
        OnQuerySessionListCallback(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
    });
}

void RecentSessionWidget::OnQuerySessionListCallback(int unread_count, const nim::SessionDataList& session_list) {
    qDebug() << "[info]: 最近会话一共有 " << unread_count << " 条";
    for(auto &session_data: session_list.sessions_) {
        qDebug() << QString::fromStdString(nim::SessionData::ToJsonString(session_data));
        Message msg;
        msg.name = QString::fromStdString(session_data.msg_sender_accid_);
        msg.msgs = {QString::fromStdString(session_data.msg_content_)};
//        msg.date_time = session_data.msg_timetag_;
        msg.header_pixmap = QPixmap(":/default_header/dh" + QString::number(rand() % 10 + 1));
//        add_item(msg);
        emit AddOneMsg(msg);
    }
}

