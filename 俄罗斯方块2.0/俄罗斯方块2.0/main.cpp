#include "Tetris.h"
#include "resource.h"


LRESULT CALLBACK WinProc(HWND hWnd, UINT uID, WPARAM wParam, LPARAM lParam);
//������
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// 1������������
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

	// 2��ע�ᴰ����
	ATOM nRes = RegisterClassEx(&wce);
	if (0 == nRes)
	{
		return 1;
	}

	// 3����������
	HWND hWnd = CreateWindowEx(WS_EX_TOPMOST, TEXT("window"), TEXT("Tetris"), WS_OVERLAPPEDWINDOW, 100, 30, 500, 645, NULL, NULL, hInstance, NULL);
	if (NULL == hWnd)
	{
		return 1;
	}
	// 4����ʾ����
	ShowWindow(hWnd, SW_SHOWNORMAL);

	// 5�����´���
	UpdateWindow(hWnd);

	// 6����Ϣѭ��
	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//���������Ϣת��Ϊ�ַ���Ϣ
		DispatchMessage(&msg);//����Ϣ�ַ������ڴ�����
	}

	return 0;
}

//�ص�����
LRESULT CALLBACK WinProc(HWND hWnd, UINT uID, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT pt;
	HDC hDc;
	//
	switch(uID)
	{
	case WM_CREATE: //��ʼ������
		MessageBox(NULL, L"		WELCOME\nMade Lucci", L"Lucci's Square", MB_OK);
		OnCreate();
		break;
	case WM_TIMER:
		//��ʱ��
		OnTimer(hWnd);
		break;
	case WM_PAINT:       //���ڻ�ͼ��Ϣ
		hDc = BeginPaint(hWnd, &pt);

		//�����ڵ�����
		OnPaint(hDc);
		EndPaint(hWnd, &pt);
		break;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_RETURN:
			//��ʼ����
			OnReturn(hWnd);
			break;
		case VK_LEFT:
			//��������
			OnLeft(hWnd);
			break;
		case VK_RIGHT:
			//��������
			OnRight(hWnd);
			break;
		case VK_UP:
			//�������
			OnChange(hWnd);
			break;
		case VK_DOWN:
			//�����������
			OnDown(hWnd);
			break;
		}
		break;
	case WM_DESTROY:     //����������Ϣ
		MessageBox(NULL, L"Game Over", L"��ʾ", MB_OK);
		KillTimer(hWnd, DEF_TIMER1);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uID, wParam, lParam);
}
