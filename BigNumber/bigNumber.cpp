#include "bigNumber.h"


void removeZero(string &a) {
    int count = 0;
    while ((a[count] - '0' < 1 and count != a.length())) {
        ++count;
    }
    if (count == a.length()) {
        a.erase(0, count - 1);
    } else {
        a.erase(0, count);
    }
}

bool operator>(const bigNumber &big1, const bigNumber &big2) {
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
        return bigNumber(big1.Digits, true) +
               bigNumber(big2.Digits, true);
    } else if (!big1.sign and big2.sign)
        return bigNumber(big1.Digits, false) +
               bigNumber(big2.Digits, false);

    remove_Zero(big2);
    remove_Zero(big1);
    if (big1 >= big2) {
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

    string result;
    int delta = a->numberOfDigits - b->numberOfDigits;
    for (; i >= 0; --i) {

        if (i < delta) {
            sum = a->Digits[i] - '0' + carry;
            if (sum >= 0) {
                result = to_string(sum) + result;
                carry = 0;
            } else {
                result = std::to_string(sum + 10) + result;
                carry = -1;
            }
            continue;
        }
        if (a->Digits[i] - '0' + carry < b->Digits[i - delta] - '0') {
            sum = a->Digits[i] - b->Digits[i - delta] + carry + 10;
            result = std::to_string(sum) + result;
            carry = -1;
        } else if (a->Digits[i] - '0' + carry == b->Digits[i - delta] - '0') {
            result = "0" + result;
            carry = 0;
        } else {
            sum = (a->Digits[i] - '0') - (b->Digits[i - delta] - '0') + carry;
            result = std::to_string(sum) + result;
            carry = 0;
        }
    }
    int count = 0;
    while (result[count] - '0' < 1 and count != result.length() - 1)
        count++;
    if (count != result.length())
        result.erase(0, count);
    return bigNumber(result, Sign);
}


bigNumber operator+(const bigNumber &big1, const bigNumber &big2) {
    int sum;
    int carry = 0;
    bool Sign;
    if (big1.sign and !big2.sign) {
        return bigNumber(big1.Digits, true) -
               bigNumber(big2.Digits, true);
    } else if (!big1.sign and big2.sign) {
        return bigNumber(big2.Digits, true) -
               bigNumber(big1.Digits, true);
    }
    string s1 = big1.Digits;
    string s2 = big2.Digits;
    removeZero(s1);
    removeZero(s2);
    int i;

    if (s1.length() >= s2.length()) {
        i = s1.length() - 1;
    } else {
        i = s2.length() - 1;
        swap(s1, s2);
    }
    string result;

    int delta = s1.length() - s2.length();
    if (big1.sign)
        Sign = true;
    else Sign = false;
    for (i; i >= 0; --i) {
        if (i < delta) {
            sum = (s1[i] - '0' + carry);
            if (sum > 9) {
                result = to_string(s1[i] - '0' + carry - 10) + result;
                carry = 1;
            } else {
                result = to_string(s1[i] - '0' + carry) + result;
                carry = 0;
            }
            continue;
        }

        sum = s1[i] - '0' + s2[i - (delta)] - '0' + carry;

        carry = 0;
        if (sum > 9 and i != 0) {
            result = to_string(sum - 10) + result;
            carry = 1;
        } else if (sum > 9) {
            result = to_string(sum - 10) + result;
            carry = 1;
        } else result = to_string(sum) + result;

    }
    if (i == -1 and carry != 0) {
        result = "1" + result;
    }
    return bigNumber(result, Sign);
}


bigNumber::bigNumber(int arr[], int length, bool S) {
    sign = S;
    int count = 0;
    if (length == 0) {
        numberOfDigits = 0;
        Digits += +"";
    } else {
        numberOfDigits = length - count;
        for (int i = 0; i < numberOfDigits; ++i) {
            Digits += to_string(arr[i + count]);
        }
    }
}

bigNumber bigNumber::shiftR() {
    string str = Digits;
    str.pop_back();
    return bigNumber(str, sign);
}

bigNumber bigNumber::shiftR(int n) {
    string str = Digits;
    for (int i = 0; i < n; ++i) {
        str.pop_back();
    }
    return bigNumber(str, sign);
}

bigNumber bigNumber::shiftL() {
    Digits = Digits + "0";
    return bigNumber(Digits, sign);
}

bigNumber bigNumber::shiftL(int n) {
    for (int i = 0; i < n; ++i) {
        Digits = Digits + "0";
    }
    return bigNumber(Digits, sign);
}

bigNumber::bigNumber(const string &str, bool S) {
    sign = S;
    int count = 0;
    numberOfDigits = str.length();
    Digits = str;
}

bigNumber::bigNumber(int num) {
    if (num >= 0)
        sign = true;
    else sign = false;
    num = abs(num);
    if (num == 0) {
        Digits = "0" + Digits;
        numberOfDigits = 1;
    } else {
        int i = 9;
        while (num > 0) {
            Digits = to_string(num % 10) + Digits;
            num /= 10;
            i--;
        }
        numberOfDigits = 9 - i;
    }
}

bigNumber::bigNumber(const bigNumber &other) {
    sign = other.sign;
    numberOfDigits = other.numberOfDigits;
    Digits = other.Digits;
}


bigNumber operator*(bigNumber &big1, bigNumber &big2) {
    bool s = false;
    if (big1.sign and big2.sign or !big1.sign and !big2.sign)
        s = true;

    int n1, n2;
    n1 = big1.numberOfDigits;
    n2 = big2.numberOfDigits;

    if (n1 > n2) {
        while (big1.numberOfDigits != big2.numberOfDigits) {
            big2.Digits = "0" + big2.Digits;
            big2.numberOfDigits++;
            n2++;
        }
    } else if (n1 < n2)
        while (big1.numberOfDigits != big2.numberOfDigits) {
            big1.Digits = "0" + big1.Digits;
            big1.numberOfDigits++;
            n1++;
        }
    if (big1.numberOfDigits == 1) {
        int ans = (big1.Digits[0] - '0') * (big2.Digits[0] - '0');
        return ans;
    }

    if (n1 % 2 == 1) {
        big2.numberOfDigits++;
        big1.numberOfDigits++;
        big1.Digits = "0" + big1.Digits;
        big2.Digits = "0" + big2.Digits;
    }

    string Al, Ar, Bl, Br;
    Al = big1.Digits.substr(0, big1.numberOfDigits / 2);
    Bl = big2.Digits.substr(0, big1.numberOfDigits / 2);
    Ar = big1.Digits.substr(big1.numberOfDigits / 2, big1.numberOfDigits);
    Br = big2.Digits.substr(big2.numberOfDigits / 2, big2.numberOfDigits);

    bigNumber al(Al, true);
    bigNumber bl(Bl, true);
    bigNumber p = al * bl;

    bigNumber ar(Ar, true);
    bigNumber br(Br, true);

    bigNumber q = ar * br;
    bigNumber r1 = Al + ar;
    bigNumber r2 = Bl + br;
    bigNumber r3 = p + q;
    bigNumber r = (r1 * r2) - r3;
    p = p.shiftL(big1.numberOfDigits);
    r = r.shiftL(big1.numberOfDigits / 2);

    bigNumber answer(p + q + r, s);

    remove_Zero(answer);
    return (answer);
}

void shiftL(bigNumber &big, int n) {
    int *temp = new int[big.numberOfDigits + n];
    for (int i = 0; i < big.numberOfDigits + n; ++i) {
        if (i >= big.numberOfDigits) {
            temp[i] = 0;
        } else
            temp[i] = big.Digits[i];
    }
    big.numberOfDigits += n;
}

bigNumber::bigNumber(const bigNumber &other, bool s) {
    sign = s;
    numberOfDigits = other.numberOfDigits;
    Digits = other.Digits;
}

bigNumber mult(bigNumber big1, bigNumber big2) {
    bigNumber *a = nullptr;
    bigNumber *b = nullptr;
    string *list = nullptr;
    bool Sign = false;
    if (big1.sign and big2.sign or !big1.sign and !big2.sign)
        Sign = true;
    if (big1 > big2) {
        a = &big1;
        b = &big2;
    } else {
        a = &big2;
        b = &big1;
    }
    int pro;
    int carry = 0;
    int j;
    list = new string[b->getNum()];

    for (int i = b->getNum() - 1; i >= 0; --i) {
        for (j = a->getNum() - 1; j >= 0; --j) {
            pro = (b->Digits[i] - '0') * (a->Digits[j] - '0') + carry;
            if (pro > 9) {
                list[i] = to_string(pro % 10) + list[i];
                carry = pro / 10;
            } else {
                list[i] = to_string(pro) + list[i];
                carry = 0;
            }
        }
        for (int k = 0; k < i; ++k) {
            list[k] = list[k] + "0";
        }
        if (j == -1 and carry != 0) {
            list[i] = to_string(carry) + list[i];
            carry = 0;
        }
    }
    bigNumber result = 0;
    for (int i = 0; i < b->getNum(); ++i) {
        result = list[i] + result;
    }
    return {result, Sign};
}


bigNumber operator/(const bigNumber &big1, const bigNumber &big2) {
    bool Sign = false;
    if (big1.sign and big2.sign or !big1.sign and !big2.sign)
        Sign = true;
    if (big2 > big1)
        return 0;
    if (big2.Digits == "0") {
        cout << "Indivisible by 0 .";
        return bigNumber("", true);
    }

    string a = big1.Digits;
    bigNumber b = big2.Digits;

    bool firstTime = true;
    bool firstTry = true;
    int num = 0;
    string result;
    string temp = "";
    int i = 0;
    for (; i < a.length();) {
        while (b > temp and i < a.length()) {
            if (firstTime)
                temp = temp + a[i];
            else if (!firstTry) {
                result = result + "0";
                temp = temp + a[i];
            } else {

                temp = temp + a[i];
                firstTry = false;
            }
            i++;
            removeZero(temp);
        }
        firstTry = true;
        int count = 0;
        while (temp[count] - '0' < 1 and count != temp.length() - 1)
            count++;
        if (count != result.length())
            temp.erase(0, count);
        bigNumber temp2(temp);
        while (temp2 >= b) {
            temp2 = temp2 - b;
            num++;
        }
        result = result + to_string(num);
        temp = "";
        if (temp2.Digits != "0") {
            temp = temp2.Digits + temp;
        }
        num = 0;
        firstTime = false;
    }
    return {result, Sign};
}

bigNumber::bigNumber(const string &str) {
    sign = true;
    numberOfDigits = str.length();
    Digits = str;
}


bool operator>=(const bigNumber &big1, const bigNumber &big2) {
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
    return true;
}

void remove_Zero(bigNumber &a) {
    int count = 0;
    while ((a.Digits[count] - '0' < 1 and count != a.numberOfDigits)) {
        ++count;
    }
    if (count == a.numberOfDigits) {
        a.Digits.erase(0, count - 1);
        a.numberOfDigits = 1;
    } else {
        a.Digits.erase(0, count);
        a.numberOfDigits = a.numberOfDigits - count;
    }
}

bigNumber power(bigNumber &big, int n) {
    if (n == 0)
        return 1;
    if (n == 1)
        return big;
    int i = 2;
    while (n % i != 0) {
        i++;
    }
    if (i == n and i != 2) {

        return power(big, n + 1) / big;
    } else {
        bigNumber temp = 1;
        for (int j = 0; j < i; ++j) {
            temp = mult(temp, big);
        }
        return power(temp, n / i);
    }
}

bigNumber fact(int n) {
    bigNumber res = 1;
    int i = 2;
    for (; n > i; i = i + 1) {
        res = mult(res, i);
    }
    return res;
}