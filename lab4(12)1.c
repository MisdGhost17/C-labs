#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//определение структуры узла списка
struct Node {
    int degree;                //степень
    int coefficient;           //коэффициент
    struct Node* next;         //указатель на следующий элемент
};

//функция для создания нового узла
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

//функция для добавления узла в список
void addTerm(struct Node** head, int degree, int coefficient) {
    //проверка на существование степени
    struct Node* current = *head;
    while (current != NULL) {
        if (current->degree == degree) {
            current->coefficient += coefficient; //суммируем коэффициенты
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
        free(temp);
    }
}

//функция для сложения двух многочленов
struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;

    //добавляем все члены первого многочлена в результат
    struct Node* current = poly1;
    while (current != NULL) {
        addTerm(&result, current->degree, current->coefficient);
        current = current->next;
    }

    //добавляем все члены второго многочлена в результат
    current = poly2;
    while (current != NULL) {
        addTerm(&result, current->degree, current->coefficient);
        current = current->next;
    }

    return result; //возвращаем новый многочлен
}

//основная функция
int main() {
    SetConsoleOutputCP(CP_UTF8);
    struct Node* polynomial1 = NULL;
    struct Node* polynomial2 = NULL;

    float termsCount1, termsCount2;

    //создание первого многочлена
    printf("Введите количество членов первого многочлена: ");
    scanf("%f", &termsCount1);
    int inttermsCount = (int)termsCount1;
    if ((termsCount1 != inttermsCount) || termsCount1 <= 0) {
        printf("Ошибка ввода. Количество должно быть целым положительным числом!");
        return -1;
    }

    for (int i = 0; i < termsCount1; i++) {
        int degree, coefficient;
        printf("Введите степень и коэффициент (например: 2 3 для 3x^2): ");

        while (scanf("%d %d", &degree, &coefficient) != 2 || coefficient == 0 || degree < 0) {
            printf("Некорректный ввод. Убедитесь, что степень не отрицательная и коэффициент не равен нулю.\n");
            while (getchar() != '\n'); // Очистка буфера ввода
            printf("Введите степень и коэффициент: ");
        }

        addTerm(&polynomial1, degree, coefficient);
    }

    // Создание второго многочлена
    printf("Введите количество членов второго многочлена: ");
    scanf("%f", &termsCount2);
    int inttermsCount2 = (int)termsCount2;

    if ((termsCount2!= inttermsCount2)|| termsCount2 <= 0) {
        printf("Ошибка ввода. Количество должно быть целым положительным числом! ");
        return -1;
    }

    for (int i = 0; i < termsCount2; i++) {
        int degree, coefficient;
        printf("Введите степень и коэффициент (например: 2 -5 для -5x^2): ");

        while (scanf("%d %d", &degree, &coefficient) != 2 || coefficient == 0 || degree < 0) {
            printf("Некорректный ввод. Убедитесь, что степень не отрицательная и коэффициент не равен нулю.\n");
            while (getchar() != '\n'); // Очистка буфера ввода
            printf("Введите степень и коэффициент: ");
        }

        addTerm(&polynomial2, degree, coefficient);
    }

   //вывод многочленов до обработки
   printf("Первый многочлен: ");
   printPolynomial(polynomial1);

   printf("Второй многочлен: ");
   printPolynomial(polynomial2);

   //сложение двух многочленов
   struct Node* resultPolynomial = addPolynomials(polynomial1, polynomial2);

   //вывод результата после обработки
   printf("Результат сложения: ");
   printPolynomial(resultPolynomial);

   //освобождение памяти
   freePolynomial(polynomial1);
   freePolynomial(polynomial2);
   freePolynomial(resultPolynomial);

   return 0;
}
