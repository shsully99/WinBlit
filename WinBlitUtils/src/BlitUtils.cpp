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
//*		Various utilies - dispatch wrapper and file string cracker
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/


#include "stdafx.h"
#include "BlitUtils.h"

BSTR FileString (CComBSTR bstrDataSource)
{
	CComBSTR bstrTemp;
	USES_CONVERSION;
	
	UINT iLength = 0; 
	WCHAR wchBackSlash ('\\');
	
	while (iLength < bstrDataSource.Length())
	{
		if (bstrDataSource[iLength] ==  wchBackSlash)
		{
			bstrTemp.Append (&wchBackSlash,1);
		}
		bstrTemp.Append(&bstrDataSource[iLength],1);
		iLength++;
	}
	return bstrTemp.Detach();
}