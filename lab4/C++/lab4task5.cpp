#include <iostream>
#include <cstdint>
#include <ctime> // Для использования функции time()

// Функция для генерации следующего случайного числа
uint32_t next(uint32_t& state) {
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

int main() {
    // Используем текущее время в качестве зерна для генератора
    uint32_t seed = static_cast<uint32_t>(time(nullptr));

    // Генерация и вывод нескольких случайных чисел
    for (uint32_t random_number : {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) {
        seed = next(seed);
        std::cout << "Random number " << random_number << ": " << seed << std::endl;
    }

    return 0;
}
