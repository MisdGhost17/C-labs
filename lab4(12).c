#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_TERMS 100 //максимальное количество членов многочлена

//функция для добавления члена в многочлен
void addTerm(int polynomial[MAX_TERMS][2], int* termCount, int degree, int coefficient) {

    //проверка на существование степени
    for (int i = 0; i < *termCount; i++) {
        if (polynomial[i][0] == degree) {
            polynomial[i][1] += coefficient; //суммируем коэффициенты
            return;
        }
    }

    //добавляем новый член, если еще не достигнуто максимальное количество
    if (*termCount < MAX_TERMS) {
        polynomial[*termCount][0] = degree;
        polynomial[*termCount][1] = coefficient;
        (*termCount)++;
    } else {
        printf("Превышено максимальное количество членов многочлена.\n");
    }
}

//функция для вывода многочлена на экран
void printPolynomial(int polynomial[MAX_TERMS][2], int termCount) {
    if (termCount == 0) {
        printf("0\n"); //пустой многочлен
        return;
    }

    for (int i = 0; i < termCount; i++) {
        printf("%dx^%d ", polynomial[i][1], polynomial[i][0]);
        if (i < termCount - 1) {
            printf("+ ");
        }
    }
    printf("\n");
}

//функция для формирования нового многочлена из двух
void formPolynomial(int poly1[MAX_TERMS][2], int termCount1,
                    int poly2[MAX_TERMS][2], int termCount2,
                    int result[MAX_TERMS][2], int* resultTermCount) {
    *resultTermCount = 0;

    //проходимся по первому многочлену
    for (int i = 0; i < termCount1; i++) {
        for (int j = 0; j < termCount2; j++) {
            if (poly1[i][0] == poly2[j][0]) {
                //если степени совпадают, добавляем в результат сумму коэффициентов
                addTerm(result, resultTermCount, poly1[i][0], poly1[i][1] + poly2[j][1]);
            }
        }
    }
}


int main() {
    SetConsoleOutputCP(CP_UTF8);
    int polynomial1[MAX_TERMS][2]; //массив для первого многочлена
    int polynomial2[MAX_TERMS][2]; //массив для второго многочлена

    int resultPolynomial[MAX_TERMS][2]; //массив для результата

    int termCount1 = 0, termCount2 = 0;

    //создание первого многочлена
    printf("Введите количество членов первого многочлена: ");

    float termsCount1;
    scanf("%f", &termsCount1);
    int termsCount1_int = (int)termsCount1;

    if (termsCount1_int != termsCount1 || termsCount1 <= 0 || termsCount1 > MAX_TERMS) {
        fprintf(stderr,"Ошибка ввода. Введите положительное целое число не больше %d ", MAX_TERMS);
        return -1;
    }

    for (int i = 0; i < termsCount1; i++) {
        int degree, coefficient;
        printf("Введите степень и коэффициент (например: 2 3 для 3x^2): ");

        while (scanf("%d %d", &degree, &coefficient) != 2 || coefficient == 0 || degree < 0) {
            fprintf(stderr, "Некорректный ввод. Убедитесь, что степень не отрицательная и коэффициент не равен нулю.\n");
            while (getchar() != '\n'); //очистка буфера ввода
            printf("Введите степень и коэффициент: ");
        }

        addTerm(polynomial1, &termCount1, degree, coefficient);
    }

    //создание второго многочлена
    printf("Введите количество членов второго многочлена: ");


    float termsCount2;
    scanf("%f", &termsCount2);
    int termsCount2_int = (int)termsCount2;

    if (termsCount2_int != termsCount2 || termsCount2 <= 0 || termsCount2 > MAX_TERMS) {
        fprintf(stderr,"Ошибка ввода. Введите положительное целое число не больше %d ", MAX_TERMS);
        return -1;
    }


    for (int i = 0; i < termsCount2; i++) {
        int degree, coefficient;
        printf("Введите степень и коэффициент (например: 2 -5 для -5x^2): ");

        while (scanf("%d %d", &degree, &coefficient) != 2 || coefficient == 0 || degree < 0) {
            fprintf(stderr, "Некорректный ввод. Убедитесь, что степень не отрицательная и коэффициент не равен нулю.\n");
            while (getchar() != '\n'); //очистка буфера ввода
            printf("Введите степень и коэффициент: ");
        }

        addTerm(polynomial2, &termCount2, degree, coefficient);
    }

    //вывод многочленов до обработки
    printf("Первый многочлен: ");
    printPolynomial(polynomial1, termCount1);

    printf("Второй многочлен: ");
    printPolynomial(polynomial2, termCount2);

   //формирование нового многочлена из L1 и L2
   int resultTermCount = 0;
   formPolynomial(polynomial1, termCount1,
                  polynomial2, termCount2,
                  resultPolynomial, &resultTermCount);

   //вывод результата после обработки
   printf("Результат формирования: ");
   printPolynomial(resultPolynomial, resultTermCount);

   return 0;
}
