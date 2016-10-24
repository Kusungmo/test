#include <stdio.h>
#define TOL 0.0005

void main(){
	
	double p[30]={0};	
	double p1=1.3652300134,s;	
	int n,i;
	p[0]=1;
	

	for(n=0;n<=19;n++){		
		p[n+1]=p[n]-((((p[n])*(p[n])*(p[n])+4*(p[n])*(p[n])-10)) / (3*(p[n])*(p[n])+8*(p[n])));
		s=(p1-p[n]);
		if(s<=0){
			s=-s;
		}
		else{
			s=s;
		}	
		if(s<=TOL) break;
	}

	printf(" n        p(n)         f(p(n))    \n");
	for(i=1;i<=n+1;i++){
		printf("%d      %.10lf        %.10lf    \n",i,p[i],(p[i])*(p[i])*(p[i])+4*(p[i])*(p[i])-10);
	}
	printf("구해진 근사값은 %.10lf입니다 .\n",p[i-1]);
	printf("반복횟수는 %d번입니다 .\n",i-1);
}