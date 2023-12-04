//***************************************************************************
//*
//*		Name		: WinBlitConstants.h
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
//*
//* 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

enum eDATASOURCETYPE {
	e_STRING = 0,
	e_TXTFILEASCII = 1, 
	e_TXTFILEUNICODE = 2, 
	e_WORD_OPENDOCUMENT = 3,
	e_WORD_FILE = 4,
	e_HTML_OPENDOCUMENT = 5, 
	e_HTML_FILE = 6, 
	e_ADOBE = 7,
	e_INFO_LOADINGDATA = 98,
	e_INFO_NONE = 99
};

enum eFIXWIDTHTYPE {
	e_CHARS = 0, 
	e_COLUMNS = 1, 
	e_WORDS = 2
};

static int ciMaxFixWidthTypes = 3;

static const WCHAR* cawchFixWidthTypes [3] = {	L"Characters", 
												L"Columns",
												L"Words" }; 

static const WCHAR* cawchFixWidthDescriptions [3] = 
{L"Fixation width is determined by the number of characters. You can set up the maximum number of characters allowed in a fixation on the Fixation Details tab", 
 L"Fixation width is determined by the width of a column. You can set up the number of columns on the Fixation Details tab", 
 L"Fixation width  is determined by the number of words. You can set up the maximum number of words in a fixation on the Fixation Details tab"}; 


static int ciMaxStatistics = 3;
const CComBSTR bstrStatisticNames [3] = {"Word","ElapsedTime","ReadTime"};

static const WCHAR cawchWhiteSpaceArray[] = { L' ', L'\r', L'\n', L'\t',  L'\f', L'\0'};
static const int ciDefaultWordSize = 200;

static const int   ciWhiteSpaceArraySize = 5; 
static const DWORD cdwPageSize(500); 
static const CComBSTR cbstrSelDefault = " (Default) ";

static const int ilf (10);
static const WCHAR cwchLF = static_cast<WCHAR> (ilf);
static const int icr(13); 
static const WCHAR cwchCR = static_cast<WCHAR> (icr);
static const WCHAR cwchNewLine (L'\n');
static const WCHAR cawchNewLine [2]  = {L'\n', L'\0'};
static const WCHAR cwchSpace (L' ');
static const WCHAR cwchPeriod (L'.');
static const WCHAR cwchNull (L'\0');

static const DWORD cdwTXTReadBufferLength (10000); 

static const CComBSTR cbstrWinBlitKey [2] = {	"Software\\PataSucia\\WinBlit\\Configurations\\",
												"Software\\PataSucia\\WinBlit\\Templates\\"};
static const CComBSTR cbstrWinBlitKeyDelete [2] = {
												"Software\\PataSucia\\WinBlit\\Configurations",
												"Software\\PataSucia\\WinBlit\\Templates"};

static const CComBSTR cbstrSettings = "\\Settings";
static const CComBSTR cbstrDefault = "Default";

static const TCHAR* tchRuleType [2] = 
	{	"Pause ",
		"Delay "	};

static const TCHAR* tchWidthText [5] = 
{	"System error",
	"column (fixation is width of screen)",
	"columns",
	"characters per fixation (maximum)",
	"words per fixation (maximum)"};


static const TCHAR* tchRowText [3] = 
{	"System error",
	"row",
	"rows"};

static const int ciRuleType = 2;

static const int ciSpeedMin (12); 
static const int ciSpeedMax (1200);

static const int ciPeriodMin (0); 
static const int ciPeriodMax (10000); 

static const int ciPercentMin (0); 
static const int ciPercentMax (100); 

static const int ciFreq (100); 

static const int ciToolBarHeight (24); 

static const int ciTrackBarHeight (25); 

static const int ciTrackFreq	(1);
static const int ciTrackMin		(0);
static const int ciTrackMax		(10000);
static const DWORD dwPercentage (10000);

static const int ciMaxTrialCharacters(5000); 

#endif