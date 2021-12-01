#include "frame_34.h"
using std::vector;

Frame34::Frame34(Binary &f, bool u)
    : Frame(f, u)
{}

Frame34::~Frame34() = default;

bool Frame34::parse() {
    qDebug() << "Frame3,4: starting to parse\n";
    if (parseHeader()) {
        if (unreadable) {
            qDebug() << "Frame3,4: i am unreadable, skipping\n";
            return skip();
        }
        else {
            checkCompression();
            qDebug() << "Frame3,4: ended checking compression, going to parse data\n";
            return parseData();
        }
    }
    else
        return !skip();
}

FrameStatus & Frame34::getStatus() {
    return frameStatus;
}

const FrameStatus & Frame34::getStatus() const {
    return frameStatus;
}

QString Frame34::getEncodingDependentString() const {
    qDebug() << "Frame3,4: getting encoding dependent string\n";
    if (content) {
        qDebug() << "Frame3,4: getting encoding dependent string from frame's content\n";
        return getEncodingDependentString(content);
    }
    else {
        if (tagHasContent()) {
            qDebug() << "Frame3,4: getting encoding dependent string from tag's content\n";
            return getEncodingDependentString(tagsContent());
        }
        else {
            qDebug() << "Frame3,4: getting encoding dependent string straight from file\n";
            return getEncodingDependentStringFileHolder();
        }
    }
}

QString Frame34::getEncodingDependentString(ulong len) const {
    if (content)
        return getEncodingDependentStringFromContents(content, len);
    else {
        if (tagHasContent())
            return getEncodingDependentStringFromContents(tagsContent(), len);
        else
            return getEncodingDependentStringFileHolder(len);
    }
}

QString Frame34::getUrl() const {
    if (content) {
        return content.getUrl();
    }
    else {
        if (tagHasContent()) {
            return tagsContent().getUrl();
        }
        else {
            return FileHolder::getUrl();
        }
    }
}

QString Frame34::getUrl(ulong len) const {
    if (content) {
        return content.getUrl(len);
    }
    else {
        if (tagHasContent()) {
            return tagsContent().getUrl(len);
        }
        else {
            return FileHolder::getUrl(len);
        }
    }
}

vector<uchar> Frame34::getBinaryTillEnd() const {
    if (content)
        return content.getBinaryTillEnd();
    else {
        if (tagHasContent())
            return tagsContent().getBinaryTillEnd();
        else
            return FileHolder::getBinaryTillEnd();
    }
}

ulong Frame34::get32Bit(ulong &count) const {
    if (content)
        return content.get32Bit(count);
    else {
        if (tagHasContent())
            return tagsContent().get32Bit(count);
        else
            return FileHolder::get32Bit(count);
    }
}

std::pair<uint, uint> Frame34::getNumericPair(ulong len, char separator) const {
    if (content)
        return content.getNumericPair(len, toUchar(separator));
    else {
        if (tagHasContent())
            return tagsContent().getNumericPair(len, toUchar(separator));
        else
            return FileHolder::getNumericPair(len, separator);
    }
}

QList<QString> Frame34::getList(ulong len, QChar separator) const {
    if (content)
        return __getList(content, len, separator);
    else {
        if (tagHasContent())
            return __getList(tagsContent(), len, separator);
        else
            return __getList(len, separator);
    }
}

bool Frame34::skip() const {
    qDebug() << "Frame3,4: skipping\n";
    if (content)
        return content.skip();
    else {
        if (tagHasContent()) {
            tagsContent().seek(endPosition);
            return true;
        }
        else
            return FileHolder::skip();
    }
}

long long Frame34::pos() const {
    if (content)
        return content.pos();
    else
    {
        if (tagHasContent())
            return tagsContent().pos();
        else
            return FileHolder::pos();
    }
}

void Frame34::seek(long long pos) const {
    if (content)
        return content.seek(pos);
    else {
        if (tagHasContent())
            return tagsContent().seek(pos);
        else
            return FileHolder::seek(pos);
    }
}

void Frame34::shift(long long offset) const {
    if (content)
        return content.shift(offset);
    else {
        if (tagHasContent())
            return tagsContent().shift(offset);
        else
            return FileHolder::shift(offset);
    }
}

bool Frame34::end() const {
    if (content)
        return content.end();
    else {
        if (tagHasContent())
            return tagsContent().end();
        else
            return FileHolder::end();
    }
}

long long Frame34::size() const {
    if (content)
        return content.size();
    else {
        if (tagHasContent())
            return tagsContent().size();
        else
            return FileHolder::size();
    }
}

std::string Frame34::getSymbols(int amount) {
    if (content)
        return content.getSymbols(amount);
    else {
        if (tagHasContent())
            return tagsContent().getSymbols(amount);
        else
            return FileHolder::getSymbols(amount);
    }
}

char Frame34::ch() const {
    if (content)
        return content.ch();
    else {
        if (tagHasContent())
            return tagsContent().ch();
        else
            return FileHolder::ch();
    }
}

uchar Frame34::get() const {
    if (content)
        return content.get();
    else {
        if (tagHasContent())
            return tagsContent().get();
        else
            return FileHolder::get();
    }
}

char Frame34::uch() const {
    if (content)
        return content.ch();
    else {
        if (tagHasContent())
            return tagsContent().ch();
        else
            return FileHolder::uch();
    }
}

uchar Frame34::getb() const {
    if (content)
        return content.get();
    else {
        if (tagHasContent())
            return tagsContent().get();
        else
            return FileHolder::getb();
    }
}

char Frame34::ch(ulong &count) const {
    if (content)
        return content.ch(count);
    else {
        if (tagHasContent())
            return tagsContent().ch(count);
        else
            return FileHolder::ch(count);
    }
}

uchar Frame34::get(ulong &count) const {
    if (content)
        return content.get(count);
    else {
        if (tagHasContent())
            return tagsContent().get(count);
        else
            return FileHolder::get(count);
    }
}

char Frame34::uch(ulong &count) const {
    if (content)
        return content.ch(count);
    else {
        if (tagHasContent())
            return tagsContent().ch(count);
        else
            return FileHolder::uch(count);
    }
}

uchar Frame34::getb(ulong &count) const {
    if (content)
        return content.get(count);
    else {
        if (tagHasContent())
            return tagsContent().get(count);
        else
            return FileHolder::getb(count);
    }
}

void Frame34::checkCompression() {
    if (uncompressedSize > 0) {
        qDebug() << "Frame3,4: doing something with compressed info\n";
        if (tagHasContent()) {
            if (!content.decompressRawData(tagsContent(),length,uncompressedSize))
                qCritical() << "Frame3,4: фрейм не смог достать байты из своего тега\n";
        }
        else {
            if (!content.decompressRawData(file,unsynch,length,uncompressedSize))
                qCritical() << "Frame3,4: фрейм не смог достать байты из файла\n";
        }

        if (content) {
            ulong len_diff = length - content.size();
            endPosition -= len_diff;
            length = content.size();
        }
    }
    else {
        qDebug() << "Frame3,4: no compression\n";
    }
}
