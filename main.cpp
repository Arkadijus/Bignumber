
#include <iostream>
#include "bignumber.h"

using namespace std;

int main()
{
    Bignumber a("0.000010000000"); //TODO -0
    Bignumber b(a);
    a.print();

    return 0;
}