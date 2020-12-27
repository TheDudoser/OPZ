#include <iostream>
#include <vector>
#include "OPZ_lib.h"
#include <cstring>

using namespace std;

int main(int argc, char** argv) {
    //Необходимо реализовать:
    //считывание + проверка на запись (done)
    //запись на стек и вывод (done)
    //окончательный вывод (done)
    //тесты ()
    vector<char> mes;
    vector<char> stack;
    char *message = new char[500];
    //char message[] = "1+(2-3*4)/5";
    bool flag = true;
    for (int i = 0; i < argc && flag; i++) {
        if (!strcmp(argv[i], "dude"))
            flag = false;
    }

        if (flag)
            cout << "Введите арифметическое выражение:" << endl;
    cin >> message;

    try {
        mes = write_in_vector(message);
    } catch (std::logic_error & exception)
    {
        cout << exception.what() << endl;
    }

    /*
    for (int i = 0; i < mes.size(); ++i) {
        cout << mes[i];
    } */

    //cout << endl;

    stack = StackAndOut(mes);

    if (flag) {
        cout << "Запись в ОПЗ:" << endl;
        for (int i = 0; i < stack.size(); ++i) {
            cout << stack[i];
        }
    }

    if (flag)
        cout << "Результат выражения:" << endl;
    cout << '\n' << calculate(stack) << endl;

    //calculate
    // 1 + (4 - 7) * 3 / 2
    //вывод 33/2 + 1
    //стек

    return 0;
}
