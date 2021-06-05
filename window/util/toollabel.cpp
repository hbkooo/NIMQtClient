//
// Created by 19216 on 2021/5/31.
//

#include "toollabel.h"


ToolLabel::ToolLabel(QString text, QWidget *parent) :
        QLabel(parent) {
    setText(text);
    setAlignment(Qt::AlignCenter);
    setContentsMargins(20, 16, 20, 16);
    setStyleSheet("QLabel {"
                  "font-size:18px;}"
                  // 自定义checked属性，根据设置的不同属性值显示不同的css样式
                  "QLabel[checked=true] {"
                  "color:#238efa;"
                  "border: 2px none #238efa;"
                  "border-bottom-style:solid;}"
                  "QLabel[checked=false] {"
                  "border: 2px none #238efa;"
                  "color:#726d6f;}"

                  "QLabel:hover{"
                  "color:black;}");
    // 设置初始化的是否选中属性为false
    setProperty("checked", false);
}

ToolLabel::~ToolLabel() {

}

void ToolLabel::mousePressEvent(QMouseEvent *event) {
    emit clicked();
}

void ToolLabel::setChecked() {
    setProperty("checked", true);
}

void ToolLabel::setUnChecked() {
    setProperty("checked", false);
}

