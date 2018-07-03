#include <Windows.h>
#include <process.h>
#include <iostream>
#include <time.h>
using namespace std;

#define P(S) WaitForSingleObject(S, INFINITE)
#define V(S) ReleaseSemaphore(S, 1, NULL)
// Fmutex ����д�߻���
HANDLE Mut1, Mut2, Wmutex, Fmutex;
int Rcount = 0;
int Wcount = 0;

DWORD WINAPI writer()
{
	DWORD id = GetCurrentThreadId();

	cout << "[" << id << "]\t\t��д�߳���" << "\tд��������" << Wcount << endl;
	P(Mut1);
	Wcount += 1;
	if (Wcount == 1)
		P(Fmutex);
	V(Mut1);

	P(Wmutex);
	cout << "[" << id << "]\t\tд�߿�ʼд" << endl;
	Sleep(2000);
	cout << "[" << id << "]\t\tд�߽���д" << endl;
	V(Wmutex);

	P(Mut1);
	Wcount -= 1;
	if (Wcount == 0)
	{
		cout << "[" << id << "]\t\t��д�ߣ����Զ�" << endl;
		V(Fmutex);
	}
	V(Mut1);

	return 1;
}

DWORD WINAPI reader()
{
	DWORD id = GetCurrentThreadId();

	cout << "[" << id << "]\t\t�¶��߳���" << endl;
	
	P(Mut1);
	V(Mut1);

	P(Mut2);
	Rcount += 1;
	if (Rcount == 1)
		P(Fmutex);
	V(Mut2);

	cout << "[" << id << "]\t\t���߿�ʼ��" << endl;
	Sleep(500);
	cout << "[" << id << "]\t\t���߽�����" << endl;

	P(Mut2);
	Rcount -= 1;
	if (Rcount == 0)
	{
		cout << "[" << id << "]\t\tд�ſ���д" << endl;
		V(Fmutex);
	}
	V(Mut2);

	return 1;
}

int main()
{
	Wmutex = CreateSemaphore(NULL, 1, 1, NULL);
	Fmutex = CreateSemaphore(NULL, 1, 1, NULL);
	Mut1 = CreateSemaphore(NULL, 1, 1, NULL);
	Mut2 = CreateSemaphore(NULL, 1, 1, NULL);

	// srand((unsigned)time(NULL));
	srand(90);

	while (true)
	{
		Sleep(500);
		
		int rC = rand() % 1000;
		if (rC % 6 == 0)
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)writer, NULL, NULL, NULL);
		else
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)reader, NULL, NULL, NULL);
	}

	return 0;
}