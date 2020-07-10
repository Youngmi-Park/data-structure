#include <stdio.h>
#include <stdlib.h>

int binSearch(int list[], int searchNum, int left, int right);

void main()
{
	int list[16] = {4, 7, 8, 11, 13, 15, 21, 26, 42, 43, 48, 49, 75, 96, 97, 103 };
	int searchNum;//찾고자하는 숫자를 입력받는 변수
	int searchIndex;//찾고자하는 숫자의 인덱스를 저장하는변수
	int left = 0, right = sizeof(list)/sizeof(int) -1;//왼쪽은 첫번째인덱스, 오른쪽은 맨끝인덱스
	int end = 1;

	while(1)//계속반복
	{
		if (end == 1)
		{
			printf("4, 7, 8, 11, 13, 15, 21, 26, 42, 43, 48, 49, 75, 96, 97, 103\n찾고자하는 숫자를 입력하세요 : ");
			scanf_s("%d", &searchNum);//searchNum에 저장
			searchIndex = binSearch(list, searchNum, left, right);//binSearch가 반환한 값을 저장한다.
			if (searchIndex == -1)//배열에 숫자가 없는 경우 -1을 반환한다.
				printf("배열에 찾고자하는 숫자가 없습니다.\n");
			else
				printf("숫자 %d는 list index %d에 있습니다.\n", searchNum, searchIndex);//찾고자하는 숫자의 index를 출력하는 함수
			printf("다른 숫자를 더 찾으시겠습니까(계속(1) or 종료(0)) : ");
			scanf_s("%d", &end);//while문을 탈출하는 장치
			printf("\n");
		}
		else if (end == 0)//0을 입력하면 while문을 빠져나가고 프로그램을 종료한다.
			break;
	}
	system("PAUSE");
	return 0;
}

int binSearch(int list[], int searchNum, int left, int right)
{
	//순차적으로 정렬되어있는 배열에서 searchNum을 찾는 함수 찿지못한 경우-1을 리턴함
	int middle;//중간 인덱스를 저장하는 변수
	while (left <= right)
	{
		middle = (right + left) / 2;//배열의 중간인덱스(중간값)
		if (list[middle] < searchNum)
			left = middle + 1;//왼쪽값을 이동
		else if (list[middle] > searchNum)
			right = middle - 1;//오른쪽 값을 이동
		else return middle;//list[middle]과 search넘이 같은경우
	}
	return -1;
}

