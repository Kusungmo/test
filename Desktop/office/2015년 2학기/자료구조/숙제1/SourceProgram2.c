#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

void selection(int list[], int n)
{
	
	int i, j, min, temp;
	for (i = 0; i < n - 1; i++)
	{
		min = i;
		for (j = i + 1; j < n; j++)
		{
			if (list[j] < list[min])
				min = j;
		}
		SWAP(list[i], list[min], temp);
	}
}

int main(void)
{
	FILE *fp;
	int list[100000];
	int i, n;
	
	clock_t start, stop;
	double duration;
	errno_t err;
	
	if ((err = fopen_s(&fp, "output.txt", "w")) != 0)
	{
		printf("파일이 열리지 않습니다.");
		exit(1);
	}
	
	for (n = 1000; n <= 100000; n += 3000)
	{
		for (i = 0; i < n; i++)
		{
			list[i] = rand() % 1000;
		}
		start = clock();

		selection(list, n);
		
		stop = clock();
		duration = ((double)(stop - start)) / CLOCKS_PER_SEC;
		
		printf("데이터 n 의 갯수 : %d, 소요시간 : %.2f\n",n, duration*1000);
		
		fprintf_s(fp, "%.2f\n", duration * 1000);
	}
	return 0;
}