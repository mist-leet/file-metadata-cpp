#pragma once
#include "frame.h"
#include "file_contents.h"

class Frame34 : public Frame
{
protected:
    FrameStatus frameStatus{};
    ulong uncompressedSize{0};//0 означает отсутствие сжатия
    bool unreadable{false};//фрейм зашифрован или сжат без указания размера несжатых данных
    mutable FileContents content{};//mutable - это костыль, который пришлось поставить, чтобы переопределить const virtual функцию
    unsigned long dataLength{0};//длина информации без учёта расширенного заголовка

private:
    Frame34(const Frame34 &) = delete;//ЗАПРЕЩЕНО
    Frame34 & operator = (const Frame34 &) = delete;//ЗАПРЕЩЕНО

protected:
    void checkCompression();

    virtual char ch() const override final;
    virtual char uch() const override final;
    char ch(ulong&) const;
    char uch(ulong&) const;

    virtual uchar get() const override final;
    virtual uchar getb() const override final;
    uchar get(ulong&) const;
    uchar getb(ulong&) const;

    virtual QString getEncodingDependentStringFromContents(FileContents &) const = 0;
    virtual QString getEncodingDependentStringFromContents(FileContents &, ulong) const = 0;

    virtual QString getEncodingDependentStringFileHolder() const = 0;
    virtual QString getEncodingDependentStringFileHolder(ulong) const = 0;

    virtual QString getEncodingDependentString() const override final;
    virtual QString getEncodingDependentString(ulong) const override final;

    virtual QString getUrl() const override final;
    virtual QString getUrl(ulong) const override final;

    virtual std::vector<uchar> getBinaryTillEnd() const override final;
    virtual ulong get32Bit(ulong &) const override final;
    virtual std::pair<uint, uint> getNumericPair(ulong, char) const override final;
    QList<QString> getList(ulong, QChar) const;

    virtual QList<QString> __getList(ulong, QChar) const = 0;
    virtual QList<QString> __getList(FileContents&, ulong, QChar) const = 0;

    virtual bool skip() const override final;
    virtual long long pos() const override final;
    virtual void seek(long long) const override final;
    virtual void shift(long long) const override final;
    virtual bool end() const override final;
    virtual long long size() const override final;

    virtual std::string getSymbols(int) override final;

    virtual bool tagHasContent() const = 0;
    virtual FileContents &tagsContent() const = 0;

public:
    Frame34(Binary&, bool);

    FrameStatus & getStatus();
    const FrameStatus & getStatus() const;

    virtual bool parse() override final;

    virtual ~Frame34() override;
};
