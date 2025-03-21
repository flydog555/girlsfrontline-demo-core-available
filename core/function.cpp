#define _CRT_SECURE_NO_WARNINGS 1
#include <graphics.h> 
#include <easyx.h>
#include <conio.h>  
#include <stdio.h>  
#include <math.h>
#include <time.h>
#pragma comment( lib, "MSIMG32.LIB")
#pragma comment(lib,"winmm.lib")

//人物位置
int x = 100;
int y = 100;
int* px = &x;
int* py = &y;
//检测键鼠状态变化标志
int sign = 0;  
int* psign = &sign;  //将sign指针化
//鼠标追踪
int mx = 100;
int my = 100;
int* pmx = &mx;//鼠标的实时x坐标
int* pmy = &my;//鼠标的实时y坐标
//帧率控制
int anime_fps = 30; // 动画播放帧率
int start_time_anime = 0;
int frame_time_anime = 0;
//ui显示
int killed_number = 10;  //击杀计数
char killed_number_display[20];
int lv = 1; //等级
char lv_display[20];
//int live = 3;
//char lv_live[20];

//动画帧加载
const char* frames_run_left[] = {
    "./resource/character/HK416/run_left/(1).png",
    "./resource/character/HK416/run_left/(2).png",
    "./resource/character/HK416/run_left/(3).png",
    "./resource/character/HK416/run_left/(4).png",
    "./resource/character/HK416/run_left/(5).png",
    "./resource/character/HK416/run_left/(6).png",
    "./resource/character/HK416/run_left/(7).png",
    "./resource/character/HK416/run_left/(8).png",
    "./resource/character/HK416/run_left/(9).png",
    "./resource/character/HK416/run_left/(10).png",
    "./resource/character/HK416/run_left/(11).png",
    "./resource/character/HK416/run_left/(12).png",
    "./resource/character/HK416/run_left/(13).png",
    "./resource/character/HK416/run_left/(14).png",
    "./resource/character/HK416/run_left/(15).png",
    "./resource/character/HK416/run_left/(16).png",
    "./resource/character/HK416/run_left/(17).png",
    "./resource/character/HK416/run_left/(18).png",
    "./resource/character/HK416/run_left/(19).png",
    "./resource/character/HK416/run_left/(20).png",
    "./resource/character/HK416/run_left/(21).png",
    "./resource/character/HK416/run_left/(22).png",
    "./resource/character/HK416/run_left/(23).png",
    "./resource/character/HK416/run_left/(24).png"
};
const char* frames_run_right[] = {
    "./resource/character/HK416/run_right/(1).png",
    "./resource/character/HK416/run_right/(2).png",
    "./resource/character/HK416/run_right/(3).png",
    "./resource/character/HK416/run_right/(4).png",
    "./resource/character/HK416/run_right/(5).png",
    "./resource/character/HK416/run_right/(6).png",
    "./resource/character/HK416/run_right/(7).png",
    "./resource/character/HK416/run_right/(8).png",
    "./resource/character/HK416/run_right/(9).png",
    "./resource/character/HK416/run_right/(10).png",
    "./resource/character/HK416/run_right/(11).png",
    "./resource/character/HK416/run_right/(12).png",
    "./resource/character/HK416/run_right/(13).png",
    "./resource/character/HK416/run_right/(14).png",
    "./resource/character/HK416/run_right/(15).png",
    "./resource/character/HK416/run_right/(16).png",
    "./resource/character/HK416/run_right/(17).png",
    "./resource/character/HK416/run_right/(18).png",
    "./resource/character/HK416/run_right/(19).png",
    "./resource/character/HK416/run_right/(20).png",
    "./resource/character/HK416/run_right/(21).png",
    "./resource/character/HK416/run_right/(22).png",
    "./resource/character/HK416/run_right/(23).png",
    "./resource/character/HK416/run_right/(24).png"
};
const char* frames_wait_left[] = {
    "./resource/character/HK416/wait_left/(1).png",
    "./resource/character/HK416/wait_left/(2).png",
    "./resource/character/HK416/wait_left/(3).png",
    "./resource/character/HK416/wait_left/(4).png",
    "./resource/character/HK416/wait_left/(5).png",
    "./resource/character/HK416/wait_left/(6).png",
    "./resource/character/HK416/wait_left/(7).png",
    "./resource/character/HK416/wait_left/(8).png",
    "./resource/character/HK416/wait_left/(9).png",
    "./resource/character/HK416/wait_left/(10).png",
    "./resource/character/HK416/wait_left/(11).png",
    "./resource/character/HK416/wait_left/(12).png",
    "./resource/character/HK416/wait_left/(13).png",
    "./resource/character/HK416/wait_left/(14).png",
    "./resource/character/HK416/wait_left/(15).png",
    "./resource/character/HK416/wait_left/(16).png",
    "./resource/character/HK416/wait_left/(17).png",
    "./resource/character/HK416/wait_left/(18).png",
    "./resource/character/HK416/wait_left/(19).png",
    "./resource/character/HK416/wait_left/(20).png",
    "./resource/character/HK416/wait_left/(21).png",
    "./resource/character/HK416/wait_left/(22).png",
    "./resource/character/HK416/wait_left/(23).png",
    "./resource/character/HK416/wait_left/(24).png",
    "./resource/character/HK416/wait_left/(25).png",
    "./resource/character/HK416/wait_left/(26).png",
    "./resource/character/HK416/wait_left/(27).png",
    "./resource/character/HK416/wait_left/(28).png",
    "./resource/character/HK416/wait_left/(29).png",
    "./resource/character/HK416/wait_left/(30).png",
    "./resource/character/HK416/wait_left/(31).png",
    "./resource/character/HK416/wait_left/(32).png",
    "./resource/character/HK416/wait_left/(33).png",   
    "./resource/character/HK416/wait_left/(34).png",
    "./resource/character/HK416/wait_left/(35).png",
    "./resource/character/HK416/wait_left/(36).png",
    "./resource/character/HK416/wait_left/(37).png",
    "./resource/character/HK416/wait_left/(38).png",
    "./resource/character/HK416/wait_left/(39).png",
    "./resource/character/HK416/wait_left/(40).png",
    "./resource/character/HK416/wait_left/(41).png",
    "./resource/character/HK416/wait_left/(42).png",
    "./resource/character/HK416/wait_left/(43).png",
    "./resource/character/HK416/wait_left/(44).png",
    "./resource/character/HK416/wait_left/(45).png",
    "./resource/character/HK416/wait_left/(46).png",
    "./resource/character/HK416/wait_left/(47).png",
    "./resource/character/HK416/wait_left/(48).png",
    "./resource/character/HK416/wait_left/(49).png",
    "./resource/character/HK416/wait_left/(50).png",
    "./resource/character/HK416/wait_left/(51).png",
    "./resource/character/HK416/wait_left/(52).png",
    "./resource/character/HK416/wait_left/(53).png",
    "./resource/character/HK416/wait_left/(54).png"

};
const char* frames_wait_right[] = {
    "./resource/character/HK416/wait_right/(1).png",
    "./resource/character/HK416/wait_right/(2).png",
    "./resource/character/HK416/wait_right/(3).png",
    "./resource/character/HK416/wait_right/(4).png",
    "./resource/character/HK416/wait_right/(5).png",
    "./resource/character/HK416/wait_right/(6).png",
    "./resource/character/HK416/wait_right/(7).png",
    "./resource/character/HK416/wait_right/(8).png",
    "./resource/character/HK416/wait_right/(9).png",
    "./resource/character/HK416/wait_right/(10).png",
    "./resource/character/HK416/wait_right/(11).png",
    "./resource/character/HK416/wait_right/(12).png",
    "./resource/character/HK416/wait_right/(13).png",
    "./resource/character/HK416/wait_right/(14).png",
    "./resource/character/HK416/wait_right/(15).png",
    "./resource/character/HK416/wait_right/(16).png",
    "./resource/character/HK416/wait_right/(17).png",
    "./resource/character/HK416/wait_right/(18).png",
    "./resource/character/HK416/wait_right/(19).png",
    "./resource/character/HK416/wait_right/(20).png",
    "./resource/character/HK416/wait_right/(21).png",
    "./resource/character/HK416/wait_right/(22).png",
    "./resource/character/HK416/wait_right/(23).png",
    "./resource/character/HK416/wait_right/(24).png",
    "./resource/character/HK416/wait_right/(25).png",
    "./resource/character/HK416/wait_right/(26).png",
    "./resource/character/HK416/wait_right/(27).png",
    "./resource/character/HK416/wait_right/(28).png",
    "./resource/character/HK416/wait_right/(29).png",
    "./resource/character/HK416/wait_right/(30).png",
    "./resource/character/HK416/wait_right/(31).png",
    "./resource/character/HK416/wait_right/(32).png",
    "./resource/character/HK416/wait_right/(33).png",
    "./resource/character/HK416/wait_right/(34).png",
    "./resource/character/HK416/wait_right/(35).png",
    "./resource/character/HK416/wait_right/(36).png",
    "./resource/character/HK416/wait_right/(37).png",
    "./resource/character/HK416/wait_right/(38).png",
    "./resource/character/HK416/wait_right/(39).png",
    "./resource/character/HK416/wait_right/(40).png",
    "./resource/character/HK416/wait_right/(41).png",
    "./resource/character/HK416/wait_right/(42).png",
    "./resource/character/HK416/wait_right/(43).png",
    "./resource/character/HK416/wait_right/(44).png",
    "./resource/character/HK416/wait_right/(45).png",
    "./resource/character/HK416/wait_right/(46).png",
    "./resource/character/HK416/wait_right/(47).png",
    "./resource/character/HK416/wait_right/(48).png",
    "./resource/character/HK416/wait_right/(49).png",
    "./resource/character/HK416/wait_right/(50).png",
    "./resource/character/HK416/wait_right/(51).png",
    "./resource/character/HK416/wait_right/(52).png",
    "./resource/character/HK416/wait_right/(53).png",
    "./resource/character/HK416/wait_right/(54).png",
};

//自定义函数的声明
void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
void playAnimation(const char* frames[], int frameCount, int a);
void draw_background();
void drawProgressBar(int x, int y, int progress, int total);


//自定义函数的定义
void playAnimation(const char* frames[], int frameCount,int a,IMAGE bgimg)  //主渲染函数
{
    IMAGE img;
    settextstyle(35, 0, "黑体");
    for (int i = 0; i < frameCount; i++)
    {
        cleardevice(); // 清除屏幕
        start_time_anime = clock();
        if (*psign != a)
        {
            //printf("break\n");
            break;
        }
        BeginBatchDraw();
        //加载背景
        putimage(0, 0, &bgimg);  
        //加载ui
        drawProgressBar(240, 10, /*killed_number * 100 - lv * 1000*/ 500, 1000);
        setbkmode(TRANSPARENT);
        outtextxy(640, 50, killed_number_display);
        outtextxy(240, 50, lv_display);
        //outtextxy(100, 50, lv_live);
        //加载射击线 
        setcolor(WHITE);
        setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
        circle(*pmx, *pmy, 20);
        setlinecolor(WHITE);
        setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 3);
        line(*pmx, *pmy, *px + 170, *py + 170);
        //加载当前帧图像
        loadimage(&img, frames[i]);   
        transparentimage3(NULL, *px, *py, &img);
        EndBatchDraw();
        frame_time_anime = clock() - start_time_anime;
        if (i != frameCount - 1)
        {
            if (anime_fps - frame_time_anime > 0)
            {
                Sleep(anime_fps - frame_time_anime);
                
            }
        }
    }
}

void character_move(IMAGE img)
{
    if(*psign == 0)
    {
        playAnimation(frames_wait_left, sizeof(frames_wait_left) / sizeof(frames_wait_left[0]), *psign, img);
    }
    if(*psign == 10)
    {
        playAnimation(frames_wait_right, sizeof(frames_wait_right) / sizeof(frames_wait_right[0]), *psign, img);
    }

    if (*psign == 1)
    {
        
        playAnimation(frames_run_right, sizeof(frames_run_right) / sizeof(frames_run_right[0]), *psign, img);
    }
    if (*psign == 2)
    {
        playAnimation(frames_run_left, sizeof(frames_run_left) / sizeof(frames_run_left[0]), *psign, img);
    }
    //playAnimation(frames_run_left, sizeof(frames_run_left) / sizeof(frames_run_left[0]), *psign);
}

void keymove()
{
    
    //*psign = 0;
    if (!_kbhit())
    {
        if (*pmx < *px) // 检查是否鼠标在小人左侧
        {
            *psign = 0;
        }
        if (*pmx > *px) // 检查是否鼠标在小人右侧
        {
            *psign = 10;
        }
    }
    
     //检测键盘状态  
    if (GetAsyncKeyState('W') < 0) // 使用字符常量代替VK_W 
    {
        *py -= 10;
        //printf("W\n");
        *psign = 1;
    }
    if (GetAsyncKeyState('S') < 0) // 使用字符常量代替VK_S  
    {
        *py += 10;
        //printf("S\n");
        *psign = 2;
    }
    if (GetAsyncKeyState('A') < 0) // 使用字符常量代替VK_A  
    {
        *px -= 10;
        //printf("A\n");
        *psign = 2;
    }
    if (GetAsyncKeyState('D') < 0) // 使用字符常量代替VK_D  
    {
        *px += 10;
        //printf("D\n");
        *psign = 1;
    }

    // 边界检查
    if (*px < -100)
    {
        *px = -100;
    }

    if (*px > 1280 - 260)
    {
        *px = 1280 - 260;
    }

    if (*py < -100)
    {
        *py = -100;
    }

    if (*py > 720 - 270)
    {
        *py = 720 - 270; // 假设帧高度为100
    }

    Sleep(50); // 控制检查的刷新频率
}

void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
{
    HDC dstDC = GetImageHDC(dstimg);
    HDC srcDC = GetImageHDC(srcimg);
    int w = srcimg->getwidth();
    int h = srcimg->getheight();
    BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
    AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}

void drawProgressBar(int x, int y, int progress, int total)
{
    // 计算进度条的宽度  
    int barWidth = 800; // 进度条的总宽度  
    int barHeight = 30; // 进度条的高度  
    int filledWidth = (progress * barWidth) / total; // 已填充的宽度  
    // 设置进度条的背景颜色  
    setfillcolor(WHITE);
    //setlinecolor(WHITE);
    //setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
    solidrectangle(x, y, x + barWidth, y + barHeight); // 绘制背景框  
    // 绘制已填充的进度部分
    setfillcolor(GREEN);
    //setlinecolor(GREEN);
    //setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
    solidrectangle(x, y, x + filledWidth, y + barHeight); // 绘制进度条  
}


void ui_process()
{
    sprintf(killed_number_display, "%d", killed_number * 100);
    sprintf(lv_display, "%d", lv);
    //sprintf(lv_live, "%d", live);
    POINT mousePos;
    GetCursorPos(&mousePos);
    ScreenToClient(GetHWnd(), &mousePos);
    *pmx = mousePos.x;
    *pmy = mousePos.y;
}

