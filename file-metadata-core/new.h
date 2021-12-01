#pragma once
#include "pch.h"
using namespace std;

/*
extern constexpr size_t npos_ = string::npos;
extern constexpr int id3_frame_header_len(10);
*/
typedef bitset<8> Byte;

long long power(int, int);

ostream & operator << (ostream &, const QBitArray &);

unsigned char to_u_char(QBitArray);

unsigned char to_u_char(char);

//все метаданные файла
struct File_metadata//UNDONE
{
    //дописать
};

//ограничения для тега v2.4
struct Restrictions
{
    bool precense;
    //при отсутствии ограничений: 268 435 455
    unsigned long max_size;//в байтах
    //при отсутствии ограничений: 24 403 223
    unsigned long max_frames;
    //false - нет ограничений, true - только ISO-8859-1 или UTF-8
    bool encoding_rest;
    //при отсутствии ограничений: 268 435 445 = max_len - frame_header_len
    unsigned long max_char_per_frame;
    //false - нет ограничений, true - только PNG или JPEG[JFIF]
    bool image_encoding_rest;
    /* 00 - нет ограничений
     * 01 - 256х256 пкс или менее
     * 10 - 64х64 пкс или менее
     * 11 - строго 64х64 пкс
    */
    pair<bool,bool> image_size_rest;

    Restrictions() :
        precense(false),
        max_size(0),
        max_frames(0),
        max_char_per_frame(static_cast<unsigned long>(268435445))
    {}

    operator bool();
};

//размер несжатой информация для сжатого фрейма
struct Raw_data
{
    bool compression;
    bool raw_data_presence;
    unsigned long size;
    //дописать
    //подготовить zlib.h для работы
    Raw_data() :
        compression(false),
        raw_data_presence(false),
        size(0)
    {}

    operator bool ();
};

//v3-4
struct Frame_status
{
    bool tag_alter_preservation;
    bool file_alter_preservation;
    bool read_only;
};

//v3-4
struct Frame_format
{
    bool group_id_presence;
    unsigned char group_id;
    Raw_data raw_data;
    bool encryption;
    unsigned char encryption_method_marker;

    Frame_format() :
        group_id_presence(false),
        raw_data(Raw_data()),
        encryption(false)
    {}
};

//v3
struct Group_markers_3
{
    unordered_map<unsigned char, string> url;
    unordered_map<unsigned char, QByteArray> info;
};

//v4
struct Group_markers_4
{
    unordered_map<unsigned char, string> url;
    unordered_map<unsigned char, QByteArray> info;
    unordered_map<unsigned char, QByteArray> sign;
};

//v3-4
struct Encryption_method_markers
{
    unordered_map<unsigned char, string> url;
    unordered_map<unsigned char, QByteArray> info;
};
