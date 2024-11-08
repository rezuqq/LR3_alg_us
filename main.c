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
        printf("������ ��� ������������� ������\n");
        exit(1);
    }

    printf("������� �������� �������: \n");
    scanf("%s", s);
    if (*s == 0) {
        printf("������ �� ���� �����������\n");
        return NULL;
    }
    strcpy(p->inf, s);
    p->next = NULL;
    return p;
}

// ���������� �������� � ����
void push(struct stack* st) {
    struct node* p = get_struct();
    if (p == NULL) return;

    p->next = st->head;
    st->head = p;
}

// �������� �������� �� �����
void pop(struct stack* st) {
    if (st->head == NULL) {
        printf("���� ����\n");
        return;
    }

    struct node* temp = st->head;
    printf("�����: %s\n", temp->inf);

    st->head = st->head->next;

    free(temp);

    if (st->head == NULL) {
        st->last = NULL;
    }
}

// �������� ����������� �������
void review(struct stack* st) {
    struct node* struc = st->head;
    if (st->head == NULL) {
        printf("���� ����\n");
        return;
    }
    while (struc != NULL) {
        printf("��� - %s\n", struc->inf);
        struc = struc->next;
    }
}

// ����� �������� �� �����������
struct node* find(struct stack* st, char* name) {
    struct node* struc = st->head;
    if (st->head == NULL) {
        printf("������� �����\n");
        return NULL;
    }
    while (struc) {
        if (strcmp(name, struc->inf) == 0) {
            return struc;
        }
        struc = struc->next;
    }
    printf("������� �� ������\n");
    return NULL;
}

// �������� �������� �� �����������
void delete_by_name(struct stack* st, char* name) {
    struct node* struc = st->head;
    struct node* prev = NULL;

    if (st->head == NULL) {
        printf("������� �����\n");
        return;
    }

    while (struc != NULL) {
        if (strcmp(name, struc->inf) == 0) {
            printf("�������� ��������: %s\n", struc->inf);
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

    printf("������� �� ������\n");
}


int main() {
    setlocale(LC_ALL, "Rus");
    int choice;
    char name[256];

    struct stack st = { NULL };

    while (1) {
        printf("\n����:\n");
        printf("1. �������� ������� � �������\n");
        printf("2. �������� �������\n");
        printf("3. ����� �������� �� �����\n");
        printf("4. ������� ������� �� �����\n");
        printf("5. ������� ������� �� �����\n");
        printf("6. �����\n");
        printf("�������� ��������: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            push(&st);
            break;
        case 2:
            review(&st);
            break;
        case 3:
            printf("������� ��� ��� ������: ");
            scanf("%s", name);
            if (find(&st, name) != NULL)
                printf("������� ������: %s\n", name);
            break;
        case 4:
            printf("������� ��� ��� ��������: ");
            scanf("%s", name);
            delete_by_name(&st, name);
            break;
        case 5:
            pop(&st);
            break;
        case 6:
            printf("�����\n");
            exit(0);
        default:
            printf("�������� �����\n");
            break;
        }
    }

    return 0;
}
