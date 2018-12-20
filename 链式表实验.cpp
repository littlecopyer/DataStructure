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
typedef struct ElemType{ //����Ԫ�����Ͷ���
    int No;
    char Name[30];
}ElemType;
typedef struct LNode{  //��ʽ������ṹ
	ElemType elem;
	struct LNode *next;
}LNode,*LinkList;

/*-------������ʵ��-------*/
typedef struct DataFiled{
    char name[30];  //ÿ���������
    LinkList head;  //�ӱ��ͷָ��
}DataFiled;
typedef struct Table{//�ܱ�Ķ���
    struct DataFiled List;//������
    struct Table *next; //ָ����
}Table,*TableLink;
/*---------����ĺ��� ---------*/
status IntiaList(LinkList &L);/*��ʼ�����Ա�*/
status DestroyList(LinkList& L);/*�ݻ����Ա�*/
status ClearList(LinkList & L);/*������Ա�*/
status ListEmpty(LinkList L);/*���Ա��п�*/
int ListLength(LinkList L);/*���*/
status GetElem(LinkList L,int i,ElemType *e);/*��ȡԪ��*/
int LocateElem(LinkList L,ElemType e,status (*compare)(ElemType , ElemType ));/*��ȡԪ��λ��*/
status PriorElem(LinkList L,ElemType cur,ElemType * pre_e);/*���ǰ��*/
status NextElem(LinkList L,ElemType cur,ElemType *next_e);/*��ú��*/
status ListInsert(LinkList &L,int i,ElemType e);/*����Ԫ��*/
status ListDelete(LinkList &L,int i,ElemType *e);/*ɾ��Ԫ��*/
status ListTrabverse(LinkList L, void (*visit)(ElemType*));/*����Ԫ��*/
void visit(ElemType*);/*��ӡԪ��*/
status compare(ElemType a, ElemType b);/*�Ƚ�Ԫ�ع�ϵ*/
status save(LinkList L,char *s);/*������*/
status readfile(LinkList L);/*�������Ա�*/

/*-----------���ĺ���-----------*/
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


int main(void){//���������
     Table TA;
     TableLink TAP=&TA; //�ܱ��ͷָ��
    int flag=0;//�ж��ܱ��Ƿ��ʼ��
    int op=1;//op����ѡ��Ĳ�����
    while(op){
	system("cls");	printf("\n\n");
	printf("                    �ܱ����                       \n");
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
	printf("    ��ѡ����Ĳ���[0~8]:");
		scanf("%d",&op);
	switch(op){
    case 1:if(!flag&&initialTable(TAP))//δ��ʼ�����ҳ�ʼ���ɹ�
              {
                 flag=1;
                 printf("��ʼ���ɹ���\n");
              }
            else if(flag)
                printf("�ܱ��ѳ�ʼ��!�����ظ���ʼ��\n");
            else
                printf("��ʼ��ʧ�ܣ�\n");
	       system("pause");
            break;
    case 2:if(flag){
                if(DestroyTable(TAP)){
                    printf("�ɹ��ݻ��ܱ�\n");flag=0;}
                else printf("�ݻ�ʧ�ܣ�\n");
                    }
            else printf("�ܱ�δ��ʼ��!\n");
	       system("pause");
            break;
    case 3:if(flag){
	    		if(ClearTable(TAP))printf("�ɹ�����ܱ�\n");
	    		else printf("�޷�����ܱ��\n");
			}
            else printf("�ܱ�δ��ʼ��!\n");
			system("pause");
            break;
    case 4:if(flag){
				if(TableEmpty(TAP))printf("�ܱ��Ϊ�գ����ӱ�����\n");
				else printf("�ܱ��Ϊ��\n");}
            else printf("�ܱ�δ��ʼ��!\n");
            system("pause");
            break;
    case 5:if(flag){
                int i;
                i=TableLength(TAP);
                printf("��Ϊ%d",i);
                }
            else printf("�ܱ�δ��ʼ��!\n");
            system("pause");
            break;
    case 6:
            if(flag){
                struct DataFiled *q;//��q�����ջ�ȡ�����Ա�
                q=(struct DataFiled*)malloc(sizeof(struct DataFiled));
                if(GetTableElemByName(TAP,q)){
                   void(*visit1)(ElemType *);//�������Ա�
                        printf("��������%s��\n",(*q).name);
                        if(ListTrabverse((*q).head,visit1)==ERROR)
                            printf("���Ա�Ϊ�ձ�\n");
                }}
            else printf("�ܱ�δ��ʼ��!\n");
            system("pause");
            break;
    case 7:if(flag){
                if(newSubList(TAP)==OK)
                    printf("�ɹ������µ��ӱ�\n");}
            else printf("�ܱ�δ��ʼ��!\n");
            system("pause");
            break;
    case 8:
            if(flag){
                if(RewriteSublist(TAP))
                    printf("�ɹ��޸��ӱ�\n");
				else
					printf("���в����ڸñ�\n");}
            else printf("�ܱ�δ��ʼ��!\n");
            system("pause");
            break;
    case 0:system("pause");
            break;
        }
    }
  printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
  return 0;
}

status IntiaList(LinkList &L){//���Ա��ʼ��
	L=(LinkList)malloc(sizeof(LNode));
	if(!L) exit(OVERFLOW);
	L->next=NULL;
	return OK;
}

status DestroyList(LinkList &L){//�ݻ����Ա�
    L->next=NULL;
    free(L);
    return OK;
}

status ClearList(LinkList &L){//������Ա�
    L->next=NULL;
    return OK;
}

status ListEmpty(LinkList L){//���Ա��п�
    if(L->next!=NULL)
        return FALSE;
    else
        return TRUE;
}

int ListLength(LinkList L){//���ر�
    int length=0;
    LinkList p=L->next;
    while(p){
        length++;
    	p=p->next;
    }
    return length;

}
/*-------------------------------------------------------------
��������GetElem
�������ܣ�������Ա�L�е�i��Ԫ�أ�����e����
����������L�����Ա�i:��ȡĿ��Ԫ�ص��±�ֵ��e:���ڽ���Ŀ��Ԫ��
��������ֵ���ɹ�����OK�����ֵԽ�緵��ERROR
--------------------------------------------------------------*/
status GetElem(LinkList L,int i,ElemType *e){
    //LΪ��ͷ���ĵ������ͷָ�룻
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

int LocateElem(LinkList L,ElemType e,status (*compare1)(ElemType , ElemType )){//��ȡԪ��λ��
    int i=0;
    compare1=compare;//����ָ��ָ��compare����
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
        printf("�ñ�Ϊ�ձ�\n");
    return 0;
}

status PriorElem(LinkList L,ElemType cur,ElemType *pre_e){//���ǰ��
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

status NextElem(LinkList L,ElemType cur,ElemType * next_e){//��ú��
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
�������ƣ�ListInsert
�������ܣ������Ա�L�е�i��Ԫ��ǰ����Ԫ��e
����������&L�����Ա�L�ĵ�ַ��i:����Ԫ�ص�λ�ã�e:����Ԫ�ص�ֵ
��������ֵ���������ɹ�������OK�����iֵԽ���򷵻�ERROR
------------------------------------------------------------*/
status ListInsert(LinkList &L,int i,ElemType e){//����Ԫ��
    LinkList p=L,s;
    int j=0;
    while(p&&j<i-1){
        p=p->next;
        j++;//Ѱ�ҵ�i�����
    }
    if(!p||j>i-1)//iС��1���ߴ��ڱ���1;
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
    printf("���Ա�Ϊ�գ�\n");
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
    printf("��������Ҫ��ѯ�ı������:\n");
    scanf("%s",s);
    TableLink p=TA->next;
    for(index=0;p&&strcmp((*p).List.name,s);index++)
        p=p->next;
    if(!TA){
        printf("����ѯ�����в�������Ϊ%s�ı��!\n",s);
        return 0;}
    else
        return index+1;

}

status GetTableElemByName(TableLink TA,struct DataFiled* e){
     int index;
    char s[30];
    printf("��������Ҫ��ѯ�ı������:\n");
    scanf("%s",s);
    TableLink p=TA->next;
    while(p){
    	if(!strcmp((*p).List.name,s))
    		break;
    	else
    	 p=p->next;
	}

    if(!p){
        printf("����ѯ�����в�������Ϊ%s�ı��!\n",s);
        return 0;}
    else{
        *e=(*p).List;
        return OK;
    }
}

status newSubList(TableLink TA){
    char s[30];
    printf("�������½��ӱ�����֣�\n");
    scanf("%s",s);
    int i;
    TableLink TB=TA,T=TA;
    TB=TB->next;//TBΪ����ָ�룬TΪTB��ǰ�����ָ�룬T->next==TB
    while(TB){
        if(!strcmp((*TB).List.name,s)){
            printf("�Ѿ�������Ϊ%s�����Ա�\n",s);
            return ERROR;
        }
        else{
            TB=TB->next;
            T=T->next;}
        }//end of while
        /*ѭ������������������β��T==tail,TB==T->next==NULL;*/
    TB=(TableLink)malloc(sizeof(Table));//�½��ӽڵ㲢Ϊ�䴴���ռ�
    T->next=TB;
    (*TB).List.head=(LinkList)malloc(sizeof(LNode));
 	if(!SubListOperation((*TB).List.head,0,s)){
        free((*TB).List.head);
        free(TB);
        T->next=NULL;
        return ERROR;}
    else{
    strcpy((*TB).List.name,s);//Ϊ������
    TB->next=NULL;//Ϊ��β����ָ����ֵΪNULL����ָֹ������
    return OK;}
}

status RewriteSublist(TableLink TA){
    char s[30];
    printf("��������Ҫ�޸��ӱ�����֣�\n");
    scanf("%s",s);
    int i;
    TableLink TB=TA;//TBΪ����ָ��
    TB=TB->next;//����ָ��ָ��ͷ���
    while(TB){//���ܱ���б���
        if(!strcmp((*TB).List.name,s)){//�Ƚ������Ƿ���ͬ
            if(!SubListOperation((*TB).List.head,1,s))//���ӱ���в�����1����ñ��Ѿ����г�ʼ���������ٴγ�ʼ��
                return ERROR;
            else
            	return OK;
        }
        else    TB=TB->next;
    }//end of while
    return ERROR;
}

status SubListOperation(LinkList newList,int hasInitial,char *s){//�ж����Ա��Ƿ��ʼ��
    LinkList L;
    L=newList;
  int op=1;//op����ѡ��Ĳ�����
  ElemType cur,pre_e,next_e;//��ǰ��ǰ�����������Ԫ��
 while(op){
	system("cls");	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("--------------�����ڶԱ�%s�����в���-----------\n",s);
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
	printf("    ��ѡ����Ĳ���[0~14]:");
	scanf("%d",&op);
    switch(op){
	   case 1://���Ա��ʼ��
            if((!hasInitial)&&IntiaList(L)==OK)
            {  printf("���Ա����ɹ���\n");
                hasInitial=1; //��ʶ��ʼ���ɹ�
            }
            else printf("���Ա���ʧ�ܣ�\n");
		 system("pause");
		 break;
	   case 2://�������Ա�
		 if(hasInitial){
            if(DestroyList(L)){
            hasInitial=0; //δ��ʼ��
            printf("�ɹ��������Ա�\n");
		 }
		 }
		 else
            printf("���Ա����ڣ��޷����٣�\n");
		 system("pause");
		 break;
	   case 3://������Ա�
		 if(hasInitial){
            ClearList(L);
            printf("�ɹ�������Ա�\n");
		 }
		 else
            printf("���Ա����ڣ��޷���գ�\n");
		 system("pause");
		 break;
	   case 4://�п����Ա�
		 if(hasInitial){
            if(ListEmpty(L)) printf("���Ա�Ϊ�գ�\n");
            else  printf("���Ա�ǿգ�\n");
		 }
		 else
            printf("���Ա����ڣ�\n");
		 system("pause");
		 break;
	   case 5://���Ա���
		 if(hasInitial){
            int i;
            i=ListLength(L);
            printf("���Ա���Ϊ%d\n",i);
		 }
		 else
            printf("���Ա����ڣ�\n");
		 system("pause");
		 break;
	   case 6://���ָ��λ��Ԫ��
		 if(hasInitial){
            ElemType e;
            int i;
            printf("�����õڼ���Ԫ�أ�\n");
            scanf("%d",&i);
            if(GetElem(L,i,&e)==OK)
                printf("��%d��Ԫ��Ϊ%d %s\n",i,e.No,e.Name);
            else
                printf("�޷���õ�%d��Ԫ��\n",i);
		 }
		 else
            printf("���Ա����ڣ�\n");
		 system("pause");
		 break;
	   case 7://����ָ��Ԫ��λ��
		 if(hasInitial){
            int i;
            ElemType e;
            printf("������������ҵ�Ԫ�أ�");
            scanf("%d %s",&e.No,e.Name);
            status (*compare)(ElemType a, ElemType b);//���庯��ָ��
            if(!(i=LocateElem(L,e,compare)))
               printf("���Ա��в�����Ԫ��%d %s\n",e.No,e.Name);
            else
                printf("%d %sΪ�����Ա��е�%d��λ��\n",e.No,e.Name,i);
		 }
		 else
            printf("���Ա����ڣ�\n");
		 system("pause");
		 break;
	   case 8://���ƶ�Ԫ��ǰ��
            if(hasInitial){
            printf("�����뵱ǰԪ�أ�\n");
            scanf("%d %s",&cur.No,cur.Name);
            if(PriorElem(L,cur,&pre_e))
                printf("%d %sǰһ��Ԫ��Ϊ%d %s\n",cur.No,cur.Name,pre_e.No,pre_e.Name);
            else
                printf("���Ա��в����ڸ�Ԫ�ػ��߸�Ԫ��û��ǰ��\n");
		 }
		 else
            printf("���Ա����ڣ�\n");
		 system("pause");
		 break;
	   case 9://��ָ��Ԫ�غ��
		 if(hasInitial){
            printf("�����뵱ǰԪ�أ�\n");
            scanf("%d %s",&cur.No,cur.Name);
            if(NextElem(L,cur,&next_e))
                printf("%d %s��һ��Ԫ��Ϊ%d %s\n",cur.No,cur.Name,next_e.No,next_e.Name);
            else
                printf("���Ա��в����ڻ���û�к��\n",cur,cur);
		 }
		 else
            printf("���Ա����ڣ�\n");
		 system("pause");
		 break;
	   case 10://����Ԫ��
		 if(hasInitial){
            ElemType e;
            int i;
            printf("������뵽�ڼ���Ԫ��ǰ:");
            scanf("%d",&i);
            printf("��������������Ԫ�أ�");
            scanf("%d %s",&e.No,e.Name);
            if(ListInsert(L,i,e)==OK)
                printf("����ɹ���\n");
            else
                printf("����ʧ�ܣ�\n");
		 }
		 else
            printf("���Ա����ڣ�\n");
		 system("pause");
		 break;
	   case 11://ɾ��Ԫ��
		 if(hasInitial){
            ElemType e;
            int i;
            printf("����ɾ���ڼ���Ԫ��:");
            scanf("%d",&i);
            if(ListDelete(L,i,&e)==OK)
                printf("ɾ���ɹ���\n");
            else
                printf("ɾ��ʧ�ܣ�\n");
		 }
		 else
            printf("���Ա����ڣ�\n");
		 system("pause");
		 break;
	   case 12://����Ԫ��
		 if(hasInitial){
           void(*visit1)(ElemType*);
            if(ListTrabverse(L,visit1)==ERROR)
                printf("���Ա�Ϊ�ձ�\n");
		 }
		 else
            printf("���Ա����ڣ�\n");
		 system("pause");
		 break;
       case 13://��������
        if(hasInitial){
            if(save(L,s))
                printf("����ɹ���\n");
            else
                printf("����ʧ�ܣ�\n");
        }
        else printf("���Ա����ڣ��޷��������ݣ�\n");
            system("pause");break;
       case 14://��ȡ�ļ�
        if(hasInitial)
            readfile(&L);
        else printf("δ��ʼ�����޷���ȡ��\n");
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
