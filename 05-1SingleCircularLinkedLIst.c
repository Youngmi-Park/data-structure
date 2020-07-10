#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define IS_EMPTY(temp) (!(temp)) //Empty list가 비어있는지 테스트
#define IS_FULL(temp) (!(temp))

typedef struct listNode* list_pt;//구조체를 가리키는 포인터
typedef struct listNode {
	int num; // 번호를 저장하는 변수
	char name[10];//이름을 저장하는 변수
	list_pt link; // 구조체 포인터
}listNode;

typedef struct cirList {//원형연결리스트 노드를 가리키는 포인터
	list_pt head;//첫 노드
	list_pt ptr;//이동하는 노드
	list_pt tail;//제일 마지막 노드
	int nodeNum;//노드 개수
}cirList;

void printList(list_pt ptr);//Circular LInked List출력함수
void freeList(list_pt head, list_pt ptr);//동적메모리 해제함수

void main()
{
	int n = 0;//입력받은 숫자를 저장, 몇개의 숫자를 입력받을것인지
	int skipNum = 0;//임의의 번호를 저장하는 변수
	srand(time(NULL));//rand 함수 실행을 위한 srand함수

	cirList* ptList = (cirList*)malloc(sizeof(cirList));//초기화
	ptList->head = NULL;
	ptList->tail = NULL;
	ptList->ptr = NULL;
	ptList->nodeNum = 0;

	for (int i = 1; i < 38; i++)//37명으로 linked list 생성
	{
		list_pt temp = (list_pt)malloc(sizeof(listNode));
		if (IS_FULL(temp))//heap영역이 없으면 NULL반환
		{
			fprintf(stderr, "메모리가 가득찼습니다.\n");
			exit(1);
		}

		printf("%d번 사람의 이름을 입력하세요 : ", i);//사람의 이름을 입력받음
		gets(temp->name);//temp의 name에 입력받은 이름 저장
		temp->num = i;//temp의 num에 입력받은 값 저장
		temp->link = NULL;//temp의 link에 NULL저장

		if (temp->num==1)//head가 가리키는 노드가 NULL일때(빈노드일때, 첫번째 노드를 삽입)
		{
			ptList->head = temp;//Head가 temp를 가리킴
			ptList->tail = temp;//tail이 temp를 가리킴
			temp->link = temp;//자기자신을 가리킴
		}
		else//첫번째 입력이 아닐때 앞에 삽입
		{
			temp->link = ptList->head;//이동하는 포인터를 첫번째 노드를 가리키게한다.
			ptList->tail->link = temp;//끝노드의 link를 새로운 입력에 연결
			ptList->tail = temp;//tail을 마지막노드를 가리키게 이동시킴
		}
		ptList->nodeNum++;//인원수 체크, 노드개수 증가
		printf("생성된 Circular Linked List는 ");
		printList(ptList);//LInked List출력함수
	}
	printf("현재 node개수는%d입니다.\n", ptList->nodeNum);

	//한명씩 제거하는 코드
	ptList->ptr = ptList->head;//ptr이 처음을 가리키게함

	while (ptList->nodeNum > 3)//3명이 아닌동안(3명이 남을 때 까지)
	{
		skipNum = rand() % (ptList->nodeNum);//nodeNum범위에서 숫자를 뽑음
		printf("\n******Skip Number는 %d입니다.*******\n", skipNum);
		for (int i = 1; i < skipNum; i++)
		{
			ptList->ptr = ptList->ptr->link;//skipNum만큼 포인터이동
		}
		printf("탈락한 사람은 %d번 %s입니다.\n", ptList->ptr->link->num, ptList->ptr->link->name);
		
		if (ptList->ptr->link == ptList->head)//제거하고자하는 노드를 head가 가리키고 있을 때
		{
			ptList->head = ptList->ptr->link->link;//head를 현재 head노드의 다음 노드를 가리키게한다.
			ptList->ptr->link = ptList->ptr->link->link;//다음 노드로 연결
			(ptList->nodeNum)--;//노드 수 감소
		}
		else if (ptList->ptr->link == ptList->tail)//제거하고자하는 노드를 tail이 가리키고 있을 때
		{
			ptList->tail = ptList->ptr;//tail을 현재 tail노드의 이전 노드를 가리키게 한다.
			ptList->ptr->link = ptList->ptr->link->link;//다음 노드로 연결
			(ptList->nodeNum)--;//노드 수 감소
		}
		else
		{
			ptList->ptr->link = ptList->ptr->link->link;//다음것을 연결
			(ptList->nodeNum)--;//노드수감소
		}
		printList(ptList);//LInked List출력함수
			
		if (ptList->nodeNum == 3)//3명이 남았을 때
		{
			printf("\n-------------선정완료--------------\n");
			printf("최종선발된 3인은 ");
			printList(ptList);//최종적으로 남은 3명만 출력
			break;
		}
	}
	free(ptList->head, ptList->ptr);//메모리 해제
	system("PAUSE");
	return 0;
	}
	
void printList(cirList* pt)	
{
	list_pt tmp;
	tmp = pt->head;

	if (pt->head) {
		do
		{
			printf("%d번-", tmp->num);//tmp가 가리키는 num을 출력
			printf("%s ", tmp->name);//tmp가 가리키는 name을 출력
			tmp = tmp->link;
		} while (tmp != pt->head);
		printf("입니다.\n\n");
	}
}

void freeList(list_pt head, list_pt ptr)
{
	while (head != NULL)//할당받은 메모리를 해제시킴
	{
		ptr = head;
		head = ptr->link;//첫번째 노드를 바꿈
		free(ptr);//노드를 해제시킴
	}
}