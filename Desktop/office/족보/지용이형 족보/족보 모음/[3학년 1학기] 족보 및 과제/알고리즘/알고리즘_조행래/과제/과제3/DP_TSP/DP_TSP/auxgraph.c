#include <stdio.h>
#define tofiles 1
#define infinity (1<<30) /* close enough */
#define masktype unsigned long int
#define ones(x) ((x&1)+((x>>1)&1)+((x>>2)&1)+((x>>3)&1)+((x>>4)&1)+((x>>5)&1)+((x>>6)&1)+((x>>7)&1)+((x>>8)&1)+((x>>9)&1)+((x>>10)&1)+((x>>11)&1)+((x>>12)&1)+((x>>13)&1)+((x>>14)&1)+((x>>15)&1)+((x>>16)&1)+((x>>17)&1)+((x>>18)&1)+((x>>19)&1)+((x>>20)&1))
#define highbit(x) ((x>>15)?(x>>19)?(x>>20)?20:19:(x>>17)?(x>>18)?18:17:(x>>16)?16:15:(x>>7)?(x>>11)?(x>>13)?(x>>14)?14:13:(x>>12)?12:11:(x>>9)?(x>>10)?10:9:(x>>8)?8:7:(x>>3)?(x>>5)?(x>>6)?6:5:(x>>4)?4:3:(x>>1)?(x>>2)?2:1:(x)?0:(-1))
#define max1(a,b) (((a)>b)?((a)>1)?(a):1:((b)>1)?(b):1)
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)>(b)?(b):(a))
#define numClasses (1<<(k-1))
#define makesure(op,msg) {if((op)==0){fprintf(stderr,msg);exit(17);}}
#define allocErr "Allocation Error"

#define printset(x,f) for(c1=0;c1<16;c1++){if(x&(1<<c1)){printf(f,c1);}}

FILE *myfile;
signed char k, h, h2, which2, which, *j, *minK, *predLoc, candj, adj, *w1;
unsigned long int c, c1, c2, b;
unsigned long int *succs, succCount, predsCount, predsPoint, *succInx;
unsigned long int *preds, *predInx, *predCount;
unsigned long int SclassCount, *SclassMap;
unsigned long int candSrce, candDest, candSclass, ktemp;
unsigned long int
    bA[20]={     0,       1,       3,     4*2,
               5*4,     6*8,    7*16,    8*32,
              9*64,  10*128,  11*256,  12*512,
           13*1024, 14*2048, 15*4096, 16*8192,
          17*16384,18*32768,19*65536,20*131072},
    b2A[20]={    0,       2,       5,     6*2,
               7*4,     8*8,    9*16,   10*32,
             11*64,  12*128,  13*256,  14*512,
           15*1024, 16*2048, 17*4096, 18*8192,
          19*16384,20*32768,21*65536,22*131072},
    counter[20]={0,0,     1,       3,     4*2,
               5*4,     6*8,    7*16,    8*32,
              9*64,  10*128,  11*256,  12*512,
           13*1024, 14*2048, 15*4096, 16*8192,
          17*16384,18*32768,19*65536};
/* bit masks indicating membership */
masktype *Sminus, *Splus, maskmaxplus, maskmaxminus, maskmaxtemp, candSminus, candSplus;
signed char highPlus, highMinus;

main (int argc, char *argv[])
{ if (argc != 2)
  { fprintf(stderr,"command needs one integer argument (>1)\n");
    exit(1);
  }
  sscanf (argv[1],"%d",&ktemp);
  k = ktemp;
  b = bA[k];
  if (k<2)
  { fprintf(stderr,"command needs one integer argument (>1)\n");
    exit(1);
  }
  if (k>20)
  { fprintf(stderr,"Surely, you jest\n");
    exit(1);
  }
  maskmaxminus = 1<<(k)-1;
  maskmaxplus = maskmaxminus*2;
  makesure(Sminus = (masktype *)calloc(b,sizeof(masktype)),allocErr);
  makesure(Splus = (masktype *)calloc(b,sizeof(masktype)),allocErr);
  makesure(j = (signed char *)calloc(b,sizeof(char)),allocErr);
  makesure(minK = (signed char *)calloc(b,sizeof(char)),allocErr);
  makesure(SclassMap = (unsigned long int *)calloc(numClasses,sizeof(long int)),allocErr);
//  makesure(Sclass =(unsigned long int *)calloc(b,sizeof(long int)),allocErr);
  makesure(succs = (unsigned long int *)calloc(numClasses*k,sizeof(long int)),allocErr);
  makesure(succInx=(unsigned long int *)calloc(b,sizeof(long int)),allocErr);
  makesure(preds = (unsigned long int *)calloc(numClasses*(k+1),sizeof(long int)),allocErr);
  makesure(predInx=(unsigned long int *)calloc(b,sizeof(long int)),allocErr);
  makesure(predLoc=(signed char *)calloc(b,sizeof(char)),allocErr);
  makesure(predCount = (unsigned long int *)calloc(numClasses,sizeof(long int)),allocErr);
  for (c=0;c<numClasses*(k+1);preds[c++]=infinity);

  printf("Generating %d Nodes (%dK) ...\n",b,(b>>10)+1);
//  bracket(h,k);
//  h2=1;
  SclassCount=succCount=0;
  for (candSplus=0; candSplus<=maskmaxplus; candSplus+=2)
  { maskmaxtemp = min(maskmaxminus,(1<<(k-(highPlus=highbit(candSplus))))-1);
//    if (candSplus>>h2) {h2++;dotC;}
    for (candSminus=0; candSminus<=maskmaxtemp; candSminus++)
    { if (ones(candSplus) == ones(candSminus))
      { highMinus=highbit(candSminus);
        SclassMap[SclassCount]=succCount;
        for (candj=1; candj<k; candj++)
	{ if (candSplus&(1<<candj))
	  { which = max1(highPlus+highMinus+1,candj+1);
            j[counter[which]]=-candj;
            Sminus[counter[which]]=candSminus;
            Splus[counter[which]]=candSplus;
            succs[succCount]=counter[which];
            minK[counter[which]]=1+candj+highMinus;
            /*Sclass[counter[which]]=SclassCount;*/
            counter[which]++;
            succCount++;
        } }
        for (candj=0; candj<k-max(0,highPlus); candj++)
	{ if (!(candSminus&(1<<candj))) 
	  { which2 = max1(highPlus+highMinus+1,candj+highPlus+1);
            which = max1(which2,candj+1);
            j[counter[which]]=candj;
            Sminus[counter[which]]=candSminus;
            Splus[counter[which]]=candSplus;
            succs[succCount]=counter[which];
            minK[counter[which]]=1+max(highMinus-candj,0);
            /*Sclass[counter[which]]=SclassCount;*/
            counter[which]++;
            succCount++;
        } }
        SclassCount++;
        succs[succCount]=infinity;
        succCount++;
  } } }

  ktemp=0;
//  newln;
  printf("Generating Arcs...\n");
  for (candSrce=0;candSrce<b;candSrce++)
  { if ((candSrce & 1023) == 1023)
    { fprintf(stderr,"\015%dK out of %dK nodes done",++ktemp,(b>>10)+1);
    }
    for (candSclass=0;candSclass<numClasses;candSclass++)
    { candDest=succs[SclassMap[candSclass]];
      adj=0;
      if (j[candDest]!=j[candSrce]-1)
      { if (j[candSrce]<0)
        { if (Sminus[candSrce]&1) /* situation (a) */ 
	  { adj=(((Sminus[candDest]<<1)==(Sminus[candSrce]-1)) &&
                 ((Splus[candDest]>>1) ==(Splus[candSrce]-(1<<(-j[candSrce])))));
	  }
          else /* situation (b) */
	  { adj=(((Sminus[candDest]<<1)==Sminus[candSrce]) &&
                 ((Splus[candDest]>>1)==(Splus[candSrce]+1-(1<<(-j[candSrce])))));
	  }
        }
        else if (j[candSrce]>0)
        { if (Sminus[candSrce]&1) /* situation (d) */
	  { adj=(((Splus[candDest]>>1)==Splus[candSrce]) &&
                 ((Sminus[candDest]<<1)==(Sminus[candSrce]-1+(1<<(j[candSrce])))));
	  }
          else /* situation (e) */
	  { adj=(((Splus[candDest]>>1)==(Splus[candSrce]+1)) &&
                 ((Sminus[candDest]<<1) ==(Sminus[candSrce]+(1<<(j[candSrce])))));
	  }
        }
        else /* situation (c) */
	{ if (((Splus[candDest]>>1)==Splus[candSrce]) &&
	      ((Sminus[candDest]<<1)==Sminus[candSrce])) {adj=1;}
	}
      }
      if (adj) /* there is an arc from candSrce to candDest */
      { succInx[candSrce]=candSclass;
        preds[candSclass*(k+1)+predCount[candSclass]]=candSrce;
        predLoc[candSrce]=predCount[candSclass];
        predCount[candSclass]++;
        candSclass=numClasses;
      }
    }
  }
  for (predsCount=predsPoint=c=0;c<numClasses;c++)
  { for (c1=SclassMap[c];succs[c1]<infinity;c1++)
    { predInx[succs[c1]]=c;
    }
    do
    { preds[predsCount]=preds[predsPoint];
      predsPoint++;
      predsCount++;
    }
    while (preds[predsPoint-1]<infinity);
    while (preds[predsPoint]==infinity && c<numClasses-1)
    { predsPoint++;
    }
  }
  fprintf(stderr,"\015All nodes done                    \n");

  if (k<9 && tofiles==0)
  { for (c=0;c<b;c++)
    { printf("%3d: j=i%+d: minK=%d: S+={", c+1, j[c], minK[c]);
      printset(Splus[c],",i-%d");
      printf("}: S-={");
      printset(Sminus[c],",i+%d");
      printf("}\n");
      printf("    outgoing arcs: (class%3d) ",succInx[c]+1);
      for (c1=SclassMap[succInx[c]];succs[c1]<infinity;c1++)
      { printf(",%d",succs[c1]+1);
      }
      printf("\n");
      printf("    incoming arcs: (class%3d) ",predInx[c]+1);
      for (c1=c2=0;c2<predInx[c];c2+=(preds[c1]==infinity?1:0),c1++);
      for (;preds[c1]<infinity;c1++)
      { printf(",%d",preds[c1]+1);
      }
      printf("\n");
  } }
  else
  { printf("Writing to Files...\n");
  }
  cfree (Sminus);
  cfree (Splus);

  if ((myfile = fopen("auxgraph.lim", "w")) == NULL)
  { fprintf(stderr,"error with file auxgraph.lim\n");
    exit(1);
  }
  fprintf(myfile,"%d",k);
  fclose(myfile);

  if ((myfile = fopen("auxgraph.s.inx", "wb")) == NULL)
  { fprintf(stderr,"error with file auxgraph.s.inx\n");
    exit(1);
  }
  for (w1=(signed char *)succInx,c=0;c<b*4;c++,w1++){fprintf(myfile,"%c",*w1);}
  fclose(myfile);

  if ((myfile = fopen("auxgraph.p.inx", "wb")) == NULL)
  { fprintf(stderr,"error with file auxgraph.p.inx\n");
    exit(1);
  }
  for (w1=(signed char *)predInx,c=0;c<b*4;c++,w1++){fprintf(myfile,"%c",*w1);}
  fclose (myfile); 

  if ((myfile = fopen("auxgraph.s.arc", "wb")) == NULL)
  { fprintf(stderr,"error with file auxgraph.s.arc\n");
    exit(1);
  }
  for (w1=(signed char *)succs,c=0;c<b2A[k]*4;c++,w1++){fprintf(myfile,"%c",*w1);}
  fclose (myfile); 

  if ((myfile = fopen("auxgraph.p.arc", "wb")) == NULL)
  { fprintf(stderr,"error with file auxgraph.p.arc\n");
    exit(1);
  }
  for (w1=(signed char *)preds,c=0;c<b2A[k]*4;c++,w1++){fprintf(myfile,"%c",*w1);}
  fclose (myfile);

  if ((myfile = fopen("auxgraph.j", "wb")) == NULL)
  { fprintf(stderr,"error with file auxgraph.j\n");
    exit(1);
  }
  for (w1=j,c=0;c<b;c++,w1++){fprintf(myfile,"%c",*w1);}
  fclose (myfile);

  if ((myfile = fopen("auxgraph.mk", "wb")) == NULL)
  { fprintf(stderr,"error with file auxgraph.mk\n");
    exit(1);
  }
  for (w1=minK,c=0;c<b;c++,w1++){fprintf(myfile,"%c",*w1);}
  fclose (myfile);

  if ((myfile = fopen("auxgraph.loc", "wb")) == NULL)
  { fprintf(stderr,"error with file auxgraph.loc\n");
    exit(1);
  }
  for (w1=predLoc,c=0;c<b;c++,w1++){fprintf(myfile,"%c",*w1);}
  fclose (myfile); 

/*  cfree(Sclass);*/
  cfree(SclassMap);
  cfree(succs);
  cfree(succInx);
  cfree(preds);
  cfree(predInx);
  cfree(predLoc);
  cfree(predCount);
  cfree(j);
  cfree(minK);
  for (c=1;c<k+1;c++) {printf("[%d-%d]",c,counter[c]);} printf("\nDONE\n");
}
