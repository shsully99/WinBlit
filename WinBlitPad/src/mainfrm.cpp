//***************************************************************************
//*
//*		Name		: Mainfrm.cpp
//*							
//*		$Revision:$
//*
//*		Date        : 20-Feb-2002
//*
//*		Author      : Sean Sullivan
//*
//*
//*		Copyright (c) Pata-Sucia Ltd 2001
//*		All rights reserved
//*
//*		This document contains matter that is confidential,
//*		proprietary information of Pata-Sucia 
//*
//***************************************************************************

//***************************************************************************
//*		M O D U L E   D E S C R I P T I O N
//***************************************************************************
//*	
//*		Implementation for  BlitPad
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

#include "stdafx.h"
#include "Mainfrm.h"
#include "PAKVal.h"
#include <atldlgs.h>
#include "Registry.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

LRESULT  CMainFrame::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	_CrtDumpMemoryLeaks();

	RECT rcClient; 
	GetWindowRect(&rcClient);
	CRegistry Reg;
	if (TRUE == Reg.SetRootKey(HKEY_CURRENT_USER))
	{
		if (TRUE == Reg.SetKey(lpcstrWinBlitPadRegKey , TRUE))
		{
			Reg.WriteInt("top", rcClient.top); 
			Reg.WriteInt("left", rcClient.left); 
			Reg.WriteInt("bottom", rcClient.bottom); 
			Reg.WriteInt("right", rcClient.right); 
		}
	}
	// TODO : Add Code for message handler. Call DefWindowProc if necessary.
	return 0;
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	if(CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
		return TRUE;
	return m_view.PreTranslateMessage(pMsg);
}

BOOL CMainFrame::OnIdle()
{
	return FALSE;
}

LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_hWndClient = m_view.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);

	RECT rcClient; 
	CRegistry Reg; 
	Reg.SetRootKey(HKEY_CURRENT_USER);
	if (TRUE == Reg.SetKey(lpcstrWinBlitPadRegKey , FALSE))
	{
		if (TRUE == Reg.ReadInt("top", rcClient.top))
		{
			Reg.ReadInt("left", rcClient.left); 
			Reg.ReadInt("bottom", rcClient.bottom); 
			Reg.ReadInt("right", rcClient.right); 
			::MoveWindow(m_hWnd, rcClient.left, rcClient.top,  rcClient.right - rcClient.left, rcClient.bottom - rcClient.top, TRUE); 
		}
	}

	// Stuff license status into m_view
	CPAKVal* pPAKVal = new CPAKVal;		 
	m_view.SetLic	(pPAKVal->Val(eWinBlitPad,	ciLatestVersion) * ciLicMultiplier);
	delete pPAKVal; 

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	HMENU hMenu =		GetMenu();
	HMENU hFileMenu =	::GetSubMenu(hMenu, FILE_MENU_POSITION);
#ifdef _DEBUG
	// absolute position, can change if menu changes
	TCHAR szMenuString[100];
	::GetMenuString(hFileMenu, RECENT_MENU_POSITION, szMenuString, sizeof(szMenuString), MF_BYPOSITION);
	ATLASSERT(lstrcmp(szMenuString, _T("Recent &Files")) == 0);
#endif //_DEBUG
	HMENU hMruMenu =	::GetSubMenu(hFileMenu, RECENT_MENU_POSITION);

	m_mru.SetMenuHandle(hMruMenu);

	m_mru.ReadFromRegistry(lpcstrWinBlitPadRegKey);

	// Change title of WinBlit Pad if necessary 
	if (m_view.GetLic() <= (eTrialLicense  * ciLicMultiplier) )
	{
		USES_CONVERSION; 
		CComBSTR bstrTemp;
		bstrTemp.LoadString(IDR_MAINFRAME); 
		bstrTemp.Append(cbstrLicStat[1 + (m_view.GetLic()/ciLicMultiplier)]);
		SendMessage (WM_SETTEXT, NULL, (LPARAM) OLE2T(bstrTemp));
		EnableMenuItem(GetMenu(), ID_APP_REGISTER, MF_ENABLED);
	}
	m_bLoggingStarted = false; 

	// Start logging as a client
	if (lLogLevel == -1)
	{
		IUnknown *pUnk;
		CLSID clsLogApp;
		CLSIDFromProgID(L"ATLLogApp.BlitLog.1", &clsLogApp);
		if (SUCCEEDED(GetActiveObject(clsLogApp,  NULL,  (IUnknown**)&pUnk)))
		{
			m_Log = pUnk;
			if (m_Log) m_Log->get_Level(&lLogLevel);
			ATL_TRACE0(e_LOGFLOW," Started logging in WinBlitPad"); 
		}
	}
	// Ask the control if it wants to show startup tips. 
	m_view.ShowHelp(3);
	return 0;
}

LRESULT CMainFrame::OnFileOpen(WORD wNotifyCode, WORD wID, HWND HWndCtl, BOOL& bHandled)
{
	CFileDialog dlg(TRUE, NULL, _T(""),  OFN_OVERWRITEPROMPT, lpcstrFilter);
	int nRet = dlg.DoModal();
	if (IDOK == nRet)
	{
		char *pch = strstr(dlg.m_ofn.lpstrFile, "Blit123" );
		if (pch)
		{
			StartLogging();
		}
		else			
		{
			int iA = m_view.Initialise (dlg.m_ofn.lpstrFile); 
			ATL_TRACE1 (e_LOGDETAIL, "Return from view Initi %d ",iA ); 
			if (0 == iA)
			{
				// Add to mru list. 
				m_mru.AddToList(dlg.m_ofn.lpstrFile);
				m_mru.WriteToRegistry(lpcstrWinBlitPadRegKey);
			}
			else if (-1 == iA)
			{
				MessageBox("Failed to open data source", "Error", MB_OK); 
			}
		}
	}
	ATL_TRACE0 (e_LOGDETAIL, "rETURN FROM oNfILEoPEN");
	return 0;
}

LRESULT  CMainFrame::OnFileRecent(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// get file name from the MRU list
	TCHAR szFile[MAX_PATH];
	if(m_mru.GetFromList(wID, szFile))
	{
		// find file name without the path
		LPTSTR lpstrFileName = szFile;
		for(int i = lstrlen(szFile) - 1; i >= 0; i--)
		{
			if(szFile[i] == '\\')
			{
				lpstrFileName = &szFile[i + 1];
				break;
			}
		}
		// open file
		ATLTRACE(_T("File path: %s\n"), szFile);
		if (m_view.Initialise (szFile) < 0)
		{
			m_mru.RemoveFromList(wID);
		}
		else
		{
			m_mru.MoveToTop(wID);
		}
		m_mru.WriteToRegistry(lpcstrWinBlitPadRegKey);
	}
	else
	{
		::MessageBeep(MB_ICONERROR);
	}
	return 0;
}

LRESULT  CMainFrame::OnEditPaste(WORD wNotifyCode, WORD wID, HWND HWndCtl, BOOL& bHandled)
{
	m_view.Initialise ("<<paste>>"); 
	return 0;
}


LRESULT CMainFrame::OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	StopLogging(); 
	RECT m_Rect;
	GetWindowRect(&m_Rect); 
	PostMessage(WM_CLOSE);
	return 0;
}

LRESULT CMainFrame::OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	return 0;
}

LRESULT CMainFrame::OnFileNewWindow(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{		
	::PostThreadMessage(_Module.m_dwMainThreadID, WM_USER, 0, 0L);
	return 0;
}

LRESULT CMainFrame::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_view.About(); 
	return 0;
}

LRESULT CMainFrame::OnContact(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_view.ShowHelp(4); 
	return 0;
}

LRESULT CMainFrame::OnHelpTopics(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_view.ShowHelp(1); 
	return 0;
}

LRESULT CMainFrame::OnDemo(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_view.ShowHelp(2); 
	return 0;
}

LRESULT CMainFrame::OnAppRegister(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_view.Register(); 
	return 0;
}

void CMainFrame::StartLogging () 
{
	// Kick off trace 
	CLSID clsAtl;
	CLSIDFromProgID(L"ATLLogApp.BlitLog.1", &clsAtl);
	HRESULT hr;
	hr = m_Log.CreateInstance(__uuidof(CoLogger));
	if(SUCCEEDED(hr)) 
	{
		hr = m_Log->Initialize();	
			
		if (SUCCEEDED(hr))
		{
			m_bLoggingStarted = true; 
			CComPtr<IUnknown> pUnk;
			m_Log.QueryInterface(IID_IUnknown, (void **) &pUnk);
			RegisterActiveObject(pUnk, clsAtl, ACTIVEOBJECT_STRONG,  &m_dwCookie); 
			lLogLevel = 1; 
			ATL_TRACE0(1, " *** STARTED LOGGING in BlitPad *** ");
		}
	}
};

void CMainFrame::StopLogging ()
{
	if (true == m_bLoggingStarted)
	{
		if (m_Log)
		{
			m_Log->UnInitialize();
			m_bLoggingStarted = false; 
			RevokeActiveObject(m_dwCookie, NULL); 
		}
	}
}; 