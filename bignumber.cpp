
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
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
        else
        {
                fractionalPart.push_back(0); // TODO - change?
        }
        

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

Bignumber& Bignumber::operator=(const Bignumber& rhs)
{
    isPositive = rhs.isPositive;
    integerPart = rhs.integerPart;
    fractionalPart = rhs.fractionalPart;
    return *this;
}

Bignumber& Bignumber::operator=(string rhs)
{
    // if temp != rhs
    Bignumber temp(rhs);
    *this = temp;
    return *this;
}

Bignumber Bignumber::operator+(const Bignumber& rhs)
{
    if ((!isPositive) && (rhs.isPositive))
    {
        Bignumber num = *this;
        num.isPositive = true;
        //return rhs - num;
        //return -(num - rhs);
    }
    else if ((isPositive) && (!rhs.isPositive))
    {
        Bignumber num = rhs;
        num.isPositive = true;
        return *this - num; 
    }
    else
    {
        Bignumber result;
        result.fractionalPart.clear();
        result.integerPart.clear();
        int carry = 0;
      //  int longerFractionPartSize = fractionalPart.size() > rhs.fractionalPart.size() ? fractionalPart.size() : rhs.fractionalPart.size();
      //  int longerIntegerPartSize = integerPart.size() > rhs.integerPart.size() ? integerPart.size() : rhs.integerPart.size();
      //  int shorterFractionPartSize = fractionalPart.size() < rhs.fractionalPart.size() ? fractionalPart.size() : rhs.fractionalPart.size();
      //  int shorterIntegerPartSize = integerPart.size() < rhs.integerPart.size() ? integerPart.size() : rhs.integerPart.size();
      //  cout << endl << endl << rhs.fractionalPart.size() << endl;
        if (fractionalPart.size() > rhs.fractionalPart.size())
        {
            for (int i = fractionalPart.size() - 1; i >= 0; i--)
            {
                if (i > rhs.fractionalPart.size()-1)
                {
                    result.fractionalPart.push_back(fractionalPart[i]);
                }
                else
                {
                    if ((fractionalPart[i] + rhs.fractionalPart[i] + carry) >= 10)
                    {
                        result.fractionalPart.push_back(fractionalPart[i] + rhs.fractionalPart[i] + carry - 10);
                        carry = 1;
                    }
                    else
                    {
                        result.fractionalPart.push_back(fractionalPart[i] + rhs.fractionalPart[i] + carry);
                        carry = 0;
                    }
                }
            }
        }
        else
        {
            for (int i = rhs.fractionalPart.size() - 1; i >= 0; i--)
            {
                if (i > fractionalPart.size()-1)
                {
                    result.fractionalPart.push_back(rhs.fractionalPart[i]);
                }
                else
                {
                    if ((fractionalPart[i] + rhs.fractionalPart[i] + carry) >= 10)
                    {
                        result.fractionalPart.push_back(fractionalPart[i] + rhs.fractionalPart[i] + carry - 10);
                        carry = 1;
                    }
                    else
                    {
                        result.fractionalPart.push_back(fractionalPart[i] + rhs.fractionalPart[i] + carry);
                        carry = 0;
                    }
                }
            }
        }

        if (integerPart.size() > rhs.integerPart.size())
        {
            int diffInSize = integerPart.size() - rhs.integerPart.size();
            for (int i = integerPart.size() - 1; i >= 0; i--)
            {
                if (i < diffInSize)
                {
                    if (integerPart[i] + carry >= 10)
                    {
                        result.integerPart.push_back(integerPart[i] + carry - 10);
                        carry = 1;
                    }
                    else
                    {
                        result.integerPart.push_back(integerPart[i] + carry);
                        carry = 0;
                    }
                }
                else
                {
                    if ((integerPart[i] + rhs.integerPart[i - diffInSize] + carry) >= 10)
                    {
                        result.integerPart.push_back(integerPart[i] + rhs.integerPart[i - diffInSize] + carry - 10);
                        carry = 1;
                    }
                    else
                    {
                        result.integerPart.push_back(integerPart[i] + rhs.integerPart[i - diffInSize] + carry);
                        carry = 0;
                    }
                }
            }
        }
        else
        {
            int diffInSize = rhs.integerPart.size() - integerPart.size();
            for (int i = rhs.integerPart.size() - 1; i >= 0; i--)
            {
                if (i < diffInSize)
                {
                    if (rhs.integerPart[i] + carry >= 10)
                    {
                        result.integerPart.push_back(rhs.integerPart[i] + carry - 10);
                        carry = 1;
                    }
                    else
                    {
                        result.integerPart.push_back(rhs.integerPart[i] + carry);
                        carry = 0;
                    }
                }
                
                else
                {
                    if ((integerPart[i - diffInSize] + rhs.integerPart[i] + carry) >= 10)
                    {
                        result.integerPart.push_back(integerPart[i - diffInSize] + rhs.integerPart[i] + carry - 10);
                        carry = 1;
                    }
                    else
                    {
                        result.integerPart.push_back(integerPart[i - diffInSize] + rhs.integerPart[i] + carry);
                        carry = 0;
                    }
                }
            }
        } //FIX
        
        if (carry != 0)
        {
            result.integerPart.push_back(1);
        }

        result.isPositive = isPositive;
        /* if (carry != 0)
        {
            if (integerPart.size() == rhs.integerPart.size())
            {
                result.integerPart.push_back(1);
                carry = 0;
            }   
            else if (result.integerPart[result.integerPart.size() - 1] == 9)
            {
                result.integerPart[result.integerPart.size() - 1] = 0;
                result.integerPart.push_back(1);
            }
            else
            {
                result.integerPart[result.integerPart.size() - 1] += 1;
            }
        } */

        reverse(result.fractionalPart.begin(), result.fractionalPart.end());  
        reverse(result.integerPart.begin(), result.integerPart.end());

        return result;
    }
}   

Bignumber Bignumber::operator+(string rhs)
{
    Bignumber temp(rhs);
    Bignumber result = *this + temp;
    return result;
}

Bignumber Bignumber::operator-(const Bignumber& rhs)
{
    //  a - b
    // -a - b
    //  a - -b
    // -a - -b
    if (!isPositive && rhs.isPositive)
    {
        Bignumber temp(*this);
        temp.isPositive = true;
        //return -(temp + rhs);
    }
    if (isPositive && !rhs.isPositive)
    {
        Bignumber temp(rhs);
        temp.isPositive = true;
        return (*this + temp);
    }
    if (!isPositive && !rhs.isPositive)
    {
        Bignumber temp(rhs);
        temp.isPositive = true;
        return (*this + temp);
    }

  //  if (rhs > *this)
  //  {
       // return -(rhs - *this);
  // }

    Bignumber a(*this);
    Bignumber b(rhs);
    Bignumber result;
    result.integerPart.clear();
    result.fractionalPart.clear();
    makeSameLength(a, b);
    int intPartSize = a.integerPart.size();
    int fractPartSize = a.fractionalPart.size();
    int borrow = 0; // change name?
    
    for (int i = fractPartSize - 1; i >= 0; i--)
    {
        if (a.fractionalPart[i] - b.fractionalPart[i] - borrow < 0)
        {
            result.fractionalPart.push_back(a.fractionalPart[i] - b.fractionalPart[i] - borrow + 10);
            borrow = 1;
        }
        else
        {
            result.fractionalPart.push_back(a.fractionalPart[i] - b.fractionalPart[i] - borrow);
            borrow = 0;
        } 
    }

    for (int i = intPartSize - 1; i >= 0; i--)
    {
        if (a.integerPart[i] - b.integerPart[i] - borrow < 0)
        {
            result.integerPart.push_back(a.integerPart[i] - b.integerPart[i] - borrow + 10);
            borrow = 1;
        }
        else
        {
            result.integerPart.push_back(a.integerPart[i] - b.integerPart[i] - borrow);
            borrow = 0;
        } 
    }

    reverse(result.fractionalPart.begin(), result.fractionalPart.end());
    reverse(result.integerPart.begin(), result.integerPart.end());
    
    return result;
}

Bignumber& Bignumber::operator-() // Needs testing.
{
    isPositive = !isPositive;
    return *this;
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

bool Bignumber::operator!=(const Bignumber& rhs) // Needs testing.
{
    if (*this == rhs)
        return false;
    else
        return true;
}

bool Bignumber::operator!=(std::string rhs) // Needs testing.
{
    Bignumber temp(rhs);
    if (*this != temp)
        return true;
    else
        return false;
}

bool Bignumber::operator>(const Bignumber& rhs)
{
    if (integerPart.size() > rhs.integerPart.size())
        return true;
    else if (rhs.integerPart.size() > integerPart.size())
        return false;
    else
    {
        for (int i = 0; i < integerPart.size(); i++)
        {
            if (integerPart[i] > rhs.integerPart[i])
                return true;
            else if (rhs.integerPart[i] > integerPart[i])
                return false;
        }
    }
    
    for (int i = 0; i < fractionalPart.size(); i++)
    {
        if (i > (rhs.fractionalPart.size() - 1))
        {
            return true;
        }
        else
        {
            if (fractionalPart[i] > rhs.fractionalPart[i])
                return true;
            else if (rhs.fractionalPart[i] > fractionalPart[i])
                return false;
        }
    }
    return false;
}

bool Bignumber::operator>(string rhs)
{
    Bignumber temp(rhs);
    return (*this > temp);
}

void Bignumber::removeTrailingZeros(string& num) // add to + and -
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

void Bignumber::makeSameLength(Bignumber& num1, Bignumber& num2)
{
    int intSize1 = num1.integerPart.size();
    int intSize2 = num2.integerPart.size();
    int fractSize1 = num1.fractionalPart.size();
    int fractSize2 = num2.fractionalPart.size();
    int intSizeDiff = (intSize1 > intSize2) ? intSize1 - intSize2 : intSize2 - intSize1;
    int fractSizeDiff = (fractSize1 > fractSize2) ? fractSize1 - fractSize2 : fractSize2 - fractSize1;
    vector<int>::iterator it;

    if (intSize1 > intSize2)
    {
        it = num2.integerPart.begin();
        num2.integerPart.insert(it, intSizeDiff, 0);
    }
    else if (intSize2 > intSize1)
    {
        it = num1.integerPart.begin();
        num1.integerPart.insert(it, intSizeDiff, 0);
    }
    if (fractSize1 > fractSize2)
    {
        it = num2.fractionalPart.end();
        num2.fractionalPart.insert(it, fractSizeDiff, 0);
    }
    else if (fractSize2 > fractSize1)
    {
        
        it = num1.fractionalPart.end();
        num1.fractionalPart.insert(it, fractSizeDiff, 0);
    }
}

//fd
//4353fds
//+432423
//-54353
//3213123
//321.10000000