#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void main()
{
	int **m1, **m2;
	int n, i, j, k, sum;
	LARGE_INTEGER start, end, liFrequency;

	srand(time(NULL));

	printf("n = ");
	scanf("%d", &n);

	m1 = (int**)malloc(sizeof(int*)*n);			// �迭�� �Է� ���� ������ ��ŭ �Ҵ�
	m2 = (int**)malloc(sizeof(int*)*n);

	for( i=0; i<n; i++ )
	{
		m1[i] = (int*)malloc(sizeof(int*)*n);
		m2[i] = (int*)malloc(sizeof(int*)*n);
	}


	for( i=0; i<n; i++ )						// �迭 m1, m2 ����
		for( j=0; j<n; j++ )
		{
			m1[i][j] = rand()%10+1;
			m2[i][j] = rand()%10+1;
		}

	QueryPerformanceFrequency(&liFrequency);
	QueryPerformanceCounter(&start);

	printf("\n*** M1 + M2 ***\n");				// �迭 m1+m2 ����
	for( i=0; i<n; i++ )
		for( j=0; j<n; j++ )
			sum = m1[i][j] + m2[i][j];

	printf("\n*** M1 * M2 ***\n");				// �迭 m1*m2 ����
	for( i=0; i<n; i++ )
		for( j=0; j<n; j++ )
			for( k=0, sum=0; k<n; k++ )
				sum += (m1[i][k]*m2[k][j]);

	QueryPerformanceCounter(&end);
	printf("\n%6d %f\n", n, (double)(end.QuadPart - start.QuadPart)/(double)liFrequency.QuadPart );

	for( i=0; i<n; i++ )						// �迭�� �Ҵ��� �޸� ����
	{
		free( m1[i] );
		free( m2[i] );
	}
	free( m1 );
	free( m2 );
}

// ��米�� : ���෡ ������
// ��    �� : ��ǻ�� ���а�
// ��    �� : 20721708
// ��    �� : ������
// �� �� �� : 2010.9.10