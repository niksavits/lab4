#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    const int n = 5; // Размер массива
    vector<char> chars(n); // Объявление вектора символов

    // Инициализация генератора случайных чисел mt19937
    mt19937 generator(random_device{}());

    // Генерация случайных символов (буквы и цифры)
    uniform_int_distribution<int> distribution(48, 90);
    for (char& c : chars) {
        c = static_cast<char>(distribution(generator));
    }

    // Вывод исходного массива
    cout << "Исходный массив: [";
    for (const char& c : chars) {
        cout << c;
        if (&c != &chars.back()) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    // Модификация массива
    rotate(chars.begin(), chars.begin() + 2, chars.end());

    // Вывод модифицированного массива
    cout << "Модифицированный массив: [";
    for (const char& c : chars) {
        cout << c;
        if (&c != &chars.back()) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    return 0;
}
