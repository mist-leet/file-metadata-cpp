#pragma once
#include "pch.h"
using namespace std;

extern constexpr size_t npos_ = string::npos;
extern constexpr int len_of_id3_identifier(3);
extern constexpr int min_id3_tag_len(21);
extern constexpr int min_id3_frame_len(11);
extern constexpr int id3_tag_header_len(10);
extern constexpr int id3_frame_header_len(10);
extern constexpr int id3_frame_ID_len(4);
extern constexpr char big_endian('B');
extern constexpr char little_endian('L');
typedef unordered_map<string, string> Text_frames;
typedef bitset<8> Byte;
typedef bitset<16> char_16;
typedef unordered_map<string, Byte *> UFID;
typedef long long li;

//международный стандартный номер аудиозаписи
struct ISRC
{
    bool present;//присутствует ли ISRC в теге
    char country_code[2];//ISO 3166-1 Alpha-2
    char issuer_code[3];//код организации, выдавшей данный ISRC
    char registration_year[2];
    char code[5];
};

struct File_metadata
{
    UFID ufid;//unique file identifier
    Text_frames common_info;
    ISRC isrc;

};

//ограничения для тега v2.4
struct Restrictions
{
    //при отсутствии ограничений: 268 435 455
    unsigned long max_size;//в байтах
    //при отсутствии ограничений: 24 403 223
    unsigned long max_frames;//в байтах
    bool encoding_rest;//при отсутствии ограничений: false
    unsigned long max_char_per_frame;//при отсутствии ограничений: 268 435 445 = max_len - frame_header_len
    bool pic_type_rest;//при отсутствии ограничений: false
    bool pic_size_rest;//при отсутствии ограничений: false
    int max_pic_size;
    int min_pic_size;
};

//информация из расширенного хедера
struct Extd_data
{
    pair<bitset<32>,bool> CRC32;
    bool update;
    pair<Restrictions,bool> restrictions;
    pair<unsigned long,bool> padding_size;
};

//свойства и корректность тега
struct Tag
{
    bool correct;
    bool unsynch;
    bool experimental;
    bool footer;
    unsigned long len;
    pair<Extd_data,bool> extd_data;
    long t_count;
    li start_pos;
    //устанавливает correct, сбрасывает все остальные флаги, ставит t_count = 0; вызывается при парсинге нового тега
    void set_to_initial_state();
};

class binaryfile : public fstream
{
    File_metadata file_metadata;//метаданные
    Tag tag;//свойства текущего тега
    const li size = get_size();//размер всего файла
public:
    explicit binaryfile(const char * fileway) : fstream(fileway, ios::binary | ios::in | ios::out) {}

    //вставляет строку str с позиции bias
    void insert(const string & str, const long long int & bias);

    //устанавливает длину файла в байтах
    li get_size();

    //обрабатывает тег ID3v2
    void handle_id3v2_tag();

    //обрабатывает тег ID3v2.2
    void handle_v22();

    //обрабатывает тег ID3v2.3
    void handle_v23();

    //обрабатывает тег ID3v2.4
    void handle_v24();

    //обрабатывает хедер
    bool parse_header(int);

    //обрабатывает расширенный хедер для v2.4
    void parse_extd_h_4();

    //обрабатывает расширенный хедер для v2.3
    void parse_extd_h_3();

    //устанавливает значение CRC32 для v2.4
    void get_CRC32_v24();

    //определяет ограничения для тега v2.4
    void get_restrictions_v24();

    //парсит файл
    void parse();

    //парсит фрейм
    bool parse_frame(const char * const);

    //возвращает байт из тега, флаг десинхронизации берётся из свойств тега
    int getb();

    //возвращает байт из фрейма с учётом десинхронизации (только для v2.4)
    int getb(bool);

    //возвращает числовое значение двух байтов из тега с учётом порядка бит, флаг десинхронизации берётся из свойств тега
    unsigned get2b(char byteorder);

    //возвращает числовое значение двух байтов из фрейма с учётом порядка бит и десинхронизации (только для v2.4)
    unsigned get2b(bool unsynch, char byteorder);

    //возвращает метку порядка байтов, флаг десинхронизации берётся из свойств тега
    char getBOM();

    //возвращает метку порядка байтов
    char getBOM(bool);

    //возвращает десятеричный код символа из UTF-8, флаг десинхронизации берётся из свойств тега
    long utf8();

    //возвращает десятеричный код символа из UTF-8
    long utf8(bool);
};

//переводит 4-байтный synchsafe int в двоичную запись обычного int
pair<bitset<28>,bool> synchsafe_handler(const bitset<32> &);

//принимает массив символов и переводит первые четыре в bitset<32>
pair<bitset<28>,bool> synchsafe_handler(const char * const);
