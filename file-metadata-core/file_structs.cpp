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

QMap<QString, QString> FileMetadata::showOnEdit() const {
    QMap<QString, QString> data = {};

    for (auto i = textFields.constBegin();i != textFields.constEnd();++i) {
        QString text = i.key() + ": " + i.value();
        data.insert(i.key(), i.value());
    }

    data.insert("Title", generalInfo.title);
    data.insert("Performer", generalInfo.performer);
    data.insert("Album", generalInfo.album);

    return data;
}

FileMetadata::FileMetadata() {
    isrc[12] = 0;
}

bool FileMetadata::needsV1() const {
    return !generalInfo.hasAllDisplayableData() || !textFields.contains("Comment") || !textFields.contains("Release time") ||
            !textFields.contains("Genre") || !albumPosition.first;
}
