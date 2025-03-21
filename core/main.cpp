#include <stdio.h>
#include <Windows.h>
#include <process.h>
#include <graphics.h>  
#include <conio.h>  

extern void playAnimation(const char* frames[], int frameCount);
extern void keymove();
extern void character_move(IMAGE img);
volatile int exitFlag = 0;


/* 线程函数声明 */
void Thread1(void*);
void Thread2(void*);
void Thread3(void*);

/* 线程句柄 */
HANDLE h1, h2, h3;

/* 线程共享内存 */
volatile int i = 0;
//IMAGE buffer;
IMAGE background;

/* 主线程 */
int main()
{
	initgraph(1280, 720);
	loadimage(&background, "./bg.jpg", 1280, 720);
	//getimage(&buffer, 0, 0, 1280, 720); // 创建与窗口大小相同的图像
	//setwritemode(R2_COPYPEN); // 设置画笔模式为异或模式


	/* 创建线程 */
	h1 = (HANDLE)_beginthread(Thread1, 0, NULL);//线程1
	h2 = (HANDLE)_beginthread(Thread2, 0, NULL);//线程2
	h3 = (HANDLE)_beginthread(Thread3, 0, NULL);//线程3

	WaitForSingleObject(h1, INFINITE);//等待线程1结束
	WaitForSingleObject(h2, INFINITE);//等待线程2结束
	WaitForSingleObject(h3, INFINITE);//等待线程3结束

	closegraph();
	printf("主线程结束\n");
	return 0;
}


void Thread1(void* arg)  //线程1：渲染线程
{
	while (!exitFlag)
	{
		character_move(background);
	}
}

void Thread2(void* arg)  //线程2：键鼠控制
{
	while (!exitFlag)
	{
        keymove();
	}
}

void Thread3(void* arg)  //线程3：背景绘制
{
	
}