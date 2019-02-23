
#include <iostream>
#include "bignumber.h"
#include <string>
//#define NDEBUG
#include <cassert>

using namespace std;

int main()   
{
    Bignumber a("871.241"); //TODO -0
    Bignumber b("4.0");
    Bignumber c("871.241");
   // c = a + "99.99";
   // c.print();
   // a.print();
    //cout << (a == b);
    //cout << ("300.1" > "101.01");  //TODO - lhs, rhs
     /* for (int i = 0; i < 38; i++)
    {
        c = c * a;
    } */ 
    //c = b * c;
    //cout << c.toString() << endl; // 552.
    b = a / c;
    b.print();











    //Asserts--------------------------------------

    //constructor
    assert(Bignumber("1").toString() == "1.0");
    assert(Bignumber("1.0").toString() == "1.0");
    assert(Bignumber("-1").toString() == "-1.0");
    assert(Bignumber("0").toString() == "0.0");
    //assert(Bignumber("-0").toString() == "0.0");
    assert(Bignumber("17.25").toString() == "17.25");
    assert(Bignumber("1").toString() == "1.0");
    
    //assert(Bignumber("0").toString() == Bignumber("-0").toString());
    //operator+
    assert((Bignumber("0") + Bignumber("0.0")).toString() == "0.0");
    assert((Bignumber("0.1") + Bignumber("0.0")).toString() == "0.1");
    assert((Bignumber("-3") + Bignumber("7.2")).toString() == "4.2");
    assert((Bignumber("-3") + Bignumber("-7.2")).toString() == "-10.2");
    assert((Bignumber("19.99") + Bignumber("99.9")).toString() == "119.89");
    assert((Bignumber("1.0") + Bignumber("-50")).toString() == "-49.0");
    assert((Bignumber("17.24175") + Bignumber("9179.861")).toString() == "9197.10275");
    assert((Bignumber("21.55") + Bignumber("80.45")).toString() == "102.0");

    //operator-
    assert((Bignumber("0") - Bignumber("0.0")).toString() == "0.0");
    assert((Bignumber("0.1") - Bignumber("0.0")).toString() == "0.1");
    assert((Bignumber("-3") - Bignumber("7.2")).toString() == "-10.2");
    assert((Bignumber("-3") - Bignumber("-7.2")).toString() == "4.2");
    assert((Bignumber("19.99") - Bignumber("99.9")).toString() == "-79.91");
    assert((Bignumber("1.0") - Bignumber("-50")).toString() == "51.0");
    assert((Bignumber("17.24175") - Bignumber("9179.861")).toString() == "-9162.61925");
    assert((Bignumber("21.55") - Bignumber("80.45")).toString() == "-58.9");

    //operator*
    assert((Bignumber("0") * Bignumber("0.0")).toString() == "0.0");
    assert((Bignumber("0.1") * Bignumber("0.0")).toString() == "0.0");
    assert((Bignumber("-3") * Bignumber("7.2")).toString() == "-21.6");
    assert((Bignumber("3.91") * Bignumber("-7.2")).toString() == "-28.152");
    assert((Bignumber("19.99") * Bignumber("99.9")).toString() == "1997.001");
    assert((Bignumber("1.0") * Bignumber("-50")).toString() == "-50.0");
    assert((Bignumber("17.24175") * Bignumber("9179.861")).toString() == "158276.86839675");
    assert((Bignumber("21.55") * Bignumber("80.45")).toString() == "1733.6975");

    //operator/
    //assert((Bignumber("0") / Bignumber("0.0")).toString() == "0.0");
    //assert((Bignumber("0.1") / Bignumber("0.0")).toString() == "0.0");
    assert((Bignumber("-3") / Bignumber("7.2")).toString() == "-0.41666666666666666666666666666666666666666666666666");
    assert((Bignumber("3.91") / Bignumber("-7.2")).toString() == "-0.54305555555555555555555555555555555555555555555555");
    assert((Bignumber("19.99") / Bignumber("99.9")).toString() == "0.2001001001001001001001001001001001001001001001001");
    assert((Bignumber("1.0") / Bignumber("-50")).toString() == "-0.02");
    assert((Bignumber("17.24175") / Bignumber("9179.861")).toString() == "0.00187821471370862805003256585257663487497250775365");
    assert((Bignumber("9179.861") / Bignumber("17.24175")).toString() == "532.42049095944437194600316093203996114083547203735119");
    assert((Bignumber("1.0") / Bignumber("1")).toString() == "1.0");
    assert((Bignumber("871.241") / Bignumber("871.241")).toString() == "1.0");
    assert((Bignumber("-999515.199999999999973") / Bignumber("-0.00000149")).toString() == "670815570469.7986577");
    assert((Bignumber("20") / Bignumber("3")).toString() == "6.66666666666666666666666666666666666666666666666666");

    // operator==
    //assert(Bignumber("-0") == Bignumber("0.0"));
    assert(Bignumber("1.0") == Bignumber("1"));
    assert(Bignumber("17.24") == Bignumber("17.240"));
    assert(Bignumber("0.15") == Bignumber("0.15"));
    assert(!(Bignumber("1.2") == Bignumber("12")));
    assert(!(Bignumber("-2") == Bignumber("2")));
    assert(!(Bignumber("1.000000000001") == Bignumber("1.000000000002")));

    // operator!=
    assert(!(Bignumber("1.0") != Bignumber("1")));
    assert(!(Bignumber("17.24") != Bignumber("17.240")));
    assert(!(Bignumber("0.15") != Bignumber("0.15")));
    assert((Bignumber("1.2") != Bignumber("12")));
    assert((Bignumber("-2") != Bignumber("2")));
    assert((Bignumber("1.000000000001") != Bignumber("1.000000000002")));

    // operator>
    assert(Bignumber("2") > Bignumber("0.0"));
    //assert(Bignumber("0") > Bignumber("-1"));
    assert(Bignumber("1.12000013") > Bignumber("1.1200001200"));
    assert(!(Bignumber("5") > Bignumber("5")));
    assert(!(Bignumber("0.0") > Bignumber("-0")));
    assert(!(Bignumber("3") > Bignumber("3.01")));
    // - 0 +
    // operator<
    assert(Bignumber("0.0") < Bignumber("2"));
    //assert(Bignumber("-1") < Bignumber("0"));
    assert(Bignumber("1.1200001200") < Bignumber("1.12000013"));
    assert(!(Bignumber("5") < Bignumber("5")));
    //assert(!(Bignumber("-0") < Bignumber("0.0")));
    assert(!(Bignumber("3.01") < Bignumber("3")));

    // operator>=
    assert(Bignumber("0") >= Bignumber("0.00"));
    assert(Bignumber("-5.01") >= Bignumber("-5.01"));
    //assert(Bignumber("2.5") >= Bignumber("-2.5"));
    //assert(Bignumber("7") >= Bignumber("-7.11"));
    assert(!(Bignumber("5") >= Bignumber("17")));
    assert(!(Bignumber("-2.5") >= Bignumber("2.5")));
    assert(!(Bignumber("99.989") >= Bignumber("99.99")));

    // operator<=
    assert(Bignumber("0.00") <= Bignumber("0"));
    assert(Bignumber("-5.01") <= Bignumber("-5.01"));
    //assert(Bignumber("-7.11") <= Bignumber("7"));
    assert(!(Bignumber("17") <= Bignumber("5")));
    //assert(!(Bignumber("2.5") <= Bignumber("-2.5")));
    assert(!(Bignumber("99.99") <= Bignumber("99.989")));





    return 0;
}