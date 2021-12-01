#include "tagparser.h"
#include "v1.h"
#include "v22.h"
#include "v23.h"
#include "v24.h"
using std::nothrow;

TagParser::TagParser(Binary &file)
    : tag(new(nothrow) Binary::V1(file))
{
    qDebug() << "TagParser: set V1\n";
}

TagParser::TagParser(TagVersion version, Binary &file) {
    switch (version) {
    case two:{
        qDebug() << "TagParser: set v2" << endl;
        tag = new(nothrow) Binary::V22(file);
        return;
    }
    case three:{
        qDebug() << "TagParser: set v3" << endl;
        tag = new(nothrow) Binary::V23(file);
        return;
    }
    case four:{
        qDebug() << "TagParser: set v4" << endl;
        tag = new(nothrow) Binary::V24(file);
        return;
    }
    case noTag:{
        qDebug() << "TagParser: got noTag, nothing is set" << endl;
        return;
    }
    }
}

ParsingResult TagParser::parse() const {
    if (tag) {
        qDebug() << "TagParser: starting parsing" << endl;
        bool fine = tag->parse();
        qDebug() << "TagParser: ended parsing" << endl;
        if (fine)
            return success;
        else
            return fail;
    }
    else {
        qDebug() << "TagParser: failed to parse because tag is nullptr\n";
        return noId;
    }
}

TagParser::~TagParser() {
    qDebug() << "TagParser: dying\n";
    delete tag;
}
