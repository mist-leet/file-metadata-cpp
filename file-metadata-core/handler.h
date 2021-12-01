#pragma once
#include "pch.h"
using namespace std;
/*
class binaryfile : public fstream
{
    File_metadata file_metadata;//метаданные
    Tag tag;//свойства текущего тега
    const li size = get_size();//размер всего файла
public:
    binaryfile(const char * fileway) : fstream(fileway, ios::binary | ios::in | ios::out) {}

    //вставляет строку str с позиции bias
    void insert(const string & str, const long long int & bias);

    //парсит текстовый фрейм, возвращает true, если парсинг прошёл успешно (фрейм не поломан)
    bool parse_text_frame(const char * const);

    //парсит URL-фрейм, возвращает true, если парсинг прошёл успешно (фрейм не поломан)
    bool parse_url_frame(const char * const);

    //
    bool parse_MCDI();

    //
    bool parse_MLLT();

    //
    bool parse_ETCO();

    //
    bool parse_EQU2();

    //
    bool parse_ENCR();

    //
    bool parse_SYTC();

    //
    bool parse_SYLT();

    //
    bool parse_SIGN();

    //
    bool parse_SEEK();

    //
    bool parse_USLT();

    //
    bool parse_USER();

    //
    bool parse_COMM();

    //
    bool parse_COMR();

    //
    bool parse_RVA2();

    //
    bool parse_RVRB();

    //
    bool parse_RBUF();

    //
    bool parse_APIC();

    //
    bool parse_AENC();

    //
    bool parse_ASPI();

    //
    bool parse_PCNT();

    //
    bool parse_POPM();

    //
    bool parse_POSS();

    //
    bool parse_GRID();

    //
    bool parse_GEOB();

    //
    bool parse_LINK();

    //
    bool parse_OWNE();

    //
    bool parse_unknown_frame();
};

//проверяет, может ли символ входить в заголовок фрейма
bool check_char(char);

//проверяет, может ли строка являться заголовком или частью заголовка фрейма
bool check_str(const char * const);
*/
