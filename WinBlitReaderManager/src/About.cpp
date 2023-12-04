//***************************************************************************
//*
//*		Name		: About.cpp
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
//*		implementation of about box 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/
// About.cpp: implementation of the About Box.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "About.h"
#include <windowsx.h>

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

static void  DisplayExecutableVersionInfo (HWND hwnd);

static const TCHAR szValueNameBase [] = TEXT("\\StringFileInfo\\040904B0\\") ;
static const TCHAR szProductName []   = TEXT("ProductName") ;

// Number of characters in the base portion of the value name string
#define BASECHARS    (DIM(szValueNameBase) - 1)

#define DIM(a) (sizeof(a)/sizeof(a[0]))

LRESULT CAbout::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CenterWindow();
	DisplayExecutableVersionInfo (m_hWnd);
	return 0;
}

LRESULT CAbout::OnOK(WORD, WORD wID, HWND , BOOL& )
{
	EndDialog(wID);
	return 0;
}

LRESULT CAbout::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}

static void DisplayExecutableVersionInfo (HWND hwnd)
{
	BOOL                bResult ;               // Result of Boolean functions
    DWORD               dwVerInfoSize ;         // Size of version information
    DWORD               dwHandle ;              // Extraneous but required parameter
    HMODULE             hmod ;                  // Application's module handle
    HWND                hwndControl ;           // Control window handle
    LPVOID              pVerInfo ;              // File version info pointer
    LPVOID              pValue ;                // Value from version info
	TCHAR               szFullPath [_MAX_PATH] ;// Application executable path
	TCHAR               szValueName [256] ;     // Name of value to retrieve
    UINT                uLength ;               // Length of retrieved value

    // Get the full path to this server
    hmod = _Module.GetModuleInstance() ;
    ::GetModuleFileName (hmod, szFullPath, DIM(szFullPath)) ;

    // Determine the size buffer needed to store the version information:
    dwVerInfoSize = ::GetFileVersionInfoSize (szFullPath, &dwHandle) ;
    if (0 == dwVerInfoSize)
        return ;

    // Allocate a buffer for the version info block
    pVerInfo = new char [dwVerInfoSize] ;
    ATLASSERT (NULL != pVerInfo) ;
    if (NULL == pVerInfo)
        return ;

    // Read the version info block into the buffer
    ::GetFileVersionInfo (szFullPath, dwHandle, dwVerInfoSize, pVerInfo) ;

    // Build value name base string...
	lstrcpy (szValueName, szValueNameBase) ;
	
	// Build the \StringFileInfo\040904E4\ProductName value name
	lstrcpy (szValueName + BASECHARS, szProductName) ;

	// Retrieve the value
    bResult = ::VerQueryValue (pVerInfo, szValueName, &pValue, &uLength) ;

    // Format the output for the dialog caption
    // Get the current caption then append to it the ProductName value
    GetWindowText (hwnd, szValueName, DIM (szValueName)) ;
	lstrcat (szValueName, reinterpret_cast <LPCTSTR>(pValue)) ;

    // Change the dialog caption - normally "About <ProductName>"
	SetWindowText (hwnd, szValueName) ;

	// For each control in the dialog...
    //  fetch the version info name from the control's initial window text.
    //  retrieve the value with that name,
    //  change the control's window text to the retrieved value.
    // Technique derived from GENERIC.C.

    hwndControl = GetFirstChild (hwnd) ;
    while (NULL != hwndControl) {
        // Build value name base string...
	    lstrcpy (szValueName, szValueNameBase) ;
	
    	// Build the \StringFileInfo\040904E4\<ControlText> value name
        // The Win32 API contains the following predefined version information strings:
        //     CompanyName              LegalCopyright     
        //     FileDescription          OriginalFilename   
        //     FileVersion              ProductName        
        //     InternalName             ProductVersion     
        
        // Get the control's text...
        GetWindowText (hwndControl,
                       szValueName + BASECHARS,
                       DIM(szValueName) - BASECHARS) ;

	    // Retrieve the value
		bResult = ::VerQueryValue (pVerInfo, szValueName, &pValue, &uLength) ;

        // If version information is available and the version information name exists...
        if (bResult)
            // If a value exists for the version information name...
            if (0 != uLength && NULL != pValue)
                // Change the control's text to the version information value
                SetWindowText (hwndControl, reinterpret_cast<LPCTSTR>(pValue)) ;

        hwndControl = GetNextSibling (hwndControl) ;
    }
    // Free the memory for the version information block
    delete [] pVerInfo ;
}