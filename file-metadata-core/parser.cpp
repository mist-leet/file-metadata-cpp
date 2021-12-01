#include "parser.h"
using namespace std;

//V1
Parser::Parser(Binary &file)
    : subject(new(nothrow) Binary::V1(file))
{}

//V2*
Parser::Parser(TagVersion version, Binary &file)
{
    switch (version)
    {
    case two:
        subject = new(nothrow) Binary::V22(file);
        return;
    case three:
        subject = new(nothrow) Binary::V23(file);
        return;
    case four:
        subject = new(nothrow) Binary::V24(file);
        return;
    case noTag:
        return;
    }
}

//frame 2
Parser::Parser(const char * const id, Binary::V22 &tag)
{
    setFrame(id, tag);
}

//frame 3
Parser::Parser(const char * const id , Binary::V23 &tag)
{
    setFrame(id, tag);
}

//frame 4
Parser::Parser(const char * const id, Binary::V24 &tag)
{
    setFrame(id, tag);
}

Parser::~Parser()
{
    delete subject;
}

void Parser::setFrame(const char *const id, Binary::V22 &tag)
{
    if (!subject)//если память ещё не выделена
    {
        if (Binary::V22::isFreeFrame(id)) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (Binary::V22::isUserdefUrl(id)) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (Binary::V22::isUserdefTxt(id)) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "BUF")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "CNT")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "COM")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "CRA")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "CRM")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "ETC")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "EQU")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "GEO")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "IPL")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "LNK")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "MCI")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "MLL")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "PIC")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "POP")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "REV")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "RVA")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "SLT")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "STC")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TAL")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TBP")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TCM")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TCO")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TCR")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TDA")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TDY")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TEN")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TFT")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TIM")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TKE")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TLA")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TLE")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TMT")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOA")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOF")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOL")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOR")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOT")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TP1")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TP2")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TP3")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TP4")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TPA")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TPB")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TRC")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TRD")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TRK")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TSI")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TSS")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TT1")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TT2")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TT3")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TXT")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "TYE")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "UFI")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "ULT")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "WAF")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "WAR")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "WAS")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "WCM")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "WCP")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
        if (!strcmp(id, "WPB")) {subject = new(nothrow) Binary::V22::UnknownFrame(tag);return;}
    }
}

void Parser::setFrame(const char *const id, Binary::V23 &tag)
{
    if (!subject)//если память ещё не выделена
    {
        if (isNull(id)) {subject = new(nothrow) Binary::V23::PaddingHandler(tag);return;}
        if (Binary::V23::isFreeFrame(id)) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (Binary::V23::isUserdefUrl(id)) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (Binary::V23::isUserdefTxt(id)) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "AENC")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "APIC")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "COMM")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "COMR")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "ENCR")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "EQUA")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "ETCO")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "GEOB")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "GRID")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "IPLS")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "LINK")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "MCDI")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "MLLT")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "OWNE")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "PRIV")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "PCNT")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "POPM")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "POSS")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "RBUF")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "RVAD")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "RVRB")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "SYLT")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "SYTC")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TALB")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TBPM")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TCOM")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TCON")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TCOP")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TDAT")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TDLY")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TENC")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TEXT")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TFLT")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TIME")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TIT1")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TIT2")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TIT3")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TKEY")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TLAN")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TLEN")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TMED")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOAL")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOFN")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOLY")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOPE")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TORY")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOWN")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TPE1")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TPE2")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TPE3")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TPE4")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TPOS")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TPUB")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TRCK")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TRDA")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TRSN")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TRSO")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TSIZ")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TSRC")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TSSE")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "TYER")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "UFID")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "USER")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "USLT")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "WCOM")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "WCOP")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "WOAF")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "WOAR")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "WOAS")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "WORS")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "WPAY")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
        if (!strcmp(id, "WPUB")) {subject = new(nothrow) Binary::V23::UnknownFrame(tag);return;}
    }
}

void Parser::setFrame(const char *const id, Binary::V24 &tag)
{
    if (!subject)//если память ещё не выделена
    {
        if (isNull(id)) {subject = new(nothrow) Binary::V24::PaddingHandler(tag);return;}
        if (Binary::V24::isFreeFrame(id)) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (Binary::V24::isUserdefUrl(id)) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (Binary::V24::isUserdefTxt(id)) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "UFID")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TIT1")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TIT2")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TIT3")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TALB")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOAL")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TRCK")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TPOS")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TSST")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TSRC")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TPE1")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TPE2")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TPE3")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TPE4")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOPE")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TEXT")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOLY")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TCOM")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TMCL")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TIPL")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TENC")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TBPM")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TLEN")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TKEY")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TLAN")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TCON")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TFLT")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TMED")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TMOO")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TCOP")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TPRO")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TPUB")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOWN")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TRSN")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TRSO")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOFN")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TDLY")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TDEN")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TDOR")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TDRC")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TDRL")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TDTG")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TSSE")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TSOA")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TSOP")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "TSOT")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "WCOM")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "WCOP")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "WOAF")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "WOAR")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "WOAS")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "WORS")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "WPAY")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "WPUB")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "MCDI")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "ETCO")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "MLLT")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "SYTC")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "USLT")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "SYLT")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "COMM")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "RVA2")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "EQU2")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "RVRB")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "APIC")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "GEOB")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "PCNT")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "POPM")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "RBUF")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "AENC")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "LINK")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "POSS")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "USER")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "OWNE")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "COMR")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "ENCR")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "GRID")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "PRIV")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "SIGN")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "SEEK")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
        if (!strcmp(id, "ASPI")) {subject = new(nothrow) Binary::V24::UnknownFrame(tag);return;}
    }
}

ParsingResult Parser::parse() const
{
    if (subject)//если память выделена
    {
        if (subject->parse())
            return success;
        else
            return fail;
    }
    else
        return noId;
}
