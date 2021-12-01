#pragma once
#include "tag.h"
#include "parser.h"
using namespace std;

//тег v2.2
class Binary::V22 : public Tag
{
    friend class Parser;

    V22 (const V22 & ) = delete;
    V22 & operator = (const V22 &) = delete;

    class UserdefTxt;
    class UserdefUrl;
    class UnknownFrame;
    class BUF;
    class CNT;
    class COM;
    class CRA;
    class CRM;
    class ETC;
    class EQU;
    class GEO;
    class IPL;
    class LNK;
    class MCI;
    class MLL;
    class PIC;
    class POP;
    class REV;
    class RVA;
    class SLT;
    class STC;
    class TAL;
    class TBP;
    class TCM;
    class TCO;
    class TCR;
    class TDA;
    class TDY;
    class TEN;
    class TFT;
    class TIM;
    class TKE;
    class TLA;
    class TLE;
    class TMT;
    class TOA;
    class TOF;
    class TOL;
    class TOR;
    class TOT;
    class TP1;
    class TP2;
    class TP3;
    class TP4;
    class TPA;
    class TPB;
    class TRC;
    class TRD;
    class TRK;
    class TSI;
    class TSS;
    class TT1;
    class TT2;
    class TT3;
    class TXT;
    class TYE;
    class UFI;
    class ULT;
    class WAF;
    class WAR;
    class WAS;
    class WCM;
    class WCP;
    class WPB;

protected:
    virtual bool parseHeader() override final;

    virtual bool parseData() override final;

    virtual string getFrameId() override final;

public:
    explicit V22(Binary & file_);//объект создаётся после проверки значений версии и ревизии

    static bool is_userdef_txt(const char * const);

    static bool is_userdef_url(const char * const);

    static bool is_free_frame(const char * const);

    static bool correct_id(const char * const);

    virtual ~V22() override;
};
