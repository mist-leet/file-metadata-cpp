#include "new.h"
using namespace std;

ostream & operator << (ostream & stream, const QBitArray & array)
{
    stream << noboolalpha;
    for (int i = array.size() - 1;i >=0;--i)
        stream << array.testBit(i);
    return stream;
}

long long power(long long num, int pow)
{
    if (pow < 0)
        return 0;
    else
    {
        long long k = 1;
        for (int i = pow;i > 0;--i)
            k *= num;
        return k;
    }
}

ushort cut_ulong(ulong code)
{
    if (code > 65535)//2^16 - 1
        return 65533;//возвращает заменяющий символ если переданный символ нельзя представить 16 битами
    else
        return static_cast<ushort>(code);
}

QByteArray qUncompressWrapper(const QByteArray &raw_data, ulong expected_size)
{
    QByteArray copy(raw_data);
    char expected_size_storage[4];
    value_to_bits(expected_size_storage,expected_size);
    copy.prepend(expected_size_storage,4);
    return qUncompress(copy);
}

QByteArray qUncompressWrapper(QByteArray &&raw_data, ulong expected_size)
{
    char expected_size_storage[4];
    value_to_bits(expected_size_storage,expected_size);
    raw_data.prepend(expected_size_storage,4);
    return qUncompress(raw_data);
}

//https://en.wikipedia.org/wiki/List_of_ID3v1_Genres
QString get_genre(uchar id)
{
    switch (id)
    {
    case 0:return "Blues";
    case 1:return "Classic Rock";
    case 2:return "Country";
    case 3:return "Dance";
    case 4:return "Disco";
    case 5:return "Funk";
    case 6:return "Grunge";
    case 7:return "Hip-Hop";
    case 8:return "Jazz";
    case 9:return "Metal";
    case 10:return "New Age";
    case 11:return "Oldies";
    case 12:return "Unknown";
    case 13:return "Pop";
    case 14:return "Rhythm and Blues";
    case 15:return "Rap";
    case 16:return "Reggae";
    case 17:return "Rock";
    case 18:return "Techno";
    case 19:return "Industrial";
    case 20:return "Alternative";
    case 21:return "Ska";
    case 22:return "Death Metal";
    case 23:return "Pranks";
    case 24:return "Soundtrack";
    case 25:return "Euro-Techno";
    case 26:return "Ambient";
    case 27:return "Trip-Hop";
    case 28:return "Vocal";
    case 29:return "Jazz & Funk";
    case 30:return "Fusion";
    case 31:return "Trance";
    case 32:return "Classical";
    case 33:return "Instrumental";
    case 34:return "Acid";
    case 35:return "House";
    case 36:return "Game";
    case 37:return "Sound clip";
    case 38:return "Gospel";
    case 39:return "Noise";
    case 40:return "Alternative Rock";
    case 41:return "Bass";
    case 42:return "Soul";
    case 43:return "Punk";
    case 44:return "Space";
    case 45:return "Meditative";
    case 46:return "Instrumental Pop";
    case 47:return "Instrumental Rock";
    case 48:return "Ethnic";
    case 49:return "Gothic";
    case 50:return "Darkwave";
    case 51:return "Techno-Industrial";
    case 52:return "Electronic";
    case 53:return "Pop-Folk";
    case 54:return "Eurodance";
    case 55:return "Dream";
    case 56:return "Southern Rock";
    case 57:return "Comedy";
    case 58:return "Cult";
    case 59:return "Gangsta";
    case 60:return "Top 40";
    case 61:return "Christian Rap";
    case 62:return "Pop/Funk";
    case 63:return "Jungle music";
    case 64:return "Native US";
    case 65:return "Cabaret";
    case 66:return "New Wave";
    case 67:return "Psychedelic";
    case 68:return "Rave";
    case 69:return "Showtunes";
    case 70:return "Trailer";
    case 71:return "Lo-Fi";
    case 72:return "Tribal";
    case 73:return "Acid Punk";
    case 74:return "Acid Jazz";
    case 75:return "Polka";
    case 76:return "Retro";
    case 77:return "Musical";
    case 78:return "Rock 'n' Roll";
    case 79:return "Hard Rock";
    case 80:return "Folk";
    case 81:return "Folk-Rock";
    case 82:return "National Folk";
    case 83:return "Swing";
    case 84:return "Fast Fusion";
    case 85:return "Bebop";
    case 86:return "Latin";
    case 87:return "Revival";
    case 88:return "Celtic";
    case 89:return "Bluegrass";
    case 90:return "Avantgarge";
    case 91:return "Gothic Rock";
    case 92:return "Progressive Rock";
    case 93:return "Psychedelic Rock";
    case 94:return "Symphonic Rock";
    case 95:return "Slow Rock";
    case 96:return "Big Band";
    case 97:return "Chorus";
    case 98:return "Easy Listening";
    case 99:return "Acoustic";
    case 100:return "Humour";
    case 101:return "Speech";
    case 102:return "Chanson";
    case 103:return "Opera";
    case 104:return "Chamber music";
    case 105:return "Sonata";
    case 106:return "Symphony";
    case 107:return "Booty Bass";
    case 108:return "Primus";
    case 109:return "Porn Groove";
    case 110:return "Satire";
    case 111:return "Slow Jam";
    case 112:return "Club";
    case 113:return "Tango";
    case 114:return "Samba";
    case 115:return "Folklore";
    case 116:return "Ballad";
    case 117:return "Power Ballad";
    case 118:return "Rhythmic Soul";
    case 119:return "Freestyle";
    case 120:return "Duet";
    case 121:return "Punk Rock";
    case 122:return "Drum Solo";
    case 123:return "A Capella";
    case 124:return "Euro-House";
    case 125:return "Dance Hall";
    case 126:return "Goa music";
    case 127:return "Drum & Bass";
    case 128:return "Club-House";
    case 129:return "Hardcore Techno";
    case 130:return "Terror";
    case 131:return "Indie";
    case 132:return "BritPop";
    case 133:return "Negerpunk";
    case 134:return "Polsk Punk";
    case 135:return "Beat";
    case 136:return "Christian Gangsta Rap";
    case 137:return "Heavy Metal";
    case 138:return "Black Metal";
    case 139:return "Crossover";
    case 140:return "Contemporary christian";
    case 141:return "Christian Rock";
    case 142:return "Merengue";
    case 143:return "Salsa";
    case 144:return "Thrash Metal";
    case 145:return "Anime";
    case 146:return "Jpop";
    case 147:return "Synthpop";
    case 148:return "Abstract";
    case 149:return "Art Rock";
    case 150:return "Baroque";
    case 151:return "Bhangra";
    case 152:return "Big beat";
    case 153:return "Breakbeat";
    case 154:return "Chillout";
    case 155:return "Downtempo";
    case 156:return "Dub";
    case 157:return "EBM";
    case 158:return "Eclectic";
    case 159:return "Electro";
    case 160:return "Electroclash";
    case 161:return "Emo";
    case 162:return "Experimental";
    case 163:return "Garage";
    case 164:return "Global";
    case 165:return "IDM";
    case 166:return "Illbient";
    case 167:return "Industro-Goth";
    case 168:return "Jam Band";
    case 169:return "Krautrock";
    case 170:return "Leftfield";
    case 171:return "Lounge";
    case 172:return "Math Rock";
    case 173:return "New Romantic";
    case 174:return "Nu-Breakz";
    case 175:return "Post-Punk";
    case 176:return "Post-Rock";
    case 177:return "Psytrance";
    case 178:return "Shoegaze";
    case 179:return "Space Rock";
    case 180:return "Trop Rock";
    case 181:return "World music";
    case 182:return "Neoclassical";
    case 183:return "Audiobook";
    case 184:return "Audio Theatre";
    case 185:return "Neue Deutsche Welle";
    case 186:return "Podcast";
    case 187:return "Indie-Rock";
    case 188:return "G-Funk";
    case 189:return "Dubstep";
    case 190:return "Garage Rock";
    case 191:return "Psybient";
    default: return "Unknown";
    }
}
