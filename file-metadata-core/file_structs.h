#pragma once
using namespace std;

//все метаданные файла
struct File_metadata
{
    QHash<QString, QString> fields;
    pair<uint, uint> position_in_album{make_pair(0,0)};
    //дописать

    File_metadata();

    bool has_info() const;

    void display_on_console() const;//написать

    void display_on_ui() const;//написать

    bool needs_v1() const;
};

bool File_metadata::has_info() const//нужно поддерживать в актуальном состоянии!
{
    return position_in_album.first && !fields.isEmpty();
}

File_metadata::File_metadata()
{}

bool File_metadata::needs_v1() const//неизвестно хотя бы что то из нижеперечисленного
{
    return !fields.contains("Title") || !fields.contains("Performer") || !fields.contains("Album") ||
            !fields.contains("Comment") || !fields.contains("Release time") || !fields.contains("Genre") || !position_in_album.first;
}
