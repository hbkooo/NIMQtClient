//
// Created by 19216 on 2021/6/5.
//

#ifndef NIMQTCLIENT_ADDFRIENDWIDGET_H
#define NIMQTCLIENT_ADDFRIENDWIDGET_H

#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>

#include "client.h"

class AddFriendWidget : public QWidget {
Q_OBJECT

public:
    explicit AddFriendWidget(QWidget *parent = nullptr);

    ~AddFriendWidget() override;

private:
    void InitControl();
    void SetLayout();
    void SetConnect();

private:

    QLabel *accIDLabel;             // 账户提示
    QLineEdit *accIDLineEdit;       // 搜索账户输入框

    QLabel *requestMsgLabel;        // 请求验证的消息
    QLineEdit *requestMsgLineEdit;  // 消息输入框

    QLabel *infoLabel;              // 操作提示信息

    QPushButton *cancelButton;      // 取消按钮
    QPushButton *searchButton;      // 搜索按钮

    QVBoxLayout *mainLayout;        // 主界面布局

private:
    // 添加好友
    void AddFriendRequest(const QString &accID, const QString& msg="");
    // 添加好友回调
    void OnFriendRequest(nim::NIMResCode res_code);

protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;

signals:
    // 显示添加好友的提示信息结果
    void ShowResultOfAddFriendSignal(const QString &resultInfo);

public slots:
    // 搜索好友按钮槽函数
    void ClickedSearchButtonSlot();
    // 显示添加好友的提示信息结果
    void ShowResultOfAddFriendSlot(const QString &resultInfo);

};


#endif //NIMQTCLIENT_ADDFRIENDWIDGET_H
