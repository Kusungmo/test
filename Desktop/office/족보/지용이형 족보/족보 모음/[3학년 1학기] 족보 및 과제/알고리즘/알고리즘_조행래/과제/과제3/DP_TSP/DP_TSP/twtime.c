/* Example of using dynamic program subroutines for the time
   window problems in the style of E. Baker (Op. Res. 1983) */

#include <stdio.h>
#include <math.h>

#define MAXSIZE 250
long int theMatrix[MAXSIZE][MAXSIZE];   /* n by n matrix of costs */
long int tour1[MAXSIZE],tour2[MAXSIZE]; /* space for input/output */
long int wB[MAXSIZE],                   /* release times */
         wE[MAXSIZE],                   /* deadlines */
         sT[MAXSIZE];                   /* service times */

#define _twTime 1
#define theNorm(a,b) (theMatrix[a][b])
#include "solver.h"

int ReadData(char *fname)
{ FILE *inpf;
  int c1,c2,c3,c4,d,n;
  char iStr[50];

  if ((inpf = fopen(fname, "r")) == NULL)
  { fprintf(stderr,"error with input file %s\n",fname);
    return(0);
  }
  fscanf (inpf,"%d",&n);
  n++;
  for (c1 = 0; c1 < n; c1++)
  { fscanf (inpf, "%d", wB+c1);
    sT[c1]=0;
  }
  for (c1 = 0; c1 < n; c1++)
  { fscanf (inpf, "%d", wE+c1);
  }
  for (c1 = 0; c1 < ((n+7)>>3); c1++)
  { for (c2 = 0; c2 < ((n+7)>>3); c2++)
    { for (c3 = 0; c3 < _min(8,n-(c1*8)); c3++)
      { for (c4 = 0; c4 < _min(8,n-(c2*8)); c4++)
        { fscanf (inpf, "%d", &theMatrix[(c1*8)+c3][(c2*8)+c4]);
  } } } }
  fclose(inpf);
  return(n);
}

main (int argc, char *argv[])
{ costtype FinalCost;
  nodeXtype c,n;
  char guarantee;
  long int h,k,q;


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
  tour1[0]=n;
  FinalCost = DynOpt(k,n,h,0,tour1,tour2,
                     wB,wE,sT,&guarantee);

  if (FinalCost == (1<<30)) /* no feasible solution found */
  { if (guarantee)
    { printf("There is no feasible solution, guaranteed.\n");
    }
    else
    { printf("Could not find a feasible solution.\n");
      printf("Problem may or may not be feasible.\n");
    }
  }
  else
  { printf("Final Cost: %d\n",FinalCost);
    printf("Sequence:\n");
    if (tour2[0]<n)
    { for (c=0;c<n;c++) {printf(" %d",tour2[c]+1);}
    }
    else
    { printf("  A larger value of h must be used to recover the sequence.");
    }
    if (guarantee)
    { printf("\n**Solution is optimal**\n");
    }
    else
    { printf("\n**Solution may not be optimal**\n");
    }
} }
