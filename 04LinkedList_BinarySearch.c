#include <stdio.h>
#include <stdlib.h>
#define IS_EMPTY(ptr) (!(ptr)) //Empty list가비어있는지테스트
#define IS_FULL(ptr) (!(ptr))

typedef struct listNode* list_pt;//구조체를가리키는포인터
typedef struct listNode {
	int num; // 입력받은숫자를저장하는변수
	list_pt link; // 구조체포인터
}listNode;

void printList(list_pt ptr, list_pt head);//LInked List출력함수
int binSearch(list_pt ptr, list_pt head, int searchNum, int left, int right);//binarySearch함수
void freeList(list_pt ptr, list_pt head);//linkedlist해제함수

void main()
{
	list_pt head = NULL;//첫번째노드의주소가담기는포인터변수
	list_pt temp = NULL;//새롭게입력되는값을저장하는포인터변수
	list_pt ptr = NULL;;//노드를이동하면서가리키는포인터변수중간에삽입할때
	int n = 0, j = 0;//입력받은숫자를 저장 몇개의숫자를입력받을것인지
	int searchNum, searchIndex;//찾고자하는 숫자를 입력받는 변수, binSearch값을 받는 변수
	int left = 0, right = 15;//왼쪽은 첫번째인덱스, 오른쪽은 맨끝인덱스
	int middle = 0;
	int end = 1;


	printf("몇 개의 숫자를 입력하시겠습니까? ");//입력받을숫자의개수를입력받음
	scanf_s("%d", &j);

	//입력받은 수로 linked list를 만드는 과정
	for (int i = 0; i < j; i++)
	{
		printf("숫자%d를 입력하세요 : ", i + 1);//숫자를입력받음
		scanf_s("%d", &n);

		temp = (list_pt)malloc(sizeof(listNode));//heap영역이없으면ULL반환
		if (IS_FULL(temp))
		{
			fprintf(stderr, "메모리가가득찼습니다\n");
			exit(1);
		}

		temp->num = n;//temp의num에입력받은값저장
		temp->link = NULL;//temp의link에NULL저장

		if (head == NULL)//head가가리키는노드가NULL일때빈노드일때 첫번째노드를삽입
		{
			head = temp;//입력받은숫자를ptr이가리키고있는첫번째노드에삽입
			ptr = head;
		}
		else //두번째 값부터는 뒤로 연결한다.
		{
			ptr->link = temp;//head(첫번째노드앞에temp를넣어서연결맨앞
			ptr = ptr->link;
		}
	}
	temp = NULL;//temp초기화
	//입력받은 수를 찾는 과정
	printList(ptr,head);

	while (1)//계속반복
	{
		printf("찾고자하는 숫자를 입력하세요 : ");
		scanf_s("%d", &searchNum);//searchNum에 저장
		searchIndex = binSearch(ptr,head,searchNum, left, right);
		if (searchIndex == -1)
			printf("Linked List에 찾고자하는 숫자가 없습니다\n");
		else
			printf("숫자%d는 Linked list의 %d번째에 있습니다\n", searchNum, searchIndex);//찾고자하는숫자의 위치를출력하는함수
		printf("다른 숫자를 더 찾으시겠습니까(계속(1) or 종료(0)) : ");
		scanf_s("%d", &end);//while문을 탈출하는 장치
		printf("\n");

		if (end == 0)//0을 입력하면 while문을 빠져나가고 프로그램을 종료한다.
			break;
	}
	free(ptr, head);
	system("PAUSE");
	}


void printList(list_pt ptr, list_pt head)
{
	ptr = head;//ptr을 처음으로 이동시킴

	printf("Linked List는 ");
	while (ptr != NULL)//ptr이 빈노드가 아닌동안(마지막까지)
	{
		printf("%d ", ptr->num);//ptr이 가리키는 num을 출력
		ptr = ptr->link;//ptr을 다음노드로 이동시킴
	}
	printf("입니다.\n");
}

int binSearch(list_pt ptr, list_pt head, int searchNum, int left, int right)
{
	//순차적으로 정렬되어있는 Linked List에서 searchNum을 찾는 함수 찿지못한 경우-1을 리턴함
	int middle;//중간 위치를 저장하는 변수
	while (left <= right)
	{
		ptr = head;
		middle = (right + left) / 2;//배열의 중간위치(중간값)
		for (int i = 0; i < middle; i++)
		{
			ptr = ptr->link;//ptr을 가운데 위치한 노드로 이동시킴
		}
		if (ptr->num < searchNum)
			left = middle + 1;//왼쪽값을 이동
		else if (ptr->num > searchNum)
			right = middle - 1;//오른쪽 값을 이동
		else return middle+1;
	}
	return -1;
}

void freeList(list_pt ptr, list_pt head)
{
	while (head != NULL)//할당받은메모리를해제시킴
	{
		ptr = head;
		head = ptr->link;//첫번째노드를바꿈
		free(ptr);//노드를해제시킴
	}
}