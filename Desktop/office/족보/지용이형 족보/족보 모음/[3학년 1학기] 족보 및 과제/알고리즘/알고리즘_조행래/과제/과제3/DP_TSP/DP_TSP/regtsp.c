/* Example of using dynamic program subroutines for the TSPLIB
   instances with norm EUC_2D */

#include <stdio.h>
#include <math.h>

#define MAXSIZE 20000
double xloc[MAXSIZE], yloc[MAXSIZE];     /* coordinates of cities */
long int tour1[MAXSIZE],tour2[MAXSIZE]; /* space for input/output */

#define round(n) ((int)((n)+0.5))
#define theNorm(a,b) round(sqrt(((xloc[a])-(xloc[b]))*((xloc[a])-(xloc[b]))+((yloc[a])-(yloc[b]))*((yloc[a])-(yloc[b]))))
#include "solver.h"

int ReadData(char *fname)
{ FILE *inpf;
  int c,d,n;
  char iStr[50];

  if ((inpf = fopen(fname, "r")) == NULL)
  { fprintf(stderr,"error with input file %s\n",fname);
    exit(1);
  }
  fgets(iStr,50,inpf);
  while (iStr[0]!='D') {fgets(iStr,50,inpf);}
  sscanf (iStr+11,"%d",&n);
  while (iStr[0]!='E') {fgets(iStr,50,inpf);}
  if (strcmp("EUC_2D\n",iStr+19)!=0)
  { fprintf(stderr,"code designed for norms of type EUC_2D\n");
    exit(1);
  }
  while (iStr[0]!='N') {fgets(iStr,50,inpf);}
  for (c=0; c<n; c++)
  { fgets(iStr,50,inpf);
    sscanf (iStr,"%d %lf %lf",&d,xloc+c,yloc+c);
  }
  fclose(inpf);
  return(n);
}

void NearestNeighbor(long int *tour, long int *used, nodeXtype n)
{ long int c, d, h, current, cheapest, cost;

  for (c=1;c<n;used[c++]=0);
  used[0]=1;
  current=tour[0]=0;
  for (c=1; c<n; c++)
  { cost=(1<<30);
    for (d=1; d<n; d++)
    { if (used[d]==0 && (h=theNorm(current,d)) < cost)
      { cost=h; cheapest=d;
    } }
    current=tour[c]=cheapest;
    used[cheapest]=1;
} }


main (int argc, char *argv[])
{ costtype FinalCost;
  nodeXtype c,n;
  long int h,k;


  if (argc!=4)
  { fprintf(stderr,"Program needs three arguments (h k filename)\n");
    exit(1);
  }
  sscanf(argv[1],"%d",&h);
  sscanf(argv[2],"%d",&k);
  n=ReadData(argv[3]);
  if (n>MAXSIZE)
  { fprintf(stderr,"problem size too big.\n");
    exit(1);
  }

  GetAuxgraph(k,n,h,1);
  printf("Constructing Nearest Neighbor Tour...\n");
  NearestNeighbor(tour1,tour2,n);
  for (c=0;c<n;c++) {printf(" %d",tour1[c]+1);}
  printf("\n\n");

  FinalCost = DynOpt(k,n,h,0,0,tour1,tour2,0L);

  printf("Final Cost: %d\n",FinalCost);
  printf("Sequence:\n");
  if (tour2[0]<n)
  { for (c=0;c<n;c++) {printf(" %d",tour2[c]+1);}
  }
  else
  { printf("  A larger value of h must be used to recover the sequence.");
  }
  printf("\n");
}
