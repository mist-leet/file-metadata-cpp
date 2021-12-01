#include "debugfile.h"

#ifndef NO_DEBUG_FILE
namespace {
QByteArray date() {
    QString s;
    constexpr int sideLen = 37;

    for (uint i = 0;i < sideLen;++i) {
        s.append('-');
    }
    s += QDateTime::currentDateTime().toString(Qt::SystemLocaleShortDate) + ':' + QTime::currentTime().toString("ss");
    for (uint i = 0;i < sideLen;++i) {
        s += '-';
    }
    s += '\n';
    return s.toLatin1();
}

QByteArray endMessage() {
    QString s;
    constexpr uint halfLineLen = 43;

    s += '\n';
    for (uint i = 0;i < halfLineLen;++i) {
        s += '-';
    }
    s += "THE END";
    for (uint i = 0;i < halfLineLen;++i) {
        s += '-';
    }
    s += "\n\n\n\n";
    return s.toLatin1();
}
} //anonimous namespace
#endif //NO_DEBUG_FILE

df::df()
{
#ifndef NO_DEBUG_FILE

    QIODevice::OpenMode mode;
#ifdef CLEAR_DEBUG_FILE
    mode = QIODevice::Truncate | QIODevice::ReadWrite | QIODevice::Text;
#else
    mode = QIODevice::Append | QIODevice::Text;
#endif //CLEAR_DEBUG_FILE

    f.open(mode);
    s.setDevice(&f);
    s << date();

#endif //NO_DEBUG_FILE
}

df::~df() {
#ifndef NO_DEBUG_FILE
    s << endMessage();
    f.close();
#endif //NO_DEBUG_FILE
}

df &df::save() {
    static df s;
    return s;
}
