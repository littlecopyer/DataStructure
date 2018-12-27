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
#define MAX_VERTEX_NUM 20
#define MAXQSIZE 5
typedef int Status; //状态的类型定义
typedef int InfoType;
typedef char VertexType[30];
int visited[MAX_VERTEX_NUM];
typedef struct ArcNode
{
    int adjvex;              //该弧所指向顶点的位置
    struct ArcNode *nextarc; //指向下一条弧的指针
    InfoType *info;          //该户相关信息的指针
} ArcNode;
typedef struct VNode
{
    struct value
    {
        int key;
        VertexType data;
    }value;
    ArcNode *firstarc;
} VNode, AdjList[MAX_VERTEX_NUM];//顶点数组
typedef struct Arc
{
    int tail;
    int head;
} Arc;
VNode NullVNode = {.value.key=0, .value.data = "#", .firstarc = NULL}; //NullVNode代表空结点
typedef struct
{
    AdjList vertices;
    int vexnum, arcnum;
} ALGraph;
typedef VNode QElemType;
typedef struct
{
    QElemType *base;
    int front;
    int rear;
} SqQueue;
int LocateVex(ALGraph G, int c);
Status CreateDG(ALGraph *G, struct value V[], Arc ArcSet[]);
//Status DestroyGraph(ALGraph *G);
struct VNode GetVex(ALGraph G, int i);
Status PutVex(ALGraph *G, struct VNode v, VertexType value);
int FirstAdjVex(ALGraph G, struct VNode v);
int NextAdjVex(ALGraph G, VNode v, VNode w);
Status InsertVex(ALGraph *G, struct VNode V);
Status DeleteVex(ALGraph *G, int v);
Status InsertArc(ALGraph *G, Arc A);
Status DeleteArc(ALGraph *G, Arc A);
Status DFSTraverse(ALGraph G, Status (*Visit)());
void DFS(ALGraph G, int v);
Status Save(ALGraph G);
Status ReadFile(ALGraph *G);
Status Visit(struct value A);
Status InitQueue(SqQueue *Q);
Status QueueEmpty(SqQueue Q);
Status EnQueue(SqQueue *Q, QElemType e);
Status DeQueue(SqQueue *Q, QElemType *e);
/**name:CreatDG
 * param:ALGraph *G,VertexType V[],Arc ArcSet[]
 * return:Status
 * function:Creat a DGraph*/
Status CreateDG(ALGraph *G,struct value V[], Arc ArcSet[])
{
    int flag = 1;
    int i;
    for (i = 0; flag&&V[i].key!=0&&V[i+1].key!=0; i++)
    {
        int j;
        for ( j = i + 1; flag&&V[j].key!=0;j++)
        {
            if(V[i].key==V[j].key)
            {
                flag = 0;
                break;
            }
        }
    }
    if(flag)
    {
        int i = 0;
        while(V[i].key!=0)
        {
            (*G).vertices[i].value = V[i];
            (*G).vertices[i].firstarc = NULL;
            i++;
        }
        (*G).vexnum = i;
        int k = 0;
        while(ArcSet[k].tail!=0&&ArcSet[k].head!=0)
           {
               if(InsertArc(G, ArcSet[k]))
                (*G).arcnum++;
               k++;
           }
               if ((*G).vexnum != 0)
                   return OK;
               else
                   return ERROR;
    }//end of if
    else
        return ERROR;
}

/**name:DestroyGraph
 * param:ALGraph *G
 * retrun:Status
 * function:Destroy Graph G when G exists*/
Status DestroyGraph(ALGraph *G)
{
    for (int i = 0;i<(*G).vexnum;i++)
    {
        (*G).vertices[i].value.key = 0;
        memset((*G).vertices[i].value.data, 0x00, sizeof (char) * 30);
        (*G).vertices[i].firstarc = NULL;
    }
    (*G).arcnum = 0;
    (*G).vexnum = 0;
    return OK;
}
/**name:LocateVex
 * param:ALGraph G,int c
 * return:int
 * function:get Vertex's location*/
int LocateVex(ALGraph G, int c)
{
    int i;
    for (i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].value.key==c)
            return i;
    }
    return -1;
}

/**name:GetVex
 * param:ALGraph G,int i
 * return:struct VNode
 * function:return the VNode n which is struct VNode*/
struct VNode GetVex(ALGraph G, int i)
{
    return G.vertices[i];
}

/**name:PutVex
 * param:ALGraph *G,struct VNode v, vertexType data
 * return:Status
 * function:let VNode v's data=data*/
Status PutVex(ALGraph *G, struct VNode v, VertexType data)
{
    int i;
    i = LocateVex((*G), v.value.key);
    if(i!=-1)
    {
        strcpy((*G).vertices[i].value.data, data);
        return OK;
    }
    else
        return ERROR;
}

/**name:FirstAdjVex
 * param:ALGraph G,struct VNode v
 * return:int
 * function:return the first adjVex of v,else return NullVNode*/
int  FirstAdjVex(ALGraph G, struct VNode v)
{
    int i = LocateVex(G, v.value.key);
    if(G.vertices[i].firstarc==NULL)
        return -1;
    else
        return G.vertices[i].firstarc->adjvex;

}

/**name:NextAdjVex
 * param:ALGraph G,VNode v,VNode w
 * return:int
 * function:return v'adjvex behind w*/
int NextAdjVex(ALGraph G, VNode v, VNode w)
{
    int vi = 0, wi = 0;
    vi = LocateVex(G, v.value.key);
    wi = LocateVex(G, w.value.key);
    if (vi != -1 && wi != -1) //v,w都是G中的顶点
    {
        ArcNode *N;
        N = G.vertices[vi].firstarc;
        while (N != NULL && N->adjvex != wi)
        {
            N = N->nextarc;
        }
        if (N == NULL)
        {
            //printf("w is not the adjvex of v!\n");
            return -1;
        }
        else if (N->nextarc == NULL)
        {
           // printf("w is the last adjvex of v!\n");
            return -2;
        }
        else
        {
            int j = N->nextarc->adjvex;
            return j;
        }
    }
    else
    {
        printf("One of v and w is not the vex of G!\n");
        return -1;
    }
}

/**name:InsertVex
 * param:ALGraph *G,struct VNode
 * return:Status
 * function:add a new vex to Graph G,and the vex==v*/
Status InsertVex(ALGraph *G,struct VNode V)
{
    if((*G).vexnum==MAX_VERTEX_NUM)
    {
        printf("The vexnum is up to the MAX_VERTEX_NUM,can't insert vex any more!");
        return ERROR;
    }
    int i = 0;
    for (i = 0; i < (*G).vexnum;i++)
    {
        if(V.value.key==(*G).vertices[i].value.key)
            break;
    }
    if(i<(*G).vexnum)
    {
        printf("The vex has already existed in the graph!\n");
        return ERROR;
    }
    else
    {

        (*G).vertices[(*G).vexnum] = V;
        (*G).vertices[(*G).vexnum].firstarc = NULL;
        (*G).vexnum++;
        return OK;
    }
}

/**name:DeleteVex
 * param:ALGraph *G,int v
 * return:Status
 * function:Delete the vex N whoes key equals to v,and delete all the arc related to N*/
Status DeleteVex(ALGraph *G,int v)
{
    int vi = 0;
    vi = LocateVex((*G), v);
    if(vi!=-1)      //v is one vex's data in Graph G
    {
        int j = 0;
        for (j = 0; j < (*G).vexnum; j++) //Traverse all the ArcNode,delete all the ArcNode related to v;
        {
            ArcNode *M = (*G).vertices[j].firstarc;
            ArcNode *N = (*G).vertices[j].firstarc;
            if(N!=NULL)
            {
                if(N->adjvex==vi)
                    (*G).vertices[j].firstarc = NULL;
                else
                {
                    N = M->nextarc; //M is the Precursor node of N;
                    while(N!=NULL)
                    {
                        if(N->adjvex==vi)
                        {
                            M->nextarc = N->nextarc;
                            break;
                        }
                        M = M->nextarc;
                        N = N->nextarc;
                    }
                }
            }
        }
        int tail = (*G).vexnum - 1;
        int i;
        for (i= vi; i <tail;i++)
            (*G).vertices[i] = (*G).vertices[i + 1];
        (*G).vexnum--;
        return OK;
    }
    else
        return ERROR;
}

/**name:InsertArc
 * param:ALGraph *G,Arc A
 * return:Status
 * function:add arc<v,w> to Graph G*/
Status InsertArc(ALGraph *G,Arc A)
{
    int vi = 0, wi = 0;
    vi = LocateVex((*G),A.tail);
    wi = LocateVex((*G), A.head);
    if (vi != -1 && wi != -1) //both of v and w are in the graph G;
    {
        ArcNode *N;
        N = (*G).vertices[vi].firstarc;
        if(N==NULL)
        {
            N = (ArcNode *)malloc(sizeof(ArcNode));
            N->adjvex = wi;
            N->info = NULL;
            N->nextarc = NULL;
            (*G).vertices[vi].firstarc = N;
            return OK;
        }
        else
        {
            ArcNode *M;
            M=(*G).vertices[vi].firstarc;
            while(N!=NULL&&N->adjvex!=wi)
               {
                   M = N; //M is the Precursor Node of N;
                   N = N->nextarc;
               }
            if(N==NULL)
                {
                    N = (ArcNode *)malloc(sizeof(ArcNode));
                    N->adjvex = wi;
                    N->info = NULL;
                    N->nextarc = (*G).vertices[vi].firstarc;
                    (*G).vertices[vi].firstarc = N;
                    return OK;
                }
            else
            {
                printf("Arc %d->%d has already existed!\n", A.tail,A.head);
                return ERROR;
            }
        }
    }
    else
    {
        printf("%d or %d is not the vex of the graph!\n", A.tail, A.head);
        return ERROR;
    }
}

/**name:DeleteArc
 * param:ALGraph *G,Arc A
 * return:Status
 * function:Delete arc<v,w>*/
Status DeleteArc(ALGraph *G, Arc A)
{
    int vi = 0, wi = 0;
    vi = LocateVex((*G), A.tail);
    wi = LocateVex((*G), A.head);
    if (vi != -1 && wi != -1) //both of v and w are in the graph G;
    {
        ArcNode *N;
        N = (*G).vertices[vi].firstarc;
        if (N == NULL)
        {
            printf("%d doesn't has any Arc!\n", A.tail);
            return ERROR;
        }
        else
        {
            if (N->adjvex == wi)
            {
                (*G).vertices[vi].firstarc = N->nextarc;
                return OK;
            }
            else
            {
                ArcNode *M;
                M = N; //M is the Precursor Node of N;
                N = N->nextarc;
                while (N != NULL && N->adjvex != wi)
                {
                    M = N;
                    N = N->nextarc;
                }
                if (N == NULL)
                {
                    printf("Arc %d->%d doesn't exist!\n", A.tail, A.head);
                    return ERROR;
                }
                else
                {
                    M->nextarc = N->nextarc;
                    return OK;
                }
            }
        }
    }
    else
    {
        printf("%d or %d is not the vex of the graph!\n", A.tail, A.head);
        return ERROR;
    }
}

/**name:DFSTraverse
 * param:ALGraph G,Visit()
 * return:Status
 * function:Deep first traverse all the vexes of the Graph G*/
Status DFSTraverse (ALGraph G,Status (*Visit)())
{
    int i;
    for( i = 0; i < G.vexnum; i++)   //initial flag array
        visited[i] = 0;
        int j;
    for ( j= 0; j < G.vexnum;j++)
    {
        if(!visited[j])
            DFS(G, j);
    }
    return OK;
}

/**name:DFS
 * param:ALGraph G,int v
 * return:void
 * function:Recursive depth-first traversal from the vth vertex*/
void DFS(ALGraph G,int v)
{
    visited[v] = 1;
    Visit(G.vertices[v].value);
    int w;
    for ( w = FirstAdjVex(G, G.vertices[v]); w >= 0;w=NextAdjVex(G,G.vertices[v],G.vertices[w]))
    {
        if(!visited[w])
            DFS(G, w);
    }
}
/**name:Visit
 * param:struct value A
 * return:Status
 * function:print vex v*/
Status Visit(struct value A)
{
    printf("%d %s\n",A.key,A.data);
    return OK;
}

/**name:BFSTraverse
 * param:ALGraph G,Status(*Visit)()
 * return:Status
 * function:Breadth-first non-recursive traversal Graph*/
Status BFSTraverse(ALGraph G,Status(*Visit)())
{
    int i;
    for ( i = 0; i < G.vexnum;i++)
        visited[i] = 0;
    SqQueue Q;
    InitQueue(&Q);
    int v;
    for ( v = 0; v < G.vexnum;v++)
        if(!visited[v])
        {
            visited[v] = 1;
            Visit(G.vertices[v].value);
            EnQueue(&Q, G.vertices[v]);
            while(!QueueEmpty(Q))
            {
                QElemType u;
                DeQueue(&Q, &u);
                int w;
                for ( w = FirstAdjVex(G, u); w >= 0;w=NextAdjVex(G,u,G.vertices[w]))
                if(!visited[w])
                {
                    visited[w] = 1;
                    Visit(G.vertices[w].value);
                    EnQueue(&Q, G.vertices[w]);
                }//end of if
            }//end of while
        }//end of if
    return OK;
}//BFTraverse

/**name:Save
 * param:ALGragh G
 * return:Status
 * function:Save ALGragh as a file*/
Status Save (ALGraph G)
{
    FILE  *fp;
    char s[30];
    printf("Input the file name:");
    scanf("%s", s);
    if ((fp=fopen(s,"ab+"))==NULL)
    {
        printf("File open error\n ");
        return ERROR;
    }
        fwrite(&G.vexnum, sizeof(int), 1, fp);
        fwrite(&G.arcnum, sizeof(int), 1, fp);
        fwrite(G.vertices, sizeof(VNode), G.vexnum, fp);
        int i = 0;
        for (i = 0; i < G.vexnum;i++)
        {
            ArcNode *p;
            p = G.vertices[i].firstarc;
            while(p!=NULL)
            {
                fwrite(p,sizeof(ArcNode),1,fp);
                printf("%d Ox%p\n", (*p).adjvex, (*p).nextarc);
                p=p->nextarc;
            } 
        }
    fclose(fp);
    return OK;
}
/**name:ReadFile
 * param:ALGragh *G
 * return:Status
 * function:Read a specific file to creat a DGragh*/
Status ReadFile(ALGraph *G)
{
    FILE  *fp;  char filename[30];
    printf("input file name: ");
    scanf("%s",filename);
    if ((fp=fopen(filename,"rb"))==NULL)
	{
	 printf("File open error\n ");
	 return ERROR;
	}
    fread(&(*G).vexnum,sizeof(int),1,fp);
    printf("%d", (*G).vexnum);
    fread(&(*G).arcnum, sizeof(int), 1, fp);
    printf("%d", (*G).arcnum);
    fread((*G).vertices, sizeof(VNode), (*G).vexnum, fp);
    int i;
    for (i = 0; i < (*G).vexnum;i++)
    {
        ArcNode *p, *k;
        p = (*G).vertices[i].firstarc;
        if(p!=NULL)
        {
            ArcNode *q = (ArcNode *)malloc(sizeof(ArcNode));
            fread(q, sizeof(ArcNode), 1, fp);
            (*G).vertices[i].firstarc = q;
            p = q->nextarc;
            k = (*G).vertices[i].firstarc;
            while(p!=NULL)
            {
                ArcNode *q = (ArcNode *)malloc(sizeof(ArcNode));
                fread(q, sizeof(ArcNode), 1, fp);
                k->nextarc = q;
                k = q;
                p=q->nextarc;
            }
        }    
    }
    fclose(fp);
    return OK;
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

int main(int argc, char const *argv[])
{
    ALGraph G;
    int op = 1;
    int flag = 0;
    while(op)
    {
        system("cls");
        printf("----------Menu  of  DGraph--------------------\n");
        printf("1.CreatDG                          9.DeleteVex\n");
        printf("2.DestroyGraph                    10.InsertArc\n");
        printf("3.LocateVex                       11.DeleteArc\n");
        printf("4.GetVex                          12.DFSTravers\n");
        printf("5.PutVex                          13.BFSTraverse\n");
        printf("6.FirstAdjVex                     14.Save\n");
        printf("7.NextAdjVex                      15.ReadFile\n");
        printf("8.InsertVex                        0.Exit\n");
        printf("-------------------------------------------------\n");
        scanf("%d", &op);
        switch (op)
        {
            case 1:if(!flag)
                {
                    int i = 0, j = 0;
                    struct value V[MAX_VERTEX_NUM]; Arc ArcSet[400];
                    printf("Plese input the %d Vertex's value(key&data) :\n", i+1);
                    scanf("%d %s",&V[i].key,V[i].data); //输入顶点值
                    while(V[i].key!=0)
                    {
                        i++;
                        printf("Plese input the %d Vertex's value(key&data) :\n", i);
                        scanf("%d %s",&V[i].key,V[i].data); //输入顶点值
                    }
                    printf("Please input the tailvex and the headvex of the Arc:\n");
                    scanf("%d %d", &ArcSet[j].tail, &ArcSet[j].head);
                    while(ArcSet[j].tail!=0&&ArcSet[j].head!=0)
                    {
                        j++;
                        printf("Please input the tailvex and the headvex of the Arc:\n");
                        scanf("%d %d", &ArcSet[j].tail, &ArcSet[j].head);
                    }
                    if (CreateDG(&G,V,ArcSet))
                    {
                        printf("Created successfully!\n");
                        flag = 1;
                    }
                    else
                        printf("Failed to creat!\n");
                 }
                 else
                     printf("Failed to creat! You have already created a graph!\n");
                system("pause");
                break;
            case 2:if(!flag)
                    {
                        printf("Failed to destroy! You even didn't creat a graph!\n");
                    }
                    else
                    {
                        if(DestroyGraph(&G))
                            {
                                printf("Destroyed successfully!\n");
                                flag = 0;
                            }
                        else
                            printf("Failed to destroy!\n");
                    }
                system("pause");
                break;
            case 3:if(!flag)
                        printf("Graph doesn't exist!\n");
                    else
                    {
                        printf("---LocateVex-----\n");
                        printf("Plese input the key of the vex:");
                        int key;
                        scanf("%d", &key);
                        int i;
                        i = LocateVex(G, key)+1;
                        if(i!=0)
                            printf("%d is the %d Vex;\n", key, i);
                        else
                            printf("%d is not in the graph!\n",key);
                    }
                system("pause");
                break;
            case 4:if(!flag)
                    printf("Graph doesn't exist!\n");
                    else
                    {
                        printf("-----GetVex-----\n");
                        printf("Please input the key of the vex that you wanna get:");
                        int key=0;
                        scanf("%d", &key);
                        int i = LocateVex(G, key);
                        if(i!=-1)
                        {
                            VNode V;
                            V=GetVex(G,i);
                            printf("%d %s\n", V.value.key,V.value.data);
                        }
                        else
                            printf("The vex is not in the graph!\n");
                    }
                system("pause");
                break;
            case 5:if(!flag)
                    printf("Graph doesn't exist!\n");
                    else
                    {
                        printf("------PutVex-----\n");
                        printf("Plese input the key of the vex:");
                        VNode v;
                        scanf("%d",&v.value.key);
                        printf("Please input the new data:");
                        VertexType value;
                        scanf("%s", value);
                        if(PutVex(&G,v,value))
                            printf("Assign successfully!\n");
                        else
                            printf("%d is not the vex of graph!\n",v.value.key);
                    }
                system("pause");
                break;
            case 6:if(!flag)
                        printf("Graph doesn't exist!\n");
                    else
                    {
                        printf("-----FirstAdjVex----\n");
                        printf("Please input the key of the vex:");
                        VNode v;
                        scanf("%d", &v.value.key);
                        int i = LocateVex(G, v.value.key);
                        if(i==-1)
                            printf("%d is not the vex of graph!\n",v.value.key);
                        else
                        {
                            int first;
                            first = FirstAdjVex(G, v);
                            if(first==-1)
                                printf("The vex has no FirstAdjVex!\n");
                            else
                                printf("%d's FirstAdjVex is the vex:%d %s\n", v.value.key,G.vertices[first].value.key,G.vertices[first].value.data);
                        }
                    }
                system("pause");
                break;
            case 7:if(!flag)
                        printf("Graph doesn't exist!\n");
                    else
                    {
                        printf("-----NextAdjVex-----\n");
                        printf("Please input the tailvex:");
                        VNode v, w;
                        scanf("%d", &v.value.key);
                        printf("Please input the headvex:");
                        scanf("%d", &w.value.key);
                        int j = NextAdjVex(G, v, w);
                        if(j==-1)
                            printf("%d is not the adjvex of %d!\n",w.value.key,v.value.key);
                        else if(j==-2)
                            printf("%d is the last adjvex of %d!\n",w.value.key,v.value.key);
                        else
                            printf("%d %s is the NextAdjVex!\n",G.vertices[j].value.key,G.vertices[j].value.data);
                    }
                system("pause");
                break;
            case 8:if(!flag)
                        printf("Graph doesn't exist!\n");
                    else
                    {
                        printf("-----InsertVex----\n");
                        printf("Please input the value of the vex");
                        VNode V;
                        scanf("%d %s",&V.value.key,V.value.data);
                        if(InsertVex((&G),V))
                            printf("Insert Vex successfully!\n");
                    }
                system("pause");
                break;
            case 9:if(!flag)
                        printf("Graph doesn't exist!\n");
                    else
                    {
                        printf("------DeleteVex-----\n");
                        printf("Please input the key of the vex that you want to delete:");
                        int key;
                        scanf("%d", &key);
                        if(DeleteVex((&G),key))
                            printf("Delete vex successfully!\n");
                        else
                            printf("%d is not the vex of the graph!\n",key);
                    }
                system("pause");
                break;
            case 10:if(!flag)
                        printf("Graph doesn't exist!\n");
                    else
                    {
                        printf("-----InsertArc-----\n");
                        printf("Please input the tailVex'key:");
                        Arc A;
                        scanf("%d",&A.tail);
                        printf("Please input the headVex'key:");
                        scanf("%d",&A.head);
                        if(InsertArc((&G),A))
                            printf("Insert arc %d->%d successfully!\n",A.tail,A.head);
                        else
                            printf("Failed to insert Arc %d->%d\n",A.tail,A.head);
                    }
                system("pause");
                break;
            case 11:if(!flag)
                        printf("Graph doesn't exist!\n");
                    else
                    {
                        printf("-----DeleteArc----\n");
                        printf("Please input the tailVex's key:");
                        Arc A;
                        scanf("%d",&A.tail);
                        printf("Please input the headVex's key:");
                        scanf("%d",&A.head);
                        if(DeleteArc((&G),A))
                            printf("Delete successfully!\n");
                        else
                            printf("Failed to delete!\n");
                    }
                system("pause");
                break;
            case 12:if(!flag)
                        printf("Graph doesn't exist!\n");
                    else
                        DFSTraverse(G, Visit);
                system("pause");
                break;
            case 13:if(!flag)
                        printf("Graph doesn't exist!\n");
                    else
                        BFSTraverse(G, Visit);
                system("pause");
                break;
            case 14:if(!flag)
                        printf("Graph doesn't exist!\n");
                    else
                    {
                        if(Save(G))
                            printf("Success to save it!\n");
                        else
                            printf("Failed to save it!\n");
                    }
                system("pause");
                break;
            case 15:if(flag)
                        printf("Failed to read! You have already created a graph!\n");
                    else
                    {
                        if(ReadFile(&G))
                        {
                            printf("Success to read it!\n");
                            flag = 1;
                        }
                            
                        else
                            printf("Failed to read it!\n");
                    }
                system("pause");
                break;
            case 0:
                system("pause");
                break;
            default:
                break;
        }//end of switch
    }//end of while
    return 0;
}//end of main