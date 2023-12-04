//***************************************************************************
//*
//*		Name		: BltCreator.h
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
//*		Implements the algorithms for sectoring WinBlit's screen into 
//*		rectangles 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

#if !defined(AFX_BLTCREATOR_H__D7847353_6EC4_11D5_8625_60CF6D000000__INCLUDED_)
#define AFX_BLTCREATOR_H__D7847353_6EC4_11D5_8625_60CF6D000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StlClasses.h"

class CWinBlitProperties; 



class CBltCreator  
{
	int m_iIndex;							// Index of blt 
	int m_iBltPos;							// Blt position 
	int m_iCount;							// Running count of chars,words or line divisions 
	int m_iLineWidth;						// Width of screen. 
	int m_iScreenHeight;					// Height of screen 
	int m_iSpaceSize;						// Size of a space in pixels for current font
	int m_iExtentCount;						// Count of text extent 
	int m_iOverhang;						// Overhang value 
	CWinBlitProperties *m_pProp;			// Pointer to WinBlit's Properties object
	LISTBLTS* m_plistBlts;					// LISTBLTS pointer 
	vector<int>   m_vexcess;				// Excess words array. 


public:

	CBltCreator		();			
	void Initialise	(	CWinBlitProperties*	pWinBlitProperties,
						int					iLineWidth,
						int					iScreenHeight,
						LISTBLTS*			pListBlts,
						int					iSpaceSize,
						int					iOverhang);
	void Uninitialise ();
	int  AddLine (int					 iTotalExtent,
				  VECWORDSITERATOR		 vitStart, 
				  VECWORDSITERATOR		 vitEnd, 
				  LISTPARAGRAPHSITERATOR pit,
				  int					 iLineOffsetStart,
				  int					 iLineNumber);

	void Sort		(int iLineCount); 
	virtual ~CBltCreator();

protected:
	int InitExcessWordsVector(int iWordTotal, int iCursorWidth);


	void CheckCursorActions(LISTPARAGRAPHSITERATOR pit, 
							int iStartOffset,
							int iEndOffset,	
							BOOL* bPause, 
							int*  iDelay);


};

#endif // !defined(AFX_BLTCREATOR_H__D7847353_6EC4_11D5_8625_60CF6D000000__INCLUDED_)
