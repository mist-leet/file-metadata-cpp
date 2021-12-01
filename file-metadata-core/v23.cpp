#include "v23.h"
#include "frames3.h"
using namespace std;

Binary::V23::V23(Binary &file) :
    Tag34(file)
{}

Binary::V23::~V23() = default;

bool Binary::V23::parse_header()
{
    mByte flags = get();
    for (unsigned i = 0;i < 5;++i)
        if (flags.test(i))//если установлены неопределённые флаги
            return false;

    unsynch = flags.test(7);
    bool extdh = flags.test(6);
    experimental_tag = flags.test(5);

    bool correctness = set_length([this](int &count)
                                    {
                                        return this->File_holder::get(count);
                                    }).second;
    end_position = start_position + 10 + length;
    if (correctness && extdh)
        correctness = parse_extended_header();
    extreme_position_of_frame = end_position - 11 - size_of_padding;
    return correctness;
}

bool Binary::V23::parse_extended_header()
{
    for (int i = 0;i < 4;++i)
        getb(size_of_extended_header);

    expected_crc.second = (getb(size_of_extended_header) > 127);//установлен первый бит первого флага
    getb(size_of_extended_header);//второй байт не имеет значимого контента

    for (int i = 3;i >= 0;--i)
        size_of_padding += getb(size_of_extended_header)*power(256,i);

    if (expected_crc.second)
        for (int i = 3;i >= 0;--i)
            expected_crc.first += getb(size_of_extended_header)*power(256,i);

    return true;
}

bool Binary::V23::is_userdef_txt(const char *const id)
{
    return  (id[0] == 'T' && Binary::V23::correct_id(id) && strcmp(id, "TALB") && strcmp(id, "TBPM")
     && strcmp(id, "TCOP") && strcmp(id, "TDAT") && strcmp(id, "TDLY") && strcmp(id, "TENC")
     && strcmp(id, "TEXT") && strcmp(id, "TFLT") && strcmp(id, "TIME") && strcmp(id, "TIT1")
     && strcmp(id, "TIT2") && strcmp(id, "TIT3") && strcmp(id, "TKEY") && strcmp(id, "TLAN")
     && strcmp(id, "TLEN") && strcmp(id, "TMED") && strcmp(id, "TOAL") && strcmp(id, "TOFN")
     && strcmp(id, "TOLY") && strcmp(id, "TOPE") && strcmp(id, "TORY") && strcmp(id, "TOWN")
     && strcmp(id, "TPE1") && strcmp(id, "TPE2") && strcmp(id, "TPE3") && strcmp(id, "TPE4")
     && strcmp(id, "TPOS") && strcmp(id, "TPUB") && strcmp(id, "TRCK") && strcmp(id, "TRDA")
     && strcmp(id, "TRSN") && strcmp(id, "TRSO") && strcmp(id, "TSIZ") && strcmp(id, "TSRC")
     && strcmp(id, "TSSE") && strcmp(id, "TYER")&& strcmp(id, "TCOM") && strcmp(id, "TCON"));
}

bool Binary::V23::parse_data()
{
    bool fine_crc = true;
    if (expected_crc.second)
    {
        if (!content.set_data_and_check_src(file,unsynch,end_position - size_of_padding - pos(),expected_crc.first))
        {
            qCritical() << "посчитанный CRC32 не совпадает с переданным\n";
            fine_crc = false;
        }
        else
            extreme_position_of_frame = content.size() - 11 - size_of_padding;
    }

    if (fine_crc)
    {
        while (pos() <= extreme_position_of_frame)
        {
            string frame_id = get_frame_id();
            Parser frame(frame_id.c_str(), *this);
            if (frame.parse() == no_id)
                shift(-3);
        }
    }

    if (!end())
        skip();
    return fine_crc;
}
