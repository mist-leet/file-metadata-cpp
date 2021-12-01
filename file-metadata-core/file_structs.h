#pragma once
using namespace std;

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
    QHash<QString, QByteArray> ufids{};//unique file id
    GeneralInfo generalInfo{};//исполнитель, альбом, название трека
    pair<uint, uint> albumPosition{make_pair(0,0)};
    pair<uint, uint> setPosition{make_pair(0,0)};
    char isrc[13];//последний байт - индикатор наличия isrc; он равен 0, если isrc отсутствует, в противном случае не равен 0
    QList<QString> languages{};
    //дописать

    FileMetadata();

    bool hasInfo() const;

    void displayOnConsole() const;//написать

    void displayOnUi() const;//написать

    bool needsV1() const;
};
