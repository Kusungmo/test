#include<stdio.h>
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

void selection(int list[], int n)
{
	int i, j, min,temp;
	
	for (i = 0; i < n - 1; i++)
	{
		min = i;
		for (j = i + 1; j < n; j++)
		{
			if (list[j] < list[min])
				min = j;
		}
		SWAP(list[i], list[min],temp);
	}
}
int main(void)
{
	int list[1000];
	int i,n;
	
	scanf_s("%d", &n);
	
	for (i = 0; i < n; i++)
	{
		list[i] = rand() % 1000;
	}
	
	selection(list, n);
	
	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
	
	printf("\n");
	return 0;
}