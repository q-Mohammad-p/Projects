#include <iostream>
#include <cmath>
#include "pbPlots.hpp"
#include "supportLib.hpp"
#include "stack.cpp"

using namespace std;


bool pre(char op_1, char op_2) {
    if (op_1 == op_2 and op_1 != '(')
        return false;
    if (op_1 == '*' and op_2 == '/' or op_1 == '/' and op_2 == '*')
        return false;
    if ((op_1 == '+' and op_2 == '-') or (op_1 == '-' and op_2 == '+'))
        return false;
    if ((op_1 == '*' or op_1 == '/') and (op_2 == '+' or op_2 == '-'))
        return true;
    if ((op_1 == '+' or op_1 == '-') and (op_2 == '*' or op_2 == '/'))
        return false;
    if ((op_1 == '^') and (op_2 == '*' or op_2 == '/' or op_2 == '+' or op_2 == '-'))
        return true;
    if ((op_2 == '^') and (op_1 == '*' or op_1 == '/' or op_1 == '+' or op_1 == '-'))
        return false;
    if ((op_1 == '+' or op_1 == '-' or op_1 == '*' or op_1 == '/' or op_1 == '^') and op_2 == '(')
        return true;
    else return true;
}


float parametric_post_calculator(string str, float value) {
    stack<float> s(str.length());
    int i = 0;
    string temp;
    while (i < str.length()) {
        if (str[i] == ' ') {
            if (temp.empty()) {
                i++;
                continue;
            }
            if (temp[0] == '~') {
                s.push(-1 * value);
            } else
                s.push(value);
            temp = "";
            i++;
        } else if (str[i] == '+' or str[i] == '-' or str[i] == '*' or str[i] == '/' or str[i] == '^') {
            float num1, num2;
            try {
                num1 = s.pop();
                num2 = s.pop();
            }
            catch (stack<float>::is_empty) {}
            if (str[i] == '+')
                s.push(num2 + num1);
            else if (str[i] == '-')
                s.push(num2 - num1);
            else if (str[i] == '*')
                s.push(num2 * num1);
            else if (str[i] == '/')
                s.push(num2 / num1);
            else if (str[i] == '^')
                s.push(pow(num2, num1));
            i++;
            temp = "";
        } else
            temp += str[i++];
    }
    return s.pop();
}


float to_float(string str) {
    int i = 0;
    float result = 0;
    int counter = 1;
    bool decimal = false;
    while (i < str.length()) {
        if (str[i] == '.') {
            decimal = true;
            i++;
            continue;
        }
        if (decimal)
            counter *= 10;
        result = result * 10 + (str[i] - '0');
        i++;
    }
    result = result / counter;
    return result;
}


float calculator_post(string str) {
    stack<float> s(str.length());
    int i = 0;
    string temp;
    while (i < str.length()) {
        if (str[i] == ' ') {
            if (temp.empty()) {
                i++;
                continue;
            }
            if (temp[0] == '~') {

                temp = temp.substr(1);
                s.push(-1 * to_float(temp));
            } else
                s.push(to_float(temp));
            temp = "";
            i++;
        } else if (str[i] == '+' or str[i] == '-' or str[i] == '*' or str[i] == '/' or str[i] == '^') {
            float num1, num2;
            try {
                num1 = s.pop();
                num2 = s.pop();
            }
            catch (stack<float>::is_empty) {

            }
//            cout << num1 << "  " << num2 << endl;
            if (str[i] == '+')
                s.push(num2 + num1);
            else if (str[i] == '-')
                s.push(num2 - num1);
            else if (str[i] == '*')
                s.push(num2 * num1);
            else if (str[i] == '/')
                s.push(num2 / num1);
            else if (str[i] == '^')
                s.push(pow(num2, num1));
            i++;
            temp = "";
        } else
            temp += str[i++];
    }
    return s.pop();
}


string convert_to_post(string str) {
    string result;
    string temp;
    stack<char> s(str.length());
    int i = 0;
    if (str[0] == '-') {
        result += "~";
        i++;
    }
    for (; i < str.length();) {
        if (str[i - 1] == '(' and str[i] == '-') {
            result += "~";
            i++;
        }
        while (str[i] != '+' and str[i] != '-' and str[i] != '*' and str[i] != '/' and str[i] != '(' and
               str[i] != ')' and str[i] != '^' and i < str.length()) {
            result += str[i++];
        }
        result += " ";
        if (str[i] == ')') {
            while (true) {

                char a;
                try {
                    a = s.pop();
                }
                catch (stack<char>::is_empty) {};
                if (a == '(') {
                    break;
                }
                result += a;
            }
            i++;
        } else if (s.isEmpty()) {
            s.push(str[i++]);

        } else if (pre(str[i], s.s[s.top])) {
            s.push(str[i++]);
        } else {

            while (!pre(str[i], s.s[s.top]))
                try {
                    result += s.pop();
                }
                catch (stack<char>::is_empty) {}
            s.push(str[i++]);
        }
    }
    while (!s.isEmpty()) {
        try {
            result += s.pop();
        }
        catch (stack<char>::is_empty) {}
    }
    cout << result << endl;
    return result;
}


float pre_claculator(string str) {
    stack<float> s(str.length());
    int i = str.length() - 1;
    string temp;
    while (i >= 0) {
        if (str[i] == ' ') {
            if (temp.empty()) {
                i--;
                continue;
            }
            if (temp[0] == '~') {
                temp = temp.substr(1);
                s.push(-1 * to_float(temp));
            } else
                s.push(to_float(temp));
            temp = "";
            i--;
        } else if (str[i] == '+' or str[i] == '-' or str[i] == '*' or str[i] == '/' or str[i] == '^') {
            float num1, num2;
            try {
                num1 = s.pop();
                num2 = s.pop();
            }
            catch (stack<float>::is_empty) {

            }
            if (str[i] == '+') {
                s.push(num1 + num2);
            } else if (str[i] == '-') {
                s.push(num1 - num2);
            } else if (str[i] == '*') {
                s.push(num1 * num2);
            } else if (str[i] == '/') {
                s.push(num1 / num2);
            } else if (str[i] == '^') {
                s.push(pow(num1, num2));
            }
            i--;
            temp = "";
        } else
            temp = str[i--] + temp;
    }
    return s.pop();
}


float parametric_pre_calculator(string str, float value) {
    stack<float> s(str.length());
    int i = str.length() - 1;
    string temp;
    while (i >= 0) {
        if (str[i] == ' ') {
            i--;
            continue;
        } else if (str[i] == '+' or str[i] == '-' or str[i] == '*' or str[i] == '/' or str[i] == '^') {
            float num1, num2;
            try {
                num1 = s.pop();
                num2 = s.pop();
            }
            catch (stack<float>::is_empty) {

            }
            if (str[i] == '+') {
                cout << num1 + num2 << endl;
                s.push(num1 + num2);
            } else if (str[i] == '-') {
                cout << num1 - num2 << endl;
                s.push(num1 - num2);
            } else if (str[i] == '*') {
                cout << num1 * num2 << endl;
                s.push(num1 * num2);
            } else if (str[i] == '/') {
                cout << num1 / num2 << endl;
                s.push(num1 / num2);
            } else if (str[i] == '^') {
                cout << pow(num1, num2) << endl;
                s.push(pow(num1, num2));
            }
            i--;
            temp = "";
        } else if (str[i - 1] == '~') {
            s.push(-value);
            i = i - 2;
        } else {
            s.push(value);
            i--;
        }
    }
    return s.pop();
}


void convert_to_pre(string str) {
    string result;
    stack<string> operand(str.length());
    stack<char> Operator(str.length());
    int i = 0;
    if (str[0] == '-') {
        result += "~";
        i++;
    }
    for (; i < str.length();) {

        if (str[i - 1] == '(' and str[i] == '-') {
            result += "~";
            i++;
        }

        while (str[i] != '+' and str[i] != '-' and str[i] != '*' and str[i] != '/' and str[i] != '(' and
               str[i] != ')' and str[i] != '^' and i < str.length()) {
            result += str[i++];
        }
        if (!result.empty()) {
            result += " ";
            operand.push(result);
            result = "";
        } else if (str[i] == ')') {
            while (true) {

                string a;
                string s1, s2, temp;
                try {
                    a = Operator.pop();
                    s1 = operand.pop();
                    s2 = operand.pop();
                }
                catch (stack<string>::is_empty) {};
                if (a == "(") {
                    operand.push(s2);
                    operand.push(s1);
                    break;
                }
                temp = a + " " + s2 + s1;
                operand.push(temp);
            }
            i++;
        } else if (Operator.isEmpty()) {
            Operator.push(str[i++]);
        } else if (pre(str[i], Operator.s[Operator.top])) {
            Operator.push(str[i++]);
        } else {
            while (!pre(str[i], Operator.s[Operator.top])) {
                string a;
                string s1, s2, temp;
                try {
                    a = Operator.pop();
                    s1 = operand.pop();
                    s2 = operand.pop();
                }
                catch (stack<string>::is_empty) {}
                catch (stack<char>::is_empty) {}
                temp = a + " " + s2 + s1;
                operand.push(temp);
            }
            Operator.push(str[i++]);
        }
    }
    while (!Operator.isEmpty()) {
        string a;
        string s1, s2, temp;
        try {
            a = Operator.pop();
            s1 = operand.pop();
            s2 = operand.pop();
        }
        catch (stack<string>::is_empty) {}
        catch (stack<char>::is_empty) {}
        temp = a + " " + s2 + s1;
        operand.push(temp);
    }
    string s = operand.pop();
    cout << s << endl;
}


int main() {

    string str;
    cout << "Enter an expression : ";
    cin >> str;
    cout << "Prefix : ";
    convert_to_pre(str);
    cout << endl << "Postfix : ";
    string result = convert_to_post(str);
    cout << endl;

    char parameter;
    float value;
    bool p = false;
    char q;
    for (int j = 0; j < str.length(); ++j) {
        if (str[j] >= 65 and str[j] <= 90) {
            parameter = str[j];
            p = true;
            break;
        }
    }

    if (p) {
        cout << "Do you want to draw a plot ? ";
        cin >> q;
        if (q == 'y') {
            cout << "Enter a bound : \n";
            int number1, number2;
            cout << "Number 1 : ";
            cin >> number1;
            cout << "Number 2 : ";
            cin >> number2;

            RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
            vector<double> x;
            vector<double> y;
            for (int i = number1; i <= number2; ++i) {
                x.push_back(i);
                y.push_back(parametric_post_calculator(result, i));
            }

            DrawScatterPlot(imageRef, 1920, 1080, &x, &y);

            vector<double> *pngData = ConvertToPNG(imageRef->image);
            WriteToFile(pngData, "plot_post.png");
            DeleteImage(imageRef->image);

        } else {
            cout << "enter the value of " << parameter << " : ";
            cin >> value;
            cout << parametric_post_calculator(result, value);
        }
    } else cout << calculator_post(result);
}