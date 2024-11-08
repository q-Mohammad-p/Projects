#include "bigNumber.cpp"

int main() {

    int arr1[] = {1, 0, 0, 4};


    bigNumber a("890000076540678965473237", true);
    bigNumber b("187000065", false);
//    cout<<a.getNum();
//    bigNumber a("50505", true);
//    bigNumber b("", true);
    string  t = "10";
//    cout<<(b >= t);
//    a.removeZero();
//    a.print();

//    bigNumber b(1);
//    b.shiftL(8);
//    b.print();

    bigNumber c(arr1, 4, true);


//    int count;
//    string n = "000000123456";
//    p(n);
//    while ((n[count] - '0') < 1) {
//
////        a.Digits = '0' - (a.Digits);
//        ++count;
//    }
//    n.erase(0, 0);
//cout<<n;
//    numberOfDigits -=count;
//    n+='0';
//    cout<<n[2];
//

//    a.shiftR().print();


    (a/10).print();cout<<endl<<endl;
//    dive(a,-10).print();
//    cout<<(a>=b);
//    mult(a,b).print();

//bigNumber *g = new bigNumber[2];
//    g[0] = 10000;
//    g[1]  = 123;
//    (g[0] + g[1]).print();
//a.print();cout<<endl;
//cout<<a.getDigits()<<endl;
//    (a*b).print();cout<<endl;
//cout<<a.getDigits()<<endl;
//a.print();cout<<endl;

//    fact(100).print();

//    karatsubaMultiply(a,b);

//    mult(a, b).print();

//    power(b, 70).print();

//    karatsubaMultiply(a,b).print();

//    bigNumber j()

//    bigNumber h (a, 0,8);

//    h.print();

//    bigNumber d = (a * b);


//    d.print();

}






//#include <iostream>
//#include <string>
//#include <algorithm>
//
//class bigNumber {
//public:
//    std::string Digits;
//    int numberOfDigits;
//
//    bigNumber() : Digits(""), numberOfDigits(0) {}
//
//    bigNumber(std::string digits, bool validate = false) {
//        if (validate) {
//            while (digits.size() > 1 && digits[0] == '0') {
//                digits.erase(0, 1);
//            }
//        }
//        Digits = digits;
//        numberOfDigits = Digits.size();
//    }
//
//    bigNumber shiftL(int positions) const {
//        return bigNumber(Digits + std::string(positions, '0'));
//    }
//
//    void removeZero() {
//        while (Digits.size() > 1 && Digits[0] == '0') {
//            Digits.erase(0, 1);
//        }
//        numberOfDigits = Digits.size();
//    }
//
//    bigNumber operator+(const bigNumber& other) const {
//        std::string result = "";
//        int carry = 0, i = numberOfDigits - 1, j = other.numberOfDigits - 1;
//        while (i >= 0 || j >= 0 || carry) {
//            int sum = carry;
//            if (i >= 0) sum += Digits[i--] - '0';
//            if (j >= 0) sum += other.Digits[j--] - '0';
//            result += (sum % 10) + '0';
//            carry = sum / 10;
//        }
//        std::reverse(result.begin(), result.end());
//        return bigNumber(result);
//    }
//
//    bigNumber operator-(const bigNumber& other) const {
//        std::string result = "";
//        int borrow = 0, i = numberOfDigits - 1, j = other.numberOfDigits - 1;
//        while (i >= 0 || j >= 0) {
//            int diff = Digits[i--] - '0' - borrow;
//            if (j >= 0) diff -= other.Digits[j--] - '0';
//            if (diff < 0) {
//                diff += 10;
//                borrow = 1;
//            } else {
//                borrow = 0;
//            }
//            result += diff + '0';
//        }
//        std::reverse(result.begin(), result.end());
//        return bigNumber(result, true);
//    }
//
//    friend bigNumber karatsubaMultiply(bigNumber, bigNumber);
//    friend std::ostream& operator<<(std::ostream&, const bigNumber&);
//};
//
//std::ostream& operator<<(std::ostream& os, const bigNumber& num) {
//    os << num.Digits;
//    return os;
//}
//
//bigNumber karatsubaMultiply(bigNumber big1, bigNumber big2) {
//    int n1 = big1.numberOfDigits;
//    int n2 = big2.numberOfDigits;
//
//    if (n1 != n2) {
//        int maxLength = std::max(n1, n2);
//        while (big1.numberOfDigits < maxLength) {
//            big1.Digits = "0" + big1.Digits;
//            big1.numberOfDigits++;
//        }
//        while (big2.numberOfDigits < maxLength) {
//            big2.Digits = "0" + big2.Digits;
//            big2.numberOfDigits++;
//        }
//    }
//
//    if (big1.numberOfDigits == 1) {
//        int ans = (big1.Digits[0] - '0') * (big2.Digits[0] - '0');
//        return bigNumber(std::to_string(ans));
//    }
//
//    if (n1 % 2 == 1) {
//        big1.Digits = "0" + big1.Digits;
//        big2.Digits = "0" + big2.Digits;
//        n1++;
//        n2++;
//        big1.numberOfDigits = n1;
//        big2.numberOfDigits = n2;
//    }
//
//    int splitPosition = n1 / 2;
//
//    std::string Al = big1.Digits.substr(0, splitPosition);
//    std::string Ar = big1.Digits.substr(splitPosition);
//    std::string Bl = big2.Digits.substr(0, splitPosition);
//    std::string Br = big2.Digits.substr(splitPosition);
//
//    bigNumber al(Al, true);
//    bigNumber ar(Ar, true);
//    bigNumber bl(Bl, true);
//    bigNumber br(Br, true);
//
//    bigNumber p = karatsubaMultiply(al, bl);
//    bigNumber q = karatsubaMultiply(ar, br);
//    bigNumber r1 = al + ar;
//    bigNumber r2 = bl + br;
//    bigNumber r3 = karatsubaMultiply(r1, r2);
//    bigNumber rr = (r3 - p - q);
//
//    bigNumber P = p.shiftL(n1);
//    bigNumber R = rr.shiftL(splitPosition);
//
//    bigNumber answer = P + q + R;
//    answer.removeZero();
//    return answer;
//}
//
//int main() {
//    bigNumber num1("12");
//    bigNumber num2("98");
//
//    bigNumber result = karatsubaMultiply(num1, num2);
//
//    std::cout << "Result: " << result << std::endl;
//
//    return 0;
//}
