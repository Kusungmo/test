#include <stdio.h>
#include <math.h>
void Add()
{
	int a, b;
	printf("(����)�� ���� �Է��Ͻÿ� : ");
	scanf("%d %d", &a, &b);
	printf("x+y = %d\n", a+b);
}

void Subtract()
{
	int a, b;
	printf("(����)�� ���� �Է��Ͻÿ� : ");
	scanf("%d %d", &a, &b);
	printf("x-y = %d\n", a-b);
}
void Division()
{
	int a, b;
	
	printf("(������)�� ���� �Է��Ͻÿ� : ");
	scanf("%d %d", &a, &b);
	printf("x/y = %d\n", a/b);
}
void Multiply()
{
	int a, b;
	
	printf("(����)�� ���� �Է��Ͻÿ� : ");
	scanf("%d %d", &a, &b);
	printf("x*y = %d\n", a*b);
}
void Square()
{
	int a;
	printf("(����)���� �Է��Ͻÿ� : ");
	scanf("%d", &a);
	printf("x ���� = %d\n", a*a);
}
void Root()
{
	int a;
	printf("(������)���� �Է��Ͻÿ� : ");
	scanf("%d", &a);
	printf("x ������ = %lf\n", sqrt((double)a));
}
void Tri()
{
	int a;
	char str[10];
	
	printf("sin, cos, tan �� �ϳ��� �Է��Ͻÿ� :");
	scanf("%s", str);
	//while (getchar() != '\n');

	if(str=="sin\0")
	{
		//fflush(stdin);
		//while (getchar() != '\n');
		printf("(�ﰢ�Լ�)30,45,60�� �� �ϳ��� �Է��Ͻÿ�:");
		scanf("%d", &a);
		
		if(a==30)
			printf("%lf\n", 1/2);
		else if(a==45)
			printf("%lf\n", (sqrt(2.0))/2);
		else if(a==60)
			printf("%lf\n", (sqrt(3.0))/2);
		else
			printf("�߸��Է��Ͽ����ϴ�.\n");
	}
	else if(str=="cos")
	{
		printf("(�ﰢ�Լ�)30,45,60�� �� �ϳ��� �Է��Ͻÿ�:");
		scanf("%d", &a);
		if(a==30)
			printf("%lf\n", (sqrt(3.0))/2);
		else if(a==45)
			printf("%lf\n", (sqrt(2.0))/2);
		else if(a==60)
			printf("%lf\n", 1/2);
		else
			printf("�߸��Է��Ͽ����ϴ�.\n");

	}
	else if(str=="tan")
	{
		printf("(�ﰢ�Լ�)30,45,60�� �� �ϳ��� �Է��Ͻÿ�:");
		scanf("%d", &a);
		if(a==30)
			printf("%lf\n", 1/(sqrt(3.0)));
		else if(a==45)
			printf("%lf\n", 1);
		else if(a==60)
			printf("%lf\n", sqrt(3.0));
		else
			printf("�߸��Է��Ͽ����ϴ�.\n");
	}
}


void main()
{
	int n, m;

	while(1){
		printf("user interface : ");
		scanf("%d", &n);

		if(n!=1)
			printf("���⸦ ���ּ���\n");

		else if(n==1)
		{
		printf("ON\n");
		while(1){
		printf("user interface : \n(2)����, (3)����, (4)������, (5)����, (6)����, (7)������, (8)�ﰢ�Լ�, (9)����\n");
		scanf("%d", &m);

		switch(m)
		{
		case 2:
			Add();
			break;
		case 3:
			Subtract();
			break;
		case 4:
			Division();
			break;
		case 5:
			Multiply();
			break;
		case 6:
			Square();
			break;
		case 7:
			Root();
			break;
		case 8:
			Tri();
			break;
		case 9:
			printf("OFF\n");
			return ;
			}
		printf("---------------------------------\n");
		}
		}
	}
}