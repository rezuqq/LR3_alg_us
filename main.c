#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

struct node {
    char inf[256];
    struct node* next;
};

struct stack {
    struct node* head;
    struct node* last;
};

struct node* get_struct(void) {
    struct node* p = NULL;
    char s[256];

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL) {
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
    p->next = NULL;
    return p;
}

// Добавление элемента в стек
void push(struct stack* st) {
    struct node* p = get_struct();
    if (p == NULL) return;

    p->next = st->head;
    st->head = p;
}

// Удаление элемента из стека
void pop(struct stack* st) {
    if (st->head == NULL) {
        printf("Стек пуст\n");
        return;
    }

    struct node* temp = st->head;
    printf("Удалён: %s\n", temp->inf);

    st->head = st->head->next;

    free(temp);

    if (st->head == NULL) {
        st->last = NULL;
    }
}

// Просмотр содержимого очереди
void review(struct stack* st) {
    struct node* struc = st->head;
    if (st->head == NULL) {
        printf("Стек пуст\n");
        return;
    }
    while (struc != NULL) {
        printf("Имя - %s\n", struc->inf);
        struc = struc->next;
    }
}

// Поиск элемента по содержимому
struct node* find(struct stack* st, char* name) {
    struct node* struc = st->head;
    if (st->head == NULL) {
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
void delete_by_name(struct stack* st, char* name) {
    struct node* struc = st->head;
    struct node* prev = NULL;

    if (st->head == NULL) {
        printf("Очередь пуста\n");
        return;
    }

    while (struc != NULL) {
        if (strcmp(name, struc->inf) == 0) {
            printf("Удаление элемента: %s\n", struc->inf);
            if (prev == NULL) { 
                st->head = struc->next;
            }
            else {
                prev->next = struc->next;
            }
            free(struc);
            return;
        }
        prev = struc;
        struc = struc->next;
    }

    printf("Элемент не найден\n");
}


int main() {
    setlocale(LC_ALL, "Rus");
    int choice;
    char name[256];

    struct stack st = { NULL };

    while (1) {
        printf("\nМеню:\n");
        printf("1. Добавить элемент в очередь\n");
        printf("2. Просмотр очереди\n");
        printf("3. Поиск элемента по имени\n");
        printf("4. Удалить элемент по имени\n");
        printf("5. Удалить элемент из стека\n");
        printf("6. Выйти\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            push(&st);
            break;
        case 2:
            review(&st);
            break;
        case 3:
            printf("Введите имя для поиска: ");
            scanf("%s", name);
            if (find(&st, name) != NULL)
                printf("Элемент найден: %s\n", name);
            break;
        case 4:
            printf("Введите имя для удаления: ");
            scanf("%s", name);
            delete_by_name(&st, name);
            break;
        case 5:
            pop(&st);
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
