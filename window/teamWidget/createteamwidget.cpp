//
// Created by 19216 on 2021/6/9.
//


#include "createteamwidget.h"


CreateTeamWidget::CreateTeamWidget(QWidget *parent) :
        QWidget(parent) {
    setWindowTitle("创建群聊");
    setMinimumSize(600, 500);
    InitControl();
}

CreateTeamWidget::~CreateTeamWidget() {

}

void CreateTeamWidget::InitControl() {

    QMargins EditMargins(12, 6, 12, 6);
    int EditHeight = 40;

    teamNameLineEdit = new QLineEdit();
    teamNameLineEdit->installEventFilter(this);
    teamNameLineEdit->setFixedHeight(EditHeight);
    teamNameLineEdit->setTextMargins(EditMargins);
    teamNameLineEdit->setPlaceholderText("请输入群名称");
    teamNameLineEdit->setStyleSheet("QLineEdit { border: 1px solid #e5e5e5;"
                                    "border-radius: 6px;"
                                    "font-size:18px;"
                                    "color:#2c2c2c; }"
                                    "QLineEdit:focus {"
                                    "border-color:#238efa;}");

    userInfoListWidget = new QListWidget();
    QFile css(":/css/listWidget");
    css.open(QFile::ReadOnly);
    userInfoListWidget->setStyleSheet(css.readAll());
    userInfoListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);//水平滚动条关闭
    userInfoListWidget->setFocusPolicy(Qt::NoFocus);      // 删除选中某一个item是产生的虚线框
    userInfoListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);   // 让内容连续地滚动，而不是整行整行的滚动

    teamDescriptionTextEdit = new QTextEdit();
    teamDescriptionTextEdit->installEventFilter(this);
    teamDescriptionTextEdit->setPlaceholderText("输入群描述");
    teamDescriptionTextEdit->setContentsMargins(EditMargins);
    teamDescriptionTextEdit->setFixedHeight(88);
    QString padding = QString("%1px %2px %3px %4px;").arg(EditMargins.left())
            .arg(EditMargins.top())
            .arg(EditMargins.right())
            .arg(EditMargins.bottom());
    teamDescriptionTextEdit->setStyleSheet("QTextEdit { border: 1px solid #e5e5e5;"
                                           "border-radius: 6px;"
                                           "padding:" + padding +
                                           "font-size:18px;"
                                           "background:#ffffff;"
                                           "color:#2c2c2c; }"
                                           "QTextEdit:focus {"
                                           "border-color:#238efa;}");

    infoLabel = new QLabel("提示消息");
    infoLabel->setContentsMargins(0, 8, 0, 0);
    infoLabel->setStyleSheet("color:red;"
                             "font-size: 20px;");
    infoLabel->setVisible(false);

    createButton = new QPushButton("创建");
    connect(createButton, &QPushButton::clicked, this, &CreateTeamWidget::ClickedCreateTeamButtonSlot);
    createButton->setFixedSize(120, 40);
    createButton->setStyleSheet("QPushButton { font-size:20px;"
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

    auto *hLayout = new QHBoxLayout();
    hLayout->addWidget(infoLabel);
    hLayout->addStretch();
    hLayout->addWidget(createButton);

    auto mainLayout = new QVBoxLayout();
    mainLayout->addWidget(teamNameLineEdit);
    mainLayout->addWidget(userInfoListWidget);
    mainLayout->addWidget(teamDescriptionTextEdit);
    // mainLayout->addWidget(createButton, 0, Qt::AlignRight);
    mainLayout->addLayout(hLayout);
    setLayout(mainLayout);

    // 显示创建群的提示信息结果
    connect(this, &CreateTeamWidget::ShowResultOfCreateTeamSignal, this, &CreateTeamWidget::ShowResultOfCreateTeamSlot);

}

// 更新显示的好友列表
void CreateTeamWidget::updateWindow() {
    userInfoListWidget->clear();
    for (const auto &friendProfile: friendProfileMap) {
        QString accID = QString::fromStdString(friendProfile.GetAccId());
        auto *userItem = new CreateTeamItem(userNameCardMap[accID], friendProfile);
        auto *listItem = new QListWidgetItem();
        // 必须设置，设置每一个条目显示的宽、高
        listItem->setSizeHint(QSize(0, userItem->size().height()));
        userInfoListWidget->addItem(listItem);
        userInfoListWidget->setItemWidget(listItem, userItem);
    }
}

void CreateTeamWidget::ClickedCreateTeamButtonSlot() {
    qDebug() << "[info]: create ...";

    if (teamNameLineEdit->text() == "") {
        ShowResultOfCreateTeamSlot("群名称不能为空！");
        return;
    }
    nim::TeamInfo teamInfo;
    teamInfo.SetName(teamNameLineEdit->text().toStdString());
    teamInfo.SetType(nim::kNIMTeamTypeNormal);

    QList<std::string> accIDs;

    for (int i = 0; i < userInfoListWidget->count(); ++i) {
        auto *listItem = userInfoListWidget->item(i);
        auto *userItem = dynamic_cast<CreateTeamItem *>(userInfoListWidget->itemWidget(listItem));
        if (userItem->getChecked()) {
            // 如果选中了
            accIDs.append(userItem->getUserNameCard().GetAccId());
            qDebug() << "[info]: 创建群聊包含用户：" << QString::fromStdString(userItem->getUserNameCard().GetAccId());
        }
    }
    CreateTeam(teamInfo, accIDs, teamDescriptionTextEdit->toPlainText());
}


// 创建群聊
void CreateTeamWidget::CreateTeam(const nim::TeamInfo &teamInfo,
                                  const QList<std::string> &ids,
                                  const QString &description) {

    std::list<std::string> id_list;

    for(const auto &id: ids) {
        id_list.push_back(id);
    }

    Team::CreateTeamAsync(teamInfo, id_list, description.toStdString(),
                          [this](const nim::TeamEvent &team_event) {
                              if (team_event.res_code_ == nim::kNIMResSuccess) {
                                  emit ShowResultOfCreateTeamSignal("创建群成功！");
                              } else {
                                  emit ShowResultOfCreateTeamSignal("创建群失败！" + QString::number(team_event.res_code_));
                              }
                          });

}

// 显示添加好友的提示信息结果
void CreateTeamWidget::ShowResultOfCreateTeamSlot(const QString &resultInfo) {
    infoLabel->setVisible(true);
    infoLabel->setText(resultInfo);
}

bool CreateTeamWidget::eventFilter(QObject *obj, QEvent *ev) {
    if(obj == teamNameLineEdit) {
        if(ev->type() == QEvent::FocusIn) {
            infoLabel->setVisible(false);
        }
    }
    if(obj == teamDescriptionTextEdit) {
        if(ev->type() == QEvent::FocusIn) {
            infoLabel->setVisible(false);
        }  else if(ev->type() == QEvent::KeyPress) {
            // 在验证消息框内回车按键则直接搜索添加好友
            auto *key = dynamic_cast<QKeyEvent *>(ev);
            if (key->key() == Qt::Key_Enter || key->key() == Qt::Key_Return) {
                ClickedCreateTeamButtonSlot();
            }
        }
    }
    return QWidget::eventFilter(obj,ev);
}


