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
//顺序表,目前没什么问题
//记得把GNode换回VNode(悲
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
//但是没free,记得调用的时候free掉
QNode *deQueue() {
    QNode *qNode = head.next;
    head.next = head.next->next;
    return qNode;
}

//创建邻接表本体，需指定大小(节点数)
graphStruct createGraph(int capacity) {
    graph.graph = malloc(capacity * sizeof(VNode));
    int i = 0;
    //手动把所有VNode的索引都初始化成-1(什么标记法
    while (i != capacity - 1) {
        graph.graph[i].index = -1;
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
    while (i != graph.capacity - 1) {
        if (graph.graph[i].index == -1) {
            graph.graph[i] = *vNode;
            vNode->index = i;
            //找到空位并返回对应索引
            return vNode->index;
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
UEdge *createEdge(VNode *from, VNode *to, int weight) {
    UEdge *uEdge = malloc(sizeof(UEdge));
    uEdge->from = from;
    uEdge->to = to;
    uEdge->weight = weight;
    uEdge->next = NULL;
    return uEdge;
}

//一键找到边链表的最后的轮椅♿,帅!otto!
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
int addEdgeToAdjacencyList(VNode *from, VNode *to, int weight, int dir) {
    if (checkInList(to) < 0) {
        addNodeToAdjacencyList(to);
    }
    //新建一条edge并放入from节点存储edge的表的末尾
    //判断from是否已有UEdge节点,如果有就直接加入
    if (from->pEdge == NULL) {
        from->pEdge = createEdge(from, to, weight);
    } else {
        findLastGNode(from)->next = createEdge(from, to, weight);
    }
    //实现无向图双向边
    if (dir) {
        addEdgeToAdjacencyList(to, from, weight, 0);
    }
    return 1;
}

//广度遍历
int breathFirstSearch(int *arr, VNode *vNode) {
    arr[vNode->index] = 1;
    enQueue(vNode);
    UEdge *uEdge = vNode->pEdge;
    while (uEdge->next != NULL) {
        if (!arr[uEdge->to->index]) {
            enQueue(uEdge->to);
        }
        uEdge = uEdge->next;
    }
    if (!emptyOrNot()) {
        return 1;
    }
    breathFirstSearch(arr, deQueue()->vNode);
    free(vNode);
    return 1;
}

//深度遍历
int depthFirstSearch(int *arr, VNode *vNode) {
    arr[vNode->index] = 1;
    UEdge *uEdge = vNode->pEdge;
    while (uEdge->next != NULL) {
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
            breathFirstSearch(arr, &graph.graph[0]);
            break;
        case 1:
            depthFirstSearch(arr, &graph.graph[0]);
            break;
        default:
    }
    return 1;

}
