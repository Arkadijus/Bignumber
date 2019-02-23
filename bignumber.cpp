
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "bignumber.h"

#define MAX_DECIMAL_PLACES 50     // Maximum number of decimal places after divison

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
        //cout << this->toString() << endl;
        //cout << integerPart[0] << endl;
        //cout << fractionalPart[0] << endl;
        if (integerPart.size() == 1 && fractionalPart.size() == 1)
        {
            if (integerPart[0] == 0 && fractionalPart[0] == 0)
            {
                isPositive = true;
            }
        }
        //cout << this->toString() << endl;
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
        //return rhs - num; //TODO function const;
        return -(num - rhs);
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
        removeTrailingZeros(result);
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
        return -(temp + rhs);
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

    if (rhs > *this)
    {
        Bignumber temp(rhs);
        return -(temp - *this);
    }

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
    removeLeadingZeros(result);
    removeTrailingZeros(result);
    return result;
}

Bignumber Bignumber::operator*(const Bignumber& rhs)
{
    if (*this == "0.0" || rhs == "0.0") // Change to 0?
    {
        Bignumber temp("0.0");
        return temp;
    }
    if (*this == "1.0" || *this == "-1.0")
    {
        Bignumber temp(rhs);
        temp.isPositive = (temp.isPositive == isPositive) ? true : false;
        return temp;
        //return rhs;
    }
    if (rhs == "1.0" || rhs == "-1.0")
    {
        Bignumber temp(*this);
        temp.isPositive = (temp.isPositive == rhs.isPositive) ? true : false;
        return temp;
    }

    Bignumber result;
    result.integerPart.clear();   //TODO - no clear?
    result.fractionalPart.clear();

    Bignumber temp;
    temp.integerPart.clear();   //TODO - no temp
    temp.fractionalPart.clear();

    vector<int> noDecimals1 = integerPart;
    noDecimals1.insert(noDecimals1.end(), fractionalPart.begin(), fractionalPart.end()); 
    int size1 = noDecimals1.size();

    vector<int> noDecimals2 = rhs.integerPart;
    noDecimals2.insert(noDecimals2.end(), rhs.fractionalPart.begin(), rhs.fractionalPart.end());
    int size2 = noDecimals2.size();

    int carry = 0;

    if (size1 > size2)
    {
        for (int i = size2 - 1; i >= 0; i--)
        {
            for (int j = size1 - 1; j >=0; j--)
            {
                if (noDecimals2[i] * noDecimals1[j] + carry >= 10)
                {
                    temp.integerPart.push_back((noDecimals2[i] * noDecimals1[j] + carry) % 10);
                    carry = (noDecimals2[i] * noDecimals1[j] + carry) / 10;
                }
                else
                {
                    temp.integerPart.push_back(noDecimals2[i] * noDecimals1[j] + carry);
                    carry = 0;
                }
            }
            if (carry != 0)
            {
                temp.integerPart.push_back(carry);
                carry = 0;
            }
            reverse(temp.integerPart.begin(), temp.integerPart.end());
            temp.integerPart.insert(temp.integerPart.end(), size2 - i - 1, 0);
            result = result + temp;
            temp.integerPart.clear();
        }
    }
    else
    {
        for (int i = size1 - 1; i >= 0; i--)
        {
            for (int j = size2 - 1; j >=0; j--)
            {
                if (noDecimals2[j] * noDecimals1[i] + carry >= 10)
                {
                    temp.integerPart.push_back((noDecimals2[j] * noDecimals1[i] + carry) % 10);
                    carry = (noDecimals2[j] * noDecimals1[i] + carry) / 10;
                }
                else
                {
                    temp.integerPart.push_back(noDecimals2[j] * noDecimals1[i] + carry);
                    carry = 0;
                }
            }
            if (carry != 0)
            {
                temp.integerPart.push_back(carry);
                carry = 0;
            }
            reverse(temp.integerPart.begin(), temp.integerPart.end());
            temp.integerPart.insert(temp.integerPart.end(), size1 - i - 1, 0);
            result = result + temp;
            temp.integerPart.clear();
        }
    }
    int decimalPlace = fractionalPart.size() + rhs.fractionalPart.size();
    result.fractionalPart.insert(result.fractionalPart.end(), result.integerPart.end() - decimalPlace, result.integerPart.end());
    result.integerPart.erase(result.integerPart.end() - decimalPlace, result.integerPart.end());

    result.isPositive = (isPositive == rhs.isPositive) ? true : false;
    removeTrailingZeros(result);
    return result;
}

Bignumber Bignumber::operator*(string rhs)
{
    Bignumber temp(rhs);
    return *this * temp;
}

Bignumber Bignumber::operator/(const Bignumber& rhs)
{
    if (rhs == "0.0")
    {
        return *this; // Error
    }
    if (rhs == "1.0" || rhs == "-1.0")
    {
        Bignumber temp(*this);
        temp.isPositive = (temp.isPositive == rhs.isPositive) ? true : false;
        return temp;
    }

    Bignumber divisor, temp, result;
    divisor.integerPart.clear();
    //divisor.fractionalPart.clear();
    temp.integerPart.clear();
    //temp.fractionalPart.clear();
    result.integerPart.clear();
    result.fractionalPart.clear();
    //Bignumber dividend;
    //dividend.integerPart.clear();
    //dividend.fractionalPart.clear();
    //dividend.integerPart.insert(dividend.integerPart.begin(), integerPart.begin(), integerPart.end());
    //dividend.integerPart.insert(dividend.integerPart.end(), fractionalPart.begin(), fractionalPart.end());
    vector<int> dividend;
    dividend.insert(dividend.begin(), integerPart.begin(), integerPart.end());
    dividend.insert(dividend.end(), fractionalPart.begin(), fractionalPart.end());
    int zerosToInsert = ((int)(rhs.fractionalPart.size() - fractionalPart.size()) > 0) ? (int)(rhs.fractionalPart.size() - fractionalPart.size()) : 0; // shorter
    if (fractionalPart.size() == 1 && fractionalPart[0] == 0)
    {
        if (!(rhs.fractionalPart.size() == 1 && rhs.fractionalPart[0] == 0))
        {
            zerosToInsert++; // test
        }
    }

    //cout << zerosToInsert << endl;
    dividend.insert(dividend.end(), zerosToInsert, 0);
    /* for (int i = 0; i < dividend.size(); i++)
    {
        cout << dividend[i] << endl;
    } */
    int quotient = 0; // rename
    int decimalPlaces = 0;
    
    divisor.integerPart.insert(divisor.integerPart.begin(), rhs.integerPart.begin(), rhs.integerPart.end());
    divisor.integerPart.insert(divisor.integerPart.end(), rhs.fractionalPart.begin(), rhs.fractionalPart.end());
    removeLeadingZeros(divisor);
    

    /* for (int i = 0; i < divisor.integerPart.size(); i++)
    {
        cout << divisor.integerPart[i] << endl;
    } */
    //cout << dividend.size();
    for (int i = 0; i < dividend.size(); i++)
    {
        temp.integerPart.push_back(dividend[i]);
        removeLeadingZeros(temp);
        //temp.print();
        while (temp >= divisor)
        {
            //temp.print();
            //divisor.print();
            temp = temp - divisor;
            //temp.print();
            quotient++;
        }
        result.integerPart.push_back(quotient);
        quotient = 0;
    }
    //temp.print();
    while (temp != "0.0" && decimalPlaces != MAX_DECIMAL_PLACES)
    {
        temp.integerPart.push_back(0);
        while (temp >= divisor)
        {
            temp = temp - divisor;
            quotient++;
        }
        result.integerPart.push_back(quotient);
        quotient = 0;
        //temp.print();
        decimalPlaces++;
    }
    int dp = 0; // change
    dp = rhs.fractionalPart.size() + integerPart.size();
    result.fractionalPart.insert(result.fractionalPart.begin(), result.integerPart.begin() + dp, result.integerPart.end());
    if (result.fractionalPart.size() == 0)
        result.fractionalPart.push_back(0);
    result.integerPart.erase(result.integerPart.begin() + dp, result.integerPart.end());
    if (result.fractionalPart.size() > MAX_DECIMAL_PLACES)
        result.fractionalPart.erase(result.fractionalPart.begin() + MAX_DECIMAL_PLACES, result.fractionalPart.end());
    removeTrailingZeros(result);
    removeLeadingZeros(result);
    result.isPositive = (isPositive == rhs.isPositive) ? true : false;
    return result;
}

Bignumber Bignumber::operator/(string rhs)
{
    Bignumber temp(rhs);
    return (*this / temp);
}

Bignumber Bignumber::operator-() const // Needs testing.
{
    Bignumber temp(*this);
    temp.isPositive = !temp.isPositive;
    return temp;
}

bool Bignumber::operator==(const Bignumber& rhs) const
{
    if ((isPositive == rhs.isPositive) && (integerPart == rhs.integerPart) && (fractionalPart == rhs.fractionalPart))
        return true;
    else
        return false;
}

bool Bignumber::operator==(string rhs) const
{
    Bignumber temp(rhs);
    if (*this == temp)
        return true;
    else
        return false; 
}

bool Bignumber::operator!=(const Bignumber& rhs) const
{
    if (*this == rhs)
        return false;
    else
        return true;
}

bool Bignumber::operator!=(std::string rhs) const
{
    Bignumber temp(rhs);
    if (*this != temp)
        return true;
    else
        return false;
}

bool Bignumber::operator>(const Bignumber& rhs) const
{
    //removeLeadingZeros(rhs); // Remove;
    if (isPositive && !rhs.isPositive)
        return true;
    if (!isPositive && rhs.isPositive)
        return false;
    if (!isPositive && !rhs.isPositive)
        return -(*this) > -rhs;

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

bool Bignumber::operator>(string rhs) const
{
    Bignumber temp(rhs);
    return (*this > temp);
}

bool Bignumber::operator<(const Bignumber& rhs) const // test
{
    if (*this >= rhs)
        return false;
    else
        return true;
}
bool Bignumber::operator<(string rhs) const
{
    Bignumber temp(rhs);
    return (*this < temp);
}

bool Bignumber::operator>=(const Bignumber& rhs) const // test
{
    if (*this > rhs || *this == rhs)
        return true;
    else
        return false;
}

bool Bignumber::operator>=(std::string rhs) const// Test
{
    Bignumber temp(rhs);
    return (*this >= temp);
}

bool Bignumber::operator<=(const Bignumber& rhs) const
{
    if (*this > rhs)
        return false;
    else
        return true;
}

bool Bignumber::operator<=(string rhs) const
{
    Bignumber temp(rhs);
    return (*this <= temp);
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

void Bignumber::removeTrailingZeros(Bignumber& num)
{
    int i = num.fractionalPart.size() - 1;
    while (num.fractionalPart[i] == 0 && i != 0)
    {
        i--;
    }
    num.fractionalPart.erase(num.fractionalPart.begin() + i + 1, num.fractionalPart.end());
}

void Bignumber::removeLeadingZeros(Bignumber& num)
{
    int i = 0;
    while (num.integerPart[i] == 0 && i != num.integerPart.size() - 1)
    {
        i++;
    }
    num.integerPart.erase(num.integerPart.begin(), num.integerPart.begin() + i);
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

string Bignumber::toString()
{
    string num = "";
    if (!isPositive)
        num.push_back('-');
    for (int i = 0; i < integerPart.size(); i++)
    {
        num.push_back(integerPart[i] + '0');
    }
    num.push_back('.');
    for (int i = 0; i < fractionalPart.size(); i++)
    {
        num.push_back(fractionalPart[i] + '0');
    }
    return num;
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