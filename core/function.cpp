#define _CRT_SECURE_NO_WARNINGS 1
#include <graphics.h> 
#include <easyx.h>
#include <conio.h>  
#include <stdio.h>  
#include <math.h>
#include <time.h>
#pragma comment( lib, "MSIMG32.LIB")
#pragma comment(lib,"winmm.lib")

#define BULLET_SPEED 20 // �ӵ��ٶ�

//����λ��
int x = 100;
int y = 100;
int* px = &x;
int* py = &y;
//������״̬�仯��־
int sign = 0;  
int* psign = &sign;  //��signָ�뻯
//���׷��
int mx = 100;
int my = 100;
int* pmx = &mx;//����ʵʱx����
int* pmy = &my;//����ʵʱy����
//֡�ʿ���
int anime_fps = 30; // ��������֡��
int start_time_anime = 0;
int frame_time_anime = 0;
//ui��ʾ
int killed_number = 10;  //��ɱ����
char killed_number_display[20];
int lv = 1; //�ȼ�
char lv_display[20];
//int live = 3;
//char lv_live[20];
//�ӵ�
int bx = 500;
int by = 500;
int* bpy = &bx;//�ӵ���ʵʱλ��y
int* bpx = &by;//�ӵ���ʵʱλ��x
int* bullet_active = &bx;//�ӵ��Ƿ񼤻�

int tsign = 0;  //��¼�߳�ѭ������

//�ӵ�
typedef struct {
    int x, y; // �ӵ�λ��  
    int targetX, targetY; // Ŀ��λ��  
    int active; // �ӵ��Ƿ��Ծ  
} Bullet;

//����֡����
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
const char* frames_fire_left[] = {
    "./resource/character/HK416/fire_left/ (1).png",
    "./resource/character/HK416/fire_left/ (2).png",
    "./resource/character/HK416/fire_left/ (3).png",
    "./resource/character/HK416/fire_left/ (4).png",
    "./resource/character/HK416/fire_left/ (5).png",
    "./resource/character/HK416/fire_left/ (6).png",
    "./resource/character/HK416/fire_left/ (7).png",
    "./resource/character/HK416/fire_left/ (8).png",
    "./resource/character/HK416/fire_left/ (9).png",
    "./resource/character/HK416/fire_left/ (10).png",
    "./resource/character/HK416/fire_left/ (11).png",
    "./resource/character/HK416/fire_left/ (12).png",
    "./resource/character/HK416/fire_left/ (13).png",
    "./resource/character/HK416/fire_left/ (14).png",
    "./resource/character/HK416/fire_left/ (15).png",
    "./resource/character/HK416/fire_left/ (16).png",
    "./resource/character/HK416/fire_left/ (17).png",
    "./resource/character/HK416/fire_left/ (18).png",
    "./resource/character/HK416/fire_left/ (19).png",
    "./resource/character/HK416/fire_left/ (20).png",
    "./resource/character/HK416/fire_left/ (21).png",
    "./resource/character/HK416/fire_left/ (22).png",
    "./resource/character/HK416/fire_left/ (23).png",
    "./resource/character/HK416/fire_left/ (24).png",
    "./resource/character/HK416/fire_left/ (25).png",
    "./resource/character/HK416/fire_left/ (26).png",
    "./resource/character/HK416/fire_left/ (27).png",
    "./resource/character/HK416/fire_left/ (28).png",
    "./resource/character/HK416/fire_left/ (29).png",
    "./resource/character/HK416/fire_left/ (30).png",
    "./resource/character/HK416/fire_left/ (31).png",
    "./resource/character/HK416/fire_left/ (32).png",
    "./resource/character/HK416/fire_left/ (33).png",
    "./resource/character/HK416/fire_left/ (34).png"
};
const char* frames_fire_right[] = {
    "./resource/character/HK416/fire_right/ (1).png",
    "./resource/character/HK416/fire_right/ (2).png",
    "./resource/character/HK416/fire_right/ (3).png",
    "./resource/character/HK416/fire_right/ (4).png",
    "./resource/character/HK416/fire_right/ (5).png",
    "./resource/character/HK416/fire_right/ (6).png",
    "./resource/character/HK416/fire_right/ (7).png",
    "./resource/character/HK416/fire_right/ (8).png",
    "./resource/character/HK416/fire_right/ (9).png",
    "./resource/character/HK416/fire_right/ (10).png",
    "./resource/character/HK416/fire_right/ (11).png",
    "./resource/character/HK416/fire_right/ (12).png",
    "./resource/character/HK416/fire_right/ (13).png",
    "./resource/character/HK416/fire_right/ (14).png",
    "./resource/character/HK416/fire_right/ (15).png",
    "./resource/character/HK416/fire_right/ (16).png",
    "./resource/character/HK416/fire_right/ (17).png",
    "./resource/character/HK416/fire_right/ (18).png",
    "./resource/character/HK416/fire_right/ (19).png",
    "./resource/character/HK416/fire_right/ (20).png",
    "./resource/character/HK416/fire_right/ (21).png",
    "./resource/character/HK416/fire_right/ (22).png",
    "./resource/character/HK416/fire_right/ (23).png",
    "./resource/character/HK416/fire_right/ (24).png",
    "./resource/character/HK416/fire_right/ (25).png",
    "./resource/character/HK416/fire_right/ (26).png",
    "./resource/character/HK416/fire_right/ (27).png",
    "./resource/character/HK416/fire_right/ (28).png",
    "./resource/character/HK416/fire_right/ (29).png",
    "./resource/character/HK416/fire_right/ (30).png",
    "./resource/character/HK416/fire_right/ (31).png",
    "./resource/character/HK416/fire_right/ (32).png",
    "./resource/character/HK416/fire_right/ (33).png",
    "./resource/character/HK416/fire_right/ (34).png"
};

//�Զ��庯��������
void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
void playAnimation(const char* frames[], int frameCount, int a);
void drawProgressBar(int x, int y, int progress, int total);
void ui_process();
void fire();

IMAGE background;
IMAGE bulletimg;

//�Զ��庯���Ķ���
void playAnimation(const char* frames[], int frameCount,int a)  //����Ⱦ����
{
    IMAGE img;
    settextstyle(35, 0, "����");
    for (int i = 0; i < frameCount; i++)
    {
        cleardevice(); // �����Ļ
        start_time_anime = clock();
        if (*psign != a)
        {
            break;
        }
        BeginBatchDraw();
        //���ر���
        
        putimage(0, 0, &background); //
        //����ui
        drawProgressBar(240, 10, /*killed_number * 100 - lv * 1000*/ 500, 1000);
        setbkmode(TRANSPARENT);
        outtextxy(640, 50, killed_number_display);
        outtextxy(240, 50, lv_display);
        //outtextxy(100, 50, lv_live);
        //��������� 
        setcolor(WHITE);
        setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
        circle(*pmx, *pmy, 20);
        setlinecolor(WHITE);
        setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 3);
        line(*pmx, *pmy, *px + 170, *py + 170);
		//�����ӵ�(����psignΪ3/4ʱ����)
        if (*bullet_active)
        {
            transparentimage3(NULL, *bpx, *bpy, &bulletimg);
        }
        //���ص�ǰ֡ͼ��
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

void character_move( )
{
    if(*psign == 0)
    {
        playAnimation(frames_wait_left, sizeof(frames_wait_left) / sizeof(frames_wait_left[0]), *psign);
    }
    if(*psign == 10)
    {
        playAnimation(frames_wait_right, sizeof(frames_wait_right) / sizeof(frames_wait_right[0]), *psign);
    }
    if (*psign == 1)
    {
        playAnimation(frames_run_right, sizeof(frames_run_right) / sizeof(frames_run_right[0]), *psign);
    }
    if (*psign == 2)
    {
        playAnimation(frames_run_left, sizeof(frames_run_left) / sizeof(frames_run_left[0]), *psign);
    }
	if (*psign == 3)
	{
		playAnimation(frames_fire_left, sizeof(frames_fire_left) / sizeof(frames_fire_left[0]), *psign);
	}
    if (*psign == 4)
    {
        playAnimation(frames_fire_right, sizeof(frames_fire_right) / sizeof(frames_fire_right[0]), *psign);
    }
}

void keymove()
{
    
    //������״̬ 
    if (!_kbhit())
    {
        if (*pmx < *px) // ����Ƿ������С�����
        {
            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
            {
                *psign = 3;
            }
            else
            {
                *psign = 0;
            }
        }
        if (*pmx > *px) // ����Ƿ������С���Ҳ�
        {
            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
            {
                *psign = 4;
            }
			else
			{
				*psign = 10;
			}
        }
    }
    
    if (GetAsyncKeyState('W') < 0) // ʹ���ַ���������VK_W 
    {
        *py -= 10;
        *psign = 1;
    }
    if (GetAsyncKeyState('S') < 0) // ʹ���ַ���������VK_S  
    {
        *py += 10;
        *psign = 2;
    }
    if (GetAsyncKeyState('A') < 0) // ʹ���ַ���������VK_A  
    {
        *px -= 10;
        *psign = 2;
    }
    if (GetAsyncKeyState('D') < 0) // ʹ���ַ���������VK_D  
    {
        *px += 10;
        *psign = 1;
    }

    // �߽���
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
        *py = 720 - 270; // ����֡�߶�Ϊ100
    }

    Sleep(50); // ���Ƽ���ˢ��Ƶ��
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
    // ����������Ŀ��  
    int barWidth = 800; // ���������ܿ��  
    int barHeight = 30; // �������ĸ߶�  
    int filledWidth = (progress * barWidth) / total; // �����Ŀ��  
    // ���ý������ı�����ɫ  
    setfillcolor(WHITE);
    solidrectangle(x, y, x + barWidth, y + barHeight); // ���Ʊ�����  
    // ���������Ľ��Ȳ���
    setfillcolor(GREEN);
    solidrectangle(x, y, x + filledWidth, y + barHeight); // ���ƽ�����  
}

void ui_process()
{
    if (tsign==0)//����һ��ѭ��ִ��
    {
		//���ػ���ͼƬ��Դ
        loadimage(&background, "./resource/ui/bg.jpg", 1280, 720);
        loadimage(&bulletimg, "./resource/other/bullet.png", 21, 21);//�����ӵ�ͼƬ
    }
    //�ַ�ת��
    sprintf(killed_number_display, "%d", killed_number * 100);
    sprintf(lv_display, "%d", lv);
    //sprintf(lv_live, "%d", live);
	//���׷��
    POINT mousePos;
    GetCursorPos(&mousePos);
    ScreenToClient(GetHWnd(), &mousePos);
    *pmx = mousePos.x;
    *pmy = mousePos.y;
    tsign++;
}



void fire_move(Bullet* bullet, int heroX, int heroY, int targetX, int targetY) {
    bullet->x = heroX;
    bullet->y = heroY;
    bullet->targetX = targetX;
    bullet->targetY = targetY;
    bullet->active = 1; // �����ӵ�  
}

void updateBullet(Bullet* bullet) {
    if (bullet->active) {
        // �����ӵ��ķ���  
        int dx = bullet->targetX - bullet->x;
        int dy = bullet->targetY - bullet->y;
        double distance = sqrt(dx * dx + dy * dy);

        // ����ӵ�����Ŀ��λ�ã�ͣ���ӵ�  
        if (distance < BULLET_SPEED) {
            bullet->active = 0;
            return;
        }
        // �����ӵ�λ��  
        bullet->x += (int)(BULLET_SPEED * (dx / distance));
        bullet->y += (int)(BULLET_SPEED * (dy / distance));
    }
}

void fire() { 
    Bullet bulletInstance = { 0 };
    while (1)
    {
        // ��������������ӵ�  
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
        {
            if (!bulletInstance.active) // ֻ�����ӵ�δ����ʱ���ܷ���
            {
                fire_move(&bulletInstance, *px+170, *py+170, *pmx, *pmy);
            }
        }
        // �����ӵ�λ��  
        updateBullet(&bulletInstance);
        *bullet_active = bulletInstance.active;
        *bpx = bulletInstance.x;
        *bpy = bulletInstance.y;
        if (!bulletInstance.active)
        {
            break;
        }
        Sleep(10);
    }
}

