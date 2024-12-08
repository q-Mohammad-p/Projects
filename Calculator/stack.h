#ifndef CALCULATOR_STACK_H
#define CALCULATOR_STACK_H


#include<iostream>

using namespace std;

template<class T>
class stack {
private:
    int size;
public:
    T *s;
    int top;

    explicit stack(int n) : s(new T[n]), size(n), top(-1) {}

    stack() : s(new T[1]), size(0), top(-1) {}

    class is_empty {
    };

    void push(T element);

    T pop();

    bool isEmpty();
};

#endif
