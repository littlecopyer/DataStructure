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
typedef int Status;      //状态的类型定义
typedef struct TElemType //数据元素类型定义
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
} //初始化

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
    if (a == 0) /* 空 */
        *T = NULL;
    else
    {
        *T = (BiTree)malloc(sizeof(BiTNode));
        if (!*T)
            exit(OVERFLOW);
        (*T)->data = ch;             /* 生成根结点 */
        CreateBiTree(&(*T)->lchild); /* 构造左子树 */
        CreateBiTree(&(*T)->rchild); /* 构造右子树 */
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
    if (T) /* 非空树 */
    {
        if (T->data.Number == e.Number)
            return b;
        InitQueue(&q);         /* 初始化队列 */
        EnQueue(&q, T);        /* 树根入队 */
        while (!QueueEmpty(q)) /* 队不空 */
        {
            DeQueue(&q, &a); /* 出队,队列元素赋给a */
            if ((a->lchild && a->lchild->data.Number == e.Number) || (a->rchild && a->rchild->data.Number == e.Number))
                /* 找到e(是其左或右孩子) */
                return a->data; /* 返回e的双亲的值*/
            else                /* 没找到e,则入队其左右孩子指针(如果非空) */
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
        a = Point(T, e);           /* a是结点e的指针 */
        if (a && a->lchild)         /* T中存在结点e且e存在左孩子 */
            return a->lchild->data; /* 返回e的左孩子的值 */
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
    /* 初始条件: 二叉树T存在,e是T中某个结点 */
    /* 操作结果: 返回e的左兄弟。若e是T的左孩子或无左兄弟,则返回＂空＂ */
    TElemType a, b = {0, '#'};
    BiTree p; //遍历指针
    if (T)    /* 非空树 */
    {
        a = Parent(T, e); /* a为e的双亲 */
        if (a.Number != 0)
        {
            p = Point(T, a);                                                  /* p为指向结点a的指针 */
            if (p->lchild && p->rchild && p->rchild->data.Number == e.Number) /* p存在左右孩子且右孩子是e */
                return p->lchild->data;                                       /* 返回p的左孩子(e的左兄弟) */
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

Status InsertChild(BiTree *p, int LR, BiTree *c) /* 形参T无用 */
{
    /* 初始条件: 二叉树T存在,p指向T中某个结点,LR为0或1,非空二叉树c与T */
    /*           不相交且右子树为空 */
    /* 操作结果: 根据LR为0或1,插入c为T中p所指结点的左或右子树。p所指结点的 */
    /*           原有左或右子树则成为c的右子树 */
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
        if (LR == 0) /* 删除左子树 */
            {if((*p)->lchild==NULL)
                return ERROR;
            else
            ClearBiTree(&(*p)->lchild);}
        else /* 删除右子树 */
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
    if (T) /* T不空 */
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
    /* 构造一个空队列Q */
    (*Q).base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
    if (!(*Q).base) /* 存储分配失败 */
        exit(OVERFLOW);
    (*Q).front = (*Q).rear = 0;
    return OK;
}

Status DestroyQueue(SqQueue *Q)
{
    /* 销毁队列Q,Q不再存在 */
    if ((*Q).base)
        free((*Q).base);
    (*Q).base = NULL;
    (*Q).front = (*Q).rear = 0;
    return OK;
}

Status QueueEmpty(SqQueue Q)
{
    /* 若队列Q为空队列,则返回TRUE,否则返回FALSE */
    if (Q.front == Q.rear) /* 队列空的标志 */
        return TRUE;
    else
        return FALSE;
}

Status EnQueue(SqQueue *Q, QElemType e)
{
    /* 插入元素e为Q的新的队尾元素 */
    if ((*Q).rear >= MAXQSIZE)
    {
        /* 队列满，增加1个存储单元 */
        (*Q).base = (QElemType *)realloc((*Q).base, ((*Q).rear + 1) * sizeof(QElemType));
        if (!(*Q).base) /* 增加单元失败 */
            return ERROR;
    }
    *((*Q).base + (*Q).rear) = e;
    (*Q).rear++;
    return OK;
}

Status DeQueue(SqQueue *Q, QElemType *e)
{
    /* 若队列不空,则删除Q的队头元素,用e返回其值,并返回OK,否则返回ERROR */
    if ((*Q).front == (*Q).rear) /* 队列空 */
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
    printf("请输入文件名！\n");
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
        printf("二叉树已存在，确定继续读取文件？此操作将覆盖原有二叉树！(1/0)\n");
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
        printf("    请选择你的操作[0~23]:");
        scanf("%d", &op);
        if (flag == 0 && op != 1 && op != 0)
        {
            printf("二叉树未初始化！无法操作！\n");
            system("pause");
            continue;
        }
        switch (op)
        {
        case 1:
            if (flag == 0)
            {
                if (InitBiTree(&root, &T))
                    printf("二叉树已成功初始化！\n");
                flag = 1;
            }
            else
                printf("二叉树已初始化，不能重复操作！\n");
            system("pause");
            break;
        case 2:
            if (DestroyBiTree(&root))
            {
                printf("二叉树已成功销毁！\n");
                flag = 0;
            }
            else
                printf("销毁失败！\n");
            system("pause");
            break;
        case 3:
            printf("-----CreateBiTree----\n");
            if (CreateBiTree(&T))
            {
                root->lchild = T;
                printf("成功创建二叉树！\n");
            }

            else
                printf("创建失败！\n");
            system("pause");
            break;
        case 4:
            printf("----ClearBiTree----\n");
            if (ClearBiTree(&T))
                printf("成功清空二叉树！\n");
            else
                printf("无法清空！\n");
            system("pause");
            break;
        case 5:
            if (!BiTreeEmpty(T))
                printf("二叉表非空！\n");
            else
                printf("二叉表为空！\n");
            system("pause");
            break;
        case 6:
            printf("-----BiTreeDepth----\n");
            {
                int depth;
                depth = BiTreeDepth(T);
                printf("树的深度为%d\n", depth);
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
                    printf("树为空树！\n");
                system("pause");
            }
            break;
        case 8:
            printf("----Value----\n");
            printf("请输入查询结点元素的关键字\n");
            int num = 0;
            TElemType x;
            printf("Number:");
            scanf("%d", &num);
            x = Value(T, num);
            if (x.Number)
                printf("该节点的值为%s\n", x.Name);
            else
                printf("该节点不存在！\n");
            system("pause");
            break;
        case 9:if(T==NULL)
                    printf("树为空！\n");
            else{
            printf("----Assign----\n");
            printf("请输入需要赋值结点的关键字！\n");
            TElemType e;
            scanf("%d", &e.Number);
            char value[30];
            printf("请输入修改后的值value:\n");
            scanf("%s", value);
            if(Assign(T, &e, value))
                printf("赋值成功！\n");
            else
                    printf("不存在该结点！\n");}
            system("pause");
            break;
        case 10:
            printf("请输入需要查找的结点！\n");
            TElemType a, b;
            printf("Number:");
            scanf("%d", &a.Number);
            printf("Name:");
            scanf("%s", a.Name);
            b = Parent(T, a);
            if (b.Number != 0)
                printf("%d %s的父节点为%d %s\n", a.Number, a.Name, b.Number, b.Name);
            else if (!strcmp(b.Name,"#"))
                printf("%d %s为根节点，无父节点！\n", a.Number, a.Name);
            else
                printf("不存在该节点！\n");
            system("pause");
            break;
        case 11:
            if(T==NULL)
                printf("树为空！\n");
            else{
                printf("请输入需要查找的结点！\n");
                printf("Number:");
                scanf("%d", &a.Number);
                printf("Name:");
                scanf("%s", a.Name);
                b = LeftChild(T, a);
                if (b.Number != 0)
                    printf("%d %s的左孩子为%d %s\n", a.Number, a.Name, b.Number, b.Name);
                else if (!strcmp(b.Name,"#"))
                    printf("不存在该节点！\n");
                else
                    printf("该节点没有左孩子！\n");
            }
            system("pause");
            break;
        case 12:
            if(T==NULL)
                printf("树为空！\n");
            else{
                printf("请输入需要查找的结点！\n");
                printf("Number:");
                scanf("%d", &a.Number);
                printf("Name:");
                scanf("%s", a.Name);
                b = RightChild(T, a);
                if (b.Number != 0)
                    printf("%d %s的右孩子为%d %s\n", a.Number, a.Name, b.Number, b.Name);
                else if(!strcmp(b.Name,"#"))
                    printf("不存在该节点！\n");
                else
                    printf("该节点没有右孩子！\n");}
            system("pause");
            break;
        case 13:
        {
            TElemType a, b;
            printf("请输入需要查找的结点！\n");
            printf("Number:");
            scanf("%d", &a.Number);
            printf("Name:");
            scanf("%s", a.Name);
            b = LeftSibling(T, a);
            if (b.Number != 0)
                printf("%d %s的左兄弟为%d %s\n", a.Number, a.Name, b.Number, b.Name);
            else if(!strcmp(b.Name,"#"))
                printf("不存在该节点！\n");
            else
                printf("该节点没有左兄弟！\n");
        }
            system("pause");
            break;
        case 14:
        {
            TElemType a, b;
            printf("请输入需要查找的结点！\n");
            printf("Number:");
            scanf("%d", &a.Number);
            printf("Name:");
            scanf("%s", a.Name);
            b = RightSibling(T, a);
            if (b.Number != 0)
                printf("%d %s的右兄弟为%d %s\n", a.Number, a.Name, b.Number, b.Name);
            else if(!strcmp(b.Name,"#"))
                printf("不存在该节点！\n");
            else
                printf("该节点没有左兄弟！\n");
        }
            system("pause");
            break;
        case 15:
        {
            int LR;
            BiTNode subTree, *psubTree = &subTree; //subTree为插入的子树
            BiTree subRoot;
            InitBiTree(&subRoot, &psubTree);
            CreateBiTree(&psubTree);
            printf("请输入目标节点的值！\n");
            TElemType q;
            printf("Number:");
            scanf("%d", &q.Number);
            printf("Name:");
            scanf("%s", q.Name);
            BiTree p = Point(T, q); //p为指向q的指针；
            printf("请输入想插入为该节点的左子树还是右子树（0/1）？\n");
            scanf("%d", &LR);
            if(p!=NULL){
                if (InsertChild(&p, LR, &psubTree))
                    printf("插入成功！\n");
                else
                    printf("删除失败!\n");
                }
            else
                printf("插入失败！\n");
        }
            system("pause");
            break;
        case 16:
        {
            int LR;
            printf("请输入目标节点的值!\n");
            TElemType a;
            printf("Number:");
            scanf("%d", &a.Number);
            printf("Name:");
            scanf("%s", a.Name);
            printf("删除左子树还是右子树呢(0/1)?\n");
            scanf("%d", &LR);
            BiTree b;
            b = Point(T, a); //b为指向a的指针
            if(b!=NULL){
                if (DeleteChild(&b, LR))
                    printf("删除成功！\n");
                else
                    printf("删除失败!\n");
                    }
            else
                printf("删除失败!\n");
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
                printf("保存成功！\n");
            else
                printf("保存失败！\n");
            system("pause");
            break;
        case 22:
            if (readfile(&T))
            {
                printf("读取成功！\n");
                root->lchild = T;
            }
            else
                printf("读取失败！\n");
            system("pause");
            break;
        case 0:
            printf("欢迎使用本系统！再见\n");
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
Status IntiaList(SqList *L) //线性表初始化
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
        printf("\n-------------欢迎使用二叉树管理系统-------------\n");
        printf("你选择对第几棵树进行操作？1-%d\n", L.length + 1);
        printf("输入0退出本系统！\n");
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
