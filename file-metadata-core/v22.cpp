#include "v22.h"
#include "frames2.h"
using namespace std;

Binary::V22::V22(Binary & f) :
    Tag(f)
{}

Binary::V22::~V22() = default;

bool Binary::V22::parse_header()
{
    mByte flags = get();
    unsynch = flags.test(7);
    bool correctness = set_length([this](int &count)
                                    {
                                        return this->File_holder::get(count);
                                    }).second;
    end_position = start_position + 10 + length;
    extreme_position_of_frame = end_position - 7;
    if (correctness)
        correctness = !flags.test(6);
    return correctness;
}

string Binary::V22::get_frame_id()
{
    return get_symbols(3);
}

bool Binary::V22::correct_id(const char * const id)
{
    for (int i = 0;i < 3;++i)
        if (!correct_char(id[i]))
            return false;
    return !id[3];
}

bool Binary::V22::is_userdef_txt(const char * const id)
{
    return (id[0] == 'T' && V22::correct_id(id) && strcmp(id, "TAL") && strcmp(id, "TBP") && strcmp(id, "TCM")
     && strcmp(id, "TCR") && strcmp(id, "TDA") && strcmp(id, "TDY") && strcmp(id, "TEN")
     && strcmp(id, "TFT") && strcmp(id, "TIM") && strcmp(id, "TKE") && strcmp(id, "TLA")
     && strcmp(id, "TLE") && strcmp(id, "TMT") && strcmp(id, "TOA") && strcmp(id, "TOF")
     && strcmp(id, "TOL") && strcmp(id, "TOR") && strcmp(id, "TOT") && strcmp(id, "TP1")
     && strcmp(id, "TP2") && strcmp(id, "TP3") && strcmp(id, "TP4") && strcmp(id, "TPA")
     && strcmp(id, "TPB") && strcmp(id, "TRC") && strcmp(id, "TRD") && strcmp(id, "TRK")
     && strcmp(id, "TSI") && strcmp(id, "TSS") && strcmp(id, "TT1") && strcmp(id, "TT2")
     && strcmp(id, "TT3") && strcmp(id, "TXT") && strcmp(id, "TYE") && strcmp(id, "TCO"));
}

bool Binary::V22::is_userdef_url(const char * const id)
{
    return (id[0] == 'W' && V22::correct_id(id) && strcmp(id, "WAF") && strcmp(id, "WAR") && strcmp(id, "WAS")
             && strcmp(id, "WCM") && strcmp(id, "WCP") && strcmp(id, "WPB"));
}

bool Binary::V22::is_free_frame(const char * const id)
{
    return (id[0] == 'X' || id[0] == 'Y' || id[0] == 'Z') && V22::correct_id(id);
}

bool Binary::V22::parse_data()
{
    while (pos() <= extreme_position_of_frame)
    {
        string frame_id = get_frame_id();
        Parser frame(frame_id.c_str(), *this);
        if (frame.parse() == no_id)
            shift(-2);
    }
    if (!end())//на всякий случай
        skip();
    return true;
}
