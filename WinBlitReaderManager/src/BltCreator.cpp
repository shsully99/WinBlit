//***************************************************************************
//*
//*		Name		: BltCreator.cpp
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
//*		Implements the algorithms for sectoring WinBlit's 
//*		screen into rectangles 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

#include "stdafx.h"
#include "BltCreator.h"
#include "WinBlitProperties.h"
#include "WinBlitConstants.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBltCreator::CBltCreator() //:  m_pStrategy (NULL)
{	
}

CBltCreator::~CBltCreator()
{
}

//===========================================================================
//
//	Method:			Uninitialise 
//
//	Description :	Clear up memory 
//
//============================================================================

void CBltCreator::Uninitialise ()
{
	m_plistBlts->clear(); 
	m_vexcess.clear();
}

//=========================================================================== 
//						
//	Method :		Initialise
//						
//	Description :	Initialise the object to create a new page of 
//					blits for the supplied ListBlts pointer 
//					which we then store as a member variable.
//	
//	Returns			void
//				  
//============================================================================

void CBltCreator::Initialise	(CWinBlitProperties *pWinBlitProperties, 
								int iLineWidth, 
								int iScreenHeight,
								LISTBLTS* pListBlts,
								int iSpaceSize ,
								int iOverhang)
{
	m_iIndex = 0;
	m_iBltPos = 0;
	m_pProp = pWinBlitProperties; 
	m_iLineWidth = iLineWidth;
	m_iScreenHeight = iScreenHeight; 
	m_plistBlts = pListBlts; 
	m_iSpaceSize = iSpaceSize; 
	m_iOverhang = iOverhang; 

	// Clear out exisiting blts. 
	m_plistBlts->clear(); 
	m_vexcess.clear(); 
}

//=========================================================================== 
//						
//	Method :		AddLine
//						
//	Description :	Called by client to create the blits for 
//					a single line
//	
//	Returns			0
//				  
//============================================================================

int CBltCreator::AddLine	(	int						iTotalExtent,		// Extent of line 
								VECWORDSITERATOR		vitStart,			// First word
								VECWORDSITERATOR		vitEnd,				// Last word
								LISTPARAGRAPHSITERATOR	pit,				// Pointer Paragraph
								int						iLineOffsetStart,	// Offset of first word in string
								int						iLineNumber)		// Line number
{
	ATL_TRACE0 (e_LOGDETAIL, "\n AddLine "); 

	VECWORDSITERATOR vit; 

	// If this is the first word in the paragraph or the previous word was a 
	// sentence end then a new index is required for static type cursors. 
	if ( (cRSVPCursor & m_pProp->Cursor()) ||
		 (cRandomCursor & m_pProp->Cursor()))
	{
		if (vitStart == pit->m_vecWords.begin())
		{
			m_iIndex++; 
			m_iCount = 0;
			m_iExtentCount = 0; 
		}
	}
	// For seqential and slowhand cursors 
	// always reset count at start of line 
	else if ( (cTachistoscopicCursor & m_pProp->Cursor()) ||
		 	  (cSlowHandCursor   & m_pProp->Cursor())  ) 
	{
		m_iCount = 0;
		m_iIndex++; 
		m_iExtentCount = 0; 
	}

	// Total words on line 
	int iWordTotal = distance(vitStart, vitEnd)+1;

	// Total characters on line 
	int iCharTotal = vitEnd->m_iOffset - iLineOffsetStart;

	int iExcessWords = 0;
	if ((cWordDivisions         & m_pProp->Cursor()) &&  
		(cEqualiseWordDivisions & m_pProp->Cursor()))
	{
		iExcessWords = InitExcessWordsVector (iWordTotal, m_pProp->CursorWidth());	
	}

	int iOffset = iLineOffsetStart;						// Offset in string buffer of word start
	int iFixationHeight = m_pProp->CursorHeight();		// Height of each fixation  
	int iFixationWidth  = m_pProp->CursorWidth();		// Width of each fixation 
	vit = vitStart;										// Iterator into words vector  

	int iIndex = 0;		
	vector<int>::iterator vexsit;						// Iterator for excess words array 

	if (iExcessWords > 0)
	{
		vexsit = m_vexcess.begin();
		iFixationWidth -= *vexsit;
	}
	int xPos   = 0;
	short sSentenceEnd = 0;								// Was previous word end of a sentence
	int iBlitTotal = 1;									// Total of fixations on line 

	if (cLineDivisions & m_pProp->Cursor())
	{
		iBlitTotal = m_pProp->CursorWidth(); 
	}

	do 
	{
		if (cLineDivisions & m_pProp->Cursor())
		{
			// The index depends on the physical poisiton of the centre of the word. 
			// Find the centre of the word 
			int iCentre = xPos + abs(vit->m_sTextExtent / 2);
			// Find which sector of the screen it fits on. 
			int iPos = iCentre / (m_iLineWidth / m_pProp->CursorWidth());
			// Assign blit index value to a word 
			vit->m_sBltIndex =  ((iLineNumber / iFixationHeight) * iFixationWidth ) + iPos;
		}
		else if (cCharDivisions & m_pProp->Cursor())
		{
			bool bNewIndex = false; 

			if (m_iCount + (vit->m_iOffset - iOffset) > iFixationWidth )
			{
				bNewIndex = true;
			}
			else if ( m_iExtentCount > 0 && m_iExtentCount + abs(vit->m_sTextExtent) > m_iLineWidth)
			{
				bNewIndex = true;
			}
			else if (sSentenceEnd == -1 &&  (cRSVPCursor   & m_pProp->Cursor() || 
											 cRandomCursor & m_pProp->Cursor()) )
			{
				bNewIndex = true;
			}
			if (bNewIndex)
			{
				m_iIndex++;
				m_iCount=0;
				m_iExtentCount = 0;
				vit->m_sBltIndex = m_iIndex;
				iBlitTotal++;
			}
			vit->m_sBltIndex = m_iIndex;
			m_iCount+= vit->m_iOffset - iOffset; 
			iOffset = vit->m_iOffset;
		}
		else if (cWordDivisions & m_pProp->Cursor())
		{
			bool bNewIndex = false; 
			if (m_iCount == iFixationWidth)
			{
				bNewIndex = true;
			}
			else if (m_iExtentCount > 0 && m_iExtentCount + abs(vit->m_sTextExtent) > m_iLineWidth) 
			{	
				bNewIndex = true;
			}
			else if (sSentenceEnd == -1 &&  (cRSVPCursor   & m_pProp->Cursor() || 
											 cRandomCursor & m_pProp->Cursor()) )
			{
				bNewIndex = true;
			}
			if (bNewIndex)
			{
				iFixationWidth =  m_pProp->CursorWidth();
				if (iExcessWords > 0) 
				{
					vexsit++;
					iFixationWidth = m_pProp->CursorWidth() - *vexsit;
				}
				m_iExtentCount = 0;
				m_iIndex++;
				iBlitTotal++;
				m_iCount=0;
			}
			vit->m_sBltIndex = m_iIndex;
			m_iCount+=1;
		}
		// Increment  offset and iterator for the next word. 
		m_iExtentCount+= abs(vit->m_sTextExtent);
		xPos += abs(vit->m_sTextExtent);			
		iOffset = vit->m_iOffset;
		vit->m_sFiller = 0; 
		sSentenceEnd = vit->m_sSentenceEnd;
		vit++;
	} while (vit <= vitEnd);

	// If this is the last line and the last word has no spaces in it then add in the overhang. 
	if (vitEnd == pit->m_vecWords.end() -1 )
	{
		if (cwchSpace != pit->m_str[pit->m_str.size()])
		{
			if (vitEnd->m_sTextExtent > 0)
			{
				vitEnd->m_sTextExtent += m_iOverhang; 
			}
			else
			{
				vitEnd->m_sTextExtent -= m_iOverhang; 
			}
		}
	}


	iWordTotal--; 
	iBlitTotal--; 
	int iFillperBlit = 0;					// Number of pixels to be added to each blit to fill screen 
	int iFillperWord = 0;					// Number of pixels to be added to each word to fill screen 
	int iExtraFillperWord =  0;				// Extra filler per word at start and end of line 
	int iExtraFillperBlit = 0;				// Extra filler per blit at start and end of line 
	int iFillTotal = 0;

	if ( vitEnd				  != pit->m_vecWords.end() -1  && 
		 m_pProp->FillType() != e_FILL_NONE )
	{
		if ( (cTachistoscopicCursor & m_pProp->Cursor()) ||
			 (cSlowHandCursor   & m_pProp->Cursor())  ) 
		{
			float fTemp = (float(iTotalExtent) / float(m_iLineWidth)) * 100;
			if (fTemp >= m_pProp->FillPercent())
			{
				iFillTotal = m_iLineWidth - iTotalExtent; 
				if		(e_FILL_BETWEEN_WORDS == m_pProp->FillType() && iWordTotal > 0)
				{
					iFillperWord = iFillTotal / iWordTotal;
					iExtraFillperWord = (iFillTotal % iWordTotal)/2; 
				}
				else if (e_FILL_BETWEEN_BLITS == m_pProp->FillType() && iBlitTotal > 0)
				{
					iFillperBlit = iFillTotal / iBlitTotal;
					iExtraFillperBlit = (iFillTotal % iBlitTotal)/2; 
				}
				else if (e_FILL_BETWEEN_BOTH  == m_pProp->FillType()  && iWordTotal > 0)
				{
					if (iBlitTotal > 0)
					{
						iFillperWord = (iFillTotal / iWordTotal) / 2;
						iFillperBlit = (iFillTotal / iBlitTotal) / 2;
					}
					else
					{
						iFillperWord = iFillTotal / iWordTotal;
						iExtraFillperWord = (iFillTotal % iWordTotal)/2; 
					}
				}
			}
		}
	}

	ATL_TRACE4 (e_LOGDETAIL, "\n iFillperBlit %d iFillperWord %d iExtraFillperWord %d iExtraFillperBlit %d ",iFillperBlit, iFillperWord, iExtraFillperWord ,iExtraFillperBlit); 
	ATL_TRACE0 (e_LOGDETAIL, "\n Before Words ");

	vit = vitStart;
	do {
		ATL_TRACE3  (e_LOGDETAIL," @@ %d %d %d ", abs(vit->m_sTextExtent), vit->m_sFiller, vit->m_sBltIndex);
		vit++;
	}while (vit <= vitEnd);

	vit = vitStart;
	iIndex = -1;							// Force creation of new blit 1st time
	xPos   = 0;										
	int iWordCount = 0; 
	LISTBLTITERATOR lblt; 
	LISTBLTITERATOR lbltOld = m_plistBlts->end(); 
	lbltOld--;

	iOffset = 0; 

	do 
	{
		// Add in filler to words and blits if this is not the first word.
		if (vit != vitStart && iFillTotal > 0)
		{
			if (0 != iFillperWord) 
			{
				// Add in filler per word 
				vit->m_sFiller += iFillperWord; 
			}

			if (iExtraFillperWord > 0)
			{
				if (iWordCount - iExtraFillperWord > 0)
				{
					// Extra filler between words at start of line 
					vit->m_sFiller += 1;
				}
				else if ( (iWordTotal -  iExtraFillperWord) < iWordCount)
				{
					// Extra filler between words at end of line 
					vit->m_sFiller += 1;
				}
			}

			// If we are about to add a new blit check to see if there is 
			// any fill required between blits and
			if (vit->m_sBltIndex != iIndex)
			{
				if (0 != iFillperBlit) 
				{
					// Add in filler per blit 
					vit->m_sFiller += iFillperBlit; 
				}

				if (iExtraFillperBlit > 0)
				{
					if (iWordCount - iExtraFillperBlit > 0)
					{
						// Extra filler between blits at start of line 
						vit->m_sFiller += 1;
					}
					else if ( (iWordTotal -  iExtraFillperBlit) < iWordCount)
					{
						// Extra filler between blits at end of line 
						vit->m_sFiller += 1;
					}
				}
			}
		}
		// Move xPos along to take account of filler 
		xPos += vit->m_sFiller; 

		// Index has changed - create a new blit
		if (vit->m_sBltIndex != iIndex)
		{
			iIndex = vit->m_sBltIndex;

			m_plistBlts->push_back (CBlt(iLineNumber,xPos,iIndex));

			lblt = m_plistBlts->end(); 
			lblt--; 
		}
		else 
		{
			lblt->m_sxExt += vit->m_sFiller;
		}

		lblt->m_sxExt += abs(vit->m_sTextExtent);	
		xPos += abs(vit->m_sTextExtent);	

		lblt->m_sWordCount++;
		iWordCount++; 
		
		if (!pit->m_listCursorAction.empty() && FALSE == lblt->m_bPause)
		{
			if (0 == iOffset && vit != pit->m_vecWords.begin())
			{
				VECWORDSITERATOR pvit = vit;	pvit--;
				iOffset = pvit->m_iOffset+1; 
			}

			// Check for breakpoints if we do not already have a pause set up. 
			CheckCursorActions(pit, iOffset, vit->m_iOffset, &lblt->m_bPause, &lblt->m_iDelay);
		}
		iOffset = vit->m_iOffset;

		vit++;
	} while (vit <= vitEnd);

	ATL_TRACE0 (e_LOGDETAIL,"\n After Words ");
	vit = vitStart;
	do {
		ATL_TRACE3  (e_LOGDETAIL," @@ %d %d %d ", abs(vit->m_sTextExtent),  vit->m_sFiller,  vit->m_sBltIndex );
		vit++;
	}while (vit <= vitEnd);

	ATL_TRACE0  (e_LOGDETAIL,"\n After  Blits  ");
	lbltOld++;

	do {
		ATL_TRACE2  (e_LOGDETAIL," @@ %d %d ",lbltOld->m_sxPos, lbltOld->m_sxExt); 
		lbltOld++;
	}while (lbltOld != m_plistBlts->end());

	return 0; 
}

//===========================================================================
//
//	Method :		Sort 
//
//	Description :	Called after the blits have been created to sort them 
//					into order based on the value of the blits m_sIndex 
//					property.
//
//	Returns	:		void
//
//============================================================================

void CBltCreator::Sort (int iLineCount)
{	
	ATL_TRACE0  (e_LOGDETAIL, "\nCBltCreator::Sort");

	int iLine = -1; 

	// For slowhand cursor we must reverse alternate lines
	if (cSlowHandCursor & m_pProp->Cursor() && iLineCount > 0)
	{
		m_iIndex = 0; 

		if (m_pProp->CursorHeight() <= 1)
		{
			// Build vector of last index value on eash line 
			LISTBLTITERATOR lblt = m_plistBlts->begin(); 
			int iLineNumber = -1;
			int iIndex = -1;
			vector<int> vecindex; 
			vecindex.resize(iLineCount+1); 
			do
			{
				if (lblt->m_sLineNumber != iLineNumber)
				{
					iLineNumber = lblt->m_sLineNumber;
				}
				vecindex[iLineNumber] = lblt->m_sIndex;
				lblt++; 
			}while (lblt != m_plistBlts->end() );

			LISTBLTITERATOR lbltA = m_plistBlts->begin(); 

			lbltA = m_plistBlts->begin(); 
			do 
			{	
				// Do we need to reverse this line 
				if (0 != (lbltA->m_sLineNumber / m_pProp->CursorHeight()) % 2)
				{
					// Yes so reset its index to the end. 
					lbltA->m_sIndex = vecindex[lbltA->m_sLineNumber];
					vecindex[lbltA->m_sLineNumber]-=1 ;
				}
				lbltA++;
			}while (lbltA != m_plistBlts->end());
			vecindex.clear(); 
		}
		else
		{
			// Slow hand with a line height greater than 1
			LISTBLTITERATOR lbltA = m_plistBlts->begin(); 

			lbltA = m_plistBlts->begin(); 
			do 
			{	
				// Do we need to reverse this line 
				if (0 != (lbltA->m_sLineNumber / m_pProp->CursorHeight()) % 2)
				{
					// Index at start of this line 
					int iStartIndex = (lbltA->m_sLineNumber / m_pProp->CursorHeight()) * m_pProp->CursorWidth();
					// Index at start of next line 
					int iNextLineIndex = iStartIndex + m_pProp->CursorWidth();
	ATL_TRACE1  (e_LOGDETAIL, "\n Index change %d ",lbltA->m_sIndex );
					lbltA->m_sIndex = iNextLineIndex -  1 - (lbltA->m_sIndex - iStartIndex);

	ATL_TRACE1   (e_LOGDETAIL, "to  %d ",lbltA->m_sIndex );


				}
				lbltA++;
			}while (lbltA != m_plistBlts->end());
		}
	}

	// Sort everything into index order 
	m_plistBlts->sort();	
}

//===========================================================================
//
//	Method :		CheckCursorActions	
//
//	Description :	See if there is a breakpoint required for a word 
//					and if so set up the pause or delay member variable of the blit
//
//	Returns	:		void
//
//============================================================================

void CBltCreator::CheckCursorActions
						(LISTPARAGRAPHSITERATOR pit,			// Paragraph iterator
						int iStartOffset,						// Start of Offset of word in paragraph
						int iEndOffset,							// End of Offset of word in paragraph
						BOOL* pbPause,							// Pointer to pause value of blit
						int*  piDelay)							// Pointer to delay field of blit
{
	ATL_TRACE2  (e_LOGDETAIL, "\n CBltCreator::CheckCursorActions %d %d", iStartOffset,iEndOffset); 
	LISTCURSORACTIONITERATOR lit = pit->m_listCursorAction.begin();
	do 
	{
		if (lit->m_iOffset >= iStartOffset &&
			lit->m_iOffset < iEndOffset)
		{
			ATL_TRACE2  (e_LOGDETAIL, " Adding breakpoint %d %d ", lit->m_iOffset, lit->m_sActionType); 

			if		(lit->m_sActionType == 1)
			{
				*pbPause = TRUE; 
			}
			else if (lit->m_sActionType == 2)
			{
				*piDelay = lit->m_iPeriod;
			}
		}
		lit++;
	} while (lit != pit->m_listCursorAction.end());
}

//===========================================================================
//
//	Method :		InitExcessWordsVector	
//
//	Description :	Initialise the excess words vector. 
//					The excess words vector has one entry for each fixation on 
//					a line. Each entry contains the number of words which need to  
//					be knocked off that fixation to equalise fixation size across 
//					the line.
// 
//	Returns	:		The number of excess words on this line 
//
//============================================================================

int CBltCreator::InitExcessWordsVector(int iWordTotal, int iCursorWidth)
{
	int iExcessWords = 0;						// Assume no excess words 

	// Try and equalise the word breaks over the line. 
	int iTemp = (iWordTotal / m_pProp->CursorWidth()) * m_pProp->CursorWidth(); 

	if (iTemp == iWordTotal || iTemp == 0) 
	{
		// Nothing to do - there can only be one fixation.
	}
	else if  (iTemp < iWordTotal)
	{
		// Resize vector to number of fixations.
		m_vexcess.resize((iTemp/m_pProp->CursorWidth())+1);
		vector<int>::iterator vexsit = m_vexcess.begin();
		for (;  vexsit != m_vexcess.end(); vexsit++) 
		{
			 *vexsit = 0;
		}
		iExcessWords = m_pProp->CursorWidth() + iTemp - iWordTotal;
		do 
		{
			vexsit = m_vexcess.end();
			// We cannot break evenly over the lines  
			do 
			{					
				vexsit--;
				(*vexsit)+=1;
				if (--iExcessWords == 0) break;

			}while (vexsit != m_vexcess.begin());

		}while (iExcessWords > 0);

		iExcessWords = iWordTotal - iTemp;

	}
	return iExcessWords;
}