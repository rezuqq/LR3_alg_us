#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

struct node {
    char inf[256];      // Полезная информация
    struct node* next;  // Ссылка на следующий элемент
};

struct queue {
    struct node* head;  // Указатель на начало (голову) очереди
    struct node* last;  // Указатель на конец (хвост) очереди
};

// Функция создания нового узла
struct node* get_struct(void) {
    struct node* p = NULL;
    char s[256];

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL) {  // Выделяем память под новый элемент списка
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите название объекта: \n");
    scanf("%s", s);
    if (*s == 0) {
        printf("Запись не была произведена\n");
        return NULL;
    }
    strcpy(p->inf, s);
    p->next = NULL;  // Следующего элемента нет
    return p;
}

// Добавление элемента в конец очереди (enqueue)
void enqueue(struct queue* q) {
    struct node* p = get_struct();
    if (p == NULL) return;  // Если элемент не был создан

    if (q->head == NULL) {  // Если очередь пустая
        q->head = p;
        q->last = p;
    }
    else {  // Если очередь уже существует
        q->last->next = p;
        q->last = p;
    }
}

// Удаление элемента из начала очереди (dequeue)
void dequeue(struct queue* q) {
    if (q->head == NULL) {  // Если очередь пуста
        printf("Очередь пуста\n");
        return;4
    }

    struct node* temp = q->head;
    printf("Удаление: %s\n", temp->inf);
    q->head = q->head->next;
    free(temp);

    if (q->head == NULL) {  // Если очередь стала пустой
        q->last = NULL;
    }
}

// Просмотр содержимого очереди
void review(struct queue* q) {
    struct node* struc = q->head;
    if (q->head == NULL) {
        printf("Очередь пуста\n");
        return;
    }
    while (struc != NULL) {
        printf("Имя - %s\n", struc->inf);
        struc = struc->next;
    }
}

// Поиск элемента по содержимому
struct node* find(struct queue* q, char* name) {
    struct node* struc = q->head;
    if (q->head == NULL) {
        printf("Очередь пуста\n");
        return NULL;
    }
    while (struc) {
        if (strcmp(name, struc->inf) == 0) {
            return struc;
        }
        struc = struc->next;
    }
    printf("Элемент не найден\n");
    return NULL;
}

// Удаление элемента по содержимому
void delete_by_name(struct queue* q, char* name) {
    struct node* struc = q->head;
    struct node* prev = NULL;

    if (q->head == NULL) {
        printf("Очередь пуста\n");
        return;
    }

    while (struc != NULL) {
        if (strcmp(name, struc->inf) == 0) {
            printf("Удаление элемента: %s\n", struc->inf);
            if (prev == NULL) {  // Если элемент первый
                q->head = struc->next;
            }
            else {
                prev->next = struc->next;
            }
            if (struc == q->last) {  // Если элемент последний
                q->last = prev;
            }
            free(struc);
            return;
        }
        prev = struc;
        struc = struc->next;
    }

    printf("Элемент не найден\n");
}

// Основная функция
int main() {
    setlocale(LC_ALL, "Rus");
    int choice;
    char name[256];

    struct queue q = { NULL, NULL };  // Инициализация пустой очереди

    while (1) {
        printf("\nМеню:\n");
        printf("1. Добавить элемент в очередь\n");
        printf("2. Просмотр очереди\n");
        printf("3. Поиск элемента по имени\n");
        printf("4. Удалить элемент по имени\n");
        printf("5. Удалить элемент из начала очереди (dequeue)\n");
        printf("6. Выйти\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            enqueue(&q);  // Добавление элемента
            break;
        case 2:
            review(&q);  // Просмотр очереди
            break;
        case 3:
            printf("Введите имя для поиска: ");
            scanf("%s", name);
            if (find(&q, name) != NULL)
                printf("Элемент найден: %s\n", name);
            break;
        case 4:
            printf("Введите имя для удаления: ");
            scanf("%s", name);
            delete_by_name(&q, name);  // Удаление элемента по имени
            break;
        case 5:
            dequeue(&q);  // Удаление элемента из начала очереди
            break;
        case 6:
            printf("Выход\n");
            exit(0);
        default:
            printf("Неверный выбор\n");
            break;
        }
    }

    return 0;
}
