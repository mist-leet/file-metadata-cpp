#pragma once
#include "tag34.h"
#include "parser.h"
using namespace std;

//тег v2.4
class Binary::V24 : public Tag34
{
protected:
    Restrictions restrictions{};

    friend class Parser;

private:
    V24 (const V24 & ) = delete;
    V24 & operator = (const V24 &) = delete;

    class PaddingHandler;
    class UserdefTxt;
    class UserdefUrl;
    class UnknownFrame;
    class UFID;
    class TIT1;
    class TIT2;
    class TIT3;
    class TALB;
    class TOAL;
    class TRCK;
    class TPOS;
    class TSST;
    class TSRC;
    class TPE1;
    class TPE2;
    class TPE3;
    class TPE4;
    class TOPE;
    class TEXT;
    class TOLY;
    class TCOM;
    class TMCL;
    class TIPL;
    class TENC;
    class TBPM;
    class TLEN;
    class TKEY;
    class TLAN;
    class TCON;
    class TFLT;
    class TMED;
    class TMOO;
    class TCOP;
    class TPRO;
    class TPUB;
    class TOWN;
    class TRSN;
    class TRSO;
    class TOFN;
    class TDLY;
    class TDEN;
    class TDOR;
    class TDRC;
    class TDRL;
    class TDTG;
    class TSSE;
    class TSOA;
    class TSOP;
    class TSOT;
    class WCOM;
    class WCOP;
    class WOAF;
    class WOAR;
    class WOAS;
    class WORS;
    class WPAY;
    class WPUB;
    class MCDI;
    class ETCO;
    class MLLT;
    class SYTC;
    class USLT;
    class SYLT;
    class COMM;
    class RVA2;
    class EQU2;
    class RVRB;
    class APIC;
    class GEOB;
    class PCNT;
    class POPM;
    //class RBUF; поскольку этот фрейм имеет смысл только при стриминге файла, его можно не парсить
    class AENC;
    class LINK;
    //class POSS; тут тоже что то связанное с аудио потоком, не вижу смысла парсить этот фрейм
    class USER;
    class OWNE;
    class COMR;
    class ENCR;
    class GRID;
    //class PRIV;
    class SIGN;
    class SEEK;
    class ASPI;

protected:
    virtual bool parseExtendedHeader() override final;

    virtual bool parseHeader() override final;

    virtual bool handleCrc() override final;

    virtual void actualParse() override final;

    bool setCrc();

    bool setRestrictions();

public:
    explicit V24(Binary & file);//объект создаётся после проверки значений версии и ревизии

    static bool is_userdef_txt(const char * const);

    virtual ~V24() override;
};
