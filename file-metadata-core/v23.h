#pragma once
#include "tag34.h"
#include "parser.h"
using namespace std;

//тег v2.3
class Binary::V23 : public Tag34
{
    friend class Parser;

    ulong size_of_padding{0};

    class padding_handler;
    class userdef_txt;
    class userdef_url;
    class unknown_frame;
    class AENC;
    class APIC;
    class COMM;
    class COMR;
    class ENCR;
    class EQUA;
    class ETCO;
    class GEOB;
    class GRID;
    class IPLS;
    class LINK;
    class MCDI;
    class MLLT;
    class OWNE;
    class PRIV;
    class PCNT;
    class POPM;
    class POSS;
    class RBUF;
    class RVAD;
    class RVRB;
    class SYLT;
    class SYTC;
    class TALB;
    class TBPM;
    class TCOM;
    class TCON;
    class TCOP;
    class TDAT;
    class TDLY;
    class TENC;
    class TEXT;
    class TFLT;
    class TIME;
    class TIT1;
    class TIT2;
    class TIT3;
    class TKEY;
    class TLAN;
    class TLEN;
    class TMED;
    class TOAL;
    class TOFN;
    class TOLY;
    class TOPE;
    class TORY;
    class TOWN;
    class TPE1;
    class TPE2;
    class TPE3;
    class TPE4;
    class TPOS;
    class TPUB;
    class TRCK;
    class TRDA;
    class TRSN;
    class TRSO;
    class TSIZ;
    class TSRC;
    class TSSE;
    class TYER;
    class UFID;
    class USER;
    class USLT;
    class WCOM;
    class WCOP;
    class WOAF;
    class WOAR;
    class WOAS;
    class WORS;
    class WPAY;
    class WPUB;

    V23 (const V23 & ) = delete ;
    V23 & operator = (const V23 &) = delete ;

protected:
    virtual bool parse_extended_header() override final;

    virtual bool parse_header() override final;

    virtual bool parse_data() override final;

public:
    explicit V23(Binary &);//объект создаётся после проверки значений версии и ревизии

    static bool is_userdef_txt(const char *const);

    virtual ~V23() override;
};
