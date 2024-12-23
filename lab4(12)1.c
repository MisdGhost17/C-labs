#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Определение структуры узла списка
struct Node {
    int degree;                // Степень
    int coefficient;           // Коэффициент
    struct Node* next;         // Указатель на следующий элемент
};

// Функция для создания нового узла
struct Node* createNode(int degree, int coefficient) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "Ошибка выделения памяти.\n");
        exit(EXIT_FAILURE);
    }
    newNode->degree = degree;
    newNode->coefficient = coefficient;
    newNode->next = NULL;
    return newNode;
}

// Функция для добавления узла в список
void addTerm(struct Node** head, int degree, int coefficient) {
    if (coefficient == 0) {
        return; // Игнорируем нулевые коэффициенты
    }

    // Проверка на существование степени
    struct Node* current = *head;
    while (current != NULL) {
        if (current->degree == degree) {
            current->coefficient += coefficient; // Суммируем коэффициенты
            return;
        }
        current = current->next;
    }

    // Добавляем новый член в начало списка
    struct Node* newNode = createNode(degree, coefficient);
    newNode->next = *head;
    *head = newNode;
}

// Функция для вывода многочлена на экран
void printPolynomial(struct Node* head) {
    if (head == NULL) {
        printf("0\n"); // Пустой многочлен
        return;
    }

    struct Node* current = head;
    while (current != NULL) {
        printf("%dx^%d ", current->coefficient, current->degree);
        if (current->next != NULL) {
            printf("+ ");
        }
        current = current->next;
    }
    printf("\n");
}

// Функция для освобождения памяти
void freePolynomial(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
}

// Функция для формирования нового многочлена из двух по заданному правилу
struct Node* formPolynomial(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;

    // Проходим по первому многочлену
    struct Node* current1 = poly1;

    while (current1 != NULL) {
        struct Node* current2 = poly2;

        while (current2 != NULL) {
            if (current1->degree == current2->degree) {
                // Если степени совпадают, добавляем в результат сумму коэффициентов
                addTerm(&result, current1->degree, current1->coefficient + current2->coefficient);
            }
            current2 = current2->next;
        }

        current1 = current1->next;
    }

    return result; //возвращаем новый многочлен
}

//основная функция
int main() {
    SetConsoleOutputCP(CP_UTF8);
    struct Node* polynomial1 = NULL;
    struct Node* polynomial2 = NULL;

   // Создание первого многочлена L1
   printf("Введите количество членов первого многочлена L1: ");
   int termsCount1;

   while (scanf("%d", &termsCount1) != 1 || termsCount1 <= 0) {
       fprintf(stderr, "Ошибка ввода. Введите положительное целое число: ");
       while (getchar() != '\n'); // Очистка буфера ввода
   }

   for (int i = 0; i < termsCount1; i++) {
       int degree, coefficient;

       printf("Введите степень и коэффициент для L1 (например: 2 3): ");
       while (scanf("%d %d", &degree, &coefficient) != 2 || coefficient == 0 || degree < 0) {
           fprintf(stderr, "Некорректный ввод. Убедитесь, что степень не отрицательная и коэффициент не равен нулю.\n");
           while (getchar() != '\n'); // Очистка буфера ввода
           printf("Введите степень и коэффициент: ");
       }

       addTerm(&polynomial1, degree, coefficient);
   }

   // Создание второго многочлена L2
   printf("Введите количество членов второго многочлена L2: ");
   int termsCount2;

   while (scanf("%d", &termsCount2) != 1 || termsCount2 <= 0) {
       fprintf(stderr, "Ошибка ввода. Введите положительное целое число: ");
       while (getchar() != '\n'); // Очистка буфера ввода
   }

   for (int i = 0; i < termsCount2; i++) {
       int degree, coefficient;

       printf("Введите степень и коэффициент для L2 (например: 2 -5): ");
       while (scanf("%d %d", &degree, &coefficient) != 2 || coefficient == 0 || degree < 0) {
           fprintf(stderr, "Некорректный ввод. Убедитесь, что степень не отрицательная и коэффициент не равен нулю.\n");
           while (getchar() != '\n'); // Очистка буфера ввода
           printf("Введите степень и коэффициент: ");
       }

       addTerm(&polynomial2, degree, coefficient);
   }

   // Вывод многочленов до обработки
   printf("Первый многочлен L1: ");
   printPolynomial(polynomial1);

   printf("Второй многочлен L2: ");
   printPolynomial(polynomial2);

   // Формирование нового многочлена из L1 и L2 по заданному правилу
   struct Node* resultPolynomial = formPolynomial(polynomial1, polynomial2);

   // Вывод результата после обработки
   printf("Результат формирования: ");
   printPolynomial(resultPolynomial);

   // Освобождение памяти
   freePolynomial(polynomial1);
   freePolynomial(polynomial2);
   freePolynomial(resultPolynomial);

   return 0;
}