#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct node
{
	char inf[256];  // �������� ����������
	struct node* next; // ������ �� ��������� ������� 
};


struct node* head = NULL, * last = NULL, * f = NULL; // ��������� �� ������ � ��������� �������� ������
int dlinna = 0;

// ������� ���������� ��������, ��������� ������
void spstore(void), review(void), del(char* name);

char find_el[256];
struct node* find(char* name); // ������� ���������� ��������
struct node* get_struct(void); // ������� �������� ��������



struct node* get_struct(void)
{
	struct node* p = NULL;
	char s[256];

	if ((p = (struct node*)malloc(sizeof(struct node))) == NULL)  // �������� ������ ��� ����� ������� ������
	{
		printf("������ ��� ������������� ������\n");
		exit(1);
	}

	printf("������� �������� �������: \n");   // ������ ������
	scanf("%s", s);
	if (*s == 0)
	{
		printf("������ �� ���� �����������\n");
		return NULL;
	}
	strcpy(p->inf, s);

	p->next = NULL;

	return p;		// ���������� ��������� �� ��������� �������
}

/* ���������������� ���������� � ������ �������� (� �����)*/
void spstore(void)
{
	struct node* p = NULL;
	p = get_struct();
	if (head == NULL && p != NULL)	// ���� ������ ���, �� ������������� ������ ������
	{
		head = p;
		last = p;
	}
	else // ������ ��� ����, �� ��������� � �����
	{
		struct node* curr = head;
		struct node* prev = NULL;

		while (curr != NULL && strlen(curr->inf) < strlen(p->inf)) {
			prev = curr;
			curr = curr->next;
		}
		if (prev == NULL) {
			p->next = head;
			head = p;
		}
		else {
			prev->next = p;
			p->next = curr;
		}
		if (p->next == NULL) {
			last = p;
		}
	}
	return;
}


/* �������� ����������� ������. */
void review(struct node* first)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("������ ����\n");
	}
	while (struc)
	{
		printf("��� - %s, \n", struc->inf);
		struc = struc->next;
	}
	return;
}




/* ����� �������� �� �����������. */
struct node* find(char* name)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("������ ����\n");
	}
	while (struc)
	{
		if (strcmp(name, struc->inf) == 0)
		{
			return struc;
		}
		struc = struc->next;
	}
	printf("������� �� ������\n");
	return NULL;
}

/* �������� �������� �� �����������. */
void del(char* name)
{
	struct node* struc = head; // ���������, ���������� �� ������ ���������� �� ������ ������
	struct node* prev = NULL;// ��������� �� �������������� ���������� �������
	int flag = 0;      // ��������� ���������� ���������� �������� � ������

	if (head == NULL) // ���� ������ ������ ����� NULL, �� ������ ����
	{
		printf("������ ����\n");
		return;
	}

	if (strcmp(name, struc->inf) == 0) // ���� ��������� ������� - ������
	{
		flag = 1;
		head = struc->next; // ������������� ������ �� ��������� �������
		free(struc);  // ������� ������ �������
		struc = head; // ������������� ��������� ��� ����������� ������
	}
	else
	{
		prev = struc;
		struc = struc->next;
	}

	while (struc) // ������ �� ������ � ����� ���������� ��������
	{
		if (strcmp(name, struc->inf) == 0) // ���� �����, ��
		{
			flag = 1;         // ���������� ���������
			if (struc->next)  // ���� ��������� ������� �� ��������� � ������
			{
				prev->next = struc->next; // ������ ���������
				free(struc);		    // �������  �������
				struc = prev->next; // ������������� ��������� ��� ����������� ������
			}
			else			// ���� ��������� ������� ��������� � ������
			{
				prev->next = NULL; // �������� ��������� ��������������� ��������
				free(struc);	// �������  �������
				return;
			}
		}
		else // ���� �� �����, ��
		{
			prev = struc; // ������������� ��������� ��� ����������� ������
			struc = struc->next;
		}
	}

	if (flag == 0)				// ���� ���� = 0, ������ ������ ������� �� ������
	{
		printf("������� �� ������\n");
		return;
	}


}

int main()
{
	setlocale(LC_ALL, "Rus");
	int choice;
	char name[256];

	while (1)
	{
		printf("\n����:\n");
		printf("1. �������� ������� � ������\n");
		printf("2. �������� ������\n");
		printf("3. ����� �������� �� �����\n");
		printf("4. ������� ������� �� �����\n");
		printf("5. �����\n");
		printf("�������� ��������: ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			spstore(); // ���������� ��������
			break;
		case 2:
			review(head); // �������� ������
			break;
		case 3:
			printf("������� ��� ��� ������: ");
			scanf("%s", name);
			if (find(name) != NULL)
				printf("������� ������: %s\n", name);
			break;
		case 4:
			printf("������� ��� ��� ��������: ");
			scanf("%s", name);
			del(name); // �������� ��������
			break;
		case 5:
			printf("�����\n");
			exit(0);
		default:
			printf("�������� �����\n");
			break;
		}
	}

	return 0;
}