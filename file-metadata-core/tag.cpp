#include "tag.h"

Tag::Tag(Binary &file) :
    FileHolder(file)
{}

Tag::~Tag() = default;
