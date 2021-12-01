#pragma once
#include "frame_structs.h"
#include "tag_structs.h"
#include "file_structs.h"
#include "new_char_extracting.h"
#include "global_functions.h"
#include "debugfile.h"

class Binary : public QFile
{
    Binary(const Binary &) = delete;
    Binary& operator = (const Binary &) = delete;

    void oneByteBack();

protected:
    FileMetadata data{};

    std::function<char()> chLambda {
                                    [this] {
                                        return this->ch();
                                    }
                                };

    std::function<uchar()> getLambda {
                                    [this] {
                                        return this->get();
                                    }
                                };

    std::function<void()> backLambda {
                                    [this] {
                                        return this->oneByteBack();
                                    }
                                };

    void seekForStartOfFooter();

    void shift(long long = -1);

    void backFromEnd(qint64);
    char charBackwards();
    bool checkFor3Char(std::string);

    TagVersion v2Header();

public:
    class V1;
    class V22;
    class V23;
    class V24;

    explicit Binary(const QString &);
    Binary();

    bool openf(const QString &);

    char ch();
    char uch(bool);
    char ch(ulong&);
    char uch(ulong&, bool);

    uchar get();
    uchar getb(bool);
    uchar get(ulong&);
    uchar getb(ulong&, bool);

    QString getUrl(bool, ulong);
    QString getEncodingDependentString(bool, TagVersion, ulong);
    QList<QString> getList(bool, TagVersion, ulong, QChar);
    ulong get32Bit(bool unsynch, ulong &count);
    std::pair<uint, uint> getNumericPair(bool unsynch, ulong len, char separator);
    std::vector<uchar> getBytes(bool, ulong);

    operator bool () const;

    const FileMetadata &getData() const;
    FileMetadata &getData();

    bool hasInfo() const;

    bool parse();

    ulong parseV2Footer();//возвращает 0, если футер не найден или некорректен
    void parseFromStart();
    void parseFromEnd();
    void parseV1();

    virtual ~Binary() override;
};
