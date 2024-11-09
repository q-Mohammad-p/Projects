#include "bigNumber.cpp"

int main() {

    bigNumber a("89000007654067896547", true);
    bigNumber b("187000065", false);


    (a+b).print();cout<<endl;
    (a*b).print();cout<<endl;
    (a/b).print();cout<<endl;
    power(b,10).print();cout<<endl;
    mult(a,b).print();
}