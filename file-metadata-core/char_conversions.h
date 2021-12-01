#pragma once
#include "global_constants.h"

ulong pow2(int);

uchar toUchar(const QBitArray&);
uchar toUchar(char);
uchar toUchar(uchar);//так надо
uchar toUchar(char source, QBitArray &buffer_array);
bool toUchar(const char *sourse, uchar *destination, uint len);

char toChar(uchar);
char toChar(uchar, QBitArray &buffer_array);
bool toChar(const uchar *sourse, char *destination, uint len);

bool valueToBits(char *destination, ulong value);
bool valueToBits(uchar *destination, ulong value);

bool is_255(char);
bool is_255(uchar);

bool notNull(QChar);

ushort cutUlong(ulong);//чекает, не превышает ли код символа 65 535
