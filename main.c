#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct student
{
    char name[10];//用户名
    char id[10];//账号
    char password[8];//密码
    char type[10];//类型
    struct student *next;
};
typedef struct student lnode, *linklist;

struct book
{
    int  id;
	char name[20];
	char author[20];
	char publisher[20];
	char type[20];
	int pubtime;
	int price;
	int Num;
    struct book *next;
};
typedef struct book LNode, *LinkList;

void load(LinkList head,linklist head1);//将文件中的信息加载到链表中的函数
void test(linklist k,char str1[],char str2[]);//检验账号信息函数
void librarian(LinkList head, linklist head1);//图书管理员函数
void SMS (linklist head1);//用户管理函数
void print(linklist head1);//输出已有读者账号信息
void printsms(linklist head1);
void printread(linklist head1);
void addread(linklist head1);//添加读者账号信息
void addallread(linklist head1);//批量添加读者信息
void save(linklist head1);//将读者账号写入文件
void deleteread(linklist head1);//删除读者账号
void deleteallread(linklist head1);//批量删除读者信息
void change(linklist head1);//重置单个用户密码

void information(LinkList head);//图书信息管理函数
void newbook(LinkList head);//新书入库
void allinput(LinkList head);//批量导入
void Input(LinkList head);//单独导入
void Save(LinkList head);//将图书信息写入文件中
void Output(LinkList head);//输出图书信息
void Sort(LinkList head);//图书排序
void oldbook(LinkList head);//旧书下架
void titledelete(LinkList head);//按书名删除
void timedelete(LinkList head);//按出版时间删除
void modify(LinkList head);//图书信息修改

void reader(LinkList head,linklist head1);//普通读者函数
void password(linklist head1);//读者更改密码
void query(LinkList head);//查询图书信息
void borrow(LinkList head);//借阅图书
void titlequery(LinkList head);//书名查找
void authorquery(LinkList head);//作者名查找
void pressquery(LinkList head);//出版社查找
void titleauthor(LinkList head);//按书名作者名查询
int compare(char k[],char m[], char n[], char str[], char password[]);
int select, b=0;
LinkList head;
linklist head1;

int main()
{
    system("color 3a");
    head1=(linklist)malloc(sizeof(lnode));
    head=(LinkList)malloc(sizeof(LNode));
    head1->next=NULL;
    head->next=NULL;
    load(head,head1);
    char str1[10],str2[10];
    linklist k=head1->next;
    while(1)
    {
        printf("***************************************************\n");
        printf("*               欢迎来到图书管理系统              *\n");
        printf("***************************************************\n\n");
        printf("请输入用户名和密码或账号和密码：\n");
        printf("用户名或账号：");
        scanf("%s",str1);
        printf("密码：");
        scanf("%s",str2);
        test(k,str1,str2);
    }
   return 0;
}
void load(LinkList head,linklist head1)
{
    LinkList p,rear=head;
	char name[20],author[20],publisher[20],type[20];
	int id, pubtime,price,Num;
    FILE *fp;
    if((fp=fopen("bookinfo.txt","r"))==NULL)
	{
		printf("File Open Error!\n");
		exit(0);
	}

	while(fscanf(fp,"%d%s%s%s%s%d%d%d",&id,name,author,publisher,type,&pubtime,&price,&Num)!=EOF)
    {
      p=(LinkList)malloc(sizeof(LNode));
	  p->id=id;
	  strcpy(p->name,name);
	  strcpy(p->author,author);
	  strcpy(p->publisher,publisher);
	  strcpy(p->type,type);
	  p->pubtime=pubtime;
	  p->price=price;
      p->Num=Num;
	  rear->next=p;
	  rear=p;
    }
    rear->next=NULL;
    linklist q, rear1=head1;
	char name1[10],ID[10], password[10],type1[10];
    if((fp=fopen("userinfo.txt","r"))==NULL)
	{
		printf("File Open Error!\n");
		exit(0);
	}
	while(fscanf(fp,"%s %s %s %s",name1,ID, password,type1)!=EOF)
    {
      q=(linklist)malloc(sizeof(lnode));
      strcpy(q->name,name1);
	  strcpy(q->id,ID);
	  strcpy(q->password,password);
	  strcpy(q->type,type1);
	  rear1->next=q;
	  rear1=q;
    }
    rear1->next=NULL;
}

void test(linklist k,char str1[],char str2[])
{
    while(k)
        {
            b=0;
            b=compare(k->name,k->id,k->password,str1,str2);
            if(b==1)
            {
               if(strcmp(k->type,"管理员")==0)
               {
                   librarian(head, head1);//图书管理员函数
               }
               if(strcmp(k->type,"用户")==0)
               {
                   reader(head, head1);//普通读者函数
               }
               break;
            }
            k=k->next;
        }
        int b1;
        while(b!=1)
        {
            printf("输入信息错误，退出请按0，再次输入按1：\n");
            scanf("%d",&b1);
            if(b1==1)
            {
                printf("请重新输入信息：\n");
                printf("用户名或账号：");
                scanf("%s",str1);
                printf("密码：");
                scanf("%s",str2);
                k=head1->next;
                while(k)
                {
                    b=0;
                    b=compare(k->name,k->id,k->password,str1,str2);
                    if(b==1)
                    {
                        if(strcmp(k->type,"管理员")==0)
                        {
                            librarian(head, head1);//图书管理员函数
                        }
                        if(strcmp(k->type,"用户")==0)
                        {
                            reader(head, head1);//普通读者函数
                        }
                        break;
                    }
                    k=k->next;
                }
            }
            else
                exit(0);
        }
}

int compare(char k[],char m[], char n[], char str[], char password[])
{
    if((strcmp(str,k)==0||strcmp(str,m)==0)&&(strcmp(password,n)==0))
    {
        printf("输入信息正确,即将进入系统\n\n");
        return 1;
    }

    return 0;
}

void librarian(LinkList head, linklist head1)//图书管理员函数
{
    do{
    printf("******************************************\n");
    printf("*             1:用户管理                 *\n");
    printf("*             2:图书信息管理             *\n");
    printf("*             3:退出                     *\n");
    printf("******************************************\n\n");
    printf("请输入你要进行的项目选项\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            SMS (head1);//用户管理函数
            break;
        case 2:
            information(head);//图书信息管理函数
            break;
    }}while(select!=3);
}

void SMS(linklist head1)//用户管理函数
{
    do{
    printf("************************************\n");
    printf("*        1:单独添加账号            *\n");
    printf("*        2:批量添加账号            *\n");
    printf("*        3:单独删除账号            *\n");
    printf("*        4:批量删除账号            *\n");
    printf("*        5:输出已有账号            *\n");
    printf("*        6:重置单个用户密码        *\n");
    printf("*        7:退出                    *\n");
    printf("************************************\n\n");
    printf("请输入你要进行的项目选项\n");
    scanf("%d", &select);

    switch(select)
    {
        case 1:
            addread(head1);//单独添加
            break;
        case 2:
            addallread(head1);//批量添加
            break;
        case 3:
            deleteread(head1);//删除读者账号
            break;
        case 4:
            deleteallread(head1);//批量删除
            break;
        case 5:
            print(head1);//输出读者信息
            break;
        case 6:
            change(head1);//重置单个用户密码
            break;
        default:return;
    }}while(select!=7);
}
void print(linklist head1)//显示已有读者信息
{
    do{
    printf("************************************\n");
    printf("*        1:输出管理员账号            *\n");
    printf("*        2:输出用户账号              *\n");
    printf("*        3:退出                    *\n");
    printf("************************************\n\n");
    printf("请输入你要进行的项目选项\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            printsms(head1);//单独添加
            break;
        case 2:
            printread(head1);//批量添加
            break;
        default:return;
    }}while(select!=3);
}
void printsms(linklist head1)
{
    linklist q=head1->next;
    int i=0;
    while(q)
    {
        if(strcmp(q->type,"管理员")==0)
        {
            printf("%s %s %s\n",q->name,q->id,q->password);
            i++;
        }
        q=q->next;
    }
    if(i==0)
        printf("没有管理员信息！");
}
void printread(linklist head1)
{
    linklist q=head1->next;
    int i=0;
    while(q)
    {
        if(strcmp(q->type,"用户")==0)
        {
            printf("%s %s %s\n",q->name,q->id,q->password);
            i++;
        }
        q=q->next;
    }
    if(i==0)
    {
        printf("没有用户信息！");
    }
    return;
}
void addread(linklist head1)
{
    linklist p,rear=head1;
    char name[10];
    char id[20];
    char password[20];
    char type[10];
    FILE *fp;
    if((fp=fopen("userinfo.dat","r+"))==NULL)
    {
        printf("File Open Error!\n");
        exit(0);
    }

    while(fscanf(fp,"%s %s %s %s",name,id,password,type)!=EOF)
        {
            p=(linklist)malloc(sizeof(lnode));
            strcpy(p->name,name);
            strcpy(p->id,id);
            strcpy(p->password,password);
            strcpy(p->type,type);
            rear->next=p;
            rear=p;
        }
    printf("请依次输入用户名、账号、密码和类别，输入#表示输入结束\n");
    printf("输入示例：张三 1 111111 用户\n");
        while(scanf("%s",name)!=EOF&&strcmp(name,"#")!=0)
        {
            p=(linklist)malloc(sizeof(lnode));
            scanf("%s",id);
            scanf("%s",password);
            scanf("%s",type);
            strcpy(p->name,name);
            strcpy(p->id,id);
            strcpy(p->password,password);
            strcpy(p->type,type);
            rear->next=p;
            rear=p;
        }
        rear->next=NULL;
        printf("已有普通读者用户信息:\n");
        printread(head1);
        save(head1);
}

void addallread(linklist head1)
{
    linklist p,rear=head1;
	char name[10],id[20],password[20],type[10];
    FILE *fp;

    if((fp=fopen("userinfo.dat","r"))==NULL)
	{
		printf("File Open Error!\n");
		exit(0);
	}

	while(fscanf(fp,"%s %s %s %s",name,id,password,type)!=EOF)
    {
      p=(linklist)malloc(sizeof(lnode));
      strcpy(p->name,name);
	  strcpy(p->id,id);
	  strcpy(p->password,password);
	  strcpy(p->type,type);
	  rear->next=p;
	  rear=p;
    }
    if((fp=fopen("待批量添加的读者账号密码.txt","r"))==NULL)
	{
		printf("File Open Error!\n");
		exit(0);
	}

	while(fscanf(fp,"%s %s %s %s",name,id,password,type)!=EOF)
    {
      p=(linklist)malloc(sizeof(lnode));
      strcpy(p->name,name);
	  strcpy(p->id,id);
	  strcpy(p->password,password);
	  strcpy(p->type,type);
	  rear->next=p;
	  rear=p;
    }
    rear->next=NULL;
    save(head1);
    printf("待添加的读者信息已批量导入！\n");
    printf("当前读者信息为：\n");
    printread(head1);
}
void deleteread(linklist head1)//删除读者账号
{
    printf("请输入待删除的读者用户名或账号信息\n");
    linklist p=head1,pre;
    char Delete[20];
    int flag=0;
    scanf("%s",Delete);
    while(p)
    {
        pre=p;
        p=p->next;
        if(p)
        {
                if(strcmp(Delete,p->name)==0||strcmp(Delete,p->id)==0)
                {
                    printf("待删除的读者信息为：\n");
                    printf("%s %s %s %s\n",p->name,p->id,p->password,p->type);
                    pre->next=p->next;
                    flag=1;
                    free(p);
                    printf("读者信息已删除\n");
                }
        }

    }
    if(flag==0)
    {

        printf("查无读者信息，无法删除\n");

    }
    save(head1);
}
void deleteallread(linklist head1)
{
    linklist p,rear=head1,pre,q;
    char name[10],str[10],id[20],password[20],type[10];
    FILE *fp;
    if((fp=fopen("userinfo.dat","r"))==NULL)
	{
		printf("File Open Error!\n");
		exit(0);
	}
	while(fscanf(fp,"%s %s %s %s",name,id,password,type)!=EOF)
    {
      p=(linklist)malloc(sizeof(lnode));
      strcpy(p->name,name);
	  strcpy(p->id,id);
	  strcpy(p->password,password);
	  strcpy(p->type,type);
	  rear->next=p;
	  rear=p;
    }
    rear->next=NULL;
    if((fp=fopen("待批量删除读者账号密码.txt","r"))==NULL)
	{
		printf("File Open Error!\n");
		exit(0);
	}
    while(fscanf(fp,"%s",str)!=EOF)
    {
        pre=head1;
        q=pre;
        pre=pre->next;
      while(pre)
      {
          if(strcmp(pre->name,str)==0||strcmp(pre->id,str)==0)
          {
              q->next=pre->next;
              break;
          }
          q=pre;
          pre=pre->next;
      }
    }
    printf("已批量删除读者信息\n");
    printf("当前读者信息为：\n");
    printread(head1);
    save(head1);
}

void change(linklist head1)
{
    linklist p=head1->next;
    char str[10];
    int flag=0;
    printf("请输入要重置密码的用户名或账号：\n");
    scanf("%s",str);
    while(p)
    {
        if(strcmp(p->type,"用户")==0)
        {
            if(strcmp(p->name,str)==0||strcmp(p->id,str)==0)
            {
                printf("请输入重置密码：\n");
                scanf("%s",p->password);
                printf("已重置用户密码！\n");
                flag=1;
            }
        }
       p=p->next;
    }
    if(flag==0)
    {
        printf("未找到对应的用户名或账号！\n");
    }
    printf("当前读者信息为：\n");
    printread(head1);
    save(head1);
}
void save(linklist head1)
{
    FILE *fp;
    linklist p;
    if((fp=fopen("userinfo.dat","w"))==NULL)
    {
        printf("File Open Error!\n");
        exit(0);
    }
    for(p=head1->next;p;p=p->next)
        {
            fprintf(fp,"%s %s %s %s\n",p->name,p->id,p->password,p->type);
        }
        fclose(fp);
}
void information(LinkList head)//图书信息管理函数
{
      do{
      printf("**********************************************\n");
	  printf("*         欢迎进入图书管理员界面             *\n");
	  printf("*         1：新书上架                        *\n");
	  printf("*         2：输出图书信息                    *\n");
	  printf("*         3：查询                            *\n");
	  printf("*         4：排序                            *\n");
	  printf("*         5：旧书下架                        *\n");
	  printf("*         6：修改图书信息                    *\n");
	  printf("*         7：退出                            *\n");
	  printf("**********************************************\n");

	  printf("     请输入你的选择：\n");
      scanf("%d",&select);

    switch(select)
    {
        case 1:newbook(head);//新书上架
		       break;
	    case 2:Output(head);//图书输出
		       break;
	    case 3:query(head);//图书查找
		       break;
        case 4:Sort(head);//图书排序
			   break;
	    case 5:oldbook(head);//旧书下架
		       break;
	    case 6:modify(head);//修改图书信息
		       break;

    }}while(select!=7);
}
void newbook(LinkList head)//新书入库
{
    do{
    printf("******************************************\n");
    printf("*              1:单独导入                *\n");
    printf("*              2:批量导入　　　          *\n");
    printf("*              3:退出                    *\n");
    printf("******************************************\n\n");
    printf("请输入你要进行的项目选项\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            Input(head);
            break;
        case 2:
            allinput(head);
            break;
        default:return;
    }}while(select!=3);
}

void Input(LinkList head)//单独添加图书信息
{
	LinkList p,rear=head;
	char name[20],author[20],publisher[20],type[20];
	int id,pubtime,price,Num;
    FILE *fp;

    if((fp=fopen("bookinfo.dat","r"))==NULL)
	{
		printf("File Open Error!\n");
		exit(0);
	}

	while(fscanf(fp,"%d%s%s%s%s%d%d%d",&id,name,author,publisher,type,&pubtime,&price,&Num)!=EOF)
    {
      p=(LinkList)malloc(sizeof(LNode));
	  p->id=id;
	  strcpy(p->name,name);
	  strcpy(p->author,author);
	  strcpy(p->publisher,publisher);
	  strcpy(p->type,type);
	  p->pubtime=pubtime;
	  p->price=price;
	  p->Num=Num;
	  rear->next=p;
	  rear=p;
    }

	printf("请依次输入图书编号、书名、作者、出版社、类别、出版年月日、价格,输入-1表示输入结束\n");
    printf("输入示例：201501 西游记 吴承恩 中华  名著 19580624 56\n");
    while(scanf("%d",&id),id!=-1)
    {
      p=(LinkList)malloc(sizeof(LNode));
      scanf("%s%s%s%s%d%d%d",name,author,publisher,type,&pubtime,&price,&Num);
	  p->id=id;
	  strcpy(p->name,name);
	  strcpy(p->author,author);
	  strcpy(p->publisher,publisher);
	  strcpy(p->type,type);
	  p->pubtime=pubtime;
	  p->price=price;
	  p->Num=Num;
	  rear->next=p;
	  rear=p;
	}

   rear->next=NULL;
   Save(head);
   printf("现在的图书信息为：\n");
   Output(head);
}
void allinput(LinkList head)//批量添加图书信息
{
    LinkList p,rear=head;
	char name[20],author[20],publisher[20],type[20];
	int id,pubtime,price,Num;
    FILE *fp;

    if((fp=fopen("bookinfo.dat","r"))==NULL)
	{
		printf("File Open Error!\n");
		exit(0);
	}

	while(fscanf(fp,"%d%s%s%s%s%d%d%d",&id,name,author,publisher,type,&pubtime,&price,&Num)!=EOF)
    {
      p=(LinkList)malloc(sizeof(LNode));
	  p->id=id;
	  strcpy(p->name,name);
	  strcpy(p->author,author);
	  strcpy(p->publisher,publisher);
	  strcpy(p->type,type);
	  p->pubtime=pubtime;
	  p->price=price;
	  p->Num=Num;
	  rear->next=p;
	  rear=p;
    }
    if((fp=fopen("待批量添加的新书信息.txt","r"))==NULL)
	{
		printf("File Open Error!\n");
		exit(0);
	}

	while(fscanf(fp,"%d%s%s%s%s%d%d%d",&id,name,author,publisher,type,&pubtime,&price,&Num)!=EOF)
    {
      p=(LinkList)malloc(sizeof(LNode));
	  p->id=id;
	  strcpy(p->name,name);
	  strcpy(p->author,author);
	  strcpy(p->publisher,publisher);
	  strcpy(p->type,type);
	  p->pubtime=pubtime;
	  p->price=price;
	  p->Num=Num;
	  rear->next=p;
	  rear=p;
    }
    rear->next=NULL;
    Save(head);
    printf("新书已批量导入！\n");
    printf("当前图书信息为：\n");
    Output(head);
}
void Save(LinkList head)//将图书馆信息导入文件中
{
	FILE *fp;
	LinkList p;

	if((fp=fopen("bookinfo.dat","w"))==NULL)
	{
		printf("File Open Error!\n");
		exit(0);
	}
    for(p=head->next;p;p=p->next)
	{
	   fprintf(fp,"%d%10s%10s%10s%10s%10d%8d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
	}
	fclose(fp);
}

void Output(LinkList head)//输出图书信息
{
   LinkList p=head->next;

   if(p==NULL)
   {
	   printf("没有图书信息\n");
   }
   else
   {
       printf("编号      书名    作者     出版社   类别 出版年月日 价格   库存\n");
	   while(p)
	   {
         printf("%d%8s%10s%8s%8s%10d%4d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
         p=p->next;
	   }
   }
}

void Sort(LinkList head)//图书排序（按书号）
{
   LinkList p1=head,p2,q=NULL;
   p2=p1;
   while(p1)
   {
       printf("OK");
       p1=p1->next;
       p2=p1->next;
       while(p2)
       {
           if(p1->id>p2->id)
		   {
		       q=p1;
		       p1=p2;
		       p2=q;
		       printf("xuhaihu ");
		   }
		   p2=p2->next;
       }
    }
   printf("排序后的图书信息为：\n");
   Output(head);
   Save(head);
}

void oldbook(LinkList head)//旧书下架
{
    do{
    printf("************************************\n");
    printf("*         1:按书名删除             *\n");
    printf("*         2:按出版时间删除         *\n");
    printf("*         3：退出                  *\n");
    printf("************************************\n\n");
    printf("      请输入你要进行的项目选项\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            titledelete(head);//按书名删除
            break;
        case 2:
            timedelete(head);//按出版时间删除
            break;
        default:return;
    }}while(select!=3);
}

void titledelete(LinkList head)//按书名删除
{
    LinkList p1=head,p3=head->next;
    char name[10];
	int  k=0;

	printf("请输入要删除图书的书名：\n");
	scanf("%s",name);
	while(p3)
	{
	    LinkList p2=p3;
		if(strcmp(p2->name,name)==0)
		{
		   k=1;
		   p3=p2->next;
		   p1->next=p2->next;
		   free(p2);
		}
		else
		{
			p1=p3;
			p3=p3->next;
		}
	}
	if(k==0)
	{
		printf("该图书信息不存在\n");
	}
	if(k==1)
	{
	  printf("删除后的图书信息为:\n");
	  Output(head);
	  Save(head);
	}
}

void timedelete(LinkList head)//按出版时间删除
{
    LinkList p1=head,p3=head->next;
    int pubtime,k=0;

	printf("请输入要删除图书的出版时间：\n");
	scanf("%d",&pubtime);
	while(p3)
	{
	    LinkList p2=p3;
		if(p2->pubtime<=pubtime)
		{
		  k=1;
		  p3=p2->next;
		  p1->next=p2->next;
		  free(p2);
		}
		else
		{
			p1=p3;
			p3=p3->next;
		}
	}
	if(k==0)
	{
		printf("符合条件的图书信息不存在\n");
	}
	if(k==1)
	{
		printf("删除后的图书信息为:\n");
	    Output(head);
		Save(head);
	}
}

void modify(LinkList head)//图书信息修改
{
    int  id,pubtime,price,Num;
	int  flag=0;
	char sel,name[20],author[20],publisher[20],type[20];
    LinkList p;

	printf("请输入要修改图书的编号：\n");
	scanf("%d",&id);

	if(head==NULL)
	{
		printf("没有图书信息\n");
	}
	for(p=head;p!=NULL;p=p->next)
	{
		if(p->id==id)
		{
			flag=1;
			break;
		}
	}
	if(flag==0)
		printf("图书信息不存在\n");
	if(flag==1)
	{
		printf("该图书的信息已查询到，信息如下：\n");
		printf("编号      书名    作者     出版社    类别    出版年月日   价格   库存\n");
	    printf("%d%8s%10s%8s%10s%10d%8d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
        //修改书名
		printf("是否修改书名，请输入 y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("请输入书名：\n");
			scanf("%s",name);
			strcpy(p->name,name);;
		}
		//修改作者名
		printf("是否修改作者名，请输入 y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("请输入作者名：\n");
			scanf("%s",author);
			strcpy(p->author,author);
		}
		//修改出版社
	    printf("是否修改出版社，请输入 y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("请输入出版社：\n");
			scanf("%s",publisher);
			strcpy(p->publisher,publisher);
		}
		//修改图书类型
	    printf("是否修改图书类型，请输入 y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("请输入图书类型：\n");
			scanf("%s",type);
			strcpy(p->type,type);
		}
		//修改出版时间
        printf("是否修改出版时间，请输入 y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("请输入出版时间：\n");
			scanf("%d",&pubtime);
			p->pubtime=pubtime;
		}
		//是否修改价格
		printf("是否修改价格，请输入 y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("请输入价格：\n");
			scanf("%d",&price);
			p->price=price;
		}
		printf("是否修改库存，请输入 y or n:\n");
		scanf(" %c",&sel);
		if(sel=='y')
		{
			printf("请输入库存：\n");
			scanf("%d",&Num);
			p->Num=Num;
		}
		printf("修改后的图书信息为：\n");
        printf("编号      书名    作者     出版社    类别    出版年月日   价格   库存\n");
	    printf("%d%8s%10s%8s%10s%10d%8d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);

		Save(head);
	}
}

void reader(LinkList head, linklist head1)//普通读者函数
{
    do{
    printf("************************************\n");
    printf("*          1:更改密码              *\n");
    printf("*          2:查询图书信息          *\n");
    printf("*          3:借阅图书              *\n");
    printf("*          4:退出                  *\n");
    printf("************************************\n\n");
    printf("   请输入你要进行的项目选项\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            password(head1);//读者更改密码
            break;
        case 2:
            query(head);//查询图书信息
            break;
        case 3:
            borrow(head);
            break;
        default:return;
    }}while(select!=4);
}

void password(linklist head1)//读者更改密码
{
    linklist p=head1->next;
    int flge=0;
    char str[10], password[10];
    printf("请输入您的用户名或账号\n");
    scanf("%s",str);
    int m=1;
    while(p)
	{
		if(strcmp(p->name,str)==0||strcmp(p->id,str)==0)
		{
		    while(m==1)
            {
                printf("请输入您原来的密码\n");
                scanf("%s", password);
                if(strcmp(p->password, password)!=0)
                {
                    printf("密码错误，重新输入请按1， 退出请按2\n");
                    scanf("%d", &m);
                }
                if(strcmp(p->password, password)==0)
                    break;
		    }

		    if(m==2)
                break;
			printf("请输入您的新密码\n");
	        scanf("%s", password);
	        strcpy(p->password,password);
	        save(head1);
	        flge=1;
	        break;
		}
		p=p->next;
	}
	if(flge==0)
		printf("账号信息不存在\n");
}

void query(LinkList head)//查询图书信息
{
    do{
    printf("***********************************\n");
    printf("*         1:按书名查找            *\n");
    printf("*         2:作者名查找            *\n");
    printf("*         3:按出版社查找          *\n");
    printf("*         4:按书名作者名查找      *\n");
    printf("*         5:退出                  *\n");
    printf("***********************************\n\n");
    printf("     请输入你要进行的项目选项\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            titlequery(head);//书名查找
            break;
        case 2:
            authorquery(head);//作者名查找
            break;
        case 3:
            pressquery(head);//出版社查找
            break;
        case 4:
            titleauthor(head);//按书名作者名查找
            break;
        default:return;
    }}while(select!=5);
}

void titlequery(LinkList head)//书名查找
{
    LinkList p=head->next;
	char name[20];
	int flge=0;

    printf("请输入要查询的书名：\n");
	scanf("%s",name);
    while(p)
	{
		if(strstr(p->name,name)!=NULL||strstr(name,p->name)!=NULL)
		{
			printf("%d%8s%10s%8s%10s%10d%4d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
		    flge=1;
		}
		  p=p->next;
	}
	if(flge==0)
	 printf("该书信息不存在\n");

	return;
}

void authorquery(LinkList head)//作者名查找
{
	LinkList p=head->next;
	char author[20];
	int flge=0;

    printf("请输入要查询的作者名字：\n");
	scanf("%s",author);
    while(p)
	{
		if(strstr(p->author,author)!=NULL||strstr(author,p->author)!=NULL)
		{
			printf("%d%8s%10s%8s%10s%10d%4d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
		    flge=1;
		}
		  p=p->next;
	}
	if(flge==0)
	 printf("该书信息不存在\n");

	return;
}

void pressquery(LinkList head)//出版社查找
{
    LinkList p=head->next;
	char publisher[20];
	int flge=0;

    printf("请输入要出版社的作者名字：\n");
	scanf("%s",publisher);
    while(p)
	{
		if(strstr(p->publisher,publisher)!=NULL||strstr(publisher,p->publisher)!=NULL)
		{
			printf("%d%8s%10s%8s%10s%10d%4d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
		    flge=1;
		}
		  p=p->next;
	}
	if(flge==0)
	 printf("该书信息不存在\n");
	return;
}
void titleauthor(LinkList head)
{
    LinkList p=head->next;
	char name[20],author[20];
	int flge=0;
	printf("请输入要查询的书名和作者名字：\n");
	scanf("%s %s",name,author);
    while(p)
	{
		if((strcmp(p->name,name)==0)&&(strcmp(p->author,author)==0))
		{
			printf("%d%8s%10s%8s%10s%10d%4d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
		    flge=1;
		}
		  p=p->next;
	}
	if(flge==0)
	   printf("该书信息不存在\n");
    return ;
}

void borrow(LinkList head)
{
    LinkList p=head->next;
    int ID,flge=0,a=0;
    char sel;
    printf("请输入要借阅图书的编号：\n");
    scanf("%d",&ID);
    while(p)
	{
		if(p->id==ID)
		{
		    if(p->Num==0)
            {
                printf("已全部借出！");
            }
            else
            {
                a=p->Num;
                printf("请确定图书信息：\n");
                printf("编号      书名    作者     出版社   类别 出版年月日 价格   库存\n");
                printf("%d%8s%10s%8s%10s%10d%4d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
            }
            flge=1;
            break;
		}
		  p=p->next;
	}
	if(flge==0)
    {
        printf("该书信息不存在\n");
    }
    if(flge!=0&&a!=0)
    {
        printf("确定借阅么(一个帐号只能借一本)？请输入 y or n:\n");
        scanf(" %c",&sel);
        if(sel=='y')
		{
			p->Num=p->Num-1;
			printf("当前此图书信息为：\n");
			printf("编号      书名    作者     出版社   类别 出版年月日 价格   库存\n");
            printf("%d%8s%10s%8s%10s%10d%4d%8d\n",p->id,p->name,p->author,p->publisher,p->type,p->pubtime,p->price,p->Num);
		}
		if(sel=='n')
        {
            system("pause");
        }
        Save(head);
    }
}
