#include "bigNumber.h"


bool operator>(bigNumber big1, bigNumber big2) {
    if (big1.numberOfDigits > big2.numberOfDigits)
        return true;
    else if (big1.numberOfDigits < big2.numberOfDigits)
        return false;
    else if (big1.numberOfDigits == big2.numberOfDigits) {
        for (int i = 0; big1.numberOfDigits >= i; ++i) {
            if (big1.Digits[i] > big2.Digits[i])
                return true;
            else if (big1.Digits[i] == big2.Digits[i])
                continue;
            else return false;
        }
    }
    return false;
}

bigNumber operator-(bigNumber big1, bigNumber big2) {
    bigNumber *a = nullptr;
    bigNumber *b = nullptr;
    int carry = 0;
    int sum;
    bool Sign;
    int i;
    if (big1.sign and !big2.sign) {
        return bigNumber(big1.Digits, big1.numberOfDigits, true) +
               bigNumber(big2.Digits, big2.numberOfDigits, true);
    } else if (!big1.sign and big2.sign)
        return bigNumber(big1.Digits, big1.numberOfDigits, false) +
               bigNumber(big2.Digits, big2.numberOfDigits, false);


    if (big1 > big2) {
        Sign = true;
        i = big1.numberOfDigits - 1;
        a = &big1;
        b = &big2;
    } else {
        Sign = false;
        i = big2.numberOfDigits - 1;
        a = &big2;
        b = &big1;
    }

    int *result = new int[a->numberOfDigits];
    int delta = a->numberOfDigits - b->numberOfDigits;
    for (; i >= 0; --i) {

        if (i < delta) {
            sum = a->Digits[i] + carry;
            if (sum >= 0) {
                result[i] = sum;
                carry = 0;
            } else {
                result[i] = sum + 10;
                carry = -1;
            }
            continue;
        }
        if (a->Digits[i] + carry < b->Digits[i - delta]) {
            sum = a->Digits[i] - b->Digits[i - delta] + carry + 10;
            result[i] = sum;
            carry = -1;
        } else if (a->Digits[i] + carry == b->Digits[i - delta]) {
            result[i] = 0;
            carry = 0;
        } else {
            sum = a->Digits[i] + carry - b->Digits[i - delta];
            result[i] = sum;
            carry = 0;
        }
    }
    return bigNumber(result, a->numberOfDigits, Sign);
}


bigNumber operator+(bigNumber big1, bigNumber big2) {
    bigNumber *a = nullptr;
    bigNumber *b = nullptr;
    int sum;
    int carry = 0;
    bool Sign;
    if (big1.sign and !big2.sign) {
        return bigNumber(big1.Digits, big1.numberOfDigits, true) -
               bigNumber(big2.Digits, big2.numberOfDigits, true);
    } else if (!big1.sign and big2.sign) {
        return bigNumber(big2.Digits, big2.numberOfDigits, true) -
               bigNumber(big1.Digits, big1.numberOfDigits, true);
    }
    int i;
    if (big1.numberOfDigits >= big2.numberOfDigits) {
        i = big1.numberOfDigits - 1;
        a = &big1;
        b = &big2;
    } else {
        i = big2.numberOfDigits - 1;
        a = &big2;
        b = &big1;
    }
    int *result = new int[a->numberOfDigits];
    int delta = a->numberOfDigits - b->numberOfDigits;
    if (big1.sign)
        Sign = true;
    else Sign = false;
    for (i; i >= 0; --i) {
        if (i < delta) {
            result[i] = a->Digits[i] + carry;
            carry = 0;
            continue;
        }


        sum = a->Digits[i] + b->Digits[i - (delta)] + carry;
        carry = 0;
        if (sum > 9 and i != 0) {
            result[i] = sum - 10;
            carry = 1;
        } else if (sum > 9) {
            result[i] = sum - 10;
            carry = 1;
        } else result[i] = sum;

    }
    if (i == -1 and carry != 0) {

        int *temp = new int[a->numberOfDigits + 1];
        for (int j = 0; j < a->numberOfDigits + 1; ++j) {
            if (j == 0)
                temp[0] = 1;
            else temp[j] = result[j - 1];
        }
        delete[]result;
        return bigNumber(temp, a->numberOfDigits + 1, Sign);
    }
    return bigNumber(result, a->numberOfDigits, Sign);
}


bigNumber::bigNumber(int arr[], int length, bool S) {
    sign = S;
    int count = 0;
    while (arr[count] < 1) {
        ++count;
    }
    if (length == 0) {
        numberOfDigits = 0;
        Digits = new int[1];
        Digits[0] = 0;
    } else {
        numberOfDigits = length - count;
        Digits = new int[numberOfDigits];
        for (int i = 0; i < numberOfDigits; ++i) {
            Digits[i] = arr[i + count];
        }
    }
}

bigNumber bigNumber::shiftR() {
    int i = 0;
    int *temp = new int[numberOfDigits - 1];
    while (i < numberOfDigits - 1) {
        temp[i] = Digits[i];
        i++;
    }

    return bigNumber(temp, numberOfDigits - 1, sign);
}

bigNumber bigNumber::shiftR(int n) {
    int *temp = new int[numberOfDigits - n];
    for (int i = 0; i < numberOfDigits - n; ++i) {
        temp[i] = Digits[i];
    }
    return bigNumber(temp, numberOfDigits - n, true);
}

bigNumber bigNumber::shiftL() {
    int *temp = new int[numberOfDigits + 1];
    for (int i = 0; i < numberOfDigits + 1; ++i) {
        if (i == numberOfDigits)
            temp[i] = 0;
        else
            temp[i] = Digits[i];
    }
    return bigNumber(temp, numberOfDigits + 1, sign);
}

bigNumber bigNumber::shiftL(int n) {
    int *temp = new int[numberOfDigits + n];
    for (int i = 0; i < numberOfDigits + n; ++i) {
        if (i >= numberOfDigits) {
            temp[i] = 0;
        } else
            temp[i] = Digits[i];
    }
    return bigNumber(temp, numberOfDigits + n, sign);
}

bigNumber::bigNumber(string str, bool S) {
    sign = S;
    int count = 0;
    while (str[count] < 1) {
        ++count;
    }
    if (str.length() == 0) {
        numberOfDigits = 0;
        Digits = new int[1];
        Digits[0] = 0;
    } else {
        numberOfDigits = str.length() - count;
        Digits = new int[numberOfDigits];
        for (int i = 0; i < numberOfDigits; ++i) {
            Digits[i] = str[i + count] - '0';
        }
    }
}

bigNumber::bigNumber(int num) {
    if (num > 0)
        sign = true;
    else sign = false;
    num = abs(num);
    Digits = new int[10];
    int i = 9;
    while (num > 0) {
        Digits[i] = num % 10;
        num /= 10;
        i--;
    }
    if (i >= 0) {
        int *temp = new int[9 - i];
        for (int j = 9; j > i; --j) {
            temp[j - i - 1] = Digits[j];
        }
        delete[] Digits;
        Digits = temp;
        numberOfDigits = 9 - i;
    } else numberOfDigits = 10;
}

bigNumber::~bigNumber() {
    delete[] Digits;
}

bigNumber::bigNumber(const bigNumber &other) {
    sign = other.sign;
    numberOfDigits = other.numberOfDigits;
    Digits = new int[other.numberOfDigits];
    for (int i = 0; i < other.numberOfDigits; ++i) {
        Digits[i] = other.Digits[i];
    }
}
