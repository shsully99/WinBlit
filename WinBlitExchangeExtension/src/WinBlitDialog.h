//***************************************************************************
//*
//*		Name		: WinBlitDialog.h
//*							
//*		$Revision:$
//*
//*		Date        : 21-Feb-2002
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
//*		 Interface for WinBlit container dialog
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/#ifndef __WINBLITDIALOG_H_
#define __WINBLITDIALOG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>
#include "WinBlitReaderManager_i.c"
#include "WinBlitReaderManager.h"

/////////////////////////////////////////////////////////////////////////////
// CWinBlitDialog
class CWinBlitDialog : 
	public CAxDialogImpl<CWinBlitDialog>,  public CMessageFilter
{
public:
	enum { IDD = IDD_WINBLITDIALOG };
	friend static LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam);
	int LoadData (BSTR bstrData, RECT rc);
	CWinBlitDialog()
	{ 
	}
	~CWinBlitDialog()
	{
	}

	BEGIN_MSG_MAP(CWinBlitDialog)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
		MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	virtual BOOL PreTranslateMessage(MSG* pMsg);

	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


protected: 
	CComQIPtr<IWinBlitReader> m_WinBlitReader;
	RECT m_Rect; 
	CAxWindow m_wndView;
	BSTR m_bstrData; 
	void CloseDialog (); 
};


#endif //__WINBLITDIALOG_H_
