#pragma once
#include "binary.h"
#include <QVBoxLayout>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);

    virtual void dragEnterEvent(QDragEnterEvent *) override;

    void parseFile(const QString &);

    virtual ~Widget() override;

private:
    Ui::Widget *ui;
    QVBoxLayout *m_pLayout{nullptr};
};
