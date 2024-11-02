#include "bigNumber.cpp"

int main() {

    int arr1[] = {1, 0, 0, 4};


    bigNumber a("123456789", true);

    bigNumber b(123456788);

    bigNumber c(arr1, 4, true);

    bigNumber d = a + b + c;

    d.print();

}