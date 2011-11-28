#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float pearson(float x[  ], float y[  ], int columncount)
{   int i;
	float aver_x,aver_y,sum_xy,sum_xi,sum_yi,sum_xx,sum_yy;
	sum_xi=0;
	sum_yi=0;
	sum_xx=0;
	sum_yy=0;
	sum_xy=0;
	
	
	/*
	printf("x[i]=  ");
	for (i=0;i<columncount;i++)
	{
		printf("%f\t",x[i]);
	}
	printf("\n");
	printf("y[i]=  ");
	for (i=0;i<columncount;i++)
	{
		printf("%f\t",y[i]);
	}
	printf("\n");	
	*/
	
	for (i=0;i<columncount;i++)
	{
		sum_xi=sum_xi+x[i];
		sum_yi=sum_yi+y[i];
	}
	aver_x=sum_xi/columncount;
	aver_y=sum_yi/columncount;
	for (i=0; i<columncount; i++)
	{
		sum_xy=sum_xy+((x[i]-aver_x)*(y[i]-aver_y));
		sum_xx=sum_xx+((x[i]-aver_x)*(x[i]-aver_x));
		sum_yy=sum_yy+((y[i]-aver_y)*(y[i]-aver_y));
	}
	
	return(sum_xy/(sqrt(sum_xx*sum_yy)));
}







main(int argc,char *argv[]) 
{
	int i,j,k,w;
	char line[20000];
	int linecount;
	int columncount;
	FILE *in,*out;
	int determine;
	
	in=fopen(argv[1], "r");
	if (in!=NULL) printf("Input file is opened.\n");
	out=fopen(argv[2], "w");
	
	if (argc!=3)
	{
		printf("A programme to caculate Pearson Correlation Coefficient.\n");
		printf("Please input the command as the format:  Pearson2 <infile> <outfile>\n");exit(0);
	}
	if (in==NULL)
	{
		printf("cannot open infile\n");exit(0);
	}
	if (out==NULL)
	{
		printf("cannot open outfile\n");exit(0);
	}
	
	linecount=0;
	for (;fgets(line,20000,in)!=NULL;)
	{
	    linecount++;
	}
	columncount=0;
	for (i=0;line[i]!=NULL;i++)
	{
	    if (line[i]=='\t')
		    { columncount++;}
	}

	printf("line: %d\n",linecount);
	printf("column: %d\n",columncount);
	
	determine=fclose(in);
	if(determine==0) printf("Input file is closed.\n");
	
    int rowcount;
	rowcount=linecount-1;
	printf("rowcount: %d\n",rowcount);
	
	
	
	char name1[30];
	char name2[30];
	char transfer[30];

	
	float data1[columncount];
	float data2[columncount];
	char t;
	int line_n1;
	int line_n2;
	int file1_linecount;
	
	
	for (line_n1=1;line_n1<=linecount;line_n1++)
	{
	    in=fopen(argv[1], "r");
	    /*if (in!=NULL) printf("\n\nInput file is opened again.\n");*/
		fgets(line,20000,in);
		printf("line_n1: %d\n",line_n1);
		/*printf("%s\n",line);*/

		if(line_n1>1)
		{
			for (file1_linecount=2;file1_linecount<=line_n1;file1_linecount++)
			{
				/*printf("file1_linecount: %d\n",file1_linecount);*/
				fgets(line,20000,in);
				/*printf("%s\n",line);*/
			}
			fclose(in);
		
			for (i=0;line[i]!='\t';i++)
			{
				name1[i]=line[i];
			}
			name1[i]='\0';
			/*printf("The name is: %s\n",name1);*/
			i++;
			for (k=0;k<columncount;k++)
			{
				for (j=0;line[i]!='\t'&&line[i]!='\n';i++,j++)
					{transfer[j]=line[i];}
				data1[k]=atof(transfer);
			
				for (j=0;(t=transfer[j])!='\0';j++)
				{
					transfer[j]=0;
				}
			i++;
			}
			/*printf("The data of %s are: ",name1);
			for (k=0;k<columncount;k++)
			{
				printf("%f\t",data1[k]);
			}
			printf("\n");*/
		
			in=fopen(argv[1], "r");
			for (line_n2=1;line_n2<=linecount;line_n2++)
			{
				fgets(line,20000,in);
				if(line_n2>1)
				{
					if(line_n2!=line_n1)
					{
						for (i=0;line[i]!='\t';i++)
						{
							name2[i]=line[i];
						}
						name2[i]='\0';
						i++;
						for (k=0;k<columncount;k++)
						{
							for (j=0;line[i]!='\t'&&line[i]!='\n';i++,j++)
								{transfer[j]=line[i];}
							data2[k]=atof(transfer);
			
							for (j=0;(t=transfer[j])!='\0';j++)
							{
								transfer[j]=0;
							}
							i++;
						}

						/*printf("%s\t%s\t%f\n",name1,name2,pearson(data1,data2,columncount));*/
						fprintf(out,"%s\t%s\t%f\r\n",name1,name2,pearson(data1,data2,columncount));
					}
				}
			}
			fclose(in);
		
		}
	}

	fclose(out);
}
	
	
	
