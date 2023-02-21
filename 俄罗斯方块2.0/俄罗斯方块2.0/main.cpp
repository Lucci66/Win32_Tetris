#include "Tetris.h"
#include "resource.h"


LRESULT CALLBACK WinProc(HWND hWnd, UINT uID, WPARAM wParam, LPARAM lParam);
//主函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// 1、创建窗口类
	WNDCLASSEX wce;
	wce.cbClsExtra = 0;
	wce.cbSize = sizeof(WNDCLASSEX);
	wce.cbWndExtra = 0;
	wce.hbrBackground = (HBRUSH)COLOR_MENU;
	wce.hCursor = NULL;
	wce.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wce.hIconSm = NULL;
	wce.hInstance = hInstance;
	wce.lpfnWndProc = WinProc;
	wce.lpszClassName = TEXT("window");
	wce.lpszMenuName = NULL;
	wce.style = CS_HREDRAW | CS_VREDRAW;

	// 2、注册窗口类
	ATOM nRes = RegisterClassEx(&wce);
	if (0 == nRes)
	{
		return 1;
	}

	// 3、创建窗口
	HWND hWnd = CreateWindowEx(WS_EX_TOPMOST, TEXT("window"), TEXT("Tetris"), WS_OVERLAPPEDWINDOW, 100, 30, 500, 645, NULL, NULL, hInstance, NULL);
	if (NULL == hWnd)
	{
		return 1;
	}
	// 4、显示窗口
	ShowWindow(hWnd, SW_SHOWNORMAL);

	// 5、更新窗口
	UpdateWindow(hWnd);

	// 6、消息循环
	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//将虚拟键消息转换为字符消息
		DispatchMessage(&msg);//将消息分发给窗口处理函数
	}

	return 0;
}

//回调函数
LRESULT CALLBACK WinProc(HWND hWnd, UINT uID, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT pt;
	HDC hDc;
	//
	switch(uID)
	{
	case WM_CREATE: //初始化数据
		MessageBox(NULL, L"		WELCOME\nMade Lucci", L"Lucci's Square", MB_OK);
		OnCreate();
		break;
	case WM_TIMER:
		//计时器
		OnTimer(hWnd);
		break;
	case WM_PAINT:       //窗口绘图消息
		hDc = BeginPaint(hWnd, &pt);

		//画窗口的内容
		OnPaint(hDc);
		EndPaint(hWnd, &pt);
		break;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_RETURN:
			//开始下落
			OnReturn(hWnd);
			break;
		case VK_LEFT:
			//方块左移
			OnLeft(hWnd);
			break;
		case VK_RIGHT:
			//方块右移
			OnRight(hWnd);
			break;
		case VK_UP:
			//方块变形
			OnChange(hWnd);
			break;
		case VK_DOWN:
			//方块加速下落
			OnDown(hWnd);
			break;
		}
		break;
	case WM_DESTROY:     //窗口销毁消息
		MessageBox(NULL, L"Game Over", L"提示", MB_OK);
		KillTimer(hWnd, DEF_TIMER1);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uID, wParam, lParam);
}
