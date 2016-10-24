#include<stdio.h>

int count = 0;

void hanoi(int n, char first, char second, char third)
{
	
	if (1 == n)
	{
		printf("%c 탑의 %d 번원판 >> %c탑으로 이동\n", first, n, third);
		count++;
	}
	else
	{
		hanoi(n - 1, first, third, second);
		
		printf("%c 탑의 %d 번원판 >> %c탑으로 이동\n", first, n, third);
		count++;
		
		hanoi(n - 1, second, first, third);
	}
	
}
int main(void)
{
	int n;
	printf("쟁반의 수를 입력하세요. (0 < n <= 64)\n");
	scanf_s("%d", &n);
	while (1)
	{
		if (n > 64 || n < 0)
		{
			printf("쟁반의 수를 잘못입력하셧습니다. 다시설정해 주세요!!\n");
			scanf_s("%d", &n);
		}
			else
				break;
	}
	printf("\n");
	hanoi(n, 'A', 'B', 'C');
	printf("쟁반 이동 횟수 : %d\n", count);
	return  0;
}