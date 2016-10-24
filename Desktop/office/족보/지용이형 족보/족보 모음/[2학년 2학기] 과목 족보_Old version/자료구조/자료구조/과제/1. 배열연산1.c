#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main()
{
	int **m1, **m2;
	int n, i, j, k, sum;

	srand(time(NULL));

	printf("n = ");
	scanf("%d", &n);

	m1 = (int**)malloc(sizeof(int*)*n);			// 배열을 입력 받은 사이즈 만큼 할당
	m2 = (int**)malloc(sizeof(int*)*n);

	for( i=0; i<n; i++ )
	{
		m1[i] = (int*)malloc(sizeof(int*)*n);
		m2[i] = (int*)malloc(sizeof(int*)*n);
	}


	for( i=0; i<n; i++ )						// 배열 m1, m2 생성
		for( j=0; j<n; j++ )
		{
			m1[i][j] = rand()%10+1;
			m2[i][j] = rand()%10+1;
		}

	printf("*** M1 ***\n");						// 배열 m1 출력
	for( i=0; i<n; i++, putchar('\n') )
		for( j=0; j<n; j++ )
			printf("%3d ", m1[i][j] );

	printf("\n*** M2 ***\n");					// 배열 m2 출력
	for( i=0; i<n; i++, putchar('\n') )
		for( j=0; j<n; j++ )
			printf("%3d ", m2[i][j] );

	printf("\n*** M1 + M2 ***\n");				// 배열 m1+m2 출력
	for( i=0; i<n; i++, putchar('\n') )
		for( j=0; j<n; j++ )
			printf("%3d ", m1[i][j] + m2[i][j] );

	printf("\n*** M1 * M2 ***\n");				// 배열 m1*m2 출력
	for( i=0; i<n; i++, putchar('\n') )
		for( j=0; j<n; j++ )
		{
			for( k=0, sum=0; k<n; k++ )
				sum+=(m1[i][k]*m2[k][j]);
			printf("%3d ", sum );
		}

	for( i=0; i<n; i++ )						// 배열에 할당한 메모리 해제
	{
		free( m1[i] );
		free( m2[i] );
	}
	free( m1 );
	free( m2 );
}

// 담당교수 : 조행래 교수님
// 학    과 : 컴퓨터 공학과
// 학    번 : 20721708
// 이    름 : 이현복
// 제 출 일 : 2010.9.10