//***************************************************************************
//*
//*		Name		: StlClasses.h
//*							
//*		$Revision:$
//*
//*		Date        : 21-feb-2002
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
//*		Defintions of classes used in STL containers 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

#ifndef STLCLASSES_H
#define STLCALSSES_H

#include <map> 
#include <vector> 
#include <list> 
#include <algorithm>
#include <string>

using namespace std; 

// Represents a word in a paragraph

class CWord
{
public:
	CWord::CWord() { CWord::CWord(0,0, 0);};
	CWord::CWord(int iOffset,short sTextExtent, short sSentenceEnd): m_iOffset (iOffset), m_sTextExtent(sTextExtent), m_sBltIndex(0), m_sFiller (0), m_sSentenceEnd(sSentenceEnd)
	{
		ATL_TRACE ("%d <> ", sTextExtent); 
	};
	int m_iOffset;			// Offset from Paragraph start for end of this word
	short m_sTextExtent;	// Text Extent for the word -ve if the word starts a line
	short m_sBltIndex;		// Blt Index  of this word 
	short m_sFiller;		// Filler extent before this word.
	short m_sSentenceEnd;	// -1 if true.
};

// STL typedefs for vector collections of Word objects 

typedef vector<CWord> VECWORDS;
typedef vector<CWord>::const_iterator	VECWORDSCONST_ITERATOR;
typedef vector<CWord>::iterator			VECWORDSITERATOR;
typedef vector<CWord>::reverse_iterator	VECWORDSREVERESITERATOR;
typedef vector<CWord>::reference		VECWORDSREFERENCE;
typedef vector<CWord>::difference_type	VECWORDSDIFFERENCE; 

//	Cursor action represents an action aka rule or setting to be
//	performed once a particular blit is displayed 

class CCursorAction
{
public:
	CCursorAction::CCursorAction() { CCursorAction::CCursorAction(0,0,0);};
	CCursorAction::CCursorAction(	int iOffset,	short sActionType,	int iPeriod):
 		m_iOffset		(iOffset)		,  
		m_sActionType	(sActionType)	,
		m_iPeriod		(iPeriod)
		{};

	int	m_iOffset;				// Offset in paragraph for action 
	short m_sActionType;		// 1 = pause at , 2 = delay 
	int	m_iPeriod;				// Delay period
};

// STL typedefs for STL lists of cursor actions 

typedef list<CCursorAction> LISTCURSORACTION;
typedef list<CCursorAction>::const_iterator LISTCURSORACTIONCONST_ITERATOR;
typedef list<CCursorAction>::iterator LISTCURSORACTIONITERATOR;
typedef list<CCursorAction>::reference LISTCURSORACTIONREFERENCE;
typedef list<CCursorAction>::difference_type LISTCURSORACTIONDIFFERENCE; 

// Paragraph class 

class CParagraph
{
public:
	CParagraph::CParagraph() 
	{
		CParagraph::CParagraph( 0, NULL); 
	};
	CParagraph::CParagraph(int iParagraphNumber, BSTR bstrVal) :	
							m_iParagraphNumber			(iParagraphNumber),
							m_bWhitespace				(false) ,
							m_str						(bstrVal,  ::SysStringLen(bstrVal)) ,
							m_listCursorActionIterator  (NULL),
							m_iLineCount				(0)
	{
		m_vecWords.clear();
		m_vecSentences.clear(); 
		m_listCursorAction.clear();
	};

	VECWORDS m_vecWords;						// All the words in this paragaph
	vector<int> m_vecSentences;					// Offset of end of sentence
	wstring m_str;								// Text of paragraph
	int  m_iParagraphNumber;					// Paragraph number
	int  m_iLineCount;							// Number of lines in paragraph 
	bool m_bWhitespace;							// True if this paragraph just contains whitespace

	LISTCURSORACTION			m_listCursorAction; // Actions to perform when this paragraph is displayed
	LISTCURSORACTIONITERATOR	m_listCursorActionIterator; 

	CParagraph::~CParagraph()
	{
		m_str.erase(m_str.begin(), m_str.end()); 
		m_vecWords.clear();
		m_vecSentences.clear(); 
		m_listCursorAction.clear();
	}
};

// STL typedefs for lists of paragraph objects

typedef list<CParagraph> LISTPARAGRAPHS;
typedef list<CParagraph>::iterator LISTPARAGRAPHSITERATOR;
typedef list<CParagraph>::const_iterator LISTPARAGRAPHSCONST_ITERATOR;
typedef list<CParagraph>::reference LISTPARAGRAPHSREFERENCE; 

//=========================================================================

enum eWORDSTATE {
			EAT_WHITESPACE_BEFORE_WORD	= 1,
			EAT_WORD_UNTIL_WHITESPACE	= 2,
			EAT_WHITESPACE_AFTER_WORD	= 3,
			FINISHED_EATING = 4
};

//=========================================================================

// Enumerator for the state machine of the cursor 

enum eCURSOR {
	e_DISPLAYCURSOR = 1,
	e_HIGHLIGHTCURSOR = 2,							
	e_BLACKOUTCURSOR = 3
};

typedef vector<eCURSOR> VECCURSOR;
typedef vector<eCURSOR>::iterator VECCURSORITERATOR;

//=========================================================================

// Class containing all information for a single recatngle blit onto the screen 

class CBlt 
{
public:
	CBlt()	{	CBlt::CBlt(0,0,0); };
	CBlt(short sLineNumber,	
		 short sxPos, 
		 short sxIndex): 
	m_sLineNumber(sLineNumber), 
	m_sxPos(sxPos),
	m_sIndex(sxIndex),
	m_sxExt(0), 
	m_sRand(0),
	m_bPause(FALSE), 
	m_iDelay(0),
	m_sWordCount(0) {};

	short m_sLineNumber;				// Line number to blit to 
	short m_sxPos;						// x position of blit in pixels
	short m_sxExt;						// Extent of blit
	short m_sIndex;						// Index of this blit. Blits with the 
										// same index are all blitted together
	int	 m_sRand;						// Random number for random cursor
	BOOL m_bPause;						// Pause required after this blit ( a rule)
	int	 m_iDelay;						// Period of delay following blit
	short m_sWordCount;					// Count of words used in this blit

	// These 2 methods are used in sorting an array into index 
	// order when the STL container blit instruction is issued. 

	bool operator > (const CBlt& BltA)  const 
	{
		if (BltA.m_sIndex      > this->m_sIndex)
		{
			return false;
		}
		else if (BltA.m_sIndex     == this->m_sIndex &&
				 BltA.m_sLineNumber > this->m_sLineNumber)
		{
			return false; 
		}
		else 
		{
			return true; 
		}
	};
	bool operator< (const CBlt& BltA) const
	{
		if (BltA.m_sIndex      < this->m_sIndex)
		{
			return false;
		}
		else if (BltA.m_sIndex     == this->m_sIndex &&
				 BltA.m_sLineNumber < this->m_sLineNumber)
		{
			return false; 
		}
		else 
		{
			return true; 
		}
	};
};

//	Typedefs for STL containers of blit operations

typedef list <CBlt> LISTBLTS;
typedef list <CBlt>::const_iterator LISTBLTSCONST_ITERATOR;
typedef list <CBlt>::reference LISTBLTSREFERENCE;  
typedef list <CBlt>::value_type LISTBLTVALUE;
typedef list <CBlt, LISTBLTS::allocator_type >::iterator LISTBLTITERATOR;

#endif