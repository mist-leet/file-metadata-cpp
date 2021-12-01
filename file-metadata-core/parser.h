#pragma once
#include "v1.h"

#include "v22.h"
#include "frames2.h"

#include "v23.h"
#include "frames3.h"

#include "v24.h"
#include "frames4GCLO.h"
#include "frames4RP.h"
#include "frames4SA.h"
#include "frames4text.h"
#include "frames4UEM.h"
#include "frames4unknown.h"
#include "frames4url.h"

using namespace std;

class Parser
{
    Parser & operator = (const Parser &) = delete;//З а П р Е щ Е н О_о
    Parser(const Parser &) = delete;//З А П Р Е Щ Е Н О
    Parser(Parser &&) = delete;//zapresheno
    Parser() = delete;//restricted

protected:
    FileHolder *subject{nullptr};

    void setFrame(const char *const, Binary::V22 &);//frame v2.2

    void setFrame(const char *const, Binary::V23 &);//frame v2.3

    void setFrame(const char *const, Binary::V24 &);//frame v2.4

public:
    Parser(Binary &);//V1

    Parser(TagVersion, Binary &);//V2*

    Parser(const char *const, Binary::V22 &);//frame 2

    Parser(const char *const, Binary::V23 &);//frame 3

    Parser(const char *const, Binary::V24 &);//frame 4

    ParsingResult parse() const;

    ~Parser();
};
