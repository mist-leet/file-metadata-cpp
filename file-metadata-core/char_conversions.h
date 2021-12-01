#pragma once
#include "new.h"
using namespace std;

uchar toUchar(const QBitArray &);

uchar toUchar(char);

uchar toUchar(char source, QBitArray &buffer_array);

bool toUchar(const char *const sourse, uchar *const destination, uint len);

char toChar(uchar);

char toChar(uchar, QBitArray &buffer_array);

bool toChar(const uchar *const sourse, char *const destination, uint len);

bool valueToBits(char *const destination, ulong value);

bool valueToBits(uchar *const destination, ulong value);

bool is_255(char);
