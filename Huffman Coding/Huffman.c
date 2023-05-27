#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

typedef struct node* node_pointer;
typedef struct node {
	char symbol;
	int freq;
	node_pointer left;
	node_pointer right;
	node_pointer next;
}node;

typedef struct ans {
	char symbol;
	int number;
}ans;

void single_node_trees(char* code, int len);
void make_tree();
void traversal(node_pointer root, char* str);

node_pointer head = NULL;
int num = 0;	//���� �ٸ� ������ ����

int main() {
	char code[MAXLINE]; int len;
	FILE* fp;
	fp = fopen("Huffman.txt", "r");
	
	//���Ͽ��� ���ڿ��� �����´�
	fgets(code, MAXLINE, fp);
	fclose(fp);
	len = (int)strlen(code);

	//�� ���ڿ��� �󵵼��� ���� ����� ����� freq �������� �������� �����Ѵ�
	single_node_trees(code, len);

	//greedy�� ���� �ϳ��� tree�� merge�Ѵ�(���� ���Ǵ� symbol�� ���� ���� 0, 1 �������� ������� �� �ֵ��� ����)
	make_tree(num);
	
	//������ symbol�� � ���ڷ� ��ȯ�Ǵ����� ������ش�
	code[0] = '\0';
	printf("SYMBOL   FREQ    CODE\n");
	traversal(head, code); //���� child�� �� ������ 0��, ������ child�� �������� 1�� �߰��Ͽ�
						   //�������� Ư�� symbol�� � binary code�� �ٲ��� �˷��ִ� �Լ�
}
void single_node_trees(char* code, int len) {
	int i, freq; char symbol;
	node_pointer ptr, ptr2, temp;

	for (i = 0; i < len; i++) {
		for (ptr = head; ptr != NULL; ptr = ptr->next) { 
			if (code[i] == ptr->symbol) { //���� symbol�� ������ char�� ���Դٸ�
				ptr->freq++; //�ش� ����� �󵵼��� 1����
				break;
			}
		}
		if (ptr == NULL) { //���ο� symbol�� �����ߴٸ�
			temp = (node_pointer)malloc(sizeof(node));
			temp->symbol = code[i];
			temp->freq = 1;
			temp->left = NULL;
			temp->right = NULL;

			//head �տ� �ְ� ���ο� �պκ��� head�� ����Ű�� �ϴ� ���
			temp->next = head;
			head = temp;
			
			num++;	//symbol�� ���ڸ� ����
		}
	}

	//ó���� freq�� �������� �������� ����(selection sort ���)
	for (ptr = head; ptr->next != NULL; ptr = ptr->next) {
		for (ptr2 = ptr->next; ptr2 != NULL; ptr2 = ptr2->next) {
			if (ptr->freq > ptr2->freq) {
				symbol = ptr->symbol;
				freq = ptr->freq;
				ptr->symbol = ptr2->symbol;
				ptr->freq = ptr2->freq;
				ptr2->symbol = symbol;
				ptr2->freq = freq;
			}
		}
	}
}
void make_tree() {
	int i;
	node_pointer u, v, w, ptr, prev;

	for (i = 0; i < num - 1; i++) {
		ptr = head;
		u = ptr; //�� �տ� �ִ� ��尡 freq�� ���� ��� u�� ��
		ptr = ptr->next;
		v = ptr; //�� ��° �ִ� ��尡 v�� ��
		head = ptr->next; //head�� �տ� �ΰ� ��带 �� ���� linked list�� ����Ű�� ��

		//u�� v�� ���� w�� ����
		w = (node_pointer)malloc(sizeof(node));
		w->symbol = 0;
		w->freq = u->freq + v->freq;
		w->left = u;
		w->right = v;
		w->next = NULL;
		if (i == num - 2) { //�������� 2���� ��常 ���Ƽ� w�� ����� w�� head�� ����Ű�� ����
			head = w;
			break;
		}

		prev = NULL;
		//w�� linked list�� freq�� �������� ���������� �ǰ� ������ ��ġ�� ����
		for (ptr = head; ptr != NULL; ptr = ptr->next) {
			if (w->freq < ptr->freq) {
				if (prev == NULL) { //w�� �� ó������ ���ԵǾ�� �ϴ� ���
					w->next = head;
					head = w;
					break;
				}
				prev->next = w;
				w->next = ptr;
				break;
			}

			prev = ptr;
			if (ptr->next == NULL) { //w�� �� �������� ���ԵǾ�� �ϴ� ���
				ptr->next = w;
				w->next = NULL;
			}
		}
	}
}
void traversal(node_pointer root, char* str) { 
	char buf[MAXLINE];

	if (root->symbol != 0) { //leaf ��忡���� 
		printf("%6c   %4d    %s\n", root->symbol, root->freq, str);
		return;
	}

	strcpy(buf, str);
	strcat(buf, "0"); //������ ���� str�� �����Ͽ� 0�� �߰��ؼ� �ѱ�
	traversal(root->left, buf);

	strcpy(buf, str);
	strcat(buf, "1"); //������ ���� str�� �����Ͽ� 1�� �߰��ؼ� �ѱ�
	traversal(root->right, buf);
}