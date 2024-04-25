#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPSILON = 1e-4; // Точность

// Уравнение
double f(double x) {
    return cos(x) - pow(x - 1, 2);
}

// Производная уравнения для метода Ньютона
double df(double x) {
    return -sin(x) - 2 * (x - 1); // Производная от cos(x) - (x - 1)^2
}

// Функция phi(x) для метода простых итераций
double phi(double x) {
    return x - f(x) / df(x); // Пересмотренная функция phi(x)
}

// Метод половинного деления
void bisectionMethod(double a, double b, double epsilon) {
    double c, fa, fc; // Переменные для хранения значений функции на концах интервала и в середине
    int iter = 0; // Счётчик итераций

    // Вывод заголовка таблицы
    cout << "Bisection method:" << endl;
    cout << setw(5) << "Iter" << setw(15) << "an" << setw(15) << "bn" << setw(15) << "bn - an" << setw(15) << "f(c)" << endl;

    // Цикл метода половинного деления
    while ((b - a) >= epsilon) {
        iter++;
        c = (a + b) / 2; // Находим середину интервала
        fa = f(a); // Значение функции на левом конце
        fc = f(c); // Значение функции в середине

        // Выводим значения в текущей итерации
        cout << setw(5) << iter << setw(15) << a << setw(15) << b << setw(15) << b - a << setw(15) << fc << endl;

        // Переопределение интервала в зависимости от знака функции в середине
        if (fa * fc < 0)
            b = c; // Корень находится в левой половине интервала
        else
            a = c; // Корень находится в правой половине интервала
    }

    // Вывод найденного корня
    cout << "Root found by bisection method: " << c << endl;
}

// Метод Ньютона
void newtonMethod(double x, double epsilon) {
    double h; // Инициализация h
    int iter = 0; // Счётчик итераций

    // Вывод заголовка таблицы
    cout << "Newton's method:" << endl;
    cout << setw(5) << "Iter" << setw(15) << "xn" << setw(15) << "xn+1" << setw(15) << "xn+1 - xn" << endl;

    // Цикл метода Ньютона
    while (true) {
        h = f(x) / df(x); // Вычисление h
        double x_next = x - h; // Вычисление следующего значения x
        iter++; // Увеличение счётчика итераций

        // Вывод значений в текущей итерации
        cout << setw(5) << iter << setw(15) << x << setw(15) << x_next << setw(15) << abs(x_next - x) << endl;

        x = x_next; // Обновление текущего значения x

        // Проверка условия выхода из цикла
        if (abs(h) < epsilon) {
            break; // Выход из цикла, если достигнута заданная точность
        }
    }

    // Вывод найденного корня
    cout << "Root found by Newton's method: " << x << endl;
}

// Метод простых итераций
void simpleIterationMethod(double x, double epsilon) {
    int iter = 0; // Счётчик итераций
    double x_next; // Объявляем x_next здесь

    // Вывод заголовка таблицы
    cout << "Simple iteration method:" << endl;
    cout << setw(5) << "Iter" << setw(15) << "xn" << setw(15) << "xn+1" << setw(15) << "|xn+1 - xn|" << endl;

    // Цикл метода простых итераций
    while (true) {
        x_next = phi(x); // Вычисление следующего значения x
        iter++; // Увеличение счётчика итераций

        // Вывод значений в текущей итерации
        cout << setw(5) << iter << setw(15) << x << setw(15) << x_next << setw(15) << abs(x_next - x) << endl;

        // Проверка условия выхода из цикла
        if (abs(x_next - x) < epsilon) {
            break; // Выход из цикла, если достигнута заданная точность
        }

        x = x_next; // Обновление текущего значения x
    }

    // Вывод найденного корня
    cout << "Root found by simple iteration method: " << x_next << endl;
}

int main() {
    double a = 0.0, b = 3.0; // Начальные границы интервала
    double x0 = 1.5; // Начальное приближение
    int method;

    cout << "Choose a method to solve the equation:" << endl;
    cout << "1. Bisection method" << endl;
    cout << "2. Newton's method" << endl;
    cout << "3. Simple iteration method" << endl;
    cout << "Enter the number of the method: ";
    cin >> method;

    switch (method) {
        case 1:
            bisectionMethod(a, b, EPSILON);
            break;
        case 2:
            newtonMethod(x0, EPSILON);
            break;
        case 3:
            simpleIterationMethod(x0, EPSILON);
            break;
        default:
            cout << "Invalid input. Please enter a number between 1 and 3." << endl;
    }
    return 0;
}
