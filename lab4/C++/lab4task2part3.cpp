#include <iostream>
#include <random>
#include <algorithm>
#include <array>
#include <map>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    const int n = 20; // Размер массива
    array<int, n> numbers; // Объявление массива

    // Инициализация генератора случайных чисел mt19937
    mt19937 generator(random_device{}());

    // Заполнение массива случайными числами из диапазона [100, 900]
    uniform_int_distribution<int> distribution(100, 900);
    for (int& number : numbers) {
        number = distribution(generator);
    }

    // Сортировка массива по убыванию
    sort(numbers.begin(), numbers.end(), greater<int>());

    // Определение, сколько раз каждая цифра встречается в элементах массива
    map<int, int> digitCount; // Счетчик цифр

    for (const auto& number : numbers) {
        int num = number;
        while (num > 0) {
            int digit = num % 10; // Получаем последнюю цифру числа
            digitCount[digit]++; // Увеличиваем счетчик для этой цифры
            num /= 10; // Убираем последнюю цифру из числа
        }
    }
    for (const auto& elem : numbers) {
        cout << elem << " ";
    }

    cout << endl;

    // Вывод количества встреч каждой цифры
    cout << "Количество встреч каждой цифры в отсортированном массиве:\n";
    for (const auto& pair : digitCount) {
        cout << "Цифра " << pair.first << ": " << pair.second << " раз\n";
    }

    return 0;
}
