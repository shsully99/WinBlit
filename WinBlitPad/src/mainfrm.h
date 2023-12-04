//***************************************************************************
//*
//*		Name		: Mainfrm.h
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
//*		Interface for BlitPad
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

#if !defined(AFX_MAINFRM_H__4100275E_6FC1_11D5_862B_D445D2000000__INCLUDED_)
#define AFX_MAINFRM_H__4100275E_6FC1_11D5_862B_D445D2000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define FILE_MENU_POSITION	0
#define RECENT_MENU_POSITION	3

#include "stdafx.h"
#import  "..\import\build\ATLLogApp.tlb" no_namespace named_guids
#include "atlframe.h"
#include "WinBlitPadView.h"
#include "resource.h"

class CMainFrame : public CFrameWindowImpl<CMainFrame>, public CUpdateUI<CMainFrame>,
		public CMessageFilter, public CIdleHandler
{
public:
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

	CWinBlitPadView m_view;
	CRecentDocumentList m_mru;
	bool m_bLoggingStarted; 
	DWORD m_dwCookie; 

	virtual BOOL PreTranslateMessage(MSG* pMsg);

	virtual BOOL OnIdle();

	BEGIN_MSG_MAP(CMainFrame)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
		COMMAND_ID_HANDLER(ID_FILE_NEW_WINDOW, OnFileNewWindow)
		COMMAND_ID_HANDLER(ID_FILE_OPEN, OnFileOpen)
		COMMAND_ID_HANDLER(ID_EDIT_PASTE, OnEditPaste)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(ID_APP_REGISTER, OnAppRegister)
		COMMAND_ID_HANDLER(ID_APP_HELPTOPICS,OnHelpTopics)
		COMMAND_ID_HANDLER(ID_APP_DEMO,		 OnDemo)
		COMMAND_ID_HANDLER(ID_APP_CONTACT,	 OnContact)
		COMMAND_RANGE_HANDLER(ID_FILE_MRU_FIRST, ID_FILE_MRU_LAST, OnFileRecent)
		CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	END_MSG_MAP()

	BEGIN_UPDATE_UI_MAP(CMainFrame)
	END_UPDATE_UI_MAP()

	LRESULT OnCreate		(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnFileOpen		(WORD wNotifyCode, WORD wID, HWND HWndCtl, BOOL& bHandled);
	LRESULT OnFileRecent	(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnEditPaste		(WORD wNotifyCode, WORD wID, HWND HWndCtl, BOOL& bHandled);
	LRESULT OnFileExit		(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFileNew		(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFileNewWindow	(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout		(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnHelpTopics	(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnDemo			(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnAppRegister	(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnContact		(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	void StartLogging ();
	void StopLogging ();

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__4100275E_6FC1_11D5_862B_D445D2000000__INCLUDED_)
