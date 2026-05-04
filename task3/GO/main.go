package main

import (
	"fmt"
	"math"
	"strings"
)

// Функция для печати матрицы
func printMatrix(A [][]float64, B []float64) {
	for i := 0; i < len(A); i++ {
		for j := 0; j < len(A[i]); j++ {
			fmt.Printf("%12.4f", A[i][j])
		}
		fmt.Printf(" | %10.4f\n", B[i])
	}
}

// 1. Прямой метод (Гаусс)
func solveGauss(A [][]float64, B []float64) {
	n := len(A)
	fmt.Println("\n--- ПРЯМОЙ ХОД ---")
	for k := 0; k < n; k++ {
		// Поиск главного элемента
		maxRow := k
		for i := k + 1; i < n; i++ {
			if math.Abs(A[i][k]) > math.Abs(A[maxRow][k]) {
				maxRow = i
			}
		}
		// Перестановка
		A[k], A[maxRow] = A[maxRow], A[k]
		B[k], B[maxRow] = B[maxRow], B[k]

		// Исключение
		for i := k + 1; i < n; i++ {
			factor := A[i][k] / A[k][k]
			for j := k; j < n; j++ {
				A[i][j] -= factor * A[k][j]
			}
			B[i] -= factor * B[k]
		}
		fmt.Printf("После шага %d:\n", k+1)
		printMatrix(A, B)
	}

	fmt.Println("\n--- ОБРАТНЫЙ ХОД (Корни) ---")
	x := make([]float64, n)
	for i := n - 1; i >= 0; i-- {
		sum := 0.0
		for j := i + 1; j < n; j++ {
			sum += A[i][j] * x[j]
		}
		x[i] = (B[i] - sum) / A[i][i]
		fmt.Printf("x%d = %10.4f\n", i+1, x[i])
	}
}

// 2. Метод Зейделя
func solveSeidel(A [][]float64, B []float64, eps float64) {
	n := len(A)
	x := make([]float64, n)
	xOld := make([]float64, n)

	fmt.Println("\n--- ТАБЛИЦА ИТЕРАЦИЙ (Метод Зейделя) ---")

	// Вывод заголовка
	header := fmt.Sprintf("%-5s %12s %12s %12s %12s %15s", "N", "X1", "X2", "X3", "X4", "eps_n")
	fmt.Println(header)
	fmt.Println(strings.Repeat("-", len(header)))

	for iter := 1; iter < 100; iter++ {
		copy(xOld, x)
		for i := 0; i < n; i++ {
			sum := 0.0
			for j := 0; j < n; j++ {
				if i != j {
					sum += A[i][j] * x[j]
				}
			}
			x[i] = (B[i] - sum) / A[i][i]
		}

		maxDiff := 0.0
		for i := 0; i < n; i++ {
			diff := math.Abs(x[i] - xOld[i])
			if diff > maxDiff {
				maxDiff = diff
			}
		}

		// Вывод строки: строго фиксированная ширина
		fmt.Printf("%-5d %12.4f %12.4f %12.4f %12.4f %15.2e\n",
			iter, x[0], x[1], x[2], x[3], maxDiff)

		if maxDiff < eps {
			break
		}
	}
	fmt.Println(strings.Repeat("-", len(header)))
}

func main() {
	// Исходные данные (Вариант 8)
	A := [][]float64{
		{0.91, -0.04, 0.21, -1.16},
		{0.25, -1.23, -0.23, -0.09},
		{-0.21, -0.23, 0.8, -0.13},
		{0.15, -1.31, 0.06, -1.04},
	}
	B := []float64{-1.24, -1.04, 2.56, 0.91}

	solveGauss(A, B)

	Acan := [][]float64{
		{0.91, -0.04, 0.21, -1.16},
		{0.25, -1.23, -0.23, -0.09},
		{-0.21, -0.23, 0.8, -0.13},
		{0.15, -1.31, 0.06, -1.04},
	}
	Bcan := []float64{-1.24, -1.04, 2.56, 0.91}

	solveSeidel(Acan, Bcan, 0.001)
}
