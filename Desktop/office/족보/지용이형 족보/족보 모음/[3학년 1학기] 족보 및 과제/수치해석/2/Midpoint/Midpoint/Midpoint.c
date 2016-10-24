#include <stdio.h>

void main(){
	double pow(double x,double y);
	double a=1,b=1.2;
	double c=0,d=2;
	double Mid1 , Simp1 , Trape1;
	double Mid2 , Simp2 , Trape2;
	double e=2.7182818284;
	double Mide1, Trapee1 , Simpe1;
	double Mide2, Trapee2 , Simpe2;

	

	Mid1=(b-a)*(pow(e,(a+b)/2));
	Trape1=(b-a)*((pow(e,a)+pow(e,b))/2);
	Simp1=((b-a)/6)*(pow(e,a)+4*pow(e,(a+b)/2)+pow(e,b));

	Mid2=(d-c)*(pow(e,(c+d)/2));
	Trape2=(d-c)*((pow(e,c)+pow(e,d))/2);
	Simp2=((d-c)/6)*(pow(e,c)+4*pow(e,(c+d)/2)+pow(e,d));

	Mide1=(pow(e,b))/24*(b-a)*(b-a)*(b-a);
	Trapee1=(pow(e,b))/12*(b-a)*(b-a)*(b-a);
	Simpe1=(pow(e,b))/2880*(b-a)*(b-a)*(b-a)*(b-a)*(b-a);

	Mide2=(pow(e,d))/24*(d-c)*(d-c)*(d-c);
	Trapee2=(pow(e,d))/12*(d-c)*(d-c)*(d-c);
	Simpe2=(pow(e,d))/2880*(d-c)*(d-c)*(d-c)*(d-c)*(d-c);



	printf("함수 f(x)를 구간 [1,1.2]에서 적분했을때의 근사적분값\n");
	printf("Exact Value : 0.60184\n");
	printf("Midpoint    : %.5lf\n",Mid1);
	printf("Trapezoidal : %.5lf\n",Trape1);
	printf("Simpson     : %.5lf\n\n",Simp1);
	
	printf("함수 f(x)를 구간 [1,1.2]에서 적분했을때의 오차한계\n");
	printf("Midpoint    : %.5lf\n",Mide1);
	printf("Trapezoidal : %.5lf\n",Trapee1);
	printf("Simpson     : %.5lf\n\n",Simpe1);

	printf("함수 f(x)를 구간 [0,2]에서 적분했을때의 근사적분값\n");
	printf("Exact Value : 6.38900\n");
	printf("Midpoint    : %.5lf\n",Mid2);
	printf("Trapezoidal : %.5lf\n",Trape2);
	printf("Simpson     : %.5lf\n\n",Simp2);
	
	printf("함수 f(x)를 구간 [0,2]에서 적분했을때의 오차한계\n");
	printf("Midpoint    : %.5lf\n",Mide2);
	printf("Trapezoidal : %.5lf\n",Trapee2);
	printf("Simpson     : %.5lf\n\n",Simpe2);


}