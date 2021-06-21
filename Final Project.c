#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int people=50,court=50,treasury=50,random[50];
//tartibe emtiazaye file haye txt ham hamine.
char mainarr[100],arrtmp[100],data[1000];
void loading(void)
{
	printf("\n\n\t\t\t\t!!!Loading!!!\n");
	system("color f2");
	sleep(1);
	system("color 3b");
	sleep(1);
	system("color 81");
	sleep(1);
}
int numberoflines (FILE *input)
{
	int count_num=0;
	char d;
	if (input==NULL)
		printf ("cannot open");
	while ((d=fgetc(input))!=EOF)
		if (d==' ')
			count_num++;		
	return count_num;
}
void makemainarr(FILE *in)
{
	char c;
	int i=0;
	while (fscanf(in,"%c",&c)!=EOF)
	{
		mainarr[i]=c;	
		i++;
	}

}
void makerandom(int countlines)
{
	int barr[40];
	int r1,i,j;
	time_t t = time(NULL);
	srand(t);
	r1=rand();
	for (i=0;i<40;i++)
	{
		barr[i]=r1%countlines;
		r1=rand();	
	}	
	for (i=0;i<40;i++)
		for(j=0;j<40;j++)
			if ((barr[i]==barr[j])&&(i!=j))
				barr[j]=100;	
	j=0;
	for (i=0;i<40;i++)				
		if (barr[i]!=100)
		{
			random[j]=barr[i];
			j++;
		}
	for (i=0;i<countlines;i++)
		random[countlines+i]=random[random[i]];
	for (i=0;i<countlines;i++)
		random[2*countlines+i]=random[random[i]];					
}
void savegame(FILE* fdata,int winorlose,char name[])
{	
	fdata=fopen("data.txt","a+");
	if (fdata==NULL)
		printf ("Cannot open");	
	fputs(name,fdata);
	fprintf(fdata,"\n%d\n%d\n%d\n%d\n",winorlose,people,court,treasury);
	fclose(fdata);	
}
int checkgame(FILE* fdata,int winorlose,char name[])
{
	int decision;
	if (((people<=0)||(court<=0)||(treasury<=0))||(people+court+treasury<=30))
	{
		system("color c0");
		printf ("\n\n\t\t\t!!!You lost the game!!!\nDo you want to save(1),or not(0)\n");
		winorlose=0;
		scanf("%d",&decision);
		if (decision==0)
		{
			printf("\n\t\t\tthanks for playing!!!");	
			return 0;
		}
		if (decision==1)
		{
		savegame(fdata,winorlose,name);		
		printf("\n\t\t\tthanks for playing!!!");
		return 0;
		}			
	}
	else
		return 1;
}
void makedataarr(FILE *fdata)
{
	fdata=fopen("data.txt","r");
	if (fdata==NULL)
		printf("cannot open");
	char c;
	int i=0;
	while (fscanf(fdata,"%c",&c)!=EOF)
	{
	data[i]=c;	
	i++;
	}
	fclose(fdata);		
}
int main ()
{	
	FILE *fpin,*fpincopy,*fdata,*ftmp;
	int k,j,i,firstdecision,decision,winorlose;	
	//For fun
	printf ("\t\t\t!!                   !!     ####\n");
	for(i=0;i<3;i++)
		printf ("\t\t\t!!                   !!      ##\n");
		printf ("\t\t\t!!!!!!!!!!!!!!!!!!!!!!!      ##\n");
	for(i=0;i<3;i++)
		printf ("\t\t\t!!                   !!      ##\n");
	printf ("\t\t\t!!                   !!     ####\n\n\n");	
	//for  fun
	sleep(1);
	system("color 3b");
	printf ("\t\t\t    The Nation Is Falling!!!\n\n");
	sleep(1);
	printf("\t\t\t    Night Mode(1) or bright(2)\n");
	scanf("%d",&k);
	if (k==1)
		system("color 80");
	if (k==2)
		system("color e0");
	printf ("\nPlease enter your name:\n");
	char name[20];
	scanf("%s",name);
	printf("\nWelcome %s,select one of these options:\n\n",name);
	printf ("1)Start a new game\n2)Resume a game\n");
	scanf("%d",&firstdecision);
	fpin=fopen("CHOICES.txt","r");
	if (fpin==NULL)
	{
		printf ("Cannot open");
		return -1;	
	}	
	fpincopy=fopen("CHOICEScopy.txt","w+");
	if (fpincopy==NULL)
	{
		printf ("Cannot2 open");
		return -1;	
	}
	char c,h;
	while (1)
	{
		c=fgetc(fpin);
		if (feof(fpin))
			break;
		fputc(c,fpincopy);	
	}
	fclose(fpin);
	fseek(fpincopy,0,SEEK_SET);
	makemainarr(fpincopy);		
	fseek(fpincopy,0,SEEK_SET);
	int countlines;
	countlines=numberoflines(fpincopy);
	makerandom(countlines);
	winorlose=1;
	if (firstdecision==1)
	{
		for (i=0;(i<(3*countlines))&&(winorlose==1);i++)
		{		
			//havaset be i bashe
			for (j=0;j<6;j++)
				arrtmp[j]=mainarr[j+7*random[i]];	
			ftmp=fopen(arrtmp,"r");
			if (ftmp==NULL)
				printf ("cannot open");
			char buff1[3*countlines][200],buff2[3*countlines][200],buff3[3*countlines][200],buff4[3*countlines][200];
			for (j=0;j<150;j++)
			{
				buff1[i][j]=fgetc(ftmp);		
				if (buff1[i][j]=='\n')
				{
					buff1[i][j]=' ';
					break;
				}
			}	
			puts (buff1[i]);
			for (j=0;j<150;j++)
			{
				buff2[i][j]=fgetc(ftmp);		
				if (buff2[i][j]=='\n')
				{
					buff2[i][j]=' ';
					break;	
				}	
			}	
			puts (buff2[i]);
			//skip 3 lines
			while (fgetc(ftmp)!='\n');
			while (fgetc(ftmp)!='\n');	
			while (fgetc(ftmp)!='\n');
			for (j=0;j<150;j++)
			{
				buff3[i][j]=fgetc(ftmp);		
				if (buff3[i][j]=='\n')
				{
					buff3[i][j]='\0';
					break;
				}	
			}	
			puts (buff3[i]);	
			scanf("%d",&decision);
			fseek(ftmp,0,SEEK_SET);
			if (decision==1)
			{
				while (fgetc(ftmp)!='\n');
				while (fgetc(ftmp)!='\n');
				fgets(buff4[i],4,ftmp);
				people+=atoi(buff4[i]);
				fgets(buff4[i],4,ftmp);
				court+=atoi(buff4[i]);
				fgets(buff4[i],4,ftmp);
				treasury+=atoi(buff4[i]);	
			}
			if (decision==2)
			{
				for(k=0;k<6;k++)
					while (fgetc(ftmp)!='\n');
				fgets(buff4[i],4,ftmp);
				people+=atoi(buff4[i]);		
				fgets(buff4[i],4,ftmp);
				court+=atoi(buff4[i]);
				fgets(buff4[i],4,ftmp);
				treasury+=atoi(buff4[i]);		
			}
			if (!((decision==-1)||(decision==0)||(decision==1)||(decision==2)))
			{
				printf("WARNING:you missed this decision, because you didn't enter correct integer;so you have lost 20 points of each parameters :(\n");
				people+=-20;		
				court+=-20;
				treasury+=-20;
			}
			winorlose=checkgame(fdata,winorlose,name);
			if (winorlose==0)
				break;
			if (decision==-1)
			{
				printf ("Do you want to save(1),or not(0)\n");
				scanf("%d",&decision);
				if (decision==0)
				{
					printf("\n\t\t\tthanks for playing!!!");
					fclose(fpincopy);
					int ret=remove("CHOICEScopy.txt");
					if (ret!=0)
					printf ("Not deleted");
					return 0;
				}
				if (decision==1)
				{
					savegame(fdata,winorlose,name);		
					fclose(fpincopy);
					int ret=remove("CHOICEScopy.txt");
					if (ret!=0)
					printf ("Not deleted");
					printf("\n\t\t\tthanks for playing!!!");
					return 0;
				}
				printf ("\nOK, nothing Just end!!");	
				fclose(fpincopy);
				int ret=remove("CHOICEScopy.txt");
				if (ret!=0)
				printf ("Not deleted");	
				return -1;		
			}
		}
	fclose(ftmp);
	} 

 	if (firstdecision==2)
	{
		loading();
		makedataarr(fdata);	
		if (strstr(data,name)==NULL)
		{
			printf("You dont have any data");
			system("color c0");
			return -1;	
		}
		char *tmpchar=strstr(data,name);
		k=tmpchar-(&data[0]);
		for(j=k;j<k+20;j++)
			if (data[j]=='\n')
				break;	
		j++;
		if (data[j]=='0')
		{
			j++;
			printf("\n\t\t\t   You have lost the game\nThese are your scores:\n%c%c%c\n%c%c%c\n%c%c%c"
			,data[j+1],data[j+2],data[j+3],data[j+4],data[j+5],data[j+6],data[j+7],data[j+8],data[j+9]);
			system("color c0");
			return -1;
		}
		//pay attention to the names!
		char buffer1[10],buffer2[10],buffer3[10];
		j++;
		for(i=0;i<3;i++)
			buffer1[i]=data[j+i];
		people=atoi(buffer1);
		j+=3;
		for(i=0;i<3;i++)
			buffer2[i]=data[j+i];
		court=atoi(buffer2);
		j+=3;
		for(i=0;i<3;i++)
			buffer3[i]=data[j+i];
		treasury=atoi(buffer3);
		//just copy!
		//just copy!
		//just copy!
		for (i=0;(i<(3*countlines))&&(winorlose==1);i++)
		{		
			//havaset be i bashe
			for (j=0;j<6;j++)
				arrtmp[j]=mainarr[j+7*random[i]];	
			ftmp=fopen(arrtmp,"r");
			if (ftmp==NULL)
				printf ("cannot open");
			char buff1[3*countlines][200],buff2[3*countlines][200],buff3[3*countlines][200],buff4[3*countlines][200];
			for (j=0;j<150;j++)
			{
				buff1[i][j]=fgetc(ftmp);		
				if (buff1[i][j]=='\n')
				{
					buff1[i][j]=' ';
					break;
				}
			}	
			puts (buff1[i]);
			for (j=0;j<150;j++)
			{
				buff2[i][j]=fgetc(ftmp);		
				if (buff2[i][j]=='\n')
				{
					buff2[i][j]=' ';
					break;	
				}	
			}	
			puts (buff2[i]);
			//skip 3 lines
			while (fgetc(ftmp)!='\n');
			while (fgetc(ftmp)!='\n');	
			while (fgetc(ftmp)!='\n');
			for (j=0;j<150;j++)
			{
				buff3[i][j]=fgetc(ftmp);		
				if (buff3[i][j]=='\n')
				{
					buff3[i][j]='\0';
					break;
				}	
			}	
			puts (buff3[i]);	
			scanf("%d",&decision);
			fseek(ftmp,0,SEEK_SET);
			if (decision==1)
			{
				while (fgetc(ftmp)!='\n');
				while (fgetc(ftmp)!='\n');
				fgets(buff4[i],4,ftmp);
				people+=atoi(buff4[i]);
				fgets(buff4[i],4,ftmp);
				court+=atoi(buff4[i]);
				fgets(buff4[i],4,ftmp);
				treasury+=atoi(buff4[i]);	
			}
			if (decision==2)
			{
				for(k=0;k<6;k++)
					while (fgetc(ftmp)!='\n');
				fgets(buff4[i],4,ftmp);
				people+=atoi(buff4[i]);		
				fgets(buff4[i],4,ftmp);
				court+=atoi(buff4[i]);
				fgets(buff4[i],4,ftmp);
				treasury+=atoi(buff4[i]);		
			}
			if (!((decision==-1)||(decision==0)||(decision==1)||(decision==2)))
			{
				printf("WARNING:you missed this decision, because you didn't enter correct integer;so you have lost 20 points of each parameters :(\n");
				people+=-20;		
				court+=-20;
				treasury+=-20;
			}
			winorlose=checkgame(fdata,winorlose,name);
			if (winorlose==0)
				break;
			if (decision==-1)
			{
				printf ("Do you want to save(1),or not(0)\n");
				scanf("%d",&decision);
				if (decision==0)
				{
					printf("\n\t\t\tthanks for playing!!!");
					fclose(fpincopy);
					int ret=remove("CHOICEScopy.txt");
					if (ret!=0)
					printf ("Not deleted");	
					return 0;
				}
				if (decision==1)
				{
					savegame(fdata,winorlose,name);		
					printf("\n\t\t\tthanks for playing!!!");
					fclose(fpincopy);
					int ret=remove("CHOICEScopy.txt");
					if (ret!=0)
					printf ("Not deleted");
					return 0;
				}
				printf ("\nOK, nothing Just end!!");	
				fclose(fpincopy);
				int ret=remove("CHOICEScopy.txt");
				if (ret!=0)
				printf ("Not deleted");
				return -1;		
			}
		}
	fclose(ftmp);					
	}
	fclose(fpincopy);
	int ret=remove("CHOICEScopy.txt");
	if (ret!=0)
		printf ("Not deleted");	
	return 0;
}

