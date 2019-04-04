#include "windows.h"
#include "calc.h"

/*This is a very basic RPN fixed-ish calculator application to demonstrate Windows 3 programming. 
It is not intended to be a productive calculator, only a retro programming demo
Originally created March 2018 by BSS*/

const int IDL_RES = 101, IDB_INIT = 110, IDB_CLR = 102, IDB_FUNC = 103; /*Control IDs*/

double immed, accum;

int PASCAL WinMain(hInstance, hPrevInstance, lpszCmdLine, nCmdShow) /*Entry point*/
	HANDLE hInstance,
	hPrevInstance; /*Declaring parameters this way was required for ANSI C*/
LPSTR lpszCmdLine;
int nCmdShow;
{
	MSG msg;
	HWND hWnd;
	PWNDCLASS pCalcClass;

	if (!hPrevInstance)
	{ /*Windows 3 and before only allow registering a window class once*/
		pCalcClass = (PWNDCLASS)LocalAlloc(LPTR, sizeof(WNDCLASS));

		pCalcClass->lpszMenuName = (LPSTR)NULL;
		pCalcClass->lpszClassName = "CalcDemo";
		pCalcClass->hInstance = hInstance;
		pCalcClass->style = CS_HREDRAW | CS_VREDRAW;
		pCalcClass->lpfnWndProc = MainWinProc;
		pCalcClass->hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		pCalcClass->hIcon = LoadIcon(hInstance, "AppIcon");

		if (!RegisterClass((LPWNDCLASS)pCalcClass))
			return FALSE;
		LocalFree((HANDLE)pCalcClass);
	}

	hWnd = CreateWindow("CalcDemo", "Calculator Demo", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 200, 250, (HWND)NULL, (HMENU)NULL, (HANDLE)hInstance, (LPSTR)NULL);

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage((LPMSG)&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

long FAR PASCAL MainWinProc(hWnd, message, wParam, lParam) /*Event handling callback*/
	HWND hWnd;
unsigned message;
WORD wParam;
LONG lParam;
{
	HWND btn_clr, btn_func, btn_num, lbl_res;
	int i, j, indig;
	LPSTR btntext = "0";
	char strres[300];
	switch (message)
	{
	case WM_CREATE:
		immed = 0;
		accum = 0;
		btn_clr = CreateWindow("BUTTON", "Clear", WS_VISIBLE | WS_CHILD, 10, 40, 50, 20, hWnd, (HMENU)IDB_CLR, GetModuleHandle(NULL), (LPSTR)NULL);
		lbl_res = CreateWindow("STATIC", "0", WS_VISIBLE | WS_CHILD, 5, 10, 250, 15, hWnd, (HMENU)IDL_RES, GetModuleHandle(NULL), (LPSTR)NULL);
		btn_func = CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD, 10, 70, 20, 20, hWnd, (HMENU)IDB_FUNC, GetModuleHandle(NULL), (LPSTR)NULL);
		btn_func = CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD, 10, 100, 20, 20, hWnd, (HMENU)(IDB_FUNC + 1), GetModuleHandle(NULL), (LPSTR)NULL);
		btn_func = CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD, 10, 130, 20, 20, hWnd, (HMENU)(IDB_FUNC + 2), GetModuleHandle(NULL), (LPSTR)NULL);
		btn_func = CreateWindow("BUTTON", "\\", WS_VISIBLE | WS_CHILD, 10, 160, 20, 20, hWnd, (HMENU)(IDB_FUNC + 3), GetModuleHandle(NULL), (LPSTR)NULL);
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
			{
				btntext[0] = (char)('1' + i * 3 + j);
				btn_num = CreateWindow("BUTTON", btntext, WS_VISIBLE | WS_CHILD, 40 + 30 * j, 70 + 30 * i, 20, 20, hWnd, (HMENU)(1 + IDB_INIT + i * 3 + j), GetModuleHandle(NULL), (LPSTR)NULL);
			}
		btn_num = CreateWindow("BUTTON", "0", WS_CHILD | WS_VISIBLE, 40, 160, 40, 20, hWnd, (HMENU)(IDB_INIT), GetModuleHandle(NULL), (LPSTR)NULL);
		return (LONG)TRUE;
		break;
	case WM_COMMAND:
		if (HIWORD(wParam) == BN_CLICKED)
		{ /*Button clicked - check ID to see which one and perform correct action*/
			switch (LOWORD(wParam))
			{
			case 102: /*IDB_CLR*/
				immed = 0;
				accum = 0;
				DestroyWindow(lbl_res);
				lbl_res = CreateWindow("STATIC", "0", WS_VISIBLE | WS_CHILD, 5, 10, 250, 15, hWnd, (HMENU)IDL_RES, GetModuleHandle(NULL), (LPSTR)NULL);
				break;
			case 103:
				accum += immed;
				immed = 0;
				sprintf(strres, "%f", accum);
				DestroyWindow(lbl_res);
				lbl_res = CreateWindow("STATIC", (LPSTR)strres, WS_VISIBLE | WS_CHILD, 5, 10, 250, 15, hWnd, (HMENU)IDL_RES, GetModuleHandle(NULL), (LPSTR)NULL);
				break;
			case 104:
				accum -= immed;
				immed = 0;
				sprintf(strres, "%f", accum);
				DestroyWindow(lbl_res);
				lbl_res = CreateWindow("STATIC", (LPSTR)strres, WS_VISIBLE | WS_CHILD, 5, 10, 250, 15, hWnd, (HMENU)IDL_RES, GetModuleHandle(NULL), (LPSTR)NULL);
				break;
			case 105:
				accum *= immed;
				immed = 0;
				sprintf(strres, "%f", accum);
				DestroyWindow(lbl_res);
				lbl_res = CreateWindow("STATIC", (LPSTR)strres, WS_VISIBLE | WS_CHILD, 5, 10, 250, 15, hWnd, (HMENU)IDL_RES, GetModuleHandle(NULL), (LPSTR)NULL);
				break;
			case 106:
				if (immed != 0)
					accum /= immed;
				immed = 0;
				sprintf(strres, "%f", accum);
				DestroyWindow(lbl_res);
				lbl_res = CreateWindow("STATIC", (LPSTR)strres, WS_VISIBLE | WS_CHILD, 5, 10, 250, 15, hWnd, (HMENU)IDL_RES, GetModuleHandle(NULL), (LPSTR)NULL);
				break;
			default:
				if (immed < 1e24)
				{ /*Just put some limit here to prevent insanity and overflows*/
					immed *= 10;
					immed += LOWORD(wParam) - IDB_INIT;
					sprintf(strres, "%f", immed);
					DestroyWindow(lbl_res);
					lbl_res = CreateWindow("STATIC", strres, WS_VISIBLE | WS_CHILD, 5, 10, 250, 15, hWnd, (HMENU)IDL_RES, GetModuleHandle(NULL), (LPSTR)NULL);
				}
			}
		}
		return (LONG)TRUE;
	case WM_DESTROY:
		return PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return (LONG)TRUE;
}
