
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