#ifndef DEF_ELS_HEAD
#define DEF_ELS_HEAD
#include <Windows.h>
#include <time.h>
#define DEF_TIMER1 1234



void OnPaint(HDC hDc);
//��ʾ����
void PaintSquare(HDC hDc);
//���������
int CreateRandomSquare();
//����鸴�Ƶ�����
void CopySquareToBack();
void OnCreate();

//������Ϣ
void OnReturn(HWND hWnd);

//��ʱ����������Ӧ�ĺ���
void OnTimer(HWND hWnd);
void OnLeft(HWND hWnd);
void OnRight(HWND hWnd);
void OnDown(HWND hWnd);
void OnChange(HWND hWnd);

//��������
void SquareDown();
//��������
void SquareLeft();
//��������
void SquareRight();
//����ֹͣ�ڵײ�  ����0�������䣬����1��������
int CanSquareDown();
//����������·�������ײ�ж�
int CanSquareDown2();
//�����Ƿ��������ж�
int CanSquareLeft();
//��������������һ�������ж�
int CanSquareLeft2();
//�����Ƿ��������ж�
int CanSquareRight();
//��������������һ�������ж�
int CanSquareRight2();
//������������ж�
int CanSquareChangeShape();
//������������ж�
int CanLineSquareChange();
//��Ϸ�����ж�
int CanGameOver();
//1 ��� 2
void Change1To2();
//�������
void ChangeSquare();
//�����������
void ChangeLineSquare();
//��ʾ2
void ShowSquare2(HDC hMemDC);
//��ʾ����
//void ShowScore(HDC hMemDC);
//������
void DestroyLineSquare();
#endif


