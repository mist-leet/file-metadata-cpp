#ifndef WIDGET_INFO_H
#define WIDGET_INFO_H

#include <QDialog>
namespace Ui {
class widget_info;
}

class widget_info : public QDialog
{
    Q_OBJECT

public:
    explicit widget_info(QWidget *parent = nullptr);
    ~widget_info();

private:
    Ui::widget_info *ui;
    void label_generator(QLayout *lay, int n);
};

#endif // WIDGET_INFO_H
