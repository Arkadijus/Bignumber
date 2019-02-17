
#include <iostream>
#include <string>
#include "bignumber.h"

using namespace std;

Bignumber::Bignumber()
{
    integerPart.push_back(0);
    fractionalPart.push_back(0);
    isPositive = true;
}
Bignumber::Bignumber(string num)
{
    bool hasDecimalPoint = false;
    if (isValidNumber(num, hasDecimalPoint))
    {
        if (hasDecimalPoint)
            removeTrailingZeros(num);

        int i = 0;
        while ((num[i] != '.') && (num[i] != '\0'))
        {
            integerPart.push_back(num[i] - '0');
            i++;
        }

        if (num[i] == '.')
            i++;

        while (num[i] != '\0')
        {
            fractionalPart.push_back(num[i] - '0');
            i++;
        }
    }
    // TODO - add else.
}

Bignumber::Bignumber(const Bignumber& bn)
{
    integerPart = bn.integerPart;
    fractionalPart = bn.fractionalPart;
    isPositive = bn.isPositive;
}

bool Bignumber::operator==(const Bignumber& rhs)
{
    if ((isPositive == rhs.isPositive) && (integerPart == rhs.integerPart) && (fractionalPart == rhs.fractionalPart))
        return true;
    else
        return false;
}

bool Bignumber::operator==(string rhs)
{
    Bignumber temp(rhs);
    if (*this == temp)
        return true;
    else
        return false; 
}

void Bignumber::removeTrailingZeros(string& num)
{
    int i = num.size() - 1;
    while ((num[i] == '0') && (num[i-1] != '.'))
    {
        i--;
    }
    num.erase(i+1, string::npos);
}

bool Bignumber::isValidNumber(string& num, bool& hasDecimalPoint)
{  
    if (num[0] == '-')
    {
        isPositive = false;
        num.erase(0, 1);
    }
    else if (num[0] == '+')
    {
        isPositive = true;
        num.erase(0, 1);
    }
    else if ((num.size() > 1) && (num[0] == '0') && (num[1] != '.'))
    {
        return false;
    }
    else
    {
        isPositive = true;
    }
    
    for (int i = 0; i < num.size(); i++)
    {
        if ((num[i] < '0') || (num[i] > '9'))
        {
            if ((num[i] == '.') && (hasDecimalPoint == false))
            {
                if ((i == 0) || (i == num.size() - 1))
                    return false;

                hasDecimalPoint = true;
            }
            else
            {
                return false;
            }
        }
    }

    return true;
}

void Bignumber::print() // fix
{
    if (!isPositive)
    {
        cout << "-";
    }
    for (int i = 0; i < integerPart.size(); i++)
    {
        cout << integerPart[i];
    }
    cout << ".";
    for (int i = 0; i < fractionalPart.size(); i++)
    {
        cout << fractionalPart[i];
    }
    cout << endl;
}


//fd
//4353fds
//+432423
//-54353
//3213123
//321.10000000