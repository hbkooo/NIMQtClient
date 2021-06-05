//
// Created by 19216 on 2021/6/4.
//

#include <util/util.h>
#include "userinfowidget.h"


UserInfoWidget::UserInfoWidget(const nim::UserNameCard &nameCard, QWidget *parent) :
        userNameCard(nameCard), QWidget(parent) {
    qDebug() << "[info]: create widget, " << __FUNCTION__;

    this->setFixedSize(520, 680);
    this->setStyleSheet("background:#ffffff;");

    InitControl();
    SetLayout();
    SetConnect();
    updateEditEnable(false);

    // 更新界面数据
    updateWindow();

}

UserInfoWidget::~UserInfoWidget() {
    qDebug() << "[info]: In " << __FUNCTION__;
    if(birthCalendarWidget != nullptr) {
        delete birthCalendarWidget;
        birthCalendarWidget = nullptr;
    }
}

void UserInfoWidget::InitControl() {
    headerPhotoLabel = new ClickableLabel("头像");
    headerPhotoLabel->setFixedSize(100, 100);
    headerPhotoLabel->setStyleSheet("background:#F0F2F5;");
    // 鼠标移上去变手型
    headerPhotoLabel->setCursor(QCursor(Qt::PointingHandCursor));

    nameLabel = new QLabel("昵称");
    nameLabel->setStyleSheet("font-size: 24px;"
                             "font-weight: bold;"
                             "background:#F0F2F5;");
    nameLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    nameLabel->setCursor(QCursor(Qt::IBeamCursor));

    genderLabel = new QLabel("性别");
    genderLabel->setFixedSize(18, 18);
    genderLabel->setStyleSheet("background:#F0F2F5;");

    accountLabel = new QLabel("账号");
    accountLabel->setStyleSheet("font-size:20px;"
                                "background:#F0F2F5;");
    accountLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    accountLabel->setCursor(QCursor(Qt::IBeamCursor));

    auto hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->addWidget(nameLabel, 0, Qt::AlignVCenter);
    hLayout->addSpacing(8);
    hLayout->addWidget(genderLabel, 0, Qt::AlignVCenter);
    hLayout->addStretch();

    auto vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);
    vLayout->addStretch();
    vLayout->addLayout(hLayout);
    vLayout->addSpacing(20);
    vLayout->addWidget(accountLabel);
    vLayout->addStretch();

    auto *headerLayout = new QHBoxLayout();
    headerLayout->setContentsMargins(0, 10, 0, 0);
    headerLayout->setSpacing(0);
    headerLayout->addSpacing(40);
    headerLayout->addWidget(headerPhotoLabel, 0, Qt::AlignVCenter);
    headerLayout->addSpacing(28);
    headerLayout->addLayout(vLayout);
    headerLayout->addSpacing(40);

    headerWidget = new QWidget();
    headerWidget->setStyleSheet(".QWidget { background:#F0F2F5;"
                                "border: 1px solid #e5e5e5;"
                                "border-radius: 6px;}");
    headerWidget->setFixedHeight(180);
    headerWidget->setLayout(headerLayout);

    int EditHeight = 40;
    QMargins EditMargins(12, 6, 12, 6);

    // 手机号信息
    mobileLabel = new QLabel("手机");
    mobileLabel->setCursor(QCursor(Qt::IBeamCursor));
    mobileLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    mobileEdit = new QLineEdit();
    mobileEdit->setFixedHeight(EditHeight);
    mobileEdit->setTextMargins(EditMargins);
    mobileEdit->setStyleSheet("QLineEdit { border: 1px solid #e5e5e5;"
                              "border-radius: 6px;"
                              "font-size:18px;"
                              "color:#2c2c2c; }"
                              "QLineEdit:focus {"
                              "border-color:#238efa;}");

    // 生日信息
    birthLabel = new QLabel("生日");
    birthLabel->setCursor(QCursor(Qt::IBeamCursor));
    birthLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    birthDateEdit = new QDateEdit();
    birthDateEdit->setSizePolicy(mobileEdit->sizePolicy());
    birthDateEdit->setFixedHeight(EditHeight);
    birthDateEdit->setContentsMargins(EditMargins);
    birthDateEdit->setStyleSheet("QDateEdit { border: 1px solid #e5e5e5;"
                                 "border-radius: 6px;"
                                 "padding: 5px 10px;"
                                 "font-size:18px;"
                                 "color:#2c2c2c; }"
                                 "QDateEdit::down-arrow{image:url(:/res/down_normal);}"         // 下拉箭头
                                 "QDateEdit::up-arrow{image:url(:/res/up_normal);}"             // 下拉箭头
                                 "QDateEdit::drop-down{border:0px;}"                            // 去除下拉按钮边框
                                 "QDateEdit:focus { border-color:#238efa; }"
                                 "QDateEdit::down-arrow:focus {image:url(:/res/down_focus);}"
                                 "QDateEdit::up-arrow:focus {image:url(:/res/up_focus);}"
                                 );
    birthDateEdit->installEventFilter(this);

    birthCalendarWidget = new QCalendarWidget();
    birthCalendarWidget->setFixedSize(250, 200);
    birthCalendarWidget->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    birthCalendarWidget->setStyleSheet("border: 3px solid #e5e5e5;"
                                       "border-radius: 6px;"
                                       "color:black;"
                                       "font-size:14px;");
    birthCalendarWidget->hide();

    // 邮箱信息
    emailLabel = new QLabel("邮箱");
    emailLabel->setCursor(QCursor(Qt::IBeamCursor));
    emailLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    emailEdit = new QLineEdit();
    emailEdit->setFixedHeight(EditHeight);
    emailEdit->setTextMargins(EditMargins);
    emailEdit->setStyleSheet("QLineEdit { border: 1px solid #e5e5e5;"
                             "border-radius: 6px;"
                             "font-size:18px;"
                             "color:#2c2c2c; }"
                             "QLineEdit:focus {"
                             "border-color:#238efa;}");

    // 个性签名信息
    signatureLabel = new QLabel("签名");
    signatureLabel->setCursor(QCursor(Qt::IBeamCursor));
    signatureLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    signatureEdit = new QTextEdit();
    signatureEdit->setContentsMargins(EditMargins);
    signatureEdit->setFixedHeight(88);
    QString padding = QString("%1px %2px %3px %4px;").arg(EditMargins.left())
            .arg(EditMargins.top())
            .arg(EditMargins.right())
            .arg(EditMargins.bottom());
    signatureEdit->setStyleSheet("QTextEdit { border: 1px solid #e5e5e5;"
                                 "border-radius: 6px;"
                                 "padding:" + padding +
                                 "font-size:18px;"
                                 "background:#ffffff;"
                                 "color:#2c2c2c; }"
                                 "QTextEdit:focus {"
                                 "border-color:#238efa;}");

    if (userNameCard.GetAccId() == SELF_USER_NAME_CARD.GetAccId()) {
        // 是自己的用户信息，则可以修改

        // 修改昵称信息
        changeNameLabel = new QLabel("昵称");
        changeNameLabel->setCursor(QCursor(Qt::IBeamCursor));
        changeNameLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
        changeNameEdit = new QLineEdit();
        changeNameEdit->setFixedHeight(EditHeight);
        changeNameEdit->setTextMargins(EditMargins);
        changeNameEdit->setStyleSheet("QLineEdit { border: 1px solid #e5e5e5;"
                                      "border-radius: 6px;"
                                      "font-size:18px;"
                                      "color:#2c2c2c; }"
                                      "QLineEdit:focus {"
                                      "border-color:#238efa;}");

        // 修改性别信息
        changeGenderLabel = new QLabel("性别");
        changeGenderLabel->setCursor(QCursor(Qt::IBeamCursor));
        changeGenderLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);

        changeGenderBox = new QComboBox();
        changeGenderBox->setView(new QListView());
        changeGenderBox->setFixedHeight(EditHeight);
        changeGenderBox->setSizePolicy(changeNameEdit->sizePolicy());
        changeGenderBox->addItem("男");
        changeGenderBox->addItem("女");
        changeGenderBox->setStyleSheet("QComboBox{border:1px solid #e5e5e5;"
                                       "border-radius: 6px;"
                                       "padding: 5px 10px;"
                                       "font-size:18px;"
                                       "}"
                                       "QComboBox QAbstractItemView::item{min-height: 30px;}"       // 下拉选项高度
                                       "QComboBox::down-arrow{image:url(:/res/drop_down);}"         // 下拉箭头
                                       "QComboBox::drop-down{border:0px;}"                          // 去除下拉按钮边框
                                       "QComboBox:focus {"
                                       "border-color:#238efa;}");

        // 修改按钮
        cancelButton = new QPushButton("取消");
        connect(cancelButton, &QPushButton::clicked, this, [this](){
            changeSaveButton->setText("修改");
            updateEditEnable(false);
        });
        cancelButton->setFixedSize(120, 40);
        cancelButton->setStyleSheet("QPushButton { font-size:20px;"
                                        "color:white;"
                                        "border: none;"
                                        "border-radius: 6px;"
                                        "background-color:#6C757D;}"
                                        "QPushButton:hover {"
                                        "background-color:#5A6268;}"
                                        "QPushButton:pressed {"
                                        "background-color:#545B62;"
                                        "border: 2px solid #B6BABE;}"
                                        "QPushButton:focus{outline: none;}"); // 获取焦点时不显示虚线框

        // 修改按钮
        changeSaveButton = new QPushButton("修改");
        connect(changeSaveButton, &QPushButton::clicked, this, &UserInfoWidget::ChangeSaveUserCardSlot);
        changeSaveButton->setFixedSize(120, 40);
        changeSaveButton->setStyleSheet("QPushButton { font-size:20px;"
                                        "color:white;"
                                        "border: none;"
                                        "border-radius: 6px;"
                                        "background-color:#4ca6ff;}"
                                        "QPushButton:hover {"
                                        "background-color:#238efa;}"
                                        "QPushButton:pressed {"
                                        "background-color:#1f7ddb;"
                                        "border: 2px solid #80BDFF;}"
                                        "QPushButton:focus{outline: none;}"); // 获取焦点时不显示虚线框

    }

}

void UserInfoWidget::SetLayout() {

    auto *birthLayout = new QHBoxLayout();
    birthLayout->addWidget(birthLabel);
    birthLayout->addSpacing(30);
    birthLayout->addWidget(birthDateEdit);

    auto *mobileLayout = new QHBoxLayout();
    mobileLayout->addWidget(mobileLabel);
    mobileLayout->addSpacing(30);
    mobileLayout->addWidget(mobileEdit);

    auto *emailLayout = new QHBoxLayout();
    emailLayout->addWidget(emailLabel);
    emailLayout->addSpacing(30);
    emailLayout->addWidget(emailEdit);

    auto *signatureLayout = new QHBoxLayout();
    signatureLayout->addWidget(signatureLabel, 0, Qt::AlignTop);
    signatureLayout->addSpacing(30);
    signatureLayout->addWidget(signatureEdit);

    int SpaceBetweenWidget = 18;
    mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(26, 0, 26, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(headerWidget);
    if (userNameCard.GetAccId() == SELF_USER_NAME_CARD.GetAccId()) {
        // 修改用户昵称
        changeNameLayout = new QHBoxLayout();
        changeNameLayout->addWidget(changeNameLabel);
        changeNameLayout->addSpacing(30);
        changeNameLayout->addWidget(changeNameEdit);

        mainLayout->addSpacing(SpaceBetweenWidget);
        mainLayout->addLayout(changeNameLayout);
        changeNameLabel->hide();
        changeNameEdit->hide();

        // 修改用户性别
        changeGenderLayout = new QHBoxLayout();
        changeGenderLayout->addWidget(changeGenderLabel);
        changeGenderLayout->addSpacing(30);
        changeGenderLayout->addWidget(changeGenderBox);

        mainLayout->addSpacing(SpaceBetweenWidget);
        mainLayout->addLayout(changeGenderLayout);
        changeGenderLabel->hide();
        changeGenderBox->hide();
    }
    mainLayout->addSpacing(SpaceBetweenWidget);
    mainLayout->addLayout(birthLayout);
    mainLayout->addSpacing(SpaceBetweenWidget);
    mainLayout->addLayout(mobileLayout);
    mainLayout->addSpacing(SpaceBetweenWidget);
    mainLayout->addLayout(emailLayout);
    mainLayout->addSpacing(SpaceBetweenWidget);
    mainLayout->addLayout(signatureLayout);
    if (userNameCard.GetAccId() == SELF_USER_NAME_CARD.GetAccId()) {
        mainLayout->addSpacing(SpaceBetweenWidget);
        auto *btnLayout = new QHBoxLayout();
        btnLayout->addStretch();
        btnLayout->addWidget(cancelButton);
        btnLayout->addSpacing(SpaceBetweenWidget);
        btnLayout->addWidget(changeSaveButton);
        mainLayout->addLayout(btnLayout);
    }
    mainLayout->addStretch();
    setLayout(mainLayout);
}

void UserInfoWidget::SetConnect() {
    connect(this, &UserInfoWidget::ChangeUserCardSuccessSignal, this, &UserInfoWidget::updateWindow);
}

void UserInfoWidget::updateWindow() {
    updateMyHeader();
    updateCenter();
}

void UserInfoWidget::ShowNormal() {
    updateEditEnable(false);
    updateWindow();
    this->showNormal();
}

void UserInfoWidget::updateMyHeader() {
    // 更新头像
    updateHeaderPhotoIcon();

    // 更新账号
    accountLabel->setText(QString::fromStdString("账号:" + userNameCard.GetAccId()));

    QPixmap pixmap;
    if (userNameCard.GetGender() == 0) {
        // 男
        pixmap.load(":/res/boy");
    } else {
        // 女
        pixmap.load(":/res/girl");
    }
    genderLabel->setPixmap(pixmap.scaled(genderLabel->size()));

    // 更新用户昵称
    if (!userNameCard.GetName().empty()) {
        nameLabel->setText(QString::fromStdString(userNameCard.GetName()));
    } else {
        nameLabel->setText(QString::fromStdString(userNameCard.GetAccId()));
    }

}

void UserInfoWidget::updateCenter() {
    if (userNameCard.GetAccId() == SELF_USER_NAME_CARD.GetAccId()) {
        changeNameEdit->setText(QString::fromStdString(userNameCard.GetName()));
        changeGenderBox->setCurrentIndex(userNameCard.GetGender());
    }
    birthDateEdit->setDate(QDate::fromString(QString::fromStdString(userNameCard.GetBirth()),
                                             "yyyy-MM-dd"));
    mobileEdit->setText(QString::fromStdString(userNameCard.GetMobile()));
    emailEdit->setText(QString::fromStdString(userNameCard.GetEmail()));
    signatureEdit->setText(QString::fromStdString(userNameCard.GetSignature()));
}

// 设置用户头像
void UserInfoWidget::updateHeaderPhotoIcon() {
    if (userNameCard.GetIconUrl().empty()) {
        userNameCard.SetIconUrl(":/default_header/dh9");
    }
    QPixmap map(QString::fromStdString(SELF_USER_NAME_CARD.GetIconUrl()));
    if (map.isNull()) {
        // 头像加载失败
        map.load(":/default_header/dh9");
    }
    headerPhotoLabel->setPixmap(
            PixmapToRound(
                    map.scaled(headerPhotoLabel->size()),
                    headerPhotoLabel->height() / 2)
    );
}

// 修改边界框是否可修改
void UserInfoWidget::updateEditEnable(bool state) {
    changeNameLabel->setVisible(state);
    changeNameEdit->setVisible(state);
    changeGenderLabel->setVisible(state);
    changeGenderBox->setVisible(state);

    birthDateEdit->setEnabled(state);
    mobileEdit->setEnabled(state);
    emailEdit->setEnabled(state);
    signatureEdit->setEnabled(state);
//    signatureEdit->setReadOnly(!state);
//    signatureEdit->setFocusPolicy(Qt::ClickFocus);
    if(!state) {
        changeSaveButton->setText("修改");
    }
    cancelButton->setVisible(state);
}

void UserInfoWidget::ChangeSaveUserCardSlot() {

    if (changeSaveButton->text() == "修改") {
        // 点击了修改，可以修改所有信息
        changeSaveButton->setText("保存");
        updateEditEnable(true);
    } else if (changeSaveButton->text() == "保存") {
        // 点击了保存，则要执行保存操作。所有的信息不可再修改
        changeSaveButton->setText("修改");
        updateEditEnable(false);

        nim::UserNameCard nameCard(userNameCard.GetAccId());
        nameCard.SetName(changeNameEdit->text().toStdString());
        nameCard.SetGender(changeGenderBox->currentIndex());
        nameCard.SetBirth(birthDateEdit->date().toString("yyyy-MM-dd").toStdString());
        nameCard.SetEmail(emailEdit->text().toStdString());
        nameCard.SetMobile(mobileEdit->text().toStdString());
        nameCard.SetSignature(signatureEdit->toPlainText().toStdString());
        UpdateMyUserNameCard(nameCard);
    }

}

void UserInfoWidget::UpdateMyUserNameCard(const nim::UserNameCard &nameCard) {
//    qDebug() << "[info]: 修改用户信息：" << QString::fromStdString(info.ToJsonString());
    nim::User::UpdateMyUserNameCard(nameCard, [this, nameCard](auto &&PH1) {
        OnUpdateMyInfo(nameCard, std::forward<decltype(PH1)>(PH1));
    });
}

void UserInfoWidget::OnUpdateMyInfo(const nim::UserNameCard &nameCard, nim::NIMResCode res) {
    if (res == nim::kNIMResSuccess) {
        qDebug() << "资料修改成功！";
        userNameCard = nameCard;
        SELF_USER_NAME_CARD = userNameCard;
        qDebug() << "[info]: 修改用户信息为：" << QString::fromStdString(userNameCard.ToJsonString());

        // UserInfoWidget::updateWindow、MainWindow::updateMyHeader
        // 发送修改成功信号，更新本界面的名片信息和主界面的名片显示信息
        emit ChangeUserCardSuccessSignal();
    } else {
        qDebug() << "修改资料失败..., error code is: " << res;
    }
}

bool UserInfoWidget::eventFilter(QObject *obj, QEvent *ev) {
    if (obj == birthDateEdit) {
        if (ev->type() == QEvent::FocusIn) {
            //qDebug() << "mobile focus in ...";
            //qDebug() << "mobile location: " << birthDateEdit->geometry();
            //qDebug() << "this location: " << this->geometry();
            if (!birthCalendarWidget->isVisible()) {
                auto mobileLoc = birthDateEdit->geometry();
                auto thisLoc = this->geometry();
                birthCalendarWidget->setGeometry(mobileLoc.x()+thisLoc.x(),
                                                 mobileLoc.y()+thisLoc.y()-birthCalendarWidget->height(),
                                                 0, 0);
                // birthCalendarWidget->setVisible(true);
            }

        } else if (ev->type() == QEvent::FocusOut) {
            //qDebug() << "mobile focus out ...";
            if (!birthCalendarWidget->hasFocus()) {
                birthCalendarWidget->setVisible(false);
            }
        }
    }
    return QObject::eventFilter(obj, ev);
}



