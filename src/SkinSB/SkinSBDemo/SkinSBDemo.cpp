// SkinSBDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SkinSBDemo.h"
#include "SkinSBDemoDlg.h"

//包含头文件
#include <detours.h>
#include <skinsb.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
// 申明钩子
//////////////////////////////////////////////////////////////////////////
#if (DETOURS_VERSION >= 20100)
int (WINAPI* SetScrollInfoT) (HWND, int, LPCSCROLLINFO, BOOL) = SetScrollInfo;
BOOL(WINAPI* GetScrollInfoT) (HWND, int, LPSCROLLINFO) = GetScrollInfo;
int (WINAPI* SetScrollPosT) (HWND, int, int, BOOL) = SetScrollPos;
int (WINAPI* GetScrollPosT) (HWND, int) = GetScrollPos;
BOOL(WINAPI* GetScrollRangeT) (HWND, int, LPINT, LPINT) = GetScrollRange;
BOOL(WINAPI* SetScrollRangeT) (HWND, int, int, int, BOOL) = SetScrollRange;
BOOL(WINAPI* ShowScrollBarT) (HWND, int, BOOL) = ShowScrollBar;
BOOL(WINAPI* EnableScrollBarT) (HWND, UINT, UINT) = EnableScrollBar;
#else
DETOUR_TRAMPOLINE(int   WINAPI SetScrollInfoT(HWND, int, LPCSCROLLINFO, BOOL), SetScrollInfo)
DETOUR_TRAMPOLINE(BOOL  WINAPI GetScrollInfoT(HWND, int, LPSCROLLINFO), GetScrollInfo)
DETOUR_TRAMPOLINE(int   WINAPI SetScrollPosT(HWND, int, int, BOOL), SetScrollPos)
DETOUR_TRAMPOLINE(int   WINAPI GetScrollPosT(HWND, int), GetScrollPos)
DETOUR_TRAMPOLINE(BOOL  WINAPI GetScrollRangeT(HWND, int, LPINT, LPINT), GetScrollRange)
DETOUR_TRAMPOLINE(BOOL  WINAPI SetScrollRangeT(HWND, int, int, int, BOOL), SetScrollRange)
DETOUR_TRAMPOLINE(BOOL  WINAPI ShowScrollBarT(HWND, int, BOOL), ShowScrollBar)
DETOUR_TRAMPOLINE(BOOL  WINAPI EnableScrollBarT(HWND, UINT, UINT), EnableScrollBar)
#endif


int WINAPI SetScrollInfoD(HWND hwnd, int fnBar, LPCSCROLLINFO lpsi, BOOL bRedraw)
{
	if( SkinSB_IsValid(hwnd) )
		return SkinSB_SetScrollInfo(hwnd, fnBar, lpsi, bRedraw);
	else
		return SetScrollInfoT(hwnd, fnBar, lpsi, bRedraw);
}

BOOL WINAPI GetScrollInfoD(HWND hwnd, int fnBar, LPSCROLLINFO lpsi)
{
	if( SkinSB_IsValid(hwnd) )
		return SkinSB_GetScrollInfo(hwnd, fnBar, lpsi);
	else
		return GetScrollInfoT(hwnd, fnBar, lpsi);
}

int WINAPI SetScrollPosD(HWND hwnd, int nBar, int nPos, BOOL bRedraw)
{
	if( SkinSB_IsValid(hwnd) )
		return SkinSB_SetScrollPos(hwnd, nBar, nPos, bRedraw);
	else
		return SetScrollPosT(hwnd, nBar, nPos, bRedraw);
}

int WINAPI GetScrollPosD(HWND hwnd, int nBar)
{
	if( SkinSB_IsValid(hwnd) )
		return SkinSB_GetScrollPos(hwnd, nBar);
	else
		return GetScrollPosT(hwnd, nBar);
}

BOOL WINAPI SetScrollRangeD(HWND hwnd, int nBar, int nMinPos, int nMaxPos, BOOL bRedraw)
{
	if( SkinSB_IsValid(hwnd) )
		return SkinSB_SetScrollRange(hwnd, nBar, nMinPos, nMaxPos, bRedraw);
	else
		return SetScrollRangeT(hwnd, nBar, nMinPos, nMaxPos, bRedraw);
}

BOOL WINAPI GetScrollRangeD(HWND hwnd, int nBar, LPINT lpMinPos, LPINT lpMaxPos)
{
	if( SkinSB_IsValid(hwnd) )
		return SkinSB_GetScrollRange(hwnd, nBar, lpMinPos, lpMaxPos);
	else
		return GetScrollRangeT(hwnd, nBar, lpMinPos, lpMaxPos);
}

BOOL WINAPI ShowScrollBarD(HWND hwnd, int nBar, BOOL bShow)
{
	if( SkinSB_IsValid(hwnd) )
		return SkinSB_ShowScrollBar(hwnd, nBar, bShow);
	else
		return ShowScrollBarT(hwnd, nBar, bShow);
}

BOOL WINAPI EnableScrollBarD(HWND hwnd, UINT wSBflags, UINT wArrows)
{
	if( SkinSB_IsValid(hwnd) )
		return SkinSB_EnableScrollBar(hwnd, wSBflags, wArrows);
	else
		return EnableScrollBarT(hwnd, wSBflags, wArrows);
}

// CSkinSBDemoApp

BEGIN_MESSAGE_MAP(CSkinSBDemoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CSkinSBDemoApp construction

CSkinSBDemoApp::CSkinSBDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CSkinSBDemoApp object

CSkinSBDemoApp theApp;


// CSkinSBDemoApp initialization

BOOL CSkinSBDemoApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	AfxInitRichEdit2();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

#if (DETOURS_VERSION >= 20100)
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	// 加载钩子
	::DetourAttach(&(PVOID&)SetScrollInfoT, SetScrollInfoD);
	::DetourAttach(&(PVOID&)GetScrollInfoT, GetScrollInfoD);
	::DetourAttach(&(PVOID&)SetScrollPosT, SetScrollPosD);
	::DetourAttach(&(PVOID&)GetScrollPosT, GetScrollPosD);
	::DetourAttach(&(PVOID&)SetScrollRangeT, SetScrollRangeD);
	::DetourAttach(&(PVOID&)GetScrollRangeT, GetScrollRangeD);
	::DetourAttach(&(PVOID&)ShowScrollBarT, ShowScrollBarD);
	::DetourAttach(&(PVOID&)EnableScrollBarT, EnableScrollBarD);
	DetourTransactionCommit();
#else
	::DetourFunctionWithTrampoline((PBYTE)SetScrollInfoT, (PBYTE)SetScrollInfoD);
	::DetourFunctionWithTrampoline((PBYTE)GetScrollInfoT, (PBYTE)GetScrollInfoD);
	::DetourFunctionWithTrampoline((PBYTE)SetScrollPosT, (PBYTE)SetScrollPosD);
	::DetourFunctionWithTrampoline((PBYTE)GetScrollPosT, (PBYTE)GetScrollPosD);
	::DetourFunctionWithTrampoline((PBYTE)SetScrollRangeT, (PBYTE)SetScrollRangeD);
	::DetourFunctionWithTrampoline((PBYTE)GetScrollRangeT, (PBYTE)GetScrollRangeD);
	::DetourFunctionWithTrampoline((PBYTE)ShowScrollBarT, (PBYTE)ShowScrollBarD);
	::DetourFunctionWithTrampoline((PBYTE)EnableScrollBarT, (PBYTE)EnableScrollBarD);
#endif

	CSkinSBDemoDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CSkinSBDemoApp::ExitInstance()
{
#if (DETOURS_VERSION >= 20100)    
	// 卸载钩子
	::DetourDetach(&(PVOID&)SetScrollInfoT, SetScrollInfoD);
	::DetourDetach(&(PVOID&)GetScrollInfoT, GetScrollInfoD);
	::DetourDetach(&(PVOID&)SetScrollPosT, SetScrollPosD);
	::DetourDetach(&(PVOID&)GetScrollPosT, GetScrollPosD);
	::DetourDetach(&(PVOID&)SetScrollRangeT, SetScrollRangeD);
	::DetourDetach(&(PVOID&)GetScrollRangeT, GetScrollRangeD);
	::DetourDetach(&(PVOID&)ShowScrollBarT, ShowScrollBarD);
	::DetourDetach(&(PVOID&)EnableScrollBarT, EnableScrollBarD);
#else
	::DetourRemove((PBYTE)SetScrollInfoT, (PBYTE)SetScrollInfoD);
	::DetourRemove((PBYTE)SetScrollPosT, (PBYTE)SetScrollPosD);
	::DetourRemove((PBYTE)GetScrollInfoT, (PBYTE)GetScrollInfoD);
	::DetourRemove((PBYTE)GetScrollPosT, (PBYTE)GetScrollPosD);
	::DetourRemove((PBYTE)SetScrollRangeT, (PBYTE)SetScrollRangeD);
	::DetourRemove((PBYTE)GetScrollRangeT, (PBYTE)GetScrollRangeD);
	::DetourRemove((PBYTE)ShowScrollBarT, (PBYTE)ShowScrollBarD);
	::DetourRemove((PBYTE)EnableScrollBarT, (PBYTE)EnableScrollBarD);
#endif

	return CWinApp::ExitInstance();
}
