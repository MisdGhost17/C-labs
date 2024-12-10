#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <stdint.h>
#include <time.h>
#include <windows.h>

#define FILENAME "C:/Users/Misd/CLionProjects/labs_C/f.txt"

//функция для формирования файла с случайными числами
void random_nums_file(int count) {
    srand((unsigned int)time(NULL)); //инициализация генератора случайных чисел
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Ошибка открытия файла для записи");
        exit(-1);
    }

    for (int i = 0; i < count; i++) {
        float number = ((float)rand() / RAND_MAX) * 200 - 100; //генерация числа от -100 до 100
        fprintf(file, "%.2f\n", number);
    }

    fclose(file);
}

//функция для формирования файла с вводом чисел пользователем
void user_nums_file(int count) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Ошибка открытия файла для записи");
        exit(-1);
    }

    printf("Введите %d действительных чисел:\n", count);
    for (int i = 0; i < count; i++) {
        float number;
        while (1) {
            printf("%d: ", i + 1);
            if (scanf("%f", &number) == 1) {
                fprintf(file, "%.2f\n", number);
                break; //выход из цикла при корректном вводе
            }
            else {
                printf( "Введено некорректное число. Попробуйте снова.\n");
                while (getchar() != '\n'); //очищаем буфер ввода
            }
        }
    }

    fclose(file);
}

//функция для обработки файла
void transformfile(float *minValue, float *maxValue, int *count) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла для чтения");
        exit(-1);
    }

    float numbers[1000];
    *minValue = FLT_MAX;
    *maxValue = -FLT_MAX;

    //считываем числа и находим минимальное и максимальное значения
    *count = 0; //счетчик считанных чисел
    while (fscanf(file, "%f", &numbers[*count]) == 1 && *count < 1000) {
        if (numbers[*count] < *minValue) {
            *minValue = numbers[*count];
        }
        if (numbers[*count] > *maxValue) {
            *maxValue = numbers[*count];
        }
        (*count)++;
    }

    fclose(file);

    //eсли максимальное значение найдено, вставляем минимальное значение перед ним
    if (*count > 0) {
        for (int i = 0; i < *count; i++) {
            if (numbers[i] == *maxValue && i > 0) { //вставляем перед первым максимальным значением
                for (int j = *count; j > i; j--) { //сдвигаем элементы вправо
                    numbers[j] = numbers[j - 1];
                }
                numbers[i] = *minValue; //вставляем минимальное значение
                (*count)++; //увеличиваем счетчик на одно число
                break;
            }
        }

        //записываем обновленные данные обратно в файл
        file = fopen(FILENAME, "w");
        if (file == NULL) {
            printf("Ошибка открытия файла для записи");
            exit(-1);
        }

        for (int i = 0; i < *count; i++) {
            fprintf(file, "%.2f\n", numbers[i]);
        }

        fclose(file);
    }
}

//функция для вывода результата
void result(float minValue, float maxValue) {
    printf("Наименьшее значение: %.2f\n", minValue);
    printf("Наибольшее значение: %.2f\n", maxValue);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    float count;
    float choice;

    printf("Выберите способ формирования исходного файла:\n");
    printf("1 - Случайные числа\n");
    printf("2 - Ввод пользователем\n");
    scanf("%f", &choice);
    int choice_int = (int)choice;

    if (!(choice_int == choice && (choice == 1 || choice == 2))){
        printf("Неверный выбор. Выберите 1 или 2.");
        return -1;
    }

    printf("Введите количество элементов в файле: ");
    scanf("%f", &count);
    int count_int = (int)count;
    if (!(count_int == count && count > 0 && count <= 1000)) {
        printf("Количество элементов должно быть положительным целым числом.\n");
        return 0;
    }

    if (choice == 1) {
        random_nums_file(count); //создаем файл с случайными числами
    }
    if (choice == 2) {
        user_nums_file(count); //создаем файл с вводом пользователя
    }

    float minValue, maxValue;

    transformfile(&minValue, &maxValue, &count); //обрабатываем файл для нахождения мин/макс значений

    result(minValue, maxValue); //выводим результат

    return 1;
}