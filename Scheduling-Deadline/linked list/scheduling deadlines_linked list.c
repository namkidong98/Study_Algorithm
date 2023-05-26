#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* node_pointer;
typedef struct node{
	int ID;
	int deadline;
	int profit;
	node_pointer next;
}node;

typedef struct {
	int ID;
	int deadline;
	int profit;
}job;

int compare(job* first, job* second) {
	return (second->profit - first->profit);
}

int main() {
	FILE* fp;
	int ID, deadline, profit;
	job job[100]; int num_job = 0; int num_node = 0;
	node_pointer head, ptr, temp, prev, target;
	int count, flag;

	fp = fopen("deadline.txt", "r");

	while (fscanf(fp, "%d %d %d\n", &ID, &deadline, &profit) != EOF) {
		job[num_job].ID = ID; job[num_job].deadline = deadline; job[num_job++].profit = profit;
	}
	fclose(fp);

	//profit�� �������� ������������ �����͸� ���� --> O(nlogn)
	qsort(job, num_job, sizeof(job[0]), compare);

	/* ������������ ���ĵ� �����͸� ����ϴ� �Լ�(for debugging)
	for (int i = 0; i < num_job; i++) {
		printf("%d %d %d\n", job[i].ID, job[i].deadline, job[i].profit);
	}
	*/

	//���ĵ� n���� job�� �������� linked list�� �߰���ų�� �Ǵ��ϰ� �߰��ϴ� �κ� --> O(n^2)
	head = NULL;
	for (int i = 0; i < num_job; i++) {
		//�ش� ������ job�� ���� ��带 ����� �ʱ�ȭ
		temp = (node_pointer)malloc(sizeof(node));
		temp->ID = job[i].ID;
		temp->deadline = job[i].deadline;
		temp->profit = job[i].profit;
		temp->next = NULL;

		if (i == 0) {
			head = temp;
			continue;
		}

		//������ ������� linked list�� ���鼭 ���ԵǾ�� �� ��ġ�� �ľ�
		count = 1; flag = 0; prev = head; target = NULL;
		for (ptr = head; ptr != NULL; ) {
			if (temp->deadline < ptr->deadline && target == NULL) {
				target = ptr; //�����ؾ� �� ��ġ�� target �����ͷ� �����س���
				if (count > temp->deadline) flag = 1;	//�ش� ��尡 ������ ��¥�� �̹� deadline�� ������ flag = 1
				count++; //�ش� ��尡 �߰��Ǿ��ٰ� �����ϸ� count�� 1 ������Ű�� ����ؾ� �Ѵ�
			}
			if (target != NULL) {
				if (count > ptr->deadline) flag = 1; //�ش� ��带 ������ �� �ȴٴ� ��ȣ
			}

			count++; //���� ��¥�� �����
			if(target == NULL) prev = ptr; //���� ��ġ�� prev�� ����Ű��
			ptr = ptr->next; //ptr�� ���� ��带 ����Ű���� ����
		}

		if (target != NULL) { //temp�� ��ġ�� �κ��� linked list�� �߰��� ��ġ�Ѵٸ�
			if (flag == 0) { //flag�� 0�̸� �����ص� �Ǵ� ���̰� 1�̸� �����ϸ� �� �Ǵ� ����̴�
				if (prev == head) head = temp; //���ο� ��尡 linked list�� �� �տ� ��ġ�ؾ� �ϴ� ���
				else prev->next = temp;
				temp->next = target;
			}
			else { //�ش� ���(temp)�� ��ġ�ؾ��� ��¥�� �̹� �ش� ����� deadline�� �����ٸ�, �߰����� ����
				   //Ȥ�� �ش� ��带 �������ν� ���� �������� deadline�� �и��� �ȴٸ�, �߰����� ����
				free(temp);
			}
		}
		else { //temp�� linked list�� �� ���� ��ġ�ؾ� �Ѵٸ�
			prev->next = temp;
			temp->next = NULL;
		}
	}

	//greedy�� �����ٵ� job�� ���ʴ�� ���
	printf("JOB ID   DEADLINE    PROFIT\n");
	for (ptr = head; ptr != NULL; ptr = ptr->next) {
		printf("%6d   %8d   %7d\n", ptr->ID, ptr->deadline, ptr->profit);
	}
}