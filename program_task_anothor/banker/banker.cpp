#include <iostream>

//全局变量定义
int Available[100];     //可利用资源数组
int Max[50][100];       //最大需求矩阵
int Allocation[50][100];//分配矩阵
int Need[50][100];      //需求矩阵
int Request[50][100];   //M个进程还需要N类资源的资源量
