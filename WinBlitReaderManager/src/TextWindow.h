//***************************************************************************
//*
//*		Name		: TextWindow.h
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
//*		Screen Display object
//* 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/
//////////////////////////////////////////////////////////////////////
//
// TextWindow.h: interface for the CTextWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined _TextWindow_H
#define _TextWindow_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WinBlitConstants.h"
#include "WinBlitReaderManager.h"
#include "BltCreator.h"
#include "atlgdi.h"

interface ISettings;
interface IStatistics; 

//
//=========================================================================
//

class CWinBlitReader; 

class CWinBlitProperties;

class CTextWindow  
{
public:
	int GetCurrentPercentage();
	int TickTock(bool bReDisplay = false);
	void SetWindow	(HWND hWnd);
	void SetRect	(RECT rc);
	RECT GetRect    (void); 
	void ReDisplayOnTimer();
	void ResetBlits();
	void Initialise(CWinBlitProperties* m_pProp, CWinBlitReader *pReader);
	void GetCurrentStatistics (long& lReadTime, long& lWordCount);
	void Uninitialise();
	int LoadData (eDATASOURCETYPE eDataSourceType, VARIANT varDataSource);
	void UnLoadData ();
	void SetupTimePeriods();
	int Display (int iMove, int iQuantity = 0); 
	void OnBeforeTimerStart (int iType); 
	void OnAfterTimerStop	(int iType); 
	CTextWindow();
	virtual ~CTextWindow();
	CWinBlitReader* m_pWinBlitReader; 
	HRESULT get_Statistics(/*[out, retval]*/ IDispatch* *pVal);
	CComPtr<IStatistics> m_pStatistics;		// Pointer to statistics collection

protected:	
	
	// WinBlit public preoperties 
	HWND m_hWnd;							// Container supplied Client window 
	CWinBlitProperties* m_pProp;				// Pointer to WinBlit Properties 
	CBltCreator m_BltCreator;				// Class to create the screen blits 
	long m_lActualDisplayPeriod;			// Period of display in milliseconds
	long m_lActualBlackoutPeriod;			// Blackout period in milliseconds
	long m_lActualHighlightPeriod;			// Highlight  period in milliseconds
	long m_lWordCount;						// Word count for statistics
	DWORD m_dwElapsedTickCount;				// 
	DWORD m_dwReadTickCount;

	DWORD m_dwTickTock;						// Time of last call to Tick Tock method
	DWORD m_dwTickTockInterval;				// 

	RECT m_PreviousRect;					// Member var used to see if rect has changed
	RECT m_ClientTextRect;					// Client DC area just for text
	RECT m_ClientDisplayRect;				// Client Display DC area
	RECT m_OffScreenTextRect;				// Offscreen DC area just for text
	RECT m_OffScreenDisplayRect;			// Client Display DC area
	VECCURSOR m_vecCursorStates;			// State machine of a single flashing cursor 
	VECCURSORITERATOR m_vecCursorStateIterator;		// Current position of cursor state machine
	LISTBLTS			m_listBlts;					// BLT sandwiches 
	LISTBLTITERATOR		m_listBltCurrentIterator;	// Current  iterator 	
	LISTBLTITERATOR		m_listBltPreviousIterator;	// Previous iterator 	

	bool m_bInitialised; 
	bool m_bSoundClick;					
	
	int m_Ascii2Ext[256];				// Extpoint mapping for Words array.
	int m_iOverhang;					// Text overhang. 

	
	int m_iCurrentFirstWord;			// Word in Paragrpahs array representing word which starts the page 
	int m_iCurrentFirstParagraph;		// Paragraph number of first paragraph displayed
	int m_iDisplayCount;				// No of lines currently displaying 
	int m_iTrialCharCount;				// Maximum characters count for trial version 
	int m_iTrialLastParagraph;			// Last Paragraph for trial version 
		
	int m_iScreenHeight;				// Screen height 
	int m_iLineWidth;					// Width of screen in pixels
	int m_iCharHeight;					// Height of a line in pixels 
	
	LISTPARAGRAPHS	m_Paras;			// Paragraphs array
	CComQIPtr<IWinBlitData> m_pWinBlitData; 
		
	int  MakePage		 ();
	int  MovePercentage	 (int iLineMove);
	int  MovePage		 (int iLineMove);
	int  MakeParagraph	 (int iParagraphNumber,	int iLocation);
	int  SortParagraphs();
	void MakeBlts		 ();

	void  BlitToScreen	 (HDC hdcTo,
						  eCURSOR e_CursorState, 
						  HDC hdcFrom,
						  LISTBLTITERATOR lblt);



	int GetLineNumberforWord	(LISTPARAGRAPHSITERATOR pit, int iWord);
	int GetWordforLineNumber(LISTPARAGRAPHSITERATOR pit, int iLineNumber);
	int GetOffsetforWord(LISTPARAGRAPHSITERATOR pit, int iWord);

	void DisplayCurrentCursor (HDC hdc);

	CBitmap m_BitMapCursor;				// Bitmap for cursor DC 
	CBitmap m_BitMapScreen;			// Bitmap for screen DC
	CDC		m_DCCursor;					// Device context for offscreen DC to draw cursor
	CDC		m_DCScreen;					// Device context for offscreen DC to draw screen

	HRSRC m_hWaveRes;					// Handle for resource sound
	HANDLE m_hGlobMem;					// Handle for resource sound


};		

#endif // !defined(AFX_TEXTWINDOW_H__FA86B346_2D97_11D5_85C1_24B6A1000000__INCLUDED_)