#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//определение структуры элемента списка
struct Node {
    int degree;                //степень
    int coefficient;           //коэффициент
    struct Node* next;         //указатель на следующий элемент
};

//функция для создания нового элемента
struct Node* createNode(int degree, int coefficient) {
    struct Node* newNode = malloc(sizeof(struct Node)); /*выделяем блок памяти, вернет указатель void на выделенное пространство
    или Null*/
    if (newNode == NULL) {
        fprintf(stderr, "Ошибка выделения памяти.\n");
        exit(-1);
    }
    newNode->degree = degree;
    newNode->coefficient = coefficient;
    newNode->next = NULL;
    return newNode;
}

//функция для добавления элемента в список
void addTerm(struct Node** head, int degree, int coefficient) {
    struct Node* current = *head;
    while (current != NULL) {
        //суммируем коэффициенты если вводимая степень уже встречалась
        if (current->degree == degree) {
            current->coefficient += coefficient;
            return;
        }
        current = current->next;
    }
    //добавляем новый член в начало списка
    struct Node* newNode = createNode(degree, coefficient);
    newNode->next = *head;
    *head = newNode;
}

//функция для вывода многочлена на экран
void printPolynomial(struct Node* head) {
    if (head == NULL) {
        printf("0\n"); //пустой многочлен
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

//функция для освобождения памяти
void freePolynomial(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp); //освобождает память, на которую указывает параметр
    }
}

//функция для формирования нового многочлена из двух по заданному правилу
struct Node* formPolynomial(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;

    //проходим по первому многочлену
    struct Node* current1 = poly1;

    while (current1 != NULL) {
        struct Node* current2 = poly2;

        while (current2 != NULL) {
            if (current1->degree == current2->degree) {
                //если степени совпадают, добавляем в результат сумму коэффициентов
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

   //создание первого многочлена L1
    printf("Введите количество членов первого многочлена L1: ");
    float termsCount1;

   while (scanf("%fl", &termsCount1) != 1 || termsCount1 <= 0 || termsCount1 != (int)termsCount1) {
       fprintf(stderr, "Ошибка ввода. Введите положительное целое число: ");
       while (getchar() != '\n'); //очистка буфера ввода
   }

   for (int i = 0; i < termsCount1; i++) {
       int degree, coefficient;
       printf("Введите степень и коэффициент для L1 (например: 2 3): ");
       while (scanf("%d %d", &degree, &coefficient) != 2 || coefficient == 0 || degree < 0) {
           fprintf(stderr, "Некорректный ввод. Убедитесь, что степень не отрицательная и коэффициент не равен нулю:\n");
           while (getchar() != '\n'); //очистка буфера ввода
       }

       addTerm(&polynomial1, degree, coefficient);
   }

   //создание второго многочлена L2
   printf("Введите количество членов второго многочлена L2: ");
   float termsCount2;

   while (scanf("%fl", &termsCount2) != 1 || termsCount2 <= 0 || termsCount2 != (int)termsCount2) {
       fprintf(stderr, "Ошибка ввода. Введите положительное целое число: ");
       while (getchar() != '\n'); //очистка буфера ввода
   }

   for (int i = 0; i < termsCount2; i++) {
       int degree, coefficient;

       printf("Введите степень и коэффициент для L2 (например: 2 -5): ");
       while (scanf("%d %d", &degree, &coefficient) != 2 || coefficient == 0 || degree < 0) {
           fprintf(stderr, "Некорректный ввод. Убедитесь, что степень не отрицательная и коэффициент не равен нулю:\n");
           while (getchar() != '\n'); //очистка буфера ввода
       }

       addTerm(&polynomial2, degree, coefficient);
   }

   printf("Первый многочлен L1: ");
   printPolynomial(polynomial1);

   printf("Второй многочлен L2: ");
   printPolynomial(polynomial2);

   //формирование нового многочлена из L1 и L2 по заданному правилу
   struct Node* resultPolynomial = formPolynomial(polynomial1, polynomial2);

   printf("Результат формирования: ");
   printPolynomial(resultPolynomial);

   //освобождение памяти
   freePolynomial(polynomial1);
   freePolynomial(polynomial2);
   freePolynomial(resultPolynomial);

   return 0;
}