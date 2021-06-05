//
// Created by 19216 on 2021/6/4.
//

#include "clickablelabel.h"

ClickableLabel::ClickableLabel(const QString& text, QWidget *parent):
    QLabel(text, parent) {

}

void ClickableLabel::mousePressEvent(QMouseEvent *event) {
    emit clicked();
}
