// Win32RandonList.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32RandonList.h"
using namespace std;
#define MAX_LOADSTRING 100
#define IDC_MAIN_STATUS 101

// Global Variables:
HINSTANCE hInst;								// current instance
HWND hWnd;
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
int cxChar, cyChar;
CsvReader csvReader;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void InitStatusbar(HWND hStatusbar);
BOOL OpenDialog(HWND hWnd);

const TCHAR * strPOF = L"无文件打开，请打开文件\n";

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32RANDONLIST, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32RANDONLIST));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32RANDONLIST));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32RANDONLIST);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   INITCOMMONCONTROLSEX iccx;
   iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
   iccx.dwICC = ICC_BAR_CLASSES;
   if (!InitCommonControlsEx(&iccx))
	   return FALSE;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	wstring s;
	HWND hStatusbar;
	
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_FILE_OPEN:
			OpenDialog(hWnd);
			
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_CREATE:
		hdc = GetDC(hWnd);

		//Get Text Height and Width
		TEXTMETRIC tm;
		GetTextMetrics(hdc, &tm);

		cxChar = tm.tmAveCharWidth;
		cyChar = tm.tmHeight + tm.tmExternalLeading;

		ReleaseDC(hWnd, hdc);
		hStatusbar = CreateWindowEx(0, STATUSCLASSNAME, NULL,
			WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0,
			hWnd, (HMENU)IDC_MAIN_STATUS, GetModuleHandle(NULL), NULL);
		// Store the statusbar control handle as the user data associated with 
		// the parent window so that it can be retrieved for later use.
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)hStatusbar);
		InitStatusbar(hStatusbar);


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		TCHAR buffer[20];
		s += L"Text Height";
		wsprintf(buffer, L"%d ", cyChar);
		s.append(buffer);

		s += L" Text Width";
		wsprintf(buffer, L"%d ", cxChar);
		s += buffer;
		
		TextOut(hdc, 0, 20, s.c_str(), s.length());

		if (csvReader.isOpened()){

		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
//Load Document
BOOL LoadCSV(const TCHAR * filepath){
	csvReader.open(filepath);
	HWND hStatusbar = (HWND)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	return TRUE;
}
//Display the openfile common dialog
BOOL OpenDialog(HWND hwnd){
	OPENFILENAME ofn;
	TCHAR szFile[MAX_PATH];


	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.hwndOwner = hwnd;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = TEXT("EXCEL csv files(*.csv)\0*.csv\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFileTitle = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	wstring s1, s2;
	if (GetOpenFileName(&ofn)){
		s1 += L"正在打开：";
		s2 += ofn.lpstrFile;
		s1 += s2;
		SendMessage((HWND)GetWindowLongPtr(hWnd, GWLP_USERDATA), SB_SETTEXT, 1, (LPARAM)s1.c_str());
		LoadCSV(ofn.lpstrFile);
	}
	std::wostringstream s;
	s << L"已经打开了" << s2 << "     " << L"共读取了" << csvReader.getRowCount() << L"条";
	wstring r(s.str());
	SendMessage((HWND)GetWindowLongPtr(hWnd, GWLP_USERDATA), SB_SETTEXT, 0, (LPARAM)L"编辑中");
	SendMessage((HWND)GetWindowLongPtr(hWnd, GWLP_USERDATA), SB_SETTEXT, 1, (LPARAM)r.c_str());
		
	return TRUE;

}
void InitStatusbar(HWND hStatusbar)
{
	int statwidths[] = { 150, -1 };
	SendMessage(hStatusbar, SB_SETPARTS, sizeof(statwidths) / sizeof(int), (LPARAM)statwidths);
	SendMessage(hStatusbar, SB_SETTEXT, 0, (LPARAM)L"无文件打开");
}
