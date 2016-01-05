#include <windows.h>     
#include <crtdbg.h>
#include "main.h"

//处理窗口信息
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch ( message )  {	
	case WM_SIZE:        // 窗口大小改变
		Reshape();
		return 0; 
	case WM_CLOSE:       // 退出游戏
		ShowWindow (hWnd, SW_HIDE);
		PostQuitMessage( 0 );
		return 0;
	case WM_LBUTTONDOWN: // 鼠标左键
		// TODO
		break;
	case WM_MOUSEMOVE:   // 光标移动
		// LOWORD(lParam), HIWORD(lParam) 分别代表鼠标光标移动是对应的x和y坐标
		break;
	case WM_KEYDOWN:     // 键盘操作
		KeyHandle(wParam, lParam);
		break;
	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}
}

int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR     lpCmdLine,
					 int       nCmdShow)
{
	//创建OpenGL窗口，设置标题、宽高及颜色数
	WNDCLASS wc;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "Name";
	RegisterClass( &wc );
	
	hWnd = CreateWindow(
			"Name",
		   "3D飞机大战",
			WS_TILEDWINDOW | WS_VISIBLE,
			GetSystemMetrics( SM_CXSCREEN )/2 - W_WIDTH /2,
			GetSystemMetrics( SM_CYSCREEN )/2 - W_HEIGHT /2,
			W_WIDTH,
			W_HEIGHT,
			NULL, NULL,
			hInstance,
			NULL );
	
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	
	//初始化
	InitOpenGL();
	InitScene();
	Reshape();

	MSG msg;
	//消息获取与发送以及无消息等待时实现动画
	while (1){
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ){ 
			if (msg.message == WM_QUIT) {
				break;
			}
			else {
				TranslateMessage( &msg );//如果消息不是退出，使得WndProc（）或窗口能处理它
				DispatchMessage( &msg );
			}
		}
		else{ 
			// 此处实现OpenGL 动画，如果程序被激活并且ESC没有被按下，可以渲染场景及交换缓冲区
			DrawScene();
			SwapBuffers(hDC); 
		}
	}

	DestroyOpenGL();
	EndDialog(hWnd, 0);
	return msg.wParam;
}
