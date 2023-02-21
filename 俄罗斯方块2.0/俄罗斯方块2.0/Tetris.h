#ifndef DEF_ELS_HEAD
#define DEF_ELS_HEAD
#include <Windows.h>
#include <time.h>
#define DEF_TIMER1 1234



void OnPaint(HDC hDc);
//显示方块
void PaintSquare(HDC hDc);
//产生随机块
int CreateRandomSquare();
//随机块复制到背景
void CopySquareToBack();
void OnCreate();

//按键消息
void OnReturn(HWND hWnd);

//定时器，按键相应的函数
void OnTimer(HWND hWnd);
void OnLeft(HWND hWnd);
void OnRight(HWND hWnd);
void OnDown(HWND hWnd);
void OnChange(HWND hWnd);

//方块下落
void SquareDown();
//方块左移
void SquareLeft();
//方块右移
void SquareRight();
//方块停止于底部  返回0不能下落，返回1可以下落
int CanSquareDown();
//方块下落和下方方块碰撞判断
int CanSquareDown2();
//方块是否能左移判断
int CanSquareLeft();
//方块左移碰到另一个方块判断
int CanSquareLeft2();
//方块是否能右移判断
int CanSquareRight();
//方块右移碰到另一个方块判断
int CanSquareRight2();
//方块变形条件判断
int CanSquareChangeShape();
//长条方块变形判断
int CanLineSquareChange();
//游戏结束判断
int CanGameOver();
//1 变成 2
void Change1To2();
//方块变形
void ChangeSquare();
//长条方块变形
void ChangeLineSquare();
//显示2
void ShowSquare2(HDC hMemDC);
//显示分数
//void ShowScore(HDC hMemDC);
//消除行
void DestroyLineSquare();
#endif


