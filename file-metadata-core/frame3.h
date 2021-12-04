#pragma once
#include "frame_34.h"
#include "v23.h"

class Frame3 : public Frame34
{
    Frame3(const Frame3 &) = delete;//ЗАПРЕЩЕНО
    Frame3 & operator = (const Frame3 &) = delete;//ЗАПРЕЩЕНО

protected:
    Binary::V23 &tag;

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
    explicit Frame3(Binary::V23&);
    virtual ~Frame3() override;
};

namespace Frames_3 {
    class PaddingHandler;
    class UserdefTxt;
    class UserdefUrl;
    class UnknownFrame;
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
}

class Frames_3::UnknownFrame : public Frame3
{
protected:
    virtual bool parseHeader() override final;
public:
    explicit UnknownFrame(Binary::V23 &t) : Frame3(t) {}
    virtual ~UnknownFrame() override = default;
};

class Frames_3::PaddingHandler : public Frame3
{
protected:
    virtual bool parseHeader() override final;
    virtual bool parseData() override final;
public:
    explicit PaddingHandler(Binary::V23 &t) : Frame3(t) {}
    virtual ~PaddingHandler() override = default;
};

class Frames_3::TIT2 : public Frame3
{
protected:
    virtual void extract() override final;
public:
    explicit TIT2(Binary::V23 &t) : Frame3(t) {}
    virtual ~TIT2() override = default;
};

class Frames_3::TPE1 : public Frame3
{
protected:
    virtual void extract() override final;
public:
    explicit TPE1(Binary::V23 &t) : Frame3(t) {}
    virtual ~TPE1() override = default;
};

class Frames_3::TPE2 : public Frame3
{
protected:
    virtual void extract() override final;
public:
    explicit TPE2(Binary::V23 &t) : Frame3(t) {}
    virtual ~TPE2() override = default;
};

class Frames_3::TPE3 : public Frame3
{
protected:
    virtual void extract() override final;
public:
    explicit TPE3(Binary::V23 &t) : Frame3(t) {}
    virtual ~TPE3() override = default;
};

class Frames_3::TPE4 : public Frame3
{
protected:
    virtual void extract() override final;
public:
    explicit TPE4(Binary::V23 &t) : Frame3(t) {}
    virtual ~TPE4() override = default;
};

class Frames_3::TALB : public Frame3
{
protected:
    virtual void extract() override final;
public:
    explicit TALB(Binary::V23 &t) : Frame3(t) {}
    virtual ~TALB() override = default;
};

class Frames_3::TCON : public Frame3
{
protected:
    virtual void extract() override final;
public:
    explicit TCON(Binary::V23 &t) : Frame3(t) {}
    virtual ~TCON() override = default;
};

class Frames_3::TYER : public Frame3
{
protected:
    virtual void extract() override final;
public:
    explicit TYER(Binary::V23 &t) : Frame3(t) {}
    virtual ~TYER() override = default;
};
