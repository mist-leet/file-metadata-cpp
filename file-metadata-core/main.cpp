#include "form.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Form widget;
    widget.show();
    return app.exec();
}
