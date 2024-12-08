#include "stack.h"

template<class T>
void stack<T>::push(T element) {
    if (top + 1 == size) {
        cout << "Stack is full.";
        return;
    }
    s[top + 1] = element;
    top++;
};

template<class T>
T stack<T>::pop() {
    if (top == -1) {
        cout << "Stack is empty ." << endl;
        throw is_empty();
    }
    return s[top--];
};

template<class T>
bool stack<T>::isEmpty() {
    if (top == -1)
        return true;
    else
        return false;
}