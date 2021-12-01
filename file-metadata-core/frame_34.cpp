#include "frame_34.h"
using namespace std;

Frame34::Frame34(Tag &t)
    : Frame(t)
    , frameStatus()
    , frameFormat()
{}

Frame34::~Frame34() = default;

bool Frame34::parse()//переделать
{
    if (parseHeader())
    {
        if (frameFormat.encryption)
            return skip();
        else
        {
            checkCompression();
            return parseData();
        }
    }
    else
        return !skip();
}

FrameFormat & Frame34::getFormat()
{
    return frameFormat;
}

FrameStatus & Frame34::getStatus()
{
    return frameStatus;
}

const FrameFormat & Frame34::getFormat() const
{
    return frameFormat;
}

const FrameStatus & Frame34::getStatus() const
{
    return frameStatus;
}

ByteOrder Frame34::getBOM() const
{
    if (content)
        return content.getBOM();
    else
    {
        if (tagHasContent())
            return tagsContent().getBOM();
        else
            return FileHolder::getBOM();
    }
}

QString Frame34::getIso8859Str() const
{
    if (content)
        return content.getIso8859Str();
    else
    {
        if (tagHasContent())
            return tagsContent().getIso8859Str();
        else
            return FileHolder::getIso8859Str();
    }
}

QString Frame34::getIso8859Str(const long long &dur) const
{
    if (content)
        return content.getIso8859Str(dur);
    else
    {
        if (tagHasContent())
            return tagsContent().getIso8859Str(dur);
        else
            return FileHolder::getIso8859Str(dur);
    }
}

QString Frame34::getUtf16Str(ByteOrder bo) const//не чекает BOM
{
    if (content)
        return content.getUtf16Str(bo);
    else
    {
        if (tagHasContent())
            return tagsContent().getUtf16Str(bo);
        else
            return FileHolder::getUtf16Str(bo);
    }
}

QString Frame34::getUtf16Str(ByteOrder bo, const long long &dur) const//не чекает BOM
{
    if (content)
        return content.getUtf16Str(bo, dur);
    else
    {
        if (tagHasContent())
            return tagsContent().getUtf16Str(bo, dur);
        else
            return FileHolder::getUtf16Str(bo, dur);
    }
}

QString Frame34::getUtf8Str() const
{
    if (content)
        return content.getUtf8Str();
    else
    {
        if (tagHasContent())
            return tagsContent().getUtf8Str();
        else
            return FileHolder::getUtf8Str();
    }
}

QString Frame34::getUtf8Str(const long long &dur) const
{
    if (content)
        return content.getUtf8Str(dur);
    else
    {
        if (tagHasContent())
            return tagsContent().getUtf8Str(dur);
        else
            return FileHolder::getUtf8Str(dur);
    }
}

QString Frame34::getUcs2Str(ByteOrder bo) const//не чекает BOM
{
    if (content)
        return content.getUcs2Str(bo);
    else
    {
        if (tagHasContent())
            return tagsContent().getUcs2Str(bo);
        else
            return FileHolder::getUcs2Str(bo);
    }
}

QString Frame34::getUcs2Str(ByteOrder bo, const long long &dur) const//не чекает BOM
{
    if (content)
        return content.getUcs2Str(bo, dur);
    else
    {
        if (tagHasContent())
            return tagsContent().getUcs2Str(bo, dur);
        else
            return FileHolder::getUcs2Str(bo, dur);
    }
}

QString Frame34::getEncodingDependentString() const
{
    if (content)
        return getEncodingDependentString(content);
    else
    {
        if (tagHasContent())
            return getEncodingDependentString(tagsContent());
        else
            return getEncodingDependentString(true);
    }
}

QString Frame34::getEncodingDependentString(const long long &dur) const
{
    if (content)
        return getEncodingDependentString(content, dur);
    else
    {
        if (tagHasContent())
            return getEncodingDependentString(tagsContent(), dur);
        else
            return getEncodingDependentString(true, dur);
    }
}

QByteArray Frame34::getBinaryTillEnd() const
{
    if (content)
        return content.getBinaryTillEnd();
    else
    {
        if (tagHasContent())
            return tagsContent().getBinaryTillEnd();
        else
            return FileHolder::getBinaryTillEnd();
    }
}

bool Frame34::skip() const
{
    if (content)
        return content.skip();
    else
    {
        if (tagHasContent())
        {
            tagsContent().seek(endPosition);
            return true;
        }
        else
            return FileHolder::skip();
    }
}

long long Frame34::pos() const
{
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

void Frame34::seek(long long pos) const
{
    if (content)
        return content.seek(pos);
    else
    {
        if (tagHasContent())
            return tagsContent().seek(pos);
        else
            return FileHolder::seek(pos);
    }
}

void Frame34::shift(long long offset) const
{
    if (content)
        return content.shift(offset);
    else
    {
        if (tagHasContent())
            return tagsContent().shift(offset);
        else
            return FileHolder::shift(offset);
    }
}

bool Frame34::end() const
{
    if (content)
        return content.end();
    else
    {
        if (tagHasContent())
            return tagsContent().end();
        else
            return FileHolder::end();
    }
}

long long Frame34::size() const
{
    if (content)
        return content.size();
    else
    {
        if (tagHasContent())
            return tagsContent().size();
        else
            return FileHolder::size();
    }
}

string Frame34::getSymbols(int amount)
{
    if (content)
        return content.getSymbols(amount);
    else
    {
        if (tagHasContent())
            return tagsContent().getSymbols(amount);
        else
            return FileHolder::getSymbols(amount);
    }
}

char Frame34::ch() const
{
    if (content)
        return content.ch();
    else
    {
        if (tagHasContent())
            return tagsContent().ch();
        else
            return FileHolder::ch();
    }
}

uchar Frame34::get() const
{
    if (content)
        return content.get();
    else
    {
        if (tagHasContent())
            return tagsContent().get();
        else
            return FileHolder::get();
    }
}

char Frame34::uch() const
{
    if (content)
        return content.ch();
    else
    {
        if (tagHasContent())
            return tagsContent().ch();
        else
            return FileHolder::uch();
    }
}

uchar Frame34::getb() const
{
    if (content)
        return content.get();
    else
    {
        if (tagHasContent())
            return tagsContent().get();
        else
            return FileHolder::getb();
    }
}

char Frame34::ch(int &count) const
{
    if (content)
        return content.ch(count);
    else
    {
        if (tagHasContent())
            return tagsContent().ch(count);
        else
            return FileHolder::ch(count);
    }
}

uchar Frame34::get(int &count) const
{
    if (content)
        return content.get(count);
    else
    {
        if (tagHasContent())
            return tagsContent().get(count);
        else
            return FileHolder::get(count);
    }
}

char Frame34::uch(int &count) const
{
    if (content)
        return content.ch(count);
    else
    {
        if (tagHasContent())
            return tagsContent().ch(count);
        else
            return FileHolder::uch(count);
    }
}

uchar Frame34::getb(int &count) const
{
    if (content)
        return content.get(count);
    else
    {
        if (tagHasContent())
            return tagsContent().get(count);
        else
            return FileHolder::getb(count);
    }
}

void Frame34::checkCompression()//вызывается, когда хедер уже пропаршен
{
    if (frameFormat.compressionInfo.second)//если фрейм сжат
    {
        if (tagHasContent())
        {
            if (!content.decompressRawData(tagsContent(),length,frameFormat.compressionInfo.first))
                qCritical() << "фрейм не смог достать байты из хранилища тега\n";
        }
        else
        {
            if (!content.decompressRawData(file,unsynch,length,frameFormat.compressionInfo.first))
                qCritical() << "фрейм не смог достать байты из файла\n";
        }

        if (content)
        {
            ulong len_diff = length - content.size();
            endPosition -= len_diff;
            length = content.size();
        }
    }
}
