#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Функция для вывода матрицы
void printMatrix(const vector<vector<double>>& A, const vector<double>& B) {
    for (size_t i = 0; i < A.size(); i++) {
        for (size_t j = 0; j < A[i].size(); j++) 
            cout << setw(10) << fixed << setprecision(4) << A[i][j] << " ";
        cout << "| " << B[i] << endl;
    }
}

// 1. Прямой метод (Гаусс)
void solveGauss(vector<vector<double>> A, vector<double> B) {
    int n = A.size();
    cout << "ПРЯМОЙ ХОД" << endl;
    for (int k = 0; k < n; k++) {
        int maxRow = k;
        for (int i = k + 1; i < n; i++)
            if (abs(A[i][k]) > abs(A[maxRow][k])) maxRow = i;
        swap(A[k], A[maxRow]);
        swap(B[k], B[maxRow]);

        for (int i = k + 1; i < n; i++) {
            double factor = A[i][k] / A[k][k];
            for (int j = k; j < n; j++) A[i][j] -= factor * A[k][j];
            B[i] -= factor * B[k];
        }
        cout << "После шага " << k + 1 << ":" << endl;
        printMatrix(A, B);
    }

    cout << "\nОБРАТНЫЙ ХОД (Корни)" << endl;
    vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++) sum += A[i][j] * x[j];
        x[i] = (B[i] - sum) / A[i][i];
        cout << "x" << i + 1 << " = " << x[i] << endl;
    }
}

// 2. Метод Зейделя
void solveSeidel(vector<vector<double>> A, vector<double> B, double eps) {
    int n = A.size();
    vector<double> x(n, 0.0);
    vector<double> x_old(n);
    
    cout << "\nТАБЛИЦА ИТЕРАЦИЙ (Метод Зейделя)" << endl;
    cout << setw(5) << "N" << setw(10) << "X1" << setw(10) << "X2" << setw(10) << "X3" 
         << setw(10) << "X4" << setw(15) << "eps_n" << endl;

    for (int iter = 1; iter < 100; iter++) {
        x_old = x;
        for (int i = 0; i < n; i++) {
            double sum = 0;
            for (int j = 0; j < n; j++) if (i != j) sum += A[i][j] * x[j];
            x[i] = (B[i] - sum) / A[i][i];
        }

        double max_diff = 0;
        for (int i = 0; i < n; i++) max_diff = max(max_diff, abs(x[i] - x_old[i]));
        
        cout << setw(5) << iter;
        for (double val : x) cout << setw(10) << fixed << setprecision(4) << val;
        cout << setw(15) << scientific << setprecision(2) << max_diff << endl;

        if (max_diff < eps) break;
    }
}

int main() {
    // исходная матрица
    vector<vector<double>> A = {
        {0.91, -0.04, 0.21, -1.16},
        {0.25, -1.23, -0.23, -0.09},
        {-0.21, -0.23, 0.8, -0.13},
        {0.15, -1.31, 0.06, -1.04}
    };
    vector<double> B = {-1.24, -1.04, 2.56, 0.91};

    // Выполняем Гаусса
    solveGauss(A, B);
    
    // Канонический вид для сходимости Зейделя
    vector<vector<double>> A_can = {
        {0.91, -0.04, 0.21, -1.16}, 
        {0.25, -1.23, -0.23, -0.09},
        {-0.21, -0.23, 0.8, -0.13},  
        {0.15, -1.31, 0.06, -1.04}   
    };
    vector<double> B_can = {-1.24, -1.04, 2.56, 0.91};

    solveSeidel(A_can, B_can, 0.001);

    return 0;
}