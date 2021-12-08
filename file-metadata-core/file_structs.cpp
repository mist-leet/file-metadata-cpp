#include "file_structs.h"
#include <QLabel>

GeneralInfo::GeneralInfo()
{}

bool GeneralInfo::isEmpty() const {
    return title.isEmpty() && titleSorting.isEmpty() && performer.isEmpty() &&
            performerSorting.isEmpty() && album.isEmpty() && albumSorting.isEmpty();
}

bool GeneralInfo::hasAllDisplayableData() const {
    return !title.isEmpty() && !performer.isEmpty() && !album.isEmpty();
}

bool FileMetadata::hasInfo() const {//нужно поддерживать в актуальном состоянии!
    return albumPosition.first || setPosition.first || !textFields.isEmpty() ||
            !commercial.isEmpty() || !ufids.isEmpty() || isrc[12] || !languages.isEmpty() || !generalInfo.isEmpty();
}

void FileMetadata::showOnEdit(QVBoxLayout *layout) const {
    for (auto i = textFields.constBegin();i != textFields.constEnd();++i) {
        QString text = i.key() + ": " + i.value();
        QLabel *label = new QLabel(text);
        layout->addWidget(label);
    }

    QString text = "Title: " + generalInfo.title;
    QLabel *label = new QLabel(text);
    layout->addWidget(label);

    QString text1 = "Performer: " + generalInfo.performer;
    QLabel *label1 = new QLabel(text1);
    layout->addWidget(label1);

    QString text2 = "Album: " + generalInfo.album;
    QLabel *label2 = new QLabel(text2);
    layout->addWidget(label2);
}

FileMetadata::FileMetadata() {
    isrc[12] = 0;
}

bool FileMetadata::needsV1() const {
    return !generalInfo.hasAllDisplayableData() || !textFields.contains("Comment") || !textFields.contains("Release time") ||
            !textFields.contains("Genre") || !albumPosition.first;
}
