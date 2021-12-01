#pragma once
#include "widget.h"
#include "ui_widget.h"
#include <QMimeData>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    qDebug() << "constructing widget\n";
    ui->setupUi(this);
    ui->textEdit->setAcceptDrops(true);
}

Widget::~Widget() {
    qDebug() << "widget is dying\n";
    delete ui;
}

void Widget::dragEnterEvent(QDragEnterEvent *e) {
    qDebug() << "dragEnterEvent\n";
    if (e->mimeData()->hasText()) {
        QString s = e->mimeData()->text();
        s.remove(0,8);
        qDebug() << s;
    }
    else {
        qDebug() << "no text\n";
    }
}
