#include<stdio.h>
#include<stdlib.h>


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;


int initialize(headNode** h);


int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;
	printf("[----길동현 2022041025----]\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {


	if(*h != NULL)
		freeList(*h); //h가 NULL이 아니라면 메모리 해제

	*h = (headNode*)malloc(sizeof(headNode)); //새로운 구조체 메모리할당하고 h가 가리키는 포인터에 할당된 메모리 주소 저장
	(*h)->first = NULL;
	return 1;
}

int freeList(headNode* h){
	listNode* p = h->first; //리스트의 첫번째 노드를 가리키는 포인터

	listNode* prev = NULL; 
	while(p != NULL) { //리스트 탐색 반복문
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { //리스트가 비어있는 경우 예외처리
		printf("Nothing to print....\n"); 
		return;
	}

	p = h->first; //리스트의 첫번째 노드를 가리키는 변수 p초기화

	while(p != NULL) { //리스트 탐색 반복문
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}



int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드 생성
	node->key = key; //키값 저장
	node->rlink = NULL; //rlink NULL로 초기화
	node->llink = NULL; //llink NULL로 초기화

	if (h->first == NULL) //리스트가 비어있는 경우
	{
		h->first = node; //새로운 노드를 첫번째 노드로 설정
		return 0;
	}

	listNode* n = h->first; //리스트의 첫번쨰 노드를 가리키는 포인터 변수 n 초기화
	while(n->rlink != NULL) { //리스트의 마지막 노드를 찾는 반복문
		n = n->rlink;
	}
	n->rlink = node;
	node->llink = n;
	return 0;
}



int deleteLast(headNode* h) {

	if (h->first == NULL)//리스트가 비어있는 경우 예외처리
	{
		printf("nothing to delete.\n"); 
		return 0;
	}

	listNode* n = h->first; //리스트의 첫번째 노드를 가리키는 포인터 변수 초기화
	listNode* trail = NULL; //n의 이전 노드를 가리키는 변수 trail 초기화


	if(n->rlink == NULL) { //리스트에 노드가 한개일때
		h->first = NULL; //첫번째 노드를 NULL로 설정
		free(n);
		return 0;
	}

	while(n->rlink != NULL) {//리스트 마지막 노드를 찾는 반복문
		trail = n;
		n = n->rlink;
	}

	trail->rlink = NULL;
	free(n);

	return 0;
}


int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //노드 생성
	node->key = key;
	node->rlink = node->llink = NULL;

	if(h->first == NULL) //리스트가 비어있을때
	{
		h->first = node; //새로운 노드를 리스트의 첫번째 노드로 추가
		return 1;
	}

	node->rlink = h->first; //새로운 노드의 rlink를 현재 첫번째 노드로 설정
	node->llink = NULL; // 새로운 노드의 llink를 NULL로 설정

	listNode *p = h->first; //포인터변수 p초기화
	p->llink = node; //llink를 새로운 노드로 설정
	h->first = node; //첫번째 노드를 새로운 노드를 설정

	return 0;
}

int deleteFirst(headNode* h) {

	if (h->first == NULL) //리스트가 비어있는 경우 예외
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; //첫번째 노드를 가리키는 변수 n초기화
	h->first = n->rlink; //첫번째 노드를 두번째 노드로 변경

	free(n);

	return 0;
}



int invertList(headNode* h) {


	if(h->first == NULL) {
		printf("nothing to invert...\n"); //역순으로 바꿀 노드가 없다는 메시지 출력
		return 0;
	}
	listNode *n = h->first; //첫번째 노드를 가리키는 포인터 변수 n 초기화
	listNode *trail = NULL; //역순으로 바꿀때 이전 노드를 가리키는 포인터변수 초기화
	listNode *middle = NULL; //역순으로 바꿀때 현재노드를 가리키는 변수 초기화

	while(n != NULL){
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	h->first = middle;

	return 0;
}



int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;

	while(n != NULL) {
		if(n->key >= key) {
			if(n == h->first) {
				insertFirst(h, key);
			} else {
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
			}
			return 0;
		}

		n = n->rlink;
	}

	insertLast(h, key);
	return 0;
}




int deleteNode(headNode* h, int key) {

	if (h->first == NULL) //연결리스트가 비어있는경우
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;

	while(n != NULL) {
		if(n->key == key) { //키값에 해당하는 노드를 찾은경우
			if(n == h->first) { //첫번째 노드인경우
				deleteFirst(h);
			} else if (n->rlink == NULL){ //마지막 노드인경우
				deleteLast(h);
			} else { //중간에 위치한 노드인 경우
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 1;
		}

		n = n->rlink;
	}

	printf("cannot find the node for key = %d\n", key);
	return 1;
}