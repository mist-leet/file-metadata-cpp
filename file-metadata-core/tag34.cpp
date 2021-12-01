#include "tag34.h"

Tag34::Tag34(Binary &f)
    : Tag(f)
{}

Tag34::~Tag34() = default;

std::string Tag34::getFrameId() {
    if (content)
        return content.getFrame34Id();
    else
        return FileHolder::getSymbols(4);
}

long long Tag34::pos() const {
    if (content)
        return content.pos();
    else
        return FileHolder::pos();
}

void Tag34::shift(long long offset) const {
    if (content)
        content.shift(offset);
    else
        FileHolder::shift(offset);
}

bool Tag34::parseData() {
    if (!experimentalTag) {
        if (expectedCrc.second)
            if (!handleCrc())
                return skip();

        actualParse();
    }
    return skip();
}

bool Tag34::correctId(const char *const id) {
    for (int i = 0;i < 4;++i)
        if (!correctChar(id[i]))
            return false;
    return !id[4];
}

bool Tag34::isUserdefUrl(const char *const id) {
    return (id[0] == 'W' && Tag34::correctId(id) && strcmp(id, "WCOM") && strcmp(id, "WCOP") && strcmp(id, "WOAF") &&
        strcmp(id, "WOAR") && strcmp(id, "WOAS") && strcmp(id, "WORS") && strcmp(id, "WPAY") && strcmp(id, "WPUB"));
}

bool Tag34::isFreeFrame(const char *const id) {
    return (id[0] == 'X' || id[0] == 'Y' || id[0] == 'Z') && Tag34::correctId(id);
}

bool Tag34::hasPreextractedData() const {
    return content;
}

FileContents & Tag34::getContent() {
    return content;
}
