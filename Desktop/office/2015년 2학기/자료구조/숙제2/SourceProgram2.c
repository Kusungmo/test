#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int count = 0;

void hanoi(int n, char first, char second, char third)
{
	
	if (1 == n)
	{
		printf("%c ž�� %d ������ >> %cž���� �̵�\n", first, n, third);
		count++;
	}
	else
	{
		hanoi(n - 1, first, third, second);
		
		printf("%c ž�� %d ������ >> %cž���� �̵�\n", first, n, third);
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
		printf("������ ������ �ʽ��ϴ�.");
		exit(1);
	}
	for (n = 1; n<=20; n++)
	{

		//printf("����� ���� �Է��ϼ���. (0 < n <= 64)\n");
		//scanf_s("%d", &n);
		while (1)
		{
			if (n > 64 || n < 0)
			{
				printf("����� ���� �߸��Է��ϼ˽��ϴ�. �ٽü����� �ּ���!!\n");
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
		printf("����� �� : %d , �ҿ�� �ð� : %.0f, ��� �̵� Ƚ�� : %d\n", n, duration * 1000, count);
		fprintf_s(fp, "����� �� : %d , �ҿ�� �ð� : %.0f, ��� �̵� Ƚ�� : %d\n", n, duration * 1000, count);
	}
	return  0;
}