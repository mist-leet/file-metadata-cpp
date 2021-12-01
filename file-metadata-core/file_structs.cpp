#include "file_structs.h"

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

void FileMetadata::showOnEdit(QTextEdit *te) const {
    for (auto i = textFields.constBegin();i != textFields.constEnd();++i) {
        te->append(i.key());
        te->insertPlainText(": ");
        te->insertPlainText(i.value());
    }

    te->append("Title: ");
    te->insertPlainText(generalInfo.title);

    te->append("Performer: ");
    te->insertPlainText(generalInfo.performer);

    te->append("Album: ");
    te->insertPlainText(generalInfo.album);

    te->append("");
}

FileMetadata::FileMetadata() {
    isrc[12] = 0;
}

bool FileMetadata::needsV1() const {
    return !generalInfo.hasAllDisplayableData() || !textFields.contains("Comment") || !textFields.contains("Release time") ||
            !textFields.contains("Genre") || !albumPosition.first;
}
