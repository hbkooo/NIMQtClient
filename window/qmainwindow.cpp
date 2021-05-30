#include "qmainwindow.h"

#include <qlistwidget.h>
//#include <QGLWidget>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    this->resize(360, 700);
    this->setMinimumSize(360, 700);
    this->setMaximumWidth(800);
    this->setStyleSheet("background:#ded5da;");

    InitRecentSessionWidget();
    InitFriendsWidget();

    SetLayout();

}

MainWindow::~MainWindow()
{
    qDebug() << "[info]: in ~MainWindow ...";
}

// 初始化消息列表控件
void MainWindow::InitRecentSessionWidget()
{
    recentSessionWidget = new RecentSessionWidget();
}

void MainWindow::InitFriendsWidget() {
    friendListWidget = new FriendListWidget();
    friendListWidget->setVisible(false);
}

void MainWindow::SetLayout() {
    layout = new QVBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setMargin(0);
    layout->addWidget(recentSessionWidget);
    layout->addWidget(friendListWidget);
    setLayout(layout);
}

void MainWindow::SetConnect() {

}

// 关闭窗口事件处理，这里处理为退出登录，到登录界面
void MainWindow::closeEvent(QCloseEvent *event) {
    qDebug() << "[info]: in MainWindow closeEvent ...";
    nim::Client::Logout(nim::kNIMLogoutChangeAccout, [this](nim::NIMResCode res_code) {
        qDebug() << "[info]: 退出登录 ...";
        emit LogoutSignal();                // 退出登录信号，发送到LoginWindow::OnLogoutSlot槽函数
    });
    event->ignore();
}





