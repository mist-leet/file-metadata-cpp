#pragma once
#include "frame.h"
#include "v22.h"

class Frame2 : public Frame
{
    Frame2(const Frame2 &) = delete;
    Frame2 & operator = (const Frame2 &) = delete;

protected:
    virtual bool parseHeader() override final;

    virtual QString getEncodingDependentString() const override final;
    virtual QString getEncodingDependentString(ulong) const override final;

    QList<QString> getList(ulong len, QChar separator) const;

public:
    Frame2(Binary::V22&);

    virtual bool parse() override final;

    virtual ~Frame2() override;
};

namespace Frames_2
{
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
}

class Frames_2::UnknownFrame : public Frame2
{
public:
    explicit UnknownFrame(Binary::V22 &t) : Frame2(t) {}
    virtual ~UnknownFrame() override = default;
};

class Frames_2::TT2 : public Frame2
{
protected:
    virtual void extract() override final;
public:
    explicit TT2(Binary::V22 &t) : Frame2(t) {}
    virtual ~TT2() override = default;
};

class Frames_2::TP1 : public Frame2
{
protected:
    virtual void extract() override final;
public:
    explicit TP1(Binary::V22 &t) : Frame2(t) {}
    virtual ~TP1() override = default;
};

class Frames_2::TP2 : public Frame2
{
protected:
    virtual void extract() override final;
public:
    explicit TP2(Binary::V22 &t) : Frame2(t) {}
    virtual ~TP2() override = default;
};

class Frames_2::TP3 : public Frame2
{
protected:
    virtual void extract() override final;
public:
    explicit TP3(Binary::V22 &t) : Frame2(t) {}
    virtual ~TP3() override = default;
};

class Frames_2::TP4 : public Frame2
{
protected:
    virtual void extract() override final;
public:
    explicit TP4(Binary::V22 &t) : Frame2(t) {}
    virtual ~TP4() override = default;
};

class Frames_2::TAL : public Frame2
{
protected:
    virtual void extract() override final;
public:
    explicit TAL(Binary::V22 &t) : Frame2(t) {}
    virtual ~TAL() override = default;
};

class Frames_2::TCO : public Frame2
{
protected:
    virtual void extract() override final;
public:
    explicit TCO(Binary::V22 &t) : Frame2(t) {}
    virtual ~TCO() override = default;
};

class Frames_2::TYE : public Frame2
{
protected:
    virtual void extract() override final;
public:
    explicit TYE(Binary::V22 &t) : Frame2(t) {}
    virtual ~TYE() override = default;
};
