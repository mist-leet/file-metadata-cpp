#pragma once
#include "widget.h"
#include "ui_widget.h"
#include "widget_info.h"

#include <QDropEvent>
#include <QMimeData>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->textEdit->setAcceptDrops(true);
}

Widget::~Widget()
{
    delete ui;
}

void QTextEdit::dropEvent(QDropEvent *e)
{
    qDebug("droped");
    widget_info *q = new widget_info(this);
    q->exec();
}
