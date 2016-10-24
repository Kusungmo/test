#include<stdio.h>

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
	printf("����� ���� �Է��ϼ���. (0 < n <= 64)\n");
	scanf_s("%d", &n);
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
	hanoi(n, 'A', 'B', 'C');
	printf("��� �̵� Ƚ�� : %d\n", count);
	return  0;
}