//
// Created by 19216 on 2021/5/31.
//

#ifndef NIMQTCLIENT_TOOLLABEL_H
#define NIMQTCLIENT_TOOLLABEL_H

#include <QLabel>
#include <QMouseEvent>


class ToolLabel : public QLabel {
Q_OBJECT

public:
    explicit ToolLabel(QString text="", QWidget *parent = nullptr);

    ~ToolLabel() override;

    void setChecked();
    void setUnChecked();

private:

protected:
    void mousePressEvent(QMouseEvent *event) override;

    signals:
    void clicked();



};


#endif //NIMQTCLIENT_TOOLLABEL_H
