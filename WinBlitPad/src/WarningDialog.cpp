//***************************************************************************
//*
//*		Name		: WarningDialog.cpp
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
//*		Implementation for CWarningDialog
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

#include "stdafx.h"
#include "WarningDialog.h"

LRESULT CWarningDialog::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_WarningCheck.m_hWnd = GetDlgItem(IDC_WARNING_CHECK); 
	CheckRadioButton(IDC_WARNING_YES, IDC_WARNING_NO, IDC_WARNING_NO);
	m_WarningCheck.SetCheck(FALSE); 
	if (1 == m_iType)
	{
		SetDlgItemText(IDC_WARNING_STATIC1, "To read Word documents using WinBlit it is recommended that you open the document in Word and click the WinBlit icon which you will see on the Toolbar."); 
		SetDlgItemText(IDC_WARNING_STATIC2, "Opening a Microsoft Word document in BlitPad will show all of the document formatting info - not just the text portion."); 
	}
	else
	{
		SetDlgItemText(IDC_WARNING_STATIC1, "To read HTML documents using WinBlit it is recommended that you open the document in HTML and click the WinBlit icon which you will see on the Toolbar."); 
		SetDlgItemText(IDC_WARNING_STATIC2, "Opening an HTML document in BlitPad will show all of the document formatting info - not just the text portion."); 
	}


	return 0;
}

LRESULT CWarningDialog::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}

LRESULT CWarningDialog::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int iWarning = 0;
	if (IsDlgButtonChecked(IDC_WARNING_YES))
	{
		iWarning = IDC_WARNING_YES;
	}
	else
	{
		iWarning = IDC_WARNING_NO;
	}

	if (TRUE == m_WarningCheck.GetCheck())
	{
		iWarning = 0 - iWarning; 				
	}

	EndDialog(iWarning);

	return 0;
}
LRESULT CWarningDialog::OnSelChange(WORD wNotifyCode, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	return 0;
}

