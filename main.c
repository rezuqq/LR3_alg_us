#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

struct node {
    char inf[256];      // �������� ����������
    struct node* next;  // ������ �� ��������� �������
};

struct queue {
    struct node* head;  // ��������� �� ������ (������) �������
    struct node* last;  // ��������� �� ����� (�����) �������
};

// ������� �������� ������ ����
struct node* get_struct(void) {
    struct node* p = NULL;
    char s[256];

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL) {  // �������� ������ ��� ����� ������� ������
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
    p->next = NULL;  // ���������� �������� ���
    return p;
}

// ���������� �������� � ����� ������� (enqueue)
void enqueue(struct queue* q) {
    struct node* p = get_struct();
    if (p == NULL) return;  // ���� ������� �� ��� ������

    if (q->head == NULL) {  // ���� ������� ������
        q->head = p;
        q->last = p;
    }
    else {  // ���� ������� ��� ����������
        q->last->next = p;
        q->last = p;
    }
}

// �������� �������� �� ������ ������� (dequeue)
void dequeue(struct queue* q) {
    if (q->head == NULL) {  // ���� ������� �����
        printf("������� �����\n");
        return;4
    }

    struct node* temp = q->head;
    printf("��������: %s\n", temp->inf);
    q->head = q->head->next;
    free(temp);

    if (q->head == NULL) {  // ���� ������� ����� ������
        q->last = NULL;
    }
}

// �������� ����������� �������
void review(struct queue* q) {
    struct node* struc = q->head;
    if (q->head == NULL) {
        printf("������� �����\n");
        return;
    }
    while (struc != NULL) {
        printf("��� - %s\n", struc->inf);
        struc = struc->next;
    }
}

// ����� �������� �� �����������
struct node* find(struct queue* q, char* name) {
    struct node* struc = q->head;
    if (q->head == NULL) {
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
void delete_by_name(struct queue* q, char* name) {
    struct node* struc = q->head;
    struct node* prev = NULL;

    if (q->head == NULL) {
        printf("������� �����\n");
        return;
    }

    while (struc != NULL) {
        if (strcmp(name, struc->inf) == 0) {
            printf("�������� ��������: %s\n", struc->inf);
            if (prev == NULL) {  // ���� ������� ������
                q->head = struc->next;
            }
            else {
                prev->next = struc->next;
            }
            if (struc == q->last) {  // ���� ������� ���������
                q->last = prev;
            }
            free(struc);
            return;
        }
        prev = struc;
        struc = struc->next;
    }

    printf("������� �� ������\n");
}

// �������� �������
int main() {
    setlocale(LC_ALL, "Rus");
    int choice;
    char name[256];

    struct queue q = { NULL, NULL };  // ������������� ������ �������

    while (1) {
        printf("\n����:\n");
        printf("1. �������� ������� � �������\n");
        printf("2. �������� �������\n");
        printf("3. ����� �������� �� �����\n");
        printf("4. ������� ������� �� �����\n");
        printf("5. ������� ������� �� ������ ������� (dequeue)\n");
        printf("6. �����\n");
        printf("�������� ��������: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            enqueue(&q);  // ���������� ��������
            break;
        case 2:
            review(&q);  // �������� �������
            break;
        case 3:
            printf("������� ��� ��� ������: ");
            scanf("%s", name);
            if (find(&q, name) != NULL)
                printf("������� ������: %s\n", name);
            break;
        case 4:
            printf("������� ��� ��� ��������: ");
            scanf("%s", name);
            delete_by_name(&q, name);  // �������� �������� �� �����
            break;
        case 5:
            dequeue(&q);  // �������� �������� �� ������ �������
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
