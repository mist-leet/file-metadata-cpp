#include "widget_info.h"
#include "ui_widget_info.h"
#include <QtDebug>
#include <QLabel>

widget_info::widget_info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::widget_info)
{
    qDebug() << "Second window started";
    ui->setupUi(this);
    label_generator(ui->main_layout, 5);

}

widget_info::~widget_info()
{
    delete ui;
}

// Добавляет на layout n lable'ов
void widget_info::label_generator(QLayout *lay, int n)
{
    for(int i = 0; i < n; i++)
    {
        QLabel *label = new QLabel();
        QString s = "Tag " + QString::number(i + 1) + ": ~~~~~~~";
        label->setText(s);
        label->setAlignment(Qt::AlignCenter);

        lay->addWidget(label);
    }
}
