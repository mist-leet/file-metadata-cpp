#pragma once
#include "frame_34.h"
#include "v24.h"

class Frame4 : public Frame34
{
    Frame4(const Frame4 &) = delete;//ЗАПРЕЩЕНО
    Frame4 & operator = (const Frame4 &) = delete;//ЗАПРЕЩЕНО

protected:
    Binary::V24 &tag;

    virtual bool parseHeader() override;

    virtual bool tagHasContent() const override final;
    virtual FileContents &tagsContent() const override final;

    virtual QString getEncodingDependentStringFromContents(FileContents &) const override final;
    virtual QString getEncodingDependentStringFromContents(FileContents &, ulong) const override final;

    virtual QString getEncodingDependentStringFileHolder() const override final;
    virtual QString getEncodingDependentStringFileHolder(ulong) const override final;

    virtual QList<QString> __getList(ulong, QChar) const override final;
    virtual QList<QString> __getList(FileContents&, ulong, QChar) const override final;

public:
    explicit Frame4(Binary::V24&);
    virtual ~Frame4() override;
};

namespace Frames_4
{
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
    //class ENCR;
    //class GRID;
    //class PRIV;
    //class SIGN;
    class SEEK;
    class ASPI;
}

class Frames_4::UnknownFrame : public Frame4
{
protected:
    virtual bool parseHeader() override final;
public:
    explicit UnknownFrame(Binary::V24 &t) : Frame4(t) {}
    virtual ~UnknownFrame() override = default;
};

class Frames_4::PaddingHandler : public Frame4
{
protected:
    virtual bool parseHeader() override final;
    virtual bool parseData() override final;
public:
    explicit PaddingHandler(Binary::V24 &t) : Frame4(t) {}
    virtual ~PaddingHandler() override = default;
};

class Frames_4::TIT2 : public Frame4
{
protected:
    virtual void extract() override final;
public:
    explicit TIT2(Binary::V24 &t) : Frame4(t) {}
    virtual ~TIT2() override = default;
};

//unique file id
class Frames_4::UFID : public Frame4
{
protected:
    virtual void extract() override final;
public:
    explicit UFID(Binary::V24 &t) : Frame4(t){}
    virtual ~UFID() override = default;
};

class Frames_4::TPE1 : public Frame4
{
protected:
    virtual void extract() override final;
public:
    explicit TPE1(Binary::V24 &t) : Frame4(t) {}
    virtual ~TPE1() override = default;
};

class Frames_4::TPE2 : public Frame4
{
protected:
    virtual void extract() override final;
public:
    explicit TPE2(Binary::V24 &t) : Frame4(t) {}
    virtual ~TPE2() override = default;
};

class Frames_4::TPE3 : public Frame4
{
protected:
    virtual void extract() override final;
public:
    explicit TPE3(Binary::V24 &t) : Frame4(t) {}
    virtual ~TPE3() override = default;
};

class Frames_4::TPE4 : public Frame4
{
protected:
    virtual void extract() override final;
public:
    explicit TPE4(Binary::V24 &t) : Frame4(t) {}
    virtual ~TPE4() override = default;
};

class Frames_4::TALB : public Frame4
{
protected:
    virtual void extract() override final;
public:
    explicit TALB(Binary::V24 &t) : Frame4(t) {}
    virtual ~TALB() override = default;
};

class Frames_4::TCON : public Frame4
{
protected:
    virtual void extract() override final;
public:
    explicit TCON(Binary::V24 &t) : Frame4(t) {}
    virtual ~TCON() override = default;
};

class Frames_4::TDRC : public Frame4
{
protected:
    virtual void extract() override final;
public:
    explicit TDRC(Binary::V24 &t) : Frame4(t) {}
    virtual ~TDRC() override = default;
};
