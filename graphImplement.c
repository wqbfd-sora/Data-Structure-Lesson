//
// Created by KaguraSora on 5/21/2024.
//

#include "graphTool.h"

//��ȱ�������ȱ���
//����������ͨͼ�㷨(����)

//���ڽӱ���ʽд��ͼ
//Ϊ����������ͼʵ�ֺ������ʵ�ֵĴ��붼����graphTool.h���ͷ�ļ�����

//��ô�򵥵�main����һ���ǵ�������(��

int main() {
    //ͼ�Ļ�������
    //��ʼ��ͼ����ӡ�ڽӱ�
    initialGraph();
    printAdjacencyList();
    //���ֱ�����ʽ
    traversalGraph(1);
    traversalGraph(0);
    //��������
    topologicalSort();

    //��Դ���·���㷨
    preDijkstra();

    return 0;
}
