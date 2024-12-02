#include <iso646.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <windows.h>В

// Определение функций для счета 1 и 2
double calculate_with_epsilon(double epsilon, double x);
double calculate_with_max_n(int n, double x);

//Проверка валидно ли double float число(не целое число, значение с плавающей точкой)
bool isValidDoubleNumber(double num);

int is_integer(double num) {
    return floor(num) == num;
}

int main(){
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
        return 0;
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
            if (e <= 0 ||!is_integer(e) ||!isValidDoubleNumber(e)) {
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
            if (max_n <= 1 || !isdigit(max_n)) {
                printf("Некоректный ввод для количесво членов ряда. n > 1");
                return 1;
            }
            //получаем результат после вызова функции и выводим его
            double res2 = calculate_with_max_n(max_n, x);
            printf("arcsin(%lf)=%lf c %d членами ряда", x, res2, max_n);
            return 1;
        default:
            printf("Неверный выбор (1 или 2).");
            return 0;
    }
}
//определение функции calculate_with_epsilon, которая возвращает число с плавающей точкой
double calculate_with_epsilon(double epsilon, double x) { //для функции нужна точность(эпсилон) и x
    int n = 2; //переменная для n начинаем со второго
    double temp = pow(x,3)/6; /*темповая переменная для подсчета x n-ого элемента ряда
    (равен x^3/6 потому что первый элемент при n=1 x_1=x^3/6)*/
    double prev_x = 0;
    double result = x+temp; //результат изначально равен x+xn, так как формула начинается с x+сумма
    while (fabs(prev_x-temp) >= epsilon) { //пока модуль x_n-1 - x_n >= точности продолжаем цикл
        prev_x = temp; //перезаписываем предыдущий элемент
        temp *= (2 * (n - 1)+1) *(2 * n - 1) * pow(x,2) / (2 * n * (2 * n + 1)); /*умножаем предыдущий элемент
        на его изменение, получая n-ый*/
        result += temp; //прибавляем к результату n-ый элемент
        n++; //увеличиваем n на 1
    }
    return result; //возвращаем результат
}
//определение функции calculate_with_max_n, которая возвращает число с плавающей точкой
double calculate_with_max_n(int max_n, double x) {
    double temp = pow(x,3)/6; /*темповая переменная для подсчета x n-ого элемента ряда
    (равен x^3/6 потому что первый элемент при n=1 x_1=x^3/6)*/
    double result = x+temp; //результат изначально равен x, так как формула начинается с x+сумма

    for (int n = 2; n <= max_n; n++) { //идём от n до максимального количества членов ряда, начиная со второго
        temp *= (2 * (n - 1)+1) * (2 * n - 1) * pow(x,2) / (2 * n * (2 * n + 1)); /*умножаем предыдущий элемент
        на его изменение, получая n-ый*/
        result += temp; //прибавляем к результату n-ый элемент
    }
    return result; //возвращаем результат
}
//определние функции isValidDoubleNumber, которая возвращает булевое значение
bool isValidDoubleNumber(double num) {
    // !isnan - если число и isfinite - конечное число с плавающей точкой
    return !isnan(num) && isfinite(num);
}