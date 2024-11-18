#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>


/*Вариант 26. Дана строка, содержащая от 1 до 30 слов, в каждом из которых от 1 до 10 латинских
букв и/или цифр; между соседними словами – не менее одного пробела, за последним
словом – точка. Напечатать все слова, отличные от последнего слова, предварительно
преобразовав каждое из них по следующему правилу: удалить из слова все
предыдущие вхождения последней буквы.*/

//определяем функцию
void transform_string(const char *input);

int main(){

    char input[301]; //массив для строки
    SetConsoleOutputCP(CP_UTF8);

    printf("Введите строку (до 30 слов, каждое до 10 символов):\n");
    fgets(input, sizeof(input), stdin); /*записываем строку input,
    для которой максимальный размер - размер массива input(300),
    stdin - ввод с клавиатуры
    */
    input[strcspn(input, "\n")] = '\0'; //убираем символ новой строки
    if (input[strlen(input)-1] == '.'){ //проверка точка ли последний символ
        //вывод первоначальной строки
        printf("Изначальная строка: %s\n", input);
        printf("Изменённая строка: ");
        transform_string(input);

        return 0;
        }
    else {
        printf("Строка должна заканчиваться точкой!");
        return -1;
    }
}

void transform_string(const char *input) {
    char words[30][11]; //двусвязный массив для слов (30 слов по 10 + \0 = 11 символов)
    int word_count = 0; //переменная для количества слов

    // Копируем строку, заменяя точку на \0(символ означающий конец строки)
    char str[301]; // создаем массив из 300 элементов так как 30 слов * 10 букв в каждом
    strcpy(str, input); //копируем input в массив str
    str[strcspn(str, ".")] = '\0'; /*заменяем точку на конец строки (strcspn указывает на первое
    вхождение искомого символа (точки)) */

    // Разделяем строку на слова
    char *token = strtok(str, " "); /*создаем строку token (strtok выделяет все содержимое
    строки до первого пробелам*/
    while (token != NULL && word_count < 30) { //пока выделяемая строка не пустая продолжаем цикл
        strcpy(words[word_count], token); //копируем token в массив наших слов
        word_count++; //счетчик кол-ва слов в строке
        token = strtok(NULL, " "); //выделяем следующую часть строки
    }
    int len_lastword = strlen(words[word_count-1]); //получаем длину последнего слова
    char lastchr = words[word_count-1][len_lastword-1]; //получаем последний символ

    //убираем все вхождения последней буквы
    for (int i = 0; i < word_count; i++) { //проходимся по всем словам
        for (int j = 0; j < strlen(words[i]); j++) { //проходимся по всем буквам в слове
            if (words[i][j] == lastchr) { /*если наш символ равен последнему
                находим его позицию и сдвигаем всю часть слова вместо него*/
                for (int k = j; k < strlen(words[i]); k++) {
                    if (words[i][k] != '\0') {
                        words[i][k] = words[i][k+1];
                    }
                }
            }
        }
    }
    char lastword[11]; //массив для последнего слова
    strcpy(lastword, words[word_count-1]); //копируем последнее слово в lastword
    for (int i = 0; i < word_count-1; i++) { //проходимся по всем словам, кроме последнего
        if (strcmp(lastword, words[i]) != 0) { /*сравниваем символы двух строк,
            если они не совпадают то печатаем их(если совпадают strcmp вернет 0)*/
            printf("%s ", words[i]);
        }
    }
    //печатаем последнее слово
    printf("%s.\n", lastword);
}