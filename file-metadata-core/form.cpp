#include "form.h"
#include "ui_form.h"
#include "binary.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QSizePolicy>
#include <Qt>


Form::Form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
{
    ui->setupUi(this);
    this->defaultPallete.setColor(QPalette::WindowText, QColor(Qt::white));
    this->defaultPallete.setColor(QPalette::Text, QColor(Qt::white));

    setAcceptDrops(true);

    this->setWindowTitle("Song tag parser");
}

void Form::dragEnterEvent(QDragEnterEvent *e) {
    qDebug() << "dragEnterEvent\n";
    if (e->mimeData()->hasText()) {
        qDebug() << "Widget: got path\n";
        parseFile(e->mimeData()->text().remove(0,8));
    }
    else {
        qDebug() << "no text\n";
    }
}

void Form::setTitleAndPerformer(QString title, QString performer) {

    ui->tagSigner->setText(performer + " —");
    ui->tagTitle->setText(title);
}

void Form::genrateTagPair(QString tagName, QString tagValue) {

    QLabel *tagNameLabel = new QLabel(this);
    tagNameLabel->setText(tagName);
    tagNameLabel->setFont(this->defaultFont);
    tagNameLabel->setAutoFillBackground(true);
    tagNameLabel->setPalette(this->defaultPallete);


    QTextEdit *tagValueEdit = new QTextEdit(this);
    tagValueEdit->setText(tagValue);
    tagValueEdit->setEnabled(false);
    tagValueEdit->setSizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);
    tagValueEdit->setFont(this->defaultFont);
    tagValueEdit->setAutoFillBackground(true);
    tagValueEdit->setPalette(this->defaultPallete);


    tagValueEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tagValueEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QHBoxLayout *pairLayout = new QHBoxLayout();

    pairLayout->addWidget(tagNameLabel);
    pairLayout->addWidget(tagValueEdit);

    this->ui->tagLayout->insertLayout(-1, pairLayout);
}


void Form::parseFile(const QString &path) {
    static uint _count = 0;
    Binary b(path);
    qDebug() << "Widget: going to parse\n";
    if (b.parse()) {
        qDebug() << "Widget: parsed successfully\n";

        qDebug() << "Widget: going to show\n";
        QMap<QString, QString> parsedData = b.getData().showOnEdit();
        std::map map = parsedData.toStdMap();
        this->clearLayout(this->ui->tagLayout);
        for (auto &pair: map) {
            this->genrateTagPair(pair.first, pair.second);
        }
        qDebug() << "result \n" << parsedData;

        this->setTitleAndPerformer(parsedData.find("Title").value(), parsedData.find("Performer").value());

        qDebug() << "Widget: ended showing, num" << _count++;
    }
    else {
        qDebug() << "Widget: can't open file\n";
    }
}

void Form::clearLayout(QLayout* layout, bool deleteWidgets)
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

Form::~Form()
{
    delete ui;
}
