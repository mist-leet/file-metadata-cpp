#pragma once
#include "new.h"
using namespace std;

//неплохо бы потестить всё это
uchar to_uchar(const QBitArray &);

uchar to_uchar(char);

uchar to_uchar(char source, QBitArray &buffer_array);

bool to_uchar(const char *const sourse, uchar *const destination, uint len);

char to_char(uchar);

char to_char(uchar, QBitArray &buffer_array);

bool to_char(const uchar *const sourse, char *const destination, uint len);

bool value_to_bits(char *const destination, ulong value);

bool value_to_bits(uchar *const destination, ulong value);

bool is_255(char);
