
#include <iostream>
#include "bignumber.h"
#include <string>
//#define NDEBUG
#include <cassert>

using namespace std;

int main()
{
    Bignumber a("1001.1"); //TODO -0
    Bignumber b("297.13");
    Bignumber c("-3.5");
   // c = a + "99.99";
   // c.print();
   // a.print();
    //cout << (a == b);
    //cout << ("300.1" > "101.01");  //TODO - lhs, rhs
   /*  for (int i = 0; i < 100; i++)
    {
        c = c * a;
    } */
    c = b * c;
    cout << c.toString() << endl;









    // Asserts
    assert(Bignumber("1").toString() == "1.0");
    assert(Bignumber("1.0").toString() == "1.0");
    assert(Bignumber("-1").toString() == "-1.0");
    assert(Bignumber("0").toString() == "0.0");
    //assert(Bignumber("-0").toString() == "0.0");
    assert(Bignumber("17.25").toString() == "17.25");
    assert(Bignumber("1").toString() == "1.0");
    
    //assert(Bignumber("0").toString() == Bignumber("-0").toString());
    assert((Bignumber("0") + Bignumber("0.0")).toString() == "0.0");
    assert((Bignumber("0.1") + Bignumber("0.0")).toString() == "0.1");
    assert((Bignumber("-3") + Bignumber("7.2")).toString() == "4.2");
    assert((Bignumber("19.99") + Bignumber("99.9")).toString() == "119.89");
    assert((Bignumber("1.0") + Bignumber("-50")).toString() == "-49.0");
    assert((Bignumber("17.24175") + Bignumber("9179.861")).toString() == "9197.10275");











    return 0;
}