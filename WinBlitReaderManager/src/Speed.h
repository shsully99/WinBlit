//***************************************************************************
//*
//*		Name		: Speed.h
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
//*	
//*		Interface for speed dialog box 
//* 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

#if !defined(AFX_SPEED_H__015C9503_E3DD_11D5_86E1_98AEA9000000__INCLUDED_)
#define AFX_SPEED_H__015C9503_E3DD_11D5_86E1_98AEA9000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "resource.h"
#include <atlctrls.h>
class CSpeed : public CDialogImpl<CSpeed>
{
public:
	enum { IDD = IDD_SPEED_DIALOG };

	CContainedWindowT<CTrackBarCtrl> m_SpeedSlider;
	CContainedWindowT<CEdit> m_SpeedEdit;
	CComBSTR m_bstrHelpPath; 
	RECT m_Rect; 

	
	BEGIN_MSG_MAP(CSpeed)
		MESSAGE_HANDLER(WM_INITDIALOG,	OnInitDialog)
 		MESSAGE_HANDLER(WM_HELP,		OnHelpCalled)
		COMMAND_HANDLER(IDOK,			BN_CLICKED, OnOK)
		COMMAND_HANDLER(IDCANCEL,		BN_CLICKED, OnCancel)
		MESSAGE_HANDLER(WM_HSCROLL,		OnHScroll)
		COMMAND_HANDLER(IDC_SPEED_EDIT,	EN_CHANGE,	OnChangeSpeedEdit)
		MESSAGE_HANDLER(WM_KEYUP, OnKeyUp)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
	END_MSG_MAP()

	void GetRect(LPRECT lpRect)
	{
		*lpRect = m_Rect; 
	}

	LRESULT OnInitDialog	(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	LRESULT OnOK			(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnCancel		(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnHelpCalled	(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnHScroll		(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);	

	LRESULT OnChangeSpeedEdit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	CSpeed(long lBaseTime, BSTR bstrHelpPath,RECT SpeedRect) 
		:	m_lBaseTime(lBaseTime),
			m_bstrHelpPath(bstrHelpPath),
			m_Rect(SpeedRect), 
			m_bInitDialog(false){};
	virtual ~CSpeed() {};
protected:
	long m_lBaseTime; 
	bool m_bInitDialog; 
	LRESULT OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		return 0;
	}
	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		ATL_TRACE0 (e_LOGDETAIL, "CSpeed::OnKillFocus"); 
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		return 0;
	}

};

#endif // !defined(AFX_SPEED_H__015C9503_E3DD_11D5_86E1_98AEA9000000__INCLUDED_)
