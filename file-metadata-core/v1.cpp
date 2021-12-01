#include "v1.h"
using namespace std;

Binary::V1::V1(Binary &f)
    : File_holder(f)
{}

Binary::V1::~V1() = default;

bool Binary::V1::parse_header()
{
    return true;
}

bool Binary::V1::parse()
{
    return parse_data();
}

QString Binary::V1::get_field(int n) const
{
    if (n <= 30)
    {
        char c[30];
        for (int i = 0; i < n;++i)
            c[i] = ch();
        return QString::fromLatin1(c,n);
    }
    else
        return QString();
}

bool Binary::V1::parse_data()
{
    if (!file.get_data().fields.contains("Title"))
    {
        file.get_data().fields["Title"] = get_field(30);
    }
    else
        shift(30);

    if (!file.get_data().fields.contains("Performer"))
    {
        file.get_data().fields["Performer"] = get_field(30);
    }
    else
        shift(30);

    if (!file.get_data().fields.contains("Album"))
    {
        file.get_data().fields["Album"] = get_field(30);
    }
    else
        shift(30);

    if (!file.get_data().fields.contains("Release time"))
    {
        file.get_data().fields["Release time"] = get_field(4);
    }
    else
        shift(4);

    bool no_comm = !file.get_data().fields.contains("Comment");
    if (no_comm)
    {
        file.get_data().fields["Comment"] = get_field(28);
    }
    else
        shift(28);

    char mark = ch();

    if (mark)
    {
        char smth = ch();
        if (no_comm)
            file.get_data().fields["Comment"] += mark += smth;
    }
    else
    {
        uchar num = get();
        if (!file.get_data().position_in_album.first)
            file.get_data().position_in_album.first = num;
    }

    uchar genre_id = get();
    if (genre_id != 255)
        if (!file.get_data().fields.contains("Genre"))
            file.get_data().fields["Genre"] = get_genre(genre_id);

    return true;
}
