//***************************************************************************
//*
//*		Name		: Speed.cpp
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
//*		Implementation for the speed dialog box.
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
#include "Speed.h"
#include "WinBlitConstants.h"
#include "htmlhelp.h"
#include "DialogMap.h"

LRESULT CSpeed::OnHScroll (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_bInitDialog == true) return 0;
	SetDlgItemInt(IDC_SPEED_EDIT, m_SpeedSlider.GetPos());	
	m_lBaseTime = 60000 / m_SpeedSlider.GetPos(); 
	return 0; 
}

LRESULT CSpeed::OnChangeSpeedEdit (WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_bInitDialog == true) return 0;
	int iVal = GetDlgItemInt(IDC_SPEED_EDIT);
	if (iVal < ciSpeedMin) 
	{
		iVal = ciSpeedMin;
	}
	else if (iVal > ciSpeedMax)
	{
		iVal = ciSpeedMax;
	}
	m_SpeedSlider.SetPos(iVal);
	m_lBaseTime = 60000/iVal; 

	return 0; 
}

LRESULT CSpeed::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_bInitDialog = true; 
	m_SpeedSlider.m_hWnd = GetDlgItem(IDC_SPEED_SLIDER);
	SetDlgItemInt(IDC_SPEED_EDIT, 60000 / m_lBaseTime );

	m_SpeedSlider.SetRangeMin(ciSpeedMin);
	m_SpeedSlider.SetRangeMax(ciSpeedMax);
	m_SpeedSlider.SetPos (60000/m_lBaseTime); 
	m_bInitDialog = false; 
	if (m_Rect.left != 0 && m_Rect.top != 0)
	{
		MoveWindow(&m_Rect); 
	}

	return 0;
}

LRESULT CSpeed::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	::GetWindowRect(m_hWnd , &m_Rect); 
	EndDialog(wID);
	return 0;
}

LRESULT CSpeed::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	::GetWindowRect(m_hWnd , &m_Rect); 
	EndDialog(m_lBaseTime);
	return 0;
}

LRESULT CSpeed::OnHelpCalled(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATL_TRACE ("\n  CSpeed::OnHelp");
	// TODO : Add Code for message handler. Call DefWindowProc if necessary.

	ATL_TRACE ("\n %d", ((LPHELPINFO) lParam)->dwContextId);
	
	USES_CONVERSION; 
	if (m_bstrHelpPath)
	{
		CComBSTR bstrHelpPath(m_bstrHelpPath); 
	
		for (int iA = 0; iA  < ciDialogCount; iA++)
		{
			if (0 == wcscmp(L"PropPageSpeed",	cawchDialogs[iA]))
			{
				bstrHelpPath.Append(cawchHelpPaths[iA]); 
			}
		}
		::HtmlHelp(    NULL,      NULL,       HH_CLOSE_ALL,   0) ;
		::HtmlHelp(m_hWnd, OLE2T(bstrHelpPath), HH_DISPLAY_TOPIC, 0);

	}

	return 0;
}

