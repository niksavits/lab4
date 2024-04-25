use std::f64::consts::PI;

const EPSILON: f64 = 1e-4; // Точность

// Уравнение
fn f(x: f64) -> f64 {
    (x.cos() - (x - 1.0).powi(2))
}

// Производная уравнения для метода Ньютона
fn df(x: f64) -> f64 {
    (-x.sin() - 2.0 * (x - 1.0)) // Производная от cos(x) - (x - 1)^2
}

// Функция phi(x) для метода простых итераций
fn phi(x: f64) -> f64 {
    x - f(x) / df(x) // Пересмотренная функция phi(x)
}

// Метод половинного деления
fn bisection_method(mut a: f64, mut b: f64, epsilon: f64) {
    let mut iter = 0; // Счётчик итераций

    // Вывод заголовка таблицы
    println!("Bisection method:");
    println!("{:<5} {:<15} {:<15} {:<15} {:<15}", "Iter", "an", "bn", "bn - an", "f(c)");

    // Цикл метода половинного деления
    while (b - a) >= epsilon {
        iter += 1;
        let c = (a + b) / 2.0; // Находим середину интервала
        let fc = f(c); // Значение функции в середине

        // Выводим значения в текущей итерации
        println!("{:<5} {:<15} {:<15} {:<15} {:<15}", iter, a, b, b - a, fc);

        // Переопределение интервала в зависимости от знака функции в середине
        if f(a) * fc < 0.0 {
            b = c; // Корень находится в левой половине интервала
        } else {
            a = c; // Корень находится в правой половине интервала
        }
    }

    // Вывод найденного корня
    println!("Root found by bisection method: {}", (a + b) / 2.0);
}

// Метод Ньютона
fn newton_method(mut x: f64, epsilon: f64) {
    let mut iter = 0; // Счётчик итераций

    // Вывод заголовка таблицы
    println!("Newton's method:");
    println!("{:<5} {:<15} {:<15} {:<15}", "Iter", "xn", "xn+1", "xn+1 - xn");

    // Цикл метода Ньютона
    loop {
        let h = f(x) / df(x); // Вычисление h
        let x_next = x - h; // Вычисление следующего значения x
        iter += 1; // Увеличение счётчика итераций

        // Вывод значений в текущей итерации
        println!("{:<5} {:<15} {:<15} {:<15}", iter, x, x_next, (x_next - x).abs());

        x = x_next; // Обновление текущего значения x

        // Проверка условия выхода из цикла
        if h.abs() < epsilon {
            break; // Выход из цикла, если достигнута заданная точность
        }
    }

    // Вывод найденного корня
    println!("Root found by Newton's method: {}", x);
}

// Метод простых итераций
fn simple_iteration_method(mut x: f64, epsilon: f64) {
    let mut iter = 0; // Счётчик итераций

    // Вывод заголовка таблицы
    println!("Simple iteration method:");
    println!("{:<5} {:<15} {:<15} {:<15}", "Iter", "xn", "xn+1", "|xn+1 - xn|");

    // Цикл метода простых итераций
    loop {
        let x_next = phi(x); // Вычисление следующего значения x
        iter += 1; // Увеличение счётчика итераций

        // Вывод значений в текущей итерации
        println!("{:<5} {:<15} {:<15} {:<15}", iter, x, x_next, (x_next - x).abs());

        // Проверка условия выхода из цикла
        if (x_next - x).abs() < epsilon {
            break; // Выход из цикла, если достигнута заданная точность
        }

        x = x_next; // Обновление текущего значения x
    }

    // Вывод найденного корня
    println!("Root found by simple iteration method: {}", x);
}

fn main() {
    let a = 0.0;
    let b = 3.0; // Начальные границы интервала
    let x0 = 1.5; // Начальное приближение

    println!("Choose a method to solve the equation:");
    println!("1. Bisection method");
    println!("2. Newton's method");
    println!("3. Simple iteration method");
    print!("Enter the number of the method: ");
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).expect("Failed to read input");
    let method: u32 = input.trim().parse().expect("Invalid input");

    match method {
        1 => bisection_method(a, b, EPSILON),
        2 => newton_method(x0, EPSILON),
        3 => simple_iteration_method(x0, EPSILON),
        _ => println!("Invalid input. Please enter a number between 1 and 3."),
    }
}