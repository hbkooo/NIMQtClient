//
// Created by 19216 on 2021/6/10.
//

#ifndef NIMQTCLIENT_TEAMINFOWIDGET_H
#define NIMQTCLIENT_TEAMINFOWIDGET_H

#include <QWidget>

#include "client.h"

class TeamInfoWidget : public QWidget {
Q_OBJECT

public:
    explicit TeamInfoWidget(nim::TeamInfo info, QWidget *parent = nullptr);

    ~TeamInfoWidget() override;
    // 设置界面显示的群数据
    void setTeamInfo(const nim::TeamInfo &info) { teamInfo = info; }
    // 显示界面
    void ShowNormal();

private:
    nim::TeamInfo teamInfo;

};


#endif //NIMQTCLIENT_TEAMINFOWIDGET_H
