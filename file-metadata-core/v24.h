#pragma once
#include "v23.h"
using namespace std;

//тег v2.4
class Binary::V24 : public Binary::V23
{
protected:
    bool footer_precense;
    bool tag_is_an_update;
    Restrictions restrictions;

private:
    V24 (const V24 & ) = delete ;
    V24 & operator = (const V24 &) = delete;

    class Frame4;
    class UFID_4;
    class TIT1_4;
    class TIT2_4;
    class TIT3_4;
    class TALB_4;
    class TOAL_4;
    class TRCK_4;
    class TPOS_4;
    class TSST_4;
    class TSRC_4;
    class TPE1_4;
    class TPE2_4;
    class TPE3_4;
    class TPE4_4;
    class TOPE_4;
    class TEXT_4;
    class TOLY_4;
    class TCOM_4;
    class TMCL_4;
    class TIPL_4;
    class TENC_4;
    class TBPM_4;
    class TLEN_4;
    class TKEY_4;
    class TLAN_4;
    class TCON_4;
    class TFLT_4;
    class TMED_4;
    class TMOO_4;
    class TCOP_4;
    class TPRO_4;
    class TPUB_4;
    class TOWN_4;
    class TRSN_4;
    class TRSO_4;
    class TOFN_4;
    class TDLY_4;
    class TDEN_4;
    class TDOR_4;
    class TDRC_4;
    class TDRL_4;
    class TDTG_4;
    class TSSE_4;
    class TSOA_4;
    class TSOP_4;
    class TSOT_4;
    class WCOM_4;
    class WCOP_4;
    class WOAF_4;
    class WOAR_4;
    class WOAS_4;
    class WORS_4;
    class WPAY_4;
    class WPUB_4;
    class MCDI_4;
    class ETCO_4;
    class MLLT_4;
    class SYTC_4;
    class USLT_4;
    class SYLT_4;
    class COMM_4;
    class RVA2_4;
    class EQU2_4;
    class RVRB_4;
    class APIC_4;
    class GEOB_4;
    class PCNT_4;
    class POPM_4;
    //class RBUF_4;//поскольку этот фрейм используется при стриминге файла, его можно не парсить
    class AENC_4;
    class LINK_4;
    class POSS_4;
    class USER_4;
    class OWNE_4;
    class COMR_4;
    class ENCR_4;
    class GRID_4;
    //class PRIV_4;//фрейм с приватной информацией, суть которой понятна только создателю этого фрейма
    class SIGN_4;
    class SEEK_4;
    class ASPI_4;
    //class XYZ_4;//фреймы для частного пользования, предназначение которых неспецифицировано
    class unknown_frame;

    //Мб это безумно тупо, но по стандарту это должно быть написано
    friend class Frame4;
    friend class UFID_4;
    friend class TIT1_4;
    friend class TIT2_4;
    friend class TIT3_4;
    friend class TALB_4;
    friend class TOAL_4;
    friend class TRCK_4;
    friend class TPOS_4;
    friend class TSST_4;
    friend class TSRC_4;
    friend class TPE1_4;
    friend class TPE2_4;
    friend class TPE3_4;
    friend class TPE4_4;
    friend class TOPE_4;
    friend class TEXT_4;
    friend class TOLY_4;
    friend class TCOM_4;
    friend class TMCL_4;
    friend class TIPL_4;
    friend class TENC_4;
    friend class TBPM_4;
    friend class TLEN_4;
    friend class TKEY_4;
    friend class TLAN_4;
    friend class TCON_4;
    friend class TFLT_4;
    friend class TMED_4;
    friend class TMOO_4;
    friend class TCOP_4;
    friend class TPRO_4;
    friend class TPUB_4;
    friend class TOWN_4;
    friend class TRSN_4;
    friend class TRSO_4;
    friend class TOFN_4;
    friend class TDLY_4;
    friend class TDEN_4;
    friend class TDOR_4;
    friend class TDRC_4;
    friend class TDRL_4;
    friend class TDTG_4;
    friend class TSSE_4;
    friend class TSOA_4;
    friend class TSOP_4;
    friend class TSOT_4;
    friend class WCOM_4;
    friend class WCOP_4;
    friend class WOAF_4;
    friend class WOAR_4;
    friend class WOAS_4;
    friend class WORS_4;
    friend class WPAY_4;
    friend class WPUB_4;
    friend class MCDI_4;
    friend class ETCO_4;
    friend class MLLT_4;
    friend class SYTC_4;
    friend class USLT_4;
    friend class SYLT_4;
    friend class COMM_4;
    friend class RVA2_4;
    friend class EQU2_4;
    friend class RVRB_4;
    friend class APIC_4;
    friend class GEOB_4;
    friend class PCNT_4;
    friend class POPM_4;
    //friend class RBUF_4;
    friend class AENC_4;
    friend class LINK_4;
    friend class POSS_4;
    friend class USER_4;
    friend class OWNE_4;
    friend class COMR_4;
    friend class ENCR_4;
    friend class GRID_4;
    //friend class PRIV_4;
    friend class SIGN_4;
    friend class SEEK_4;
    friend class ASPI_4;
    //friend class XYZ_4;
    friend class unknown_frame;

protected:
    virtual bool parse_extended_header() override;

    virtual bool parse_header() override;

    bool set_crc();

    bool set_restrictions();

public:
    explicit V24(Binary & file) :
        V23(file),
        footer_precense(false),
        tag_is_an_update(false),
        restrictions(Restrictions())
    {}

    virtual bool parse() override;

    virtual ~V24() override = default;
};
