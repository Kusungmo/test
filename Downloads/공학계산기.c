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
	printf("1.���� 2.���� 3.���� 4.������ 5.���� 6.��Ʈ 7.�ﰢ�Լ�\n");
	printf("�� ����?");
	scanf_s("%d", &num);
	switch (num){
	case 1:printf("�������: %lf\n", PLUS()); break;
	case 2:printf("�������: %lf\n", MINUS()); break;
	case 3:printf("�������: %lf\n", GOB()); break;
	case 4:printf("���������: %lf\n", NANU()); break;
	case 5:printf("�������: %lf\n", SUNG()); break;
	case 6:printf("��Ʈ���: %lf\n", ROUT()); break;
	case 7:TRI(); break;
	default:printf("1~7���� ����� \n"); break;
	}

}


double PLUS()
{
	double a, b;
	printf("ù��° ��: "); scanf_s("%lf", &a);
	printf("�ι�° ��: "); scanf_s("%lf", &b);

	return  a + b;
	
}

double MINUS()
{
	double a, b;
	printf("ù��° ��: "); scanf_s("%lf", &a);
	printf("�ι�° ��: "); scanf_s("%lf", &b);

	return a - b;
}

double GOB()
{
	double a, b;
	printf("ù��° ��: "); scanf_s("%lf", &a);
	printf("�ι�° ��: "); scanf_s("%lf", &b);

	return a * b;
}

double NANU()
{
	double a, b;
	printf("ù��° ��: "); scanf_s("%lf", &a);
	printf("�ι�° ��: "); scanf_s("%lf", &b);

	return a / b;
}

double SUNG()
{
	int b;
	double a;
	printf("���� ����: "); scanf_s("%lf", &a);
	printf("��� �ұ�? "); scanf_s("%d", &b);
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

	printf("���� ����: "); scanf_s("%lf", &a);
	printf("��� �ұ�? "); scanf_s("%d", &b);
	for (i = 1; i < b; i++){
		return a = sqrt(a);
	}
}
	void TRI()
	{
		int n;
		double a;
		const double PI = 3.141592;
		printf("����� ������? (1.sin 2.cos 3.tan) :"); scanf_s("%d", &n);
		printf("�? "); scanf_s("%lf", &a);
		double t = PI*a / 180;
		
		switch (n)
		{
		case 1:printf("sin%f�� : %f\n", a, sin(t)); break;
		case 2:printf("cos%f�� : %f\n", a, cos(t)); break;
		case 3:printf("tan%f�� : %f\n", a, tan(t)); break;
		default: printf(" 1,2,3, �߿� �����\n");
		}
	}

