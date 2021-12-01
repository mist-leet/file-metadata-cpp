#include "binary.h"
using namespace std;

int main(int argc, char *argv[])
{
    Binary b("D:/abcd.txt");
    if (b.parse())
    {
        //parsing was successfull
    }
    else
    {
        //parsing failed for some reason
    }
    cout << "end of code\n";
    return 0;
}
