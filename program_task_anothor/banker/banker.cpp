#include <iostream>
#include <iomanip>
using namespace std;

//全局变量定义
int Available[100];     //可利用资源数组
int Max[50][100];       //最大需求矩阵
int Allocation[50][100];//分配矩阵
int Need[50][100];      //需求矩阵
int Request[50][100];   //M个进程还需要N类资源的资源量
bool Finish[50];
int p[50];
int m, n;               //M个进程，N类资源

//安全性算法
int Safe()
{
    int i, j, k, l = 0;
    int Work[100];
    for(i = 0; i < n; i++)
        Work[i] = Available[i];
    for(i = 0; i < m; i++)
        Finish[i] = false;
    for(i = 0; i < m; i++)
    {
        if(Finish[i] == true)
            continue;
        for(j = 0; j < n; j++)
        {
            if(Need[i][j] > Work[j])
                break;
        }
        if(j != n)
            continue;   //不满足Need < Work
        Finish[i] = true;
        for(k = 0; k < n; k++)
            Work[k] += Allocation[i][k];
        p[l++] = i;
        i = -1;        
    }

    if(l == m)
    {
        cout << "系统是安全的" << endl;
        cout << "安全序列：";
        for(i = 0; i < l; i++)
        {
            cout << "[" << p[i] << "] ";
        }
        cout << endl;
        return true;
    }
    else
    {
        cout << "安全序列不存在" << endl;
        return false;
    }
}

// Banker's Algorithm
int main()
{
    int i, j, mi;

    // 定义进程的数目和资源的种类
    m = 5;
    n = 4;
    // 定义最大需求矩阵
    int tmp[5][4] = {
        {0, 0, 1, 2},
        {1, 7, 5, 0},
        {2, 3, 5, 6},
        {0, 5, 6, 2},
        {0, 6, 5, 6}
    };
    // 定义分配矩阵
    int tmp2[5][4] = {
        {0, 0, 1, 2},
        {1, 0, 0, 0},
        {1, 3, 5, 4},
        {0, 6, 3, 2},
        {0, 0, 1, 4}
    };
    // 定义可利用资源向量
    int tmp3[4] = {1, 5, 2, 0};

    for(i = 0; i < m; i++)
    {
        Available[i] = tmp3[i];
        for(j = 0; j < n; j++)
        {
            Max[i][j] = tmp[i][j];
            Allocation[i][j] = tmp2[i][j];
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
    
    // 输出当前状态
    cout << "[Max]" << endl;
    for(i = 0; i < m; i++)
    {
        cout << "\t";
        for(j = 0; j < n; j++)
            cout << setw(5) << Max[i][j];
        cout << endl;
    }
    cout << "[Allocation]" << endl;
    for(i = 0; i < m; i++)
    {
        cout << "\t";
        for(j = 0; j < n; j++)
            cout << setw(5) << Allocation[i][j];
        cout << endl;
    }
    cout << "[Need]" << endl;
    for(i = 0; i < m; i++)
    {
        cout << "\t";
        for(j = 0; j < n; j++)
            cout << setw(5) << Need[i][j];
        cout << endl;
    }
    cout << "[Avaliable]" << endl;
    for(j = 0; j < n; j++)
        cout << setw(5) << Available[j];
    cout << endl;
    // 判断当前系统状态是否安全
    if(!Safe())
    {
        cout << "系统不安全" << endl;
        return -1;
    }
    while(1)
    {
        cout << "输入要申请资源的进程号：" << endl;
        cin >> mi;
        cout << "输入进程所请求的各个资源的数量" << endl;
        for(i = 0; i < n; i++)
            cin >> Request[mi][i];
        bool flag = false;
        for(i = 0; i < n; i++)
        {
            if(Request[mi][i] > Need[mi][i])
            {
                cout << "所请求资源数超过进程所宣布的最大值" << endl;
                flag = true;
                break;
            }
            if(Request[mi][i] > Available[i])
            {
                cout << "无足够资源满足进程需求" << endl;
                flag = true;
                break;
            }
        }
        if(flag == true)
            continue;
        for(i = 0; i < n; i++)
        {
            Available[i] -= Request[mi][i];
            Allocation[mi][i] += Request[mi][i];
            Need[mi][i] -= Request[mi][i];
        }
        if(Safe())
        {
            cout << "同意分配请求" << endl;
        }
        else
        {
            cout << "拒绝分配请求" << endl;
            for(i = 0; i < n; i++)
            {
                Available[i] += Request[mi][i];
                Allocation[mi][i] -= Request[mi][i];
                Need[mi][i] += Request[mi][i];
            }
        }
        char c;
        cout << "是否再次请求分配？y/n" << endl;
        while(1)
        {
            cin >> c;
            if(c == 'Y' || c == 'y')
            {
                break;
            }
            else if(c == 'N' || c == 'n')
            {
                cout << "Bye!" << endl;
                return 0;
            }
            else
            {
                cout << "请输入y/n" << endl;
                continue;
            }
        }
    }

    return 0;
}