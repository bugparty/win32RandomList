// Win32RandonList.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32RandonList.h"
using namespace std;
#define MAX_LOADSTRING 100
#define IDC_MAIN_STATUS 101
#define IDC_HEADER 102

// Global Variables:
static HINSTANCE hInst;								// current instance
static HWND hWnd;
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
TCHAR szFailedToLoadCommCtl[MAX_LOADSTRING];
int cxChar, cyChar;
static CsvReader csvReader;
static HWND hStatusbar, hHeader;
static HMENU hMenu;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void InitStatusbar(HWND hStatusbar);
BOOL OpenDialog(HWND hWnd);
void OnHeaderSize(HWND hWnd, UINT state, int cx, int cy);
BOOL OpenSaveDialog(HWND hwnd);

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
	LoadString(hInstance, IDS_FAILED_TO_INIT_COMM_CTL, szFailedToLoadCommCtl, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32RANDONLIST));
	hMenu = (HMENU)LoadMenu(hInstance, MAKEINTRESOURCE(IDC_WIN32RANDONLIST));
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

   hWnd = CreateWindow(szWindowClass, szTitle, 
	   WS_OVERLAPPEDWINDOW | WS_VSCROLL,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, HMENU(hMenu), hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   INITCOMMONCONTROLSEX iccx;
   iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
   iccx.dwICC = ICC_BAR_CLASSES;
   if (!InitCommonControlsEx(&iccx)){
	   MessageBox(hWnd, szFailedToLoadCommCtl, szTitle, MB_OK);
	   return FALSE;
   }
	  

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
	static int cxClient, cyClient;
	static int cxChar, cyChar;
	static int iScollPos;

	
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	wstring s;
	RECT rc = { 0, 0, 0, 0 };
	TCHAR szText[200];
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
			SetScrollPos(hWnd, SB_VERT, iScollPos, FALSE);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case IDM_FILE_SAVE:
			OpenSaveDialog(hWnd);
			break;
		case IDM_RANDOMSORT_ITEM_1:
			csvReader.randSort(0);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case IDM_RANDOMSORT_ITEM_2:
			csvReader.randSort(1);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case IDM_RANDOMSORT_ITEM_3:
			csvReader.randSort(2);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case IDM_RANDOMSORT_ITEM_4:
			csvReader.randSort(3);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case IDM_RANDOMSORT_ITEM_5:
			csvReader.randSort(4);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case IDM_RANDOMSORT_ITEM_6:
			csvReader.randSort(5);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case IDM_RANDOMSORT_ITEM_7:
			csvReader.randSort(6);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case IDM_RANDOMSORT_ITEM_8:
			csvReader.randSort(7);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case IDM_RANDOMSORT_ITEM_9:
			csvReader.randSort(8);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case IDM_RANDOMSORT_ITEM_10:
			csvReader.randSort(9);
			InvalidateRect(hWnd, NULL, TRUE);
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
		// Create the Header control
		
		//hHeader = CreateWindowEx(0, WC_HEADER, 0,
		//	HDS_BUTTONS | WS_CHILD | WS_VISIBLE,
		//	0, 0, 0, 0,
		//	hWnd, (HMENU)IDC_HEADER, hInst, 0);
		//// Resize the header control
		//GetClientRect(hWnd, &rc);
		//OnHeaderSize(hWnd, 0, rc.right, rc.bottom);

		//// Set the font for the header common control
		//SendMessage(hHeader, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), 0);
		// Create the StatusBar
		hStatusbar = CreateWindowEx(0, STATUSCLASSNAME, NULL,
			WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0,
			hWnd, (HMENU)IDC_MAIN_STATUS, GetModuleHandle(NULL), NULL);
		// Store the statusbar control handle as the user data associated with 
		// the parent window so that it can be retrieved for later use.
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)hStatusbar);
		InitStatusbar(hStatusbar);
		// Add 4 Header items
		
		for (UINT i = 0; i < 4; i++)
		{
			HDITEM hdi = { 0 };
			hdi.mask = HDI_WIDTH | HDI_FORMAT | HDI_TEXT;
			hdi.cxy = rc.right / 4;
			hdi.fmt = HDF_CENTER;
			swprintf_s(szText, 200, L"Header  %d", i);
			hdi.pszText = szText;
			hdi.cchTextMax = 200;

			SendMessage(hHeader, HDM_INSERTITEM, i, (LPARAM)&hdi);
		}

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
		
		//TextOut(hdc, 0, 20, s.c_str(), s.length());

		if (csvReader.isOpened()){
			
			const int columnCount = csvReader.getHeadRow()->getColumnSize();
			wstring *heads = new wstring[columnCount];
			
			for (int i = 0; i < columnCount; i++){

				heads[i].append(csvReader.getHeadRow()->getColumn(i));
			}

			TextOut(hdc, 0, 0, (LPWSTR)csvReader.getHeader(), lstrlen(csvReader.getHeader()));


			int curStart = 0;
			EditRow *per;
			int count;
			curStart = iScollPos;
			int end = curStart + cyClient / cyChar;
			for (int i = curStart ; i < end; i++){
				
				csvReader.getRow(i,&per);
				count = per->getColumnSize();
				int j;
				for (j = 0; j < count-1; j++){
					TextOut(hdc, j*COLUMN_WIDTH, (i-curStart + 1)*cyChar, per->getColumn(j),lstrlen(per->getColumn(j)));
				}
				wstring sTailRow(per->getColumn(j));
				int fpos = -1;
				if (fpos = sTailRow.find(_T("\n"))){
					sTailRow.erase(fpos, 2);
				}
				TextOut(hdc, j*COLUMN_WIDTH, (i - curStart + 1)*cyChar,
					sTailRow.c_str(),
					sTailRow.length());
				
				
			}
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_VSCROLL:
		switch (LOWORD(wParam)){
		case SB_LINEUP:
		
			iScollPos -= 1;
			break;
		case SB_LINEDOWN:
			iScollPos += 1;
			break;
		case SB_PAGEUP:
			iScollPos -= cyClient / cyChar;
			break;
		case SB_PAGEDOWN:
			iScollPos += cyClient / cyChar;
			break;
		case SB_THUMBPOSITION:
			iScollPos = HIWORD(wParam);
			break;

		default:
			break;
		}
		iScollPos =max(0, min(iScollPos, csvReader.getRowCount()));
		if (iScollPos != GetScrollPos(hWnd, SB_VERT))
		{
			SetScrollPos(hWnd, SB_VERT, iScollPos, TRUE);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		
		break;
	
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		//InvalidateRect(hStatusbar, NULL, TRUE);
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

//Save Document
BOOL SaveCSV(const TCHAR*filepath){
	csvReader.save(filepath);
	return TRUE;
}
int DialogAskTitle(){
	return MessageBox(hWnd, _T("该CSV文件是否有标题"), _T("询问"), MB_YESNO|MB_ICONQUESTION);
}
//Load Document
BOOL LoadCSV(const TCHAR * filepath){
	int ret = DialogAskTitle();
	if (ret == IDYES)
		csvReader.open(filepath,1);
	else
		csvReader.open(filepath);
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
	SetScrollRange(hwnd, SB_VERT, 0, csvReader.getRowCount(), FALSE);
	const int columnCount = csvReader.getHeadRow()->getColumnSize();
	
	HMENU hmRand = GetSubMenu(hMenu, 1);
	assert(hmRand != NULL);
	for (int i = 0; i < columnCount; i++){
		wstring s(L"以“");
		s += csvReader.getHeadRow()->getColumn(i);
		s += L"”随机排序";
		AppendMenu(hmRand, MF_STRING, IDM_RANDOMSORT_ITEM_1 + i,s.c_str());
	}
	SetMenu(hWnd, hMenu);
	GetSystemMenu(hWnd, TRUE);
	return TRUE;

}
//Display the openfile common dialog
BOOL OpenSaveDialog(HWND hwnd){
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
	ofn.lpstrFileTitle = _T("123.csv");
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	wstring s1, s2;
	if (GetSaveFileName(&ofn)){
		s1 += L"正在保存：";
		s2 += ofn.lpstrFile;
		s1 += s2;
		SendMessage((HWND)GetWindowLongPtr(hWnd, GWLP_USERDATA), SB_SETTEXT, 1, (LPARAM)s1.c_str());
		SaveCSV(ofn.lpstrFile);
	}
	std::wostringstream s;
	s << L"已经保存" << s2 << "     " << L"共保存了" << csvReader.getRowCount() << L"条";
	wstring r(s.str());
	SendMessage((HWND)GetWindowLongPtr(hWnd, GWLP_USERDATA), SB_SETTEXT, 0, (LPARAM)L"编辑中");
	SendMessage((HWND)GetWindowLongPtr(hWnd, GWLP_USERDATA), SB_SETTEXT, 1, (LPARAM)r.c_str());

	return TRUE;

}
void InitStatusbar(HWND hStatusbar)
{
	int statwidths[] = { 150, -1 };
	SendMessage(hStatusbar, SB_SETPARTS, sizeof(statwidths) / sizeof(int), (LPARAM)statwidths);
	SendMessage(hStatusbar, SB_SETTEXT, 0, (LPARAM)_T("无文件打开"));
}
void OnHeaderSize(HWND hWnd, UINT state, int cx, int cy)
{
	// Adjust the position and the layout of the Header control
	RECT rc = { 0, 0, cx, cy };
	WINDOWPOS wp = { 0 };
	HDLAYOUT hdl = { &rc, &wp };


	// hdl.wp retrieves information used to set the size and postion of the  
	// header control within the target rectangle of the parent window. 
	SendMessage(hHeader, HDM_LAYOUT, 0, (LPARAM)&hdl);

	// Set the size and position of the header control based on hdl.wp.
	SetWindowPos(hHeader, wp.hwndInsertAfter,
		wp.x, wp.y, wp.cx, wp.cy + 8, wp.flags);
}
