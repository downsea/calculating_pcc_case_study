#include<stdio.h>
#include<malloc.h>
#include"math.h"
#define NAME 15
#define NC 200
int M=-1,N=0;
char infile[50],outfile[50];

struct node{
       char name[NAME];
       float sample[NC];
       struct node *next;
};//the node is used for storing information of one gene
       
int main(){
    struct node *head,*p1,*p2;
    FILE *fp;
    int i,j;
    float r;
    struct node *creat(struct node *head);
    int cal();
    float pcc(float a[NC],float b[NC]);
    //introduction and "do's and don'ts"
    printf("Welcome to use the PCC calculating software pcc.cpp!\n");
    printf("pcc.cpp is used for calculating the PCC for a series of gene samples,");
    printf("and the output format will be:\n");
    printf("gene1\tgene2\tpcc\n");
    printf("gene1\tgene3\tpcc\n");
    printf("......\n");
    printf("            ATTENTION!!!!There are some tips you must follow:\n");
    printf("1.The format of your datafile must be like this:\n");
    printf("ID\t*.txt\t*.txt\t*.txt...\n");
    printf("gene1\tsample1\tsample2\tsample3...\n");
    printf("gene2\tsample1\tsample2\tsample3...\n");
    printf("...................................\n");
   printf("2.Name of genes must be short than 15 chracters,otherwise change '#define NAME 15' at top of the source program.\n");
    printf("3.The samples should be small than 200,otherwise change '#define NC 200' at top the the source program.\n");
    //main body begins
    printf("Please enter 'Y' if you accept all the appoint above.\n");
    if(getchar()=='Y')
       printf("Now please enter route and name of your datafile,such as:  F:/data.txt\n");
    else return 0;
    scanf("%s",&infile);
    printf("Now please enter route and name of file you want to write the results in,such as:   F:/result.txt\n");
    scanf("%s",&outfile);
    //bulding of list
    cal();
    head=NULL;
    head=creat(head);
    p1=p2=(struct node*)malloc(sizeof(struct node));
    p1=p2=head;
    //output
    if((fp=fopen(outfile,"w+"))==NULL){
        printf("cannot open file.\n");
        return 0;
    }
    while(p1->next!=NULL){
        p2=p1->next;
        while(p2!=NULL){
        r=pcc(p1->sample,p2->sample);
        fprintf(fp,"%s\t%s\t",p1->name,p2->name);
        fprintf(fp,"%f\n",r);
        p2=p2->next;
        }
        p1=p1->next;
 }
 fclose(fp);
 return 0;
}
//creat() is used for creating the list
struct node *creat(struct node *head){
       struct node *p1,*p2;
       int i,j,k;
       char p;
       FILE *fp;
       if((fp=fopen(infile,"rt"))==NULL){
          printf("cannot open file\n");
          return 0;
       }
       p1=p2=(struct node*)malloc(sizeof(struct node));
       while(p!='\n')p=fgetc(fp);
       for(i=0;i<M;i++){
           fscanf(fp,"%s",&p1->name);
           for(j=0;j<N;j++)
               fscanf(fp,"%f",&p1->sample[j]);
           p1->next=NULL;
           if(head==NULL)head=p1;
           else p2->next=p1;
           p2=p1;
           p1=(struct node*)malloc(sizeof(struct node));
           fscanf(fp,"\n");
       }
       fclose(fp);
       return(head);
}
//cal()is used for calculating the number of genes and samples in the datafile.
int cal()
{
    FILE *fp;
    char p1,p2;
    if((fp=fopen(infile,"rt"))==NULL){
          printf("cannot open file\n");
          return 0;
       }
    while(!feof(fp))
    {   
          p1=fgetc(fp);
          if(p1=='\n') M++;   
    }
    //printf("the total number of genes is:%d\n",M);
    rewind(fp);
    while(!feof(fp))
    {   
          p2=fgetc(fp);
          if(p2=='\t') N++; 
          if(p2=='\n') break; 
    }
    
    //printf("the total number of sample is:%d\n",N);
    //getchar();getchar();
    return 0;
}
//pcc(a,b) is used for calculating the PCC between a and b.
float pcc(float a[NC],float b[NC]){
	float r;
	float sumx,sumy,sumxy,sumxx,sumyy,temp;
	int i;
	sumx=sumy=sumxy=sumxx=sumyy=0.0;
	for(i=0;i<N;i++){
		sumx=sumx+a[i];
	    sumy=sumy+b[i];
	    sumxy=sumxy+a[i]*b[i];
	    sumxx=sumxx+a[i]*a[i];
	    sumyy=sumyy+b[i]*b[i];
	}
	temp=sqrt((N*sumxx-sumx*sumx)*(N*sumyy-sumy*sumy));
	if(!temp) return 0;
    r=(N*sumxy-sumx*sumy)/temp;
	return r;
}