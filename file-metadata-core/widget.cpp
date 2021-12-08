#include "widget.h"
#include "ui_widget.h"

namespace {
void clearLayout(QLayout* layout, bool deleteWidgets = true)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                widget->deleteLater();
        }
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}
} // namespace anonymous

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget1)
    , m_pLayout{new QVBoxLayout{this}}
{
//    ui->setupUi(this);
    setAcceptDrops(true);
    m_pLayout->setAlignment(Qt::AlignmentFlag::AlignTop);
    resize(300, 400);
//    ui->textEdit->setPlainText("Перетащите иконку аудиофайла в это поле\n\
//Для успешной работы окно должно быть активным в момент перетаскивания");

}

Widget::~Widget() {
    delete ui;
    m_pLayout->deleteLater();
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
        clearLayout(m_pLayout);
        qDebug() << "Widget: going to show\n";
        b.getData().showOnEdit(m_pLayout);
        qDebug() << "Widget: ended showing, num" << _count++;
    }
    else {
        qDebug() << "Widget: can't open file\n";
    }
}
