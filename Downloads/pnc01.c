#include <stdio.h>
#include <math.h>
void Add()
{
	int a, b;
	printf("(덧셈)두 수를 입력하시오 : ");
	scanf("%d %d", &a, &b);
	printf("x+y = %d\n", a+b);
}

void Subtract()
{
	int a, b;
	printf("(뺄셈)두 수를 입력하시오 : ");
	scanf("%d %d", &a, &b);
	printf("x-y = %d\n", a-b);
}
void Division()
{
	int a, b;
	
	printf("(나눗셈)두 수를 입력하시오 : ");
	scanf("%d %d", &a, &b);
	printf("x/y = %d\n", a/b);
}
void Multiply()
{
	int a, b;
	
	printf("(곱셈)두 수를 입력하시오 : ");
	scanf("%d %d", &a, &b);
	printf("x*y = %d\n", a*b);
}
void Square()
{
	int a;
	printf("(제곱)수를 입력하시오 : ");
	scanf("%d", &a);
	printf("x 제곱 = %d\n", a*a);
}
void Root()
{
	int a;
	printf("(제곱근)수를 입력하시오 : ");
	scanf("%d", &a);
	printf("x 제곱근 = %lf\n", sqrt((double)a));
}
void Tri()
{
	int a;
	char str[10];
	
	printf("sin, cos, tan 중 하나를 입력하시오 :");
	scanf("%s", str);
	//while (getchar() != '\n');

	if(str=="sin\0")
	{
		//fflush(stdin);
		//while (getchar() != '\n');
		printf("(삼각함수)30,45,60도 중 하나를 입력하시오:");
		scanf("%d", &a);
		
		if(a==30)
			printf("%lf\n", 1/2);
		else if(a==45)
			printf("%lf\n", (sqrt(2.0))/2);
		else if(a==60)
			printf("%lf\n", (sqrt(3.0))/2);
		else
			printf("잘못입력하였습니다.\n");
	}
	else if(str=="cos")
	{
		printf("(삼각함수)30,45,60도 중 하나를 입력하시오:");
		scanf("%d", &a);
		if(a==30)
			printf("%lf\n", (sqrt(3.0))/2);
		else if(a==45)
			printf("%lf\n", (sqrt(2.0))/2);
		else if(a==60)
			printf("%lf\n", 1/2);
		else
			printf("잘못입력하였습니다.\n");

	}
	else if(str=="tan")
	{
		printf("(삼각함수)30,45,60도 중 하나를 입력하시오:");
		scanf("%d", &a);
		if(a==30)
			printf("%lf\n", 1/(sqrt(3.0)));
		else if(a==45)
			printf("%lf\n", 1);
		else if(a==60)
			printf("%lf\n", sqrt(3.0));
		else
			printf("잘못입력하였습니다.\n");
	}
}


void main()
{
	int n, m;

	while(1){
		printf("user interface : ");
		scanf("%d", &n);

		if(n!=1)
			printf("계산기를 켜주세요\n");

		else if(n==1)
		{
		printf("ON\n");
		while(1){
		printf("user interface : \n(2)덧셈, (3)뺄셈, (4)나눗셈, (5)곱셈, (6)제곱, (7)제곱근, (8)삼각함수, (9)종료\n");
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