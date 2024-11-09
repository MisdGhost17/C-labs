#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <windows.h>

// Определение функций для счета 1 и 2
double calculate_with_epsilon(double epsilon, double x);
double calculate_with_max_n(int n, double x);

//Проверка валидно ли double float число(не целое число, значение с плавающей точкой)
bool isValidDoubleNumber(double num);

int main() {
    // меняем кодировку, чтобы отображался русский язык в консоли
    SetConsoleOutputCP(CP_UTF8);
    //создание переменной
    int choice; // для выбора
    double x; // для x

    //получаем x и проверяем его на валидность (|x| < 1)
    printf("Введите значение x:\n");
    scanf("%lf", &x);
    if (!isValidDoubleNumber(x) || x <= -1 || x >= 1 ) {
        printf("Некорректный ввод для x. |x| < 1\n");
        return 1;
    }

    //получаем выбор
    printf("Выберите метод вычисления:\n");
    printf("1. С точностью\n");
    printf("2. Для заданного количества членов ряда\n");
    printf("Выбор:\n");
    scanf("%d", &choice);

    switch (choice)
    {
        //для вычисления arcsin с заданной точностью
        case 1:
            double e; //переменная для точности
            printf("Введите точность:\n");
            scanf("%lf", &e); //получаем точность и проверяем её на валидность
            if (e <= 0 || !isValidDoubleNumber(e)) {
                printf("Неверный ввод точности.");
                return 1;
            }
            //получаем результат после вызова функции и выводим его
            double res1 = calculate_with_epsilon(e, x);
            printf("arcsin(%lf) = %lf c точностью %lf\n", x, res1, e);
            return 1;
        //для вычисления arcsin с максимальным количеством членов ряда
        case 2:
            int max_n; //переменная для максимального количества членов ряда
            //получаем максимальное количество членов ряда
            printf("Введите максимальное число членов ряда:\n");
            scanf("%d", &max_n); //получаем max_n и проверяем её на валидность
            if (max_n <= 1 || !isValidDoubleNumber(max_n)) {
                printf("Некоректный ввод для количесво членов ряда. n > 1");
                return 1;
            }
            //получаем результат после вызова функции и выводим его
            double res2 = calculate_with_max_n(max_n, x);
            printf("arcsin(%lf)=%lf c %d членами ряда", x, res2, max_n);
            break;
        default:
            printf("Неверный выбор (1 или 2).");
            return 1;
    }
    return 0;
}
//определение функции calculate_with_epsilon, которая возвращает число с плавающей точкой
double calculate_with_epsilon(double epsilon, double x) { //для функции нужна точность(эпсилон) и x
    int n = 1; //переменная для n
    double temp = x; /*темповая переменная для подсчета x n-ого элемента ряда
    (равен x потому что первый элемент ряда равен x)*/
    double result = x; //результат изначально равен x, так как формула начинается с x+сумма
    while (temp >= epsilon) { //пока n-ый элемент >= точности продолжаем цикл
        temp *= (2 * n - 1) * (2 * n - 1) * pow(x,2) / (2 * n * (2 * n + 1)); /*умножаем предыдущий элемент
        на его изменение, получая n-ый*/
        result += temp; //прибавляем к результату n-ый элемент
        n++; //увеличиваем n на 1
    }
    return result; //возвращаем результат
}
//определение функции calculate_with_max_n, которая возвращает число с плавающей точкой
double calculate_with_max_n(int max_n, double x) {
    double result = x; //результат изначально равен x, так как формула начинается с x+сумма
    double temp = x; /*темповая переменная для подсчета x n-ого элемента ряда
    (равен x потому что первый элемент ряда равен x)*/

    for (int n = 1; n <= max_n; n++) { //идём от n до максимального количества членов ряда
        temp *= (2 * n - 1) * (2 * n - 1) * pow(x,2) / (2 * n * (2 * n + 1)); /*умножаем предыдущий элемент
        на его изменение, получая n-ый*/
        result += temp; //прибавляем к результату n-ый элемент
    }
    return result; //возвращаем результат
}
//определние функции isValidDoubleNumber, которая возвращает булевое значение
bool isValidDoubleNumber(double num) {
    // !isnan - не если число и isfinite - конечное число с плавающей точкой
    return !isnan(num) && isfinite(num);
}