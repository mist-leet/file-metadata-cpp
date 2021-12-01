#pragma once
#include "pch.h"
#define PRESET_PATH
//#define NO_V1_PARSING
#define EXTRANEOUS_CODE

template <typename T>
extern constexpr bool anyChar = std::is_same<T, char>::value || std::is_same<T, uchar>::value;

template <typename T>
extern constexpr bool anyInt = std::is_same<T, qint16>::value || std::is_same<T, qint32>::value || std::is_same<T, qint64>::value ||
    std::is_same<T, quint16>::value || std::is_same<T, quint32>::value || std::is_same<T, quint64>::value ||
    std::is_same<T, long>::value || std::is_same<T, ulong>::value;

template <typename T>
extern constexpr bool isChar = std::is_same<T, char>::value;

extern constexpr QChar nullqc{QChar(char(0))};
extern constexpr char end = '\n';

extern constexpr int v1Len = 128;
extern constexpr int headerLen = 10;

enum ByteOrder {littleEndian, bigEndian, none};

enum StringEncoding {iso_8859_1, ucs_2be, ucs_2le, utf_16be, utf_16le, utf_8, notGiven};

enum ParsingResult {success, fail, noId};

enum TagVersion {two, three, four, noTag};

typedef std::bitset<8> mByte;
