#include "matrix.h"
#include <ctime>
#include <iostream>

int main() {
    srand(static_cast<unsigned>(time(0)));

    cout << "Задание 1" << endl;
    task1();
    cout << "\nЗадание 2" << endl;
    task2();
    cout << "\nЗадание 3" << endl;
    task3();
    
    return 0;
}