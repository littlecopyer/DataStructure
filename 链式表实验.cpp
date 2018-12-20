#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status;
typedef struct ElemType{ //数据元素类型定义
    int No;
    char Name[30];
}ElemType;
typedef struct LNode{  //链式表物理结构
	ElemType elem;
	struct LNode *next;
}LNode,*LinkList;

/*-------多表管理实现-------*/
typedef struct DataFiled{
    char name[30];  //每个表的名字
    LinkList head;  //子表的头指针
}DataFiled;
typedef struct Table{//总表的定义
    struct DataFiled List;//数据域
    struct Table *next; //指针域
}Table,*TableLink;
/*---------单表的函数 ---------*/
status IntiaList(LinkList &L);/*初始化线性表*/
status DestroyList(LinkList& L);/*摧毁线性表*/
status ClearList(LinkList & L);/*清空线性表*/
status ListEmpty(LinkList L);/*线性表判空*/
int ListLength(LinkList L);/*求表长*/
status GetElem(LinkList L,int i,ElemType *e);/*获取元素*/
int LocateElem(LinkList L,ElemType e,status (*compare)(ElemType , ElemType ));/*获取元素位序*/
status PriorElem(LinkList L,ElemType cur,ElemType * pre_e);/*获得前驱*/
status NextElem(LinkList L,ElemType cur,ElemType *next_e);/*获得后继*/
status ListInsert(LinkList &L,int i,ElemType e);/*插入元素*/
status ListDelete(LinkList &L,int i,ElemType *e);/*删除元素*/
status ListTrabverse(LinkList L, void (*visit)(ElemType*));/*遍历元素*/
void visit(ElemType*);/*打印元素*/
status compare(ElemType a, ElemType b);/*比较元素关系*/
status save(LinkList L,char *s);/*保存表格*/
status readfile(LinkList L);/*加载线性表*/

/*-----------多表的函数-----------*/
status initialTable(TableLink &TA);
status DestroyTable(TableLink &TA);
status ClearTable(TableLink TA);
status TableEmpty(TableLink TA);
int TableLength(TableLink TA);
int LocateList(TableLink TA);
status GetTableElemByName(TableLink TA,struct DataFiled* e);
status newSubList(TableLink TA);
status RewriteSublist(TableLink TA);
status SubListOperation(LinkList newList,int hasInitial,char *s);


int main(void){//主函数入口
     Table TA;
     TableLink TAP=&TA; //总表的头指针
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
	printf("          8. RewriteSubList\n");
	printf("    	  0. Exit\n");
	printf("-------------------------------------------------\n");
	printf("    请选择你的操作[0~8]:");
		scanf("%d",&op);
	switch(op){
    case 1:if(!flag&&initialTable(TAP))//未初始化并且初始化成功
              {
                 flag=1;
                 printf("初始化成功！\n");
              }
            else if(flag)
                printf("总表已初始化!不能重复初始化\n");
            else
                printf("初始化失败！\n");
	       system("pause");
            break;
    case 2:if(flag){
                if(DestroyTable(TAP)){
                    printf("成功摧毁总表！\n");flag=0;}
                else printf("摧毁失败！\n");
                    }
            else printf("总表未初始化!\n");
	       system("pause");
            break;
    case 3:if(flag){
	    		if(ClearTable(TAP))printf("成功清空总表！\n");
	    		else printf("无法清空总表格！\n");
			}
            else printf("总表未初始化!\n");
			system("pause");
            break;
    case 4:if(flag){
				if(TableEmpty(TAP))printf("总表格为空，无子表格存在\n");
				else printf("总表格不为空\n");}
            else printf("总表未初始化!\n");
            system("pause");
            break;
    case 5:if(flag){
                int i;
                i=TableLength(TAP);
                printf("表长为%d",i);
                }
            else printf("总表未初始化!\n");
            system("pause");
            break;
    case 6:
            if(flag){
                struct DataFiled *q;//用q来接收获取的线性表
                q=(struct DataFiled*)malloc(sizeof(struct DataFiled));
                if(GetTableElemByName(TAP,q)){
                   void(*visit1)(ElemType *);//遍历线性表
                        printf("表名：《%s》\n",(*q).name);
                        if(ListTrabverse((*q).head,visit1)==ERROR)
                            printf("线性表为空表！\n");
                }}
            else printf("总表未初始化!\n");
            system("pause");
            break;
    case 7:if(flag){
                if(newSubList(TAP)==OK)
                    printf("成功创建新的子表！\n");}
            else printf("总表未初始化!\n");
            system("pause");
            break;
    case 8:
            if(flag){
                if(RewriteSublist(TAP))
                    printf("成功修改子表！\n");
				else
					printf("表中不存在该表！\n");}
            else printf("总表未初始化!\n");
            system("pause");
            break;
    case 0:system("pause");
            break;
        }
    }
  printf("欢迎下次再使用本系统！\n");
  return 0;
}

status IntiaList(LinkList &L){//线性表初始化
	L=(LinkList)malloc(sizeof(LNode));
	if(!L) exit(OVERFLOW);
	L->next=NULL;
	return OK;
}

status DestroyList(LinkList &L){//摧毁线性表
    L->next=NULL;
    free(L);
    return OK;
}

status ClearList(LinkList &L){//清空线性表
    L->next=NULL;
    return OK;
}

status ListEmpty(LinkList L){//线性表判空
    if(L->next!=NULL)
        return FALSE;
    else
        return TRUE;
}

int ListLength(LinkList L){//返回表长
    int length=0;
    LinkList p=L->next;
    while(p){
        length++;
    	p=p->next;
    }
    return length;

}
/*-------------------------------------------------------------
函数名：GetElem
函数功能：获得线性表L中第i个元素，并用e返回
函数参数：L：线性表；i:获取目标元素的下标值；e:用于接收目标元素
函数返回值：成功返回OK；如果值越界返回ERROR
--------------------------------------------------------------*/
status GetElem(LinkList L,int i,ElemType *e){
    //L为带头结点的单链表的头指针；
    LinkList p;
    p=L->next;
    int j=1;
    while(p&&j<i){
        p=p->next;
        j++;
    }
    if(!p||j>i)
        return ERROR;
    *e=p->elem;
    return OK;
}

int LocateElem(LinkList L,ElemType e,status (*compare1)(ElemType , ElemType )){//获取元素位序
    int i=0;
    compare1=compare;//函数指针指向compare函数
    LinkList p=L->next;
    while(p){
        if(compare1(p->elem,e))
            return i+1;
        else{
            p=p->next;
            i++;
        }
    }
    if(i==0)
        printf("该表为空表\n");
    return 0;
}

status PriorElem(LinkList L,ElemType cur,ElemType *pre_e){//获得前驱
    LinkList p1,p2;
    p2=L->next;
    p1=L;
    while(p2){
        if((p2->elem.No==cur.No)&&(!strcmp(p2->elem.Name,cur.Name))){
            if(p1==L)
                return ERROR;
            else{
                *pre_e=p1->elem;
                return OK;
            }
        }
        else{
            p1=p1->next;
            p2=p2->next;
        }
    }
    return FALSE;
}

status NextElem(LinkList L,ElemType cur,ElemType * next_e){//获得后继
   LinkList p1,p2;
    p2=L->next;
    p1=L->next;
    if(p2)  p2=p2->next;
    while(p2){
        if((p1->elem.No==cur.No)&&(!strcmp(p1->elem.Name,cur.Name))){
            if(!p1)
                return ERROR;
            else{
                *next_e=p2->elem;
                return OK;
            }
        }
        else{
            p1=p1->next;
            p2=p2->next;
        }
    }
    return FALSE;
}
/*------------------------------------------------------------
函数名称：ListInsert
函数功能：在线性表L中第i个元素前插入元素e
函数参数：&L：线性表L的地址；i:插入元素的位置；e:插入元素的值
函数返回值：如果插入成功，返回OK，如果i值越界则返回ERROR
------------------------------------------------------------*/
status ListInsert(LinkList &L,int i,ElemType e){//插入元素
    LinkList p=L,s;
    int j=0;
    while(p&&j<i-1){
        p=p->next;
        j++;//寻找第i个结点
    }
    if(!p||j>i-1)//i小鱼1或者大于表长加1;
        return ERROR;
    s=(LinkList)malloc(sizeof(LNode));
    s->elem=e;
	s->next=p->next;
    p->next=s;
    return OK;
}

status ListDelete(LinkList &L,int i,ElemType * e){
    LinkList p=L,q;
    int j=0;
    while(p->next&&j<i-1){
        p=p->next;
        ++j;
    }
    if(!(p->next)||j>i-1) return ERROR;
    q=p->next;p->next=q->next;
    *e=q->elem;free(q);
    return OK;
}
status ListTrabverse(LinkList L, void (*visit1)(ElemType*)){
	visit1=visit;
    LinkList p=L->next;
   if(ListEmpty(L)){
    printf("线性表为空！\n");
    return ERROR;
   }
    while(p){
        visit1(&(p->elem));
        p=p->next;
    }
    return OK;
}

void visit(ElemType *e)
{
        printf("%d\t%s\n",(*e).No,(*e).Name);
}

status compare(ElemType a, ElemType b)
{
    if((a.No==b.No)&&(!strcmp(a.Name,b.Name)))
        return TRUE;
    else
        return FALSE;
}

status save(LinkList L,char *s){
    FILE  *fp;  int i;
    if ((fp=fopen(s,"ab+"))==NULL)
        {
         printf("File open error\n ");
        return ERROR;
        }
    LinkList p=L->next;
    while(p){
        fwrite(&(p->elem),sizeof(ElemType),1,fp);
        p=p->next;}
    fclose(fp);
    return OK;
}

status readfile(LinkList *L){
   FILE  *fp;  char filename[30];
    printf("input file name: ");
    scanf("%s",filename);
    LinkList p,q;
    if ((fp=fopen(filename,"rb"))==NULL)
	{
	 printf("File open error\n ");
	 return ERROR;
	}
    p=(LinkList)malloc((sizeof(LNode)));
    q=(LinkList)malloc((sizeof(LNode)));
    p=*L;
    while(fread(&(q->elem),sizeof(ElemType),1,fp)){
    	printf("%d %s\n",(*q).elem.No,(*q).elem.Name);
       p->next=q;
       p=p->next;
       q=(LinkList)malloc((sizeof(LNode)));
    }
	   p->next=NULL;
    return OK;
}


status initialTable(TableLink &TA){
    TA=(TableLink)malloc(sizeof(Table));
    if(!TA) exit(OVERFLOW);
	TA->next=NULL;
	return OK;
}

status DestroyTable(TableLink &TA)
{
    TA->next=NULL;
    free(TA);
    return OK;
}

status ClearTable(TableLink TA){
   TA->next=NULL;
    return OK;
}

status TableEmpty(TableLink TA)
{
    if(TA->next!=NULL)
        return FALSE;
    else
        return TRUE;
}

int TableLength(TableLink TA){
    int length=0;
    TableLink p=TA->next;
    while(p){
        length++;
    	p=p->next;
    }
    return length;
}

int LocateList(TableLink TA){
    int index;
    char s[30];
    printf("请输入需要查询的表的名字:\n");
    scanf("%s",s);
    TableLink p=TA->next;
    for(index=0;p&&strcmp((*p).List.name,s);index++)
        p=p->next;
    if(!TA){
        printf("经查询，表中不存在名为%s的表格!\n",s);
        return 0;}
    else
        return index+1;

}

status GetTableElemByName(TableLink TA,struct DataFiled* e){
     int index;
    char s[30];
    printf("请输入需要查询的表的名字:\n");
    scanf("%s",s);
    TableLink p=TA->next;
    while(p){
    	if(!strcmp((*p).List.name,s))
    		break;
    	else
    	 p=p->next;
	}

    if(!p){
        printf("经查询，表中不存在名为%s的表格!\n",s);
        return 0;}
    else{
        *e=(*p).List;
        return OK;
    }
}

status newSubList(TableLink TA){
    char s[30];
    printf("请输入新建子表的名字：\n");
    scanf("%s",s);
    int i;
    TableLink TB=TA,T=TA;
    TB=TB->next;//TB为遍历指针，T为TB的前驱结点指针，T->next==TB
    while(TB){
        if(!strcmp((*TB).List.name,s)){
            printf("已经存在名为%s的线性表！\n",s);
            return ERROR;
        }
        else{
            TB=TB->next;
            T=T->next;}
        }//end of while
        /*循环结束代表遍历到达表尾，T==tail,TB==T->next==NULL;*/
    TB=(TableLink)malloc(sizeof(Table));//新建子节点并为其创建空间
    T->next=TB;
    (*TB).List.head=(LinkList)malloc(sizeof(LNode));
 	if(!SubListOperation((*TB).List.head,0,s)){
        free((*TB).List.head);
        free(TB);
        T->next=NULL;
        return ERROR;}
    else{
    strcpy((*TB).List.name,s);//为表赋名字
    TB->next=NULL;//为表尾结点的指针域赋值为NULL，防止指针悬空
    return OK;}
}

status RewriteSublist(TableLink TA){
    char s[30];
    printf("请输入需要修改子表的名字：\n");
    scanf("%s",s);
    int i;
    TableLink TB=TA;//TB为遍历指针
    TB=TB->next;//遍历指针指向头结点
    while(TB){//对总表进行遍历
        if(!strcmp((*TB).List.name,s)){//比较名字是否相同
            if(!SubListOperation((*TB).List.head,1,s))//对子表进行操作，1代表该表已经进行初始化，不必再次初始化
                return ERROR;
            else
            	return OK;
        }
        else    TB=TB->next;
    }//end of while
    return ERROR;
}

status SubListOperation(LinkList newList,int hasInitial,char *s){//判断线性表是否初始化
    LinkList L;
    L=newList;
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
            ElemType e;
            int i;
            printf("您想获得第几个元素？\n");
            scanf("%d",&i);
            if(GetElem(L,i,&e)==OK)
                printf("第%d个元素为%d %s\n",i,e.No,e.Name);
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
            scanf("%d %s",&e.No,e.Name);
            status (*compare)(ElemType a, ElemType b);//定义函数指针
            if(!(i=LocateElem(L,e,compare)))
               printf("线性表中不存在元素%d %s\n",e.No,e.Name);
            else
                printf("%d %s为于线性表中第%d个位置\n",e.No,e.Name,i);
		 }
		 else
            printf("线性表不存在！\n");
		 system("pause");
		 break;
	   case 8://找制定元素前驱
            if(hasInitial){
            printf("请输入当前元素！\n");
            scanf("%d %s",&cur.No,cur.Name);
            if(PriorElem(L,cur,&pre_e))
                printf("%d %s前一个元素为%d %s\n",cur.No,cur.Name,pre_e.No,pre_e.Name);
            else
                printf("线性表中不存在该元素或者该元素没有前驱\n");
		 }
		 else
            printf("线性表不存在！\n");
		 system("pause");
		 break;
	   case 9://找指定元素后继
		 if(hasInitial){
            printf("请输入当前元素！\n");
            scanf("%d %s",&cur.No,cur.Name);
            if(NextElem(L,cur,&next_e))
                printf("%d %s后一个元素为%d %s\n",cur.No,cur.Name,next_e.No,next_e.Name);
            else
                printf("线性表中不存在或者没有后继\n",cur,cur);
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
            scanf("%d %s",&e.No,e.Name);
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
            ElemType e;
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
           void(*visit1)(ElemType*);
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
   	newList->next=L->next;
   	return OK;
   	}
	else
		return ERROR;
}
