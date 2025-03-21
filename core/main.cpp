#include <stdio.h>
#include <Windows.h>
#include <process.h>
#include <graphics.h>  
#include <conio.h>  

extern void keymove();
extern void character_move();
extern void ui_process();
extern void fire();
volatile int exitFlag = 0;


/* �̺߳������� */
void Thread1(void*);
void Thread2(void*);
void Thread3(void*);
void Thread4(void*);

/* �߳̾�� */
HANDLE h1, h2, h3,h4;

/* �̹߳����ڴ� */
volatile int i = 0;
//IMAGE buffer;




/* ���߳� */
int main()
{
	initgraph(1280, 720);
	//setwritemode(R2_COPYPEN); // ���û���ģʽΪ���ģʽ

	/* �����߳� */
	h1 = (HANDLE)_beginthread(Thread1, 0, NULL);//�߳�1
	h2 = (HANDLE)_beginthread(Thread2, 0, NULL);//�߳�2
	h3 = (HANDLE)_beginthread(Thread3, 0, NULL);//�߳�3
	h4 = (HANDLE)_beginthread(Thread4, 0, NULL);//�߳�4

	WaitForSingleObject(h1, INFINITE);//�ȴ��߳�1����
	WaitForSingleObject(h2, INFINITE);//�ȴ��߳�2����
	WaitForSingleObject(h3, INFINITE);//�ȴ��߳�3����
	WaitForSingleObject(h4, INFINITE);//�ȴ��߳�4����

	closegraph();
	printf("���߳̽���\n");
	return 0;
}


void Thread1(void* arg)  //�߳�1����Ⱦ�߳�
{
	while (!exitFlag)
	{
		character_move();
	}
}

void Thread2(void* arg)  //�߳�2���������
{
	while (!exitFlag)
	{
        keymove();
	}
}

void Thread3(void* arg)  //�߳�3�����ݴ����߳�
{
	while (true)
	{
		ui_process();
		Sleep(10);
	}
}

void Thread4(void* arg)  //�߳�4���ӵ����ݴ����߳�
{
	while (true)
	{
		fire();
	}
}