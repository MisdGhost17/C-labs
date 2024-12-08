#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <stdint.h>

#define INPUT_FILENAME "C:/Users/Misd/CLionProjects/labs_C/files_for_lab3/f.txt"
#define OUTPUT_FILENAME "C:/Users/Misd/CLionProjects/labs_C/files_for_lab3/f1.txt"
//Вариант 26
/* Дан файл f, компоненты которого являются действительными числами. Найти:
Наименьшее из значений компонент файла. Записать это значение перед первым
наибольшим значением файла.*/

//Формирование файла f.txt с рандомными действительными числами
void generate_random_floats(int count){
    FILE *file = fopen(INPUT_FILENAME, "w");
    if (file == NULL) {
        printf("Ошибка открытия файла");
        exit(-1);
    }
    srand(time(NULL)); //Инициализатор рандомных чисел
    for (int i = 0; i < count; i++) {
        float random_number = (float)rand() / RAND_MAX*200 - 100.0; // Генерация числа от -100 до 100
        fprintf(file, "%lf\n", random_number); // Запись числа в файл
    }

    fclose(file);
}

// Функция для нахождения минимального и максимального значения
void find_min_and_max(const char *filename, double *min, double *max) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) { //если не получилось получить файл вызываем ошибку
        printf("Ошибка при открытии файла для чтения.\n");
        return;
    }

    double number;
    *min = 1000000000000000;
    *max = -10000000000000000;

    while (fscanf(file, "%lf", &number)==1) {
        if (number < *min) {
            *min = number;
        }
        if (number > *max) {
            *max = number;
        }
    }
    fclose(file);
}

// Функция для записи результата в выходной файл
void writeOutputFile(const char *inputFilename, const char *outputFilename, double min, double firstMax) {
    FILE *inputFile = fopen(inputFilename, "r");
    FILE *outputFile = fopen(outputFilename, "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Ошибка при открытии файлов.\n");
        exit(-1);
    }

    double number;
    int firstMaxWritten = 0;

    while (fscanf(inputFile, "%lf", &number) == 1) {
        if (number == firstMax && !firstMaxWritten) {
            fprintf(outputFile, "%lf\n", min); // Записываем минимальное значение перед первым максимальным
            firstMaxWritten = 1; // Устанавливаем флаг, чтобы не записывать повторно
        }
        fprintf(outputFile, "%lf\n", number);
    }

    fclose(inputFile);
    fclose(outputFile);
}

int main() {
    double minValue, firstMaxValue;
    SetConsoleOutputCP(CP_UTF8);
    int count;
    printf("Введите желаемое количество цифр в файле f.txt:\n");
    if (scanf("%d", &count)!=1 || count < 2||(int64_t)count) {
        printf("Введите целое число >= 2.");
        return -1;
    }
    generate_random_floats(count);
    // Находим минимальное и первое максимальное значения
    find_min_and_max(INPUT_FILENAME, &minValue, &firstMaxValue);

    // Записываем результат в выходной файл
    writeOutputFile(INPUT_FILENAME, OUTPUT_FILENAME, minValue, firstMaxValue);

    printf("Обработка завершена. Результат записан в файл %s\n", OUTPUT_FILENAME);

    return 0;
}