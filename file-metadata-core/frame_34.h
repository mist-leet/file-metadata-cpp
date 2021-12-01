#pragma once
#include "frame.h"
#include "file_contents.h"
using namespace std;

class Frame34 : public Frame
{
protected:
    FrameStatus frameStatus{};
    FrameFormat frameFormat{};
    mutable FileContents content{};//mutable - это костыль, который пришлось поставить, чтобы переопределить const virtual функцию
    unsigned long dataLength{0};//длина информации без учёта расширенного заголовка

private:
    Frame34(const Frame34 &) = delete;//ЗАПРЕЩЕНО
    Frame34 & operator = (const Frame34 &) = delete;//ЗАПРЕЩЕНО

protected:
    void checkCompression();

    virtual char ch() const override final;

    virtual uchar get() const override final;

    virtual char uch() const override final;

    virtual uchar getb() const override final;

    char ch(int &) const;

    uchar get(int &) const;

    char uch(int &) const;

    uchar getb(int &) const;

    virtual ByteOrder getBOM() const override final;

    virtual QString getIso8859Str() const override final;

    virtual QString getIso8859Str(const long long &) const override final;

    virtual QString getUtf16Str(ByteOrder) const override final;//не чекает BOM

    virtual QString getUtf16Str(ByteOrder, const long long &) const override final;//не чекает BOM

    virtual QString getUtf8Str() const override final;

    virtual QString getUtf8Str(const long long &) const override final;

    virtual QString getUcs2Str(ByteOrder) const override final;//не чекает BOM

    virtual QString getUcs2Str(ByteOrder, const long long &) const override final;//не чекает BOM

    virtual QString getEncodingDependentString(FileContents &) const = 0;

    virtual QString getEncodingDependentString(FileContents &, const long long &) const = 0;

    virtual QString getEncodingDependentString(bool) const = 0;

    virtual QString getEncodingDependentString(bool, const long long &) const = 0;

    virtual QString getEncodingDependentString() const override final;

    virtual QString getEncodingDependentString(const long long &) const override final;

    virtual QByteArray getBinaryTillEnd() const override final;

    virtual bool skip() const override final;

    virtual long long pos() const override final;

    virtual void seek(long long) const override final;

    virtual void shift(long long) const override final;

    virtual bool end() const override final;

    virtual long long size() const override final;

    virtual string getSymbols(int) override final;

    virtual bool tagHasContent() const = 0;

    virtual FileContents & tagsContent() const = 0;

public:
    explicit Frame34(Tag &);

    uchar getGroupMark() const;

    FrameFormat & getFormat();

    const FrameFormat & getFormat() const;

    FrameStatus & getStatus();

    const FrameStatus & getStatus() const;

    virtual bool parse() override final;

    virtual ~Frame34() override;
};
