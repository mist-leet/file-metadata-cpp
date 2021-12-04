#include "global_functions.h"
using std::vector;

long long Gl::power(long long num, int pow) {
    if (pow < 0)
        return 0;
    else {
        long long k = 1;
        for (int i = pow;i > 0;--i)
            k *= num;
        return k;
    }
}

bool Gl::isNull(const char *const ptr) {
    for (int i = 0;i < 5;++i)
        if (ptr[i])
            return false;
    return true;
}

uint Gl::toUint(const QString &s) {
    uint a = 0;
    for (int i = s.length() - 1;i >= 0;--i)
        if (s[i].isDigit())
            a += s[i].unicode()*power(10,i);
    return a;
}

vector<uchar> Gl::uncompressWrapper(const vector<uchar> &rawData, ulong expectedSize) {
    std::unique_ptr<uchar []> uncompressedData(new(std::nothrow) uchar[expectedSize]);
    if (uncompressedData.get()) {
        if (uncompress(uncompressedData.get(),&expectedSize,rawData.data(),rawData.size()) == Z_OK) {
            vector<uchar> v{};
            v.reserve(expectedSize);
            for (ulong i = 0;i < expectedSize;++i) {
                v.push_back(uncompressedData[i]);
            }
            return v;
        }
    }
    return vector<uchar>{};
}

ulong Gl::mbyte(ulong k) {
    return k*1024*1024;
}

ulong Gl::kbyte(ulong k) {
    return k*1024;
}
