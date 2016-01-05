#include "glUtility.h"

#define W_WIDTH 1000
#define W_HEIGHT 800

GL_Utility *myGLRender = NULL;

//��������Ϣ
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch ( message )  {	
	case WM_SIZE:        // ���ڴ�С�ı�
		if (myGLRender) {
			myGLRender->Reshape();
		}
		return 0; 
	case WM_CLOSE:       // �˳���Ϸ
		ShowWindow (hWnd, SW_HIDE);
		PostQuitMessage( 0 );
		return 0;
	case WM_LBUTTONDOWN: // ������
		break;
	case WM_MOUSEMOVE:   // ����ƶ�
		// LOWORD(lParam), HIWORD(lParam) �ֱ����������ƶ��Ƕ�Ӧ��x��y����
		break;
	case WM_KEYDOWN:     // ���̲���
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
	//����OpenGL���ڣ����ñ��⡢��߼���ɫ��
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
		   "3D�ɻ���ս",
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
	//��Ϣ��ȡ�뷢���Լ�����Ϣ�ȴ�ʱʵ�ֶ���
	while (1){
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ){ 
			if (msg.message == WM_QUIT) {
				break;
			}
			else {
				TranslateMessage( &msg );//�����Ϣ�����˳���ʹ��WndProc�����򴰿��ܴ�����
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
