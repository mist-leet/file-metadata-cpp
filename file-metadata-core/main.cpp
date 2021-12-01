#include "widget1.h"

int main(int argc, char *argv[]) {
#ifndef EXTRANEOUS_CODE
    Q_UNUSED(argc);
    Q_UNUSED(argv);
    {
        QString s{"D:/mus.mp3"};
#ifndef PRESET_PATH
        //set s from console/widget
#endif
        qDebug() << "Main: creating Binary\n";
        Binary b(s);

        qDebug() << "Main: starting to parse Binary\n";
        if (b.parse()) {
            qDebug() << "Main: parsed successfully\n";
            qDebug() << "Title: " << b.getData().generalInfo.title << ::end;
            qDebug() << "Performer: " << b.getData().generalInfo.performer << ::end;
            qDebug() << "Album: " << b.getData().generalInfo.album << ::end;
            //qDebug() << "Minor performer: " << b.getData().textFields["Minor performer"] << ::end;
            //qDebug() << "Conductor: " << b.getData().textFields["Conductor"] << ::end;
            //qDebug() << "Modified by: " << b.getData().textFields["Modified by"] << ::end;
            qDebug() << "Content type: " << b.getData().textFields["Content type"] << ::end;
            qDebug() << "Recording time: " << b.getData().textFields["Recording time"] << ::end;
        }
        else {
            qDebug() << "Main: can't open file\n";
        }
    }

#endif
    QApplication a(argc, argv);
    Widget1 w;
    w.show();
    return a.exec();
}
