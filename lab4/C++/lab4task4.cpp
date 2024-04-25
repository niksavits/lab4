#include <iostream>
#include <random>
#include <array>

using namespace std;

// Функция для генерации случайного числа в диапазоне [min, max]
int getRandomNumber(int min, int max) {
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

// Алгоритм 1: Всегда сотрудничает
bool algorithm1(int round_number, const array<bool, 200>& self_choices, const array<bool, 200>& enemy_choices) {
    return true; // Всегда сотрудничаем
}

// Алгоритм 2: Предает каждый 4-й раунд
bool algorithm2(int round_number, const array<bool, 200>& self_choices, const array<bool, 200>& enemy_choices) {
    return round_number % 4 != 0; // Предаем каждый 4-й раунд
}

// Алгоритм 3: Имитирует предыдущее действие противника
bool algorithm3(int round_number, const array<bool, 200>& self_choices, const array<bool, 200>& enemy_choices) {
    if (round_number == 0) {
        return true; // В первом раунде всегда сотрудничаем
    } else {
        return enemy_choices[round_number - 1]; // Имитируем предыдущее действие противника
    }
}

// Функция для запуска игры
void playGame(bool (*algorithm1)(int, const array<bool, 200>&, const array<bool, 200>&),
              bool (*algorithm2)(int, const array<bool, 200>&, const array<bool, 200>&),
              bool (*algorithm3)(int, const array<bool, 200>&, const array<bool, 200>&)) {
    int num_rounds = getRandomNumber(100, 200); // Случайное количество раундов

    array<bool, 200> self_choices1; // Выборы первого алгоритма
    array<bool, 200> self_choices2; // Выборы второго алгоритма
    array<bool, 200> self_choices3; // Выборы третьего алгоритма

    array<bool, 200> enemy_choices1; // Выборы противника для первого алгоритма
    array<bool, 200> enemy_choices2; // Выборы противника для второго алгоритма
    array<bool, 200> enemy_choices3; // Выборы противника для третьего алгоритма

    int score1 = 0; // Очки первого алгоритма
    int score2 = 0; // Очки второго алгоритма
    int score3 = 0; // Очки третьего алгоритма

    for (int round = 0; round < num_rounds; ++round) {
        bool choice1 = algorithm1(round, self_choices1, enemy_choices1);
        bool choice2 = algorithm2(round, self_choices2, enemy_choices2);
        bool choice3 = algorithm3(round, self_choices3, enemy_choices3);

        self_choices1[round] = choice1;
        self_choices2[round] = choice2;
        self_choices3[round] = choice3;

        bool enemy_choice1 = algorithm3(round, enemy_choices1, self_choices1);
        bool enemy_choice2 = algorithm3(round, enemy_choices2, self_choices2);
        bool enemy_choice3 = algorithm3(round, enemy_choices3, self_choices3);

        enemy_choices1[round] = enemy_choice1;
        enemy_choices2[round] = enemy_choice2;
        enemy_choices3[round] = enemy_choice3;

        if (choice1 && enemy_choice1) {
            score1 += 24;
        } else if (!choice1 && enemy_choice1) {
            score1 += 20;
        } else if (!choice1 && !enemy_choice1) {
            score1 += 4;
        }

        if (choice2 && enemy_choice2) {
            score2 += 24;
        } else if (!choice2 && enemy_choice2) {
            score2 += 20;
        } else if (!choice2 && !enemy_choice2) {
            score2 += 4;
        }

        if (choice3 && enemy_choice3) {
            score3 += 24;
        } else if (!choice3 && enemy_choice3) {
            score3 += 20;
        } else if (!choice3 && !enemy_choice3) {
            score3 += 4;
        }
    }

    cout << "Результаты игры:\n";
    cout << "Алгоритм 1: " << score1 << " очков\n";
    cout << "Алгоритм 2: " << score2 << " очков\n";
    cout << "Алгоритм 3: " << score3 << " очков\n";
}

int main() {
    playGame(algorithm1, algorithm2, algorithm3);
    playGame(algorithm1, algorithm2, algorithm3);
    playGame(algorithm1, algorithm2, algorithm3);

    return 0;
}
