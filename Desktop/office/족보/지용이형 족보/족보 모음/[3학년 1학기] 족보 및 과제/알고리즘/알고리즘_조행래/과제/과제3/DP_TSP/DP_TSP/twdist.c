/* Example of using dynamic program subroutines for the stacker
   crane problems of N. Ascheuer.
        http://www.zib.de/ascheuer/ATSPTWinstances.html
*/

#include <stdio.h>
#include <math.h>

#define MAXSIZE 250
long int theMatrix[MAXSIZE][MAXSIZE];   /* n by n matrix of costs */
long int tour1[MAXSIZE],tour2[MAXSIZE]; /* space for input/output */
long int wB[MAXSIZE],                   /* release times */
         wE[MAXSIZE],                   /* deadlines */
         sT[MAXSIZE];                   /* service times */

#define _twDist 1
#define theNorm(a,b) (theMatrix[a][b])
#include "solver.h"

int ReadData(char *fname)
{ FILE *inpf;
  int c,d,n;
  char iStr[50];

  if ((inpf = fopen(fname, "r")) == NULL)
  { fprintf(stderr,"error with input file %s\n",fname);
    return(0);
  }
  fgets(iStr,50,inpf);
  while (iStr[0]!='D') {fgets(iStr,50,inpf);}
  sscanf (iStr+10,"%d",&n);
  n--;
  while (iStr[0]!='T') {fgets(iStr,50,inpf);}
  for (c=0; c<n; c++)
  { fgets(iStr,50,inpf);
    for(d=0;iStr[d]>0;d++) {if(iStr[d]>'9' || iStr[d]<'0'){iStr[d]=' ';}}
    sscanf (iStr+6,"%d %d %d",sT+c,wB+c,wE+c);
  }
  fgets(iStr,50,inpf);
  for(d=0;iStr[d]>0;d++) {if(iStr[d]>'9' || iStr[d]<'0'){iStr[d]=' ';}}
  sscanf (iStr+6,"%d %d %d",&d,&d,wE);
  while (iStr[0]!='E') {fgets(iStr,50,inpf);}
  for (d=0; d<n; d++)
  { for (c=0; c<n; c++)
    { fscanf(inpf,"%d",&(theMatrix[d][c]));
    }
    fscanf(inpf,"%d",&(theMatrix[d][0]));
  }
  fclose(inpf);
  return(n);
}

main (int argc, char *argv[])
{ costtype FinalCost;
  nodeXtype c,n;
  char guarantee;
  long int h,k,q;


  if (argc!=5)
  { fprintf(stderr,"Program needs four arguments (h k q filename)\n");
    exit(1);
  }
  sscanf(argv[1],"%d",&h);
  sscanf(argv[2],"%d",&k);
  sscanf(argv[3],"%d",&q);
  n=ReadData(argv[4]);
  if (n>MAXSIZE)
  { fprintf(stderr,"problem size too big.\n");
    exit(1);
  }

  GetAuxgraph(k,n,h,q);
  tour1[0]=n;
  FinalCost = DynOpt(k,n,h,q,0,tour1,tour2,
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
    for (c=0;c<n;c++) {FinalCost = FinalCost - sT[c];}
    printf("Final Cost less Process Times: %d\n",FinalCost);
    printf("Sequence:\n");
    if (tour2[0]<n)
    { for (c=0;c<n;c++) {printf(" %d",tour2[c]);}
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
