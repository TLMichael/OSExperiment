#include <iostream>
#include <iomanip>
using namespace std;

//ȫ�ֱ�������
int Available[100];     //��������Դ����
int Max[50][100];       //����������
int Allocation[50][100];//�������
int Need[50][100];      //�������
int Request[50][100];   //M�����̻���ҪN����Դ����Դ��
bool Finish[50];
int p[50];
int m, n;               //M�����̣�N����Դ

//��ȫ���㷨
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
            continue;   //������Need < Work
        Finish[i] = true;
        for(k = 0; k < n; k++)
            Work[k] += Allocation[i][k];
        p[l++] = i;
        i = -1;        
    }

    if(l == m)
    {
        cout << "ϵͳ�ǰ�ȫ��" << endl;
        cout << "��ȫ���У�";
        for(i = 0; i < l; i++)
        {
            cout << "[" << p[i] << "] ";
        }
        cout << endl;
        return true;
    }
    else
    {
        cout << "��ȫ���в�����" << endl;
        return false;
    }
}

// Banker's Algorithm
int main()
{
    int i, j, mi;

    // ������̵���Ŀ����Դ������
    m = 5;
    n = 3;
    // ��������������
    int tmp[5][3] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    // ����������
    int tmp2[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
    // �����������Դ����
    int tmp3[3] = {3, 3, 2};

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
    
    // �����ǰ״̬
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
    // �жϵ�ǰϵͳ״̬�Ƿ�ȫ
    if(!Safe())
    {
        cout << "ϵͳ����ȫ" << endl;
        return -1;
    }
    while(1)
    {
        cout << "����Ҫ������Դ�Ľ��̺ţ�" << endl;
        cin >> mi;
        cout << "�������������ĸ�����Դ������" << endl;
        for(i = 0; i < n; i++)
            cin >> Request[mi][i];
        for(i = 0; i < n; i++)
        {
            if(Request[mi][i] > Need[mi][i])
            {
                cout << "��������Դ���������������������ֵ" << endl;
                return -1;
            }
            if(Request[mi][i] > Available[i])
            {
                cout << "���㹻��Դ�����������" << endl;
                return -1;
            }
        }
        for(i = 0; i < n; i++)
        {
            Available[i] -= Request[mi][i];
            Allocation[mi][i] += Request[mi][i];
            Need[mi][i] -= Request[mi][i];
        }
        if(Safe())
        {
            cout << "ͬ���������" << endl;
        }
        else
        {
            cout << "�ܾ���������" << endl;
            for(i = 0; i < n; i++)
            {
                Available[i] += Request[mi][i];
                Allocation[mi][i] -= Request[mi][i];
                Need[mi][i] += Request[mi][i];
            }
        }
        char c;
        cout << "�Ƿ��ٴ�������䣿y/n" << endl;
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
                cout << "������y/n" << endl;
                continue;
            }
        }
    }

    return 0;
}