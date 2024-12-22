#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

typedef struct Node {
    char word[100];
    struct Node* prev;
    struct Node* next;
} Node;

//функция для создания нового элемента списка
Node* createNode(const char* word) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Ошибка выделения памяти.\n");
        exit(-1);
    }
    strcpy(newNode->word, word);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

//функция для добавления элемента в конец списка
void appendNode(Node** head, const char* word) {
    Node* newNode = createNode(word);
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
    newNode->prev = current;
}

//функция для проверки, начинается ли слово на гласную
int startsWithVowel(const char* word) {
    char firstChar = tolower(word[0]);
    return (firstChar == 'a' || firstChar == 'e' || firstChar == 'i' ||
            firstChar == 'o' || firstChar == 'u' || firstChar == 'y');
}

//функция для проверки, состоит ли строка только из латинских букв и пробелов
int isValidInput(const char* str) {
    while (*str) {
        if (!isalpha(*str) && !isspace(*str)) {
            return 0; //неверный символ найден
        }
        str++;
    }
    return 1;
}

//функция для перестановки слов в списке
Node* rearrangeList(Node* head) {
    Node *vowelFirst = NULL, *vowelLast = NULL;
    Node *consonantFirst = NULL;

    Node* current = head;

    while (current != NULL) {
        if (startsWithVowel(current->word)) {
            //добавляем в список с гласными
            if (vowelFirst == NULL) {
                vowelFirst = createNode(current->word);
                vowelLast = vowelFirst;
            } else {
                vowelLast->next = createNode(current->word);
                vowelLast->next->prev = vowelLast;
                vowelLast = vowelLast->next;
            }
        } else {
            //добавляем в список с согласными
            if (consonantFirst == NULL) {
                consonantFirst = createNode(current->word);
            } else {
                Node* temp = consonantFirst;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = createNode(current->word);
                temp->next->prev = temp;
            }
        }
        current = current->next;
    }

    //соединяем два списка
    if (vowelLast != NULL) {
        vowelLast->next = consonantFirst;
        if (consonantFirst != NULL) {
            consonantFirst->prev = vowelLast;
        }
        return vowelFirst; //возвращаем новый список
    }

    return consonantFirst; //если нет слов на гласную, возвращаем список с согласными
}

//функция для вывода списка
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%s ", current->word);
        current = current->next;
    }
    printf("\n");
}

//функция для освобождения памяти
void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* nextNode = current->next;
        free(current);
        current = nextNode;
    }
}


int main() {
    SetConsoleOutputCP(CP_UTF8);
    Node* head = NULL;

    printf("Введите строку из строчных латинских букв (окончание - точка):\n");

    char input[1000];

    //чтение строки до точки
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Ошибка при чтении строки.\n");
        return -1;
    }

    //заменяем точку на символ завершения строки
    char *ptr = strchr(input, '.');
    if (ptr != NULL) *ptr = '\0';


	//проверка на допустимые символы
	if (!isValidInput(input)) {
		fprintf(stderr, "Ошибка: строка должна содержать только строчные латинские буквы и пробелы.\n");
		return -1;
	}

	//разделение строки на слова и добавление в список
	char *token = strtok(input, " ");

	while (token != NULL) {
		//проверка на пустые слова
		if (strlen(token) > 0) {
			appendNode(&head, token);
		}
		token = strtok(NULL, " ");
	}

	printf("Исходный список:\n");

    printList(head);

	head = rearrangeList(head);

	printf("Переставленный список:\n");

    printList(head);

	//освобождение памяти
	freeList(head);

	return 0;
}
