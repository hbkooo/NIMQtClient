//
// Created by 19216 on 2021/6/4.
//

#ifndef NIMQTCLIENT_USERINFOWIDGET_H
#define NIMQTCLIENT_USERINFOWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMap>
#include <QTime>
#include <QDate>
#include <QCalendarWidget>
#include <QDateEdit>
#include <QComboBox>
#include <QListView>
#include <QDebug>

#include "util/clickablelabel.h"
#include "client.h"

class UserInfoWidget : public QWidget {
Q_OBJECT

public:
    explicit UserInfoWidget(nim::UserNameCard nameCard, QWidget *parent = nullptr);

    ~UserInfoWidget() override;

    void setUserNameCard(const nim::UserNameCard &nameCard) { userNameCard = nameCard; }

    void ShowNormal();      // 显示界面信息

private:

    void InitControl();

    void SetLayout();

    void SetConnect();

    // 更新界面数据
    void updateWindow();

    // 更新头部信息
    void updateMyHeader();

    // 更新中间信息
    void updateCenter();

    // 更新用户的头像
    void updateHeaderPhotoIcon();

    void updateEditEnable(bool state);

private:
    // 修改用户信息资料
    void UpdateMyUserNameCard(const nim::UserNameCard &info);

    // 修改用户信息资料回调
    void OnUpdateMyInfo(const nim::UserNameCard &nameCard, nim::NIMResCode res);

private:
    ClickableLabel *headerPhotoLabel;           // 用户头像
    QLabel *accountLabel;                       // 用 accID
    QLabel *genderLabel;                        // 性别图片
    QLabel *nameLabel;                          // 用户昵称
    QWidget *headerWidget;                      // 用户头信息的综合控件

    QLabel *changeNameLabel;                    // 当可修改时，修改昵称标签
    QLineEdit *changeNameEdit;                  // 当可修改时，修改昵称编辑框
    QHBoxLayout *changeNameLayout;              // 当可修改是，修改昵称的布局

    QLabel *changeGenderLabel;                  // 当可修改时，修改性别标签
    QComboBox *changeGenderBox;                 // 当可修改时，修改性别编辑框
    QHBoxLayout *changeGenderLayout;            // 当可修改是，修改性别的布局

    QLabel *birthLabel;                         // 生日
    QDateEdit *birthDateEdit;                   // 选择生日时间
    QCalendarWidget *birthCalendarWidget;       // 选择生日时间

    QLabel *mobileLabel;                        // 手机号
    QLineEdit *mobileEdit;                      // 修改手机号编辑框

    QLabel *emailLabel;                         // 邮箱
    QLineEdit *emailEdit;                       // 修改邮箱编辑框

    QLabel *signatureLabel;                     // 签名
    QTextEdit *signatureEdit;                   // 修改签名编辑框

    QPushButton *cancelButton;                  // 取消按钮
    QPushButton *changeSaveButton;              // 修改保存按钮

    QVBoxLayout *mainLayout;                    // 界面主布局

private:
    nim::UserNameCard userNameCard;             // 当前显示的用户信息


protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;

signals:

    void ChangeUserCardSuccessSignal();                // 修改用户名片成功信号

public slots:

    void ChangeSaveUserCardSlot();              // 修改按钮槽函数

};


#endif //NIMQTCLIENT_USERINFOWIDGET_H
