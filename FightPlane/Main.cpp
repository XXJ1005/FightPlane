
#pragma comment( linker, "/subsystem:console /entry:WinMainCRTStartup" )
#include "FPGameManager.h"
#include <iostream>
using namespace std;

#define W_WIDTH 1000
#define W_HEIGHT 800

//处理窗口信息
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	switch (message) {
		case WM_CLOSE:       // 退出游戏
			ShowWindow(hWnd, SW_HIDE);
			PostQuitMessage(0);
			break;
		case WM_LBUTTONDOWN: // 鼠标左键按下
			FPGameManager::GetInstance()->GetGuiManager()->UpdateButtonState(FPGUIManager::MouseState::LBDown, wParam, lParam);
			FPGameManager::GetInstance()->GetGuiManager()->LButtonDownHandle(wParam, lParam);
			break;
		case WM_LBUTTONUP:  // 鼠标左键起来
			FPGameManager::GetInstance()->GetGuiManager()->UpdateButtonState(FPGUIManager::MouseState::LBUp, wParam, lParam);
			FPGameManager::GetInstance()->GetGuiManager()->LButtonUpHandle(wParam, lParam);
			break;
		case WM_MOUSEMOVE:   // 光标移动
			FPGameManager::GetInstance()->GetGuiManager()->UpdateButtonState(FPGUIManager::MouseState::Move, wParam, lParam);
			break;
		case WM_KEYDOWN:     // 键盘操作
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
	//创建OpenGL窗口，设置标题、宽高及颜色数
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
		"3D飞机大战",
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

	// 初始化游戏场景
	FPGameManager::GetInstance()->InitScene();

	MSG msg;
	//消息获取与发送以及无消息等待时实现动画
	while (1) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				break;
			}
			else {
				TranslateMessage(&msg);//如果消息不是退出，使得WndProc（）或窗口能处理它
				DispatchMessage(&msg);
			}
		}
		else {
			// 绘制游戏
			FPGameManager::GetInstance()->Draw();
			FPGameManager::GetInstance()->Update();
		}
	}

	EndDialog(GameHwnd, 0);
	return msg.wParam;
}
