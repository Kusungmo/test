#include <stdio.h>
#define TOL 0.0005


void main(){
	double pow(double x, double y);
	float a[30],b[30],p[30];
	float p1=1.3652300134;
	float k;
	int max=20;
	int n,i,m;
	
	a[0]=1.00000;
	b[0]=2.00000;
	p[0]=0.00000;
	p[1]=1+((2-1)/2);
	
	for(n=1;n<=20;n++){		
		if(p1<p[n]){
			a[n]=a[n-1];
			b[n]=p[n];
		}
		else if(p1>p[n]){
			a[n]=p[n];
			b[n]=b[n-1];
		}
		else break;
		p[n+1]=a[n]+((b[n]-a[n])/2);
		if(pow(2,n)>(b[0]-a[0])/TOL) break;
	}
	m=n;
		
	printf("n      a(n)             b(n)                p(n)                f(p(n))         \n");

	for(i=0;i<=n;i++){
		
		printf("%d  %.10lf       %.10lf       %.10lf       %.10lf             \n",i,a[i],b[i],p[i+1],(p[i+1])*(p[i+1])*(p[i+1])+4*(p[i+1])*(p[i+1])-10);
	}
	printf("구해진 근사값은 %.10lf이다.\n",p[i]);
	printf("반복횟수는 %d 번이다.\n\n",m);


}