#define _CRT_SECURE_NO_WARNINGS 1
#include <graphics.h> 
#include <easyx.h>
#include <conio.h>  
#include <stdio.h>  
#include <math.h>
#include <time.h>
#include "main.h"
#pragma comment( lib, "MSIMG32.LIB")
#pragma comment(lib,"winmm.lib")

#define BULLET_SPEED 20 // 子弹速度
#define ENEMY_SPEED 2 // 敌人速度
#define MAX_BULLETS 10

//人物位置
int x = 640-170;
int y = 360-170;
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
int killed_number = 0;  //击杀计数
char killed_number_display[20];
int lv = 0; //等级
char lv_display[20];
int live = 3;
//子弹
int bx = 500;
int by = 500;
int* bpy = &bx;//子弹的实时位置y
int* bpx = &by;//子弹的实时位置x
int* bullet_active = &bx;//子弹是否激活
int hit_frame = 10;//伤害显示的总帧数
int hit = 0;//子弹是否击中,是否显示伤害
//敌人
int ex = 0;
int ey = 0;
int* dpx = &ex;//敌人的实时位置x
int* dpy = &ey;//敌人的实时位置y
int* enemy_active = &ex;//敌人是否存活
int tsign = 0;//记录线程循环次数
int enemyflame = 0;//敌人移动动画帧
int enemyflame_die = 0;//敌人死亡动画帧
int enemyflame_attack = 0;//敌人血量
int Isleft = 0;//敌人移动方向

//子弹
typedef struct {
    int x, y;//子弹位置  
    int targetX, targetY;//目标位置  
    int active;//子弹是否活跃  
} Bullet;

Bullet bullets[MAX_BULLETS];  //子弹数组

//敌人
typedef struct {
    int x, y; // 敌人位置  
    int targetX, targetY; // 目标位置  
    int active; // 敌人是否活跃  
    int health ;
} enemy;

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
const char* golyat_move_left[] = {
    "./resource/enemy/golyat/move_left/ (1).png",
	"./resource/enemy/golyat/move_left/ (2).png",
	"./resource/enemy/golyat/move_left/ (3).png",
	"./resource/enemy/golyat/move_left/ (4).png",
	"./resource/enemy/golyat/move_left/ (5).png",
	"./resource/enemy/golyat/move_left/ (6).png",
	"./resource/enemy/golyat/move_left/ (7).png",
	"./resource/enemy/golyat/move_left/ (8).png",
	"./resource/enemy/golyat/move_left/ (9).png",
	"./resource/enemy/golyat/move_left/ (10).png",
	"./resource/enemy/golyat/move_left/ (11).png",
	"./resource/enemy/golyat/move_left/ (12).png",
	"./resource/enemy/golyat/move_left/ (13).png",
	"./resource/enemy/golyat/move_left/ (14).png",
	"./resource/enemy/golyat/move_left/ (15).png",
	"./resource/enemy/golyat/move_left/ (16).png",
	"./resource/enemy/golyat/move_left/ (17).png",
	"./resource/enemy/golyat/move_left/ (18).png",
	"./resource/enemy/golyat/move_left/ (19).png",
	"./resource/enemy/golyat/move_left/ (20).png",
	"./resource/enemy/golyat/move_left/ (21).png",
	"./resource/enemy/golyat/move_left/ (22).png",
	"./resource/enemy/golyat/move_left/ (23).png",
	"./resource/enemy/golyat/move_left/ (24).png"
};
const char* golyat_move_right[] = {
    "./resource/enemy/golyat/move_right/(1).png",
    "./resource/enemy/golyat/move_right/(2).png",
    "./resource/enemy/golyat/move_right/(3).png",
    "./resource/enemy/golyat/move_right/(4).png",
    "./resource/enemy/golyat/move_right/(5).png",
    "./resource/enemy/golyat/move_right/(6).png",
    "./resource/enemy/golyat/move_right/(7).png",
    "./resource/enemy/golyat/move_right/(8).png",
    "./resource/enemy/golyat/move_right/(9).png",
    "./resource/enemy/golyat/move_right/(10).png",
    "./resource/enemy/golyat/move_right/(11).png",
    "./resource/enemy/golyat/move_right/(12).png",
    "./resource/enemy/golyat/move_right/(13).png",
    "./resource/enemy/golyat/move_right/(14).png",
    "./resource/enemy/golyat/move_right/(15).png",
    "./resource/enemy/golyat/move_right/(16).png",
    "./resource/enemy/golyat/move_right/(17).png",
    "./resource/enemy/golyat/move_right/(18).png",
    "./resource/enemy/golyat/move_right/(19).png",
    "./resource/enemy/golyat/move_right/(20).png",
    "./resource/enemy/golyat/move_right/(21).png",
    "./resource/enemy/golyat/move_right/(22).png",
    "./resource/enemy/golyat/move_right/(23).png",
    "./resource/enemy/golyat/move_right/(24).png"
};
const char* golyat_die_left[] = {
    "./resource/enemy/golyat/die_left/ (1).png",
    "./resource/enemy/golyat/die_left/ (2).png",
    "./resource/enemy/golyat/die_left/ (3).png",
    "./resource/enemy/golyat/die_left/ (4).png",
    "./resource/enemy/golyat/die_left/ (5).png",
    "./resource/enemy/golyat/die_left/ (6).png",
    "./resource/enemy/golyat/die_left/ (7).png",
    "./resource/enemy/golyat/die_left/ (8).png",
    "./resource/enemy/golyat/die_left/ (9).png",
    "./resource/enemy/golyat/die_left/ (10).png",
    "./resource/enemy/golyat/die_left/ (11).png",
    "./resource/enemy/golyat/die_left/ (12).png",
    "./resource/enemy/golyat/die_left/ (13).png",
    "./resource/enemy/golyat/die_left/ (14).png",
    "./resource/enemy/golyat/die_left/ (15).png",
    "./resource/enemy/golyat/die_left/ (16).png",
    "./resource/enemy/golyat/die_left/ (17).png",
    "./resource/enemy/golyat/die_left/ (18).png",
    "./resource/enemy/golyat/die_left/ (19).png",
    "./resource/enemy/golyat/die_left/ (20).png",
    "./resource/enemy/golyat/die_left/ (21).png",
    "./resource/enemy/golyat/die_left/ (22).png",
    "./resource/enemy/golyat/die_left/ (23).png",
    "./resource/enemy/golyat/die_left/ (24).png",
    "./resource/enemy/golyat/die_left/ (25).png",
    "./resource/enemy/golyat/die_left/ (26).png",
    "./resource/enemy/golyat/die_left/ (27).png",
    "./resource/enemy/golyat/die_left/ (28).png",
    "./resource/enemy/golyat/die_left/ (29).png",
    "./resource/enemy/golyat/die_left/ (30).png",
    "./resource/enemy/golyat/die_left/ (31).png",
    "./resource/enemy/golyat/die_left/ (32).png",
    "./resource/enemy/golyat/die_left/ (33).png",
    "./resource/enemy/golyat/die_left/ (34).png",
    "./resource/enemy/golyat/die_left/ (35).png",
    "./resource/enemy/golyat/die_left/ (36).png",
    "./resource/enemy/golyat/die_left/ (37).png",
    "./resource/enemy/golyat/die_left/ (38).png",
    "./resource/enemy/golyat/die_left/ (39).png",
    "./resource/enemy/golyat/die_left/ (40).png",
    "./resource/enemy/golyat/die_left/ (41).png",
    "./resource/enemy/golyat/die_left/ (42).png",
    "./resource/enemy/golyat/die_left/ (43).png",
    "./resource/enemy/golyat/die_left/ (44).png",
    "./resource/enemy/golyat/die_left/ (45).png",
    "./resource/enemy/golyat/die_left/ (46).png",
    "./resource/enemy/golyat/die_left/ (47).png"
};
const char* golyat_die_right[] = {
    "./resource/enemy/golyat/die_right/(1).png",
    "./resource/enemy/golyat/die_right/(2).png",
    "./resource/enemy/golyat/die_right/(3).png",
    "./resource/enemy/golyat/die_right/(4).png",
    "./resource/enemy/golyat/die_right/(5).png",
    "./resource/enemy/golyat/die_right/(6).png",
    "./resource/enemy/golyat/die_right/(7).png",
    "./resource/enemy/golyat/die_right/(8).png",
    "./resource/enemy/golyat/die_right/(9).png",
    "./resource/enemy/golyat/die_right/(10).png",
    "./resource/enemy/golyat/die_right/(11).png",
    "./resource/enemy/golyat/die_right/(12).png",
    "./resource/enemy/golyat/die_right/(13).png",
    "./resource/enemy/golyat/die_right/(14).png",
    "./resource/enemy/golyat/die_right/(15).png",
    "./resource/enemy/golyat/die_right/(16).png",
    "./resource/enemy/golyat/die_right/(17).png",
    "./resource/enemy/golyat/die_right/(18).png",
    "./resource/enemy/golyat/die_right/(19).png",
    "./resource/enemy/golyat/die_right/(20).png",
    "./resource/enemy/golyat/die_right/(21).png",
    "./resource/enemy/golyat/die_right/(22).png",
    "./resource/enemy/golyat/die_right/(23).png",
    "./resource/enemy/golyat/die_right/(24).png",
    "./resource/enemy/golyat/die_right/(25).png",
    "./resource/enemy/golyat/die_right/(26).png",
    "./resource/enemy/golyat/die_right/(27).png",
    "./resource/enemy/golyat/die_right/(28).png",
    "./resource/enemy/golyat/die_right/(29).png",
    "./resource/enemy/golyat/die_right/(30).png",
    "./resource/enemy/golyat/die_right/(31).png",
    "./resource/enemy/golyat/die_right/(32).png",
    "./resource/enemy/golyat/die_right/(33).png",
    "./resource/enemy/golyat/die_right/(34).png",
    "./resource/enemy/golyat/die_right/(35).png",
    "./resource/enemy/golyat/die_right/(36).png",
    "./resource/enemy/golyat/die_right/(37).png",
    "./resource/enemy/golyat/die_right/(38).png",
    "./resource/enemy/golyat/die_right/(39).png",
    "./resource/enemy/golyat/die_right/(40).png",
    "./resource/enemy/golyat/die_right/(41).png",
    "./resource/enemy/golyat/die_right/(42).png",
    "./resource/enemy/golyat/die_right/(43).png",
    "./resource/enemy/golyat/die_right/(44).png",
    "./resource/enemy/golyat/die_right/(45).png",
    "./resource/enemy/golyat/die_right/(46).png",
    "./resource/enemy/golyat/die_right/(47).png"
};
const char* golyat_attack_left[] = {
    "./resource/enemy/golyat/attack_left/ (1).png",
	"./resource/enemy/golyat/attack_left/ (2).png",
	"./resource/enemy/golyat/attack_left/ (3).png",
	"./resource/enemy/golyat/attack_left/ (4).png",
	"./resource/enemy/golyat/attack_left/ (5).png",
	"./resource/enemy/golyat/attack_left/ (6).png",
	"./resource/enemy/golyat/attack_left/ (7).png",
	"./resource/enemy/golyat/attack_left/ (8).png",
	"./resource/enemy/golyat/attack_left/ (9).png",
	"./resource/enemy/golyat/attack_left/ (10).png",
	"./resource/enemy/golyat/attack_left/ (11).png",
	"./resource/enemy/golyat/attack_left/ (12).png",
	"./resource/enemy/golyat/attack_left/ (13).png",
	"./resource/enemy/golyat/attack_left/ (14).png",
	"./resource/enemy/golyat/attack_left/ (15).png",
	"./resource/enemy/golyat/attack_left/ (16).png",
	"./resource/enemy/golyat/attack_left/ (17).png",
	"./resource/enemy/golyat/attack_left/ (18).png",
	"./resource/enemy/golyat/attack_left/ (19).png",
	"./resource/enemy/golyat/attack_left/ (20).png",
	"./resource/enemy/golyat/attack_left/ (21).png",
	"./resource/enemy/golyat/attack_left/ (22).png",
	"./resource/enemy/golyat/attack_left/ (23).png",
	"./resource/enemy/golyat/attack_left/ (24).png",
	"./resource/enemy/golyat/attack_left/ (25).png",
	"./resource/enemy/golyat/attack_left/ (26).png",
	"./resource/enemy/golyat/attack_left/ (27).png",
	"./resource/enemy/golyat/attack_left/ (28).png",
	"./resource/enemy/golyat/attack_left/ (29).png",
	"./resource/enemy/golyat/attack_left/ (30).png",
	"./resource/enemy/golyat/attack_left/ (31).png",
	"./resource/enemy/golyat/attack_left/ (32).png",
	"./resource/enemy/golyat/attack_left/ (33).png",
	"./resource/enemy/golyat/attack_left/ (34).png",
	"./resource/enemy/golyat/attack_left/ (35).png",
	"./resource/enemy/golyat/attack_left/ (36).png",
	"./resource/enemy/golyat/attack_left/ (37).png",
	"./resource/enemy/golyat/attack_left/ (38).png",
	"./resource/enemy/golyat/attack_left/ (39).png",
	"./resource/enemy/golyat/attack_left/ (40).png",
	"./resource/enemy/golyat/attack_left/ (41).png",
	"./resource/enemy/golyat/attack_left/ (42).png",
	"./resource/enemy/golyat/attack_left/ (43).png",
	"./resource/enemy/golyat/attack_left/ (44).png",
	"./resource/enemy/golyat/attack_left/ (45).png",
	"./resource/enemy/golyat/attack_left/ (46).png",
	"./resource/enemy/golyat/attack_left/ (47).png",
	"./resource/enemy/golyat/attack_left/ (48).png",
	"./resource/enemy/golyat/attack_left/ (49).png",
	"./resource/enemy/golyat/attack_left/ (50).png",
	"./resource/enemy/golyat/attack_left/ (51).png",
	"./resource/enemy/golyat/attack_left/ (52).png",
	"./resource/enemy/golyat/attack_left/ (53).png",
	"./resource/enemy/golyat/attack_left/ (54).png",
	"./resource/enemy/golyat/attack_left/ (55).png",
	"./resource/enemy/golyat/attack_left/ (56).png",
	"./resource/enemy/golyat/attack_left/ (57).png",
	"./resource/enemy/golyat/attack_left/ (58).png",
	"./resource/enemy/golyat/attack_left/ (59).png",
	"./resource/enemy/golyat/attack_left/ (60).png",
	"./resource/enemy/golyat/attack_left/ (61).png",
	"./resource/enemy/golyat/attack_left/ (62).png",
	"./resource/enemy/golyat/attack_left/ (63).png",
	"./resource/enemy/golyat/attack_left/ (64).png",
	"./resource/enemy/golyat/attack_left/ (65).png",
	"./resource/enemy/golyat/attack_left/ (66).png",
	"./resource/enemy/golyat/attack_left/ (67).png",
	"./resource/enemy/golyat/attack_left/ (68).png",
	"./resource/enemy/golyat/attack_left/ (69).png",
	"./resource/enemy/golyat/attack_left/ (70).png",
	"./resource/enemy/golyat/attack_left/ (71).png",
	"./resource/enemy/golyat/attack_left/ (72).png",
	"./resource/enemy/golyat/attack_left/ (73).png",
	"./resource/enemy/golyat/attack_left/ (74).png"
};
const char* golyat_attack_right[] = {
    "./resource/enemy/golyat/attack_right/(1).png",
    "./resource/enemy/golyat/attack_right/(2).png",
    "./resource/enemy/golyat/attack_right/(3).png",
    "./resource/enemy/golyat/attack_right/(4).png",
    "./resource/enemy/golyat/attack_right/(5).png",
    "./resource/enemy/golyat/attack_right/(6).png",
    "./resource/enemy/golyat/attack_right/(7).png",
    "./resource/enemy/golyat/attack_right/(8).png",
    "./resource/enemy/golyat/attack_right/(9).png",
    "./resource/enemy/golyat/attack_right/(10).png",
    "./resource/enemy/golyat/attack_right/(11).png",
    "./resource/enemy/golyat/attack_right/(12).png",
    "./resource/enemy/golyat/attack_right/(13).png",
    "./resource/enemy/golyat/attack_right/(14).png",
    "./resource/enemy/golyat/attack_right/(15).png",
    "./resource/enemy/golyat/attack_right/(16).png",
    "./resource/enemy/golyat/attack_right/(17).png",
    "./resource/enemy/golyat/attack_right/(18).png",
    "./resource/enemy/golyat/attack_right/(19).png",
    "./resource/enemy/golyat/attack_right/(20).png",
    "./resource/enemy/golyat/attack_right/(21).png",
    "./resource/enemy/golyat/attack_right/(22).png",
    "./resource/enemy/golyat/attack_right/(23).png",
    "./resource/enemy/golyat/attack_right/(24).png",
    "./resource/enemy/golyat/attack_right/(25).png",
    "./resource/enemy/golyat/attack_right/(26).png",
    "./resource/enemy/golyat/attack_right/(27).png",
    "./resource/enemy/golyat/attack_right/(28).png",
    "./resource/enemy/golyat/attack_right/(29).png",
    "./resource/enemy/golyat/attack_right/(30).png",
    "./resource/enemy/golyat/attack_right/(31).png",
    "./resource/enemy/golyat/attack_right/(32).png",
    "./resource/enemy/golyat/attack_right/(33).png",
    "./resource/enemy/golyat/attack_right/(34).png",
    "./resource/enemy/golyat/attack_right/(35).png",
    "./resource/enemy/golyat/attack_right/(36).png",
    "./resource/enemy/golyat/attack_right/(37).png",
    "./resource/enemy/golyat/attack_right/(38).png",
    "./resource/enemy/golyat/attack_right/(39).png",
    "./resource/enemy/golyat/attack_right/(40).png",
    "./resource/enemy/golyat/attack_right/(41).png",
    "./resource/enemy/golyat/attack_right/(42).png",
    "./resource/enemy/golyat/attack_right/(43).png",
    "./resource/enemy/golyat/attack_right/(44).png",
    "./resource/enemy/golyat/attack_right/(45).png",
    "./resource/enemy/golyat/attack_right/(46).png",
    "./resource/enemy/golyat/attack_right/(47).png",
    "./resource/enemy/golyat/attack_right/(48).png",
    "./resource/enemy/golyat/attack_right/(49).png",
    "./resource/enemy/golyat/attack_right/(50).png",
    "./resource/enemy/golyat/attack_right/(51).png",
    "./resource/enemy/golyat/attack_right/(52).png",
    "./resource/enemy/golyat/attack_right/(53).png",
    "./resource/enemy/golyat/attack_right/(54).png",
    "./resource/enemy/golyat/attack_right/(55).png",
    "./resource/enemy/golyat/attack_right/(56).png",
    "./resource/enemy/golyat/attack_right/(57).png",
    "./resource/enemy/golyat/attack_right/(58).png",
    "./resource/enemy/golyat/attack_right/(59).png",
    "./resource/enemy/golyat/attack_right/(60).png",
    "./resource/enemy/golyat/attack_right/(61).png",
    "./resource/enemy/golyat/attack_right/(62).png",
    "./resource/enemy/golyat/attack_right/(63).png",
    "./resource/enemy/golyat/attack_right/(64).png",
    "./resource/enemy/golyat/attack_right/(65).png",
    "./resource/enemy/golyat/attack_right/(66).png",
    "./resource/enemy/golyat/attack_right/(67).png",
    "./resource/enemy/golyat/attack_right/(68).png",
    "./resource/enemy/golyat/attack_right/(69).png",
    "./resource/enemy/golyat/attack_right/(70).png",
    "./resource/enemy/golyat/attack_right/(71).png",
    "./resource/enemy/golyat/attack_right/(72).png",
    "./resource/enemy/golyat/attack_right/(73).png",
    "./resource/enemy/golyat/attack_right/(74).png"
};

//自定义函数的声明
void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
void playAnimation(const char* frames[], int frameCount, int a);
void drawProgressBar(int x, int y, int progress, int total);
void ui_process();
void fire();
void enemy_data();
void enemy_show();


IMAGE background;
IMAGE bulletimg;
IMAGE enemyimg;
IMAGE heart;

//自定义函数的定义
void playAnimation(const char* frames[], int frameCount,int a)  //主渲染函数
{
    IMAGE img;
    settextstyle(25, 0, "黑体");
    for (int i = 0; i < frameCount; i++)
    {
        cleardevice(); // 清除屏幕
        start_time_anime = clock();
        if (*psign != a)
        {
            break;
        }
        BeginBatchDraw();
        //加载背景
        putimage(0, 0, &background);
        //加载ui
        drawProgressBar(240, 10, killed_number * 100 - lv * 1000, 1000);
        setbkmode(TRANSPARENT);
        outtextxy(1020, 50, killed_number_display);
        outtextxy(250, 11, "Lv.");
        outtextxy(285, 11, lv_display);
        for (int i = 0; i < live; i++)
        {
            transparentimage3(NULL, 240+i*30,40, &heart);
        }
        //加载射击线 
        setcolor(WHITE);
        setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
        circle(*pmx, *pmy, 20);
        setlinecolor(WHITE);
        setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 3);
        line(*pmx, *pmy, *px + 170, *py + 170);
		//加载子弹
        for (int i = 0; i < MAX_BULLETS; i++)
        {
            if (bullets[i].active)
            {
                transparentimage3(NULL, bullets[i].x, bullets[i].y, &bulletimg);
            }

        }
		//加载敌人
        if (*enemy_active==1)
        {
            if (Isleft == 1)
            {
                loadimage(&enemyimg, golyat_move_left[enemyflame]);
                transparentimage3(NULL, *dpx, *dpy, &enemyimg);
            }
            else
            {
                loadimage(&enemyimg, golyat_move_right[enemyflame]);
                transparentimage3(NULL, *dpx, *dpy, &enemyimg);
            }
        }
        else if (*enemy_active == 0)
        {
            if (Isleft == 1)
            {
                loadimage(&enemyimg, golyat_die_left[enemyflame_die]);
                transparentimage3(NULL, *dpx, *dpy, &enemyimg);
            }
            else
            {
                loadimage(&enemyimg, golyat_die_right[enemyflame_die]);
                transparentimage3(NULL, *dpx, *dpy, &enemyimg);
            }
        }
        else if (*enemy_active == 2)
        {
            if (Isleft == 1)
            {
                loadimage(&enemyimg, golyat_attack_left[enemyflame_attack]);
                transparentimage3(NULL, *dpx, *dpy, &enemyimg);
            }
            else
            {
                loadimage(&enemyimg, golyat_attack_right[enemyflame_attack]);
                transparentimage3(NULL, *dpx, *dpy, &enemyimg);
            }
        }
        //加载伤害
        if (hit == 1 && hit_frame != 0)
        {
            settextstyle(40, 0, "黑体");
            settextcolor(YELLOW);
            outtextxy(*dpx + 100, *dpy + 100, "10");
            settextstyle(25, 0, "黑体");
            settextcolor(WHITE);
            hit_frame--;
        }
        if (hit_frame == 0)
        {
            hit = 0;
            hit_frame = 10;
        }
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
    
    //检测键盘状态 
    if (!_kbhit())
    {
        if (*pmx < *px) // 检查是否鼠标在小人左侧
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
        if (*pmx > *px) // 检查是否鼠标在小人右侧
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
    
    if (GetAsyncKeyState('W') < 0) // 使用字符常量代替VK_W 
    {
        *py -= 10;
        *psign = 1;
    }
    if (GetAsyncKeyState('S') < 0) // 使用字符常量代替VK_S  
    {
        *py += 10;
        *psign = 2;
    }
    if (GetAsyncKeyState('A') < 0) // 使用字符常量代替VK_A  
    {
        *px -= 10;
        *psign = 2;
    }
    if (GetAsyncKeyState('D') < 0) // 使用字符常量代替VK_D  
    {
        *px += 10;
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
    int barHeight = 25; // 进度条的高度  
    int filledWidth = (progress * barWidth) / total; // 已填充的宽度  
    
    // 绘制已填充的进度部分
    setfillcolor(RGB(13,140,251));
    solidrectangle(x, y, x + filledWidth, y + barHeight); // 绘制进度条 
    // 设置进度条的背景颜色  
    setlinecolor(WHITE);
    //setfillcolor();
    setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
    rectangle(x, y, x + barWidth, y + barHeight); // 绘制背景框  
}

void ui_process()
{
    if (tsign==0)//仅第一次循环执行
    {
		//加载基本图片资源
        loadimage(&background, "./resource/ui/bg.jpg", 1280, 720);
        loadimage(&bulletimg, "./resource/other/bullet.png", 21, 21);//加载子弹图片
		loadimage(&heart, "./resource/ui/heart.png", 32, 32);//加载心图片
    }
    if (killed_number * 100 - lv * 1000 >= 1000)
    {
        lv++;
    }
    //字符转换
    sprintf(killed_number_display, "%d", killed_number * 100);
    sprintf(lv_display, "%d", lv);
	//鼠标追踪
    POINT mousePos;
    GetCursorPos(&mousePos);
    ScreenToClient(GetHWnd(), &mousePos);
    *pmx = mousePos.x;
    *pmy = mousePos.y;
    tsign++;
}

//子弹开火

void fire_move(Bullet* bullet, int heroX, int heroY, int targetX, int targetY) {
    bullet->x = heroX;
    bullet->y = heroY;
    bullet->targetX = targetX;
    bullet->targetY = targetY;
    bullet->active = 1; // 激活子弹  
}

void updateBullet(Bullet* bullet) {
    if (bullet->active) {
        // 计算子弹的方向  
        int dx = bullet->targetX - bullet->x;
        int dy = bullet->targetY - bullet->y;
        double distance = sqrt(dx * dx + dy * dy);

        // 如果子弹到达目标位置，停用子弹  
        if (distance < BULLET_SPEED) {
            bullet->active = 0;
            return;
        }
        
        for (int i = 0; i < MAX_BULLETS; i++)
        {
            
        }

        if (*bullet_active==0)   /////////////////////
        {
            bullet->active = 0;
            return;
        }
        // 更新子弹位置  
        bullet->x += (int)(BULLET_SPEED * (dx / distance));
        bullet->y += (int)(BULLET_SPEED * (dy / distance));
    }
}

void fire() { 
    //Bullet bulletInstance = { 0 };
    while (!exitFlag)
    {
        // 检测鼠标左键发射子弹  
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
        {
            for (int i = 0; i < MAX_BULLETS; i++)
            {
                if (!bullets[i].active) // 只有在子弹未激活时才能发射
                {
                    fire_move(&bullets[i], *px + 170, *py + 170, *pmx, *pmy);
                    break;
                }
            }
        }
        // 更新子弹位置
        
        
        /**bullet_active = bulletInstance.active;
        *bpx = bulletInstance.x;
        *bpy = bulletInstance.y;*/

        /*if (!bulletInstance.active)
        {
            break;
        }*/
        Sleep(200);
    }
}

void fire_rander()
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        printf("%d\n", i);
        updateBullet(&bullets[i]); 
    }
    Sleep(1);
}

//敌人刷新及寻路
void enemy_move(enemy* enemy, int heroX, int heroY, int targetX, int targetY) 
{
    enemy->x = heroX;
    enemy->y = heroY;
    enemy->targetX = targetX;
    enemy->targetY = targetY;
    enemy->active = 1; // 敌人是否存活  
}

void updateEnemy(enemy* enemy) {
    if (enemy->active) {
        // 计算敌人寻路的方向  
        int dx = enemy->targetX - enemy->x;
        int dy = enemy->targetY - enemy->y;
        double distance = sqrt(dx * dx + dy * dy);
        // 如果敌人接触到人物  
        if (distance-100 < ENEMY_SPEED) {
            enemy->active = 2;    /////////////////////
            
            for (int i = 0; i < sizeof(golyat_attack_left) / sizeof(golyat_attack_left[0]); i++)
            {
                start_time_anime = clock();
                enemyflame_attack = i;
                frame_time_anime = clock() - start_time_anime;
                if (i != sizeof(golyat_attack_left) / sizeof(golyat_attack_left[0]) - 1)
                {
                    if (anime_fps - frame_time_anime > 0)
                    {
                        Sleep(anime_fps - frame_time_anime);
                    }
                }
            }
            live--;
            if (live == 0)
            {
               exitFlag = 1;
            }
            return;
        }


        for (int i = 0; i < MAX_BULLETS; i++)
        {
            if (bullets[i].x >= *dpx && bullets[i].x <= *dpx + 340 && bullets[i].y >= *dpy && bullets[i].y <= *dpy + 340)
            {
                enemy->health -= 10;
                bullets[i].active = 0;
                hit = 1;
                //计算敌人死亡动画
                if (enemy->health == 0)
                {
                    enemy->active = 0;
                    killed_number++;
                    for (int i = 0; i < sizeof(golyat_die_left) / sizeof(golyat_die_left[0]); i++)
                    {
                        start_time_anime = clock();
                        enemyflame_die = i;
                        frame_time_anime = clock() - start_time_anime;
                        if (i != sizeof(golyat_die_left) / sizeof(golyat_die_left[0]) - 1)
                        {
                            if (anime_fps - frame_time_anime > 0)
                            {
                                Sleep(anime_fps - frame_time_anime);
                            }
                        }
                    }
                }
            }
        }

        // 更新敌人位置  
        enemy->x += (int)(ENEMY_SPEED * (dx / distance));
        enemy->y += (int)(ENEMY_SPEED * (dy / distance));
        //判断敌人向左移动还是向右移动
        if ((int)(ENEMY_SPEED * (dx / distance)) > 0)
        {
			Isleft = 0;
        }
        else
        {
            Isleft = 1;
        }
        dpx = &enemy->x;
        dpy = &enemy->y;
		enemy_active = &enemy->active;
    }
}


void enemy_data()
{
    enemy enemyInstance = { 0 };
    enemyInstance.health = 50;
    //敌人生成位置随机
    int randomx1=rand()%101;
    int randomx2=rand()%101+840;
    int randomchoosex=rand()%2;
    if (randomchoosex == 0)
    {
        *dpx = randomx1;
    }
    else
    {
        *dpx = randomx2;
    }
    int randomy1 = rand() % 101;
    int randomy2 = rand() % 101 + 280;
    int randomchoosey = rand() % 2;
    if (randomchoosey == 0)
    {
        *dpy = randomy1;
    }
    else
    {
        *dpy = randomy2;
    }

    while (!exitFlag)
    {
        enemy_move(&enemyInstance, *dpx, *dpy, *px, *py);
        updateEnemy(&enemyInstance);
        if (!enemyInstance.active)
        {
            break;
        }
        Sleep(20);
    }
}

void enemy_show()
{
    if (enemy_active)
    {
        for (int i = 0; i < sizeof(golyat_move_left) / sizeof(golyat_move_left[0]); i++)
        {
            start_time_anime = clock();
            enemyflame = i;
            frame_time_anime = clock() - start_time_anime;
            if (i != sizeof(golyat_move_left) / sizeof(golyat_move_left[0]) - 1)
            {
                if (anime_fps - frame_time_anime > 0)
                {
                    Sleep(anime_fps - frame_time_anime);
                }
            }
        }
    }
}