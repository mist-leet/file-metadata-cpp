#pragma once
#include "tag.h"
#include "file_contents.h"

class Tag34 : public Tag
{
protected:
    bool experimentalTag{false};
    bool footerPresence{false};
    mutable FileContents content{};//mutable - костыль, чтобы можно было переопределять const virtual функции
    ulong sizeOfExtendedHeader{0};
    std::pair<ulong, bool> expectedCrc{std::make_pair(0,false)};

private:
    Tag34(const Tag34 &) = delete;
    Tag34 & operator = (const Tag34 &) = delete;

protected:
    virtual bool parseExtendedHeader() = 0;

    virtual std::string getFrameId() override final;

    virtual long long pos() const override final;

    virtual void shift(long long) const override final;

    virtual bool handleCrc() = 0;

    virtual void actualParse() = 0;

    virtual bool parseData() override final;

public:
    explicit Tag34(Binary &);

    static bool isUserdefUrl(const char *const);

    static bool correctId(const char *const);

    static bool isFreeFrame(const char *const);

    bool hasPreextractedData() const;

    FileContents & getContent();

    virtual ~Tag34() override;
};
