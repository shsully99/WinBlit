//***************************************************************************
//*
//*		Name		: WinBlitUtils.cpp
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
//*		Implementation of logging code 
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
long lLogLevel(-1);
ICoLoggerPtr m_Log(NULL);

void MyLog(INT iTemp, LPCSTR lpszFormat, ...)
{
	int i = 1;

	// Output trace for debug 
	va_list args;
	va_start(args, lpszFormat);

	int nBuf;
	char szBuffer[512];

	nBuf = _vsnprintf(szBuffer, sizeof(szBuffer), lpszFormat, args);
	ATLASSERT(nBuf < sizeof(szBuffer)); //Output truncated as it was > sizeof(szBuffer)

	va_end(args);
	USES_CONVERSION; 
	m_Log->Log(iTemp, ::GetCurrentThreadId(), T2OLE(szBuffer)); 
}

