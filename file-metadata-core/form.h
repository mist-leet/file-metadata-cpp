#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QQmlEngine>
#include <QQmlComponent>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    void dragEnterEvent(QDragEnterEvent *e);
    void parseFile(const QString &path);
    void setTitleAndPerformer(QString title, QString Performer);
    void genrateTagPair(QString tagName, QString tagValue);
    void clearLayout(QLayout* layout, bool deleteWidgets = true);

    QFont defaultFont = QFont("Roboto", 14);
    QPalette defaultPallete = QPalette();
    ~Form();

private:
    Ui::Form *ui;

};

#endif // FORM_H
