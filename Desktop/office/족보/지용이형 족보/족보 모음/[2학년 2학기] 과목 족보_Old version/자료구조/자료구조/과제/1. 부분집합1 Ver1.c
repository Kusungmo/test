#include <stdio.h>
#include <stdlib.h>
int count[4]={0};

void in_count()							// �κ����� ������ ī��Ʈ �ϴ� �Լ�
{
	int i;

	count[0]++;
	for( i=0; count[i]==1000000000; i++ )
		count[i+1]++, count[i]=0;
}

void print_count()						// �κ����� ������ ����ϴ� �Լ�
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

void print( int* str, int size )				// str�� �Էµ� �κ������� ����ϴ� �Լ�
{
	int i;
	in_count();

	printf("{");
	for( i=0; i<size; i++ )
		printf(" %d", str[i] );
	printf(" }\n");
}

void call( int* str, int n, int size )			// size���� ���Ҹ� ���� �κ����� str�� ���ϴ� �Լ�
{
	int i;

	for( i=0; i<size; i++ )						// str�迭�� 1���� size���� ������� �� �Է�(�ʱ�ȭ)
		str[i] = i+1;

	while(1)
	{
		print( str, size );						// ���� �κ������� ����ϴ� �Լ� ȣ��

		if( size==0 || str[0] == n-size+1 )	break;	// �ݺ��� �������� size�� 0�̰ų� ������ �κ������϶�

		str[size-1]++;							// str�迭�� ������ ���Ҹ� 1�� ���� ��Ŵ
		if( str[size-1] == n+1 )				// str�迭�� ������ ���Ұ� ��üũ�� n���� ū���
		{										// �ݺ����� ���Ͽ� ������ ������ �� ���Ҹ� ������Ŵ
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

	do{											// n�� �Է� �޴� �κ�
		printf("n = ");
		scanf("%d", &n);
	}while( ( n<1 || n > 100 ) ? printf("{ n | 1 <= n <= 100 }\n") : 0 );

	str = (int*)calloc(n,sizeof(int));

	for( i=0; i<=n; i++ )						// 0-n���� ���Ҹ� ���� �κ������� ���ϵ��� ȣ��
		call( str, n, i );

	printf("�� �κ������� ���� : ");
	print_count();
	free(str);
}

// ��米�� : ���෡ ������
// ��    �� : ��ǻ�� ���а�
// ��    �� : 20721708
// ��    �� : ������
// �� �� �� : 2010.9.15