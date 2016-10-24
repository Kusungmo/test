/* Example of using dynamic program subroutines for the geographic
   instances on the largest US cities, designed by Neil Simonetti */

#include <stdio.h>
#include <math.h>

#define MAXSIZE 2000
long int lon[MAXSIZE], lat[MAXSIZE];    /* coordinates of cities in
                                           millionths of a degree */
long int tourA[MAXSIZE],tourB[MAXSIZE]; /* space for input/output */
long int *tour1=tourA, *tour2=tourB,    /* pointers to space */
         *tourswap;                      /* swap space for space */
#define swapTour {tourswap=tour1;tour1=tour2;tour2=tourswap;}

#define _shrink 1
#define cs(x) cos(x*0.00000001745329251994)
#define sn(x) sin(x*0.00000001745329251994)
#define theNorm(a,b) (acos(cs(lon[a])*cs(lat[a])*cs(lon[b])*cs(lat[b])+sn(lon[a])*cs(lat[a])*sn(lon[b])*cs(lat[b])+sn(lat[a])*sn(lat[b]))*63781.5)
#include "solver.h"

int ReadData(char *fname)
{ FILE *inpf;
  int c,d,n;
  char iStr[50];

  if ((inpf = fopen(fname, "r")) == NULL)
  { fprintf(stderr,"error with input file %s\n",fname);
    exit(1);
  }
  for (c=0;fname[c]!='.';c++);
  fname[c]=0;
  sscanf (fname+4,"%d",&n);
  for (c=0; c<n; c++)
  { fscanf(inpf,"%d %d",lon+c,lat+c);
  }
  fclose(inpf);
  return(n);
}


long int NearestNeighbor(long int *tour, long int *used, nodeXtype n)
{ long int c, d, h, current, cheapest, cost, totalcost=0;

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
    totalcost+=cost;
    used[cheapest]=1;
  }
  return (totalcost+theNorm(current,0));
}


main (int argc, char *argv[])
{ costtype LastCost, CurrentCost;
  nodeXtype c,d,n;
  long int h,k,i=0,iLim,targ;


  srandom(1);
  if (argc!=5)
  { fprintf(stderr,"Program needs four arguments (h k i filename)\n");
    exit(1);
  }
  sscanf(argv[1],"%d",&h);
  sscanf(argv[2],"%d",&k);
  sscanf(argv[3],"%d",&iLim);
  n=ReadData(argv[4]);
  if (n>MAXSIZE)
  { fprintf(stderr,"problem size too big.\n");
    exit(1);
  }

  GetAuxgraph(k,n,h,2);
  printf("Constructing Nearest Neighbor Tour...\n");
  LastCost = (CurrentCost = NearestNeighbor(tour1,tour2,n))+1;

  while(CurrentCost < LastCost && i<iLim)
  { if (i++) swapTour;
    printf("Cost of Tour: %d\n",CurrentCost);
    LastCost = CurrentCost;
    CurrentCost = DynOpt(k,n,h,0,0,tour1,tour2,0L);
    if (tour2[0]==n) {i=iLim;}
  }

  while(i<iLim)
  { i++; swapTour;
    printf("Cost of Tour: %d\n",CurrentCost);
    targ = ((c=random()%(n-k))>(d=random()%(n-k)))?d:c;
    CurrentCost = DynOpt(k,n,h,13,targ,tour1,tour2,0L);
    if (tour2[0]==n) {i=iLim;}
  }

  printf("Final Cost: %d\n",CurrentCost);
  printf("Sequence:\n");
  if (tour2[0]<n)
  { for (c=0;c<n;c++) {printf(" %d",tour2[c]+1);}
  }
  else
  { printf("  A larger value of h must be used to recover the sequence.");
  }
  printf("\n");
}
