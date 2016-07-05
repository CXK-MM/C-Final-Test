#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int m[3];
typedef struct student
{
	int num;
	char name[20];
	int age;
	char sex;
}ss;
typedef struct object
{
	int num;
	int onum;
	char oname[20];
	float score;
}ob;
typedef struct kecheng
{
	char bianhao[20];
	char oname[20];
}kc;
int i,j;
ss *st;
kc *kk;
ob **t;
FILE *fpd;
void daoru();
void password();
void first();
void menu();
void changepassword();
void load();
void save();
void browse();
void chaxun();
void change();
void add();
void del();
void sort();
void statistics();
void expendmenu();
void bad();
void best();
void ave();
int main()
{
	daoru();
	return 0;
}
void daoru()
{
	FILE *fp,*fpa;
	d:printf("导入吗 y or n\n");
	char a;
	scanf("%c",&a);
	if(a=='y')
		goto l;
	else if(a=='n')
		first();
	else goto d;
	l:printf("ok\n");
	if((fp=fopen("head1.bin","rb+"))==NULL)
	{
		printf("cannot open such in file head1\n");
		goto d;
	}
	printf("基础信息文件打开完成#\n");
	for(i=0;i<3;i++)
	if(fread(&m[i],sizeof(int),1,fp)!=1)
	{
		if(feof(fp))
		{
			fclose(fp);
			continue;
		}
		printf("file read erro head1\n");
	}
	fclose(fp);
	printf("基础信息导入完成#\n");
	st=(ss*)calloc(m[1],sizeof(ss));
	kk=(kc*)calloc(m[2],sizeof(kc));
	t=(ob**)calloc(m[2],sizeof(ob*));
	for(i=0;i<m[2];i++)
		t[i]=(ob*)calloc(m[1],sizeof(ob));
	printf("存储定义完成#\n");
	if((fp=fopen("information.bin","rb"))==NULL)
	{
		printf("cannot open such in file information\n");
		goto d;
	}
	printf("学生信息文件打开完成#\n");
	for(i=0;i<m[1];i++)
	if(fread(&st[i],sizeof(ss),1,fp)!=1)
	{
		if(feof(fp))
		{
			fclose(fp);
			continue;
		}
		printf("file read erro information\n");
	}
	fclose(fp);
	printf("学生信息导入完成#\n");
	if((fp=fopen("head2.bin","rb+"))==NULL)
	{
		printf("cannot open such score1 file head2\n");
		goto d;
	}
	printf("课程信息文件打开完成#\n");
	for(i=0;i<m[2];i++)
	if(fread(&kk[i],sizeof(kc),1,fp)!=1)
	{
		if(feof(fp))
		{
			fclose(fp);
			continue;
		}
		printf("file read erro head2\n");
	}
	fclose(fp);
	printf("课程信息导入完成#\n");
	for(i=0;i<m[2];i++)
	{
		if((fp=fopen(kk[i].bianhao,"rb"))==NULL)
		{
			printf("cannot open such score file %s\n",(kk+i)->bianhao);
			goto d;
		}
		printf("%s打开完成#\n",kk[i].bianhao);
		for(j=0;j<m[1];j++)
		if(fread(&t[i][j],sizeof(ob),1,fp)!=1)
		{
			if(feof(fp))
			{ 
				fclose(fp);
				continue;
			}
			printf("file read erro %s\n",kk[i].bianhao);
		}
		fclose(fp);
		printf("%s导入完成#\n",kk[i].bianhao);
	}
	load();
	password();
	menu();
}
void password()
{
	char again;
	int p;
	printf("请输入密码（0000—9999）\n");
	scanf("%d",&p);
	while(p!=m[0])
	{
		getchar();
		printf("密码错误，是否还要继续，继续请输入 y  否则退出请输入 n\n");
		scanf("%c",&again);
		if(again=='n')
			exit(0);
		printf("请再次输入密码\n");
		scanf("%d",&p);
	}
}
void first()
{
	printf("请输入新密码\n");
	scanf("%d",&m[0]);
	printf("请输入学生数与课程数\n");
	scanf("%d %d",&m[1],&m[2]);
	st=(ss*)calloc(m[1],sizeof(ss));
	kk=(kc*)calloc(m[2],sizeof(kc));
	t=(ob**)calloc(m[2],sizeof(ob*));
	for(i=0;i<m[2];i++)
		t[i]=(ob*)calloc(m[1],sizeof(ob));
	for(i=0;i<m[2];i++)
	{
		printf("输入课程编号，课程名字\n");
		scanf("%s %s",&kk[i].bianhao,&kk[i].oname);
	}
	for(i=0;i<m[1];i++)
	{
		printf("num    name       age sex\n");
		scanf("%d %s %d %c",&st[i].num,&st[i].name,&st[i].age,&st[i].sex);
		for(j=0;j<m[2];j++)
		{
			printf("输入编号%s名为%s的分数\n",kk[j].bianhao,kk[j].oname);
			t[j][i].num=st[i].num;
			strcpy(t[j][i].oname,kk[i].oname);
			printf("输入该课程编号 分数\n");
			scanf("%d %f",&t[j][i].onum,&t[j][i].score);
			printf("ok\n");
		}
	}
	printf("%-5d %-6s %-2d %-2c\n",st[0].num,st[0].name,st[0].age,st[0].sex);
	save();
	menu();
}
void menu()
{
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%cpowerd by niubi group\n",1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);
	printf("1.密码\n");
	printf("2.浏览\n");
	printf("3.查询\n");
	printf("4.修改\n");
	printf("5.添加\n");
	printf("6.删除\n");
	printf("7.排序\n");
	printf("8.统计\n");
	printf("9.拓展\n");
	printf("0.退出\n");
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%cpowerd by niubi group\n",1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);
	int x;
	scanf("%d",&x);
	switch(x)
	{
		case 1:changepassword();break;
		case 2:browse();break;
		case 3:chaxun();break;
		case 4:change();break;
		case 5:add();break;
		case 6:del();break;
		case 7:sort();break;
		case 8:statistics();break;
		case 9:expendmenu();break;
		case 0:exit(0);break;
	}
}
void changepassword()
{
	load();
	FILE *fp;
	fp=fopen("head1.bin","wb+");
	for(i=0;i<3;i++)
	{
		fread(&m[i],sizeof(int),1,fp);
	}
	int password;
	printf("请输入新密码\n");
	scanf("%d",&m[0]);
	for(i=0;i<3;i++)
	{
		fwrite(&m[i],sizeof(int),1,fp);
	}
	menu();
}
void load()
{
	FILE *fp,*fpa;
	fp=fopen("head1.bin","rb");
	printf("基础信息文件打开完成#\n");
	
	for(i=0;i<3;i++)
	fread(&m[i],sizeof(int),1,fp);
	fclose(fp);
	printf("基础信息导入完成#\n");
	
	fp=fopen("information.bin","rb");
	printf("学生信息文件打开完成#\n");
	
	for(i=0;i<m[1];i++)
	fread(&st[i],sizeof(ss),1,fp);
	fclose(fp);
	printf("学生信息导入完成#\n");
	
	fp=fopen("head2.bin","rb+");
	printf("课程信息文件打开完成#\n");
	
	for(i=0;i<m[2];i++)
	fread(&kk[i],sizeof(kc),1,fp);
	fclose(fp);
	printf("课程信息导入完成#\n");
	
	for(i=0;i<m[2];i++)
	{
		fp=fopen(kk[i].bianhao,"rb");
		printf("%s打开完成#\n",kk[i].bianhao);
	
		for(j=0;j<m[1];j++)
			fread(&t[i][j],sizeof(ob),1,fp);
		fclose(fp);
		printf("%s导入完成#\n",kk[i].bianhao);
	}
}
void save()
{
	FILE *fp,*fpa;
	fp=fopen("head1.bin","wb+");
	for(i=0;i<3;i++)
		fwrite(&m[i],sizeof(int),1,fp);
	fclose(fp);
	
	fpa=fopen("head2.bin","wb+");
	for(i=0;i<m[2];i++)
		fwrite(&kk[i],sizeof(kc),1,fpa);
	fclose(fpa);
	
	fp=fopen("information.bin","wb+");
	for(i=0;i<m[1];i++)
		fwrite(&st[i],sizeof(ss),1,fp);
	fclose(fp);
	
	for(i=0;i<m[2];i++)
	{
		fp=fopen(kk[i].bianhao,"wb+");
	
		for(j=0;j<m[1];j++)
			fwrite(&t[i][j],sizeof(ob),1,fp);
		fclose(fp);
	}
}
void browse()
{
	load();
	for(i=0;i<m[1];i++)
	{
		printf("num    name      age sex\n");
		printf("%-5d %-10s %-2d %-2c\n",st[i].num,st[i].name,st[i].age,st[i].sex);
		for(j=0;j<m[2];j++)
		{
			printf("%s科目的成绩是 %f\n",kk[j].oname,t[j][i].score);
		}
	}
	menu();
}
void chaxun()
{
	load();
	printf("输入学号查成绩:");
	int y;
	scanf("%d",&y);
	for(i=0;i<m[1];i++)
	{
		if(st[i].num==y)
		{
			printf("num    name      age sex\n");
			printf("%d %s %d %c\n",st[i].num,st[i].name,st[i].age,st[i].sex);
			for(j=0;j<m[2];j++)
			{
				printf("%s科目的成绩是%f\n",kk[j].oname,t[j][i].score);
			}
		}
	}
	menu();
}
void change()
{
	load();
	int y;
	printf("输入更改信息的同学的学号:");
	scanf("%d",&y);
	for(i=0;i<m[1];i++)
	{
		if(st[i].num==y)
		{
			printf("num    name      age sex\n");
			scanf("%d %s %d %c\n",&st[i].num,&st[i].name,&st[i].age,&st[i].sex);
			for(j=0;j<m[2];j++)
			{
				printf("%s的成绩是:",kk[j].oname);
				scanf("%f",&t[j][i].score);
			}
		}
	}
	save();
	menu();
}
void add()
{
	int y,p1;
	printf("输入添加个数:");
	scanf("%d",&y);
	load();
	m[1]+=y;
	FILE *fp,*fpa;
	st=(ss*)calloc(m[1],sizeof(ss));
	kk=(kc*)calloc(m[2],sizeof(kc));
	t=(ob**)calloc(m[2],sizeof(ob*));
	for(i=0;i<m[2];i++)
		t[i]=(ob*)calloc(m[1],sizeof(ob));
	printf("存储定义完成#\n");
	
	fp=fopen("information.bin","rb");
	printf("学生信息文件打开完成#\n");
	
	for(i=0;i<m[1]-y;i++)
	fread(&st[i],sizeof(ss),1,fp);
	fclose(fp);
	printf("学生信息导入完成#\n");
	
	fp=fopen("head2.bin","rb+");
	printf("课程信息文件打开完成#\n");
	
	for(i=0;i<m[2];i++)
	fread(&kk[i],sizeof(kc),1,fp);
	fclose(fp);
	printf("课程信息导入完成#\n");
	
	for(i=0;i<m[2];i++)
	{
		fp=fopen(kk[i].bianhao,"rb");
		printf("%s打开完成#\n",kk[i].bianhao);
	
		for(j=0;j<m[1]-y;j++)
			fread(&t[i][j],sizeof(ob),1,fp);
		fclose(fp);
		printf("%s导入完成#\n",kk[i].bianhao);
	}
	printf("准备就绪#\n");
	for(i=m[1]-y;i<m[1];i++)
	{
		l:printf("num    name      age sex\n");
		scanf("%d %s %d %c\n",&st[i].num,&st[i].name,&st[i].age,&st[i].sex);
		for(p1=0;p1<m[1]-y;p1++)
		{
			if(st[p1].num==st[i].num)
			{
				printf("this num is erro");
				goto l;
			}
		}
		printf("ok\n");
		for(j=0;j<m[2];j++)
		{
			printf("%s的成绩是:",kk[j].oname);
			scanf("%f",&t[j][i].score);
		}
	}
	save();
	menu();
}
void del()
{
	load();
	int y,p1,p2;
	printf("输入想要删除者学号:");
	scanf("%d",&y);
	for(i=0;i<m[1];i++)
	{
		if(st[i].num==y)
		{
			for(j=i;j<m[1]-1;j++)
				st[j]=st[j+1];
			for(p1=0;p1<m[2];p1++)
			{
				for(p2=i;p2<m[1]-1;p2++)
					t[p1][p2]=t[p1][p2+1];
			}
		}
	}
	m[1]-=1;
	save();
	st=(ss*)calloc(m[1],sizeof(ss));
	kk=(kc*)calloc(m[2],sizeof(kc));
	t=(ob**)calloc(m[2],sizeof(ob*));
	for(i=0;i<m[2];i++)
		t[i]=(ob*)calloc(m[1],sizeof(ob));
	menu();
}
void sort()
{
	load();
	int y;
	ob jb;
	for(y=0;y<m[2];y++)
	{
		for(i=0;i<m[1];i++)
		{
			for(j=0;j<m[1]-i-1;j++)
			{
				if(t[y][j].score<t[y][j+1].score)
				{
					jb=t[y][j];
					t[y][j]=t[y][j+1];
					t[y][j+1]=jb;
				}
			}
		}
		printf("%s的排序\n",kk[y].oname);
		for(i=0;i<m[1];i++)
		{
			printf("%d %f\n",t[y][i].num,t[y][i].score);
		}
		printf("------没错，我就是霸气的分割线！！！！！！！！！------------\n");
	}
	menu();
}
void statistics()
{
	load();
	int jb0=0,jb1=0,jb2=0,jb3=0,jb4=0,jb5=0,jb6=0,jb7=0,jb8=0,jb9=0;
	for(i=0;i<m[2];i++)
	{
		jb0=0,jb1=0,jb2=0,jb3=0,jb4=0,jb5=0,jb6=0,jb7=0,jb8=0,jb9=0;
		for(j=0;j<m[1];j++)
		{
			if(t[i][j].score>=0&&t[i][j].score<10)
				jb0++;
			if(t[i][j].score>=10&&t[i][j].score<20)
				jb1++;
			if(t[i][j].score>=20&&t[i][j].score<30)
				jb2++;
			if(t[i][j].score>=30&&t[i][j].score<40)
				jb3++;
			if(t[i][j].score>=40&&t[i][j].score<50)
				jb4++;
			if(t[i][j].score>=50&&t[i][j].score<60)
				jb5++;
			if(t[i][j].score>=60&&t[i][j].score<70)
				jb6++;
			if(t[i][j].score>=70&&t[i][j].score<80)
				jb7++;
			if(t[i][j].score>=80&&t[i][j].score<90)
				jb8++;
			if(t[i][j].score>=90&&t[i][j].score<=100)
				jb9++;
		}
		printf("对%s的统计：\n",kk[i].oname);
		printf("00---10:%d\n",jb0);
		printf("10---20:%d\n",jb1);
		printf("20---30:%d\n",jb2);
		printf("30---40:%d\n",jb3);
		printf("40---50:%d\n",jb4);
		printf("50---60:%d\n",jb5);
		printf("60---70:%d\n",jb6);
		printf("70---80:%d\n",jb7);
		printf("80---90:%d\n",jb8);
		printf("90---100:%d\n",jb9);
		printf("------------%c请叫我霸气的分割线%c-----------\n",1,1);
	}
	menu();
}
void expendmenu()
{
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%cpowerd by niubi group\n",1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);
	printf("1.一键输出不及格\n");
	printf("2.输出每科最高分\n");
	printf("3.求各科平均分\n");
	printf("4.回主菜单\n");
	printf("0.退出\n");
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%cpowerd by niubi group\n",1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);
	int x;
	scanf("%d",&x);
	switch(x)
	{
		case 1:bad();break;
		case 2:best();break;
		case 3:ave();break;
		case 4:menu();break;
		case 0:exit(0);break;
	}
}
void bad()
{
	load();
	int w;
	for(i=0;i<m[2];i++)
	{
		printf("编号为%s的%s科目的不及格学生编号：",kk[i].bianhao,kk[i].oname);
		for(j=0;j<m[1];j++)
		{
			if(t[i][j].score<60)
			{
				printf("%-5d",st[j].num);
			}
		}
		printf("\n");
	}
	menu();
}
void best()
{
	load();
	int y;
	ob jb;
	for(y=0;y<m[2];y++)
	{
		for(i=0;i<m[1];i++)
		{
			for(j=0;j<m[1]-i-1;j++)
			{
				if(t[y][j].score<t[y][j+1].score)
				{
					jb=t[y][j];
					t[y][j]=t[y][j+1];
					t[y][j+1]=jb;
				}
			}
		}
		printf("%s的最高分：\n",kk[y].oname);
		printf("%d %f\n",t[y][0].num,t[y][0].score);
		printf("------没错，我就是霸气的分割线！！！！！！！！！------------\n");
	}
	menu();
}
void ave()
{
	load();
	float ave;
	for(i=0;i<m[2];i++)
	{
		ave=0;
		for(j=0;j<m[1];j++)
			ave+=t[i][j].score;
		ave=ave/m[1];
		printf("编号为%s的%s科目的平均分：",kk[i].bianhao,kk[i].oname);
		printf("%f\n",ave);
	}
	menu();
}