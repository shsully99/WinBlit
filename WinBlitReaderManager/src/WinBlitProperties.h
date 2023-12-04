//***************************************************************************
//*
//*		Name		: WinBlitProperties.h
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
//*		Contains WinBlits Properties - Implements all WinBlits property 
//*		get/put methods
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

// WinBlitProperties.h: interface for the CWinBlitProperties class.
//
//////////////////////////////////////////////////////////////////////

interface ISettings;
interface IStatistics; 

#if !defined(AFX_WINBLITPROPERTIES_H__54E134D4_6163_11D5_8611_82E94F000000__INCLUDED_)
#define AFX_WINBLITPROPERTIES_H__54E134D4_6163_11D5_8611_82E94F000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WinBlitReaderManager.h"

interface ISettings;
interface IStatistics; 


// Enumerator to tell blt creator how to fill text in lines
enum eFillType
{
	e_FILL_NONE = 0,						// Do not fill line 
	e_FILL_BETWEEN_WORDS = 1,				// Fill between words 
	e_FILL_BETWEEN_BLITS = 2,			// Fill between fixations
	e_FILL_BETWEEN_BOTH = 3					// Fill equally between words and fixations 
};

// Enumerator to tell text window that it needs to update itself
enum ePROPUPDATE {
	e_NOREPAINT,
	e_REBUILD_PAGE,							// Reconstruct page
	e_PAINT_LEAVE_CURSOR,					// Repaint but leave cursor 
	e_PAINT_RESET_CURSOR					// Repaint but reset  cursor 
};

class CWinBlitRegistry; 

class CWinBlitProperties  
{
public:

	friend class CWinBlitRegistry;		// Has durect access toi protected members of this class.

	CWinBlitProperties();
	virtual ~CWinBlitProperties();
	ePROPUPDATE m_ePropUpdate;			// Flag for update properties 

	bool	    SDKMode			() { return m_bSDKMode;};
	bool        ShowMetafile	() { return m_bShowMetafile;};
	bool        ShowControls	() { return m_bShowControls;};
	bool        ShowStatusBar	() { return m_bShowStatusBar;};
	bool        ShowTrackBar	() { return m_bShowTrackBar;};

	long		Left			() { return m_lLeft;};
	long		Right			() { return m_lRight;};
	long		Bottom			() { return m_lBottom;};
	long		Top				() { return m_lTop;};
	long		HighlightPeriod	() { return m_lHighlightPeriod;};
	long		BaseTime		() { return m_lBaseTime;};
	long		CursorHeight	() { return m_lCursorHeight;};
	long		CursorWidth		() { return m_lCursorWidth;};
	long		Cursor			() { return m_lCursor;};

	OLE_COLOR	ScreenBackColor	() { return m_clrScreenBackColor; }; 
	OLE_COLOR   ScreenFillColor	() { return m_clrScreenFillColor; }; 
	OLE_COLOR   ScreenTextColor	() { return m_clrScreenTextColor; }; 
	//			TextFont		(/*[out, retval]*/ IFontDisp** pVal);
	long        BlackoutPeriod	() { return m_lBlackoutPeriod;};
	long        DisplayPeriod	() { return m_lDisplayPeriod;};
	OLE_COLOR   CursorFillColor	() { return m_clrCursorFillColor; }; 
	OLE_COLOR   CursorTextColor	() { return m_clrCursorTextColor; }; 
	const BSTR*	Description		() { return &m_bstrDescription.m_str; };
	const BSTR*	TemplateID		() { return &m_bstrTemplateID.m_str; };
	const BSTR*	HelpPath		() { return &m_bstrHelpPath.m_str; };
	const BSTR*	DemoPath		() { return &m_bstrDemoPath.m_str; };
	const BSTR*	Name			() { return &m_bstrName.m_str; };
	const BSTR*	HelpStartPage	() { return &m_bstrHelpStartPage.m_str; };
	const BSTR*	HelpContextPage	() { return &m_bstrHelpContextPage.m_str; };
	long		HelpType		() { return m_lHelpType; };

	// These methods are not in the type libraray
	const BSTR*	HTMLTagsAllowed	() { return &m_bstrHTMLTagsAllowed.m_str; };
	const BSTR*	HTMLTagsBarred	() { return &m_bstrHTMLTagsBarred.m_str; };
	bool     	HTMLDuplicateTags() { return m_bHTMLDuplicateTags; };
	short		FillType		()  { return m_sFillType; };
	short		FillPercent  ()		{ return m_sFillPercent; };

	HRESULT get_DemoMode		(/*[out, retval]*/ long *lVal);
	HRESULT put_DemoMode		(/*[in]*/ long lVal);	
	HRESULT get_SDKMode			(/*[out, retval]*/ BOOL *bVal);
	HRESULT put_SDKMode			(/*[in]*/ BOOL newVal);	
	HRESULT get_ShowMetafile	(/*[out, retval]*/ BOOL *bVal);
	HRESULT put_ShowMetafile	(/*[in]*/ BOOL newVal);
	HRESULT get_ShowControls	(/*[out, retval]*/ BOOL *bVal);
	HRESULT put_ShowStatusBar	(/*[in]*/ BOOL newVal);
	HRESULT get_ShowStatusBar	(/*[out, retval]*/ BOOL *bVal);
	HRESULT put_ShowControls	(/*[in]*/ BOOL newVal);
	HRESULT get_ShowTrackBar	(/*[out, retval]*/ BOOL *bVal);
	HRESULT put_ShowTrackBar	(/*[in]*/ BOOL newVal);
	HRESULT get_Left			(/*[out, retval]*/ long *pVal);
	HRESULT put_Left			(/*[in]*/ long newVal);
	HRESULT get_Right			(/*[out, retval]*/ long *pVal);
	HRESULT put_Right			(/*[in]*/ long newVal);
	HRESULT get_Bottom			(/*[out, retval]*/ long *pVal);
	HRESULT put_Bottom			(/*[in]*/ long newVal);
	HRESULT get_Top				(/*[out, retval]*/ long *pVal);
	HRESULT put_Top				(/*[in]*/ long newVal);
	HRESULT get_Settings		(/*[out, retval]*/ IDispatch* *pVal);
	HRESULT get_HighlightPeriod	(/*[out, retval]*/ long *pVal);
	HRESULT put_HighlightPeriod	(/*[in]*/ long newVal);
	HRESULT get_BaseTime		(/*[out, retval]*/ long *pVal);
	HRESULT put_BaseTime		(/*[in]*/ long newVal);
	HRESULT get_CursorHeight	(/*[out, retval]*/ long *pVal);
	HRESULT put_CursorHeight	(/*[in]*/ long newVal);
	HRESULT get_CursorWidth		(/*[out, retval]*/ long *pVal);
	HRESULT put_CursorWidth		(/*[in]*/ long newVal);
	HRESULT get_Cursor			(/*[out, retval]*/ long *pVal);
	HRESULT put_Cursor			(/*[in]*/ long newVal);
	HRESULT get_ScreenBackColor	(/*[out, retval]*/ OLE_COLOR *pVal);
	HRESULT put_ScreenBackColor	(/*[in]*/ OLE_COLOR newVal);
	HRESULT get_ScreenFillColor	(/*[out, retval]*/ OLE_COLOR *pVal);
	HRESULT put_ScreenFillColor	(/*[in]*/ OLE_COLOR newVal);
	HRESULT get_ScreenTextColor	(/*[out, retval]*/ OLE_COLOR *pVal);
	HRESULT put_ScreenTextColor	(/*[in]*/ OLE_COLOR newVal);
	HRESULT get_TextFont		(/*[out, retval]*/ IFontDisp** pVal);
	HRESULT put_TextFont		(/*[in]*/ IFontDisp *pVal);
	HRESULT get_BlackoutPeriod	(/*[out, retval]*/ long *pVal);
	HRESULT put_BlackoutPeriod	(/*[in]*/ long newVal);
	HRESULT get_DisplayPeriod	(/*[out, retval]*/ long *pVal);
	HRESULT put_DisplayPeriod	(/*[in]*/ long newVal);
	HRESULT get_CursorFillColor	(/*[out, retval]*/ OLE_COLOR *pVal);
	HRESULT put_CursorFillColor	(/*[in]*/ OLE_COLOR newVal);
	HRESULT get_CursorTextColor	(/*[out, retval]*/ OLE_COLOR *pVal);
	HRESULT put_CursorTextColor	(/*[in]*/ OLE_COLOR newVal);
	HRESULT get_Description		(/*out, retval]*/ BSTR *pVal);
	HRESULT put_Description		(/*[in]*/ BSTR newVal);
	HRESULT get_TemplateID		(/*[out, retval]*/ BSTR *pVal);
	HRESULT put_TemplateID		(/*[in]*/ BSTR newVal);
	HRESULT get_HelpPath		(/*[out, retval]*/ BSTR *pVal);
	HRESULT put_HelpPath		(/*[in]*/ BSTR newVal);
	HRESULT get_HelpStartPage	(/*[out, retval]*/ BSTR *pVal);
	HRESULT put_HelpContextPage	(/*[in]*/ BSTR newVal);
	HRESULT get_HelpContextPage	(/*[out, retval]*/ BSTR *pVal);
	HRESULT put_HelpStartPage	(/*[in]*/ BSTR newVal);
	HRESULT get_HelpType		(/*[out, retval]*/ long *pVal);
	HRESULT put_HelpType		(/*[in]*/ long newVal);

	// These methods are not in the type libraray
	HRESULT get_HTMLTagsAllowed		(/*out, retval]*/ BSTR *pVal);
	HRESULT put_HTMLTagsAllowed		(/*[in]*/ BSTR newVal);
	HRESULT get_HTMLTagsBarred		(/*out, retval]*/ BSTR *pVal);
	HRESULT put_HTMLTagsBarred		(/*[in]*/ BSTR newVal);
	HRESULT get_HTMLDuplicateTags	(/*[out, retval]*/ BOOL *bVal);
	HRESULT put_HTMLDuplicateTags	(/*[in]*/ BOOL newVal);

protected: 

	OLE_COLOR m_clrScreenBackColor;
	OLE_COLOR m_clrScreenFillColor;
	CComPtr<IFontDisp> m_pTextFont;
	OLE_COLOR m_clrScreenTextColor;
	OLE_COLOR m_clrCursorFillColor;
	OLE_COLOR m_clrCursorTextColor;
	CComBSTR m_bstrHTMLTagsAllowed;
	CComBSTR m_bstrHTMLTagsBarred; 
	bool m_bHTMLDuplicateTags;
	CComBSTR m_bstrTemplateID;
	CComBSTR m_bstrDescription;
	CComBSTR m_bstrName; 
	long m_lDisplayPeriod; 
	long m_lBlackoutPeriod;
	long m_lHighlightPeriod;
	long m_lCursorHeight;
	long m_lCursorWidth;
	long m_lBaseTime;
	long m_lCursor;
	long m_lTop;
	long m_lBottom;
	long m_lRight;
	long m_lLeft;
	long m_lLogLevel;
	long m_lHelpType; 
	short m_sFillType; 
	short m_sFillPercent; 
	CComBSTR m_bstrDemoPath; 
	CComBSTR m_bstrHelpPath; 
	CComBSTR m_bstrHelpStartPage; 
	CComBSTR m_bstrHelpContextPage; 
	bool m_bShowControls;
	bool m_bShowTrackBar;
	bool m_bShowMetafile;
	bool m_bShowStatusBar; 
	bool m_bSDKMode; 

	CComPtr<ISettings> m_pSettings; 
};

#endif // !defined(AFX_WINBLITPROPERTIES_H__54E134D4_6163_11D5_8611_82E94F000000__INCLUDED_)
