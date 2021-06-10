//
// Created by 19216 on 2021/6/10.
//


#include "teaminfowidget.h"


TeamInfoWidget::TeamInfoWidget(nim::TeamInfo info, QWidget *parent) :
        teamInfo(std::move(info)), QWidget(parent) {

}

TeamInfoWidget::~TeamInfoWidget() {

}

void TeamInfoWidget::ShowNormal() {
    // TODO
    this->showNormal();
    this->raise();
}

