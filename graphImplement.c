//
// Created by KaguraSora on 5/21/2024.
//

#include "graphTool.h"

//深度遍历，广度遍历
//拓扑排序，连通图算法(两种)

//以邻接表形式写的图
//为了美观所有图实现和排序的实现的代码都仍在graphTool.h这个头文件下了

//这么简单的main函数一定是调包侠罢(乐

int main() {
    //图的基本功能
    //初始化图＆打印邻接表
    initialGraph();
    printAdjacencyList();
    //两种遍历方式
    traversalGraph(1);
    traversalGraph(0);
    //拓扑排序
    topologicalSort();

    //单源最短路径算法
    preDijkstra();

    return 0;
}
