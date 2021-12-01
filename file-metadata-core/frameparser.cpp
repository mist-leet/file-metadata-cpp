#include "frameparser.h"
using std::nothrow;

FrameParser::FrameParser(const char *const id, Binary::V22 &tag) {
        qDebug() << "FrameParser: constructing for V2\n";
        if (Binary::V22::isFreeFrame(id)) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (Binary::V22::isUserdefUrl(id)) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (Binary::V22::isUserdefTxt(id)) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "BUF")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "CNT")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "COM")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "CRA")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "CRM")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "ETC")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "EQU")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "GEO")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "IPL")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "LNK")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "MCI")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "MLL")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "PIC")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "POP")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "REV")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "RVA")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "SLT")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "STC")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TAL")) {frame = new(nothrow) Frames_2::TAL(tag);return;}
        if (!strcmp(id, "TBP")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TCM")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TCO")) {frame = new(nothrow) Frames_2::TCO(tag);return;}
        if (!strcmp(id, "TCR")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TDA")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TDY")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TEN")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TFT")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TIM")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TKE")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TLA")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TLE")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TMT")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOA")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOF")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOL")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOR")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOT")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TP1")) {frame = new(nothrow) Frames_2::TP1(tag);return;}
        if (!strcmp(id, "TP2")) {frame = new(nothrow) Frames_2::TP2(tag);return;}
        if (!strcmp(id, "TP3")) {frame = new(nothrow) Frames_2::TP3(tag);return;}
        if (!strcmp(id, "TP4")) {frame = new(nothrow) Frames_2::TP4(tag);return;}
        if (!strcmp(id, "TPA")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TPB")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TRC")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TRD")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TRK")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TSI")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TSS")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TT1")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TT2")) {frame = new(nothrow) Frames_2::TT2(tag);return;}
        if (!strcmp(id, "TT3")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TXT")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "TYE")) {frame = new(nothrow) Frames_2::TYE(tag);return;}
        if (!strcmp(id, "UFI")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "ULT")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "WAF")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "WAR")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "WAS")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "WCM")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "WCP")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
        if (!strcmp(id, "WPB")) {frame = new(nothrow) Frames_2::UnknownFrame(tag);return;}
}

FrameParser::FrameParser(const char *const id, Binary::V23 &tag) {
        qDebug() << "FrameParser: constructing for V3\n";
        if (Gl::isNull(id)) {frame = new(nothrow) Frames_3::PaddingHandler(tag);return;}
        if (Binary::V23::isFreeFrame(id)) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (Binary::V23::isUserdefUrl(id)) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (Binary::V23::isUserdefTxt(id)) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "AENC")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "APIC")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "COMM")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "COMR")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "ENCR")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "EQUA")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "ETCO")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "GEOB")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "GRID")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "IPLS")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "LINK")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "MCDI")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "MLLT")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "OWNE")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "PRIV")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "PCNT")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "POPM")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "POSS")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "RBUF")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "RVAD")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "RVRB")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "SYLT")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "SYTC")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TALB")) {frame = new(nothrow) Frames_3::TALB(tag);return;}
        if (!strcmp(id, "TBPM")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TCOM")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TCON")) {frame = new(nothrow) Frames_3::TCON(tag);return;}
        if (!strcmp(id, "TCOP")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TDAT")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TDLY")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TENC")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TEXT")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TFLT")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TIME")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TIT1")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TIT2")) {frame = new(nothrow) Frames_3::TIT2(tag);return;}
        if (!strcmp(id, "TIT3")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TKEY")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TLAN")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TLEN")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TMED")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOAL")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOFN")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOLY")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOPE")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TORY")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOWN")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TPE1")) {frame = new(nothrow) Frames_3::TPE1(tag);return;}
        if (!strcmp(id, "TPE2")) {frame = new(nothrow) Frames_3::TPE2(tag);return;}
        if (!strcmp(id, "TPE3")) {frame = new(nothrow) Frames_3::TPE3(tag);return;}
        if (!strcmp(id, "TPE4")) {frame = new(nothrow) Frames_3::TPE4(tag);return;}
        if (!strcmp(id, "TPOS")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TPUB")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TRCK")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TRDA")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TRSN")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TRSO")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TSIZ")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TSRC")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TSSE")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "TYER")) {frame = new(nothrow) Frames_3::TYER(tag);return;}
        if (!strcmp(id, "UFID")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "USER")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "USLT")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "WCOM")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "WCOP")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "WOAF")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "WOAR")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "WOAS")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "WORS")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "WPAY")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
        if (!strcmp(id, "WPUB")) {frame = new(nothrow) Frames_3::UnknownFrame(tag);return;}
}

FrameParser::FrameParser(const char *const id, Binary::V24 &tag) {
        qDebug() << "FrameParser: constructing for V4\n";
        if (Gl::isNull(id)) {frame = new(nothrow) Frames_4::PaddingHandler(tag);return;}
        if (Binary::V24::isFreeFrame(id)) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (Binary::V24::isUserdefUrl(id)) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (Binary::V24::isUserdefTxt(id)) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "UFID")) {frame = new(nothrow) Frames_4::UFID(tag);return;}
        if (!strcmp(id, "TIT1")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TIT2")) {frame = new(nothrow) Frames_4::TIT2(tag);return;}
        if (!strcmp(id, "TIT3")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TALB")) {frame = new(nothrow) Frames_4::TALB(tag);return;}
        if (!strcmp(id, "TOAL")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TRCK")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TPOS")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TSST")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TSRC")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TPE1")) {frame = new(nothrow) Frames_4::TPE1(tag);return;}
        if (!strcmp(id, "TPE2")) {frame = new(nothrow) Frames_4::TPE2(tag);return;}
        if (!strcmp(id, "TPE3")) {frame = new(nothrow) Frames_4::TPE3(tag);return;}
        if (!strcmp(id, "TPE4")) {frame = new(nothrow) Frames_4::TPE4(tag);return;}
        if (!strcmp(id, "TOPE")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TEXT")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOLY")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TCOM")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TMCL")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TIPL")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TENC")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TBPM")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TLEN")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TKEY")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TLAN")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TCON")) {frame = new(nothrow) Frames_4::TCON(tag);return;}
        if (!strcmp(id, "TFLT")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TMED")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TMOO")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TCOP")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TPRO")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TPUB")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOWN")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TRSN")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TRSO")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TOFN")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TDLY")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TDEN")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TDOR")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TDRC")) {frame = new(nothrow) Frames_4::TDRC(tag);return;}
        if (!strcmp(id, "TDRL")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TDTG")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TSSE")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TSOA")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TSOP")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "TSOT")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "WCOM")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "WCOP")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "WOAF")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "WOAR")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "WOAS")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "WORS")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "WPAY")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "WPUB")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "MCDI")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "ETCO")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "MLLT")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "SYTC")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "USLT")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "SYLT")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "COMM")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "RVA2")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "EQU2")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "RVRB")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "APIC")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "GEOB")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "PCNT")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "POPM")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "RBUF")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "AENC")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "LINK")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "POSS")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "USER")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "OWNE")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "COMR")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "ENCR")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "GRID")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "PRIV")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "SIGN")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "SEEK")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
        if (!strcmp(id, "ASPI")) {frame = new(nothrow) Frames_4::UnknownFrame(tag);return;}
}

ParsingResult FrameParser::parse() const {
    if (frame) {
        if (frame->parse()) {
            return success;
        }
        else {
            return fail;
        }
    }
    else {
        return noId;
    }
}

FrameParser::~FrameParser() {
    qDebug() << "FrameParser: dying\n";
    delete frame;
}
