#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct job {
	int ID;
	int take;
	int deadline;
}job;

int compare(job* first, job* second) {
	return first->deadline - second->deadline;
}

int main() {
	job job[100]; int job_num = 0;
	int ID, take, deadline;
	FILE* fp;
	fp = fopen("lateness.txt", "r");
	
	while (fscanf(fp, "%d %d %d", &ID, &take, &deadline) != EOF) {
		job[job_num].ID = ID; job[job_num].take = take; job[job_num++].deadline = deadline;
	}
	fclose(fp);

	//deadline을 기준으로 오름차순 정렬 --> O(nlogn)
	qsort(job, job_num, sizeof(job[0]), compare);

	/*
	for (int i = 0; i < job_num; i++) {
		printf("%d %d %d\n", job[i].ID, job[i].take, job[i].deadline);
	}
	*/

	printf("JOB ID   START   FINISH   LATENESS\n");

	//lateness = max{0, start + take - deadline}
	int start = 0; int lateness; int max = 0;
	for (int i = 0; i < job_num; i++) {
		lateness = start + job[i].take - job[i].deadline;
		if (lateness < 0) lateness = 0;
		if (lateness > max) max = lateness;
		
		printf("%6d %7d %8d %10d\n", job[i].ID, start, start + job[i].take, lateness);
		start = start + job[i].take; //다음 job의 시작은 이번 job이 시작하여 걸린 시간을 더한 값이 된다
	}
	printf("\n       Maximum Lateness: %d\n", max);
}