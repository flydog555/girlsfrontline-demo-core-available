#include <stdio.h>
#include <Windows.h>
#include <process.h>
#include <graphics.h>  
#include <conio.h>  


extern void keymove();
extern void character_move();
extern void ui_process();
extern void fire();
extern void fire_rander();
extern void enemy_data();
extern void enemy_show();


volatile int exitFlag = 0;


/* �̺߳������� */
void Thread1(void*);
void Thread2(void*);
void Thread3(void*);
void Thread4(void*);
void Thread5(void*);
void Thread6(void*);
void Thread7(void*);

/* �߳̾�� */
HANDLE h1, h2, h3, h4, h5, h6, h7;

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
	h5 = (HANDLE)_beginthread(Thread5, 0, NULL);//�߳�5
	h6 = (HANDLE)_beginthread(Thread6, 0, NULL);//�߳�6
	h7 = (HANDLE)_beginthread(Thread7, 0, NULL);//�߳�7

	WaitForSingleObject(h1, INFINITE);//�ȴ��߳�1����
	WaitForSingleObject(h2, INFINITE);//�ȴ��߳�2����
	WaitForSingleObject(h3, INFINITE);//�ȴ��߳�3����
	WaitForSingleObject(h4, INFINITE);//�ȴ��߳�4����
	WaitForSingleObject(h5, INFINITE);//�ȴ��߳�5����
	WaitForSingleObject(h6, INFINITE);//�ȴ��߳�6����
	WaitForSingleObject(h7, INFINITE);//�ȴ��߳�7����

	cleardevice();
	printf("You are killed");
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
	////������ʾ�����
	//while (1)
	//{
	//	for (int i = 0; i <= 36; i++)
	//	{
	//		line(0, 20 * i, 1280, 20 * i);
	//	}
	//	for (int i = 0; i <= 64; i++)
	//	{
	//		line(20 * i, 0, 20 * i, 720);
	//	}
	//}
	
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
	while (!exitFlag)
	{
		ui_process();
		Sleep(10);
	}
}

void Thread4(void* arg)  //�߳�4���ӵ����ݴ����߳�
{
	while (!exitFlag)
	{
		fire();
	}
}

void Thread5(void* arg)
{
	while (!exitFlag)
	{
		fire_rander();
	}
}

void Thread6(void* arg)  //�߳�5���������ݴ����߳�
{
	while (!exitFlag)
	{
		enemy_data();
	}
}

void Thread7(void* arg)  //�߳�6�����˶��������߳�
{
	while (!exitFlag)
	{
		enemy_show();
	}
}