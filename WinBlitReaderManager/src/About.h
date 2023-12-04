//***************************************************************************
//*
//*		Name		: About.h
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
//*		Interface for about dialog box
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/
#if !defined(AFX_ABOUT_H__9A5C3C13_EE74_11D5_86F5_96F47E000000__INCLUDED_)
#define AFX_ABOUT_H__9A5C3C13_EE74_11D5_86F5_96F47E000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "resource.h"       // main symbols
#include <atlhost.h>
class CAbout :	public CAxDialogImpl<CAbout>
{
public:
	enum { IDD = IDD_ABOUT_DIALOG};

	CAbout ()			{};
	virtual ~CAbout() {};
	
	BEGIN_MSG_MAP(CAbout )
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_HANDLER(IDOK, BN_CLICKED, OnOK)
		COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnCancel)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCancel (WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};

#endif // !defined(AFX_ABOUT_H__9A5C3C13_EE74_11D5_86F5_96F47E000000__INCLUDED_)
