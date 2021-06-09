//
// Created by 19216 on 2021/6/8.
//

#ifndef NIMQTCLIENT_TEAMITEM_H
#define NIMQTCLIENT_TEAMITEM_H

#include <QWidget>
#include <QObject>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QDateTime>
#include <QDebug>

#include "client.h"
#include "util/util.h"

using namespace nim;

class TeamItem : public QWidget {
Q_OBJECT

public:
    explicit TeamItem(const TeamInfo &info, QWidget *parent = nullptr);

    ~TeamItem() override;

    // 重新设置新的item数据
    void setTeamInfo(const TeamInfo &info);
    // 更新这一个item信息
    void updateItem();

private:
    void InitControl();

private:
    // 控件信息
    QLabel *teamPhotoLabel = nullptr;     // 用户头像
    QLabel *nameLabel = nullptr;            // 用户姓名标签

private:
    TeamInfo teamInfo;

};


#endif //NIMQTCLIENT_TEAMITEM_H
