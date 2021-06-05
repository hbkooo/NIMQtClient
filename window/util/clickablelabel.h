//
// Created by 19216 on 2021/6/4.
//

#ifndef NIMQTCLIENT_CLICKABLELABEL_H
#define NIMQTCLIENT_CLICKABLELABEL_H

#include <QLabel>
#include <QObject>
#include <QWidget>
#include <QMouseEvent>

class ClickableLabel: public QLabel {
Q_OBJECT

public:
    explicit ClickableLabel(const QString& text = "", QWidget *parent = nullptr);
    ~ClickableLabel() override = default;

protected:
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void clicked();
};


#endif //NIMQTCLIENT_CLICKABLELABEL_H
