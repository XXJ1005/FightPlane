#include "glUtility.h"

#define W_WIDTH 1000
#define W_HEIGHT 800

GL_Utility *myGLRender = NULL;

//处理窗口信息
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch ( message )  {	
	case WM_SIZE:        // 窗口大小改变
		if (myGLRender) {
			myGLRender->Reshape();
		}
		return 0; 
	case WM_CLOSE:       // 退出游戏
		ShowWindow (hWnd, SW_HIDE);
		PostQuitMessage( 0 );
		return 0;
	case WM_LBUTTONDOWN: // 鼠标左键
		break;
	case WM_MOUSEMOVE:   // 光标移动
		// LOWORD(lParam), HIWORD(lParam) 分别代表鼠标光标移动是对应的x和y坐标
		break;
	case WM_KEYDOWN:     // 键盘操作
		myGLRender->KeyHandle(wParam, lParam);
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
	
	HWND hWnd = CreateWindow(
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
	
	myGLRender = new GL_Utility(hWnd);
	double camPos[3] = { 0, 0, 1.2 };
	double camView[3] = {0, 0, -1};
	int walkSpeed = 2;
	myGLRender->InitScene(camPos, camView, walkSpeed);

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
			myGLRender->Draw();
		}
	}

	delete myGLRender;
	EndDialog(hWnd, 0);
	return msg.wParam;
}
