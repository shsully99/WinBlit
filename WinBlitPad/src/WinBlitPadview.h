//***************************************************************************
//*
//*		Name		: WinBlitPadview.h
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
//*		Interface for CWinBlitPadview.h
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

#if !defined(AFX_WINBLITPADVIEW_H__41002761_6FC1_11D5_862B_D445D2000000__INCLUDED_)
#define AFX_WINBLITPADVIEW_H__41002761_6FC1_11D5_862B_D445D2000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "stdafx.h"
#include <atlhost.h>

#include "WinBlitReaderManager_i.c"
#include "WinBlitReaderManager.h"

class CWinBlitPadView : public CWindowImpl<CWinBlitPadView>
{
public:
	LONG _cRef;
	int m_iLic; 
	DECLARE_WND_CLASS(NULL)
	bool  m_bInitialised;

	// Create the Atl Browser Container
	CComPtr<IBrowserWrapper> m_pBrowserWrapper;

	CComQIPtr<IWinBlitReader> m_WinBlitReader;
	CAxWindow m_wndView;
	BOOL m_bRegWordWarning; 
	BOOL m_bRegHTMLWarning; 

	IOleObject*  _pIOleObject;
	IWebBrowser2*      _pWebBrowserOC;
	DWORD m_dwCookie;
	DWORD m_dwTickCount; 

	void SetLic(int iLic);
	int GetLic();
	
	BOOL PreTranslateMessage(MSG* pMsg);

	// Required to forward messages to the control
	BOOL PreTranslateAccelerator(MSG* pMsg);

	BEGIN_MSG_MAP(CWinBlitPadView)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_KEYDOWN,	OnKeyDown)
		MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(ID_FILE_OPEN,OnFileOpen)
		COMMAND_ID_HANDLER(ID_APP_EXIT,OnFileExit)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_ERASEBKGND,OnErase)
		MESSAGE_HANDLER(WM_MOVE, OnMove)
		MESSAGE_HANDLER(WM_CHAR, OnChar)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
	END_MSG_MAP()
	
	int ShowHelp(long);
	int About();
	void Register(); 
	int Initialise (LPCTSTR pszDataSource);
	int UnInitialise	();
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	void OnFinalMessage(HWND /*hWnd*/);

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnErase(UINT /* uMsg */, WPARAM /* wParam */, LPARAM /* lParam */, BOOL& bHandled);
	LRESULT OnSize(UINT /* uMsg */, WPARAM /* wParam */, LPARAM /* lParam */, BOOL& /* lResult */);
	LRESULT OnFileOpen(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnFileExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINBLITPADVIEW_H__41002761_6FC1_11D5_862B_D445D2000000__INCLUDED_)
