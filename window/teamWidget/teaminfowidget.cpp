//
// Created by 19216 on 2021/6/10.
//


#include "teaminfowidget.h"


TeamInfoWidget::TeamInfoWidget(nim::TeamInfo info, QWidget *parent) :
        teamInfo(std::move(info)), QWidget(parent) {
    setWindowTitle("群信息");
    setFixedSize(630, 680);
    InitControl();
}

TeamInfoWidget::~TeamInfoWidget() {
    qDebug() << "[info]: delete team info widget, in " << __FUNCTION__;
}

void TeamInfoWidget::InitControl() {

    memberListWidget = new QListWidget();
    QFile css(":/css/listWidget");
    css.open(QFile::ReadOnly);
    memberListWidget->setStyleSheet(css.readAll());
    memberListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);//水平滚动条关闭
    memberListWidget->setFocusPolicy(Qt::NoFocus);      // 删除选中 某一个item是产生的虚线框
    memberListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);   // 让内容连续地滚动，而不是整行整行的滚动
    memberListWidget->setFixedHeight(300);

    InitBaseTeamInfoControl();

    auto *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(memberListWidget);
    mainLayout->addWidget(MakeSplitWidget("#d0c9cc", 1));
    mainLayout->addWidget(baseTeamInfoListWidget);
    mainLayout->addStretch();
    setLayout(mainLayout);

    // 更新界面显示的群成员信息
    connect(this, &TeamInfoWidget::updateWindowMembersSignal,
            this, &TeamInfoWidget::updateWindowMemberSlot);
    // 当获取一条用户的名片时，需要更新显示的成员列表中成员的信息
    connect(this, &TeamInfoWidget::updateOneMemberByUserNameCardSignal,
            this, &TeamInfoWidget::updateOneMemberByUserNameCardSlot);

}

// 初始化下方群信息控件
void TeamInfoWidget::InitBaseTeamInfoControl() {

    int height = 56;        // 每个条目的高度
    int spacing = 10;       // 每个条目中，两个控件之间的间隔
    QString font_size = "font-size:20px;";      // 字体大小

    baseTeamInfoListWidget = new QListWidget();
    QFile css(":/css/listWidget");
    css.open(QFile::ReadOnly);
    baseTeamInfoListWidget->setStyleSheet(css.readAll());
    baseTeamInfoListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);//水平滚动条关闭
    baseTeamInfoListWidget->setFocusPolicy(Qt::NoFocus);      // 删除选中 某一个item是产生的虚线框
    baseTeamInfoListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);   // 让内容连续地滚动，而不是整行整行的滚动
    baseTeamInfoListWidget->setFixedHeight(300);

    // 添加群头像信息
    auto *photoLabel = new QLabel("群头像");
    photoLabel->setStyleSheet(font_size);
    teamHeaderPhotoLabel = new QLabel("头像");
    teamHeaderPhotoLabel->setFixedSize(44, 44);
    QPixmap defaultMap(QString::fromStdString(teamInfo.GetIcon()));
    if (defaultMap.isNull()) {
        defaultMap.load(QString::fromStdString(":/default_header/default_team"));
    }
    teamHeaderPhotoLabel->setPixmap(
            PixmapToRound(
                    defaultMap.scaled(teamHeaderPhotoLabel->size()),
                    teamHeaderPhotoLabel->height() / 2)
    );
    auto *photoLayout = new QHBoxLayout();
    photoLayout->setContentsMargins(10, 0, 10, 0);
    photoLayout->addWidget(photoLabel, 0, Qt::AlignVCenter);
    photoLayout->addSpacing(spacing);
    photoLayout->addWidget(teamHeaderPhotoLabel, 0, Qt::AlignVCenter);
    photoLayout->addStretch();
    auto *photoWidget = new QWidget();
    photoWidget->setLayout(photoLayout);
    photoWidget->setFixedHeight(height);
    auto *photoItem = new QListWidgetItem();
    // 必须设置，设置每一个条目显示的宽、高
    photoItem->setSizeHint(QSize(0, photoWidget->size().height()));
    baseTeamInfoListWidget->addItem(photoItem);
    baseTeamInfoListWidget->setItemWidget(photoItem, photoWidget);

    // 添加群id
    auto *idLabel = new QLabel("群ID");
    idLabel->setStyleSheet(font_size);
    idLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    idLabel->setCursor(QCursor(Qt::IBeamCursor));
    teamIdLabel = new QLabel("群ID");
    teamIdLabel->setStyleSheet(font_size);
    teamIdLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    teamIdLabel->setCursor(QCursor(Qt::IBeamCursor));
    teamIdLabel->setText(QString::fromStdString(teamInfo.GetTeamID()));
    auto *idLayout = new QHBoxLayout();
    idLayout->setContentsMargins(10, 0, 10, 0);
    idLayout->addWidget(idLabel, 0, Qt::AlignVCenter);
    idLayout->addSpacing(spacing);
    idLayout->addWidget(teamIdLabel, 0, Qt::AlignVCenter);
    idLayout->addStretch();
    auto *idWidget = new QWidget();
    idWidget->setLayout(idLayout);
    idWidget->setFixedHeight(height);
    auto *idItem = new QListWidgetItem();
    // 必须设置，设置每一个条目显示的宽、高
    idItem->setSizeHint(QSize(0, idWidget->size().height()));
    baseTeamInfoListWidget->addItem(idItem);
    baseTeamInfoListWidget->setItemWidget(idItem, idWidget);

    // 添加群名称
    auto *nameLabel = new QLabel("群名称");
    nameLabel->setStyleSheet(font_size);
    nameLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    nameLabel->setCursor(QCursor(Qt::IBeamCursor));
    teamNameLabel = new QLabel("群名称");
    teamNameLabel->setStyleSheet(font_size);
    teamNameLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    teamNameLabel->setCursor(QCursor(Qt::IBeamCursor));
    teamNameLabel->setText(QString::fromStdString(teamInfo.GetName()));
    auto *nameLayout = new QHBoxLayout();
    nameLayout->setContentsMargins(10, 0, 10, 0);
    nameLayout->addWidget(nameLabel, 0, Qt::AlignVCenter);;
    nameLayout->addSpacing(spacing);
    nameLayout->addWidget(teamNameLabel, 0, Qt::AlignVCenter);
    nameLayout->addStretch();
    auto *nameWidget = new QWidget();
    nameWidget->setLayout(nameLayout);
    nameWidget->setFixedHeight(height);
    auto *nameItem = new QListWidgetItem();
    // 必须设置，设置每一个条目显示的宽、高
    nameItem->setSizeHint(QSize(0, nameWidget->size().height()));
    baseTeamInfoListWidget->addItem(nameItem);
    baseTeamInfoListWidget->setItemWidget(nameItem, nameWidget);

    // 添加群介绍
    auto *descLabel = new QLabel("群介绍");
    descLabel->setStyleSheet(font_size);
    descLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    descLabel->setCursor(QCursor(Qt::IBeamCursor));
    teamDescriptionLabel = new QLabel("请输入群介绍");
    teamDescriptionLabel->setStyleSheet(font_size);
    teamDescriptionLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    teamDescriptionLabel->setCursor(QCursor(Qt::IBeamCursor));
    teamDescriptionLabel->setText(QString::fromStdString(teamInfo.GetAnnouncement()));
    auto *descLayout = new QHBoxLayout();
    descLayout->setContentsMargins(10, 0, 10, 0);
    descLayout->addWidget(descLabel, 0, Qt::AlignVCenter);;
    descLayout->addSpacing(spacing);
    descLayout->addWidget(teamDescriptionLabel, 0, Qt::AlignVCenter);
    descLayout->addStretch();
    auto *descWidget = new QWidget();
    descWidget->setLayout(descLayout);
    descWidget->setFixedHeight(height);
    auto *descItem = new QListWidgetItem();
    // 必须设置，设置每一个条目显示的宽、高
    descItem->setSizeHint(QSize(0, descWidget->size().height()));
    baseTeamInfoListWidget->addItem(descItem);
    baseTeamInfoListWidget->setItemWidget(descItem, descWidget);

}


// 向成员列表中添加一行成员信息
void TeamInfoWidget::AddOneLineMemberInListWidget(QWidget *lineWidget) {
    qDebug() << "[info]: in " << __FUNCTION__ << ", add one line members ...";
    auto *listItem = new QListWidgetItem();
    // 必须设置，设置每一个条目显示的宽、高
    listItem->setSizeHint(QSize(0, lineWidget->size().height()));
    memberListWidget->addItem(listItem);
    memberListWidget->setItemWidget(listItem, lineWidget);

}

// 创建一个用户成员的显示控件
QWidget *TeamInfoWidget::createOneMemberWidget(const nim::TeamMemberProperty &memberProperty) {

    // std::cout << "createOneMemberWidget thread id : " << std::this_thread::get_id() << std::endl;
    auto *headerPhotoLabel = new QLabel("头像");
    headerPhotoLabel->setObjectName("member_header_photo");
    headerPhotoLabel->setFixedSize(44, 44);
    QPixmap defaultMap(QString::fromStdString(":/default_header/dh9"));
    headerPhotoLabel->setPixmap(
            PixmapToRound(
                    defaultMap.scaled(headerPhotoLabel->size()),
                    headerPhotoLabel->height() / 2)
    );

    auto *nameLabel = new QLabel("用户名");
    nameLabel->setObjectName("member_user_name");
    nameLabel->setStyleSheet("font-size:18px;");
    if (!memberProperty.GetNick().empty()) {
        nameLabel->setText(QString::fromStdString(memberProperty.GetNick()));
    } else {
        nameLabel->setText(QString::fromStdString(memberProperty.GetAccountID()));
    }

    if (userNameCardsMap.contains(memberProperty.GetAccountID())) {
        const auto &userNameCard = userNameCardsMap[memberProperty.GetAccountID()];
        QPixmap map(QString::fromStdString(userNameCard.GetIconUrl()));
        if (map.isNull()) {
            // 头像加载失败
            map.load(":/default_header/dh9");
        }
        headerPhotoLabel->setPixmap(
                PixmapToRound(
                        map.scaled(headerPhotoLabel->size()),
                        headerPhotoLabel->height() / 2)
        );
        if (nameLabel->text().toStdString() == userNameCard.GetAccId()) {
            // 如果显示的是用户的accID，即群里没有设置昵称
            if (!userNameCard.GetName().empty()) {
                // 用户名片中自己设置的名称不为空，则设置用户名片的名称
                nameLabel->setText(QString::fromStdString(userNameCard.GetName()));
            }
        }
    }

    auto *hLayout = new QHBoxLayout();
    hLayout->addWidget(headerPhotoLabel, 0, Qt::AlignVCenter);
    hLayout->addWidget(nameLabel, 0, Qt::AlignVCenter);

    auto *widget = new QWidget();
    widget->setFixedSize(200, 64);
    widget->setLayout(hLayout);
    memberWidget.insert(memberProperty.GetAccountID(), widget);
    return widget;
}

void TeamInfoWidget::ShowNormal() {
    // TODO
    GetTeamMembers(QString::fromStdString(teamInfo.GetTeamID()));
    // std::cout << "ShowNormal thread id : " << std::this_thread::get_id() << std::endl;

    this->showNormal();
    this->raise();
}

// 获取群组成员
void TeamInfoWidget::GetTeamMembers(const QString &teamID) {
    nim::Team::QueryTeamMembersAsync(teamID.toStdString(),
                                     [this](const std::string &tid, int member_count,
                                            const std::list<nim::TeamMemberProperty> &props) {
                                         teamMembers.clear();
                                         QList<QString> accounts;
                                         for (const auto &member: props) {
                                             teamMembers.append(member);
                                             accounts.append(QString::fromStdString(member.GetAccountID()));
                                         }
                                         GetUserNameCard(accounts);
                                         qDebug() << "[info]: get " << member_count << " members in "
                                                  << QString::fromStdString(tid);
                                         });
}

// 获取本地用户信息
void TeamInfoWidget::GetUserNameCard(const QList<QString> &accounts) {
    qDebug() << "[info]: 本地获取用户名片，" << accounts << __FUNCTION__ ;
    std::list<std::string> account_list;
    for (const auto &account: accounts) {
        account_list.push_back(account.toStdString());
    }
    nim::User::GetUserNameCard(account_list, [accounts, this](const std::list<nim::UserNameCard> &json_result) {
        qDebug() << "[info]: 获取本地用户名片数量为：" << json_result.size();
        if (json_result.empty()) {
            // 本地获取的用户信息为空，只能在线获取用户信息
            GetUserNameCardOnLine(accounts);
        } else {
            // 未获取到名片的用户列表。未获取到名片的用户列表则之后线上重新获取。
            QList<QString> notUserNames, foundUserNames;
            for (auto &info: json_result) {
                // TeamInfoWidget::updateOneMemberByUserNameCardSlot
                // 更新显示的成员列表中成员的信息
                emit updateOneMemberByUserNameCardSignal(info);
                foundUserNames.append(QString::fromStdString(info.GetAccId()));
            }
            for (const auto &name: accounts) {
                if (!foundUserNames.contains(name)) {
                    notUserNames.append(name);
                }
            }
            if (!notUserNames.empty()) {
                // 重新在线获取
                GetUserNameCardOnLine(notUserNames);
            }
            emit updateWindowMembersSignal();       // TeamInfoWidget::updateWindowMemberSlot
        }
    });
}

// 获取服务器用户信息。这里会触发用户信息发生变化
void TeamInfoWidget::GetUserNameCardOnLine(const QList<QString> &accounts) {
    qDebug() << "[info]: 在线获取用户名片，" << accounts << __FUNCTION__ ;
    std::list<std::string> account_list;
    for (const auto &account: accounts) {
        account_list.push_back(account.toStdString());
    }
    nim::User::GetUserNameCardOnline(account_list, [this](const std::list<nim::UserNameCard> &json_result) {
        // std::cout << "GetUserNameCardOnLine thread id : " << std::this_thread::get_id() << std::endl;

        qDebug() << "[info]: get " << json_result.size() << " user name cards in "
                                                            "TeamInfoWidget::GetUserNameCardOnLine";
        // 如果查找的用户 accID 不存在，则还会有回调在这里，只不过不存在查询的这条用户 accID 的数据。
        for (auto &info: json_result) {
            // TeamInfoWidget::updateOneMemberByUserNameCardSlot
            // 更新显示的成员列表中成员的信息
            emit updateOneMemberByUserNameCardSignal(info);
        }

        emit updateWindowMembersSignal();       // TeamInfoWidget::updateWindowMemberSlot
    });
}


void TeamInfoWidget::updateWindowMemberSlot() {
    // qDebug() << "[info]: update member list ... " << __FUNCTION__ ;
    memberListWidget->clear();

    int count = teamMembers.size();
    for (int i = 0; i < count;) {
        auto *lineLayout = new QHBoxLayout();
        lineLayout->setContentsMargins(0, 0, 0, 0);
        auto *lineWidget = new QWidget();

        if (i >= count) break;

        const auto memberWidget1 = createOneMemberWidget(teamMembers[i++]);
        lineWidget->setFixedHeight(memberWidget1->height());
        lineLayout->addWidget(memberWidget1, 0, Qt::AlignVCenter);
        if (i >= count) {
            lineLayout->addStretch();
            lineWidget->setLayout(lineLayout);
            AddOneLineMemberInListWidget(lineWidget);
            break;
        }

        const auto memberWidget2 = createOneMemberWidget(teamMembers[i++]);
        lineLayout->addWidget(memberWidget2, 0, Qt::AlignVCenter);
        if (i >= count) {
            lineLayout->addStretch();
            lineWidget->setLayout(lineLayout);
            AddOneLineMemberInListWidget(lineWidget);
            break;
        }

        const auto memberWidget3 = createOneMemberWidget(teamMembers[i++]);
        lineLayout->addWidget(memberWidget3, 0, Qt::AlignVCenter);
        lineWidget->setLayout(lineLayout);
        AddOneLineMemberInListWidget(lineWidget);

    }
}

// 当获取一条用户的名片时，需要更新显示的成员列表中成员的信息
void TeamInfoWidget::updateOneMemberByUserNameCardSlot(const nim::UserNameCard &userNameCard) {

    // std::cout << "updateOneMemberByUserNameCardSlot thread id : " << std::this_thread::get_id() << std::endl;
    userNameCardsMap.insert(userNameCard.GetAccId(), userNameCard);      // 插入一条用户信息数据
    if (memberWidget.contains(userNameCard.GetAccId())) {
        qDebug() << "[info]: update one showed member by find the member's userNameCard of "
                 << QString::fromStdString(userNameCard.GetAccId()) << ", " << __FUNCTION__;
        // 说明成员列表里已经包含了该成员信息，所以需要更新该成员显示的信息
        auto *widget = memberWidget[userNameCard.GetAccId()];
        // 获取该成员的头像控件和用户名控件
        auto *headerPhotoLabel = widget->findChild<QLabel *>("member_header_photo");
        auto *nameLabel = widget->findChild<QLabel *>("member_user_name");
        // 更新头像控件
        QPixmap map(QString::fromStdString(userNameCard.GetIconUrl()));
        if (map.isNull()) {
            // 头像加载失败
            map.load(":/default_header/dh9");
        }
        headerPhotoLabel->setPixmap(
                PixmapToRound(
                        map.scaled(headerPhotoLabel->size()),
                        headerPhotoLabel->height() / 2)
        );
        // 更新用户名控件
        if (nameLabel->text().toStdString() == userNameCard.GetAccId()) {
            // 如果显示的是用户的accID，即群里没有设置昵称
            if (!userNameCard.GetName().empty()) {
                // 用户名片中自己设置的名称不为空，则设置用户名片的名称
                nameLabel->setText(QString::fromStdString(userNameCard.GetName()));
            }
        }
    }

}
