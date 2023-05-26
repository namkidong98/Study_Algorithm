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

	//profit을 기준으로 내림차순으로 데이터를 정렬 --> O(nlogn)
	qsort(job, num_job, sizeof(job[0]), compare);

	/* 내림차순으로 정렬된 데이터를 출력하는 함수(for debugging)
	for (int i = 0; i < num_job; i++) {
		printf("%d %d %d\n", job[i].ID, job[i].deadline, job[i].profit);
	}
	*/

	//정렬된 n개의 job을 기준으로 linked list에 추가시킬지 판단하고 추가하는 부분 --> O(n^2)
	head = NULL;
	for (int i = 0; i < num_job; i++) {
		//해당 순서의 job에 대한 노드를 만들고 초기화
		temp = (node_pointer)malloc(sizeof(node));
		temp->ID = job[i].ID;
		temp->deadline = job[i].deadline;
		temp->profit = job[i].profit;
		temp->next = NULL;

		if (i == 0) {
			head = temp;
			continue;
		}

		//기존에 만들어진 linked list를 보면서 삽입되어야 할 위치를 파악
		count = 1; flag = 0; prev = head; target = NULL;
		for (ptr = head; ptr != NULL; ) {
			if (temp->deadline < ptr->deadline && target == NULL) {
				target = ptr; //삽입해야 할 위치를 target 포인터로 저장해놓고
				if (count > temp->deadline) flag = 1;	//해당 노드가 들어오는 날짜에 이미 deadline을 지나면 flag = 1
				count++; //해당 노드가 추가되었다고 가정하면 count는 1 증가시키고 고려해야 한다
			}
			if (target != NULL) {
				if (count > ptr->deadline) flag = 1; //해당 노드를 넣으면 안 된다는 신호
			}

			count++; //다음 날짜로 만들고
			if(target == NULL) prev = ptr; //현재 위치를 prev로 가리키고
			ptr = ptr->next; //ptr는 다음 노드를 가리키도록 변경
		}

		if (target != NULL) { //temp가 위치할 부분이 linked list의 중간에 위치한다면
			if (flag == 0) { //flag가 0이면 삽입해도 되는 것이고 1이면 삽입하면 안 되는 경우이다
				if (prev == head) head = temp; //새로운 노드가 linked list의 맨 앞에 위치해야 하는 경우
				else prev->next = temp;
				temp->next = target;
			}
			else { //해당 노드(temp)가 위치해야할 날짜가 이미 해당 노드의 deadline을 지났다면, 추가하지 않음
				   //혹은 해당 노드를 넣음으로써 뒤의 일정들이 deadline이 밀리게 된다면, 추가하지 않음
				free(temp);
			}
		}
		else { //temp가 linked list의 맨 끝에 위치해야 한다면
			prev->next = temp;
			temp->next = NULL;
		}
	}

	//greedy로 스케줄된 job을 차례대로 출력
	printf("JOB ID   DEADLINE    PROFIT\n");
	for (ptr = head; ptr != NULL; ptr = ptr->next) {
		printf("%6d   %8d   %7d\n", ptr->ID, ptr->deadline, ptr->profit);
	}
}