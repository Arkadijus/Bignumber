
#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <string>
#include <vector>


class Bignumber
{
    public:
        Bignumber();
        Bignumber(std::string);
        Bignumber(const Bignumber&);

        Bignumber& operator=(const Bignumber&);
        Bignumber& operator=(std::string);

        Bignumber operator+(const Bignumber&);
        Bignumber operator+(std::string);

        Bignumber operator-(const Bignumber&);
        Bignumber operator-(std::string);

        Bignumber operator*(const Bignumber&);
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

        Bignumber& operator+=(const Bignumber&);
        Bignumber& operator+=(std::string);

        Bignumber& operator-=(const Bignumber&);
        Bignumber& operator-=(std::string);

        Bignumber& operator*=(const Bignumber&);
        Bignumber& operator*=(std::string);

        Bignumber& operator/=(const Bignumber&);
        Bignumber& operator/=(std::string);

        Bignumber& operator%=(const Bignumber&);
        Bignumber& operator%=(std::string);

        // Returns a specified digit
        // Use positive values (and 0) for integerPart
        // And negative values for fractionalPart
        int operator[](int) const; 

        Bignumber& operator++();
        Bignumber operator++(int);

        Bignumber& operator--();
        Bignumber operator--(int);

        void print();
        std::string toString() const;
        Bignumber Abs() const;
        int getIntegerPartLength() const;
        int getFractionalPartLength() const;
        int getNumberLength() const;
        friend std::ostream& operator<<(std::ostream&, const Bignumber&);
                
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