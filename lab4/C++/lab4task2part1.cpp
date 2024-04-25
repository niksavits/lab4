#include <iostream>
#include <random>
#include <algorithm>
#include <array>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    const int n = 10; // Размер массива
    array<int, n> numbers; // Объявление массива

    // Инициализация генератора случайных чисел mt19937
    mt19937 generator(random_device{}());

    // Заполнение массива случайными числами из диапазона [10, 100]
    uniform_int_distribution<int> distribution(10, 100);
    for (int& number : numbers) {
        number = distribution(generator);
    }

    // Вывод сгенерированного массива
    cout << "Сгенерированный массив: ";
    for (const auto& elem : numbers) {
        cout << elem << " ";
    }
    cout << endl;

    // Поиск самой длинной последовательности чисел по убыванию
    int maxSequenceLength = 1; // Минимальная длина последовательности - 1
    int currentSequenceLength = 1;
    int startIndex = 0; // Индекс начала самой длинной последовательности
    int endIndex = 0; // Индекс конца самой длинной последовательности
    for (int i = 1; i < n; ++i) {
        if (numbers[i] < numbers[i - 1]) {
            ++currentSequenceLength;
            if (currentSequenceLength > maxSequenceLength) {
                maxSequenceLength = currentSequenceLength;
                startIndex = i - maxSequenceLength + 1; // Обновляем индекс начала
                endIndex = i; // Обновляем индекс конца
            }
        } else {
            currentSequenceLength = 1;
        }
    }

    // Вывод самой длинной последовательности чисел по убыванию
    cout << "Самая длинная последовательность чисел по убыванию: ";
    for (int i = startIndex; i <= endIndex; ++i) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    // Сортировка массива по убыванию
    sort(numbers.begin(), numbers.end(), greater<int>());

    // Поиск среднеарифметического значения
    double average = 0;
    for (const int& num : numbers) {
        average += num;
    }
    average /= n;

    // Инициализация нового массива, содержащего числа меньше среднеарифметического значения
    array<int, n> newArray;
    int newSize = 0;
    for (const int& num : numbers) {
        if (num < average) {
            newArray[newSize++] = num;
        }
    }

    // Вывод нового массива
    cout << "Новый массив, содержащий числа меньше среднеарифметического значения (" << average << "):\n";
    for (int i = 0; i < newSize; ++i) {
        cout << newArray[i] << " ";
    }
    cout << endl;

    return 0;
}
