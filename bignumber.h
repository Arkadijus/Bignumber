
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
        bool operator==(const Bignumber&);
        bool operator==(std::string);
        void print(); // fix
                
    private:
        bool isPositive;
        std::vector<int> integerPart;
        std::vector<int> fractionalPart;
        bool isValidNumber(std::string&, bool&);
        void removeTrailingZeros(std::string&);
};

#endif