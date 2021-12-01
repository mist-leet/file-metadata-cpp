#pragma once
#include "pch.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);

    virtual void dragEnterEvent(QDragEnterEvent *) override;

    virtual ~Widget() override;

private:
    Ui::Widget *ui;
};

