//***************************************************************************
//*
//*		Name		: Reg.h
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
//*		Interface for registration dialog box 
//* 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

#if !defined(AFX_REG_H__07FF6D23_B8A0_11D5_8690_EC9652000000__INCLUDED_)
#define AFX_REG_H__07FF6D23_B8A0_11D5_8690_EC9652000000__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "resource.h"
#include <atlctrls.h>
class CReg :	public CDialogImpl<CReg>
{
public:
	CContainedWindowT<CEdit> m_NameEdit;
	CContainedWindowT<CEdit> m_IDEdit;
	
	enum { IDD = IDD_REGDIALOG };

	CReg (CComBSTR bstrPath) : m_bstrHelpPath (bstrPath) {};
	virtual ~CReg() {};
	
	BEGIN_MSG_MAP(CReg )
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
 		MESSAGE_HANDLER(WM_HELP, OnHelpCalled)
		COMMAND_HANDLER(IDOK, BN_CLICKED, OnOK)
		COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnCancel)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnCancel (WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnHelpCalled(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

protected:
	CComBSTR m_bstrHelpPath;
};

#endif // !defined(AFX_REG_H__07FF6D23_B8A0_11D5_8690_EC9652000000__INCLUDED_)
