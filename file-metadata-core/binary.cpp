#include "binary.h"
#include "tagparser.h"

Binary::Binary(const QString &path)
    : QFile(path)
{
    qDebug() << "Binary: constructing\n";
    QFile::open(QIODevice::ReadWrite | QIODevice::ExistingOnly);
    if (QFileDevice::isOpen())
        seek(0);
}

Binary::Binary()
    : QFile()
{}

Binary::~Binary() {
    close();
}

bool Binary::openf(const QString &path) {
    setFileName(path);
    QFile::open(QIODevice::ReadWrite | QIODevice::ExistingOnly);
    if (QFileDevice::isOpen()) {
        seek(0);
    }
    return QFileDevice::isOpen();
}

char Binary::ch(ulong &count) {
    return extr::ch([this](char *c) {
                            return this->getChar(c);
                        }, count);
}

char Binary::uch(ulong &count, bool unsynch) {
    return extr::getUns(chLambda, unsynch, backLambda, count);
}

uchar Binary::get(ulong &count) {
    return extr::get([this](char *c) {
                            return this->getChar(c);
                        }, count);
}

uchar Binary::getb(ulong &count, bool unsynch) {
    return extr::getUns(getLambda, unsynch, backLambda, count);
}

Binary::operator bool() const {
    return QFileDevice::isOpen();
}

Binary & Binary::operator << (const string & s)
{
    write(s.c_str(),s.size());
    return *this;
}

Binary & Binary::operator << (char c)
{
    write(&c,1);
    return *this;
}

Binary & Binary::operator >> (char & c)
{
    getChar(&c);
    return *this;
}

const FileMetadata & Binary::getData() const {
    return data;
}

FileMetadata & Binary::getData() {
    return data;
}

bool Binary::hasInfo() const {
    return data.hasInfo();
}

void Binary::shift(long long offset) {
    long long destination = pos() + offset;

    if (destination >=0 || destination < size())
        seek(destination);
    else {
        if (destination < 0)
            seek(0);
        else
            seek(size() - 1);
    }
}

void Binary::oneByteBack() {
    seek(pos() - 1);
}

void Binary::seekForStartOfFooter() {
    qDebug() << "Binary: seeking for start of the first footer" << endl;
    backFromEnd(v1Len);//перемещаемся на место предполагаемого тега v1

    if (checkFor3Char("TAG")) {
        backFromEnd(v1Len + headerLen);
    }
    else {
        backFromEnd(headerLen);
    }
}

QByteArray Binary::get_bytes(bool unsynch, ulong amount)
{
    return ::get_bytes(getChar_lambda
                        , unsynch
                        , one_byte_back_lambda
                        , amount);
}

std::vector<uchar> Binary::getBytes(bool unsynch, ulong amount) {
    return extr::vGetBytes(getLambda, unsynch, backLambda, amount);
}

char Binary::ch() {
    return extr::ch([this](char *c) {
        return this->getChar(c);
    });
}

char Binary::uch(bool unsynch) {
    return extr::getUns(chLambda, unsynch, backLambda);
}

uchar Binary::get() {
    return extr::get([this](char *c) {
        return this->getChar(c);
    });
}

uchar Binary::getb(bool unsynch) {
    return extr::getUns(getLambda, unsynch, backLambda);
}

QString Binary::getUrl(bool unsynch, ulong len) {
    return extr::getUrl(chLambda, unsynch, backLambda, len);
}

QString Binary::getEncodingDependentString(bool unsynch, TagVersion v, ulong len) {
    qDebug() << "Binary: calling function for encoding dependent string from extr namespace, length is" << len << endl;
    return extr::getEncodingDependentString(chLambda, unsynch, backLambda, len, v);
}

QList<QString> Binary::getList(bool unsynch, TagVersion v, ulong len, QChar separator) {
    return extr::getList(chLambda, unsynch, backLambda, len, v, separator);
}

ulong Binary::get32Bit(bool unsynch, ulong &count) {
    return extr::get32Bit(chLambda, unsynch, backLambda, count);
}

std::pair<uint, uint> Binary::getNumericPair(bool unsynch, ulong len, char separator) {
    return extr::getNumericPair(chLambda, unsynch, backLambda, len, separator);
}

void Binary::parseFromStart() {
    seek(0);
    TagVersion v;
    qDebug() << "Binary: starting to seek for tag from the start\n";
    do {
        v = v2Header();
        if (v == noTag)
            break;
        else {
            qDebug() << "Binary: starting to parse\n";
            TagParser v2(v, *this);
            v2.parse();
            qDebug() << "Binary: ended parsing" << endl;
        }
    } while (v != noTag);
    qDebug() << "Binary: parsing from start complete" << endl;
}

void Binary::parseFromEnd() {
    qDebug() << "Binary: starting to seek for tag from end" << endl;

    seekForStartOfFooter();

    TagVersion v;
    qint64 len = 0;

    do {
        len = parseV2Footer();//чекаем длину предполагаемого тега
        shift(-len - 20);//перемещаемся в начало предполагаемого тега
        v = v2Header();//чекаем идентификатор хедера предполагаемого тега
        if (v == noTag)
            break;
        else {
            qDebug() << "Binary: starting to parse v2.4 header at the end of the file" << endl;
            TagParser v2(v, *this);
            v2.parse();
            shift(-len - 20);//перемещаемся в место, где начинается футер предыдущего тега, если он есть
            qDebug() << "Binary: parsing of the 2.4 header at the end complete" << endl;
        }
    } while (v != noTag);

    qDebug() << "Binary: parsing from end complete" << endl;
}

void Binary::parseV1() {
    if (data.needsV1()) {
        qDebug() << "Binary: starting to seek for v1" << endl;

        backFromEnd(128);//перемещаемся на место предполагаемого тега v1
        if (checkFor3Char("TAG")) {
            qDebug() << "Binary: starting to parse v1" << endl;
            TagParser v1(*this);
            v1.parse();
            qDebug() << "Binary: parsing v1 complete" << endl;
        }
    }
}

bool Binary::parse() {
    if (QFileDevice::isOpen()) {
        qDebug() << "Binary: start parsing\n";
        parseFromStart();
        parseFromEnd();
        parseV1();
        qDebug() << "Binary: parsing complete" << endl;
        return data.hasInfo();
    }
    else
        return false;
}

void Binary::backFromEnd(qint64 offset) {
    qint64 sz = size();
    if (offset <= sz)
        seek(sz - offset);
    else
        seek(0);
}

char Binary::charBackwards() {
    char c;
    getChar(&c);
    shift(-2);
    return c;
}

bool Binary::checkFor3Char(std::string value) {
    qDebug() << "Binary: checking for" << value.c_str() << endl;
    char id[4];
    for (int i = 0;i < 3;++i)
        getChar(id + i);
    id[3] = 0;
    return !strcmp(id,value.c_str());
}

TagVersion Binary::v2Header() {
    qDebug() << "Binary: checking for v2 header\n";
    if (checkFor3Char("ID3")) {
        uchar version = get();
        if (get() != 255) {
            switch (version) {
            case 2: {
                qDebug() << "Binary: v2 header found, version is" << 2 << endl;
                return two;
            }
            case 3: {
                qDebug() << "Binary: v2 header found, version is" << 3 << endl;
                return three;
            }
            case 4: {
                qDebug() << "Binary: v2 header found, version is" << 4 << endl;
                return four;
            }
            default: {
                qDebug() << "Binary: no v2 header\n";
                return noTag;
            }
            }
        }
        else {
            qDebug() << "Binary: no v2 header\n";
            return noTag;
        }
    }
    else {
        qDebug() << "Binary: no v2 header\n";
        return noTag;
    }
}

ulong Binary::parseV2Footer() {//возвращает 0, если футер не найден или некорректен
    qDebug() << "Binary: trying to parse v2 footer" << endl;
    if (checkFor3Char("3DI")) {
        if (get() == 4) {
            if (get() != 255) {
                mByte flags = get();
                if (!flags[4])//если в футере указано, что футера нет
                    return 0;
                for (uint i = 0;i < 4;++i)
                    if (flags[i])//если проставлены неопределённые флаги
                        return 0;

                ulong len = 0;
                uchar c;
                for (int i = 3;i >= 0;--i) {
                    c = get();
                    if (c > 127)//выставлен msb
                        return 0;
                    else
                        len += c*Gl::power(128,i);
                }
                return len;
            }
            else
                return 0;
        }
        else
            return 0;
    }
    else
        return 0;
}
