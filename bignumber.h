
#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <string>
#include <vector>


class Bignumber
{
    public:
        Bignumber();
        Bignumber(std::string);
        Bignumber(const Bignumber&); // a + b / a = ?
        Bignumber& operator=(const Bignumber&);
        Bignumber& operator=(std::string); // TODO - FIX
        Bignumber operator+(const Bignumber&);
        Bignumber operator+(std::string);
        Bignumber operator-(const Bignumber&);
        Bignumber operator-(std::string);
        bool operator==(const Bignumber&);
        bool operator==(std::string);
        bool operator>(const Bignumber&);
        bool operator>(std::string);
        void print(); // fix
                
    private:
        bool isPositive;
        std::vector<int> integerPart;
        std::vector<int> fractionalPart;
        bool isValidNumber(std::string&, bool&);
        void removeTrailingZeros(std::string&);
        void makeSameLength(Bignumber&, Bignumber&);
};

#endif