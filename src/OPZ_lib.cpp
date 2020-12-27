#include <iostream>
#include <vector>

#include "OPZ_lib.h"

using namespace std;

bool is_number(char char_value) {
    if ((char_value >= '0') && (char_value <= '9'))
        return true;
    else
        return false;
}

bool is_operation(char char_value) {
    if ((char_value == '/') || (char_value == '*') || (char_value == '+')
        || (char_value == '-') || (char_value == '(') || (char_value == ')'))
        return true;
    else return false;
}

char get_priority(char a) {
    char priority;
    if (((int) a == 47) || ((int) a == 42))       // '/','*'
        priority = '3';
    else if (((int) a == 43) || ((int) a == 45))  // '+','-'
        priority = '2';
    else if (((int) a == 40) || ((int) a == 41))  // '(',')'
        priority = '1';
    return priority;
}

bool check_priority(char a, char b) {
    if ((get_priority(a)) >= (get_priority(b)))
        return true;
    else return false;
}

vector<char> write_in_vector(char *message) {
    vector<char> mes;
    char ch;
    int i = 0;
    while (message[i] != '\0') {
        if ((is_number(message[i])) || (is_operation(message[i]))) {
            mes.push_back(message[i]);
        } else throw logic_error("Неправильные входные данные!");
        i += 1;
    }
    return mes;
}

vector<char> StackAndOut(vector<char> mes) {
    vector<char> stack;
    vector<char> outline;

    for (int i = 0; i < mes.size(); ++i) {

        if (is_operation(mes[i])) {
            if ((mes[i] != ')') && (!stack.empty()) &&
                (check_priority(stack[stack.size() - 1], mes[i]))) { //меньше или равен текущему знаку
                if ((mes[i] != '(')) {
                    outline.push_back(stack[stack.size() - 1]);
                    stack.pop_back();
                }
                stack.push_back(mes[i]);
                continue;
            }
            if ((mes[i] != '(') && (mes[i] != ')')) {
                stack.push_back(mes[i]);
                continue;
            }
            if (mes[i] == '(') {
                stack.push_back(mes[i]);
                continue;
            }
            if (mes[i] == ')') {
                unsigned long j = stack.size() - 1;
                while (stack[j] != '(') {
                    outline.push_back(stack[j]);
                    stack.pop_back();
                    j--;
                }
                stack.pop_back();
                continue;
            }
        }

        if (is_number(mes[i]))
            outline.push_back(mes[i]);
    }

    int k = stack.size() - 1;
    while (k >= 0) {
        outline.push_back(stack[k]);
        stack.pop_back();
        k--;
    }
    return outline;
}

float calculate(vector<char> vec) {
    vector<float> stack;
    float result;

    for (int i = 0; i < vec.size(); ++i) {
        if (is_number(vec[i]))
            while (is_number(vec[i])) {
                stack.push_back(vec[i] - '0');
                ++i;
            }
        switch (vec[i]) {
            case '*':
                result = stack[stack.size() - 1];
                stack.pop_back();
                result = (stack[stack.size() - 1] * result);
                stack.pop_back();
                stack.push_back(result);
                break;
            case '/':
                result = stack[stack.size() - 1];
                stack.pop_back();
                result = (stack[stack.size() - 1] / result);
                stack.pop_back();
                stack.push_back(result);
                break;
            case '+':
                result = stack[stack.size() - 1];
                stack.pop_back();
                result = (stack[stack.size() - 1] + result);
                stack.pop_back();
                stack.push_back(result);
                break;
            case '-':
                result = stack[stack.size() - 1];
                stack.pop_back();
                result = (stack[stack.size() - 1] - result);
                stack.pop_back();
                stack.push_back(result);
                break;
        }

    }

    return stack[stack.size() - 1];
}