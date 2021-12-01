#pragma once
#include "tag.h"
#include "file_contents.h"
using namespace std;

class Tag34 : public Tag
{
protected:
    bool experimental_tag{false};
    bool footer_presence{false};
    bool update{false};
    mutable File_contents content{};//mutable - костыль, чтобы можно было переопределять const virtual функции
    ulong size_of_extended_header{0};
    pair<ulong, bool> expected_crc{make_pair(0,false)};
    Encryption_method_markers encryption_info;
    Group_markers grouping_info;

private:
    Tag34(const Tag34 &) = delete;
    Tag34 & operator = (const Tag34 &) = delete;

protected:
    virtual bool parse_extended_header() = 0;

    virtual string get_frame_id() override final;

    virtual long long pos() const override final;

    virtual void shift(long long) const override final;

public:
    explicit Tag34(Binary & f);

    Encryption_method_markers & encr_info();

    Group_markers & group_info();

    static bool is_userdef_url(const char * const);

    static bool correct_id(const char * const);

    static bool is_free_frame(const char * const);

    bool has_preextracted_data() const;

    File_contents & get_content();

    virtual ~Tag34() override;
};
