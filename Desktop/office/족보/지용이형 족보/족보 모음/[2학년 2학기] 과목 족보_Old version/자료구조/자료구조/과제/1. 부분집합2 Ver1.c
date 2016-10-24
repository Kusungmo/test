#include <stdio.h>
#include <stdlib.h>
int *str, n, count[4]={0};

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

void print( int size )					// str�� �Էµ� �κ������� ����ϴ� �Լ�
{
	int i;
	in_count();

	printf("{");
	for( i=1; i<=size; i++ )
		printf(" %d", str[i] );
	printf(" }\n");
}

void call( int size, int now )			// size���� ���Ҹ� ���� �κ������� ���ϴ� �Լ�
{
	int i;

	if( size == now )					// �κ������� ������ ���Ҹ� �Է��Ͽ��� ��� ���
		print( size );
	else
		for( i=str[now]+1; i<=n; i++ )	// ���� �κ����� ������ ���� ���ں��� �ִ� �������� �ݺ�
		{
			str[now+1] = i;				// ���� �κ������� ���Ҹ� �Է�
			call( size, now+1 );
		}
}

void main()
{
	int i;

	do{									// n�� �Է� �޴� �κ�
		printf("n = ");
		scanf("%d", &n);
	}while( ( n<1 || n > 100 ) ? printf("{ n | 1 <= n <= 100 }\n") : 0 );

	str = (int*)calloc(n+1,sizeof(int));

	for( i=0; i<=n; i++ )				// 0-n���� ���Ҹ� ���� �κ������� ���ϵ��� ȣ��
		call( i, 0 );

	printf("�� �κ������� ���� : ");
	print_count();
	free(str);
}

// ��米�� : ���෡ ������
// ��    �� : ��ǻ�� ���а�
// ��    �� : 20721708
// ��    �� : ������
// �� �� �� : 2010.9.15