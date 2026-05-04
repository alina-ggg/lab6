#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Функция рекурсивно "вырезает" (заполняет пробелами) центральные треугольники
void punchHoles(vector<vector<char>>& grid, int x, int y, int size) {
    if (size <= 1) return;

    int newSize = size / 2;

    //Вырезаем перевернутый треугольник
    for (int i = 0; i < newSize; ++i) {
        // Ширина отверстия: максимальная на верхней строке (i=0), сужается книзу
        int holeWidth = 2 * (newSize - i) - 1;
        
        // Начальная координата x для выреза (чтобы отверстие было по центру)
        int startX = x - (newSize - i - 1);
        
        for (int j = 0; j < holeWidth; ++j) {
            grid[y + newSize + i][startX + j] = ' '; 
        }
    }

    // Рекурсивно обрабатываем три оставшихся угла
    punchHoles(grid, x, y, newSize);                     // Верхний
    punchHoles(grid, x - newSize, y + newSize, newSize); // Левый
    punchHoles(grid, x + newSize, y + newSize, newSize); // Правый
}

int main() {
    int n;
    cout << "Введите глубину (n): ";
    cin >> n;

    int size = pow(2, n);
    
    // 2.1 Инициализируем матрицу заполненным треугольником (символ '#')
    vector<vector<char>> grid(size, vector<char>(2 * size, ' '));
    for (int i = 0; i < size; ++i) {
        for (int j = size - 1 - i; j < size + i; ++j) {
            grid[i][j] = '#'; 
        }
    }

    // Вырезаем отверстия
    punchHoles(grid, size - 1, 0, size);

    // Вывод результата
    for (int i = 0; i < size; ++i) {
        // 1. Отступ слева (центрирование)
        for (int k = 0; k < size - i; ++k) {
            cout << " ";
        }
        
        // 2. Вывод содержимого матрицы
        for (int j = size - 1 - i; j < size + i; ++j) {
            cout << grid[i][j]; 
        }
        cout << endl;
    }
    
    return 0;
}