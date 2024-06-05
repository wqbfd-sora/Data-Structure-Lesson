//
// Created by KaguraSora on 5/21/2024.
//

#include "stdio.h"
#include "stdlib.h"


//˳���-��-���-��� (��
//˳���-��-��-��-�� (��
//����
typedef struct VNode {
    int index;
    //ָ����һ��
    struct edge *pEdge;
} VNode;

//��
//�洢�ߵ�ǰ��ڵ㷽���Ҳ���(�����д���һ��ȷ��
//next�����γ�����(������
//˫��߿������������ı߾Ͳ�������ظ������
//�洢��ͷ�Ľڵ㵥��Ϊ�˷����Ҳ���(�����ڴ治ҪǮ(�Ż�ʲô�Ĳ����ڵ�
typedef struct edge {
    VNode *from;
    VNode *to;
    int weight;
    struct edge *next;
} UEdge;

//�ڽӱ��ͷ
typedef struct graph {
    VNode *graph;
    int capacity;
} graphStruct;

//��Ա�����ڽӱ�
//���������һ��
graphStruct graph;

//��ȱ����õ�Queue
//д��������ʽ(
typedef struct QNode {
    VNode *vNode;
    struct QNode *next;
} QNode;
QNode head;

//�������нڵ�
QNode *createQNode(VNode *vNode) {
    QNode *qNode = malloc(sizeof(QNode));
    qNode->vNode = vNode;
    qNode->next = NULL;
    return qNode;
}

//�Ҷ�β
//�������һ���ڵ�
QNode *findLast() {
    QNode *qNode = &head;
    while (qNode->next != NULL) {
        qNode = qNode->next;
    }
    return qNode;
}

//�ж϶ӿ�
//0Ϊ��,1Ϊ�ǿ�
int emptyOrNot() {
    if (head.next == NULL) {
        return 0;
    }
    return 1;
}

//��ʼ������
int initQueue() {
    head.vNode = NULL;
    head.next = NULL;
    return 1;
}

//���
int enQueue(VNode *vNode) {
    QNode *qNode = findLast();
    qNode->next = createQNode(vNode);
    return 1;
}

//����
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

//���·���㷨�ýڵ�
//visit��ʾ����״̬��1Ϊ���ʹ���0Ϊδ����
typedef struct DNode {
    int visit;
    int distance;
    VNode *preVNode;
} DNode;

//�����ڽӱ��壬��ָ����С(�ڵ���)
graphStruct createGraph(int capacity) {
    graph.graph = malloc(capacity * sizeof(VNode));
    int i = 0;
    //�ֶ�������VNode����������ʼ����-1(ʲô��Ƿ�
    while (i != capacity) {
        graph.graph[i].index = -1;
        graph.graph[i].pEdge = NULL;
        i++;
    }
    //����˳���
    graph.capacity = capacity;
    return graph;
}


//���ڽӱ������δ��ӹ��Ľڵ�,��������ֵ
//������ֵΪ-1
int addNodeToAdjacencyList(VNode *vNode) {
    int i = 0;
    while (i < graph.capacity) {
        if (graph.graph[i].index == -1) {
            vNode->index = i;
            graph.graph[i] = *vNode;
            //�ҵ���λ�����ض�Ӧ����
            return i;
        }
        i++;
    }
    //�����ڽӱ�ʧ�ܷ��ظ�ֵ
    return -1;
}

//����ڽӱ����Ƿ��нڵ�,����з�������ֵ
//������ֵΪ-1
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

//��������ʼ���ڵ�
//������ֵΪ-1
//ֱ����ӽ��ڽӱ�
VNode *createNode() {
    VNode *vNode = malloc(sizeof(VNode));
    vNode->index = -1;
    vNode->pEdge = NULL;
    addNodeToAdjacencyList(vNode);
    return vNode;
}

//����edge��from�ڵ㴴������ʼ����
UEdge *createEdge(int fromIndex, int toIndex, int weight) {
    UEdge *uEdge = malloc(sizeof(UEdge));
    uEdge->from = &graph.graph[fromIndex];
    uEdge->to = &graph.graph[toIndex];
    uEdge->weight = weight;
    uEdge->next = NULL;
    return uEdge;
}

//һ���ҵ����������������?,˧!otto!
//���ⲻ���µ�VNodeû��UEdge������
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

//dir���ڱ�ʾ�ߵ���������0��ʾ����1��ʾ����(˫��)
//ͨ���ݹ����ʵ������ͼ(˫���)
int addEdgeToAdjacencyList(int fromIndex, int toIndex, int weight, int dir) {
    VNode *from = &graph.graph[fromIndex];
    VNode *to = &graph.graph[toIndex];
    if (checkInList(to) < 0) {
        addNodeToAdjacencyList(to);
    }
    //�½�һ��edge������from�ڵ�洢edge�ı��ĩβ
    //�ж�from�Ƿ�����UEdge�ڵ�,����о�ֱ�Ӽ���
    if (from->pEdge == NULL) {
        from->pEdge = createEdge(from->index, to->index, weight);
    } else {
        findLastGNode(from)->next = createEdge(from->index, to->index, weight);
    }
    //ʵ������ͼ˫���
    if (dir) {
        addEdgeToAdjacencyList(toIndex, fromIndex, weight, 0);
    }
    return 1;
}

//��ȱ���
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

//��ȱ���
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

//���ֱ�������ת����
//0ȥ��ȱ���
//1ȥ��ȱ���
//�񾭲�������Ҫ��ôд
//�ص���ô�������ͷ��=(
int traversalGraph(int type) {
    //�洢����״̬������
    //1Ϊ�Ѿ������ʹ�
    //0Ϊδ������
    int arr[graph.capacity];
    for (int i = 0; i < graph.capacity; ++i) {
        arr[i] = 0;
    }
    switch (type) {
        case 0:
            printf("������ȱ���:\n");
            initQueue();
            enQueue(graph.graph);
            breathFirstSearch(arr, &graph.graph[0]);
            printf("\n\n");
            break;
        case 1:
            printf("������ȱ���:\n");
            depthFirstSearch(arr, &graph.graph[0]);
            printf("\n\n");
            break;
        default:
    }
    return 1;

}

//������������㷨����������
int topologicalSort() {
    printf("�����������\n");
    traversalGraph(1);
    return 1;
}

//Dijkstra�㷨
//��һ����ȱ���,������Ȩ
int dijkstra(DNode *dis, VNode *vNode) {
    UEdge *uEdge = vNode->pEdge;
    while (uEdge != NULL) {
        //��¼��ʱ�洢�Ӵ˽ڵ㵽��̵ľ���ֵ,�������бȽ�
        int TDis = dis[vNode->index].distance + uEdge->weight;
        //δ���ʹ��ͽ���ʱֵ��Ϊ��ֵ,����¼��ǰ�ڵ�Ϊǰ��
        if (dis[uEdge->to->index].visit == 0) {
            enQueue(uEdge->to);
            dis[uEdge->to->index].distance = TDis;
            dis[uEdge->to->index].preVNode = vNode;
            dis[uEdge->to->index].visit = 1;
        } else {
            //���ʹ����жϺ�̽ڵ�ľ���ֵ����ʱֵ���бȽ�,��ѡ��С�ĸ�ֵ����¼ǰ���ڵ�
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

//Dijkstra�㷨ǰ��
int preDijkstra() {
    printf("Dijkstra�㷨\n");
    DNode dis[graph.capacity];
    //����ֵ
    for (int i = 0; i < graph.capacity; ++i) {
        dis[i].visit = 0;
        dis[i].preVNode = &graph.graph[i];
    }
    initQueue();
    enQueue(graph.graph);
    dis[0].distance = 0;
    dijkstra(dis, dis->preVNode);
    //��ӡ���·����ǰ��
    for (int i = 1; i < graph.capacity; ++i) {
        printf("�ڵ�:%d->[%d,%d]  ", i + 1, dis[i].preVNode->index + 1, dis[i].distance);
    }
    printf("\n");
    return 1;
}

//��ӡ�ڽӱ�
//��Ҫ��ӡ����
//��->�ָ�
//^��β
int printAdjacencyList() {
    printf("��ӡ�ڽӱ�\n");
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

//���ڽӱ���������
//����ͼ
int initialGraph() {
    createGraph(5);
    //��ӽڵ�
    createNode();//0
    createNode();//1
    createNode();//2
    createNode();//3
    createNode();//4
    //��ӱ�
    //1�ڵ�ı�
    addEdgeToAdjacencyList(0, 1, 4, 0);
    addEdgeToAdjacencyList(0, 3, 5, 0);
    //2�ڵ�ı�
    addEdgeToAdjacencyList(1, 4, 1, 0);
    addEdgeToAdjacencyList(1, 2, 3, 0);
    //3�ڵ�ı�
    //4�ڵ�ı�
    addEdgeToAdjacencyList(3, 2, 2, 0);
    //5�ڵ�ı�
    addEdgeToAdjacencyList(4, 2, 3, 0);
    return 0;
}

