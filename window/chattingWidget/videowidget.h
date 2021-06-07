//
// Created by 19216 on 2021/6/7.
//

#ifndef NIMQTCLIENT_VIDEOWIDGET_H
#define NIMQTCLIENT_VIDEOWIDGET_H

#include <QWidget>


class VideoWidget : public QWidget {
Q_OBJECT

public:
    explicit VideoWidget(QWidget *parent = nullptr);

    ~VideoWidget() override;

    //获取窗口句柄
    void* getVideoHwnd();

private:
    void InitControl();

private:
    QWidget *videoContentView;

private:

    QWidget *videoRender;


};


#endif //NIMQTCLIENT_VIDEOWIDGET_H
