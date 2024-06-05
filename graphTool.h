//
// Created by KaguraSora on 5/21/2024.
//

#include "stdio.h"
#include "stdlib.h"


//顺序表-点-点边-点边 (旧
//顺序表-点-边-边-边 (新
//顶点
typedef struct VNode {
    int index;
    //指向任一边
    struct edge *pEdge;
} VNode;

//边
//存储边的前后节点方便我查找(用于有待进一步确定
//next用于形成链表(天才设计
//双向边看作两条独立的边就不会出现重复的情况
//存储两头的节点单纯为了方便我查找(反正内存不要钱(优化什么的不存在的
typedef struct edge {
    VNode *from;
    VNode *to;
    int weight;
    struct edge *next;
} UEdge;

//邻接表表头
typedef struct graph {
    VNode *graph;
    int capacity;
} graphStruct;

//成员变量邻接表
//最不会出问题的一集
graphStruct graph;

//广度遍历用的Queue
//写成链表形式(
typedef struct QNode {
    VNode *vNode;
    struct QNode *next;
} QNode;
QNode head;

//创建队列节点
QNode *createQNode(VNode *vNode) {
    QNode *qNode = malloc(sizeof(QNode));
    qNode->vNode = vNode;
    qNode->next = NULL;
    return qNode;
}

//找队尾
//返回最后一个节点
QNode *findLast() {
    QNode *qNode = &head;
    while (qNode->next != NULL) {
        qNode = qNode->next;
    }
    return qNode;
}

//判断队空
//0为空,1为非空
int emptyOrNot() {
    if (head.next == NULL) {
        return 0;
    }
    return 1;
}

//初始化队列
int initQueue() {
    head.vNode = NULL;
    head.next = NULL;
    return 1;
}

//入队
int enQueue(VNode *vNode) {
    QNode *qNode = findLast();
    qNode->next = createQNode(vNode);
    return 1;
}

//出队
int deQueue() {
    QNode *qNode = head.next;
    if (head.next->next == NULL) {
        head.next = NULL;
        free(qNode);
        return 1;
    }
    head.next = head.next->next;
    free(qNode);
    return 1;
}

//最短路径算法用节点
//visit表示访问状态，1为访问过，0为未访问
typedef struct DNode {
    int visit;
    int distance;
    VNode *preVNode;
} DNode;

//创建邻接表本体，需指定大小(节点数)
graphStruct createGraph(int capacity) {
    graph.graph = malloc(capacity * sizeof(VNode));
    int i = 0;
    //手动把所有VNode的索引都初始化成-1(什么标记法
    while (i != capacity) {
        graph.graph[i].index = -1;
        graph.graph[i].pEdge = NULL;
        i++;
    }
    //经典顺序表
    graph.capacity = capacity;
    return graph;
}


//向邻接表中添加未添加过的节点,并赋索引值
//索引初值为-1
int addNodeToAdjacencyList(VNode *vNode) {
    int i = 0;
    while (i < graph.capacity) {
        if (graph.graph[i].index == -1) {
            vNode->index = i;
            graph.graph[i] = *vNode;
            //找到空位并返回对应索引
            return i;
        }
        i++;
    }
    //放入邻接表失败返回负值
    return -1;
}

//检查邻接表中是否含有节点,如果有返回索引值
//索引初值为-1
int checkInList(VNode *vNode) {
    int i = 0;
    while (i != graph.capacity - 1) {
        if (graph.graph[i].index == vNode->index) {
            return vNode->index;
        }
        i++;
    }
    return -1;
}

//创建并初始化节点
//索引初值为-1
//直接添加进邻接表
VNode *createNode() {
    VNode *vNode = malloc(sizeof(VNode));
    vNode->index = -1;
    vNode->pEdge = NULL;
    addNodeToAdjacencyList(vNode);
    return vNode;
}

//根据edge的from节点创建并初始化边
UEdge *createEdge(int fromIndex, int toIndex, int weight) {
    UEdge *uEdge = malloc(sizeof(UEdge));
    uEdge->from = &graph.graph[fromIndex];
    uEdge->to = &graph.graph[toIndex];
    uEdge->weight = weight;
    uEdge->next = NULL;
    return uEdge;
}

//一键找到边链表的最后的轮椅?,帅!otto!
//避免不了新的VNode没有UEdge的问题
UEdge *findLastGNode(VNode *vNode) {
    if (checkInList(vNode) < 0) {
        addNodeToAdjacencyList(vNode);
    }
    UEdge *uEdge = vNode->pEdge;
    while (uEdge->next != NULL) {
        uEdge = uEdge->next;
    }
    return uEdge;
}

//dir用于表示边的有向无向，0表示有向，1表示无向(双向)
//通过递归调用实现无向图(双向边)
int addEdgeToAdjacencyList(int fromIndex, int toIndex, int weight, int dir) {
    VNode *from = &graph.graph[fromIndex];
    VNode *to = &graph.graph[toIndex];
    if (checkInList(to) < 0) {
        addNodeToAdjacencyList(to);
    }
    //新建一条edge并放入from节点存储edge的表的末尾
    //判断from是否已有UEdge节点,如果有就直接加入
    if (from->pEdge == NULL) {
        from->pEdge = createEdge(from->index, to->index, weight);
    } else {
        findLastGNode(from)->next = createEdge(from->index, to->index, weight);
    }
    //实现无向图双向边
    if (dir) {
        addEdgeToAdjacencyList(toIndex, fromIndex, weight, 0);
    }
    return 1;
}

//广度遍历
int breathFirstSearch(int *arr, VNode *vNode) {
    printf("%d >> ", vNode->index);
    UEdge *uEdge = vNode->pEdge;
    while (uEdge != NULL) {
        if (arr[uEdge->to->index] == 0) {
            enQueue(uEdge->to);
            arr[uEdge->to->index] = 1;
        }
        uEdge = uEdge->next;
    }
    deQueue();
    if (!emptyOrNot()) {
        return 1;
    }
    breathFirstSearch(arr, head.next->vNode);
    return 1;
}

//深度遍历
int depthFirstSearch(int *arr, VNode *vNode) {
    arr[vNode->index] = 1;
    printf("%d >> ", vNode->index);
    UEdge *uEdge = vNode->pEdge;
    while (uEdge != NULL) {
        if (!arr[uEdge->to->index]) {
            depthFirstSearch(arr, uEdge->to);
        }
        uEdge = uEdge->next;
    }
    return 1;
}

//两种遍历的中转函数
//0去广度遍历
//1去深度遍历
//神经病啊干嘛要这么写
//藏的这么深别人拿头看=(
int traversalGraph(int type) {
    //存储访问状态的数组
    //1为已经被访问过
    //0为未被访问
    int arr[graph.capacity];
    for (int i = 0; i < graph.capacity; ++i) {
        arr[i] = 0;
    }
    switch (type) {
        case 0:
            printf("广度优先遍历:\n");
            initQueue();
            enQueue(graph.graph);
            breathFirstSearch(arr, &graph.graph[0]);
            printf("\n\n");
            break;
        case 1:
            printf("深度优先遍历:\n");
            depthFirstSearch(arr, &graph.graph[0]);
            printf("\n\n");
            break;
        default:
    }
    return 1;

}

//基于深度优先算法的拓扑排序
int topologicalSort() {
    printf("拓扑排序基于\n");
    traversalGraph(1);
    return 1;
}

//Dijkstra算法
//做一个广度遍历,并计算权
int dijkstra(DNode *dis, VNode *vNode) {
    UEdge *uEdge = vNode->pEdge;
    while (uEdge != NULL) {
        //记录暂时存储从此节点到后继的距离值,后续进行比较
        int TDis = dis[vNode->index].distance + uEdge->weight;
        //未访问过就将暂时值赋为初值,并记录当前节点为前驱
        if (dis[uEdge->to->index].visit == 0) {
            enQueue(uEdge->to);
            dis[uEdge->to->index].distance = TDis;
            dis[uEdge->to->index].preVNode = vNode;
            dis[uEdge->to->index].visit = 1;
        } else {
            //访问过则判断后继节点的距离值和暂时值进行比较,并选择小的负值并记录前驱节点
            if (TDis < dis[uEdge->to->index].distance) {
                dis[uEdge->to->index].distance = TDis;
                dis[uEdge->to->index].preVNode = vNode;
            }
        }
        uEdge = uEdge->next;
    }
    deQueue();
    if (!emptyOrNot()) {
        return 1;
    }
    dijkstra(dis, head.next->vNode);

    return 1;
}

//Dijkstra算法前置
int preDijkstra() {
    printf("Dijkstra算法\n");
    DNode dis[graph.capacity];
    //赋初值
    for (int i = 0; i < graph.capacity; ++i) {
        dis[i].visit = 0;
        dis[i].preVNode = &graph.graph[i];
    }
    initQueue();
    enQueue(graph.graph);
    dis[0].distance = 0;
    dijkstra(dis, dis->preVNode);
    //打印最短路径和前驱
    for (int i = 1; i < graph.capacity; ++i) {
        printf("节点:%d->[%d,%d]  ", i + 1, dis[i].preVNode->index + 1, dis[i].distance);
    }
    printf("\n");
    return 1;
}

//打印邻接表
//主要打印索引
//用->分割
//^结尾
int printAdjacencyList() {
    printf("打印邻接表\n");
    for (int i = 0; i < graph.capacity; ++i) {
        printf("%d-> ", graph.graph[i].index);
        if (graph.graph[i].pEdge == NULL) {
            printf("^\n");
            continue;
        }
        UEdge *uEdge = graph.graph[i].pEdge;
        while (uEdge != NULL) {
            printf("%d-> ", uEdge->to->index);
            uEdge = uEdge->next;
        }
        printf(" ^\n");
    }
    printf("\n");
    return 0;
}

//往邻接表里塞东西
//有向图
int initialGraph() {
    createGraph(5);
    //添加节点
    createNode();//0
    createNode();//1
    createNode();//2
    createNode();//3
    createNode();//4
    //添加边
    //1节点的边
    addEdgeToAdjacencyList(0, 1, 4, 0);
    addEdgeToAdjacencyList(0, 3, 5, 0);
    //2节点的边
    addEdgeToAdjacencyList(1, 4, 1, 0);
    addEdgeToAdjacencyList(1, 2, 3, 0);
    //3节点的边
    //4节点的边
    addEdgeToAdjacencyList(3, 2, 2, 0);
    //5节点的边
    addEdgeToAdjacencyList(4, 2, 3, 0);
    return 0;
}

