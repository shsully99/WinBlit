//***************************************************************************
//*
//*		Name		: WarningDialog.h
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
//*		Interface for CWarningDialog
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

#include "stdafx.h"
#include "resource.h"
#include <atlctrls.h>
#include <atldlgs.h>

class CWarningDialog :	public CDialogImpl<CWarningDialog>
{
public:

	int m_iType; 
	enum { IDD = IDD_WARNINGDIALOG };
	CContainedWindowT<CButton>	m_WarningCheck;

	CWarningDialog (int iType) : m_iType(iType) 	{};
	virtual ~CWarningDialog()	{};
	
	BEGIN_MSG_MAP(CWarningDialog )
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_HANDLER(IDOK, BN_CLICKED, OnOK)
		COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnCancel)
		COMMAND_RANGE_HANDLER(IDC_WARNING_YES, IDC_WARNING_NO, OnSelChange)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnCancel (WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnSelChange(WORD wNotifyCode, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

protected:

};
