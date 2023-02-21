#include "Tetris.h"
#include <stdlib.h>

//背景数组
char g_arrBackGround[20][10] = {0};
//方块数组
char g_arrSquare[2][4] = {0};
//方块id
int g_nSquareID;
//行列变量，用于记录方块位置
int g_nLine = 0;
int g_nList = 0;
//分数相关变量
int g_nScore = 0;

//绘制图像函数
void OnPaint(HDC hDc)
{
	//创建兼容性DC,dc相当于纸的编号
	HDC hMemDC = CreateCompatibleDC(hDc);
	//创建兼容性视图，创建“一张纸”
	HBITMAP hBitMapBack = CreateCompatibleBitmap(hDc, 500, 650);
	//将DC与位图绑定在一起，关联“编号”和“纸”
	SelectObject(hMemDC, hBitMapBack);
	PaintSquare(hMemDC);
	ShowSquare2(hMemDC);
	/*ShowScore(hMemDC);*/
	//将内存dc传递到窗口dc
	BitBlt(hDc, 0, 0, 500, 600, hMemDC, 0, 0, SRCCOPY);
	//释放位图的句柄
	DeleteObject(hBitMapBack);
	DeleteDC(hMemDC);
}

//初始化函数-》创建随机数种子，调用创建随机块函数，调用将随机块复制到背景数组函数
void OnCreate()
{
	srand((unsigned int)time(NULL)); //随机数种子
	CreateRandomSquare();
	CopySquareToBack();
}

//绘制方块
void PaintSquare(HDC hMemDC)
{
	int i = 0, j = 0;
	// 画背景
	Rectangle(hMemDC, 0, 0, 300, 600);
	////指定一个方块
	/*g_arrBackGround[2][4] = 1;
	g_arrBackGround[3][3] = 1;
	g_arrBackGround[3][4] = 1;
	g_arrBackGround[3][5] = 1;*/
	HBRUSH hOldBrush = NULL;
	HBRUSH hNewBrush = CreateSolidBrush(RGB(247, 55, 45));  //方块上色
	SelectObject(hMemDC, hNewBrush);
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (1 == g_arrBackGround[i][j])
			{
				//画方块
				Rectangle(hMemDC, j * 30, i * 30, j * 30 + 30, i * 30 + 30);
			}
		}
	}
	//分数
	wchar_t szScore[20] = { 0 };
	wsprintf(szScore, L"分数：%d", g_nScore);
	//设置字体
	HFONT hFont = CreateFont(18, 0, 0, 0, FW_DONTCARE, 
		FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("楷体"));
	SelectObject(hMemDC, hFont);
	TextOut(hMemDC, 310, 140, szScore,wcslen(szScore));
	//说明信息
	TextOut(hMemDC, 310, 180, L"游戏说明", wcslen(L"游戏说明"));
	TextOut(hMemDC, 310, 220, L"回车键:开始游戏", wcslen(L"回车键:开始游戏"));
	TextOut(hMemDC, 310, 260, L"空格键:暂停/继续", wcslen(L"空格键:暂停/继续"));
	TextOut(hMemDC, 310, 300, L"左键:向左移", wcslen(L"左键:向左移"));
	TextOut(hMemDC, 310, 340, L"右键:向右移", wcslen(L"右键:向右移"));
	TextOut(hMemDC, 310, 380, L"下键:加速下落", wcslen(L"下键:加速下落"));
	TextOut(hMemDC, 310, 420, L"上键:变形", wcslen(L"上键:变形"));

	SelectObject(hMemDC, hOldBrush);  //画完了，选回旧的画刷
	DeleteObject(hNewBrush); //删除新画刷
}
//创建随机块， 记录方块初始位置
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
	// 把随机获得的index赋值给方块id
	g_nSquareID = nIndex;
	return nIndex;
}
// 随机块贴近背景-》将随机块复制到背景数组中
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
//定时器-》开始游戏
void OnReturn(HWND hWnd)
{
	//打开定时器
	SetTimer(hWnd, DEF_TIMER1, 500, NULL);
}
//方块下落
void SquareDown()
{
	int i = 0, j = 0;
	for (i = 19; i >= 0; i--)
	{
		for (j = 0; j < 10; j++)
		{
			if (1 == g_arrBackGround[i][j])
			{
				g_arrBackGround[i + 1][j] = g_arrBackGround[i][j]; //把下一行同列元素变成1
				g_arrBackGround[i][j] = 0;
			}
		}
	}
}
// 定时产生新方块，新方块下落，更新方块line数据
void OnTimer(HWND hWnd)
{
	HDC hDc = GetDC(hWnd);
	if (1 == CanSquareDown() && 1 == CanSquareDown2()) //方块还没到底可以继续下落
	{
		SquareDown();
		g_nLine++;
	}
	else//方块到底
	{
		//让1变成2
		Change1To2();
		//消除方块
		DestroyLineSquare();
		if (0 == CanGameOver())
		{
			//结束应用程序
			KillTimer(hWnd, DEF_TIMER1);
			//return 0;
		}
		//产生随机块
		CreateRandomSquare();
		//复制到背景上
		CopySquareToBack();
	}

	//显示方块
	OnPaint(hDc);
	ReleaseDC(hWnd, hDc);
}
// 判断方块是否到达底部
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
//方块到底后把方块元素变成2， 防止和下一个产生的方块碰撞后重合
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
//上一个方块到底后，产生新的方块
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
				//画方块
				Rectangle(hMemDC, j * 30, i * 30, j * 30 + 30, i * 30 + 30);
			}
		}
	}
	SelectObject(hMemDC, hOldBrush);
	DeleteObject(hNewBrush);
}
////绘制分数
//void ShowScore(HDC hMemDC)
//{
//	char strScore[10] = { 0 };
//	Rectangle(hMemDC, 300, 0, 500, 600);
//	//把分数转化为字符并存到指定字符数组
//	itoa(g_nScore, strScore, 10);
//	//以字符形式输出积分
//	TextOut(hMemDC, 400, 5, L"分数", strlen("分数"));
//	TextOut(hMemDC, 400, 20, strScore, strlen(strScore));
//}
//判断是否有两个方块接触
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
//按方向左键使得方块左移，更新方块list数据
void OnLeft(HWND hWnd)
{

	//方块左移
	if (1 == CanSquareLeft() && 1 == CanSquareLeft2())
	{
		HDC hDc = GetDC(hWnd);
		SquareLeft();
		g_nList--;
		//显示方块
		OnPaint(hDc);
		ReleaseDC(hWnd, hDc);
	}
}
//按方向右键使得方块左移，更新方块list数据
void OnRight(HWND hWnd)
{
    //方块右移
	if (1 == CanSquareRight() && 1 == CanSquareRight2())
	{
		HDC hDc = GetDC(hWnd);
		SquareRight();
		g_nList++;
		OnPaint(hDc);
		ReleaseDC(hWnd, hDc);
	}
}
//按方向下键使得方块加速下落
void OnDown(HWND hWnd)
{
	OnTimer(hWnd);
}
//方块变形-》变形实现，矩阵顺向旋转
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
		//普通变形
		if (1 == CanSquareChangeShape())
		{
			ChangeSquare();
		}
		else
		{
			return;
		}
		break;
	case 5://正方形不进行变形
		return;
	case 6://长条变形
		if (1 == CanLineSquareChange())
		{
			ChangeLineSquare();
		}
		break;
	}
	//显示变形后的方块
	OnPaint(hDc);
	ReleaseDC(hWnd, hDc);
}
//方块左移
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
//判断方块是否能左移
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
//方块左移碰到另一个方块判断
int CanSquareLeft2()
{
	int i = 0, j = 0;
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 10; j++)
		{
			//首先判断背景元素是否为方块
			if (1 == g_arrBackGround[i][j])
			{
				//如果是，第二步判断该方块左边是否有方块
				if (2 == g_arrBackGround[i][j - 1])
				{
					return 0;
				}
			}
		}
	}
	return 1;
}
//方块右移
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
//判断方块是否能右移
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
//方块右移碰到另一个方块判断
int CanSquareRight2()
{
	int i = 0, j = 0;
	for (i = 0; i < 20; i++)
	{
		for (j = 9; j >= 0; j--)
		{
			//首先判断背景元素是否为方块
			if (1 == g_arrBackGround[i][j])
			{
				//如果是，第二步判断该方块右边是否有方块
				if (2 == g_arrBackGround[i][j + 1])
				{
					return 0;
				}
			}
		}
	} 
	return 1;
}
// 方块变形判断
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

	//if (g_nList < 0 || g_nList + 2 > 9) //边界检查方案1 -》检查是否越界
	//{
	//	return 0;
	//}
	if (g_nList < 0)//方案2-》改变基准点
	{
		g_nList = 0;
	}
	else if (g_nList + 2 > 9)
	{
		g_nList = 7;
	}

	return 1;
}
//方块普通变形
void ChangeSquare()
{
	int i = 0, j = 0;
	int nTemp = 2;
	char arrSquare[3][3] = {0};
	//背景块复制到临时数组里
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			arrSquare[i][j] = g_arrBackGround[g_nLine+i][g_nList+j];
		}
	}

	//变形后复制回背景
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
//长方形变形
void ChangeLineSquare()
{

	if (1 == g_arrBackGround[g_nLine][g_nList - 1])//长条方块水平时
	{
		//清零
		g_arrBackGround[g_nLine][g_nList - 1] = 0;
		g_arrBackGround[g_nLine][g_nList + 1] = 0;
		g_arrBackGround[g_nLine][g_nList + 2] = 0;
		if (2 == g_arrBackGround[g_nLine + 1][g_nList])
		{
			//赋值
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
			//元素赋值
			g_arrBackGround[g_nLine - 1][g_nList] = 1;
			g_arrBackGround[g_nLine + 1][g_nList] = 1;
			g_arrBackGround[g_nLine + 2][g_nList] = 1;
		}

	}
	else //长条方块竖直时
	{
		//清零
		g_arrBackGround[g_nLine - 1][g_nList] = 0;
		g_arrBackGround[g_nLine + 1][g_nList] = 0;
		g_arrBackGround[g_nLine + 2][g_nList] = 0;
		if (2 == g_arrBackGround[g_nLine][g_nList + 1] || 9 == g_nList)
		{
			//元素赋值
			g_arrBackGround[g_nLine][g_nList - 1] = 1;
			g_arrBackGround[g_nLine][g_nList - 2] = 1;
			g_arrBackGround[g_nLine][g_nList - 3] = 1;
			//标记改变
			g_nList = g_nList - 2;
		}
		else if (2 == g_arrBackGround[g_nLine][g_nList + 2] || 8 == g_nList)
		{

			//元素赋值
			g_arrBackGround[g_nLine][g_nList - 1] = 1;
			g_arrBackGround[g_nLine][g_nList + 1] = 1;
			g_arrBackGround[g_nLine][g_nList - 2] = 1;
			//标记改变
			g_nList = g_nList - 1;
		}
		else if (2 == g_arrBackGround[g_nLine][g_nList - 1] || 0 == g_nList)
		{
			g_arrBackGround[g_nLine][g_nList + 1] = 1;
			g_arrBackGround[g_nLine][g_nList + 2] = 1;
			g_arrBackGround[g_nLine][g_nList + 3] = 1;
			//标记改变
			g_nList = g_nList + 1;
		}
		else
		{
			//元素赋值
			g_arrBackGround[g_nLine][g_nList - 1] = 1;
			g_arrBackGround[g_nLine][g_nList + 1] = 1;
			g_arrBackGround[g_nLine][g_nList + 2] = 1;
		}
	}
}
//长条变形判断
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
//消除行
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
			//清除一行
			for (nTemp = i - 1; nTemp >= 0; nTemp--)
			{
				for (j = 0; j < 10; j++)
				{
					g_arrBackGround[nTemp + 1][j] = g_arrBackGround[nTemp][j];
				}
			}
			// 消除一行分数+1
			g_nScore += 10;
			i = 20;
		}
		nSum = 0; //qing0
	}

}
//判断游戏是否结束
int CanGameOver()
{
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		if (2 == g_arrBackGround[0][i])
		{
			MessageBox(NULL, L"Game Over", L"提示", MB_OK);
			return 0;
		}
	}
	return 1;
}