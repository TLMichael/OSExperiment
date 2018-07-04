#include <Windows.h>
#include <process.h>
#include <iostream>
#include <time.h>
using namespace std;

#define P(S) WaitForSingleObject(S, INFINITE)
#define V(S) ReleaseSemaphore(S, 1, NULL)
// Fmutex 	读者写者互斥
// Wmutex 	写者互斥
// Mut1		Rcount互斥 && 竞争Fmutex
// Mut2		Wcount互斥
HANDLE Mut1, Mut2, Wmutex, Fmutex;
int Rcount = 0;
int Wcount = 0;

DWORD WINAPI writer()
{
	DWORD id = GetCurrentThreadId();

	cout << "[" << id << "]\t\t新写者出现" << "\t写者数量：" << Wcount << endl;
	P(Mut1);
	Wcount += 1;
	if (Wcount == 1)
		P(Fmutex);		// 如果有读者，写者阻塞在此处
	V(Mut1);

	P(Wmutex);
	cout << "[" << id << "]\t\t写者开始写" << endl;
	Sleep(2000);
	cout << "[" << id << "]\t\t写者结束写" << endl;
	V(Wmutex);

	P(Mut1);
	Wcount -= 1;
	if (Wcount == 0)
	{
		cout << "[" << id << "]\t\t无写者，可以读" << endl;
		V(Fmutex);
	}
	V(Mut1);

	return 1;
}

DWORD WINAPI reader()
{
	DWORD id = GetCurrentThreadId();

	cout << "[" << id << "]\t\t新读者出现" << endl;
	
	P(Mut1);	// 读者要先申请Mut1，如果有写者在等待Fmutex，则读者被阻塞，写者优先
	V(Mut1);	// 立即释放Mut1，使写者可以随时申请到Mut1

	P(Mut2);
	Rcount += 1;
	if (Rcount == 1)
		P(Fmutex);	// 第一个读者进入时，申请Fmutex；如果有写者，则第一个读者会阻塞在此处
	V(Mut2);

	cout << "[" << id << "]\t\t读者开始读" << endl;
	Sleep(500);
	cout << "[" << id << "]\t\t读者结束读" << endl;

	P(Mut2);
	Rcount -= 1;
	if (Rcount == 0)
	{
		cout << "[" << id << "]\t\t写着可以写" << endl;
		V(Fmutex);		// 最后一个读者退出时，释放Fmutex
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