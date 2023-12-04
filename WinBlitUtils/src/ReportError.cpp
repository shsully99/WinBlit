//***************************************************************************
//*
//*		Name		: ReportError.cpp
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
//*		Error reporting implementation
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
#include <stdio.h> 
#include <stdarg.h>
static void  Report_Error (LPCSTR lpszFormat, ...); 

void Report_Error (LPCSTR lpszFormat, ...)
{
	va_list args;
	va_start(args, lpszFormat);

	int nBuf;
	TCHAR szBuffer[512];

	nBuf = _vsnprintf(szBuffer, sizeof(szBuffer) / sizeof(TCHAR), lpszFormat, args);
	va_end(args);

	::MessageBox (GetFocus(), szBuffer, "Error", MB_OK); 
  
	ATL_TRACE0 (3, szBuffer);
}