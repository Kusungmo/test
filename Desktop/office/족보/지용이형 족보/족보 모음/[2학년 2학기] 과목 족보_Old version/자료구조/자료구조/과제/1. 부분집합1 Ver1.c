#include <stdio.h>
#include <stdlib.h>
int count[4]={0};

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

void print( int* str, int size )				// str에 입력된 부분집합을 출력하는 함수
{
	int i;
	in_count();

	printf("{");
	for( i=0; i<size; i++ )
		printf(" %d", str[i] );
	printf(" }\n");
}

void call( int* str, int n, int size )			// size개의 원소를 가진 부분집합 str을 구하는 함수
{
	int i;

	for( i=0; i<size; i++ )						// str배열을 1부터 size까지 순서대로 값 입력(초기화)
		str[i] = i+1;

	while(1)
	{
		print( str, size );						// 구한 부분집합을 출력하는 함수 호출

		if( size==0 || str[0] == n-size+1 )	break;	// 반복문 종료조건 size가 0이거나 마지막 부분집합일때

		str[size-1]++;							// str배열의 마지막 원소를 1씩 증가 시킴
		if( str[size-1] == n+1 )				// str배열의 마지막 원소가 전체크기 n보다 큰경우
		{										// 반복문을 통하여 마지막 원소의 앞 원소를 증가시킴
			for( i=1; size-i>=0 && str[size-i]==n-i+2; i++ )
				str[size-i-1]++;
			for( i=size-i; i<size; i++ )
				str[i+1] = str[i]+1;
		}
	}
}

void main()
{
	int *str, n, i;

	do{											// n을 입력 받는 부분
		printf("n = ");
		scanf("%d", &n);
	}while( ( n<1 || n > 100 ) ? printf("{ n | 1 <= n <= 100 }\n") : 0 );

	str = (int*)calloc(n,sizeof(int));

	for( i=0; i<=n; i++ )						// 0-n개의 원소를 가진 부분집합을 구하도록 호출
		call( str, n, i );

	printf("총 부분집합의 개수 : ");
	print_count();
	free(str);
}

// 담당교수 : 조행래 교수님
// 학    과 : 컴퓨터 공학과
// 학    번 : 20721708
// 이    름 : 이현복
// 제 출 일 : 2010.9.15