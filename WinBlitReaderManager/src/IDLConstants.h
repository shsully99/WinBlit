//***************************************************************************
//*
//*		Name		: IDLConstants.h
//*							
//*		$Revision:$
//*
//*		Date        : 20-Jul-2001
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

#ifndef _CursorTypes_h	
#define _CursorTypes_h	

	typedef enum CursorConfiguration {
		cDisplayScreenText			= 1,
		cDisplayCursorText			= 2,
		cRSVPCursor					= 4,
		cTachistoscopicCursor		= 8,
		cRandomCursor 				= 16,
		cSlowHandCursor				= 32,
		cUnused1					= 64,
		cLineDivisions				= 128,
		cWordDivisions				= 256,
		cCharDivisions				= 512,
		cEqualiseWordDivisions		= 1024, 
		cEqualiseLineDivisions		= 2048,
		cFillCursorArea				= 4096,
		cLeaveCursorHighlighted     = 8192, 
		cCursorSound				= 16384,
		cAutoStartBlitPad			= 32768,
		cAutoStartIE				= 65536,
		cAutoStartOutlook			= 131072,
		cAutoStartWord				= 262144
    }	cCursorConfigurations;

	typedef enum StatisticType {
		cWordCount = 1,
		cElapsedTime = 2, 
		cReadTime = 3
	}	cStatisticTypes;

	typedef enum SettingType {
		cPauseAt = 1,
		cDelayAt = 2,
		cHTMLTags = 3, 
	}	cSettingTypes;

	// The state machine enumerator 
	typedef enum eSTATE {
		e_NONE = 0,
		e_LOADINGDATA = 1,
		e_DATALOADED = 2, 
		e_DISPLAYING = 3,
		e_MOVINGSCROLLBAR = 4, 
		e_RUNNING = 5,
		e_PAUSED = 6,
		e_SETTINGS = 7
	}	eSTATE;	
	

#endif