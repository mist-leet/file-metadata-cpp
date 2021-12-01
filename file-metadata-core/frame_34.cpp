#include "frame_34.h"
using namespace std;

Frame34::Frame34(Tag &t)
    : Frame(t)
    , frame_status()
    , frame_format()
{}

Frame34::~Frame34() = default;

bool Frame34::parse()//переделать
{
    if (parse_header())
    {
        if (frame_format.encryption)
            return skip();
        else
        {
            check_compression();
            return parse_data();
        }
    }
    else
        return !skip();
}

Frame_format & Frame34::get_format()
{
    return frame_format;
}

Frame_status & Frame34::get_status()
{
    return frame_status;
}

const Frame_format & Frame34::get_format() const
{
    return frame_format;
}

const Frame_status & Frame34::get_status() const
{
    return frame_status;
}

Byte_order Frame34::get_BOM() const
{
    if (content)
        return content.get_BOM();
    else
    {
        if (tag_has_content())
            return tags_content().get_BOM();
        else
            return File_holder::get_BOM();
    }
}

QString Frame34::get_iso8859_str() const
{
    if (content)
        return content.get_iso8859_str();
    else
    {
        if (tag_has_content())
            return tags_content().get_iso8859_str();
        else
            return File_holder::get_iso8859_str();
    }
}

QString Frame34::get_iso8859_str(const long long & dur) const
{
    if (content)
        return content.get_iso8859_str(dur);
    else
    {
        if (tag_has_content())
            return tags_content().get_iso8859_str(dur);
        else
            return File_holder::get_iso8859_str(dur);
    }
}

QString Frame34::get_utf16_str(Byte_order bo) const//не чекает BOM
{
    if (content)
        return content.get_utf16_str(bo);
    else
    {
        if (tag_has_content())
            return tags_content().get_utf16_str(bo);
        else
            return File_holder::get_utf16_str(bo);
    }
}

QString Frame34::get_utf16_str(Byte_order bo, const long long & dur) const//не чекает BOM
{
    if (content)
        return content.get_utf16_str(bo, dur);
    else
    {
        if (tag_has_content())
            return tags_content().get_utf16_str(bo, dur);
        else
            return File_holder::get_utf16_str(bo, dur);
    }
}

QString Frame34::get_utf8_str() const
{
    if (content)
        return content.get_utf8_str();
    else
    {
        if (tag_has_content())
            return tags_content().get_utf8_str();
        else
            return File_holder::get_utf8_str();
    }
}

QString Frame34::get_utf8_str(const long long & dur) const
{
    if (content)
        return content.get_utf8_str(dur);
    else
    {
        if (tag_has_content())
            return tags_content().get_utf8_str(dur);
        else
            return File_holder::get_utf8_str(dur);
    }
}

QString Frame34::get_ucs2_str(Byte_order bo) const//не чекает BOM
{
    if (content)
        return content.get_ucs2_str(bo);
    else
    {
        if (tag_has_content())
            return tags_content().get_ucs2_str(bo);
        else
            return File_holder::get_ucs2_str(bo);
    }
}

QString Frame34::get_ucs2_str(Byte_order bo, const long long & dur) const//не чекает BOM
{
    if (content)
        return content.get_ucs2_str(bo, dur);
    else
    {
        if (tag_has_content())
            return tags_content().get_ucs2_str(bo, dur);
        else
            return File_holder::get_ucs2_str(bo, dur);
    }
}

QString Frame34::get_encoding_dependent_string(String_encoding enc) const
{
    if (content)
        return content.get_encoding_dependent_string(enc, [this]()
                                                            {
                                                                return  this->content.skip();
                                                            });
    else
    {
        if (tag_has_content())
            return tags_content().get_encoding_dependent_string(enc, [this]()
                                                                        {
                                                                            return  this->content.skip();
                                                                        });
        else
            return File_holder::get_encoding_dependent_string(enc);
    }
}

QString Frame34::get_encoding_dependent_string(String_encoding enc, const long long & dur) const
{
    if (content)
        return content.get_encoding_dependent_string(enc, dur, [this]()
                                                                {
                                                                    return  this->content.skip();
                                                                });
    else
    {
        if (tag_has_content())
            return tags_content().get_encoding_dependent_string(enc, dur, [this]()
                                                                            {
                                                                                return  this->content.skip();
                                                                            });
        else
            return File_holder::get_encoding_dependent_string(enc, dur);
    }
}

QByteArray Frame34::get_binary_till_end() const
{
    if (content)
        return content.get_binary_till_end();
    else
    {
        if (tag_has_content())
            return tags_content().get_binary_till_end();
        else
            return File_holder::get_binary_till_end();
    }
}

bool Frame34::skip() const
{
    if (content)
        return content.skip();
    else
    {
        if (tag_has_content())
            return tags_content().skip();
        else
            return File_holder::skip();
    }
}

long long Frame34::pos() const
{
    if (content)
        return content.pos();
    else
    {
        if (tag_has_content())
            return tags_content().pos();
        else
            return File_holder::pos();
    }
}

void Frame34::seek(long long pos) const
{
    if (content)
        return content.seek(pos);
    else
    {
        if (tag_has_content())
            return tags_content().seek(pos);
        else
            return File_holder::seek(pos);
    }
}

void Frame34::shift(long long offset) const
{
    if (content)
        return content.shift(offset);
    else
    {
        if (tag_has_content())
            return tags_content().shift(offset);
        else
            return File_holder::shift(offset);
    }
}

bool Frame34::end() const
{
    if (content)
        return content.end();
    else
    {
        if (tag_has_content())
            return tags_content().end();
        else
            return File_holder::end();
    }
}

long long Frame34::size() const
{
    if (content)
        return content.size();
    else
    {
        if (tag_has_content())
            return tags_content().size();
        else
            return File_holder::size();
    }
}

string Frame34::get_symbols(int amount)
{
    if (content)
        return content.get_symbols(amount);
    else
    {
        if (tag_has_content())
            return tags_content().get_symbols(amount);
        else
            return File_holder::get_symbols(amount);
    }
}

char Frame34::ch() const
{
    if (content)
        return content.ch();
    else
    {
        if (tag_has_content())
            return tags_content().ch();
        else
            return File_holder::ch();
    }
}

uchar Frame34::get() const
{
    if (content)
        return content.get();
    else
    {
        if (tag_has_content())
            return tags_content().get();
        else
            return File_holder::get();
    }
}

char Frame34::uch() const
{
    if (content)
        return content.ch();
    else
    {
        if (tag_has_content())
            return tags_content().ch();
        else
            return File_holder::uch();
    }
}

uchar Frame34::getb() const
{
    if (content)
        return content.get();
    else
    {
        if (tag_has_content())
            return tags_content().get();
        else
            return File_holder::getb();
    }
}

char Frame34::ch(int &count) const
{
    if (content)
        return content.ch(count);
    else
    {
        if (tag_has_content())
            return tags_content().ch(count);
        else
            return File_holder::ch(count);
    }
}

uchar Frame34::get(int &count) const
{
    if (content)
        return content.get(count);
    else
    {
        if (tag_has_content())
            return tags_content().get(count);
        else
            return File_holder::get(count);
    }
}

char Frame34::uch(int &count) const
{
    if (content)
        return content.ch(count);
    else
    {
        if (tag_has_content())
            return tags_content().ch(count);
        else
            return File_holder::uch(count);
    }
}

uchar Frame34::getb(int &count) const
{
    if (content)
        return content.get(count);
    else
    {
        if (tag_has_content())
            return tags_content().get(count);
        else
            return File_holder::getb(count);
    }
}

void Frame34::check_compression()//вызывается, когда хедер уже пропаршен
{
    if (frame_format.compression_info.second)//если фрейм сжат
    {
        if (tag_has_content())
        {
            if (!content.decompress_raw_data(tags_content(),length,frame_format.compression_info.first))
                qCritical() << "фрейм не смог достать байты из хранилища тега\n";
        }
        else
        {
            if (!content.decompress_raw_data(file,unsynch,length,frame_format.compression_info.first))
                qCritical() << "фрейм не смог достать байты из файла\n";
        }

        if (content)
        {
            ulong len_diff = length - content.size();
            end_position -= len_diff;
            length = content.size();
        }
    }
}
