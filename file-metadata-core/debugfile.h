#pragma once
#include "global_constants.h"

template<typename T>
constexpr bool debugInfo =  std::is_same<T, QChar>::value || std::is_same<T, char>::value || std::is_same<T, short>::value ||
                            std::is_same<T, ushort>::value || std::is_same<T, int>::value || std::is_same<T, uint>::value ||
                            std::is_same<T, long>::value || std::is_same<T, ulong>::value || std::is_same<T, qlonglong>::value ||
                            std::is_same<T, qulonglong>::value || std::is_same<T, float>::value || std::is_same<T, double>::value ||
                            std::is_same<T, const QString &>::value || std::is_same<T, const QByteArray &>::value ||
                            std::is_same<T, const char *>::value || std::is_same<T, QTextStream &(*)(QTextStream &)>::value;

class df //синглтон Майерса
{
#ifndef NO_DEBUG_FILE
    QTextStream s{};
    QFile f{"D:/debug/file-metadata.txt"};
#endif

    df();
    ~df();

    df(const df &) = delete;
    df &operator=(const df &) = delete;

public:
    template<typename T, class = std::enable_if_t<debugInfo<T>>>
    df &operator<<(T);

    static df &save();
};

template<typename T, class >
df &df::operator<<(T t) {
#ifndef NO_DEBUG_FILE
    s << t;
#else
    Q_UNUSED(t);
#endif
    return *this;
}
