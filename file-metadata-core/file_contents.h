#pragma once
#include "binary.h"

class FileContents
{
protected:
    std::vector<uchar> arr{};
    ulong position{0};

    std::function<uchar()> getLambda{
        [this] {
            return this->get();
        }
    };

public:
    FileContents();

    bool setDataAndCheckSrc(Binary &file, bool unsynch, ulong raw_data_size, ulong expected_crc);//file -> tag

    bool decompressRawData(Binary &file, bool unsynch, ulong raw_data_size, ulong expected_data_size);//file -> frame

    bool decompressRawData(FileContents &other_storage, ulong raw_data_size, ulong expected_data_size);//tag -> frame

    std::vector<uchar> shareData(ulong size);

    char ch();
    char ch(ulong &);
    uchar get();
    uchar get(ulong &);

    std::vector<uchar> getBinaryTillEnd();

    QString getEncodingDependentString(TagVersion);
    QString getEncodingDependentString(TagVersion, ulong);

    QString getUrl();
    QString getUrl(ulong);

    ulong get32Bit(ulong &count);

    std::pair<uint, uint> getNumericPair(ulong len, uchar separator);

    QList<QString> getList(ulong len, TagVersion v, QChar separator);

    bool skip();

    ulong pos() const;

    void seek(ulong);

    void shift(long long = -1);

    bool end() const;

    ulong lastPos() const;

    ulong size() const;

    std::string getSymbols(int);

    std::string getFrame34Id();

    operator bool () const;

    virtual ~FileContents();
};
