#include "Tetris.h"
#include <stdlib.h>

//��������
char g_arrBackGround[20][10] = {0};
//��������
char g_arrSquare[2][4] = {0};
//����id
int g_nSquareID;
//���б��������ڼ�¼����λ��
int g_nLine = 0;
int g_nList = 0;
//������ر���
int g_nScore = 0;

//����ͼ����
void OnPaint(HDC hDc)
{
	//����������DC,dc�൱��ֽ�ı��
	HDC hMemDC = CreateCompatibleDC(hDc);
	//������������ͼ��������һ��ֽ��
	HBITMAP hBitMapBack = CreateCompatibleBitmap(hDc, 500, 650);
	//��DC��λͼ����һ�𣬹�������š��͡�ֽ��
	SelectObject(hMemDC, hBitMapBack);
	PaintSquare(hMemDC);
	ShowSquare2(hMemDC);
	/*ShowScore(hMemDC);*/
	//���ڴ�dc���ݵ�����dc
	BitBlt(hDc, 0, 0, 500, 600, hMemDC, 0, 0, SRCCOPY);
	//�ͷ�λͼ�ľ��
	DeleteObject(hBitMapBack);
	DeleteDC(hMemDC);
}

//��ʼ������-��������������ӣ����ô�������麯�������ý�����鸴�Ƶ��������麯��
void OnCreate()
{
	srand((unsigned int)time(NULL)); //���������
	CreateRandomSquare();
	CopySquareToBack();
}

//���Ʒ���
void PaintSquare(HDC hMemDC)
{
	int i = 0, j = 0;
	// ������
	Rectangle(hMemDC, 0, 0, 300, 600);
	////ָ��һ������
	/*g_arrBackGround[2][4] = 1;
	g_arrBackGround[3][3] = 1;
	g_arrBackGround[3][4] = 1;
	g_arrBackGround[3][5] = 1;*/
	HBRUSH hOldBrush = NULL;
	HBRUSH hNewBrush = CreateSolidBrush(RGB(247, 55, 45));  //������ɫ
	SelectObject(hMemDC, hNewBrush);
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (1 == g_arrBackGround[i][j])
			{
				//������
				Rectangle(hMemDC, j * 30, i * 30, j * 30 + 30, i * 30 + 30);
			}
		}
	}
	//����
	wchar_t szScore[20] = { 0 };
	wsprintf(szScore, L"������%d", g_nScore);
	//��������
	HFONT hFont = CreateFont(18, 0, 0, 0, FW_DONTCARE, 
		FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("����"));
	SelectObject(hMemDC, hFont);
	TextOut(hMemDC, 310, 140, szScore,wcslen(szScore));
	//˵����Ϣ
	TextOut(hMemDC, 310, 180, L"��Ϸ˵��", wcslen(L"��Ϸ˵��"));
	TextOut(hMemDC, 310, 220, L"�س���:��ʼ��Ϸ", wcslen(L"�س���:��ʼ��Ϸ"));
	TextOut(hMemDC, 310, 260, L"�ո��:��ͣ/����", wcslen(L"�ո��:��ͣ/����"));
	TextOut(hMemDC, 310, 300, L"���:������", wcslen(L"���:������"));
	TextOut(hMemDC, 310, 340, L"�Ҽ�:������", wcslen(L"�Ҽ�:������"));
	TextOut(hMemDC, 310, 380, L"�¼�:��������", wcslen(L"�¼�:��������"));
	TextOut(hMemDC, 310, 420, L"�ϼ�:����", wcslen(L"�ϼ�:����"));

	SelectObject(hMemDC, hOldBrush);  //�����ˣ�ѡ�ؾɵĻ�ˢ
	DeleteObject(hNewBrush); //ɾ���»�ˢ
}
//��������飬 ��¼�����ʼλ��
int CreateRandomSquare()
{
	int nIndex = rand()%7;
	switch(nIndex)
	{
	case 0:
		g_arrSquare[0][0] = 1, g_arrSquare[0][1] = 1, g_arrSquare[0][2] = 0, g_arrSquare[0][3] = 0;
		g_arrSquare[1][0] = 0, g_arrSquare[1][1] = 1, g_arrSquare[1][2] = 1, g_arrSquare[1][3] = 0;
		g_nLine = 0;
		g_nList = 3;
		break;
	case 1:
		g_arrSquare[0][0] = 0, g_arrSquare[0][1] = 1, g_arrSquare[0][2] = 1, g_arrSquare[0][3] = 0;
		g_arrSquare[1][0] = 1, g_arrSquare[1][1] = 1, g_arrSquare[1][2] = 0, g_arrSquare[1][3] = 0;
		g_nLine = 0;
		g_nList = 3;
		break;
	case 2:
		g_arrSquare[0][0] = 1, g_arrSquare[0][1] = 0, g_arrSquare[0][2] = 0, g_arrSquare[0][3] = 0;
		g_arrSquare[1][0] = 1, g_arrSquare[1][1] = 1, g_arrSquare[1][2] = 1, g_arrSquare[1][3] = 0;
		g_nLine = 0;
		g_nList = 3;
		break;
	case 3:
		g_arrSquare[0][0] = 0, g_arrSquare[0][1] = 0, g_arrSquare[0][2] = 1, g_arrSquare[0][3] = 0;
		g_arrSquare[1][0] = 1, g_arrSquare[1][1] = 1, g_arrSquare[1][2] = 1, g_arrSquare[1][3] = 0;
		g_nLine = 0;
		g_nList = 3;
		break;
	case 4:
		g_arrSquare[0][0] = 0, g_arrSquare[0][1] = 1, g_arrSquare[0][2] = 0, g_arrSquare[0][3] = 0;
		g_arrSquare[1][0] = 1, g_arrSquare[1][1] = 1, g_arrSquare[1][2] = 1, g_arrSquare[1][3] = 0;
		g_nLine = 0;
		g_nList = 3;
		break;
	case 5:
		g_arrSquare[0][0] = 0, g_arrSquare[0][1] = 1, g_arrSquare[0][2] = 1, g_arrSquare[0][3] = 0;
		g_arrSquare[1][0] = 0, g_arrSquare[1][1] = 1, g_arrSquare[1][2] = 1, g_arrSquare[1][3] = 0;
		g_nLine = 0;
		g_nList = 4;
		break;
	case 6:
		g_arrSquare[0][0] = 1, g_arrSquare[0][1] = 1, g_arrSquare[0][2] = 1, g_arrSquare[0][3] = 1;
		g_arrSquare[1][0] = 0, g_arrSquare[1][1] = 0, g_arrSquare[1][2] = 0, g_arrSquare[1][3] = 0;
		g_nLine = 0;
		g_nList = 4;
		break;
	}
	// �������õ�index��ֵ������id
	g_nSquareID = nIndex;
	return nIndex;
}
// �������������-��������鸴�Ƶ�����������
void CopySquareToBack()
{
	int i = 0, j = 0;
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 4; j++)
		{
			g_arrBackGround[i][j + 3] = g_arrSquare[i][j];
		}
	}
}
//��ʱ��-����ʼ��Ϸ
void OnReturn(HWND hWnd)
{
	//�򿪶�ʱ��
	SetTimer(hWnd, DEF_TIMER1, 500, NULL);
}
//��������
void SquareDown()
{
	int i = 0, j = 0;
	for (i = 19; i >= 0; i--)
	{
		for (j = 0; j < 10; j++)
		{
			if (1 == g_arrBackGround[i][j])
			{
				g_arrBackGround[i + 1][j] = g_arrBackGround[i][j]; //����һ��ͬ��Ԫ�ر��1
				g_arrBackGround[i][j] = 0;
			}
		}
	}
}
// ��ʱ�����·��飬�·������䣬���·���line����
void OnTimer(HWND hWnd)
{
	HDC hDc = GetDC(hWnd);
	if (1 == CanSquareDown() && 1 == CanSquareDown2()) //���黹û���׿��Լ�������
	{
		SquareDown();
		g_nLine++;
	}
	else//���鵽��
	{
		//��1���2
		Change1To2();
		//��������
		DestroyLineSquare();
		if (0 == CanGameOver())
		{
			//����Ӧ�ó���
			KillTimer(hWnd, DEF_TIMER1);
			//return 0;
		}
		//���������
		CreateRandomSquare();
		//���Ƶ�������
		CopySquareToBack();
	}

	//��ʾ����
	OnPaint(hDc);
	ReleaseDC(hWnd, hDc);
}
// �жϷ����Ƿ񵽴�ײ�
int CanSquareDown()
{
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		if (1 == g_arrBackGround[19][i])
		{
			return 0;
		}
	}
	return 1;
}
//���鵽�׺�ѷ���Ԫ�ر��2�� ��ֹ����һ�������ķ�����ײ���غ�
void Change1To2()
{
	int i = 0, j = 0;
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (1 == g_arrBackGround[i][j])
			{
				g_arrBackGround[i][j] = 2;
			}
		}
	}
}
//��һ�����鵽�׺󣬲����µķ���
void ShowSquare2(HDC hMemDC)
{
	int i = 0, j = 0;
	HBRUSH hOldBrush = NULL;
	HBRUSH hNewBrush = CreateSolidBrush(RGB(94, 204, 86));
	SelectObject(hMemDC, hNewBrush);
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (2 == g_arrBackGround[i][j])
			{
				//������
				Rectangle(hMemDC, j * 30, i * 30, j * 30 + 30, i * 30 + 30);
			}
		}
	}
	SelectObject(hMemDC, hOldBrush);
	DeleteObject(hNewBrush);
}
////���Ʒ���
//void ShowScore(HDC hMemDC)
//{
//	char strScore[10] = { 0 };
//	Rectangle(hMemDC, 300, 0, 500, 600);
//	//�ѷ���ת��Ϊ�ַ����浽ָ���ַ�����
//	itoa(g_nScore, strScore, 10);
//	//���ַ���ʽ�������
//	TextOut(hMemDC, 400, 5, L"����", strlen("����"));
//	TextOut(hMemDC, 400, 20, strScore, strlen(strScore));
//}
//�ж��Ƿ�����������Ӵ�
int CanSquareDown2()
{
	int i = 0, j = 0;
	for (i = 19; i >= 0; i--)
	{
		for (j = 0; j < 10; j++)
		{
			if (1 == g_arrBackGround[i][j])
			{
				if (2 == g_arrBackGround[i + 1][j])
				{
					return 0;
				}
			}
		}
	}
	return 1;
}
//���������ʹ�÷������ƣ����·���list����
void OnLeft(HWND hWnd)
{

	//��������
	if (1 == CanSquareLeft() && 1 == CanSquareLeft2())
	{
		HDC hDc = GetDC(hWnd);
		SquareLeft();
		g_nList--;
		//��ʾ����
		OnPaint(hDc);
		ReleaseDC(hWnd, hDc);
	}
}
//�������Ҽ�ʹ�÷������ƣ����·���list����
void OnRight(HWND hWnd)
{
    //��������
	if (1 == CanSquareRight() && 1 == CanSquareRight2())
	{
		HDC hDc = GetDC(hWnd);
		SquareRight();
		g_nList++;
		OnPaint(hDc);
		ReleaseDC(hWnd, hDc);
	}
}
//�������¼�ʹ�÷����������
void OnDown(HWND hWnd)
{
	OnTimer(hWnd);
}
//�������-������ʵ�֣�����˳����ת
void OnChange(HWND hWnd)
{
	HDC hDc = GetDC(hWnd);
	switch(g_nSquareID)
	{
	case 0:

	case 1:

	case 2:

	case 3:

	case 4:
		//��ͨ����
		if (1 == CanSquareChangeShape())
		{
			ChangeSquare();
		}
		else
		{
			return;
		}
		break;
	case 5://�����β����б���
		return;
	case 6://��������
		if (1 == CanLineSquareChange())
		{
			ChangeLineSquare();
		}
		break;
	}
	//��ʾ���κ�ķ���
	OnPaint(hDc);
	ReleaseDC(hWnd, hDc);
}
//��������
void SquareLeft()
{
	int i = 0, j = 0;
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (1 == g_arrBackGround[i][j])
			{
				g_arrBackGround[i][j-1] = g_arrBackGround[i][j];
				g_arrBackGround[i][j] = 0;
			}
		}
	}
}
//�жϷ����Ƿ�������
int CanSquareLeft()
{
	int i = 0;
	for (i = 0; i < 20; i++)
	{
		if (1 == g_arrBackGround[i][0])
		{
			return 0;
		}
	}
	return 1;
}
//��������������һ�������ж�
int CanSquareLeft2()
{
	int i = 0, j = 0;
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 10; j++)
		{
			//�����жϱ���Ԫ���Ƿ�Ϊ����
			if (1 == g_arrBackGround[i][j])
			{
				//����ǣ��ڶ����жϸ÷�������Ƿ��з���
				if (2 == g_arrBackGround[i][j - 1])
				{
					return 0;
				}
			}
		}
	}
	return 1;
}
//��������
void SquareRight()
{
	int i = 0, j = 0;
	for (i = 0; i < 20; i++)
	{
		for (j = 9; j >= 0; j--)
		{
			if (1 == g_arrBackGround[i][j])
			{
				g_arrBackGround[i][j + 1] = g_arrBackGround[i][j];
				g_arrBackGround[i][j] = 0;
			}
		}
	}
}
//�жϷ����Ƿ�������
int CanSquareRight()
{
	int i = 0;
	for (i = 0; i < 20; i++)
	{
		if (1 == g_arrBackGround[i][9])
		{
			return 0;
		}
	}
	return 1;
}
//��������������һ�������ж�
int CanSquareRight2()
{
	int i = 0, j = 0;
	for (i = 0; i < 20; i++)
	{
		for (j = 9; j >= 0; j--)
		{
			//�����жϱ���Ԫ���Ƿ�Ϊ����
			if (1 == g_arrBackGround[i][j])
			{
				//����ǣ��ڶ����жϸ÷����ұ��Ƿ��з���
				if (2 == g_arrBackGround[i][j + 1])
				{
					return 0;
				}
			}
		}
	} 
	return 1;
}
// ��������ж�
int CanSquareChangeShape()
{
	int i = 0, j = 0;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (2 == g_arrBackGround[g_nLine + i][g_nList + j])
			{
				return 0;
			}
		}
	}

	//if (g_nList < 0 || g_nList + 2 > 9) //�߽��鷽��1 -������Ƿ�Խ��
	//{
	//	return 0;
	//}
	if (g_nList < 0)//����2-���ı��׼��
	{
		g_nList = 0;
	}
	else if (g_nList + 2 > 9)
	{
		g_nList = 7;
	}

	return 1;
}
//������ͨ����
void ChangeSquare()
{
	int i = 0, j = 0;
	int nTemp = 2;
	char arrSquare[3][3] = {0};
	//�����鸴�Ƶ���ʱ������
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			arrSquare[i][j] = g_arrBackGround[g_nLine+i][g_nList+j];
		}
	}

	//���κ��ƻر���
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			g_arrBackGround[g_nLine + i][g_nList + j] = arrSquare[nTemp][i];
			nTemp--;
		}
		nTemp = 2;
	}
}
//�����α���
void ChangeLineSquare()
{

	if (1 == g_arrBackGround[g_nLine][g_nList - 1])//��������ˮƽʱ
	{
		//����
		g_arrBackGround[g_nLine][g_nList - 1] = 0;
		g_arrBackGround[g_nLine][g_nList + 1] = 0;
		g_arrBackGround[g_nLine][g_nList + 2] = 0;
		if (2 == g_arrBackGround[g_nLine + 1][g_nList])
		{
			//��ֵ
			g_arrBackGround[g_nLine - 1][g_nList] = 1;
			g_arrBackGround[g_nLine - 2][g_nList] = 1;
			g_arrBackGround[g_nLine - 3][g_nList] = 1;
		}
		else if (2 == g_arrBackGround[g_nLine + 2][g_nList])
		{
			g_arrBackGround[g_nLine + 1][g_nList] = 1;
			g_arrBackGround[g_nLine - 1][g_nList] = 1;
			g_arrBackGround[g_nLine - 2][g_nList] = 1;
		}
		else
		{
			//Ԫ�ظ�ֵ
			g_arrBackGround[g_nLine - 1][g_nList] = 1;
			g_arrBackGround[g_nLine + 1][g_nList] = 1;
			g_arrBackGround[g_nLine + 2][g_nList] = 1;
		}

	}
	else //����������ֱʱ
	{
		//����
		g_arrBackGround[g_nLine - 1][g_nList] = 0;
		g_arrBackGround[g_nLine + 1][g_nList] = 0;
		g_arrBackGround[g_nLine + 2][g_nList] = 0;
		if (2 == g_arrBackGround[g_nLine][g_nList + 1] || 9 == g_nList)
		{
			//Ԫ�ظ�ֵ
			g_arrBackGround[g_nLine][g_nList - 1] = 1;
			g_arrBackGround[g_nLine][g_nList - 2] = 1;
			g_arrBackGround[g_nLine][g_nList - 3] = 1;
			//��Ǹı�
			g_nList = g_nList - 2;
		}
		else if (2 == g_arrBackGround[g_nLine][g_nList + 2] || 8 == g_nList)
		{

			//Ԫ�ظ�ֵ
			g_arrBackGround[g_nLine][g_nList - 1] = 1;
			g_arrBackGround[g_nLine][g_nList + 1] = 1;
			g_arrBackGround[g_nLine][g_nList - 2] = 1;
			//��Ǹı�
			g_nList = g_nList - 1;
		}
		else if (2 == g_arrBackGround[g_nLine][g_nList - 1] || 0 == g_nList)
		{
			g_arrBackGround[g_nLine][g_nList + 1] = 1;
			g_arrBackGround[g_nLine][g_nList + 2] = 1;
			g_arrBackGround[g_nLine][g_nList + 3] = 1;
			//��Ǹı�
			g_nList = g_nList + 1;
		}
		else
		{
			//Ԫ�ظ�ֵ
			g_arrBackGround[g_nLine][g_nList - 1] = 1;
			g_arrBackGround[g_nLine][g_nList + 1] = 1;
			g_arrBackGround[g_nLine][g_nList + 2] = 1;
		}
	}
}
//���������ж�
int CanLineSquareChange()
{
	int i = 0, j = 0;
	for (i = 1; i < 4; i++)
	{
		if (g_arrBackGround[g_nLine][g_nList])
		{
			if (2 == g_arrBackGround[g_nLine][g_nList + i] || g_nList + i > 9)
			{
				break;
			}
		}
	}

	for (j = 1; j < 4; j++)
	{
		if (2 == g_arrBackGround[g_nLine][g_nList - j] || g_nList - j < 0)
		{
			break;
		}
	}
	if ((i - 1 + j - 1) < 3)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
//������
void DestroyLineSquare()
{
	int i = 0, j = 0;
	int nSum = 0;
	int nTemp = 0;

	for (i = 19; i >= 0; i--)
	{
		for (j = 0; j < 10; j++)
		{
			nSum += g_arrBackGround[i][j];
		}
		if (20 == nSum)
		{
			//���һ��
			for (nTemp = i - 1; nTemp >= 0; nTemp--)
			{
				for (j = 0; j < 10; j++)
				{
					g_arrBackGround[nTemp + 1][j] = g_arrBackGround[nTemp][j];
				}
			}
			// ����һ�з���+1
			g_nScore += 10;
			i = 20;
		}
		nSum = 0; //qing0
	}

}
//�ж���Ϸ�Ƿ����
int CanGameOver()
{
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		if (2 == g_arrBackGround[0][i])
		{
			MessageBox(NULL, L"Game Over", L"��ʾ", MB_OK);
			return 0;
		}
	}
	return 1;
}