#pragma once
#include "binary.h"

namespace Ui {
class Widget1;
}

class Widget1 : public QWidget
{
    Q_OBJECT

public:
    explicit Widget1(QWidget *parent = nullptr);

    virtual void dragEnterEvent(QDragEnterEvent *) override;
    virtual void dropEvent(QDropEvent *) override;

    void parseFile(const QString &);

    virtual ~Widget1() override;

private:
    Ui::Widget1 *ui;
};
