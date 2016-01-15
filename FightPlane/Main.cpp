
#pragma comment( linker, "/subsystem:console /entry:WinMainCRTStartup" )
#include "FPGameManager.h"
#include <iostream>
using namespace std;

#define W_WIDTH 1000
#define W_HEIGHT 800

//��������Ϣ
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	switch (message) {
		case WM_CLOSE:       // �˳���Ϸ
			ShowWindow(hWnd, SW_HIDE);
			PostQuitMessage(0);
			break;
		case WM_LBUTTONDOWN: // ����������
			FPGameManager::GetInstance()->GetGuiManager()->UpdateButtonState(FPGUIManager::MouseState::LBDown, wParam, lParam);
			FPGameManager::GetInstance()->GetGuiManager()->LButtonDownHandle(wParam, lParam);
			break;
		case WM_LBUTTONUP:  // ����������
			FPGameManager::GetInstance()->GetGuiManager()->UpdateButtonState(FPGUIManager::MouseState::LBUp, wParam, lParam);
			FPGameManager::GetInstance()->GetGuiManager()->LButtonUpHandle(wParam, lParam);
			break;
		case WM_MOUSEMOVE:   // ����ƶ�
			FPGameManager::GetInstance()->GetGuiManager()->UpdateButtonState(FPGUIManager::MouseState::Move, wParam, lParam);
			break;
		case WM_KEYDOWN:     // ���̲���
			FPGameManager::GetInstance()->KeyControl(wParam, lParam);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return FALSE;
}

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	//redirectIOToConsole();
	//����OpenGL���ڣ����ñ��⡢��߼���ɫ��
	WNDCLASS wc;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "Name";
	RegisterClass(&wc);

	GameHwnd = CreateWindow(
		"Name",
		"3D�ɻ���ս",
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
		GetSystemMetrics(SM_CXSCREEN) / 2 - W_WIDTH / 2,
		GetSystemMetrics(SM_CYSCREEN) / 2 - W_HEIGHT / 2,
		W_WIDTH,
		W_HEIGHT,
		NULL, NULL,
		hInstance,
		NULL);

	ShowWindow(GameHwnd, SW_SHOW);
	UpdateWindow(GameHwnd);

	// ��ʼ����Ϸ����
	FPGameManager::GetInstance()->InitScene();

	MSG msg;
	//��Ϣ��ȡ�뷢���Լ�����Ϣ�ȴ�ʱʵ�ֶ���
	while (1) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				break;
			}
			else {
				TranslateMessage(&msg);//�����Ϣ�����˳���ʹ��WndProc�����򴰿��ܴ�����
				DispatchMessage(&msg);
			}
		}
		else {
			// ������Ϸ
			FPGameManager::GetInstance()->Draw();
			FPGameManager::GetInstance()->Update();
		}
	}

	EndDialog(GameHwnd, 0);
	return msg.wParam;
}
