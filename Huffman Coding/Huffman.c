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
int num = 0;	//서로 다른 문자의 개수

int main() {
	char code[MAXLINE]; int len;
	FILE* fp;
	fp = fopen("Huffman.txt", "r");
	
	//파일에서 문자열을 가져온다
	fgets(code, MAXLINE, fp);
	fclose(fp);
	len = (int)strlen(code);

	//각 문자열과 빈도수를 담은 노드들로 만들고 freq 기준으로 오름차순 정렬한다
	single_node_trees(code, len);

	//greedy에 따라 하나의 tree로 merge한다(자주 사용되는 symbol이 적은 수의 0, 1 조합으로 만들어질 수 있도록 설계)
	make_tree(num);
	
	//각각의 symbol이 어떤 숫자로 변환되는지를 출력해준다
	code[0] = '\0';
	printf("SYMBOL   FREQ    CODE\n");
	traversal(head, code); //왼쪽 child로 갈 때마다 0을, 오른쪽 child로 갈때마다 1을 추가하여
						   //마지막에 특정 symbol을 어떤 binary code로 바꿀지 알려주는 함수
}
void single_node_trees(char* code, int len) {
	int i, freq; char symbol;
	node_pointer ptr, ptr2, temp;

	for (i = 0; i < len; i++) {
		for (ptr = head; ptr != NULL; ptr = ptr->next) { 
			if (code[i] == ptr->symbol) { //기존 symbol과 동일한 char이 나왔다면
				ptr->freq++; //해당 노드의 빈도수를 1증가
				break;
			}
		}
		if (ptr == NULL) { //새로운 symbol이 등장했다면
			temp = (node_pointer)malloc(sizeof(node));
			temp->symbol = code[i];
			temp->freq = 1;
			temp->left = NULL;
			temp->right = NULL;

			//head 앞에 넣고 새로운 앞부분을 head로 가리키게 하는 방식
			temp->next = head;
			head = temp;
			
			num++;	//symbol의 숫자를 증가
		}
	}

	//처음에 freq를 기준으로 오름차순 정렬(selection sort 방식)
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
		u = ptr; //맨 앞에 있는 노드가 freq가 제일 적어서 u가 됨
		ptr = ptr->next;
		v = ptr; //두 번째 있는 노드가 v가 됨
		head = ptr->next; //head를 앞에 두개 노드를 뺀 뒤의 linked list를 가리키게 함

		//u와 v를 통해 w를 생성
		w = (node_pointer)malloc(sizeof(node));
		w->symbol = 0;
		w->freq = u->freq + v->freq;
		w->left = u;
		w->right = v;
		w->next = NULL;
		if (i == num - 2) { //마지막에 2개의 노드만 남아서 w를 만들면 w를 head로 가리키고 종료
			head = w;
			break;
		}

		prev = NULL;
		//w를 linked list에 freq를 기준으로 오름차순이 되게 적절한 위치에 삽입
		for (ptr = head; ptr != NULL; ptr = ptr->next) {
			if (w->freq < ptr->freq) {
				if (prev == NULL) { //w가 맨 처음으로 삽입되어야 하는 경우
					w->next = head;
					head = w;
					break;
				}
				prev->next = w;
				w->next = ptr;
				break;
			}

			prev = ptr;
			if (ptr->next == NULL) { //w가 맨 마지막에 삽입되어야 하는 경우
				ptr->next = w;
				w->next = NULL;
			}
		}
	}
}
void traversal(node_pointer root, char* str) { 
	char buf[MAXLINE];

	if (root->symbol != 0) { //leaf 노드에서는 
		printf("%6c   %4d    %s\n", root->symbol, root->freq, str);
		return;
	}

	strcpy(buf, str);
	strcat(buf, "0"); //기존에 받은 str에 누적하여 0을 추가해서 넘김
	traversal(root->left, buf);

	strcpy(buf, str);
	strcat(buf, "1"); //기존에 받은 str에 누적하여 1을 추가해서 넘김
	traversal(root->right, buf);
}