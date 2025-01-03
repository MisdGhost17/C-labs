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

    printf("Введите строку (до 30 слов, каждое до 10 символов), строка должна заканчиваться точкой:\n");
    fgets(input, sizeof(input), stdin); /*записываем строку input,
    для которой максимальный размер - размер массива input(300),
    stdin - ввод с клавиатуры
    */
    input[strcspn(input, "\n")] = '\0';//убираем символ новой строки
    for (int i = 0; i < strlen(input); i++) {
        if ((isalpha(input[i]) || isdigit(input[i]) || !ispunct(input[i]) || input[i] == '.') == 0){
            printf("Строка должна содержать только латинские буквы и цифры!");
            return -1;
        }
    }
    //проверяем сколько точек в строке
    int count_dot = 0;
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == '.') {
            count_dot += 1;
        }
    }
    if (count_dot > 1) {
        printf("Строка должна содержать только одну точку!");
        return -1;
    }
    char teststr[400];
    strcpy(teststr, input);
    int word_count = 0;
    char words[30][11];
    char *token = strtok(teststr, " "); /*создаем строку token (strtok выделяет все содержимое
    строки до первого пробелам*/
    while (token != NULL && word_count < 30) {//пока выделяемая строка не пустая продолжаем цикл
        if (strlen(token) > 11) {
            printf("Слово должно содержать не больше 10 символов.");
            return -1;
        }
        strcpy(words[word_count], token); //копируем token в массив наших слов
        word_count++; //счетчик кол-ва слов в строке
        token = strtok(NULL, " "); //выделяем следующую часть строки
    }

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

    char str[400]; // создаем массив из 400 элементов так как 30 слов * 10 букв в каждом + произвольное количество пробелов между ними
    strcpy(str, input); //копируем input в массив str
    str[strcspn(str, ".")] = '\0'; /*заменяем точку на конец строки (strcspn указывает на первое
    вхождение искомого символа (точки)) */
    // Разделяем строку на слова
    char *token = strtok(str, " "); /*создаем строку token (strtok выделяет все содержимое
    строки до первого пробела*/
    while (token != NULL && word_count < 30) {//пока выделяемая строка не пустая продолжаем цикл
        strcpy(words[word_count], token); //копируем token в массив наших слов
        word_count++; //счетчик кол-ва слов в строке
        token = strtok(NULL, " "); //выделяем следующую часть строки
    }
    words[word_count][0]= '\0';
    //убираем все вхождения последней буквы
    for (int i = 0; i < word_count; i++) {
        //проходимся по всем словам
        char lastchr = words[i][strlen(words[i])-1]; //последний символ как char
        char lastcharstr[2] = {lastchr, '\0'};//последний символ как строка (нужно для strcspn)
        //strcsp возвращает значение больше длины строки, если заданного символа в ней нет
        /*пока значение strcspn <= длине слова - последняя буква - '\0',
         значит последний символ есть в строке, следовательно продолжаем*/
        int allsymbolsame = 1;
        for (int s=0; s < strlen(words[i])-1; s++) {
            if (words[i][s] != lastchr) {
                allsymbolsame = 0;
            }
        }
        if (allsymbolsame == 0) {
            while (strcspn(words[i],lastcharstr) <= strlen(words[i])-2){
                for (int j = 0; j < strlen(words[i])-1; j++) { //проходимся по всем символам в слове кроме последнего
                    if (words[i][j] == lastchr && words[i][j+1] != '\0') { /*если наш символ равен последнему
                        находим его позицию и сдвигаем всю часть слова вместо него*/
                        for (int k = j; k < strlen(words[i]); k++) {
                            words[i][k] = words[i][k+1];
                        }
                    }
                }
            }
        }
        if (allsymbolsame == 1){
            strcpy(words[i], lastcharstr);
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

