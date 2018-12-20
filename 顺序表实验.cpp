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
typedef int ElemType; //����Ԫ�����Ͷ���

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct{  //˳���˳��ṹ���Ķ���
	ElemType * elem;
	int length;
	int listsize;
}SqList;

struct LNode{
    char name[30];  //ÿ���������
    SqList lists;
};
typedef struct Table{//�ܱ�Ķ���
    struct LNode *elem;
    int length;
}Table;
/*-----page 19 on textbook ---------*/
status IntiaList(SqList & L);/*��ʼ�����Ա�*/
status DestroyList(SqList & L);/*�ݻ����Ա�*/
status ClearList(SqList &L);/*������Ա�*/
status ListEmpty(SqList L);/*���Ա��п�*/
int ListLength(SqList L);/*���*/
status GetElem(SqList L,int i,ElemType *e);/*��ȡԪ��*/
int LocateElem(SqList L,ElemType e,status (*compare)(ElemType , ElemType ));/*��ȡԪ��λ��*/
status PriorElem(SqList L,ElemType cur,ElemType * pre_e);/*���ǰ��*/
status NextElem(SqList L,ElemType cur,ElemType *next_e);/*��ú��*/
status ListInsert(SqList & L,int i,ElemType e);/*����Ԫ��*/
status ListDelete(SqList & L,int i,ElemType *e);/*ɾ��Ԫ��*/
status ListTrabverse(SqList L, void (*visit)(void const *e));/*����Ԫ��*/
void visit(void const *e);/*��ӡԪ��*/
status compare(ElemType a, ElemType b);/*�Ƚ�Ԫ�ع�ϵ*/
status save(SqList L,char *s);/*������*/
status readfile(SqList *L);/*�������Ա�*/
/*--------------------------------------------*/
/*---------------�ܱ��������----------------*/
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
	printf("          8. DeleteSubList\n");
	printf("          9.RewriteSubList\n");
	printf("          10.PrintAllTheTables\n");
	printf("    	  0. Exit\n");
	printf("-------------------------------------------------\n");
	printf("    ��ѡ����Ĳ���[0~10]:");
		scanf("%d",&op);
	switch(op){
    case 1:if(!flag&&initialTable(TA))//δ��ʼ�����ҳ�ʼ���ɹ�
                flag=1;
            else if(flag)
                printf("�ܱ��ѳ�ʼ��!�����ظ���ʼ��\n");
            else
                printf("��ʼ��ʧ�ܣ�\n");
	       system("pause");
            break;
    case 2:if(flag){
                if(DestroyTable(TA)){
                    printf("�ɹ��ݻ��ܱ�\n");flag=0;}
                else printf("�ݻ�ʧ�ܣ�\n");
                    }
            else printf("�ܱ�δ��ʼ��!\n");
	       system("pause");
            break;
    case 3:if(flag){
	    		if(ClearTable(TA))printf("�ɹ�����ܱ�\n");
	    		else printf("�޷�����ܱ��\n");
			}
            else printf("�ܱ�δ��ʼ��!\n");
			system("pause");
            break;
    case 4:if(flag){
				if(TableEmpty(TA))printf("�ܱ��Ϊ�գ����ӱ�����\n");
				else printf("�ܱ��Ϊ��\n");}
            else printf("�ܱ�δ��ʼ��!\n");
            system("pause");
            break;
    case 5:if(flag){
                int i;
                i=TableLength(TA);
                printf("��Ϊ%d",i);
                }
            else printf("�ܱ�δ��ʼ��!\n");
            system("pause");
            break;
    case 6:
            if(flag){
                struct LNode *q;//��q�����ջ�ȡ�����Ա�
                q=(struct LNode*)malloc(sizeof(struct LNode));
                if(GetTableElemByName(TA,q)){
                   void(*visit1)(void const *);//�������Ա�
                        printf("��������%s��\n",(*q).name);
                        if(ListTrabverse((*q).lists,visit1)==ERROR)
                            printf("���Ա�Ϊ�ձ�\n");
                }}
            else printf("�ܱ�δ��ʼ��!\n");
            system("pause");
            break;
    case 7:if(flag){
                if(newSubList(TA)==OK)
                    printf("�ɹ������µ��ӱ�\n");}
            else printf("�ܱ�δ��ʼ��!\n");
            system("pause");
            break;
    case 8:
            if(flag){
                struct LNode *r;
                r=(struct LNode*)malloc(sizeof(struct LNode));
                if(DeleteSubList(TA,r))
                    printf("�ɹ�ɾ���ӱ�\n");}
            else printf("�ܱ�δ��ʼ��!\n");
            system("pause");
            break;
    case 9:if(flag){
                if(RewriteSublist(TA))
                    printf("�ɹ��޸��ӱ�\n");}
            else printf("�ܱ�δ��ʼ��!\n");
            system("pause");
            break;
    case 10:if(flag){
                int index;
                void(*visit1)(void const *);
                for(index=0;index<TA.length;index++){
                        printf("---��%s��---\n",TA.elem[index].name);
                        if(ListTrabverse(TA.elem[index].lists,visit1)==ERROR)
                            printf("���Ա�Ϊ�ձ�\n");}
                            }

    case 0:system("pause");
            break;
        }
    }
  printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
  return 0;
}//end of main()
/*--------page 23 on textbook --------------------*/
status IntiaList(SqList & L){//���Ա��ʼ��
	L.elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    if(!L.elem) exit(OVERFLOW);//
	L.length=0;
    L.listsize=LIST_INIT_SIZE;
	return OK;
}

status DestroyList(SqList & L){//�ݻ����Ա�
    ClearList(L);
    free(L.elem);
  //  *=NULL;
    return OK;
}

status ClearList(SqList &L){//������Ա�
    L.length=0;
    return OK;
}

status ListEmpty(SqList L){//���Ա��п�
    if(L.length==0)
        return TRUE;
    else
        return FALSE;
}

int ListLength(SqList L){//���ر�
    return L.length;
}
/*-------------------------------------------------------------
��������GetElem
�������ܣ�������Ա�L�е�i��Ԫ�أ�����e����
����������L�����Ա�i:��ȡĿ��Ԫ�ص��±�ֵ��e:���ڽ���Ŀ��Ԫ��
��������ֵ���ɹ�����OK�����ֵԽ�緵��ERROR
--------------------------------------------------------------*/
status GetElem(SqList L,int i,ElemType *e){
    if(i<1||i>L.length) return ERROR;
    *e=L.elem[i-1];
    return OK;
}

int LocateElem(SqList L,ElemType e,status (*compare1)(ElemType , ElemType )){//��ȡԪ��λ��
    int i;
    compare1=compare;//����ָ��ָ��compare����
    for(i=0;i<L.length;i++)
        if(compare1(L.elem[i],e))
            return i+1;
    return 0;
}

status PriorElem(SqList L,ElemType cur,ElemType *pre_e){//���ǰ��
    int i=0;
    for(i=0;i<L.length;i++)
        if(L.elem[i]==cur)
            break;
    if(i==0||i==L.length) return ERROR;
     *pre_e=L.elem[i-1];
     return OK;
}

status NextElem(SqList L,ElemType cur,ElemType * next_e){//��ú��
    int i=0;
    for(i=0;i<L.length;i++)
        if(L.elem[i]==cur)
            break;
    if(i==L.length||i==L.length-1) return ERROR;
    *next_e=L.elem[i+1];
    return OK;
}
/*------------------------------------------------------------
�������ƣ�ListInsert
�������ܣ������Ա�L�е�i��Ԫ��ǰ����Ԫ��e
����������&L�����Ա�L�ĵ�ַ��i:����Ԫ�ص�λ�ã�e:����Ԫ�ص�ֵ
��������ֵ���������ɹ�������OK�����iֵԽ���򷵻�ERROR
------------------------------------------------------------*/
status ListInsert(SqList & L,int i,ElemType e){//����Ԫ��
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
//������ļ��������ȡ����Ԫ�ػָ�˳������ڲ�ͬ������ṹ����ͨ����//ȡ������Ԫ�ػָ��ڴ��е�����ṹ��
    fclose(fp);
    return OK;
}

status initialTable(Table &TA){
    TA.elem=(struct LNode*)malloc(100*sizeof(struct LNode));
    if(TA.elem){
        TA.length=0;
        printf("�ɹ������ܱ�\n");
        return OK;}
    else{
        printf("�ܱ���ʧ�ܣ�\n");
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
    printf("��������Ҫ��ѯ�ı������:\n");
    scanf("%s",s);
    for(index=0;index<TA.length;index++){
        if(!strcmp(TA.elem[index].name,s)){
                printf("��λ���ܱ��%d����\n",index+1);
                return index+1;
        }
    }
    printf("����ѯ�����в�������Ϊ%s�ı��!\n",s);
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
    printf("�������½��ӱ�����֣�\n");
    scanf("%s",TA.elem[TA.length].name);
    int i;
    for(i=0;i<TA.length;i++){
        if(!strcmp(TA.elem[TA.length].name,TA.elem[i].name)){
            printf("�Ѿ�������Ϊ%s�����Ա�\n",TA.elem[TA.length].name);
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


status SubListOperation(SqList *newList,int hasInitial,char *s){//�ж����Ա��Ƿ��ʼ��
    SqList L,LA;
    L=*newList;

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
            ElemType e=0;
            int i;
            printf("�����õڼ���Ԫ�أ�\n");
            scanf("%d",&i);
            if(GetElem(L,i,&e)==OK)
                printf("��%d��Ԫ��Ϊ%d\n",i,e);
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
            scanf("%d",&e);
            status (*compare)(ElemType a, ElemType b);//���庯��ָ��
            if(!(i=LocateElem(L,e,compare)))
               printf("���Ա��в�����Ԫ��%d\n",e);
            else
                printf("%dΪ�����Ա��е�%d��λ��\n",e,i);
		 }
		 else
            printf("���Ա����ڣ�\n");
		 system("pause");
		 break;
	   case 8://���ƶ�Ԫ��ǰ��
            if(hasInitial){
            printf("�����뵱ǰԪ�أ�\n");
            scanf("%d",&cur);
            if(PriorElem(L,cur,&pre_e))
                printf("%dǰһ��Ԫ��Ϊ%d\n",cur,pre_e);
            else
                printf("���Ա��в�����%d����%dû��ǰ��\n",cur,cur);
		 }
		 else
            printf("���Ա����ڣ�\n");
		 system("pause");
		 break;
	   case 9://��ָ��Ԫ�غ��
		 if(hasInitial){
            printf("�����뵱ǰԪ�أ�\n");
            scanf("%d",&cur);
            if(NextElem(L,cur,&next_e))
                printf("%d��һ��Ԫ��Ϊ%d\n",cur,next_e);
            else
                printf("���Ա��в�����%d����%dû�к��\n",cur,cur);
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
            scanf("%d",&e);
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
            ElemType e=0;
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
           void(*visit1)(void const *e);
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
   	*newList=L;
   	return OK;}
	else
		return ERROR;

}
