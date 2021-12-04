#pragma once
#include "global_constants.h"

namespace Gl {
long long power(long long, int);

ulong kbyte(ulong k = 1);
ulong mbyte(ulong k = 1);

QString getGenre(uchar);

std::vector<uchar> uncompressWrapper(const std::vector<uchar> &, ulong);

bool isNull(const char *const);

uint toUint(const QString &);
} //namespace Gl
