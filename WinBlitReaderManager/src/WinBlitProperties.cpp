//***************************************************************************
//*
//*		Name		: WinBlitProperties.cpp
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
//*		Contains WinBlits Properties - Implements all WinBlit's get/put methods 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

#include "stdafx.h"
#include "WinBlitProperties.h"
#include "Settings.h"
#include "WinBlitReaderManager.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWinBlitProperties::CWinBlitProperties()
{
	m_pSettings = NULL;

	// Todo constant 
	FONTDESC lf = 
	{sizeof(FONTDESC), OLESTR("times new roman                "), FONTSIZE( 10 ),
	FW_BOLD, ANSI_CHARSET, TRUE, FALSE, FALSE };

	OleCreateFontIndirect(&lf, IID_IFontDisp, (void**)&m_pTextFont);

	m_clrScreenBackColor = RGB (0,  0,  0);
	m_clrScreenFillColor = RGB (0,  0,  0);
	m_clrScreenTextColor = RGB (0,  255,0);
	m_clrCursorFillColor = RGB (0,  0,  0);
	m_clrCursorTextColor = RGB (255,0,  0);
	m_lDisplayPeriod = 1000; 
	m_lBlackoutPeriod = 0;
	m_lHighlightPeriod = 1000;
	m_lCursor = cDisplayScreenText & 
				cDisplayCursorText & 
				cTachistoscopicCursor  &
				cWordDivisions;

	m_lCursorHeight = 1;
	m_lCursorWidth = 2;
	m_lBaseTime = 1000;
	m_lTop = 0;
	m_lBottom = 0;
    m_lRight = 0;
	m_lLeft = 0;
	m_lLogLevel = 0;
	m_bstrHTMLTagsAllowed = "<*>";
	m_bstrHTMLTagsBarred = ""; 
	m_bHTMLDuplicateTags = false;
	m_bShowControls = true;
	m_bShowTrackBar = true;
	m_bShowMetafile = false;
	m_bShowStatusBar = false; 
	m_bSDKMode = false; 
	m_bstrTemplateID          = "";
	m_bstrDescription        = "";
	m_bstrName = "";
	m_lHelpType = 1; 
	m_bstrDemoPath = ""; 
	m_bstrHelpPath = ""; 
	m_bstrHelpStartPage = ""; 
	m_sFillType = e_FILL_BETWEEN_WORDS; 
	m_sFillPercent = 85;
}

CWinBlitProperties::~CWinBlitProperties()
{
	m_pSettings.Release();
}

HRESULT CWinBlitProperties::get_SDKMode (/*[out, retval]*/ BOOL *bVal)
{
	*bVal = m_bSDKMode;
	return S_OK;
}

HRESULT CWinBlitProperties::put_SDKMode (/*[in]*/ BOOL newVal)
{
	(newVal == FALSE) ? m_bSDKMode = false : m_bSDKMode = true;

	if (m_bSDKMode) 
	{
		m_bShowControls = false; 
		m_bShowStatusBar = false;
		m_bShowTrackBar = false;
	}

	return S_OK;
}


HRESULT CWinBlitProperties::get_ShowMetafile(/*[out, retval]*/ BOOL *bVal)
{
	*bVal = m_bShowMetafile;
	return S_OK;
}

HRESULT CWinBlitProperties::put_ShowMetafile(/*[in]*/ BOOL newVal)
{
	(newVal == FALSE) ? m_bShowMetafile = false: m_bShowMetafile = true;
	return S_OK;
}

HRESULT CWinBlitProperties::get_ShowControls (/*[out, retval]*/ BOOL *bVal)
{
	*bVal = m_bShowControls;
	return S_OK;
}

HRESULT CWinBlitProperties::put_ShowControls(/*[in]*/ BOOL newVal)
{
	(newVal == FALSE) ? m_bShowControls = false: m_bShowControls = true;
	return S_OK;
}

HRESULT CWinBlitProperties::get_ShowStatusBar (/*[out, retval]*/ BOOL *bVal)
{
	*bVal = m_bShowStatusBar;
	return S_OK;
}

HRESULT CWinBlitProperties::put_ShowStatusBar(/*[in]*/ BOOL newVal)
{
	(newVal == FALSE) ? m_bShowStatusBar = false: m_bShowStatusBar = true;
	return S_OK;
}

HRESULT CWinBlitProperties::get_ShowTrackBar(/*[out, retval]*/ BOOL *bVal)
{
	*bVal = m_bShowTrackBar;
	return S_OK;
}

HRESULT CWinBlitProperties::put_ShowTrackBar(/*[in]*/ BOOL newVal)
{
	(newVal == FALSE) ? m_bShowTrackBar = false: m_bShowTrackBar = true;
	return S_OK;
}

HRESULT CWinBlitProperties::get_Cursor(long *pVal)
{
	*pVal = m_lCursor;
	return S_OK;
}

HRESULT CWinBlitProperties::put_Cursor(long newVal)
{
	if (m_lCursor != newVal) m_ePropUpdate = e_PAINT_LEAVE_CURSOR;
	m_lCursor = newVal;
	return S_OK;
}

HRESULT CWinBlitProperties::get_CursorWidth(long *pVal)
{
	*pVal = m_lCursorWidth;
	return S_OK;
}

HRESULT CWinBlitProperties::put_CursorWidth(long newVal)
{
	if (m_lCursorWidth != newVal) m_ePropUpdate = e_PAINT_RESET_CURSOR;
	m_lCursorWidth = newVal;
	return S_OK;
}

HRESULT CWinBlitProperties::get_CursorHeight(long *pVal)
{
	*pVal = m_lCursorHeight;
	return S_OK;
}

HRESULT CWinBlitProperties::put_CursorHeight(long newVal)
{
	if (m_lCursorHeight != newVal) m_ePropUpdate = e_PAINT_RESET_CURSOR;
	m_lCursorHeight = newVal;
	return S_OK;
}

HRESULT CWinBlitProperties::get_BaseTime(long *pVal)
{
	if (*pVal < 0) return E_INVALIDARG;
	*pVal = m_lBaseTime;
	return S_OK;
}

HRESULT CWinBlitProperties::put_BaseTime(long newVal)
{
	m_lBaseTime = newVal;
	return S_OK;
}

HRESULT CWinBlitProperties::get_HighlightPeriod(long *pVal)
{
	*pVal = m_lHighlightPeriod;
	return S_OK;
}

HRESULT CWinBlitProperties::put_HighlightPeriod(long newVal)
{
	m_lHighlightPeriod = newVal;
	return S_OK;
}

HRESULT CWinBlitProperties::get_Settings(IDispatch **pVal)
{
	if (!m_pSettings.p)
	{	
		CComObject< CSettings>* pTemp = NULL;
		CComObject< CSettings>::CreateInstance(&pTemp);
		m_pSettings = pTemp;
	}

	m_pSettings->QueryInterface(IID_IDispatch, (void**) pVal); 
	return (NULL != *pVal? S_OK : E_FAIL); 
}

HRESULT CWinBlitProperties::get_Top(long *pVal)
{
	*pVal = m_lTop;		
	return S_OK; 
}

HRESULT CWinBlitProperties::put_Top(long newVal)
{
	if (m_lTop != newVal) m_ePropUpdate = e_REBUILD_PAGE;
	m_lTop = newVal;
	return S_OK;
}

HRESULT CWinBlitProperties::get_Bottom(long *pVal)
{
	*pVal = m_lBottom; 
	return S_OK;
}

HRESULT CWinBlitProperties::put_Bottom(long newVal)
{
	if (m_lBottom != newVal) m_ePropUpdate = e_REBUILD_PAGE;
	m_lBottom = newVal; 
	return S_OK;
}

HRESULT CWinBlitProperties::get_Right(long *pVal)
{
	*pVal = m_lRight;
	return S_OK;
}

HRESULT CWinBlitProperties::put_Right(long newVal)
{
	if (m_lRight != newVal) m_ePropUpdate = e_REBUILD_PAGE;
	m_lRight = newVal; 
	return S_OK;
}

HRESULT CWinBlitProperties::get_Left(long *pVal)
{
	*pVal = m_lLeft; 
	return S_OK;
}

HRESULT CWinBlitProperties::put_Left(long newVal)
{
	if (m_lLeft != newVal) m_ePropUpdate = e_REBUILD_PAGE;
	m_lLeft = newVal;
	return S_OK;
}

HRESULT CWinBlitProperties::get_ScreenTextColor(OLE_COLOR *pVal)
{
	*pVal = m_clrScreenTextColor;
	return S_OK;
}

HRESULT CWinBlitProperties::put_ScreenTextColor(OLE_COLOR newVal)
{
	if (m_clrScreenTextColor != newVal) m_ePropUpdate = e_PAINT_LEAVE_CURSOR; 
	m_clrScreenTextColor = newVal;
	return S_OK;
}

HRESULT CWinBlitProperties::get_TextFont(IFontDisp** ppFont)
{
	*ppFont = m_pTextFont;
	if (*ppFont != NULL)
			(*ppFont)->AddRef();
	return S_OK;
}

HRESULT CWinBlitProperties::put_TextFont(IFontDisp* pFont)
{
	if (pFont)
	{
		CComQIPtr<IFont, &IID_IFont> p(pFont);
		if (p)
		{
			CComPtr<IFont> pFont;
			p->Clone(&pFont);
			if (m_pTextFont) m_pTextFont.Release();
			if (pFont)
				pFont->QueryInterface(IID_IFontDisp, (void**) &m_pTextFont);
		}
	}
	m_ePropUpdate = e_REBUILD_PAGE;
	return S_OK;
}


HRESULT CWinBlitProperties::get_ScreenFillColor(OLE_COLOR *pVal)
{
	*pVal = m_clrScreenFillColor;
	return S_OK;
}

HRESULT CWinBlitProperties::put_ScreenFillColor(OLE_COLOR newVal)
{
	if (m_clrScreenFillColor != newVal) m_ePropUpdate = e_PAINT_LEAVE_CURSOR; 
	m_clrScreenFillColor = newVal;
	return S_OK;
}

HRESULT CWinBlitProperties::get_ScreenBackColor(OLE_COLOR *pVal)
{
	*pVal = m_clrScreenBackColor;
	return S_OK;
}

HRESULT CWinBlitProperties::put_ScreenBackColor(OLE_COLOR newVal)
{
	if (m_clrScreenBackColor != newVal) m_ePropUpdate = e_PAINT_LEAVE_CURSOR; 
	m_clrScreenBackColor = newVal;
	return S_OK;
}

HRESULT CWinBlitProperties::get_CursorTextColor(OLE_COLOR *pVal)
{
	*pVal = m_clrCursorTextColor;
	return S_OK;
}

HRESULT CWinBlitProperties::put_CursorTextColor(OLE_COLOR newVal)
{
	if (m_clrCursorTextColor != newVal) m_ePropUpdate = e_PAINT_LEAVE_CURSOR; 
	m_clrCursorTextColor = newVal;
	return S_OK;
}

HRESULT CWinBlitProperties::get_CursorFillColor(OLE_COLOR *pVal)
{
	*pVal = m_clrCursorFillColor;
	return S_OK;
}

HRESULT CWinBlitProperties::put_CursorFillColor(OLE_COLOR newVal)
{
	if (m_clrCursorFillColor != newVal) m_ePropUpdate = e_PAINT_LEAVE_CURSOR; 
	m_clrCursorFillColor = newVal;
	return S_OK;
}

HRESULT CWinBlitProperties::get_DisplayPeriod(long *pVal)
{
	*pVal = m_lDisplayPeriod; 
	return S_OK;
}

HRESULT CWinBlitProperties::put_DisplayPeriod(long newVal)
{
	m_lDisplayPeriod = newVal; 
	return S_OK;
}

HRESULT CWinBlitProperties::get_BlackoutPeriod(long *pVal)
{
	*pVal = m_lBlackoutPeriod;
	return S_OK;
}

HRESULT CWinBlitProperties::put_BlackoutPeriod(long newVal)
{
	m_lBlackoutPeriod = newVal; 
	return S_OK;
}

HRESULT  CWinBlitProperties::get_Description      	(/*[out, retval]*/ BSTR *pVal)
{
	if (pVal) ::SysFreeString(*pVal);
	*pVal = ::SysAllocString(m_bstrDescription.m_str);
	return (NULL != *pVal? S_OK : E_OUTOFMEMORY); 
}

HRESULT  CWinBlitProperties::put_Description	(/*[in]*/ BSTR newVal)
{
	m_bstrDescription = newVal; 
	return S_OK;
}

HRESULT  CWinBlitProperties::get_TemplateID	(/*[out, retval]*/ BSTR *pVal)
{
	if (pVal) ::SysFreeString(*pVal);
	*pVal = ::SysAllocString(m_bstrTemplateID.m_str);
	return (NULL != *pVal? S_OK : E_OUTOFMEMORY); 
}

HRESULT  CWinBlitProperties::put_TemplateID (/*[in]*/ BSTR newVal)
{
	m_bstrTemplateID = newVal; 
	return S_OK;
}

HRESULT  CWinBlitProperties::get_HTMLTagsAllowed		(/*out, retval]*/ BSTR *pVal)
{
	if (pVal) ::SysFreeString(*pVal);
	*pVal = ::SysAllocString(m_bstrHTMLTagsAllowed);
	return (NULL != *pVal? S_OK : E_OUTOFMEMORY); 
}

HRESULT CWinBlitProperties::put_HTMLTagsAllowed		(/*[in]*/ BSTR newVal)
{
	m_bstrHTMLTagsAllowed = newVal; 
	return S_OK; 
}

HRESULT CWinBlitProperties::get_HTMLTagsBarred			(/*out, retval]*/ BSTR *pVal)
{
	if (pVal) ::SysFreeString(*pVal);
	*pVal = ::SysAllocString(m_bstrHTMLTagsBarred);
	return (NULL != *pVal? S_OK : E_OUTOFMEMORY); 
}

HRESULT CWinBlitProperties::put_HTMLTagsBarred			(/*[in]*/ BSTR newVal)
{
	m_bstrHTMLTagsBarred = newVal; 
	return S_OK;
}

HRESULT CWinBlitProperties::get_HTMLDuplicateTags		(/*[out, retval]*/ BOOL *bVal)
{
	*bVal = m_bHTMLDuplicateTags;
	return S_OK;
}

HRESULT CWinBlitProperties::put_HTMLDuplicateTags		(/*[in]*/ BOOL newVal)
{
	(newVal == FALSE) ? m_bHTMLDuplicateTags = false: m_bHTMLDuplicateTags = true;
	return S_OK;
}

HRESULT CWinBlitProperties::get_HelpPath			(/*[out, retval]*/ BSTR *pVal)
{
	if (pVal) ::SysFreeString(*pVal);
	*pVal = ::SysAllocString(m_bstrHelpPath);	
	return (NULL != *pVal? S_OK : E_OUTOFMEMORY); 
}

HRESULT CWinBlitProperties::put_HelpPath			(/*[in]*/ BSTR newVal)
{
	m_bstrHelpPath = newVal; 
	return S_OK;
}

HRESULT CWinBlitProperties::get_HelpStartPage		(/*[out, retval]*/ BSTR *pVal)
{
	if (pVal) ::SysFreeString(*pVal);
	*pVal = ::SysAllocString(m_bstrHelpStartPage);	
	return (NULL != *pVal? S_OK : E_OUTOFMEMORY); 
}

HRESULT CWinBlitProperties::put_HelpStartPage		(/*[in]*/ BSTR newVal)
{
	m_bstrHelpStartPage = newVal; 
	return S_OK;
}

HRESULT CWinBlitProperties::get_HelpContextPage		(/*[out, retval]*/ BSTR *pVal)
{
	if (pVal) ::SysFreeString(*pVal);
	*pVal = ::SysAllocString(m_bstrHelpContextPage);	
	return S_OK;
}

HRESULT CWinBlitProperties::put_HelpContextPage		(/*[in]*/ BSTR newVal)
{
	m_bstrHelpContextPage = newVal; 
	return S_OK;
}

HRESULT CWinBlitProperties::get_HelpType			(/*[out, retval]*/ long *pVal)
{
	*pVal = m_lHelpType; 
	return S_OK;
}

HRESULT CWinBlitProperties::put_HelpType			(/*[in]*/ long newVal)
{
	m_lHelpType = newVal; 
	return S_OK;
}
