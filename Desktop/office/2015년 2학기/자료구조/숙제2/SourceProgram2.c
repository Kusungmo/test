#include<stdio.h>
#include<stdlib.h>
#include<time.h>

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

	FILE *fp;
	clock_t start, stop;
	double duration;
	errno_t err;

	if ((err = fopen_s(&fp, "output.txt", "w")) != 0)
	{
		printf("파일이 열리지 않습니다.");
		exit(1);
	}
	for (n = 1; n<=20; n++)
	{

		//printf("쟁반의 수를 입력하세요. (0 < n <= 64)\n");
		//scanf_s("%d", &n);
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
		start = clock();

		hanoi(n, 'A', 'B', 'C');

		stop = clock();
		duration = ((double)(stop - start)) / CLOCKS_PER_SEC;
		printf("쟁반의 수 : %d , 소요된 시간 : %.0f, 쟁반 이동 횟수 : %d\n", n, duration * 1000, count);
		fprintf_s(fp, "쟁반의 수 : %d , 소요된 시간 : %.0f, 쟁반 이동 횟수 : %d\n", n, duration * 1000, count);
	}
	return  0;
}