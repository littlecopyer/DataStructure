/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct{  //顺序表（顺序结构）的定义
	ElemType * elem;
	int length;
	int listsize;
}SqList;

struct LNode{
    char name[30];  //每个表的名字
    SqList lists;
};
typedef struct Table{//总表的定义
    struct LNode *elem;
    int length;
}Table;
/*-----page 19 on textbook ---------*/
status IntiaList(SqList & L);/*初始化线性表*/
status DestroyList(SqList & L);/*摧毁线性表*/
status ClearList(SqList &L);/*清空线性表*/
status ListEmpty(SqList L);/*线性表判空*/
int ListLength(SqList L);/*求表长*/
status GetElem(SqList L,int i,ElemType *e);/*获取元素*/
int LocateElem(SqList L,ElemType e,status (*compare)(ElemType , ElemType ));/*获取元素位序*/
status PriorElem(SqList L,ElemType cur,ElemType * pre_e);/*获得前驱*/
status NextElem(SqList L,ElemType cur,ElemType *next_e);/*获得后继*/
status ListInsert(SqList & L,int i,ElemType e);/*插入元素*/
status ListDelete(SqList & L,int i,ElemType *e);/*删除元素*/
status ListTrabverse(SqList L, void (*visit)(void const *e));/*遍历元素*/
void visit(void const *e);/*打印元素*/
status compare(ElemType a, ElemType b);/*比较元素关系*/
status save(SqList L,char *s);/*保存表格*/
status readfile(SqList *L);/*加载线性表*/
/*--------------------------------------------*/
/*---------------总表操作函数----------------*/
status initialTable(Table &TA);
status DestroyTable(Table &TA);
status ClearTable(Table &TA);
status TableEmpty(Table TA);
int TableLength(Table TA);
int LocateList(Table TA);
status GetTableElemByName(Table TA,struct LNode* e);
status newSubList(Table &TA);
status DeleteSubList(Table &TA,struct LNode *e);
status RewriteSublist(Table &TA);
status SubListOperation(SqList *newList,int hasInitial,char *s);
int main(void){
    Table TA;
    int flag=0;//判断总表是否初始化
    int op=1;//op代表选择的操作数
    while(op){
	system("cls");	printf("\n\n");
	printf("                    总表操作                       \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. IntialTable\n");
	printf("    	  2. DestroyTable\n");
	printf("    	  3. ClearTable\n");
	printf("    	  4. TableEmpty \n");
	printf("    	  5. TableLength \n");
	printf("    	  6. GetTableElemByName\n");
	printf("          7. newSubList\n");
	printf("          8. DeleteSubList\n");
	printf("          9.RewriteSubList\n");
	printf("          10.PrintAllTheTables\n");
	printf("    	  0. Exit\n");
	printf("-------------------------------------------------\n");
	printf("    请选择你的操作[0~10]:");
		scanf("%d",&op);
	switch(op){
    case 1:if(!flag&&initialTable(TA))//未初始化并且初始化成功
                flag=1;
            else if(flag)
                printf("总表已初始化!不能重复初始化\n");
            else
                printf("初始化失败！\n");
	       system("pause");
            break;
    case 2:if(flag){
                if(DestroyTable(TA)){
                    printf("成功摧毁总表！\n");flag=0;}
                else printf("摧毁失败！\n");
                    }
            else printf("总表未初始化!\n");
	       system("pause");
            break;
    case 3:if(flag){
	    		if(ClearTable(TA))printf("成功清空总表！\n");
	    		else printf("无法清空总表格！\n");
			}
            else printf("总表未初始化!\n");
			system("pause");
            break;
    case 4:if(flag){
				if(TableEmpty(TA))printf("总表格为空，无子表格存在\n");
				else printf("总表格不为空\n");}
            else printf("总表未初始化!\n");
            system("pause");
            break;
    case 5:if(flag){
                int i;
                i=TableLength(TA);
                printf("表长为%d",i);
                }
            else printf("总表未初始化!\n");
            system("pause");
            break;
    case 6:
            if(flag){
                struct LNode *q;//用q来接收获取的线性表
                q=(struct LNode*)malloc(sizeof(struct LNode));
                if(GetTableElemByName(TA,q)){
                   void(*visit1)(void const *);//遍历线性表
                        printf("表名：《%s》\n",(*q).name);
                        if(ListTrabverse((*q).lists,visit1)==ERROR)
                            printf("线性表为空表！\n");
                }}
            else printf("总表未初始化!\n");
            system("pause");
            break;
    case 7:if(flag){
                if(newSubList(TA)==OK)
                    printf("成功创建新的子表！\n");}
            else printf("总表未初始化!\n");
            system("pause");
            break;
    case 8:
            if(flag){
                struct LNode *r;
                r=(struct LNode*)malloc(sizeof(struct LNode));
                if(DeleteSubList(TA,r))
                    printf("成功删除子表！\n");}
            else printf("总表未初始化!\n");
            system("pause");
            break;
    case 9:if(flag){
                if(RewriteSublist(TA))
                    printf("成功修改子表！\n");}
            else printf("总表未初始化!\n");
            system("pause");
            break;
    case 10:if(flag){
                int index;
                void(*visit1)(void const *);
                for(index=0;index<TA.length;index++){
                        printf("---《%s》---\n",TA.elem[index].name);
                        if(ListTrabverse(TA.elem[index].lists,visit1)==ERROR)
                            printf("线性表为空表！\n");}
                            }

    case 0:system("pause");
            break;
        }
    }
  printf("欢迎下次再使用本系统！\n");
  return 0;
}//end of main()
/*--------page 23 on textbook --------------------*/
status IntiaList(SqList & L){//线性表初始化
	L.elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    if(!L.elem) exit(OVERFLOW);//
	L.length=0;
    L.listsize=LIST_INIT_SIZE;
	return OK;
}

status DestroyList(SqList & L){//摧毁线性表
    ClearList(L);
    free(L.elem);
  //  *=NULL;
    return OK;
}

status ClearList(SqList &L){//清空线性表
    L.length=0;
    return OK;
}

status ListEmpty(SqList L){//线性表判空
    if(L.length==0)
        return TRUE;
    else
        return FALSE;
}

int ListLength(SqList L){//返回表长
    return L.length;
}
/*-------------------------------------------------------------
函数名：GetElem
函数功能：获得线性表L中第i个元素，并用e返回
函数参数：L：线性表；i:获取目标元素的下标值；e:用于接收目标元素
函数返回值：成功返回OK；如果值越界返回ERROR
--------------------------------------------------------------*/
status GetElem(SqList L,int i,ElemType *e){
    if(i<1||i>L.length) return ERROR;
    *e=L.elem[i-1];
    return OK;
}

int LocateElem(SqList L,ElemType e,status (*compare1)(ElemType , ElemType )){//获取元素位序
    int i;
    compare1=compare;//函数指针指向compare函数
    for(i=0;i<L.length;i++)
        if(compare1(L.elem[i],e))
            return i+1;
    return 0;
}

status PriorElem(SqList L,ElemType cur,ElemType *pre_e){//获得前驱
    int i=0;
    for(i=0;i<L.length;i++)
        if(L.elem[i]==cur)
            break;
    if(i==0||i==L.length) return ERROR;
     *pre_e=L.elem[i-1];
     return OK;
}

status NextElem(SqList L,ElemType cur,ElemType * next_e){//获得后继
    int i=0;
    for(i=0;i<L.length;i++)
        if(L.elem[i]==cur)
            break;
    if(i==L.length||i==L.length-1) return ERROR;
    *next_e=L.elem[i+1];
    return OK;
}
/*------------------------------------------------------------
函数名称：ListInsert
函数功能：在线性表L中第i个元素前插入元素e
函数参数：&L：线性表L的地址；i:插入元素的位置；e:插入元素的值
函数返回值：如果插入成功，返回OK，如果i值越界则返回ERROR
------------------------------------------------------------*/
status ListInsert(SqList & L,int i,ElemType e){//插入元素
    if(i<1||i>L.length+1) return ERROR;
    if(L.length>=L.listsize){
        ElemType *newbase;
        newbase=(ElemType *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
        if(!newbase) exit(OVERFLOW);
        L.elem=newbase;
        L.listsize+=LISTINCREMENT;
    }
    ElemType *p,*q;
    q=&(L.elem[i-1]);
    for(p=&(L.elem[L.length-1]);p>=q;--p)
        *(p+1)=*p;
    *q=e;
    ++L.length;
    return OK;
}

status ListDelete(SqList & L,int i,ElemType * e){
    if(i<1||i>L.length) return ERROR;
    ElemType *p,*q;
    p=&(L.elem[i-1]);
    *e=*p;
    q=L.elem+L.length-1;
    for(++p;p<=q;++p) *(p-1)=*p;
    --L.length;
    return OK;
}
status ListTrabverse(SqList L, void (*visit1)(void const *)){
   int i;
   ElemType *ptr;
   ptr=L.elem;
   visit1=visit;
   if(L.length==0) return ERROR;
   for(i=0;i<L.length;i++)
       visit1(ptr+i);
   printf("\n");
   return OK;
}

void visit(void const *e)
{
        printf("%d\t",*(ElemType *)e);
}

status compare(ElemType a, ElemType b)
{
    if(a==b)
        return TRUE;
    else
        return FALSE;
}

status save(SqList L,char *s){
    FILE  *fp;  int i;
    if ((fp=fopen(s,"ab+"))==NULL)
        {
         printf("File open error\n ");
        return ERROR;
        }
    fwrite(L.elem,sizeof(ElemType),L.length,fp);
    fclose(fp);
    return OK;
}

status readfile(SqList *L){
   FILE  *fp;  char filename[30];
    printf("input file name: ");
    scanf("%s",filename);
    (*L).length=0;
    if ((fp=fopen(filename,"rb"))==NULL)
	{
	 printf("File open error\n ");
	 return ERROR;
	}
while(fread(&(*L).elem[(*L).length],sizeof(ElemType),1,fp))
   (*L).length++;
//这里从文件中逐个读取数据元素恢复顺序表，对于不同的物理结构，可通过读//取的数据元素恢复内存中的物理结构。
    fclose(fp);
    return OK;
}

status initialTable(Table &TA){
    TA.elem=(struct LNode*)malloc(100*sizeof(struct LNode));
    if(TA.elem){
        TA.length=0;
        printf("成功创建总表！\n");
        return OK;}
    else{
        printf("总表创建失败！\n");
        exit(OVERFLOW);}
}
status DestroyTable(Table &TA)
{
    ClearTable(TA);
    free(&TA);
    return OK;
}
status ClearTable(Table &TA){
    TA.length=0;
    return OK;
}
status TableEmpty(Table TA)
{
    if(TA.length==0)
        return TRUE;
    else
        return FALSE;
}
int TableLength(Table TA){
    return TA.length;
}
int LocateList(Table TA){
    int index;
    char s[30];
    printf("请输入需要查询的表的名字:\n");
    scanf("%s",s);
    for(index=0;index<TA.length;index++){
        if(!strcmp(TA.elem[index].name,s)){
                printf("表位于总表第%d个！\n",index+1);
                return index+1;
        }
    }
    printf("经查询，表中不存在名为%s的表格!\n",s);
    return 0;

}

status GetTableElemByName(Table TA,struct LNode* e){
    int index;
    index=LocateList(TA);
    if(index){
        *e=TA.elem[index-1];
        return OK;
    }
    else
        return FALSE;
}
status newSubList(Table &TA){
    if(TA.length>=100){
        return OVERFLOW;
    }
    printf("请输入新建子表的名字：\n");
    scanf("%s",TA.elem[TA.length].name);
    int i;
    for(i=0;i<TA.length;i++){
        if(!strcmp(TA.elem[TA.length].name,TA.elem[i].name)){
            printf("已经存在名为%s的线性表！\n",TA.elem[TA.length].name);
            memset(TA.elem[TA.length].name, 0x00, sizeof (char) * 30);
            return ERROR;
        }
    }
    SqList *newList=&TA.elem[TA.length].lists;
 	if(!SubListOperation(newList,0,TA.elem[TA.length].name)){
 		memset(TA.elem[TA.length].name, 0x00, sizeof (char) * 30);
        return ERROR;}
    else{
    ++TA.length;
    return OK;}
}
status DeleteSubList(Table &TA,struct LNode *e){
    int index;
    index=LocateList(TA);
    if(!index)
        return FALSE;
    struct LNode *p,*q;
    p=&(TA.elem[index-1]);
    *e=*p;
    q=TA.elem+TA.length-1;
    for(++p;p<=q;++p) *(p-1)=*p;
    --TA.length;
    return OK;
}
status RewriteSublist(Table &TA){
    int index;
    SqList *e;
    index=LocateList(TA);
    if(!index)
        return FALSE;
    else{
        e=&TA.elem[index-1].lists;
        if(SubListOperation(e,1,TA.elem[index-1].name))
        	return OK;
        else
        	return ERROR;
    }
}


status SubListOperation(SqList *newList,int hasInitial,char *s){//判断线性表是否初始化
    SqList L,LA;
    L=*newList;

  int op=1;//op代表选择的操作数
  ElemType cur,pre_e,next_e;//当前，前驱，后继三个元素
 while(op){
	system("cls");	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("--------------您正在对表《%s》进行操作-----------\n",s);
	printf("-------------------------------------------------\n");
	printf("    	  1. IntiaList       7. LocateElem\n");
	printf("    	  2. DestroyList     8. PriorElem\n");
	printf("    	  3. ClearList       9. NextElem \n");
	printf("    	  4. ListEmpty      10. ListInsert\n");
	printf("    	  5. ListLength     11. ListDelete\n");
	printf("    	  6. GetElem        12. ListTrabverse\n");
	printf("    	  13. save          14. readfile\n");
	printf("    	  0. Exit\n");
	printf("-------------------------------------------------\n");
	printf("    请选择你的操作[0~14]:");
	scanf("%d",&op);
    switch(op){
	   case 1://线性表初始化
            if((!hasInitial)&&IntiaList(L)==OK)
            {  printf("线性表创建成功！\n");
                hasInitial=1; //标识初始化成功
            }
            else printf("线性表创建失败！\n");
		 system("pause");
		 break;
	   case 2://销毁线性表
		 if(hasInitial){
            if(DestroyList(L)){
            hasInitial=0; //未初始化
            printf("成功销毁线性表！\n");
		 }
		 }
		 else
            printf("线性表不存在，无法销毁！\n");
		 system("pause");
		 break;
	   case 3://清空线性表
		 if(hasInitial){
            ClearList(L);
            printf("成功清空线性表！\n");
		 }
		 else
            printf("线性表不存在，无法清空！\n");
		 system("pause");
		 break;
	   case 4://判空线性表
		 if(hasInitial){
            if(ListEmpty(L)) printf("线性表为空！\n");
            else  printf("线性表非空！\n");
		 }
		 else
            printf("线性表不存在！\n");
		 system("pause");
		 break;
	   case 5://线性表长度
		 if(hasInitial){
            int i;
            i=ListLength(L);
            printf("线性表长度为%d\n",i);
		 }
		 else
            printf("线性表不存在！\n");
		 system("pause");
		 break;
	   case 6://获得指定位置元素
		 if(hasInitial){
            ElemType e=0;
            int i;
            printf("您想获得第几个元素？\n");
            scanf("%d",&i);
            if(GetElem(L,i,&e)==OK)
                printf("第%d个元素为%d\n",i,e);
            else
                printf("无法获得第%d个元素\n",i);
		 }
		 else
            printf("线性表不存在！\n");
		 system("pause");
		 break;
	   case 7://查找指定元素位置
		 if(hasInitial){
            int i;
            ElemType e;
            printf("请输入您想查找的元素：");
            scanf("%d",&e);
            status (*compare)(ElemType a, ElemType b);//定义函数指针
            if(!(i=LocateElem(L,e,compare)))
               printf("线性表中不存在元素%d\n",e);
            else
                printf("%d为于线性表中第%d个位置\n",e,i);
		 }
		 else
            printf("线性表不存在！\n");
		 system("pause");
		 break;
	   case 8://找制定元素前驱
            if(hasInitial){
            printf("请输入当前元素！\n");
            scanf("%d",&cur);
            if(PriorElem(L,cur,&pre_e))
                printf("%d前一个元素为%d\n",cur,pre_e);
            else
                printf("线性表中不存在%d或者%d没有前驱\n",cur,cur);
		 }
		 else
            printf("线性表不存在！\n");
		 system("pause");
		 break;
	   case 9://找指定元素后继
		 if(hasInitial){
            printf("请输入当前元素！\n");
            scanf("%d",&cur);
            if(NextElem(L,cur,&next_e))
                printf("%d后一个元素为%d\n",cur,next_e);
            else
                printf("线性表中不存在%d或者%d没有后继\n",cur,cur);
		 }
		 else
            printf("线性表不存在！\n");
		 system("pause");
		 break;
	   case 10://插入元素
		 if(hasInitial){
            ElemType e;
            int i;
            printf("您想插入到第几个元素前:");
            scanf("%d",&i);
            printf("请您输入想插入的元素：");
            scanf("%d",&e);
            if(ListInsert(L,i,e)==OK)
                printf("插入成功！\n");
            else
                printf("插入失败！\n");
		 }
		 else
            printf("线性表不存在！\n");
		 system("pause");
		 break;
	   case 11://删除元素
		 if(hasInitial){
            ElemType e=0;
            int i;
            printf("您想删除第几个元素:");
            scanf("%d",&i);
            if(ListDelete(L,i,&e)==OK)
                printf("删除成功！\n");
            else
                printf("删除失败！\n");
		 }
		 else
            printf("线性表不存在！\n");
		 system("pause");
		 break;
	   case 12://遍历元素
		 if(hasInitial){
           void(*visit1)(void const *e);
            if(ListTrabverse(L,visit1)==ERROR)
                printf("线性表为空表！\n");
		 }
		 else
            printf("线性表不存在！\n");
		 system("pause");
		 break;
       case 13://保存数据
        if(hasInitial){
            if(save(L,s))
                printf("保存成功！\n");
            else
                printf("保存失败！\n");
        }
        else printf("线性表不存在，无法保存数据！\n");
            system("pause");break;
       case 14://读取文件
        if(hasInitial)
            readfile(&L);
        else printf("未初始化，无法读取！\n");
        system("pause");break;
	   case 0:
         break;
	}//end of switch
  }//end of while
  if(hasInitial){
   	*newList=L;
   	return OK;}
	else
		return ERROR;

}
