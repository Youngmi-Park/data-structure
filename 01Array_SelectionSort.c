#include <stdio.h>
#include <math.h>
#define MAX 101
#define CRT_SECURE_NO_WARNINGS

void printArray(int list[], int num);
void sort(int list[], int n);
void swap(int *x, int *y);


void main()
{
	int i, n;//list에 값을 입력하는 for에 사용되는 i, 입력받을 숫자의 개수 n
	int list[MAX];//배열생성

	printf("몇 개의 숫자를 입력하시겠습니까? : ");//입력받을 숫자의 개수(배열크기)
	scanf_s("%d", &n);
	if (n<1 || n>MAX)//1보다 작거나 MAX값보다 큰 수를 입력한 경우 에러처리
	{
		fprintf(stderr, "잘못된 입력입니다.\n");
	}
	
	for (i = 0; i < n; i++)//1~MAX 사이의 값을 입력한 경우
	{
		printf("숫자를 입력하세요 : ");
		scanf_s("%d", &list[i]);//list배열에 값을 입력
		printf("입력한 배열 : ");
		printArray(list, i+1);//입력받은 값을 저장한 배열 출력

		sort(list, i+1);//입벽받은 값을 저장한 배열을 정렬
		printf("정렬된 배열 : ");
		printArray(list, i+1);//정렬된 배열을 출력
		printf("\n");
	}

	system("PAUSE");
	return 0;
}

void printArray(int list[], int num)//배열 출력하는 함수
{
	int i;
	for (i = 0; i < num; i++)
	{
		printf("%d ", list[i]);
	}
	printf("\n");
}

void sort(int list[],int n)//정렬 함수
{
	int i=0, j;
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (list[j] < list[i])
			{
				swap(&list[i], &list[j]);
			}
		}
	}

}
void swap(int *x, int *y)//값을 교체하는 함수
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

