#include <stdio.h>
#include <Windows.h>
#include <process.h>
#include <graphics.h>  
#include <conio.h>  

extern void playAnimation(const char* frames[], int frameCount);
extern void keymove();
extern void character_move(IMAGE img);
volatile int exitFlag = 0;


/* �̺߳������� */
void Thread1(void*);
void Thread2(void*);
void Thread3(void*);

/* �߳̾�� */
HANDLE h1, h2, h3;

/* �̹߳����ڴ� */
volatile int i = 0;
//IMAGE buffer;
IMAGE background;

/* ���߳� */
int main()
{
	initgraph(1280, 720);
	loadimage(&background, "./bg.jpg", 1280, 720);
	//getimage(&buffer, 0, 0, 1280, 720); // �����봰�ڴ�С��ͬ��ͼ��
	//setwritemode(R2_COPYPEN); // ���û���ģʽΪ���ģʽ


	/* �����߳� */
	h1 = (HANDLE)_beginthread(Thread1, 0, NULL);//�߳�1
	h2 = (HANDLE)_beginthread(Thread2, 0, NULL);//�߳�2
	h3 = (HANDLE)_beginthread(Thread3, 0, NULL);//�߳�3

	WaitForSingleObject(h1, INFINITE);//�ȴ��߳�1����
	WaitForSingleObject(h2, INFINITE);//�ȴ��߳�2����
	WaitForSingleObject(h3, INFINITE);//�ȴ��߳�3����

	closegraph();
	printf("���߳̽���\n");
	return 0;
}


void Thread1(void* arg)  //�߳�1����Ⱦ�߳�
{
	while (!exitFlag)
	{
		character_move(background);
	}
}

void Thread2(void* arg)  //�߳�2���������
{
	while (!exitFlag)
	{
        keymove();
	}
}

void Thread3(void* arg)  //�߳�3����������
{
	
}