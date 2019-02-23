
#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <string>
#include <vector>


class Bignumber
{
    public:
        Bignumber();
        Bignumber(std::string); // should work with 00002
        Bignumber(const Bignumber&); // a + b / a = ?
        Bignumber& operator=(const Bignumber&);
        Bignumber& operator=(std::string); // TODO - FIX
        Bignumber operator+(const Bignumber&);
        Bignumber operator+(std::string);
        Bignumber operator-(const Bignumber&); ///    0/1898
        Bignumber operator-(std::string);
        Bignumber operator*(const Bignumber&); //TODO - remove trailing zeros
        Bignumber operator*(std::string);
        Bignumber operator/(const Bignumber&);
        Bignumber operator/(std::string);
        Bignumber operator%(const Bignumber&);
        Bignumber operator%(std::string);
        Bignumber operator-() const;
        bool operator==(const Bignumber&) const;
        bool operator==(std::string) const;
        bool operator!=(const Bignumber&) const;
        bool operator!=(std::string) const;
        bool operator>(const Bignumber&) const;
        bool operator>(std::string) const;
        bool operator<(const Bignumber&) const;
        bool operator<(std::string) const;
        bool operator>=(const Bignumber&) const;
        bool operator>=(std::string) const;
        bool operator<=(const Bignumber&) const;
        bool operator<=(std::string) const; 
        void print(); // fix
        std::string toString();
        Bignumber myAbs() const;
                
    private:
        bool isPositive;
        std::vector<int> integerPart;
        std::vector<int> fractionalPart;
        bool isValidNumber(std::string&, bool&);
        void removeTrailingZeros(std::string&);
        void removeTrailingZeros(Bignumber&);
        void removeLeadingZeros(Bignumber&);
        void makeSameLength(Bignumber&, Bignumber&);
};

#endif