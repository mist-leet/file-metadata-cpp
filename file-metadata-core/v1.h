#pragma once
#include "binary.h"
using namespace std;

//класс, от которого будет наследоваться тег v1+; этот же класс обабатывает тег v1, в котором указан номер трека
class Binary::V1
{
protected:
    Binary & MyFile;
public:
    explicit V1(Binary & file) :
        MyFile(file)
    {}

    virtual bool parse();

    virtual ~V1() = default;
};
