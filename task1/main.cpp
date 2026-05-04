#include "matrix.h"
#include <ctime>
#include <iostream>

int main() {
    srand(static_cast<unsigned>(time(0)));

    cout << "--- Задание 1 ---" << endl;
    task1();
    cout << "\n--- Задание 2 ---" << endl;
    task2();
    cout << "\n--- Задание 3 ---" << endl;
    task3();
    
    return 0;
}