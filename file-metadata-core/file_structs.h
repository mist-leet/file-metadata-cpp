#pragma once
#include "global_constants.h"

struct GeneralInfo
{
    QString title{};
    QString performer{};
    QString album{};
    QString titleSorting{};
    QString performerSorting{};
    QString albumSorting{};

    GeneralInfo();

    bool isEmpty() const;

    bool hasAllDisplayableData() const;
};

//все метаданные файла
struct FileMetadata
{
    QHash<QString, QString> textFields{};//text info
    QHash<QString, QString> commercial{};//commercial info
    QHash<QString, std::vector<uchar>> ufids{};//unique file id
    GeneralInfo generalInfo{};//исполнитель, альбом, название трека
    std::pair<uint, uint> albumPosition{std::make_pair(0,0)};
    std::pair<uint, uint> setPosition{std::make_pair(0,0)};
    char isrc[13];//последний байт - индикатор наличия isrc; он равен 0, если isrc отсутствует, в противном случае не равен 0
    QList<QString> languages{};
    //дописать

    FileMetadata();

    bool hasInfo() const;

    void showOnEdit(QTextEdit *) const;

    bool needsV1() const;
};
