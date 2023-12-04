//***************************************************************************
//*
//*		Name		: WinBlitDialog.cpp
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
//*		 implementation of WinBlit container dialog
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/
// WinBlitDialog.cpp : Implementation of CWinBlitDialog
#include "stdafx.h"
#include "WinBlitDialog.h"

#include <atlframe.h>
#include <atlgdi.h>
#include <atlctrls.h>
#include <atldlgs.h>

#include "PAKVal.h"

static const CComBSTR bstrWinBlit ("WinBlitReaderManager.WinBlitReader.1");

static HHOOK hHook (NULL);
static HWND hWinBlitWnd; 

//===========================================================================
//
//	Method :		LoadData
//
//	Description :	Called by client to set up data source and display
//					rectangle of the dialog box
//.
//	Returns :		0
//
//===========================================================================

int CWinBlitDialog::LoadData(BSTR bstrData, RECT rc)
{
	ATL_TRACE0 (e_LOGFLOW, "\n CWinBlitDialog::LoadData");
	int iRet = 0; 
	m_bstrData = ::SysAllocString(bstrData);
	m_Rect = rc; 
	
	hHook = ::SetWindowsHookEx(WH_MSGFILTER,				// hook type
								HookProc,				// hook procedure
								NULL,					// handle to application instance
								::GetCurrentThreadId());	// thread identifier
	
	ATL_TRACE1 (e_LOGDETAIL, "\n Hooked %d", hHook);

	::SysFreeString(bstrData); 
	
	return iRet;
}

//===========================================================================
//
//	Method :		OnInitDialog
//
//	Description :	Initalise control 
//
//	Returns :		0
//
//===========================================================================

LRESULT CWinBlitDialog::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATL_TRACE0 (e_LOGFLOW, " CWinBlitDialog::OnInitDialog"); 
	// Initialise control 
	AtlAxWinInit(); 
	m_wndView.m_hWnd = m_hWnd;
	m_wndView.CreateControl(bstrWinBlit,NULL, NULL);
	m_wndView.QueryControl(IID_IWinBlitReader, (void**) &m_WinBlitReader);
	CComVariant varData(m_bstrData); 

	ATL_TRACE0 (e_LOGFLOW, " 111"); 

	// Stuff license status into m_view
	CPAKVal* pPAKVal = new CPAKVal;		 
	int iLic = pPAKVal->Val(eWinBlitExchange, ciLatestVersion) * ciLicMultiplier;
	delete pPAKVal; 
	ATL_TRACE0 (e_LOGFLOW, " 222"); 


	// Set dialog box name
	USES_CONVERSION; 
	CComBSTR bstrTemp("WinBlit Outlook"); 
	bstrTemp.Append(cbstrLicStat[1+(iLic/ciLicMultiplier)]);
	SendMessage (WM_SETTEXT, NULL, (LPARAM) OLE2T(bstrTemp));

	ATL_TRACE0 (e_LOGFLOW, " 333"); 

	// Load data and display control 
	m_WinBlitReader->LoadData(eCalledfromExchange + iLic, varData); 
	m_WinBlitReader->Display(); 

	// Position control 
	m_wndView.MoveWindow(&m_Rect);
	ATL_TRACE0 (e_LOGFLOW, " 444"); 

	// Store window as static control 
	hWinBlitWnd = m_wndView.m_hWnd;


	
	return 1;  // Let the system set the focus
}

//===========================================================================
//
//	Method :		OnCancel
//
//	Description :	Always called to close down the dialog box 
//
//	Returns :		0
//
//===========================================================================

LRESULT  CWinBlitDialog::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CloseDialog(); 
	return 0;
}
//===========================================================================
//
//	Method :		PreTranslateMessage
//
//	Description :	Process accelerator keys 
//
//	Returns :		0
//
//===========================================================================

BOOL  CWinBlitDialog::PreTranslateMessage(MSG* pMsg)
{
	ATL_TRACE0 (e_LOGDETAIL, "\n CWinBlitDialog::PreTranslateMessage"); 
	if (pMsg->message == 256 && m_wndView) 
	{
		HWND hWnd = m_wndView.m_hWnd;
		return (::SendMessage (hWnd, WM_FORWARDMSG, 0, (LPARAM)pMsg ));
	}
	pMsg;
	return FALSE;
}

//===========================================================================
//
//	Method :		OnKillFocus
//
//	Description :	Called to see if control has focus. 
//					If not then dialog box is closed down,
//
//	Returns :		0
//
//===========================================================================

LRESULT  CWinBlitDialog::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	/*ATL_TRACE1 (e_LOGDETAIL, "\n CWinBlitDialog::OnKillFocus %d", (HWND) wParam);

	HWND hwnd = GetFocus(); 
	HWND hwndTmp = m_wndView;

	bool bFocusFoundonControl = false; 

	// See whether the focus has been set to any of the children.
	while (hwnd && hwndTmp)
	{
		if (hwnd == hwndTmp)
		{
			bFocusFoundonControl = true;
			break; 
		}
		hwndTmp = ::GetWindow(hwndTmp, GW_CHILD);
	}

	if (!bFocusFoundonControl)
	{
		// Focus is not with the control or any of its child windows 
		// Release control and close down dialog box 
		CloseDialog ();
	}
*/
	return 0;
}
	
LRESULT CWinBlitDialog::OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATL_TRACE1 (e_LOGDETAIL,"\n CWinBlitDialog::OnSetFocus %d", (HWND) wParam);
	bHandled  = TRUE; 
	ShowWindow(TRUE); 
	return 0;
}

LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	MSG* pMsg = (MSG*) lParam;
	if (pMsg->message == 256)
	{
		ATL_TRACE0 (e_LOGDETAIL,"\n ::HookProc - Forwarding message "); 
		return (::SendMessage (hWinBlitWnd, WM_FORWARDMSG, 0, (LPARAM)pMsg ));
	}
	else		
	{	
		// TODO - SHOULD FORWARD THIS MESSAGE ON USING CALLNBEXT HOOK IF 
		// THIS EVER BECOMES A NON-MODAL DIALOG BOX
	}
	return 0;
}

//===========================================================================
//
//	Method :		CloseDialog
//
//	Description :	Called to close down the dialog box 
//
//	Returns :		0
//
//===========================================================================

void CWinBlitDialog::CloseDialog ()
{
	ATL_TRACE0 (e_LOGDETAIL,  "CWinBlitDialog::CloseDialog");
	m_WinBlitReader.Release();

	if (TRUE == ::UnhookWindowsHookEx(hHook))
	{
		ATL_TRACE0 (e_LOGDETAIL,"\n Unhhooked successfully");
	}
	else
	{
		ATL_TRACE0 (e_LOGDETAIL,"\n Unhhooked unsuccessfully");
	}

	::SysFreeString(m_bstrData); 
	EndDialog (0);
}
