//***************************************************************************
//*
//*		Name		: Reg.cpp
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
//*		Implementation for registration dialog box 
//* 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/
#include "stdafx.h"
#include "Reg.h"
#include "PAKVal.h"
#include "htmlhelp.h"
#include "DialogMap.h"


//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

LRESULT CReg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_NameEdit.m_hWnd = GetDlgItem(IDC_EDIT_REGNAME);
	m_IDEdit.m_hWnd = GetDlgItem(IDC_EDIT_REGID);
	return 0;
}

LRESULT CReg::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}

LRESULT CReg::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	TCHAR tchName [255]; 
	m_NameEdit.GetLine	(0,	tchName,	255);
	int iLength = m_NameEdit.LineLength();
	tchName[iLength] = '\0';

	TCHAR tchID [255]; 
	m_IDEdit.GetLine	(0,	tchID,	255); 
	iLength = m_IDEdit.LineLength();
	tchID[iLength] = '\0'; 

	CPAKVal PAKVal;
	int iA = PAKVal.Lic	(tchName, tchID);
	if (0 == iA)
	{
		MessageBox ("Registration succeeded - Close down WinBlitPad, Internet Explorer and all Office applications.\n When WinBlit is restarted within one of these applications it will be fully licensed", "Registration Succeeded"); 		
		EndDialog(wID);
	}
	else if (-1 == iA)
	{
		MessageBox ("Invalid registration key entered" , "Registration Failed"); 
	}
	else if (-2 == iA)
	{
		MessageBox ("Registration Failed due to a system error - Please contact Product Support", "Registration Failed"); 
	}
	return 0;
}

LRESULT CReg::OnHelpCalled(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATL_TRACE ("\n  CReg::OnHelp");
	
	USES_CONVERSION; 
	CComBSTR bstrHelpPath(m_bstrHelpPath); 
	
	for (int iA = 0; iA  < ciDialogCount; iA++)
	{
		if (0 == wcscmp(L"Reg",	cawchDialogs[iA]))
		{
			bstrHelpPath.Append(cawchHelpPaths[iA]); 
		}
	}
	::HtmlHelp(    NULL,      NULL,       HH_CLOSE_ALL,   0) ;

	::HtmlHelp(m_hWnd, OLE2T(bstrHelpPath), HH_DISPLAY_TOPIC, 0);

	bHandled = TRUE; 
	return 0;
}

