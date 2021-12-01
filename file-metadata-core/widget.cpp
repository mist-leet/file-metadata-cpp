#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget1)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    ui->textEdit->setPlainText("Перетащите иконку аудиофайла в это поле\n\
Для успешной работы окно должно быть активным в момент перетаскивания");
}

Widget::~Widget() {
    delete ui;
}

void Widget::dragEnterEvent(QDragEnterEvent *e) {
    qDebug() << "dragEnterEvent\n";
    if (e->mimeData()->hasText()) {
        qDebug() << "Widget: got path\n";
        parseFile(e->mimeData()->text().remove(0,8));
    }
    else {
        qDebug() << "no text\n";
    }
}

void Widget::parseFile(const QString &path) {
    static uint _count = 0;
    Binary b(path);
    qDebug() << "Widget: going to parse\n";
    if (b.parse()) {
        qDebug() << "Widget: parsed successfully\n";
        ui->textEdit->clear();
        qDebug() << "Widget: going to show\n";
        b.getData().showOnEdit(ui->textEdit);
        qDebug() << "Widget: ended showing, num" << _count++ << endl;
    }
    else {
        qDebug() << "Widget: can't open file\n";
    }
}
