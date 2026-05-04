#include "matrix.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <limits>

// Функция для безопасного ввода с проверкой
int getValidSize(int min, int max, const string& name) {
    int val;
    while (true) {
        cout << "Введите " << name << " (" << min << "-" << max << "): ";
        if (cin >> val && val >= min && val <= max) {
            return val;
        } else {
            cout << "Ошибка ввода! Введите число от " << min << " до " << max << "." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Функция для вывода матрицы
void printMatrix(const vector<vector<int>>& mat) {
    for (const auto& row : mat) {
        for (int val : row) cout << setw(5) << val << " ";
        cout << endl;
    }
}

// Задание 1
void task1() {
    int m = getValidSize(6, 20, "m");
    int n = getValidSize(6, 20, "n");
    vector<vector<int>> matrix(m, vector<int>(n));

    int maxLen = 0, bestRow = -1;
    vector<int> bestSeq;

    for (int i = 0; i < m; ++i) {
        int currentLen = 1;
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = -50 + rand() % 101;
            if (j > 0 && matrix[i][j] > matrix[i][j-1]) currentLen++;
            else currentLen = 1;

            if (currentLen > maxLen) {
                maxLen = currentLen;
                bestRow = i;
                bestSeq.assign(matrix[i].begin() + (j - currentLen + 1), matrix[i].begin() + j + 1);
            }
        }
    }
    cout << "Строка: " << bestRow << ", Длина: " << maxLen << "\nМассив: ";
    for (int val : bestSeq) cout << val << " ";
    cout << endl;
}

// Задание 2
void task2() {
    int m = getValidSize(6, 20, "m");
    vector<vector<int>> matrix(m, vector<int>(m));
    double sumEvenCols = 0, sumOddRows = 0;
    int countEvenCols = 0, countOddRows = 0;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = 100 + rand() % 101;
            if (j % 2 != 0) { sumEvenCols += matrix[i][j]; countEvenCols++; }
            if (i % 2 == 0) { sumOddRows += matrix[i][j]; countOddRows++; }
        }
    }
    cout << "Ср. арифм. четных столбцов: " << sumEvenCols/countEvenCols
         << ", нечетных строк: " << sumOddRows/countOddRows << endl;
    
    cout << "Матрица до сортировки:" << endl;
    printMatrix(matrix);

    vector<int> diag;
    for (int i = 0; i < m; ++i) diag.push_back(matrix[i][i]);
    if (sumEvenCols/countEvenCols > sumOddRows/countOddRows) sort(diag.rbegin(), diag.rend());
    else sort(diag.begin(), diag.end());

    for (int i = 0; i < m; ++i) matrix[i][i] = diag[i];
    cout << "Матрица после сортировки:" << endl;
    printMatrix(matrix);
}

// Вспомогательная функция поиска слова
bool dfs(vector<vector<char>>& mat, const string& word, int i, int j, int idx, vector<vector<bool>>& vis) {
    if (idx == word.size()) return true;
    if (i < 0 || i >= mat.size() || j < 0 || j >= mat[0].size() || vis[i][j] || mat[i][j] != word[idx]) return false;
    vis[i][j] = true;
    if (dfs(mat, word, i+1, j, idx+1, vis) || dfs(mat, word, i-1, j, idx+1, vis) ||
        dfs(mat, word, i, j+1, idx+1, vis) || dfs(mat, word, i, j-1, idx+1, vis)) return true;
    vis[i][j] = false;
    return false;
}

// Задание 3
void task3() {
    int m = getValidSize(5, 10, "m");
    int n = getValidSize(5, 10, "n");
    string word;
    cout << "Введите слово: ";
    cin >> word;
    vector<vector<char>> matrix(m, vector<char>(n));
    for (auto &row : matrix) for (char &c : row) c = 'A' + rand() % 26;

    vector<vector<bool>> vis(m, vector<bool>(n, false));
    bool found = false;
    for (int i = 0; i < m && !found; ++i)
        for (int j = 0; j < n && !found; ++j)
            if(dfs(matrix, word, i, j, 0, vis)) found = true;

    cout << (found ? "true" : "false") << endl;
}