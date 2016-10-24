#include <stdio.h>
#include <math.h>


double PLUS();
double MINUS();
double GOB();
double NANU();
double SUNG();
double ROUT();
void TRI();

int main()
{
	int num;
	printf("1.덧셈 2.뺄셈 3.곱셈 4.나눗셈 5.제곱 6.루트 7.삼각함수\n");
	printf("뭐 고를래?");
	scanf_s("%d", &num);
	switch (num){
	case 1:printf("덧셈결과: %lf\n", PLUS()); break;
	case 2:printf("뺄셈결과: %lf\n", MINUS()); break;
	case 3:printf("곱셈결과: %lf\n", GOB()); break;
	case 4:printf("나눗셈결과: %lf\n", NANU()); break;
	case 5:printf("제곱결과: %lf\n", SUNG()); break;
	case 6:printf("루트결과: %lf\n", ROUT()); break;
	case 7:TRI(); break;
	default:printf("1~7번만 고르라고 \n"); break;
	}

}


double PLUS()
{
	double a, b;
	printf("첫번째 수: "); scanf_s("%lf", &a);
	printf("두번째 수: "); scanf_s("%lf", &b);

	return  a + b;
	
}

double MINUS()
{
	double a, b;
	printf("첫번째 수: "); scanf_s("%lf", &a);
	printf("두번째 수: "); scanf_s("%lf", &b);

	return a - b;
}

double GOB()
{
	double a, b;
	printf("첫번째 수: "); scanf_s("%lf", &a);
	printf("두번째 수: "); scanf_s("%lf", &b);

	return a * b;
}

double NANU()
{
	double a, b;
	printf("첫번째 수: "); scanf_s("%lf", &a);
	printf("두번째 수: "); scanf_s("%lf", &b);

	return a / b;
}

double SUNG()
{
	int b;
	double a;
	printf("숫자 적어: "); scanf_s("%lf", &a);
	printf("몇번 할까? "); scanf_s("%d", &b);
	int i;
	for (i = 1; i < b; i++){
		return a *= a;
	}
}

double ROUT()
{
	int b;
	int i;
	double a;

	printf("숫자 적어: "); scanf_s("%lf", &a);
	printf("몇번 할까? "); scanf_s("%d", &b);
	for (i = 1; i < b; i++){
		return a = sqrt(a);
	}
}
	void TRI()
	{
		int n;
		double a;
		const double PI = 3.141592;
		printf("몇번을 고를꺼야? (1.sin 2.cos 3.tan) :"); scanf_s("%d", &n);
		printf("몇도? "); scanf_s("%lf", &a);
		double t = PI*a / 180;
		
		switch (n)
		{
		case 1:printf("sin%f도 : %f\n", a, sin(t)); break;
		case 2:printf("cos%f도 : %f\n", a, cos(t)); break;
		case 3:printf("tan%f도 : %f\n", a, tan(t)); break;
		default: printf(" 1,2,3, 중에 고르라고\n");
		}
	}

