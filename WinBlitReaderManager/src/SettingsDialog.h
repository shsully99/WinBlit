//***************************************************************************
//*
//*		Name		: SettingsDialog.h
//*							
//*		$Revision:$
//*
//*		Date        : 20-Jul-2001
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
//*
//* 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

#if !defined(_SETTINGS)
#define _SETTINGS

#include "resource.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include <atlctrls.h>
class CSettingsDialog : public CDialogImpl<CSettingsDialog>, public CMessageFilter
{
public:
	enum { IDD = IDD_CONFIGDIALOG };

	CContainedWindowT<CComboBox, CWinTraitsOR<CBS_DROPDOWNLIST> > m_Combobox;

//	CComboBox m_Combo;

	CSettingsDialog();


	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return ::IsDialogMessage(m_hWnd, pMsg);
	}

	void UpdateData()
	{

	}

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CenterWindow(); 
		ATL_TRACE ("\n CSettingsDialog::OnInitDialog ");
		m_Combobox.m_hWnd = GetDlgItem(IDC_COMBO); 
		m_Combobox.AddString ("Nuts1");
		m_Combobox.AddString ("Nuts2");
		m_Combobox.AddString ("Nuts3");
		m_Combobox.AddString ("Nuts4");
		m_Combobox.AddString ("Nuts5");
		m_Combobox.SetCurSel(1);
		m_Combobox.EnableWindow(FALSE);
		return TRUE;
	}


	LRESULT OnOK(WORD NotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		EndDialog(wID);
		return 0;
	}
	void CloseDialog(int nVal)
	{

	}

	LRESULT OnSysCommand(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
	{
		UINT uCmdType = (UINT)wParam;

			bHandled = FALSE;

		return 0;
	}
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__6920296A_4C3F_11D1_AA9A_000000000000__INCLUDED_)
