#include "v1.h"

Binary::V1::V1(Binary &f)
    : FileHolder(f)
{}

Binary::V1::~V1() = default;

bool Binary::V1::parseHeader() {
    return true;
}

bool Binary::V1::parse() {
    qDebug() << "V1: starting to parse\n";
    return parseData();
}

QString Binary::V1::getField(int n) const {
    if (n <= 30) {
        char c[30];
        char curr;
        int i = 0;
        while (i < n) {
            curr = ch();
            if (curr) {
                c[i] = curr;
                ++i;
            }
            else {
                break;
            }
        }
        return QString::fromLatin1(c,i);
    }
    else
        return QString();
}

bool Binary::V1::parseData() {
    if (file.getData().generalInfo.title.isEmpty()) {
        qDebug() << "V1: getting title\n";
        QString field = getField(30);
        file.getData().generalInfo.title = field;
        if (file.getData().generalInfo.titleSorting.isEmpty())
            file.getData().generalInfo.titleSorting = field;
    }
    else
        shift(30);

    if (file.getData().generalInfo.performer.isEmpty()) {
        qDebug() << "V1: getting performer\n";
        QString field = getField(30);
        file.getData().generalInfo.performer = field;
        if (file.getData().generalInfo.performerSorting.isEmpty())
            file.getData().generalInfo.performerSorting = field;
    }
    else
        shift(30);

    if (file.getData().generalInfo.album.isEmpty()) {
        qDebug() << "V1: getting album\n";
        QString field = getField(30);
        file.getData().generalInfo.album = field;
        if (file.getData().generalInfo.albumSorting.isEmpty())
            file.getData().generalInfo.albumSorting = field;
    }
    else
        shift(30);

    if (!file.getData().textFields.contains("Release time")) {
        qDebug() << "V1: getting release time\n";
        file.getData().textFields["Release time"] = getField(4);
    }
    else
        shift(4);

    bool no_comm = !file.getData().textFields.contains("Comment");
    if (no_comm) {
        qDebug() << "V1: getting comment\n";
        file.getData().textFields["Comment"] = getField(28);
    }
    else
        shift(28);

    char mark = ch();

    if (mark) {
        char smth = ch();
        if (no_comm)
            file.getData().textFields["Comment"] += mark += smth;
    }
    else {
        uchar num = get();
        if (!file.getData().albumPosition.first)
            file.getData().albumPosition.first = num;
    }

    uchar genre_id = get();
    if (genre_id != 255)
        if (!file.getData().textFields.contains("Genre")) {
            qDebug() << "V1: getting genre\n";
            file.getData().textFields["Genre"] = Gl::getGenre(genre_id);
        }

    return true;
}
