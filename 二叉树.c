#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define MAXQSIZE 5
typedef int Status;      //״̬�����Ͷ���
typedef struct TElemType //����Ԫ�����Ͷ���
{
    int Number;
    char Name[30];
} TElemType;

typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
typedef BiTree QElemType;
typedef struct
{
    BiTNode *elem;
    int length;
    int listsize;
} SqList;
typedef struct
{
    QElemType *base;
    int front;
    int rear;
} SqQueue;

Status InitBiTree(BiTree *root, BiTree *T);
Status DestroyBiTree(BiTree *T);
Status CreateBiTree(BiTree *T);
Status BiTreeEmpty(BiTree T);
int BiTreeDepth(BiTree T);
BiTNode Root(BiTree T);
TElemType Value(BiTree T, int Number);
BiTree Point(BiTree T, TElemType s);
Status Assign(BiTree T, TElemType *e, char value[30]);
TElemType Parent(BiTree T, TElemType e);
TElemType LeftChild(BiTree T, TElemType e);
TElemType RightChild(BiTree T, TElemType e);
TElemType LeftSibling(BiTree T, TElemType e);
TElemType RightSibling(BiTree T, TElemType e);
Status InsertChild(BiTree *p, int LR, BiTree *c);
Status DeleteChild(BiTree *p, int LR);
void PreOrderTraverse(BiTree T, Status (*Visit)(TElemType));
void InOrderTraverse(BiTree T, Status (*Visit)(TElemType));
void PostOrderTraverse(BiTree T, Status (*Visit)(TElemType));
void LevelOrderTraverse(BiTree T, Status (*Visit)(TElemType));
Status InitQueue(SqQueue *Q);
Status DestroyQueue(SqQueue *Q);
Status QueueEmpty(SqQueue Q);
Status EnQueue(SqQueue *Q, QElemType e);
Status DeQueue(SqQueue *Q, QElemType *e);
Status Visit(TElemType a);
Status save(BiTree T);
Status readfile(BiTree *T);
BiTree OperationBiTree(int flag, BiTree *);
Status IntiaList(SqList *L);
Status ChangeBiTree(SqList *L, int index, BiTree *e);

Status InitBiTree(BiTree *root, BiTree *T)
{
    (*root) = (BiTNode *)malloc(sizeof(BiTNode));
    if (!(*root))
        exit(OVERFLOW);
    (*root)->rchild = NULL;
    (*root)->lchild = NULL;
    (*root)->data.Number = 0;
    strcpy((*root)->data.Name, "#");
    *T = NULL;
    return OK;
} //��ʼ��

Status DestroyBiTree(BiTree *root)
{
    if (*root)
    {
        free(*root);
        *root = NULL;
        return OK;
    }
    else
        return ERROR;
} //DestroyBiTree

Status CreateBiTree(BiTree *T)
{
    TElemType ch;
    printf("Number:");
    scanf("%d", &ch.Number);
    printf("Name:");
    scanf("%s", ch.Name);
    int a = ch.Number;
    if (a == 0) /* �� */
        *T = NULL;
    else
    {
        *T = (BiTree)malloc(sizeof(BiTNode));
        if (!*T)
            exit(OVERFLOW);
        (*T)->data = ch;             /* ���ɸ���� */
        CreateBiTree(&(*T)->lchild); /* ���������� */
        CreateBiTree(&(*T)->rchild); /* ���������� */
    }
    return OK;
}

Status ClearBiTree(BiTree *T)
{
    if (*T)
    {
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
        (*T) = NULL;
    }
    return OK;
} //ClearBiTree

Status BiTreeEmpty(BiTree T)
{
    if (T == NULL)
        return TRUE;
    else
        return FALSE;
}

int BiTreeDepth(BiTree T)
{
    int max;
    int l, r;
    if (T)
    {
        l = BiTreeDepth(T->lchild);
        r = BiTreeDepth(T->rchild);
        max = l > r ? l : r;
        return max + 1;
    }
    else
        return 0;
}

BiTNode Root(BiTree T)
{
    return *T;
}

TElemType Value(BiTree T, int Number)
{
    TElemType b = {0, '#'};
    if (!T)
        return b;
    if (T->data.Number == Number)
        return T->data;
    else
    {
        TElemType l, r;
        l = Value(T->lchild, Number);
        r = Value(T->rchild, Number);
        return l.Number ? l : r;
    }
}
BiTree Point(BiTree T, TElemType s)
{
    if (!T)
        return NULL;
    if (T->data.Number == s.Number)
        return T;
    else
    {
        BiTree l, r;
        l = Point(T->lchild, s);
        r = Point(T->rchild, s);
        return l ? l : (r ? r : NULL);
    }
}
Status Assign(BiTree T, TElemType *e, char value[30])
{
    BiTree a;
    if (T)
    {
        a = Point(T, *e);
        if(a!=NULL){
            strcpy(a->data.Name, value);
            return OK;}
        else
            return ERROR;
    }
    return ERROR;
}
TElemType Parent(BiTree T, TElemType e)
{
    SqQueue q;
    QElemType a;
    TElemType b = {0, '#'};
    if (T) /* �ǿ��� */
    {
        if (T->data.Number == e.Number)
            return b;
        InitQueue(&q);         /* ��ʼ������ */
        EnQueue(&q, T);        /* ������� */
        while (!QueueEmpty(q)) /* �Ӳ��� */
        {
            DeQueue(&q, &a); /* ����,����Ԫ�ظ���a */
            if ((a->lchild && a->lchild->data.Number == e.Number) || (a->rchild && a->rchild->data.Number == e.Number))
                /* �ҵ�e(��������Һ���) */
                return a->data; /* ����e��˫�׵�ֵ*/
            else                /* û�ҵ�e,����������Һ���ָ��(����ǿ�) */
            {
                if (a->lchild)
                    EnQueue(&q, a->lchild);
                if (a->rchild)
                    EnQueue(&q, a->rchild);
            }
        }
    }
    strcpy(b.Name,"##");
    return b;
}

TElemType LeftChild(BiTree T, TElemType e)
{
    BiTree a;
    TElemType b = {0, '#'};
    if (T)
    {
        a = Point(T, e);           /* a�ǽ��e��ָ�� */
        if (a && a->lchild)         /* T�д��ڽ��e��e�������� */
            return a->lchild->data; /* ����e�����ӵ�ֵ */
        else if(a==NULL)
            return b;
        else
        {
            strcpy(b.Name,"##");
            return b;
        }
    }
}

TElemType RightChild(BiTree T, TElemType e)
{
    TElemType b = {0, '#'};
    BiTree a;
    if (T)
    {
        a = Point(T, e);
        if (a && a->rchild)
            return a->rchild->data;
        else if(a==NULL)
            return b;
        else{
            strcpy(b.Name,"##");
            return b;
        }
    }

}

TElemType LeftSibling(BiTree T, TElemType e)
{
    /* ��ʼ����: ������T����,e��T��ĳ����� */
    /* �������: ����e�����ֵܡ���e��T�����ӻ������ֵ�,�򷵻أ��գ� */
    TElemType a, b = {0, '#'};
    BiTree p; //����ָ��
    if (T)    /* �ǿ��� */
    {
        a = Parent(T, e); /* aΪe��˫�� */
        if (a.Number != 0)
        {
            p = Point(T, a);                                                  /* pΪָ����a��ָ�� */
            if (p->lchild && p->rchild && p->rchild->data.Number == e.Number) /* p�������Һ������Һ�����e */
                return p->lchild->data;                                       /* ����p������(e�����ֵ�) */
        }
        else
            return b;
    }
    strcpy(b.Name,"##");
    return b;
}

TElemType RightSibling(BiTree T, TElemType e)
{
    TElemType a, b = {0, '#'};
    BiTree p;
    if (T)
    {
        a = Parent(T, e);
        if (a.Number != 0)
        {
            p = Point(T, a);
            if (p->lchild && p->rchild && p->lchild->data.Number == e.Number)
                return p->rchild->data;
        }
        else
            return b;
    }
    strcpy(b.Name,"##");
    return b;
}

Status InsertChild(BiTree *p, int LR, BiTree *c) /* �β�T���� */
{
    /* ��ʼ����: ������T����,pָ��T��ĳ�����,LRΪ0��1,�ǿն�����c��T */
    /*           ���ཻ��������Ϊ�� */
    /* �������: ����LRΪ0��1,����cΪT��p��ָ���������������p��ָ���� */
    /*           ԭ��������������Ϊc�������� */
    if (p)
    {
        if (LR == 0)
        {
            (*c)->rchild = (*p)->lchild;
            (*p)->lchild = *c;
        }
        else
        {
            (*c)->rchild = (*p)->rchild;
            (*p)->rchild = *c;
        }
        return OK;
    }
    return ERROR;
}

Status DeleteChild(BiTree *p, int LR)
{
    if (*p)
    {
        if (LR == 0) /* ɾ�������� */
            {if((*p)->lchild==NULL)
                return ERROR;
            else
            ClearBiTree(&(*p)->lchild);}
        else /* ɾ�������� */
            {if((*p)->rchild==NULL)
                return ERROR;
            else
            ClearBiTree(&(*p)->rchild);}
        return OK;
    }
    return ERROR;
}

void PreOrderTraverse(BiTree T, Status (*Visit)(TElemType))
{

    if (T)
    {
        Visit(T->data);
        PreOrderTraverse(T->lchild, Visit);
        PreOrderTraverse(T->rchild, Visit);
    }
}

void InOrderTraverse(BiTree T, Status (*Visit)(TElemType))
{
    if (T)
    {
        InOrderTraverse(T->lchild, Visit);
        Visit(T->data);
        InOrderTraverse(T->rchild, Visit);
    }
}

void PostOrderTraverse(BiTree T, Status (*Visit)(TElemType))
{
    if (T) /* T���� */
    {
        PostOrderTraverse(T->lchild, Visit);
        PostOrderTraverse(T->rchild, Visit);
        Visit(T->data);
    }
}

void LevelOrderTraverse(BiTree T, Status (*Visit)(TElemType))
{

    SqQueue q;
    QElemType a;
    if (T)
    {
        InitQueue(&q);
        EnQueue(&q, T);
        while (!QueueEmpty(q))
        {
            DeQueue(&q, &a);
            Visit(a->data);
            if (a->lchild != NULL)
                EnQueue(&q, a->lchild);
            if (a->rchild != NULL)
                EnQueue(&q, a->rchild);
        }
        printf("\n");
    }
}

Status InitQueue(SqQueue *Q)
{
    /* ����һ���ն���Q */
    (*Q).base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
    if (!(*Q).base) /* �洢����ʧ�� */
        exit(OVERFLOW);
    (*Q).front = (*Q).rear = 0;
    return OK;
}

Status DestroyQueue(SqQueue *Q)
{
    /* ���ٶ���Q,Q���ٴ��� */
    if ((*Q).base)
        free((*Q).base);
    (*Q).base = NULL;
    (*Q).front = (*Q).rear = 0;
    return OK;
}

Status QueueEmpty(SqQueue Q)
{
    /* ������QΪ�ն���,�򷵻�TRUE,���򷵻�FALSE */
    if (Q.front == Q.rear) /* ���пյı�־ */
        return TRUE;
    else
        return FALSE;
}

Status EnQueue(SqQueue *Q, QElemType e)
{
    /* ����Ԫ��eΪQ���µĶ�βԪ�� */
    if ((*Q).rear >= MAXQSIZE)
    {
        /* ������������1���洢��Ԫ */
        (*Q).base = (QElemType *)realloc((*Q).base, ((*Q).rear + 1) * sizeof(QElemType));
        if (!(*Q).base) /* ���ӵ�Ԫʧ�� */
            return ERROR;
    }
    *((*Q).base + (*Q).rear) = e;
    (*Q).rear++;
    return OK;
}

Status DeQueue(SqQueue *Q, QElemType *e)
{
    /* �����в���,��ɾ��Q�Ķ�ͷԪ��,��e������ֵ,������OK,���򷵻�ERROR */
    if ((*Q).front == (*Q).rear) /* ���п� */
        return ERROR;
    *e = (*Q).base[(*Q).front];
    (*Q).front = (*Q).front + 1;
    return OK;
}
Status Visit(TElemType a)
{
    printf("%d %s\n", a.Number, a.Name);
    return OK;
}

Status save(BiTree T)
{
    FILE *fp;
    char s[30];
    printf("�������ļ�����\n");
    scanf("%s", s);
    getchar();
    system("pause");
    if ((fp = fopen(s, "ab+")) == NULL)
    {
        printf("File open error\n ");
        return ERROR;
    }
    SqQueue q;
    QElemType a;
    if (T)
    {
        InitQueue(&q);
        EnQueue(&q, T);
        while (!QueueEmpty(q))
        {
            DeQueue(&q, &a);
            fwrite(a, sizeof(BiTNode), 1, fp);

            if (a->lchild != NULL)
                EnQueue(&q, a->lchild);
            if (a->rchild != NULL)
                EnQueue(&q, a->rchild);
        }
        fclose(fp);
        return OK;
    }
    else
        return ERROR;
}

Status readfile(BiTree *T)
{
    FILE *fp;
    char filename[30];
    printf("input file name: ");
    scanf("%s", filename);
    getchar();
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        printf("File open error\n ");
        return ERROR;
    }
    SqQueue q;
    QElemType a;
    int choice = 1;
    if (!BiTreeEmpty(*T))
    {
        printf("�������Ѵ��ڣ�ȷ��������ȡ�ļ����˲���������ԭ�ж�������(1/0)\n");
        scanf("%d", &choice);
        getchar();
    }
    if (choice)
    {
        InitQueue(&q);
        *T = (BiTree)malloc(sizeof(BiTNode));
        fread(*T, sizeof(BiTNode), 1, fp);
        EnQueue(&q, *T);
        while (!QueueEmpty(q))
        {
            DeQueue(&q, &a);
            if (a->lchild != NULL)
            {
                a->lchild = (BiTree)malloc(sizeof(BiTNode));
                fread(a->lchild, sizeof(BiTNode), 1, fp);
                EnQueue(&q, a->lchild);
            }
            if (a->rchild != NULL)
            {
                a->rchild = (BiTree)malloc(sizeof(BiTNode));
                fread(a->rchild, sizeof(BiTNode), 1, fp);
                EnQueue(&q, a->rchild);
            }
        }
        fclose(fp);
        return OK;
    }
    else
        return ERROR;
}
BiTree OperationBiTree(int flag, BiTree *root1)
{
    int op = 1;
    BiTNode Tree, *T = &Tree;
    BiTree root;
    if (flag)
    {
        root = *root1;
        T = root->lchild;
    }
    while (op)
    {
        system("cls");
        printf("\n\n");
        printf("         Menu for BiTree On Sequence Structure \n\n");
        printf("    	  1. InitBiTree        11. LeftChild    \n");
        printf("    	  2. DestroyBiTree     12. RightChild    \n");
        printf("    	  3. CreateBiTree      13. LeftSibling    \n");
        printf("    	  4. ClearBiTree       14. RightSibling          \n");
        printf("    	  5. BiTreeEmpty       15. InsertChild        \n");
        printf("    	  6. BiTreeDepth       16. DeleteChild    \n");
        printf("    	  7. Root              17. PreOrderTraverse\n");
        printf("    	  8. Value             18. InOrderTraverse  \n");
        printf("    	  9. Assign            19. PostOrderTraverse \n");
        printf("    	 10. Parent            20. LevelOrderTraverse\n");
        printf("         21.save               22.readfile           \n");
        printf("    	                        0. Exit\n \n");
        printf("-------------------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~23]:");
        scanf("%d", &op);
        if (flag == 0 && op != 1 && op != 0)
        {
            printf("������δ��ʼ�����޷�������\n");
            system("pause");
            continue;
        }
        switch (op)
        {
        case 1:
            if (flag == 0)
            {
                if (InitBiTree(&root, &T))
                    printf("�������ѳɹ���ʼ����\n");
                flag = 1;
            }
            else
                printf("�������ѳ�ʼ���������ظ�������\n");
            system("pause");
            break;
        case 2:
            if (DestroyBiTree(&root))
            {
                printf("�������ѳɹ����٣�\n");
                flag = 0;
            }
            else
                printf("����ʧ�ܣ�\n");
            system("pause");
            break;
        case 3:
            printf("-----CreateBiTree----\n");
            if (CreateBiTree(&T))
            {
                root->lchild = T;
                printf("�ɹ�������������\n");
            }

            else
                printf("����ʧ�ܣ�\n");
            system("pause");
            break;
        case 4:
            printf("----ClearBiTree----\n");
            if (ClearBiTree(&T))
                printf("�ɹ���ն�������\n");
            else
                printf("�޷���գ�\n");
            system("pause");
            break;
        case 5:
            if (!BiTreeEmpty(T))
                printf("�����ǿգ�\n");
            else
                printf("�����Ϊ�գ�\n");
            system("pause");
            break;
        case 6:
            printf("-----BiTreeDepth----\n");
            {
                int depth;
                depth = BiTreeDepth(T);
                printf("�������Ϊ%d\n", depth);
                system("pause");
            }
            break;
        case 7:
            printf("----Root----\n");
            {

                if (T != NULL)
                {
                    BiTNode R = Root(T);
                    printf("%d %s\n", R.data.Number, R.data.Name);
                }
                else
                    printf("��Ϊ������\n");
                system("pause");
            }
            break;
        case 8:
            printf("----Value----\n");
            printf("�������ѯ���Ԫ�صĹؼ���\n");
            int num = 0;
            TElemType x;
            printf("Number:");
            scanf("%d", &num);
            x = Value(T, num);
            if (x.Number)
                printf("�ýڵ��ֵΪ%s\n", x.Name);
            else
                printf("�ýڵ㲻���ڣ�\n");
            system("pause");
            break;
        case 9:if(T==NULL)
                    printf("��Ϊ�գ�\n");
            else{
            printf("----Assign----\n");
            printf("��������Ҫ��ֵ���Ĺؼ��֣�\n");
            TElemType e;
            scanf("%d", &e.Number);
            char value[30];
            printf("�������޸ĺ��ֵvalue:\n");
            scanf("%s", value);
            if(Assign(T, &e, value))
                printf("��ֵ�ɹ���\n");
            else
                    printf("�����ڸý�㣡\n");}
            system("pause");
            break;
        case 10:
            printf("��������Ҫ���ҵĽ�㣡\n");
            TElemType a, b;
            printf("Number:");
            scanf("%d", &a.Number);
            printf("Name:");
            scanf("%s", a.Name);
            b = Parent(T, a);
            if (b.Number != 0)
                printf("%d %s�ĸ��ڵ�Ϊ%d %s\n", a.Number, a.Name, b.Number, b.Name);
            else if (!strcmp(b.Name,"#"))
                printf("%d %sΪ���ڵ㣬�޸��ڵ㣡\n", a.Number, a.Name);
            else
                printf("�����ڸýڵ㣡\n");
            system("pause");
            break;
        case 11:
            if(T==NULL)
                printf("��Ϊ�գ�\n");
            else{
                printf("��������Ҫ���ҵĽ�㣡\n");
                printf("Number:");
                scanf("%d", &a.Number);
                printf("Name:");
                scanf("%s", a.Name);
                b = LeftChild(T, a);
                if (b.Number != 0)
                    printf("%d %s������Ϊ%d %s\n", a.Number, a.Name, b.Number, b.Name);
                else if (!strcmp(b.Name,"#"))
                    printf("�����ڸýڵ㣡\n");
                else
                    printf("�ýڵ�û�����ӣ�\n");
            }
            system("pause");
            break;
        case 12:
            if(T==NULL)
                printf("��Ϊ�գ�\n");
            else{
                printf("��������Ҫ���ҵĽ�㣡\n");
                printf("Number:");
                scanf("%d", &a.Number);
                printf("Name:");
                scanf("%s", a.Name);
                b = RightChild(T, a);
                if (b.Number != 0)
                    printf("%d %s���Һ���Ϊ%d %s\n", a.Number, a.Name, b.Number, b.Name);
                else if(!strcmp(b.Name,"#"))
                    printf("�����ڸýڵ㣡\n");
                else
                    printf("�ýڵ�û���Һ��ӣ�\n");}
            system("pause");
            break;
        case 13:
        {
            TElemType a, b;
            printf("��������Ҫ���ҵĽ�㣡\n");
            printf("Number:");
            scanf("%d", &a.Number);
            printf("Name:");
            scanf("%s", a.Name);
            b = LeftSibling(T, a);
            if (b.Number != 0)
                printf("%d %s�����ֵ�Ϊ%d %s\n", a.Number, a.Name, b.Number, b.Name);
            else if(!strcmp(b.Name,"#"))
                printf("�����ڸýڵ㣡\n");
            else
                printf("�ýڵ�û�����ֵܣ�\n");
        }
            system("pause");
            break;
        case 14:
        {
            TElemType a, b;
            printf("��������Ҫ���ҵĽ�㣡\n");
            printf("Number:");
            scanf("%d", &a.Number);
            printf("Name:");
            scanf("%s", a.Name);
            b = RightSibling(T, a);
            if (b.Number != 0)
                printf("%d %s�����ֵ�Ϊ%d %s\n", a.Number, a.Name, b.Number, b.Name);
            else if(!strcmp(b.Name,"#"))
                printf("�����ڸýڵ㣡\n");
            else
                printf("�ýڵ�û�����ֵܣ�\n");
        }
            system("pause");
            break;
        case 15:
        {
            int LR;
            BiTNode subTree, *psubTree = &subTree; //subTreeΪ���������
            BiTree subRoot;
            InitBiTree(&subRoot, &psubTree);
            CreateBiTree(&psubTree);
            printf("������Ŀ��ڵ��ֵ��\n");
            TElemType q;
            printf("Number:");
            scanf("%d", &q.Number);
            printf("Name:");
            scanf("%s", q.Name);
            BiTree p = Point(T, q); //pΪָ��q��ָ�룻
            printf("�����������Ϊ�ýڵ��������������������0/1����\n");
            scanf("%d", &LR);
            if(p!=NULL){
                if (InsertChild(&p, LR, &psubTree))
                    printf("����ɹ���\n");
                else
                    printf("ɾ��ʧ��!\n");
                }
            else
                printf("����ʧ�ܣ�\n");
        }
            system("pause");
            break;
        case 16:
        {
            int LR;
            printf("������Ŀ��ڵ��ֵ!\n");
            TElemType a;
            printf("Number:");
            scanf("%d", &a.Number);
            printf("Name:");
            scanf("%s", a.Name);
            printf("ɾ��������������������(0/1)?\n");
            scanf("%d", &LR);
            BiTree b;
            b = Point(T, a); //bΪָ��a��ָ��
            if(b!=NULL){
                if (DeleteChild(&b, LR))
                    printf("ɾ���ɹ���\n");
                else
                    printf("ɾ��ʧ��!\n");
                    }
            else
                printf("ɾ��ʧ��!\n");
        }
            system("pause");
            break;
        case 17:
            PreOrderTraverse(T, *Visit);
            system("pause");
            break;
        case 18:
            InOrderTraverse(T, *Visit);
            system("pause");
            break;
        case 19:
            PostOrderTraverse(T, *Visit);
            system("pause");
            break;
        case 20:
            LevelOrderTraverse(T, *Visit);
            system("pause");
            break;
        case 21:
            if (save(T))
                printf("����ɹ���\n");
            else
                printf("����ʧ�ܣ�\n");
            system("pause");
            break;
        case 22:
            if (readfile(&T))
            {
                printf("��ȡ�ɹ���\n");
                root->lchild = T;
            }
            else
                printf("��ȡʧ�ܣ�\n");
            system("pause");
            break;
        case 0:
            printf("��ӭʹ�ñ�ϵͳ���ټ�\n");
            system("pause");
            break;
        default:
            system("pause");
            break;
        }
    }
    if (flag == 1)
    {
        root->lchild = T;
        return root;
    }
    else
        return NULL;

    return root;
}
Status IntiaList(SqList *L) //���Ա��ʼ��
{
    (*L).elem = (BiTree)malloc(LIST_INIT_SIZE * sizeof(BiTNode));
    if (!(*L).elem)
        exit(OVERFLOW); //
    (*L).length = 0;
    (*L).listsize = LIST_INIT_SIZE;
    return OK;
}
Status ChangeBiTree(SqList *L, int index, BiTree *e)
{
    if ((*L).length >= (*L).listsize)
    {
        BiTree newbase;
        newbase = (BiTree)realloc((*L).elem, ((*L).listsize + LISTINCREMENT) * sizeof(BiTNode));
        if (!newbase)
            exit(OVERFLOW);
        L->elem = newbase;
        (*L).listsize += LISTINCREMENT;
    }
    *e = &(*L).elem[index - 1];
    return OK;
}

int main(void)
{
    SqList L;
    IntiaList(&L);
    int op = 1;
    while (op)
    {
        system("cls");
        printf("\n-------------��ӭʹ�ö���������ϵͳ-------------\n");
        printf("��ѡ��Եڼ��������в�����1-%d\n", L.length + 1);
        printf("����0�˳���ϵͳ��\n");
        scanf("%d", &op);
        if (1 <= op && op <= L.length + 1)
        {
            int flag = 0;
            BiTree root;
            ChangeBiTree(&L, op, &root);
            system("pause");
            if (root->data.Number == 0 && !strcmp(root->data.Name, "#"))
                flag = 1;
            else
                flag = 0;
            BiTree root1 = OperationBiTree(flag, &root);
            *root = *root1;
            system("pause");
            if (!flag && op == L.length + 1)
                L.length++;
        }
    }
}
