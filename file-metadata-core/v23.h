#pragma once
#include "v22.h"
using namespace std;

//тег v2.3
class Binary::V23 : public Binary::V22
{
protected:
    bool experimental_tag;
    pair<unsigned long, bool> CRC32;
    unordered_map<unsigned char, string> group_markers;
    unsigned long size_of_extended_header;

private:
    pair<unsigned long, bool> size_of_padding;

    V23 (const V23 & ) = delete ;
    V23 & operator = (const V23 &) = delete ;

    class Frame3;
    friend class Frame3;

    friend class Binary::V24;

protected:
    virtual bool parse_extended_header();

    virtual bool parse_header() override;
public:
    explicit V23(Binary & file) :
        V22(file),
        experimental_tag(false),
        CRC32(make_pair(0,false)),
        size_of_extended_header(0),
        size_of_padding(make_pair(0,false))
    {}

    virtual bool parse() override;

    virtual ~V23() override = default;
};
