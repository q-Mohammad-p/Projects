#ifndef BIGNUMBER_BIGNUMBER_H
#define BIGNUMBER_BIGNUMBER_H

#include <iostream>

using namespace std;

class bigNumber {
private:
    int numberOfDigits;
    bool sign;
    string Digits;
public:
    bigNumber() {
        sign = true;
        numberOfDigits = 0;
        Digits = "";
    };

    bigNumber(const string &str, bool S);

    bigNumber(const string &str);

    bigNumber(int arr[], int length, bool s);

    bigNumber(int);

    bigNumber(const bigNumber &);

    bigNumber(const bigNumber &, bool);

    bigNumber(const bigNumber &, int, int);

    friend bool operator>(const bigNumber&,const bigNumber &);

    friend bool operator>=(const bigNumber&,const bigNumber&);

    friend bigNumber operator-(bigNumber, bigNumber);

    friend bigNumber operator+(  const bigNumber &,const bigNumber &);

    friend bigNumber operator*(bigNumber&, bigNumber&);

    friend bigNumber mult(bigNumber, bigNumber);

    friend bigNumber operator/(const bigNumber&, const bigNumber&);

    friend bigNumber power( bigNumber&, int);

    int getNum() const {
        return numberOfDigits;
    }

    string &getDigits() {
        return Digits;
    }

    friend void removeZero(string &);
    friend void remove_Zero(bigNumber &);

    bigNumber shiftR();

    bigNumber shiftR(int);

    bigNumber shiftL();

    bigNumber shiftL(int);

    friend void shiftL(bigNumber &, int);

    void print() const {
        if (!sign)
            cout << '-';
        cout << Digits;
//        if (numberOfDigits == 0) {
//            cout << 0;
//            return;
//        }
//        for (int i = 0; i < numberOfDigits; i++) {
//            cout << Digits[i];
//        }
    }
};


#endif
