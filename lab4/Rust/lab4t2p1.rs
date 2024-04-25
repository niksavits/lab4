use std::io;
use rand::{Rng, SeedableRng};
use rand::distributions::Uniform;
use rand::rngs::StdRng;

fn main() {
    const N: usize = 10; // Размер массива
    let mut numbers = [0; N]; // Объявление массива

    // Инициализация генератора случайных чисел StdRng
    let mut rng: StdRng = SeedableRng::from_entropy();

    // Заполнение массива случайными числами из диапазона [10, 100]
    let distribution = Uniform::new_inclusive(10, 100);
    for number in numbers.iter_mut() {
        *number = rng.sample(distribution);
    }

    // Вывод сгенерированного массива
    println!("Сгенерированный массив: {:?}", numbers);

    // Поиск самой длинной последовательности чисел по убыванию
    let (mut max_sequence_length, mut current_sequence_length, mut start_index, mut end_index) = (1, 1, 0, 0);
    for i in 1..N {
        if numbers[i] < numbers[i - 1] {
            current_sequence_length += 1;
            if current_sequence_length > max_sequence_length {
                max_sequence_length = current_sequence_length;
                start_index = i - max_sequence_length + 1; // Обновляем индекс начала
                end_index = i; // Обновляем индекс конца
            }
        } else {
            current_sequence_length = 1;
        }
    }

    // Вывод самой длинной последовательности чисел по убыванию
    println!("Самая длинная последовательность чисел по убыванию: {:?}", &numbers[start_index..=end_index]);

    // Сортировка массива по убыванию
    numbers.sort_by(|a, b| b.cmp(a));

    // Поиск среднеарифметического значения
    let average: f64 = numbers.iter().sum::<i32>() as f64 / N as f64;

    // Инициализация нового массива, содержащего числа меньше среднеарифметического значения
    let mut new_array = [0; N];
    let mut new_size = 0;
    for &num in &numbers {
        if num < average as i32 {
            new_array[new_size] = num;
            new_size += 1;
        }
    }

    // Вывод нового массива
    println!("Новый массив, содержащий числа меньше среднеарифметического значения ({:.2}): {:?}", average, &new_array[..new_size]);
}
