#include <iostream>
#include <cmath>
#include "raylib.h"

using namespace std;

// Функция для нахождения середины между двумя точками
Vector2 GetMiddle(Vector2 p1, Vector2 p2) {
    return { (p1.x + p2.x) / 2.0f, (p1.y + p2.y) / 2.0f };
}

// Рекурсивная отрисовка: делим треугольник на 3 части
void DrawSierpinski(Vector2 top, Vector2 left, Vector2 right, int depth) {
    if (depth == 0) {
        // рисуем закрашенный треугольник
        // порядок точек против часовой стрелки
        DrawTriangle(top, left, right, DARKBLUE);
        return;
    }

    // Находим середины сторон
    Vector2 midLeft = GetMiddle(top, left);
    Vector2 midRight = GetMiddle(top, right);
    Vector2 midBottom = GetMiddle(left, right);

    // Рекурсивно рисуем три маленьких треугольника по углам
    DrawSierpinski(top, midLeft, midRight, depth - 1);      // Верхний
    DrawSierpinski(midLeft, left, midBottom, depth - 1);    // Левый нижний
    DrawSierpinski(midRight, midBottom, right, depth - 1);  // Правый нижний
}

int main() {
    int n;
    cout << "Введите глубину (n): ";
    cin >> n;

    const int screenWidth = 800;
    const int screenHeight = 800;

    // Инициализация окна
    InitWindow(screenWidth, screenHeight, "Треугольник Серпинского");
    SetTargetFPS(60);

    // Определяем вершины главного треугольника
    Vector2 p1 = { screenWidth / 2.0f, 50.0f };           // Верх
    Vector2 p2 = { 50.0f, screenHeight - 50.0f };         // Лево-низ
    Vector2 p3 = { screenWidth - 50.0f, screenHeight - 50.0f }; // Право-низ

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE); 

        // Отрисовка фрактала
        DrawSierpinski(p1, p2, p3, n);

        DrawText("Sierpinski Triangle", 10, 10, 20, GRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}