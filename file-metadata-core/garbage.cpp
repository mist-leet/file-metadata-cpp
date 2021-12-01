/*
для кода, который вроде бы не нужен, но может понадобиться

enum Frames_2 {BUF, CNT, COM, CRA, CRM, ETC, EQU, GEO, IPL, LNK, MCI, MLL, PIC, POP, REV, RVA, SLT, STC, TAL, TBP, TCM, TCO,
               TCR, TDA, TDY, TEN, TFT, TIM, TKE, TLA, TLE, TMT, TOA, TOF, TOL, TOR, TOT, TP1, TP2, TP3, TP4, TPA, TPB, TRC,
               TRD, TRK, TSI, TSS, TT1, TT2, TT3, TXT, TYE, UFI, ULT, WAF, WAR, WAS, WCM, WCP, WPB,
               userdef_txt_2, userdef_url_2, undefined_2};

enum Frames_3 {AENC_3, APIC_3, COMM_3, COMR_3, ENCR_3, EQUA_3, ETCO_3, GEOB_3, GRID_3, IPLS_3, LINK_3, MCDI_3, MLLT_3, OWNE_3,
               PRIV_3, PCNT_3, POPM_3, POSS_3, RBUF_3, RVAD_3, RVRB_3, SYLT_3, SYTC_3, TALB_3, TBPM_3, TCOM_3, TCON_3, TCOP_3,
               TDAT_3, TDLY_3, TENC_3, TEXT_3, TFLT_3, TIME_3, TIT1_3, TIT2_3, TIT3_3, TKEY_3, TLAN_3, TLEN_3, TMED_3, TOAL_3,
               TOFN_3, TOLY_3, TOPE_3, TORY_3, TOWN_3, TPE1_3, TPE2_3, TPE3_3, TPE4_3, TPOS_3, TPUB_3, TRCK_3, TRDA_3, TRSN_3,
               TRSO_3, TSIZ_3, TSRC_3, TSSE_3, TYER_3, UFID_3, USER_3, USLT_3, WCOM_3, WCOP_3, WOAF_3, WOAR_3, WOAS_3, WORS_3,
               WPAY_3, WPUB_3, userdef_url_3, userdef_txt_3, undefined_3};

enum Frames_4 {undefined_4, unknown_frame_4, text_frame_4, url_frame_4, userdef_txt_4, userdef_url_4,
               UFID_4, TIT1_4, TIT2_4, TIT3_4, TALB_4, TOAL_4, TRCK_4, TPOS_4, TSST_4, TSRC_4, TPE1_4, TPE2_4, TPE3_4,
               TPE4_4, TOPE_4, TEXT_4, TOLY_4, TCOM_4, TMCL_4, TIPL_4, TENC_4, TBPM_4, TLEN_4, TKEY_4, TLAN_4, TCON_4,
               TFLT_4, TMED_4, TMOO_4, TCOP_4, TPRO_4, TPUB_4, TOWN_4, TRSN_4, TRSO_4, TOFN_4, TDLY_4, TDEN_4, TDOR_4,
               TDRC_4, TDRL_4, TDTG_4, TSSE_4, TSOA_4, TSOP_4, TSOT_4, WCOM_4, WCOP_4, WOAF_4, WOAR_4, WOAS_4, WORS_4,
               WPAY_4, WPUB_4, MCDI_4, ETCO_4, MLLT_4, SYTC_4, USLT_4, SYLT_4, COMM_4, RVA2_4, EQU2_4, RVRB_4, APIC_4,
               GEOB_4, PCNT_4, POPM_4, AENC_4, LINK_4, USER_4, OWNE_4, COMR_4, ENCR_4, GRID_4, SIGN_4, SEEK_4, ASPI_4};

class binaryfile : public fstream
{
    const li size = get_size();//размер всего файла
public:
    binaryfile(const char * fileway) : fstream(fileway, ios::binary | ios::in | ios::out) {}

    //вставляет строку str с позиции bias
    void insert(const string & str, const long long int & bias);
};

//вставляет строку str с позиции bias
void binaryfile::insert(const string & str, const li & bias)
{
    if (bias <= size)//если не выходит за пределы файла
    {
        const int strsize = str.size();
        if (this->size - bias >= strsize)//если нужно сместить полную строку 1 или более раз
        {
            li pos = this->size, seekpos = 0;
            int len = strsize;
            char * buf_c = new char [strsize + 1];
            bool continue_ = true;
            for (; (pos > bias - strsize) & continue_; pos -= strsize)
            {//идёт с конца, берёт строчку и переносит её на strsize символов вперёд
                seekpos = pos - len;
                if (seekpos < bias)
                {
                    len = pos - bias;
                    pos = bias + strsize;
                    seekpos = bias;
                    continue_ = false;
                }
                seekg(seekpos,ios::beg);
                read(buf_c,len);
                buf_c[len] = '\0';
                seekp(pos,ios::beg);
                cout << "1: going to put '" << buf_c << "' from " << tellg() << " pos\n";
                *this << buf_c;
            }
            seekp(bias,ios::beg);
            cout << "1: going to put '" << str << "' from " << tellg() << " bias = " << bias << '\n';
            *this << str;
            delete[] buf_c;
        }
        else
        {//переносит только одну строчку
            char * buf_c = new char[this->size - bias + 1];
            seekg(bias,ios::beg);
            read(buf_c,size - bias);
            buf_c[size - bias] = '\0';
            seekp(bias,ios::beg);
            *this << str;
            seekp(bias + strsize,ios::beg);
            cout << "2: going to put '" << buf_c << "' from " << tellg() << " pos\n";
            *this << buf_c;
            delete[] buf_c;
        }
    }
}

template<typename T>
class Clever_ptr
{
    T *ptr{nullptr};
    T stock;
    uint size{0};

    bool set_memory(uint s)
    {
        if (ptr == nullptr && s)
        {
            ptr = new(nothrow) T[s];
            if (ptr)
            {
                size = s;
                stock = ptr[0];
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }

public:
    explicit Clever_ptr<T>(uint s) {set_memory(s);}

    explicit Clever_ptr<T>(Clever_ptr<T> & other) {*this = other;}

    Clever_ptr<T>(){}

    bool allocate(uint new_size)
    {
        if (new_size && new_size != size)
        {
            free();
            return set_memory(new_size);
        }
        else
            return true;
    }

    const T * const get_ptr() const {return ptr;}

    uint get_size() const {return size;}

    const T & operator[] (uint pos) const
    {
        if (pos < size && ptr)
            return ptr[pos];
        else
            return stock;
    }

    T & operator[] (uint pos)
    {
        if (pos < size && ptr)
            return ptr[pos];
        else
            return stock;
    }

    T & last()
    {
        if (size && ptr)
            return ptr[size - 1];
        else
            return stock;
    }

    const T & last() const
    {
        if (size && ptr)
            return ptr[size - 1];
        else
            return stock;
    }

    operator bool () const {return ptr;}

    Clever_ptr<T> & operator= (Clever_ptr<T> & other)
    {
        this->ptr = other.ptr;
        this->stock = other.stock;
        this->size = other.size;
        other.discard();
        return *this;
    }

    void discard()//сбрасывает данный Clever_ptr, не освобождая память по указателю
    {
        ptr = nullptr;
        size = 0;
    }

    void free()//освобождает память по указателю
    {
        if (ptr) {delete [] ptr;}
        discard();
    }

    ~Clever_ptr() {free();}
};
*/
