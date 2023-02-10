#define UNICODE
#pragma comment(linker,"/opt:nowin98")
#include<windows.h>
#include<math.h>

extern "C" int _fltused = 0x9875;

TCHAR szClassName[]=TEXT("Window");

void drawspiral(HDC hdc,int cx,int cy)
{
	const double numRevs=20;
	const double iNumPoints=numRevs*2*(cx+cy);
	cx/=2;
	cy/=2;
	const double np=iNumPoints/numRevs;
	double x=cx*2.0;
	double y=cy;
	for(int i=0;i<iNumPoints;i+=50)
	{
		double fAngle=i*2.0*3.14159265/np;
		double fScale=1.0-i/iNumPoints;
		MoveToEx(hdc,x,y,0);
		x=cx*(1.0+fScale*cos(fAngle));
		y=cy*(1.0+fScale*sin(fAngle));
		LineTo(hdc,x,y);
	}
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc=BeginPaint(hWnd,&ps);
			RECT rect;
			GetClientRect(hWnd,&rect);
			drawspiral(hdc,rect.right,rect.bottom);
			EndPaint(hWnd,&ps);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd,msg,wParam,lParam);
	}
	return 0;
}

EXTERN_C void __cdecl WinMainCRTStartup()
{
	MSG msg;
	HINSTANCE hInstance=GetModuleHandle(0);
	WNDCLASS wndclass={
		CS_HREDRAW|CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		0,
		LoadCursor(0,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW+1),
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd=CreateWindow(
			szClassName,
			TEXT("Window"),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			0,
			CW_USEDEFAULT,
			0,
			0,
			0,
			hInstance,
			0
		);
	ShowWindow(hWnd,SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	ExitProcess(msg.wParam);
}

#if _DEBUG
void main(){}
#endif
