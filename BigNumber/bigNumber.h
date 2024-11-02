#ifndef BIGNUMBER_BIGNUMBER_H
#define BIGNUMBER_BIGNUMBER_H

#include <iostream>

using namespace std;

class bigNumber {
private:
    int numberOfDigits;
    int *Digits;
    bool sign;
public:
    bigNumber() : numberOfDigits(0) {
        sign = true;
        numberOfDigits = 1;
        Digits = new int[numberOfDigits];
    };

    bigNumber(string str, bool S);

    bigNumber(int arr[], int length, bool s);

    bigNumber(int);

    ~bigNumber();

    bigNumber(const bigNumber &);

    friend bool operator>(bigNumber, bigNumber);

    friend bigNumber operator-(bigNumber, bigNumber);

    friend bigNumber operator+(bigNumber, bigNumber);

    bigNumber shiftR();

    bigNumber shiftR(int);

    bigNumber shiftL();

    bigNumber shiftL(int);

    void print() {
        if (numberOfDigits == 0) {
            cout << 0;
            return;
        }
        if (!sign)
            cout << '-';
        for (int i = 0; i < numberOfDigits; i++) {
            cout << Digits[i];
        }
    }
};


#endif
