#include <stdio.h>
#include <stdlib.h>
int *str, n, count[4]={0};

void in_count()							// 부분집합 개수를 카운트 하는 함수
{
	int i;

	count[0]++;
	for( i=0; count[i]==1000000000; i++ )
		count[i+1]++, count[i]=0;
}

void print_count()						// 부분집합 개수를 출력하는 함수
{
	int i;

	for( i=3; count[i] == 0; i-- );

	switch(i)
	{
	case 0: printf("%d\n",count[0]); break;
	case 1: printf("%d%09d\n",count[1],count[0]); break;
	case 2: printf("%d%09d%09d\n",count[2],count[1],count[0]); break;
	case 3: printf("%d%09d%09d%09d\n",count[3],count[2],count[1],count[0]); break;
	}
}

void print( int size )					// str에 입력된 부분집합을 출력하는 함수
{
	int i;
	in_count();

	printf("{");
	for( i=1; i<=size; i++ )
		printf(" %d", str[i] );
	printf(" }\n");
}

void call( int size, int now )			// size개의 원소를 가진 부분집합을 구하는 함수
{
	int i;

	if( size == now )					// 부분집합의 마지막 원소를 입력하였을 경우 출력
		print( size );
	else
		for( i=str[now]+1; i<=n; i++ )	// 현재 부분집합 원소의 다음 숫자부터 최대 범위까지 반복
		{
			str[now+1] = i;				// 다음 부분집합의 원소를 입력
			call( size, now+1 );
		}
}

void main()
{
	int i;

	do{									// n을 입력 받는 부분
		printf("n = ");
		scanf("%d", &n);
	}while( ( n<1 || n > 100 ) ? printf("{ n | 1 <= n <= 100 }\n") : 0 );

	str = (int*)calloc(n+1,sizeof(int));

	for( i=0; i<=n; i++ )				// 0-n개의 원소를 가진 부분집합을 구하도록 호출
		call( i, 0 );

	printf("총 부분집합의 개수 : ");
	print_count();
	free(str);
}

// 담당교수 : 조행래 교수님
// 학    과 : 컴퓨터 공학과
// 학    번 : 20721708
// 이    름 : 이현복
// 제 출 일 : 2010.9.15