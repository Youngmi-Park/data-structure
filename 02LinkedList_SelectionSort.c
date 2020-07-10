#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define IS_EMPTY(ptr) (!(ptr)) //Empty list가 비어있는지 테스트
#define IS_FULL(ptr) (!(ptr))

typedef struct listNode* list_pt;//구조체를 가리키는 포인터
typedef struct listNode {
	int num; // 입력받은 숫자를 저장하는 변수
	list_pt link; // 구조체 포인터
}listNode;

void printList(list_pt ptr);//LInked List출력함수
void freeList(list_pt head, list_pt ptr);//동적메모리 해제함수

void main()
{
	list_pt head = NULL;//첫번째 노드의 주소가 담기는 포인터변수
	list_pt temp = NULL;//새롭게 입력되는 값을 저장하는 포인터변수
	list_pt ptr = NULL;//노드를 이동하면서 가리키는 포인터변수(중간에 삽입할 때)
	int n = 0, j = 0;//입력받은 숫자를 저장, 몇개의 숫자를 입력받을것인지

	printf("몇 개의 숫자를 입력하시겠습니까 : ");//입력받을 숫자의 개수를 입력받음
	scanf_s("%d", &j);	

	for (int i = 0; i < j; i++)
	{
		printf("숫자%d를 입력하세요 : ", i + 1);//숫자를 입력받음
		scanf_s("%d", &n);

		temp = (list_pt)malloc(sizeof(listNode));//heap영역이 없으면 NULL반환
		if (IS_FULL(temp))
		{
			fprintf(stderr, "메모리가 가득찼습니다.\n");
			exit(1);
		}
		temp->num = n;//temp의 num에 입력받은 값 저장
		temp->link = NULL;//temp의 link에 NULL저장

	//	ptr = head;//첫번째 노드의 주소를 넣음

		if (head == NULL)//head가 가리키는 노드가 NULL일때(빈노드일때, 첫번째 노드를 삽입)
		{
			head = temp;//입력받은 숫자를 ptr이 가리키고있는 첫번째 노드에 삽입
		}
		else if (temp->num < head->num)//입력받은 수가 head의 수보다 작을때(맨앞에 삽입)
		{
			temp->link = head;//head(첫번째노드)앞에 temp를 넣어서 연결(맨앞)
			head = temp;//temp가 첫번째 노드가 된다.
		}
		else//첫번째 입력이 아니고 첫번째노드 보다 값이 클때
		{
			ptr = head;//이동하는 포인터를 첫번째 노드를 가리키게한다.
			while (ptr->link != NULL) //ptr이 가리키는 노드의link가 NULL이 아닌동안(마지막 까지이동)
			{
				if ((ptr->link)->num < temp->num)//ptr이 가리키는 노드의 다음 노드의 num이 temp의 num보다 작을때(ptr이 다음으로 이동해야함)
					ptr = ptr->link;//ptr을 다음노드로 이동시킴
				else//ptr이 가리키는 노드의 다음 노드의 num보다 temp의 num이 작을때
					break;//while문을 빠져나감
			}
			if (ptr->link != NULL)
			{
				temp->link = ptr->link;//ptr이 가리키는곳에 temp를 연결한다.
				ptr->link = temp;//ptr을 temp에 연결
			}
			else
			{
				ptr->link = temp;//ptr의 뒤에 temp를 연결(맨뒤)
			}
		}
		printList(head,ptr);//LInked List출력함수
	}
	freeList(head, ptr);//동적메모리 해제함수

	system("PAUSE");
}

void printList(list_pt head,list_pt ptr)
{
	ptr = head;//ptr을 처음으로 이동시킴

	printf("정렬된 Linked List는 ");
	while (ptr != NULL)//ptr이 빈노드가 아닌동안(마지막까지)
	{
		printf("%d ", ptr->num);//ptr이 가리키는 num을 출력
		ptr = ptr->link;//ptr을 다음노드로 이동시킴
	}
	printf("입니다.\n");
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