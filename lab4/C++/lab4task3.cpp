#include <iostream>
#include <random>
#include <array>
#include <cmath>
#define M_PI 3.1415926

using namespace std;

// ‘ункци€ дл€ вычислени€ критери€ хи-квадрат
double chiSquareTest(const array<int, 100>& observed, const array<double, 100>& expected) {
    double chiSquare = 0;
    for (int i = 0; i < 100; ++i) {
        if (expected[i] != 0) {
            chiSquare += pow(observed[i] - expected[i], 2) / expected[i];
        }
    }
    return chiSquare;
}

// ‘ункци€ дл€ вычислени€ ожидаемых частот при нормальном распределении
array<double, 100> computeExpected(int n, double mean, double stddev) {
    array<double, 100> expected;
    for (int i = 1; i <= 100; ++i) {
        double z = (i - mean) / stddev;
        expected[i - 1] = n * (exp(-z * z / 2) / (sqrt(2 * M_PI) * stddev));
    }
    return expected;
}

int main() {
    const int n1 = 50; // –азмер первого массива
    const int n2 = 100; // –азмер второго массива
    const int n3 = 1000; // –азмер третьего массива

    array<int, 100> observed1 = {}; // ћассив дл€ хранени€ частот значений в первом массиве
    array<int, 100> observed2 = {}; // ћассив дл€ хранени€ частот значений во втором массиве
    array<int, 100> observed3 = {}; // ћассив дл€ хранени€ частот значений в третьем массиве

    // »нициализаци€ генератора случайных чисел mt19937
    mt19937 generator(random_device{}());

    // «адание параметров нормального распределени€
    double mean = 50.5;
    double stddev = sqrt(1000.0 / 12.0);

    // «аполнение первого массива случайными числами
    for (int i = 0; i < n1; ++i) {
        normal_distribution<double> distribution(mean, stddev);
        int randomNumber = round(distribution(generator));
        if (randomNumber >= 1 && randomNumber <= 100) {
            observed1[randomNumber - 1]++;
        }
    }

    // «аполнение второго массива случайными числами
    for (int i = 0; i < n2; ++i) {
        normal_distribution<double> distribution(mean, stddev);
        int randomNumber = round(distribution(generator));
        if (randomNumber >= 1 && randomNumber <= 100) {
            observed2[randomNumber - 1]++;
        }
    }

    // «аполнение третьего массива случайными числами
    for (int i = 0; i < n3; ++i) {
        normal_distribution<double> distribution(mean, stddev);
        int randomNumber = round(distribution(generator));
        if (randomNumber >= 1 && randomNumber <= 100) {
            observed3[randomNumber - 1]++;
        }
    }

    // ¬ычисление ожидаемых частот при нормальном распределении
    array<double, 100> expected = computeExpected(n1 + n2 + n3, mean, stddev);

    // ¬ычисление критери€ хи-квадрат дл€ каждого массива
    double chiSquare1 = chiSquareTest(observed1, expected);
    double chiSquare2 = chiSquareTest(observed2, expected);
    double chiSquare3 = chiSquareTest(observed3, expected);

    // ¬ывод результатов
    cout << "–езультаты критери€ хи-квадрат:\n";
    cout << "ћассив размером 50: " << (chiSquare1 < 124.342 ? "√ипотеза о нормальном распределении принимаетс€" : "√ипотеза о нормальном распределении отклон€етс€") << endl;
    cout << "ћассив размером 100: " << (chiSquare2 < 132.245 ? "√ипотеза о нормальном распределении принимаетс€" : "√ипотеза о нормальном распределении отклон€етс€") << endl;
    cout << "ћассив размером 1000: " << (chiSquare3 < 138.993 ? "√ипотеза о нормальном распределении принимаетс€" : "√ипотеза о нормальном распределении отклон€етс€") << endl;

    return 0;
}
