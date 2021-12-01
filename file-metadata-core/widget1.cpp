#include "widget1.h"
#include "ui_widget1.h"

Widget1::Widget1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget1)
{
    qDebug() << "Constructing Widget1\n";
    ui->setupUi(this);
    setAcceptDrops(true);
}

Widget1::~Widget1() {
    qDebug() << "Widget1 is dying\n";
    delete ui;
}

void Widget1::dragEnterEvent(QDragEnterEvent *e) {
    qDebug() << "dragEnterEvent\n";
    if (e->mimeData()->hasText()) {
        qDebug() << "Widget1: got path\n";
        parseFile(e->mimeData()->text().remove(0,8));
    }
    else {
        qDebug() << "no text\n";
    }
}

void Widget1::dropEvent(QDropEvent *e) {
    qDebug() << "dropEvent\n";
    if (e->mimeData()->hasText()) {
        qDebug() << "Widget1: got path\n";
        parseFile(e->mimeData()->text().remove(0,8));
    }
    else {
        qDebug() << "no text\n";
    }
}

void Widget1::parseFile(const QString &path) {
    static uint _count = 0;
    Binary b(path);
    qDebug() << "Widget1: going to parse\n";
    if (b.parse()) {
        qDebug() << "Widget1: parsed successfully\n";
        ui->textEdit->clear();
        qDebug() << "Widget1: going to show\n";
        b.getData().showOnEdit(ui->textEdit);
        qDebug() << "Widget1: ended showing, num" << _count++ << ::end;
    }
    else {
        qDebug() << "Widget1: can't open file\n";
    }
}
