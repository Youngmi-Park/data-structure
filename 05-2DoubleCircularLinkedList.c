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
	list_pt prev; // 이전 노드를 가리키는 포인터
	list_pt next; // 다음 노드를 가리키는 포인터
}listNode;

typedef struct cirList {//원형연결리스트 노드를 가리키는 포인터
	list_pt head;//첫 노드
	list_pt ptr;//이동하는 노드
	list_pt tail;//제일 마지막 노드
	int nodeNum;//노드 개수
}cirList;

void printList(list_pt ptr);//Circular LInked List출력함수
void reversePrintList(list_pt ptr);//Circular Linke List 역순출력함수
void freeList(list_pt head, list_pt ptr);//동적메모리 해제함수

void main()
{
	int n = 0;//입력받은 숫자를 저장, 몇개의 숫자를 입력받을것인지
	int skipNum = 0;//임의의 번호를 저장하는 변수
	int wayNum = 1;//방향을 설정하는 변수
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
		temp->prev = NULL;//temp의 link에 NULL저장
		temp->next = NULL;//temp의 link에 NULL저장

		if (temp->num == 1)//head가 가리키는 노드가 NULL일때(빈노드일때, 첫번째 노드를 삽입)
		{
			ptList->head = temp;//Head가 temp를 가리킴
			ptList->tail = temp;//tail이 temp를 가리킴
			temp->prev = temp;//자기자신을 가리킴
			temp->next = temp;
		}
		else//첫번째 입력이 아닐때 앞에 삽입
		{
			temp->prev = ptList->tail;
			temp->next = ptList->head;//이동하는 포인터를 첫번째 노드를 가리키게한다.
			ptList->tail->next = temp;//끝노드의 next를 새로운 노드에 연결
			ptList->head->prev = temp;//첫노드의 prev를 새로운 노드에 연결
			ptList->tail = temp;//tail을 마지막노드를 가리키게 이동시킴
		}
		ptList->nodeNum++;//인원수 체크, 노드개수 증가
		printf("생성된 Doubly Circular Linked List는 ");
		printList(ptList);//LInked List출력함수void reversePrintList(list_pt ptr);
		printf("생성된 역순 Doubly Circular Linked List는 ");
		reversePrintList(ptList);//Linked List 역순으로 출력
	}
	printf("현재 node개수는%d입니다.\n", ptList->nodeNum);

	//한명씩 제거하는 코드
	ptList->ptr = ptList->head;//ptr이 처음을 가리키게함

	while (ptList->nodeNum > 3)//3명이 아닌동안(3명이 남을 때 까지)
	{
		skipNum = (rand() % (ptList->nodeNum))+1;//nodeNum범위에서 숫자를 뽑음
		printf("\n******Skip Number는 %d입니다.*******\n", skipNum);
		if (wayNum % 2 == 1)//홀수이면 우측으로 이동
		{
			for (int i = 1; i < skipNum; i++)
			{
				ptList->ptr = ptList->ptr->next;//skipNum만큼 포인터이동
			}
			printf("우측으로 %d만큼 이동합니다.\n", skipNum);
			printf("탈락한 사람은 %d번 %s입니다.\n", ptList->ptr->next->num, ptList->ptr->next->name);

			if (ptList->ptr->next == ptList->head)//제거하고자하는 노드를 head가 가리키고 있을 때
			{
				ptList->head = ptList->ptr->next->next;//head를 현재 head노드의 다음 노드를 가리키게한다.
				ptList->ptr->next = ptList->ptr->next->next;//다음 노드로 연결
				ptList->ptr->next->prev = ptList->ptr;//다음노드의 prev에 연결
				(ptList->nodeNum)--;//노드 수 감소
			}
			else if (ptList->ptr->next == ptList->tail)//제거하고자하는 노드를 tail이 가리키고 있을 때
			{
				ptList->tail = ptList->ptr;//tail을 현재 tail노드의 이전 노드를 가리키게 한다.
				ptList->ptr->next = ptList->ptr->next->next;//다음 노드로 연결
				ptList->ptr->next->prev = ptList->ptr;//다음노드의 prev에 연결
				(ptList->nodeNum)--;//노드 수 감소
			}
			else
			{
				ptList->ptr->next = ptList->ptr->next->next;//다음것을 연결
				ptList->ptr->next->prev = ptList->ptr;//다음노드의 prev에 연결
				(ptList->nodeNum)--;//노드수감소
			}
			printList(ptList);//LInked List출력함수
		}
		else if(wayNum % 2 ==0)
		{
			for (int i = 1; i < skipNum-1; i++)
			{
				ptList->ptr = ptList->ptr->prev;//skipNum만큼 포인터이동
			}
			printf("좌측으로 %d만큼 이동합니다.\n", skipNum-1);
			printf("탈락한 사람은 %d번 %s입니다.\n", ptList->ptr->prev->num, ptList->ptr->prev->name);

			if (ptList->ptr->prev == ptList->head)//제거하고자하는 노드를 head가 가리키고 있을 때
			{
				ptList->head = ptList->ptr; //head를 현재 head노드의 다음 노드를 가리키게한다.
				ptList->ptr->prev = ptList->ptr->prev->prev;//다음 노드로 연결
				ptList->ptr->prev->next = ptList->ptr;
				(ptList->nodeNum)--;//노드 수 감소
			}
			else if (ptList->ptr->prev == ptList->tail)//제거하고자하는 노드를 tail이 가리키고 있을 때
			{
				ptList->tail = ptList->ptr->prev->prev;//tail을 현재 tail노드의 이전 노드를 가리키게 한다.
				ptList->ptr->prev = ptList->ptr->prev->prev;//다음 노드로 연결
				ptList->ptr->prev->next = ptList->ptr;
				(ptList->nodeNum)--;//노드 수 감소
			}
			else
			{
				ptList->ptr->prev = ptList->ptr->prev->prev;//다음 노드로 연결
				ptList->ptr->prev->next = ptList->ptr;
				(ptList->nodeNum)--;//노드수감소
			}
			printList(ptList);//LInked List출력함수
		}

		if (ptList->nodeNum == 3)//3명이 남았을 때
		{
			printf("\n-------------선정완료--------------\n");
			printf("최종선발된 3인은 ");
			printList(ptList);//최종적으로 남은 3명만 출력
			break;
		}
		wayNum++;
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
			tmp = tmp->next;
		} while (tmp != pt->head);
		printf("입니다.\n");
	}
}

void reversePrintList(cirList* pt)
{
	list_pt tmp;
	tmp = pt->tail;

	if (pt->tail) {
		do
		{
			printf("%d번-", tmp->num);//tmp가 가리키는 num을 출력
			printf("%s ", tmp->name);//tmp가 가리키는 name을 출력
			tmp = tmp->prev;
		} while (tmp != pt->tail);
		printf("입니다.\n\n");
	}
}

void freeList(list_pt head, list_pt ptr)
{
	while (head != NULL)//할당받은 메모리를 해제시킴
	{
		ptr = head;
		head = ptr->next;//첫번째 노드를 바꿈
		free(ptr);//노드를 해제시킴
	}
}