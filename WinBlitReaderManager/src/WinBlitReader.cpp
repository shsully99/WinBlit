//***************************************************************************
//*
//*		Name		: WinBlitReader.cpp
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
//*		The WinBlitReader object - implements IWinBlitReader methods and 
//*		handles windows messages. Implements WinBlit's state machine 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/

#include "stdafx.h"
#include "WinBlitReaderManager.h"
#include "WinBlitReader.h"
#include "htmlhelp.h"
#include "Reg.h"
#include "PAKVal.h"
#include "Speed.h" 
#include "About.h"
#include "Dialogmap.h"


/////////////////////////////////////////////////////////////////////////////
// CWinBlitReader

HWND GetWindowTop (HWND hWnd); 

CWinBlitReader::CWinBlitReader ()
{
	m_bWindowOnly = true;
	m_iTrackBarPos = 0;
	m_iAppLic =     999999; 
	m_iControlLic = 500000;
	m_bRepaintControls = TRUE; 
	m_hWndHelp = NULL; 
	m_SpeedRect.left   = 0;
	m_SpeedRect.right  = 0;
	m_SpeedRect.top    = 0;
	m_SpeedRect.bottom = 0;
	m_lDemoMode = 0;
	m_lStartup = 0; 
	m_bShowSpeedOnStatusBar = true; 
}

/////////////////////////////////////////////////////////////////////////////
//
//	WinBlit Properties = All properties are stored in the WinBlit Properties object 
//	which is a member of ours so forward all calls there 
//
/////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitReader::get_Cursor			(long *pVal)		{return m_WinBlitProperties.get_Cursor(pVal);	}
STDMETHODIMP CWinBlitReader::put_Cursor			(long newVal)		{return m_WinBlitProperties.put_Cursor(newVal);}
STDMETHODIMP CWinBlitReader::get_CursorWidth		(long *pVal)		{return m_WinBlitProperties.get_CursorWidth(pVal);}
STDMETHODIMP CWinBlitReader::put_CursorWidth		(long newVal)		{return m_WinBlitProperties.put_CursorWidth(newVal);}
STDMETHODIMP CWinBlitReader::get_CursorHeight	(long *pVal)		{return m_WinBlitProperties.get_CursorHeight(pVal);}
STDMETHODIMP CWinBlitReader::put_CursorHeight	(long newVal)		{return m_WinBlitProperties.put_CursorHeight(newVal);}
STDMETHODIMP CWinBlitReader::get_BaseTime		(long *pVal)		{return m_WinBlitProperties.get_BaseTime(pVal);}
STDMETHODIMP CWinBlitReader::put_BaseTime		(long newVal)		
{
	HRESULT hr = m_WinBlitProperties.put_BaseTime(newVal);
	// Tell text window the property has changed 
	if (S_OK == hr && m_eState >= e_DISPLAYING) m_TextWindow.SetupTimePeriods(); 
	return hr; 
}
STDMETHODIMP CWinBlitReader::get_HighlightPeriod	(long *pVal)		{return m_WinBlitProperties.get_HighlightPeriod(pVal);}
STDMETHODIMP CWinBlitReader::put_HighlightPeriod	(long newVal)		
{
	HRESULT hr = m_WinBlitProperties.put_HighlightPeriod(newVal);
	// Tell text window the property has changed 
	if (S_OK == hr && m_eState >= e_DISPLAYING) m_TextWindow.SetupTimePeriods(); 
	return hr; 
}
STDMETHODIMP CWinBlitReader::get_Settings		(IDispatch **pVal)	{return m_WinBlitProperties.get_Settings(pVal);}
STDMETHODIMP CWinBlitReader::get_Top				(long *pVal)		{return m_WinBlitProperties.get_Top(pVal);}
STDMETHODIMP CWinBlitReader::put_Top				(long newVal)		{return m_WinBlitProperties.put_Top(newVal);}
STDMETHODIMP CWinBlitReader::get_Bottom			(long *pVal)		{return m_WinBlitProperties.get_Bottom(pVal);}
STDMETHODIMP CWinBlitReader::put_Bottom			(long newVal)		{return m_WinBlitProperties.put_Bottom(newVal);}
STDMETHODIMP CWinBlitReader::get_Right			(long *pVal)		{return m_WinBlitProperties.get_Right(pVal);}
STDMETHODIMP CWinBlitReader::put_Right			(long newVal)		{return m_WinBlitProperties.put_Right(newVal);}
STDMETHODIMP CWinBlitReader::get_Left			(long *pVal)		{return m_WinBlitProperties.get_Left(pVal);}
STDMETHODIMP CWinBlitReader::put_Left			(long newVal)		{return m_WinBlitProperties.put_Left(newVal);}
STDMETHODIMP CWinBlitReader::get_ScreenTextColor	(OLE_COLOR *pVal)	{return m_WinBlitProperties.get_ScreenTextColor(pVal);}
STDMETHODIMP CWinBlitReader::put_ScreenTextColor	(OLE_COLOR newVal)	{return m_WinBlitProperties.put_ScreenTextColor(newVal);}
STDMETHODIMP CWinBlitReader::get_TextFont		(IFontDisp** ppFont){return m_WinBlitProperties.get_TextFont(ppFont);}
STDMETHODIMP CWinBlitReader::put_TextFont		(IFontDisp* pFont)	{return m_WinBlitProperties.put_TextFont(pFont);}
STDMETHODIMP CWinBlitReader::get_ScreenFillColor	(OLE_COLOR *pVal)	{return m_WinBlitProperties.get_ScreenFillColor(pVal);}
STDMETHODIMP CWinBlitReader::put_ScreenFillColor	(OLE_COLOR newVal)	{return m_WinBlitProperties.put_ScreenFillColor(newVal);}
STDMETHODIMP CWinBlitReader::get_ScreenBackColor	(OLE_COLOR *pVal)	{return m_WinBlitProperties.get_ScreenBackColor(pVal);}
STDMETHODIMP CWinBlitReader::put_ScreenBackColor	(OLE_COLOR newVal)	{return m_WinBlitProperties.put_ScreenBackColor(newVal);}
STDMETHODIMP CWinBlitReader::get_CursorTextColor	(OLE_COLOR *pVal)	{return m_WinBlitProperties.get_CursorTextColor(pVal);}
STDMETHODIMP CWinBlitReader::put_CursorTextColor	(OLE_COLOR newVal)	{return m_WinBlitProperties.put_CursorTextColor(newVal);}
STDMETHODIMP CWinBlitReader::get_CursorFillColor	(OLE_COLOR *pVal)	{return m_WinBlitProperties.get_CursorFillColor(pVal);}
STDMETHODIMP CWinBlitReader::put_CursorFillColor	(OLE_COLOR newVal)	{return m_WinBlitProperties.put_CursorFillColor(newVal);}
STDMETHODIMP CWinBlitReader::get_DisplayPeriod	(long *pVal)		{return m_WinBlitProperties.get_DisplayPeriod(pVal);}
STDMETHODIMP CWinBlitReader::put_DisplayPeriod	(long newVal)		
{
	HRESULT hr = m_WinBlitProperties.put_DisplayPeriod(newVal);
	// Tell text window the property has changed 
	if (S_OK == hr && m_eState >= e_DISPLAYING) m_TextWindow.SetupTimePeriods(); 
	return hr; 
}
STDMETHODIMP CWinBlitReader::get_BlackoutPeriod	(long *pVal)		{return m_WinBlitProperties.get_BlackoutPeriod(pVal);}
STDMETHODIMP CWinBlitReader::put_BlackoutPeriod	(long newVal)		
{
	HRESULT hr = m_WinBlitProperties.put_BlackoutPeriod(newVal);
	// Tell text window the property has changed 
	if (S_OK == hr && m_eState >= e_DISPLAYING) m_TextWindow.SetupTimePeriods(); 
	return hr; 
}
STDMETHODIMP CWinBlitReader::get_Statistics		(IDispatch **pVal)	{return m_TextWindow.get_Statistics(pVal);}
STDMETHODIMP CWinBlitReader::get_Description		(BSTR *pVal)		{return m_WinBlitProperties.get_Description  (pVal);}
STDMETHODIMP CWinBlitReader::put_Description		(BSTR newVal)		{return m_WinBlitProperties.put_Description	(newVal);}
STDMETHODIMP CWinBlitReader::get_TemplateID		(BSTR *pVal)		{return m_WinBlitProperties.get_TemplateID   (pVal);}
STDMETHODIMP CWinBlitReader::put_TemplateID		(BSTR newVal)		{return m_WinBlitProperties.put_TemplateID   (newVal);}
STDMETHODIMP CWinBlitReader::get_SDKMode			(BOOL *pVal)		{return m_WinBlitProperties.get_SDKMode		(pVal);}
STDMETHODIMP CWinBlitReader::put_SDKMode			(BOOL newVal)		{return m_WinBlitProperties.put_SDKMode		(newVal);}

STDMETHODIMP CWinBlitReader::put_DemoMode ( long newVal)
{
	ATL_TRACE0(e_LOGFLOW, "... Chabging demo mode"); 
	m_lDemoMode = newVal; 
	return S_OK;
}

STDMETHODIMP CWinBlitReader::get_DemoMode (/*[out, retval]*/ long* lVal)
{
	*lVal = m_lDemoMode;
	return S_OK;
}

STDMETHODIMP CWinBlitReader::ShowControls(BOOL bShowControls)
{
	m_WinBlitProperties.put_ShowControls(bShowControls);
	return S_OK;
}

STDMETHODIMP CWinBlitReader::ShowStatusBar(BOOL bShowStatusBar)
{
	m_WinBlitProperties.put_ShowStatusBar(bShowStatusBar);
	return S_OK;
}

STDMETHODIMP CWinBlitReader::ShowTrackBar(BOOL bShowTrackbar )
{
	m_WinBlitProperties.put_ShowTrackBar( bShowTrackbar);
	return S_OK;
}
STDMETHODIMP CWinBlitReader::ShowMetafile(BOOL bMetafile)
{
	ATL_TRACE0 (e_LOGFLOW, "\n CWinBlitReader::ShowMetafile"); 
	// Only show metafile for  static cursors.
	if (!(cRSVPCursor & m_WinBlitProperties.Cursor())
		&& bMetafile)
	{
		return E_INVALIDARG; 
	}
	m_WinBlitProperties.put_ShowMetafile (bMetafile);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////////////
//
//		PRIVATE METHODS 
//
/////////////////////////////////////////////////////////////////////////////////////

//===========================================================================
//
//	Method :		ChangeState 
//
//	Description :	Change state machine to new state 		
//
//	Returns :		True if state change was successful 
//
//===========================================================================

bool CWinBlitReader::ChangeState(eSTATE newState,			
								long lDataSourceType , 
								CComVariant varDataSource)
{
	bool bSuccess = false;

	eSTATE ePreviousState = m_eState;

	if (m_eState != newState)
	{
		// Load data
		if ( (m_eState == e_NONE || m_eState == e_LOADINGDATA) && newState == e_DATALOADED)
		{	
			if (e_NONE == m_eState)
			{
				m_eState = e_LOADINGDATA;
				UpdateStatusBar(); 
			}
			if (0 == m_TextWindow.LoadData(static_cast<eDATASOURCETYPE>(lDataSourceType),varDataSource))
			{
				m_eState = e_DATALOADED;
				m_varDataSource = varDataSource;
				m_eDataSourceType = static_cast<eDATASOURCETYPE> (lDataSourceType);
				bSuccess = true;
				m_eState = e_DATALOADED; 
			}
			else 
			{
				m_eState = e_NONE;
				UpdateStatusBar(); 
			}
		}
		// Informational state change - loading data 
		else if (m_eState == e_NONE && newState == e_LOADINGDATA)
		{
			m_eState = e_LOADINGDATA;
			bSuccess = true;
		}
		// Informational state change - no data loaded 
		else if (m_eState == e_LOADINGDATA && newState == e_NONE)
		{
			m_eState = e_NONE;
			bSuccess = true;
		}
		// Display data 
		else if  (m_eState == e_DATALOADED && newState == e_DISPLAYING)
		{
			if (m_TextWindow.Display(0) != 0) 
			{
				m_bDisplayRequired = true;
			}
			else
			{
				// Draw 
				m_eState = e_DISPLAYING;

				if (m_WinBlitProperties.ShowTrackBar())
				{
					m_iTrackBarPos = m_TextWindow.GetCurrentPercentage(); 
					m_TrackBar.SetRangeMin(m_iTrackBarPos, TRUE);
					m_TrackBar.SetPos(m_iTrackBarPos); 
					m_TrackBar.SetRangeMax (ciTrackMax);
					m_TrackBar.SetPageSize(50);
				}
			}
			bSuccess = true;
		}
		// Moving scrollbar 
		else if (m_eState == e_DISPLAYING  && newState == e_MOVINGSCROLLBAR)
		{
			m_eState = e_MOVINGSCROLLBAR;
			bSuccess = true;
		}
		else if (m_eState == e_MOVINGSCROLLBAR && newState == e_DISPLAYING)
		{
			m_eState = e_DISPLAYING;
			bSuccess = true;
		}
 		// Start or Pause
		else if  (m_eState == e_DISPLAYING && newState == e_RUNNING)
		{
			m_eState = e_RUNNING;
			m_TextWindow.ResetBlits();
			StartTimer(0);
			bSuccess = true;
		}
		// Pause toggle while running 
		else if  (m_eState == e_RUNNING  &&	 newState == e_PAUSED)
		{
			m_eState = e_PAUSED;
			StopTimer(0);
			bSuccess = true;
		}
		// Pause toggle while paused 
		else if	(m_eState == e_PAUSED	&&   newState == e_RUNNING)
		{
			// Reset text window
			m_eState = e_RUNNING;
			StartTimer(1); 
			bSuccess = true;
		}
		// Stop
		else if  (	(m_eState == e_RUNNING || m_eState == e_PAUSED)
					&& newState == e_DISPLAYING)
		{
			m_eState = e_DISPLAYING;
			StopTimer(1); 
			bSuccess = true;
		}
		// Unload Data 
		else if  (	(m_eState == e_DATALOADED || m_eState == e_DISPLAYING)
					&& newState == e_NONE)
		{
			m_TextWindow.UnLoadData(); 
			m_eState = e_NONE;
			bSuccess = true;
		}
	}

	if (bSuccess && m_eState != ePreviousState)
	{
		if (m_WinBlitProperties.ShowStatusBar()) 
		{
			if (m_eState != e_NONE) UpdateStatusBar(); 
		}
		if (e_RUNNING == m_eState)					// We have just started running 
		{			
			m_ToolBar.EnableButton(ID_STARTBUTTON,	FALSE);
			m_ToolBar.EnableButton(ID_STOPBUTTON,	TRUE);
			m_ToolBar.EnableButton(ID_PAUSEBUTTON,	TRUE);
			m_ToolBar.EnableButton(ID_SETTINGS,		FALSE);
			m_ToolBar.EnableButton(ID_SPEED,		FALSE);
			m_ToolBar.EnableButton(ID_REGISTER,		FALSE);
			m_ToolBar.EnableButton(ID_SWITCHCONFIG,	FALSE);
			m_TrackBar.EnableWindow(FALSE); 
		}
		else if (e_PAUSED == m_eState)					// We have just paused
		{			
			m_ToolBar.EnableButton(ID_STARTBUTTON,	FALSE);
			m_ToolBar.EnableButton(ID_STOPBUTTON,	TRUE);
			m_ToolBar.EnableButton(ID_PAUSEBUTTON,	TRUE);
			m_ToolBar.EnableButton(ID_SETTINGS,		TRUE);
			m_ToolBar.EnableButton(ID_SPEED,		TRUE);
			m_ToolBar.EnableButton(ID_REGISTER,		TRUE);
			m_ToolBar.EnableButton(ID_SWITCHCONFIG,	TRUE);
			m_TrackBar.EnableWindow(FALSE); 
		}
		else if (m_ToolBar.IsWindow()) 
		{
			m_ToolBar.EnableButton(ID_STARTBUTTON,	TRUE);
			m_ToolBar.EnableButton(ID_PAUSEBUTTON,	FALSE);
			m_ToolBar.EnableButton(ID_SETTINGS,		TRUE);
			m_ToolBar.EnableButton(ID_SPEED,		TRUE);
			m_ToolBar.EnableButton(ID_REGISTER,		TRUE);
			m_ToolBar.EnableButton(ID_SWITCHCONFIG,	TRUE);
			m_TrackBar.EnableWindow(TRUE); 
		}
	}

	return bSuccess;
}

//===========================================================================
//
//	Method :		OnTimer 
//
//	Description :	Called periodically by the timer to move the cursor 
//					along 
//
//	Returns :		0
//
//===========================================================================

LRESULT CWinBlitReader::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// Poke the text window object and it can 
	// decide if it needs to redisplay the timer. 
	int iRet = m_TextWindow.TickTock();

	// Keep drawing window until the window can draw no more (iRet = -1)
	if (-1 == iRet )
	{
		if (1 == m_lDemoMode )
		{
			// If in demo mode then kill the timer
			ChangeState(e_DISPLAYING);
		}
		else 
		{
			// Flip the page
			if (m_TextWindow.Display(6, 1) == -1)
			{
				// If a pause condition was encountered then kill the timer
				ChangeState(e_DISPLAYING);
			}
			else 
			{
				// If flipping page then clear speed display and show word rate 
				// instead 
				m_bShowSpeedOnStatusBar = false; 
				// Update the statistics on the status bar.
				if (m_WinBlitProperties.ShowStatusBar()) UpdateStatusBar(true); 
			}

			if (m_WinBlitProperties.ShowTrackBar())
			{
				m_iTrackBarPos  = m_TextWindow.GetCurrentPercentage();
				m_TrackBar.SetPos(m_iTrackBarPos);
			}
		}
	}
	else if (-2 == iRet)
	{
		ChangeState(e_PAUSED);
	}	
	return 0;
}

//===========================================================================
//
//	Method :		StartTimer 
//
//	Description :	Kick off the windows timer 
//
//	Returns :		void 
//
//===========================================================================

void CWinBlitReader::StartTimer(int iType)
{
	// Tell text window object to get ready to flash cursors
	m_TextWindow.OnBeforeTimerStart(iType);

	SetTimer(1,33);
	m_dwTickCount = GetTickCount();
}

//===========================================================================
//
//	Method :		StopTimer 
//
//	Description :	Kill off the windows timer 
//
//	Returns :		void 
//
//===========================================================================

void CWinBlitReader::StopTimer(int iType)
{
	ATL_TRACE0 (e_LOGFLOW, "\n CWinBlitReader::StopTimer"); 
	if (m_hWnd)
	{
		KillTimer(1);
	}
	// Tell Text Window it is all over 
	m_TextWindow.OnAfterTimerStop(iType);
}


///////////////////////////////////////////////////////////////////////////////////
//
//			NAVIGATION PUBLIC METHODS 
//
///////////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitReader::LineUp(long Lines)
{
	if (m_eState == e_DISPLAYING)
	{
		m_TextWindow.Display(2, Lines);	
		return S_OK; 	
	}
	else
	{
		return E_INVALIDARG;
	}
}

STDMETHODIMP CWinBlitReader::LineDown(long Lines )
{
	if (m_eState == e_DISPLAYING && eUnLicensed != m_iAppLic)
	{
		m_TextWindow.Display(3, Lines);
		return S_OK; 	
	}
	else
	{
		return E_INVALIDARG;
	}
}

STDMETHODIMP CWinBlitReader::PageUp(long Pages)
{
	if (m_eState == e_DISPLAYING)
	{
		m_TextWindow.Display(4, Pages);	
		return S_OK; 	
	}
	else
	{
		return E_INVALIDARG;
	}
}	

STDMETHODIMP CWinBlitReader::PageDown(long Pages)
{	
	if (m_eState == e_DISPLAYING && m_iAppLic != 0)
	{
		m_TextWindow.Display(5, Pages);
		return S_OK; 	
	}
	else
	{
		return E_INVALIDARG;
	}
}
	
///////////////////////////////////////////////////////////////////////////////////
//
//		PUBLIC METHODS WHICH CHANGE THE STATE MACHINE
//
///////////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWinBlitReader::LoadData(long lDataSourceType, VARIANT varDataSource)
{	
	ATL_TRACE1 (e_LOGFLOW, "\n CWinBlitReader::LoadData %d",lDataSourceType); 

	m_iCallingApp = 0;
	if (lDataSourceType > 100000)
	{
		m_iCallingApp  = (lDataSourceType / 100000) * 100000;
		lDataSourceType = lDataSourceType % 100000; 
	}

	m_iAppLic = lDataSourceType / 1000;
	lDataSourceType = lDataSourceType % 1000; 

	if (0 == m_lStartup && 0 == m_lDemoMode)
	{
		ShowHelp(3);
	}

	// Dummy call from WinBlitPad to update the status bar for loading data 
	if (lDataSourceType == e_INFO_LOADINGDATA )
	{
		ChangeState(e_LOADINGDATA); 
		return S_OK; 
	}
	else if (lDataSourceType == e_INFO_NONE )
	{
		ChangeState(e_NONE); 
		return S_OK; 
	}

	if (eUnknownLicenseWord == m_iAppLic)
	{
		// Called from Word to ask us what our license is. 
		CPAKVal PAKVal; 
		m_iAppLic = PAKVal.Val(eWinBlitWord, ciLatestVersion ); 
	}

	if ( eUnLicensed == m_iAppLic) 
	{
		// Enable register button
		m_ToolBar.HideButton(ID_REGISTER, FALSE); 
		m_ToolBar.EnableButton(ID_REGISTER, TRUE); 
		m_ToolBar.EnableButton(ID_STARTBUTTON,	FALSE);
		m_ToolBar.EnableButton(ID_STOPBUTTON,	FALSE);
		m_ToolBar.EnableButton(ID_PAUSEBUTTON,	FALSE);
		m_ToolBar.EnableButton(ID_SETTINGS,		FALSE);					
		return S_OK; 
	}
	else if (eBetaLicense == m_iAppLic || eTrialLicense == m_iAppLic)
	{
		// Enable register button
		m_ToolBar.HideButton(ID_REGISTER, FALSE); 
		m_ToolBar.EnableButton(ID_REGISTER, TRUE); 
	}

	// If in demo mode 2 hide and disable the help button and the register
	// button

	if (2 == m_lDemoMode)
	{
		// Enable register button
		m_ToolBar.EnableButton (ID_REGISTER,FALSE);
		m_ToolBar.EnableButton (ID_HELPCALLED,FALSE);
	}

	if (lDataSourceType < 0 || lDataSourceType > 7)	return E_INVALIDARG;
	else if (varDataSource.vt == VT_EMPTY)  return E_INVALIDARG;
	else if (varDataSource.vt == VT_BSTR && !varDataSource.bstrVal)  return E_INVALIDARG;

	if (!ChangeState(e_DATALOADED, lDataSourceType, varDataSource))
	{
		return E_INVALIDARG;
	}
	return S_OK; 
}

STDMETHODIMP CWinBlitReader::Display()
{
	if (500000 == m_iControlLic)
	{
		CPAKVal PAKVal;
		m_iControlLic = PAKVal.Val(eWinBlitControl, ciLatestVersion); 
		if (m_iControlLic < m_iAppLic)
		{
			m_iAppLic = m_iControlLic;
		}
	}

	if ( eUnLicensed == m_iAppLic || eOldLicense == m_iAppLic) 
	{
		// Enable register button
		m_ToolBar.HideButton(ID_REGISTER, FALSE); 
		m_ToolBar.EnableButton(ID_REGISTER, TRUE); 
		m_ToolBar.EnableButton(ID_STARTBUTTON,	FALSE);
		m_ToolBar.EnableButton(ID_STOPBUTTON,	FALSE);
		m_ToolBar.EnableButton(ID_PAUSEBUTTON,	FALSE);
		m_ToolBar.EnableButton(ID_SETTINGS,		FALSE);		

		TCHAR szReg[512];
		TCHAR szErr[50];

		if ( eUnLicensed == m_iAppLic)
		{
			::LoadString(_Module.m_hInst, IDS_MBXREG, szReg, 512);
			::LoadString(_Module.m_hInst, IDS_MBXERROR, szErr, 50);
		}
		else
		{
			::LoadString(_Module.m_hInst, IDS_MBXNEWFULL, szReg, 512);
			::LoadString(_Module.m_hInst, IDS_MBXERROR, szErr, 50);
		}

		MessageBox (szReg, szErr); 

		return S_OK; 
	}
	else if (eBetaLicense  == m_iAppLic		|| 
			 eTrialLicense == m_iAppLic)
	{
		// Enable register button
		m_ToolBar.HideButton(ID_REGISTER, FALSE); 
		m_ToolBar.EnableButton(ID_REGISTER, TRUE); 
	}

	if (!ChangeState(e_DISPLAYING))
	{
		return E_INVALIDARG;
	}
	RECT rc; 
	::GetClientRect (m_hWnd, &rc); 
	UpdateControls(rc); 

	CComBSTR bstrDemoPath(*m_WinBlitProperties.DemoPath());
	if (0 == m_lStartup && bstrDemoPath && 0 == m_lDemoMode)
	{
		USES_CONVERSION; 
		HtmlHelp(GetDesktopWindow(), OLE2T(bstrDemoPath), HH_DISPLAY_TOPIC, 0);
	}
	else
	{
		if (!m_bDisplayRequired)
		{
			CheckAutoStart();
		}
	}


	return S_OK;
}

STDMETHODIMP CWinBlitReader::Start()
{
	if (lLogLevel == -1)
	{
		IUnknown *pUnk;
		CLSID clsLogApp;
		CLSIDFromProgID(L"ATLLogApp.BlitLog.1", &clsLogApp);
		if (SUCCEEDED(GetActiveObject(clsLogApp,  NULL,  (IUnknown**)&pUnk)))
		{
			m_Log = pUnk;
			if (m_Log) m_Log->get_Level(&lLogLevel);
			ATL_TRACE0(e_LOGFLOW," Started logging in WinBlitPad"); 
		}
	}
	if (eUnLicensed == m_iAppLic ||  
		false == ChangeState(e_RUNNING))
	{
		return E_INVALIDARG;
	}
	return S_OK;
}	

STDMETHODIMP CWinBlitReader::Pause()
{	
	eSTATE newState; 
	if (m_eState == e_PAUSED)
	{
		newState = e_RUNNING;
	}
	else if (m_eState == e_RUNNING)
	{
		newState =  e_PAUSED;
	}
	else
	{
		return E_INVALIDARG;
	}
	
	if (!ChangeState(newState))
	{
		return E_INVALIDARG;
	}
	return S_OK;
}

STDMETHODIMP CWinBlitReader::UnloadData()
{
	if (!ChangeState(e_NONE))
	{
		return E_INVALIDARG;
	}
	else
	{
		return S_OK;
	}
}

STDMETHODIMP CWinBlitReader::Stop()
{
	HRESULT hr(S_OK); 
	// If we are running then 
	if (m_eState == e_RUNNING || m_eState == e_PAUSED) 
	{
		if (!ChangeState(e_DISPLAYING)) 
		{
			hr = E_INVALIDARG;
		}

	}
	else if (m_eState == e_DISPLAYING)
	{
		ChangeTrackBarPos(ciTrackMin);
	}
	else 
	{
		hr = E_INVALIDARG;
	}

	return hr;
}

STDMETHODIMP CWinBlitReader::Register()
{
	if ( eUnLicensed == m_iAppLic		||
	     eBetaLicense  == m_iAppLic		|| 
		 eTrialLicense == m_iAppLic)
	{
		CReg Reg(*m_WinBlitProperties.HelpPath());
		eSTATE eOldState = m_eState; 
		m_eState = e_SETTINGS; 
		Reg.DoModal(m_hWnd);
		m_eState = eOldState; 
	}
	return S_OK; 
}

STDMETHODIMP CWinBlitReader::ShowAbout()
{
	AboutBox(); 
	return S_OK;
}


//////////////////////////////////////////////////////////////////////////////////
//
//			STANDARD ATL METHODS 
//
//////////////////////////////////////////////////////////////////////////////////

//===========================================================================
//
//	Method :		OnCreate
//
//	Description :	Called by container to allow WinBlitReader to initialise it
//					Creates toolbar, trackbar and initialises accelerators.
//
//	Returns :		0
//
//===========================================================================

LRESULT CWinBlitReader::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	if (lLogLevel == -1)
	{
		IUnknown *pUnk;
		CLSID clsLogApp;
		CLSIDFromProgID(L"ATLLogApp.BlitLog.1", &clsLogApp);
		if (SUCCEEDED(GetActiveObject(clsLogApp,  NULL,  (IUnknown**)&pUnk)))
		{
			m_Log = pUnk;
			if (m_Log) m_Log->get_Level(&lLogLevel);
		}
	}

	ATL_TRACE0 (e_LOGFLOW,"\n CWinBlitReader::OnCreate ");
	AtlAxWinInit();

	RECT rc;
	::GetClientRect(m_hWnd, &rc);

	// Show the control bar
	RECT rcControls;

	rcControls.bottom = 13;
	HWND hWndToolBar = m_ToolBar.Create	(m_hWnd, 
										rcControls,
										NULL,
										WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_TABSTOP | TBSTYLE_TOOLTIPS);
	

	m_ToolBar.m_hWnd = hWndToolBar; 
	m_ToolBar.SetButtonStructSize(); 

	TBBUTTON tbb[11]; 

	int iA = m_ToolBar.AddBitmap(1, IDR_TOOLBAR);

	// Fill the TBBUTTON array with button information, and add the 
	// buttons to the toolbar. 
	tbb[0].iBitmap = iA; 
	tbb[0].idCommand = ID_STARTBUTTON; 
	tbb[0].fsState = TBSTATE_ENABLED; 
	tbb[0].fsStyle = TBSTYLE_BUTTON; 
 	tbb[0].dwData = 0; 
	tbb[0].iString = 0; 

	tbb[1].iBitmap = iA+1; 
	tbb[1].idCommand = ID_PAUSEBUTTON; 
	tbb[1].fsState = TBSTATE_ENABLED; 
	tbb[1].fsStyle = TBSTYLE_BUTTON; 
	tbb[1].dwData = 0; 
	tbb[1].iString = 0; 

	tbb[2].iBitmap = iA+2;
	tbb[2].idCommand = ID_STOPBUTTON;
	tbb[2].fsState = TBSTATE_ENABLED; 
	tbb[2].fsStyle = TBSTYLE_BUTTON; 
	tbb[2].dwData = 0; 
	tbb[2].iString = 0;

	tbb[3].iBitmap = iA+3;
	tbb[3].idCommand = ID_SPEED;
	tbb[3].fsState = TBSTATE_ENABLED; 
	tbb[3].fsStyle = TBSTYLE_BUTTON; 
	tbb[3].dwData = 0; 
	tbb[3].iString = 0;

	tbb[4].iBitmap = 8;
	tbb[4].idCommand = 0;
	tbb[4].fsState = 0;
	tbb[4].fsStyle = TBSTYLE_SEP;
	tbb[4].dwData = 0;
	tbb[4].iString = 0;

	tbb[5].iBitmap = iA+4;
	tbb[5].idCommand = ID_SETTINGS;
	tbb[5].fsState = TBSTATE_ENABLED; 
	tbb[5].fsStyle = TBSTYLE_BUTTON; 
	tbb[5].dwData = 0; 
	tbb[5].iString = 0;

	tbb[6].iBitmap = iA+5;
	tbb[6].idCommand = ID_SWITCHCONFIG;
	tbb[6].fsState = TBSTATE_ENABLED; 
	tbb[6].fsStyle = TBSTYLE_DROPDOWN ; 
	tbb[6].dwData = 0; 
	tbb[6].iString = 0;

	tbb[7].iBitmap = 8;
	tbb[7].idCommand = 0;
	tbb[7].fsState = 0;
	tbb[7].fsStyle = TBSTYLE_SEP;
	tbb[7].dwData = 0;
	tbb[7].iString = 0;

	tbb[8].iBitmap = iA+6;
	tbb[8].idCommand = ID_HELPCALLED;
	tbb[8].fsState = TBSTATE_ENABLED; 
	tbb[8].fsStyle = TBSTYLE_BUTTON; 
	tbb[8].dwData = 0; 
	tbb[8].iString = 0;

	tbb[9].iBitmap = 8;
	tbb[9].idCommand = 0;
	tbb[9].fsState = 0;
	tbb[9].fsStyle = TBSTYLE_SEP;
	tbb[9].dwData = 0;
	tbb[9].iString = 0;

	tbb[10].iBitmap = iA+7;
	tbb[10].idCommand = ID_REGISTER;
	tbb[10].fsState = TBSTATE_HIDDEN; 
	tbb[10].fsStyle = TBSTYLE_BUTTON; 
	tbb[10].dwData = 0; 
	tbb[10].iString = 0;

	int NUM_BUTTONS = 11;

	m_ToolBar.AddButtons(NUM_BUTTONS, &tbb[0]);
	
	// Create the trackbar 
	RECT rcTrackbar = rc;
	//if (m_WinBlitProperties.ShowMetafile())
	//{
	//	rcTrackbar.top = ((rcTrackbar.bottom -rcTrackbar.top) / 2) - 10; 
	//}
	//else
	//{
		rcTrackbar.top = rcTrackbar.bottom - 20;
	//}

	m_TrackBar.Create (this, 1, m_hWnd, &rcTrackbar, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_TABSTOP | TBSTYLE_TOOLTIPS | TBS_NOTICKS | TBS_BOTH, 0, 101);
	/*HWND hWndToolBar = m_TrackBar.Create
										(m_hWnd, 
										rcTrackbar,
										NULL,
										WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | TBSTYLE_TOOLTIPS | TBS_NOTICKS | TBS_BOTH);*/
	//m_TrackBar.m_hWnd = hWndToolBar; 
	m_TrackBar.SetTicFreq  (ciTrackFreq);
	m_TrackBar.SetRangeMin (ciTrackMin);
	m_TrackBar.SetRangeMax (ciTrackMax);
	m_iTrackBarPos = 0;
	
	m_hAccel = LoadAccelerators(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_TOOLBAR));

	m_hWndStatusBar = ::CreateStatusWindow(SBT_TOOLTIPS | WS_CHILD ,
											NULL, 
											m_hWnd, 
											ATL_IDW_STATUS_BAR);
	m_sbar.SubclassWindow(m_hWndStatusBar);

	int arrParts[] =	{ID_DEFAULT_PANE, ID_WORDSPERMINUTE, ID_TOTALWORDS, ID_READTIME};

	m_sbar.SetPanes(arrParts, sizeof(arrParts) / sizeof(int), false);	

	if (m_WinBlitProperties.ShowStatusBar()) UpdateStatusBar (e_NONE); 

	// Just in case we have a sleepy container - poke it to repaint us 
	// when we are ready
	InvalidateRect(NULL); 

	if (lLogLevel == -1)
	{
		IUnknown *pUnk;
		CLSID clsLogApp;
		CLSIDFromProgID(L"ATLLogApp.BlitLog.1", &clsLogApp);
		if (SUCCEEDED(GetActiveObject(clsLogApp,  NULL,  (IUnknown**)&pUnk)))
		{
			m_Log = pUnk;
			if (m_Log) m_Log->get_Level(&lLogLevel);
		}
	}

	return 0; 
}

//===========================================================================
//
//	Method :		OnDraw
//
//	Description :	Called by container to ask us to repaint ourselves. 
//					At the moment it always repaints the entire screen
//					and makes a dangerous assumption that the DC is normalised. 
//					in the input ATL_DRAWINFO parameter which is not the 
//					case in some DTC containers (e.g. Visual Interdev).
//
//	Returns :		0
//
//===========================================================================

HRESULT CWinBlitReader::OnDraw(ATL_DRAWINFO& di)
{
	ATL_TRACE0 (e_LOGFLOW,"\n CWinBlitReader::OnDraw");
	RECT& rc = *(RECT*)di.prcBounds;
	
	ATL_TRACE4 (e_LOGFLOW,"\n Our rect top %d left %d bottom right %d %d  ", rc.top, rc.left, rc.bottom, rc.right);
	ATL_TRACE1 (e_LOGFLOW," Redisplay required  %d ", m_bDisplayRequired); 

	// Sometimes  container call us a bit to early (i.e. they do not have 
	// a rectangle)
	if (rc.right == 0 || rc.bottom == 0) return S_OK;
	if (rc.right - rc.left <= 0 || NULL == m_hWnd) return S_OK;

	m_TextWindow.SetWindow(m_hWnd); 
	m_TextWindow.SetRect(rc); 

	// Do not redraw while settings dialog box is up 
	if (e_SETTINGS == m_eState)
	{
	}
	else if (m_bDisplayRequired == true)
	{
		// Display failed previously due to lack of a window - try it again 
		ChangeState(e_DISPLAYING); 		
		m_bDisplayRequired = false; 

		// AutoStart if required 
		CheckAutoStart();
	}
	else if (e_RUNNING == m_eState)
	{
		// If timer is runnung tell text window to redisplay itself
		// on its next display.
		m_TextWindow.ReDisplayOnTimer();
	}
	else if (e_DATALOADED <= m_eState)
	{
		// Move trackbar out of the way 
		if (m_WinBlitProperties.ShowTrackBar() && m_TrackBar.m_hWnd) 
		{
			m_TrackBar.MoveWindow(0,0,0,0,FALSE); 
		}

		// Redisplay page 		
		m_TextWindow.Display (1);
	}
	else
	{
		// Move trackbar out of the way 
		// Move trackbar out of the way 
		if (m_WinBlitProperties.ShowTrackBar() && m_TrackBar.m_hWnd) 
		{
			m_TrackBar.MoveWindow(0,0,0,0,FALSE); 
		}

		// Display banner page
		m_TextWindow.Display (-1);
	}

	// Show the controls if we need to
	UpdateControls(rc); 

	return S_OK;
}

void CWinBlitReader::FinalRelease()
{
	// Uninitialise text window. 
	m_TextWindow.Uninitialise();
	m_vecSettings.clear(); 
}

HRESULT CWinBlitReader::FinalConstruct()
{
	if (lLogLevel == -1)
	{
		IUnknown *pUnk;
		CLSID clsLogApp;
		CLSIDFromProgID(L"ATLLogApp.BlitLog.1", &clsLogApp);
		if (SUCCEEDED(GetActiveObject(clsLogApp,  NULL,  (IUnknown**)&pUnk)))
		{
			m_Log = pUnk;
			if (m_Log) m_Log->get_Level(&lLogLevel);
		}
	}

	m_bDisplayRequired = false;
	m_eState = e_NONE; 

	ATL_TRACE0(e_LOGDETAIL, "CWinBlitReader::FinalConstruct()"); 
	if ( 0 == LoadSettingsArray())
	{
		// Initialse text window, 
		m_TextWindow.Initialise(&m_WinBlitProperties, this); 
		m_lStartup = m_WinBlitRegistry.GetStartupFlag();
	}

	ATL_TRACE0(e_LOGDETAIL, "CWinBlitReader::FinalConstruct returns "); 

	return S_OK; 
}

int  CWinBlitReader::LoadSettingsArray()
{
	int iRet = 0;

	// Load registry properties 
	m_vecSettings.clear();
	m_WinBlitRegistry.GetAllSettings(m_vecSettings); 
	if (m_vecSettings.size() > 0) 
	{
		wstring wstrDefaultName; 
		CComBSTR bstrDefault;
		if (0 != m_WinBlitRegistry.GetDefaultName(wstrDefaultName))
		{
			// If no default set up then use the first setting in the registry 
			m_WinBlitRegistry.SetDefaultName(m_vecSettings[0].m_wstrName);
			bstrDefault = (m_vecSettings[0].m_wstrName).c_str(); 
		}
		else 
		{
			bstrDefault = wstrDefaultName.c_str(); 
		}

		m_WinBlitRegistry.LoadSettings(bstrDefault,	&m_WinBlitProperties);

	}
	else
	{
		iRet = -1;
	}
	return iRet; 
}

//===========================================================================
//
//	Method :		LoadSettings
//
//	Description :	Set up the properties for WinBlit from the registry 
//
//	Returns :		S_FALSE
//
//===========================================================================

STDMETHODIMP CWinBlitReader::LoadSettings(BSTR bstrKey, long lType)
{
	m_WinBlitRegistry.LoadSettings(bstrKey, &m_WinBlitProperties, lType);
	if (bstrKey)
	{
		wstring wstr(bstrKey);
		m_WinBlitRegistry.SetDefaultName(wstr); 
	}
	if (m_eState >= e_DISPLAYING)
	{
		m_TextWindow.Display(0); 
	}
	else
	{
		m_TextWindow.Display(-1); 
	}

	return S_OK;
}

//===========================================================================
//
//	Method :		SaveSettings
//
//	Description :	Save WinBlit properties to the registry
//
//	Returns :		S_FALSE
//
//===========================================================================

STDMETHODIMP CWinBlitReader::SaveSettings(BSTR bstrKey, long lType)
{
	m_WinBlitRegistry.SaveSettings(bstrKey, &m_WinBlitProperties, lType);
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////
//
//			WINDOWS MESSAGE HANDLERS 
//
//////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP  CWinBlitReader::TranslateAccelerator ( LPMSG pMsg )
{
	ATL_TRACE2 (e_LOGDETAIL,"\n CWinBlitReader::TranslateAccelerator %0x %0x",pMsg->message, pMsg->wParam);
	HRESULT hr = S_FALSE; 
	if (!m_WinBlitProperties.SDKMode())
	{
		if (::TranslateAccelerator(m_hWnd,m_hAccel, pMsg)) hr = S_OK;
	}
	return hr;
}
				
LRESULT CWinBlitReader::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{			
	ATL_TRACE1 (e_LOGDETAIL,"\n CWinBlitReader::OnKillFocus - Window %d", (HWND) wParam);
	//ATL_TRACE2 (e_LOGDETAIL," \n %d %d ", m_hWnd, m_TrackBar.m_hWnd);
		
	// Our top-level window 
	HWND hWndOurParent = GetWindowTop(m_hWnd); 
	
	// Top level window of help screen 
	HWND hWndHelpParent = NULL; 
	if (::IsWindow(m_hWndHelp))
	{
		hWndHelpParent = GetWindowTop(m_hWndHelp); 
	}	
	// Top level window of whatever now has focus 
	HWND hNewWindowParent = GetWindowTop((HWND) wParam); 
		
	// Assume we are losing focus
	bool bKillFocus = true; 

	if (hWndOurParent)
	{
		if (hWndOurParent  == hNewWindowParent) bKillFocus = false; 
	}

	if (hWndHelpParent)
	{
		if (hWndHelpParent == hNewWindowParent ) bKillFocus = false; 
	}
	//if (m_eState != e_SETTINGS) bKillFocus = false; 

	/*if (true == bKillFocus)
	{	
		// Tell our parent we have lost focus if the new window with focus 
		// is not owned by us or our ancestors. 
		HWND hWnd = ::GetParent(m_hWnd); 
		::SendMessage(hWnd,uMsg, wParam, lParam);
		ATL_TRACE0 (e_LOGDETAIL," Lost focus");
	}*/	
		
	return 0;
}

LRESULT CWinBlitReader::OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATL_TRACE1 (e_LOGFLOW,"\n CWinBlitReader::OnSetFocus - Window %d", (HWND) wParam);
	ATL_TRACE2 (e_LOGFLOW," %d %d ", m_hWnd, m_TrackBar.m_hWnd);
	HWND hWnd = ::GetParent(m_hWnd); 

	::SendMessage(hWnd,uMsg, wParam, lParam);
	return S_OK;
}

LRESULT CWinBlitReader::OnKillFocusTrackBar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATL_TRACE1 (e_LOGFLOW,"\n CWinBlitReader::OnKillFocusTrackBar %d", wParam);
	ATL_TRACE2 (e_LOGFLOW," %d %d ", m_hWnd, m_TrackBar.m_hWnd);
	// We have lost focus - check our parent window and if it does
	// not have focus then pass the message to our container. 
	if (GetFocus() != m_hWnd)
	{
		HWND hWnd = ::GetParent(m_hWnd); 
		::SendMessage(hWnd,uMsg, wParam, lParam);
		ATL_TRACE0 (e_LOGDETAIL, "\n Sending killfocus to parent  ");
	}
	else
	{
		ATL_TRACE0 (e_LOGDETAIL, "\n Main window has focus ");
		bHandled = true; 
	}
	return S_OK;
}
LRESULT CWinBlitReader::OnSetFocusTrackBar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATL_TRACE1 (e_LOGDETAIL,"\n CWinBlitReader::OnSetFocusTrackBar %d", wParam);
	ATL_TRACE2 (e_LOGDETAIL," %d %d ", m_hWnd, m_TrackBar.m_hWnd);
	return S_OK;
}

LRESULT CWinBlitReader::OnMouseActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATL_TRACE0 (e_LOGDETAIL,"\n CWinBlitReader::OnMouseActivate ");
	HWND hWnd = ::GetParent(m_hWnd); 
	::SendMessage(hWnd, 7, wParam, lParam);
	return 0;
}

LRESULT CWinBlitReader::OnHelpCalled(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATL_TRACE0  (e_LOGDETAIL, "\n CWinBlitReader::OnHelp");
	ShowHelp(1); 
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
//
//			TOOLBAR AND MENU FUNCTIONS 
//
//////////////////////////////////////////////////////////////////////////////////

LRESULT CWinBlitReader::OnConfigurationChanged (unsigned int ,unsigned int nID,struct HWND__ *,int &)
{
	vector<CSettingStrings>::iterator vit = m_vecSettings.begin(); 
	INT iA = ID_CONFIG_ID_START-1;
	while (vit != m_vecSettings.end() && iA < nID)
	{
		iA++;
		if (iA != nID) vit++;
	}

	if (iA == nID)
	{
		wstring wstrName(vit->m_wstrName);
		if (0 != wstrName.compare((*m_WinBlitProperties.Name())))
		{
			m_WinBlitRegistry.SetDefaultName(wstrName); 
			m_WinBlitRegistry.LoadSettings(NULL, &m_WinBlitProperties);
			if (m_eState >= e_DISPLAYING)
			{
				m_TextWindow.Display(0); 
			}
			else
			{
				m_TextWindow.Display(-1); 
			}
		}
	}

	return 0;
}


LRESULT CWinBlitReader::OnCommandRangeHandler(unsigned int iA ,unsigned int nID,struct HWND__ *,int &)
{
	switch(nID)
	{
	case ID_STARTBUTTON: 
		{
			Start(); 
		}
		break;
	case ID_PAUSEBUTTON:
		{
			Pause(); 
		}
		break;
	case ID_STOPBUTTON:
		{
			Stop(); 
		}
		break;

	case ID_STARTSTOPTOGGLE:
		{
			if (e_RUNNING == m_eState || e_PAUSED == m_eState)
			{
				Stop();
			}
			else if (e_DISPLAYING == m_eState)
			{
				Start();
			}
		}
		break;

	case ID_SETTINGS:
		{
			// Do not allow while running 
			if ( e_RUNNING == m_eState) break;
			
			/*ATL_TRACE ("\n CWinBlitReader::OnSettings"); 
			CPropDialog PropDialog; 
			PropDialog.DoModal(); */

			CWinBlitPropertySheet prop;
			
			eSTATE eOldState = m_eState; 
			prop.Initialise(m_lDemoMode); 
			m_eState = e_SETTINGS; 
			int iRet = prop.DoModal(m_hWnd);
			m_eState = eOldState; 

			// If any changes made on property sheets then reload. 
			if (IDOK == iRet || true == prop.WasDirty())
			{
				LoadSettingsArray();
				if (m_eState >= e_DISPLAYING)
				{
					m_TextWindow.Display(0); 
				}
				else
				{
					m_TextWindow.Display(-1); 
				}
			}
			if (prop.m_bClearStatsRequired)
			{
				m_bShowSpeedOnStatusBar = true;
				m_TextWindow.m_pStatistics->Reset(); 
				if (m_WinBlitProperties.ShowStatusBar()) UpdateStatusBar (); 
				prop.m_bClearStatsRequired = false; 
			}
		}
		break;
	case ID_SHOWTRACKBAR:
		{
			if (m_WinBlitProperties.ShowTrackBar()) 
			{
				m_WinBlitProperties.put_ShowTrackBar(FALSE); 
				m_TrackBar.ShowWindow(FALSE); 
			}
			else
			{
				m_WinBlitProperties.put_ShowTrackBar(TRUE); 
				m_TrackBar.ShowWindow(TRUE); 
			}
			// Force our client to redisplay us.
			RECT rc;
			GetClientRect(&rc);
			InvalidateRect(&rc);
			// Save to registry 
			SaveSettings(*(m_WinBlitProperties.Name()), 0);
		}
		break;

	case ID_SHOWCONTROLS:
		{
			if (m_WinBlitProperties.ShowControls()) 
			{
				m_WinBlitProperties.put_ShowControls(FALSE); 
			}
			else
			{
				m_WinBlitProperties.put_ShowControls(TRUE); 
			}
			RECT rc;
			// Force a redisplay 
			GetClientRect(&rc);
			m_bRepaintControls = TRUE;
			InvalidateRect(&rc);
			SaveSettings(*(m_WinBlitProperties.Name()), 0);
		}
		break;

	case ID_SHOWMETAFILE:
		{
			if (m_WinBlitProperties.ShowMetafile()) 
			{
				m_WinBlitProperties.put_ShowMetafile(FALSE); 
			}
			else
			{
				m_WinBlitProperties.put_ShowMetafile(TRUE); 
			}
			RECT rc;
			GetClientRect(&rc);
			InvalidateRect(&rc);
			SaveSettings(*(m_WinBlitProperties.Name()), 0);
		}		
		break;

	case ID_SHOWSTATUSBAR:
		{
			if (m_WinBlitProperties.ShowStatusBar()) 
			{
				m_WinBlitProperties.put_ShowStatusBar(FALSE); 
				//m_ToolBar.ShowWindow(FALSE); 
			}
			else
			{
				m_WinBlitProperties.put_ShowStatusBar(TRUE); 
				//m_ToolBar.ShowWindow(TRUE); 
			}
			RECT rc;
			// Force a redisplay 
			GetClientRect(&rc);
			InvalidateRect(&rc);
			SaveSettings(*(m_WinBlitProperties.Name()), 0);
		}
		break;

	case ID_CLEARSTATISTICS:
		{
			m_bShowSpeedOnStatusBar = true;
			m_TextWindow.m_pStatistics->Reset(); 
			if (m_WinBlitProperties.ShowStatusBar()) UpdateStatusBar (); 
		}
		break;

	case ID_HELPCALLED:
		{
			ShowHelp(1); 
		}
		break;

	case ID_REGISTER:
		{
			Register();		
		}
		break;
	case ID_TOP:
		{
			ChangeTrackBarPos(ciTrackMin);
		}
		break;
	case ID_BOTTOM:
		{
			ChangeTrackBarPos(ciTrackMax);
		}
		break;
	case ID_FASTER:
		{
			if (m_eState != e_RUNNING)
			{
				// Increase speed by one fixation per minute 
				long lBase = m_WinBlitProperties.BaseTime();
				long lFixations = 60000 / lBase;

				if (lFixations < ciSpeedMax)
				{	
					lFixations++; 
					m_bShowSpeedOnStatusBar = true; 
					m_WinBlitProperties.put_BaseTime(60000/lFixations); 
					SaveSettings(*(m_WinBlitProperties.Name()), 0);
					UpdateStatusBar(); 

					// Tell text window the property has changed 
					if (m_eState >= e_DISPLAYING) m_TextWindow.SetupTimePeriods(); 							
				}
			}
		}
		break;

	case ID_SLOWER:
		{
			if (m_eState != e_RUNNING)
			{
				// Increase speed by one fixation per minute 
				long lBase = m_WinBlitProperties.BaseTime();
				long lFixations = 60000 / lBase;

				// Find the next fixation period 

				bool bNextFixation = false; 
				while (false == bNextFixation && lFixations > ciSpeedMin)
				{
					lFixations--; 

					if (60000/ ( 60000/lFixations) != 60000 / lBase) bNextFixation = true;
				}
				
				if (bNextFixation)
				{	
					lFixations--; 
					m_bShowSpeedOnStatusBar = true; 
					m_WinBlitProperties.put_BaseTime(60000/lFixations); 
					SaveSettings(*(m_WinBlitProperties.Name()), 0);

					// Tell text window the property has changed 
					if (m_eState >= e_DISPLAYING) m_TextWindow.SetupTimePeriods(); 

					UpdateStatusBar(); 

				}
			}
		}
		break;

	case ID_SPEED:
		{
			CComBSTR bstrHelpPath(*m_WinBlitProperties.HelpPath());
			if (2 == m_lDemoMode)
			{
				bstrHelpPath = "";
			}

			CSpeed Speed(m_WinBlitProperties.BaseTime(), 
						 bstrHelpPath,
						 m_SpeedRect); 

			// Set state to setting so that kill focus does not kill off WinBlit
			eSTATE eOldState = m_eState; 
			m_eState = e_SETTINGS;

			// Show speed dialog box 
			long lBase = (long) Speed.DoModal(m_hWnd); 

			// Restore old state 
			m_eState = eOldState;

			if (IDCANCEL != lBase)
			{
				m_WinBlitProperties.put_BaseTime(lBase); 
				SaveSettings(*(m_WinBlitProperties.Name()), 0);

				// Tell text window the property has changed 
				if (m_eState >= e_DISPLAYING) m_TextWindow.SetupTimePeriods(); 

			}
			// Save position of Speed rectangle 
			Speed.GetRect(&m_SpeedRect);

			m_bShowSpeedOnStatusBar = true; 
			// Update Statusbar to show 
			UpdateStatusBar(true); 

		}
		break;

	case ID_PAGEUP:
		{
			if (SUCCEEDED(PageUp(1)))
			{
				if (m_WinBlitProperties.ShowTrackBar())
				{
					m_iTrackBarPos  = m_TextWindow.GetCurrentPercentage();
					m_TrackBar.SetPos(m_iTrackBarPos);
				}
			}
		}
		break;

	case ID_LINEDOWN:
		{
			if (SUCCEEDED(LineDown(1)))
			{
				if (m_WinBlitProperties.ShowTrackBar())
				{
					m_iTrackBarPos  = m_TextWindow.GetCurrentPercentage();
					m_TrackBar.SetPos(m_iTrackBarPos);
				}
			}
		}
		break;

	case ID_LINEUP:
		{
			if (SUCCEEDED(LineUp(1)))
			{
				if (m_WinBlitProperties.ShowTrackBar())
				{
					m_iTrackBarPos  = m_TextWindow.GetCurrentPercentage();
					m_TrackBar.SetPos(m_iTrackBarPos);
				}
			}
		}
		break;

	case ID_PAGEDOWN:
		{
			if (SUCCEEDED(PageDown(1)))
			{
				if (m_WinBlitProperties.ShowTrackBar())
				{
					m_iTrackBarPos  = m_TextWindow.GetCurrentPercentage();
					m_TrackBar.SetPos(m_iTrackBarPos);
				}
			}
		}
		break;

	case ID_ABOUT_BOX:
		{
			// Show application about box 
			AboutBox(); 			
		}
		break;
	
	default:
		break;
	
	}
	return 0; 
}

LRESULT  CWinBlitReader::OnToolbarDropDown(WPARAM wParam, LPNMHDR pnmh, BOOL&)
{
	ATL_TRACE0  (e_LOGDETAIL, "\n CWinBlitReader::OnToolbarDropDown");

	RECT      rc;
	HMENU     hPopupMenu = NULL;
	BOOL      bRet = FALSE;

	m_ToolBar.GetRect(ID_SWITCHCONFIG, &rc); 
    m_ToolBar.MapWindowPoints(HWND_DESKTOP, &rc); 

	CMenu menuContext;
	menuContext.CreateMenu(); 

	CMenu menuConfig;
	menuConfig.CreateMenu(); 
	SetupConfigMenu(menuConfig);

	menuContext.AppendMenu(MF_POPUP,(UINT_PTR) menuConfig.m_hMenu, "C&onfigurations"); 

	CMenuHandle menuHandlePopup(menuContext.GetSubMenu(0));

	menuHandlePopup.TrackPopupMenuEx(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL,               
            rc.left, rc.bottom, m_hWnd, NULL); 
	
	return 0;
}


LRESULT  CWinBlitReader::OnToolbarNeedText(WPARAM, LPNMHDR pnmh, BOOL&)
{
	LPTOOLTIPTEXT lpToolTipText = (LPTOOLTIPTEXT)pnmh;
	static TCHAR szBuf[128];

	// Get the string with the same ID as the button from the resource
	LoadString(_Module.GetResourceInstance(),
		lpToolTipText->hdr.idFrom,
		szBuf, sizeof(szBuf) * sizeof(TCHAR));
	lpToolTipText->lpszText = szBuf;

	return 0;
}


LRESULT  CWinBlitReader::OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATL_TRACE0 (e_LOGDETAIL,"\n CWinBlitReader::OnContextMenu");
	// No context menu if in SDK 
	if (m_WinBlitProperties.SDKMode()) return 0; 

	CMenu menuContext;
	menuContext.LoadMenu(IDR_CONTEXTMENU);
	
	if (m_WinBlitProperties.ShowTrackBar()) 
	{
		menuContext.CheckMenuItem(ID_SHOWTRACKBAR, MF_CHECKED); 
	}
	else 
	{
		menuContext.CheckMenuItem(ID_SHOWTRACKBAR, MF_UNCHECKED); 
	}
	if (m_WinBlitProperties.ShowControls()) 
	{
		menuContext.CheckMenuItem(ID_SHOWCONTROLS, MF_CHECKED); 
	}
	else 
	{
		menuContext.CheckMenuItem(ID_SHOWCONTROLS, MF_UNCHECKED); 
	}
	if (m_WinBlitProperties.ShowStatusBar()) 
	{
		menuContext.CheckMenuItem(ID_SHOWSTATUSBAR, MF_CHECKED); 
	}
	else 
	{
		menuContext.CheckMenuItem(ID_SHOWSTATUSBAR, MF_UNCHECKED); 
	}

	if (m_WinBlitProperties.Cursor() & cRSVPCursor)
	{
		if (m_WinBlitProperties.ShowMetafile()) 
		{
			menuContext.CheckMenuItem(ID_SHOWMETAFILE, MF_CHECKED); 
		}
		else 
		{
			menuContext.CheckMenuItem(ID_SHOWMETAFILE,  MF_UNCHECKED); 
		}
	}
	else 
	{
		menuContext.EnableMenuItem(ID_SHOWMETAFILE,  MF_GRAYED); 	
	}
	
	// Disallow Settings and start when running
	if (eUnLicensed == m_iAppLic )
	{
		menuContext.EnableMenuItem(ID_STARTSTOPTOGGLE,	MF_GRAYED); 	
		menuContext.EnableMenuItem(ID_CLEARSTATISTICS,	MF_GRAYED); 	
		menuContext.EnableMenuItem(ID_PAUSEBUTTON,		MF_GRAYED); 	
		menuContext.EnableMenuItem(ID_STOPBUTTON,		MF_GRAYED); 	
	}
	else if (e_RUNNING == m_eState)
	{	
		menuContext.EnableMenuItem(ID_REGISTER,			MF_GRAYED); 	
		menuContext.EnableMenuItem(ID_SPEED,			MF_GRAYED); 	
		menuContext.EnableMenuItem(ID_SETTINGS,			MF_GRAYED); 	
		menuContext.EnableMenuItem(ID_ABOUT_BOX,		MF_GRAYED); 	
		menuContext.EnableMenuItem(ID_SWITCHCONFIG,		MF_GRAYED); 	
		menuContext.EnableMenuItem(ID_CLEARSTATISTICS,	MF_GRAYED); 	
		menuContext.EnableMenuItem(ID_SHOWCONTROLS,		MF_GRAYED); 	
		menuContext.EnableMenuItem(ID_SHOWTRACKBAR,		MF_GRAYED); 
		menuContext.EnableMenuItem(ID_SHOWSTATUSBAR,	MF_GRAYED); 	
		menuContext.EnableMenuItem(ID_SHOWMETAFILE,		MF_GRAYED); 	
		menuContext.EnableMenuItem(ID_CLEARSTATISTICS,	MF_GRAYED); 	
	}	
	else if (e_PAUSED == m_eState)
	{	
		menuContext.EnableMenuItem(ID_CLEARSTATISTICS,	MF_GRAYED); 	
	}	
	else
	{	
		menuContext.EnableMenuItem(ID_PAUSEBUTTON,		MF_GRAYED); 	
	}
	
	CMenu menuConfig;
	
	menuConfig.CreateMenu();
	SetupConfigMenu (menuConfig); 

	::AppendMenu( menuContext.GetSubMenu(0), MF_POPUP,(UINT_PTR) menuConfig.m_hMenu, "C&onfigurations"); 

	CMenuHandle menuPopup(menuContext.GetSubMenu(0));
	menuPopup.TrackPopupMenu(TPM_RIGHTBUTTON,LOWORD (lParam), HIWORD (lParam),m_hWnd);

	return 0;
}

LRESULT CWinBlitReader::OnHScrollTrackBar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATL_TRACE3  (e_LOGDETAIL,"\n CWinBlitReader::OnHScrollTrackBar %d %d %d ", uMsg, wParam, lParam);

	// Ignore if unlicensed 
	if (m_iAppLic == eUnLicensed) return 0;

	// Todo - must disable trackbar when running or paused. 
	if (m_TrackBar.m_hWnd == (HWND) lParam && m_eState == e_DISPLAYING)
	{
		// Tell the text window to move to a new position, 
		if (LOWORD (wParam) == TB_ENDTRACK)
		{
			ChangeState(e_MOVINGSCROLLBAR);

			ChangeTrackBarPos(m_TrackBar.GetPos());

			ChangeState(e_DISPLAYING); 
		}
	}		
	return 0;
}

void CWinBlitReader::ChangeTrackBarPos(int iTrackBarPos)
{
	ATL_TRACE2 (e_LOGFLOW, "\n CWinBlitReader::ChangeTrackBarPos New  %d Current %d ", iTrackBarPos , m_iTrackBarPos); 

	if ( m_TrackBar.m_hWnd  && 
		(m_eState == e_DISPLAYING || m_eState == e_MOVINGSCROLLBAR))
	{
		if (iTrackBarPos > m_iTrackBarPos)
		{
			m_TextWindow.Display(7, iTrackBarPos); 
		}
		else if (iTrackBarPos < m_iTrackBarPos)
		{
			m_TextWindow.Display(7, 0-iTrackBarPos); 
		}
		m_iTrackBarPos  = m_TextWindow.GetCurrentPercentage();
		m_TrackBar.SetPos (m_iTrackBarPos); 
	}
}
//===========================================================================
//
//	Method :		UpdateControls
//
//	Description :	Displays toolbar controls and trackbar
//
//	Returns :		S_FALSE
//
//===========================================================================

void CWinBlitReader::UpdateControls(RECT rc)
{
	ATL_TRACE3  (e_LOGDETAIL,"\n UpdateControls %d %d %d", rc.top, rc.left, rc.right); 

	if (m_WinBlitProperties.ShowControls())
	{
		if (m_bRepaintControls)
		{
			m_ToolBar.ShowWindow(TRUE); 
		}

		::MoveWindow(m_ToolBar.m_hWnd, rc.left, rc.top, rc.right-rc.left, ciToolBarHeight, m_bRepaintControls);
		m_bRepaintControls = FALSE;
	}
	else 
	{
		// Showing control 
		m_ToolBar.ShowWindow(FALSE); 
	}

	if (m_WinBlitProperties.ShowTrackBar())
	{
		if (m_WinBlitProperties.ShowStatusBar())
		{
			RECT rcTemp; 
			::GetClientRect(m_hWndStatusBar, &rcTemp);
			rc.bottom = rc.bottom - rcTemp.bottom - rcTemp.top - 1;
		}
		// Showing trackbar
		//if (m_WinBlitProperties.ShowMetafile() && m_eState >= e_DISPLAYING)
		//{
		//	::MoveWindow(m_TrackBar.m_hWnd, rc.left, rc.top + ((rc.bottom  - rc.top) / 2) - ciTrackBarHeight, rc.right-rc.left, ciTrackBarHeight, false);
		//}
		//else
		//{
			::MoveWindow(m_TrackBar.m_hWnd, rc.left, rc.bottom - ciTrackBarHeight, rc.right-rc.left, ciTrackBarHeight, false);
		//}
	}
	else 
	{
		m_TrackBar.ShowWindow(FALSE); 
	}

	if (m_WinBlitProperties.ShowStatusBar())
	{
		::ShowWindow(m_sbar.m_hWnd,TRUE); 
		::SendMessage(m_hWndStatusBar, WM_SIZE, 0, 0);
	}
	else
	{
		::ShowWindow(m_sbar.m_hWnd,FALSE); 
	}
}

//===========================================================================
//
//	Method :		UpdateStatusBar
//
//	Description :	Displays Status bar 
//
//	Returns :		void
//
//===========================================================================

void CWinBlitReader::UpdateStatusBar(bool bUpdateStatistics)
{
	TCHAR szBuff[100];
	if (m_sbar.m_hWnd)
	{
		wsprintf(szBuff, _T("%s"), pszSTATEString [m_eState]);
		m_sbar.SetPaneText(ID_DEFAULT_PANE, szBuff);

		if (m_bShowSpeedOnStatusBar)
		{
			// If we have just changed the speed then 
			// show the new speed in the second panel.
			long lFpm = 60000 / m_WinBlitProperties.BaseTime();  
			wsprintf(szBuff, _T("Fixations per minute: %d  "), lFpm);
			m_sbar.SetPaneText(ID_WORDSPERMINUTE, szBuff);
		}

		if (bUpdateStatistics || m_eState == e_DISPLAYING)
		{
			long lReadTime,lWordCount;
			m_TextWindow.GetCurrentStatistics (lReadTime, lWordCount);
			wsprintf(szBuff, _T("Time (secs) : %d         "),	lReadTime/1000);
			m_sbar.SetPaneText(ID_READTIME, szBuff);
			wsprintf(szBuff, _T("Words : %d         "), lWordCount);
			m_sbar.SetPaneText(ID_TOTALWORDS, szBuff);

			// If not showing speed in 2nd pane show numbers of words 
			if (!m_bShowSpeedOnStatusBar)
			{
				// Show words per minute in the second panel.
				if (lWordCount > 0 && lReadTime > 10000)
				{
					long lSPW = lReadTime / lWordCount;
					if (lSPW > 0)
					{
						long lWpm = 60000 / lSPW;  
						wsprintf(szBuff, _T("Words per minute: %d      "), lWpm);
						m_sbar.SetPaneText(ID_WORDSPERMINUTE, szBuff);
					}
				}
			}
		}
	}
}

//===========================================================================
//					
//	Method :		ShowHelp
//												 lHelpType												
//												 ---------
//		
//	Description :	Shows help,						(1)
//					demo,							(2)
//					startup tips or					(3)
//					contact information				(4)
//						
//	Returns :		
//
//===========================================================================

STDMETHODIMP CWinBlitReader::ShowHelp(long lHelpType)
{
	USES_CONVERSION; 
	if (4 == lHelpType)
	{
		CComBSTR bstrHelpPath; 
		bstrHelpPath.Append(*(m_WinBlitProperties.HelpPath()));
		bstrHelpPath.Append(cawchContact); 

		::HtmlHelp(    NULL,      NULL,       HH_CLOSE_ALL,   0) ;
		::HtmlHelp(m_hWnd, OLE2T(bstrHelpPath), HH_DISPLAY_TOPIC, 0);
	}
	else if (2 != m_lDemoMode && 1 == lHelpType)
	{
		CComBSTR bstrPath; 
		bstrPath.Append(*(m_WinBlitProperties.HelpPath()));
		//bstrPath.Append(m_WinBlitProperties.m_bstrHelpStartPage);
		if (2 == m_WinBlitProperties.HelpType())
		{
			eSTATE eOldState = m_eState; 
			m_eState = e_SETTINGS; 
			HtmlHelp(    NULL,      NULL,       HH_CLOSE_ALL,   0) ;
			m_hWndHelp = ::HtmlHelp(m_hWnd, OLE2T(bstrPath), HH_DISPLAY_TOPIC , 0);
			m_eState = eOldState; 
		}
		else 
		{
			WinHelp(OLE2T(bstrPath), HELP_FINDER, 0L); 
		}
	}
	// Show demo 
	else if (2 == lHelpType)
	{
		CComBSTR bstrDemoPath(*m_WinBlitProperties.DemoPath());
		if (bstrDemoPath)
		{
			HtmlHelp(m_hWnd, OLE2T(bstrDemoPath), HH_DISPLAY_TOPIC, 0);
		}
	}
	// Show demo if it has not been shown yet. 
	else if (3 == lHelpType && 0 == m_lStartup && 0 == m_lDemoMode)
	{
		m_lStartup = 2; 
		CComBSTR bstrDemoPath(*m_WinBlitProperties.DemoPath());
		if (bstrDemoPath)
		{
			HtmlHelp(m_hWnd, OLE2T(bstrDemoPath), HH_DISPLAY_TOPIC, 0);
		}
		m_WinBlitRegistry.SetStartupFlag(2); 
	}
	return S_OK;
}

//===========================================================================
//
//	Method :		SetupConfigMenu
//
//	Description :	For a givenm menu reference set up of the Config names 
//
//	Returns :		void
//
//===========================================================================

void CWinBlitReader::SetupConfigMenu(CMenu& menuConfig)
{
	vector<CSettingStrings>::iterator vit = m_vecSettings.begin(); 
	int iA = ID_CONFIG_ID_START;
	USES_CONVERSION; 
	ATL_TRACE1  (e_LOGDETAIL,"\n CWinBlitReader::SetupConfigMenu %s ",OLE2T(*(m_WinBlitProperties.Name())));
	for (; vit != m_vecSettings.end(); vit++)
	{
		ATL_TRACE1 (e_LOGDETAIL, " \n %s ",OLE2T((vit->m_wstrName).c_str()));

		if ( 0 == vit->m_wstrName.compare(*(m_WinBlitProperties.Name())))
		{
			menuConfig.AppendMenu(MF_STRING | MF_CHECKED, iA, OLE2T((vit->m_wstrName).c_str())); 
		}
		else
		{
			menuConfig.AppendMenu(MF_STRING , iA, OLE2T((vit->m_wstrName).c_str())); 
	
		}
		iA++;
	} 
}

void CWinBlitReader::AboutBox()
{
	CAbout About;
	eSTATE eOldState = m_eState; 
	m_eState = e_SETTINGS; 
	int iA = About.DoModal(m_hWnd);
	m_eState = eOldState; 
}

//===========================================================================
//
//	Method :		GetWindowTop
//
//	Description :	For a given window find the top-level owned window.
//
//	Returns :		Top level window
//
//===========================================================================

HWND GetWindowTop (HWND hWnd)
{
	HWND hWndTemp = hWnd;
	while (hWnd != NULL)
	{
		hWnd = GetParent(hWndTemp); 
		if (hWnd)
		{
			hWndTemp = hWnd;
		}
	}
	return hWndTemp;
}

BOOL CWinBlitLicense::VerifyLicenseKey(BSTR bstrkey)
{
	ATL_TRACE0 (e_LOGDETAIL, "CWinBlitLicense::VerifyLicenseKey");
	/*USES_CONVERSION;
	// Run Time License Check
    return !lstrcmp(OLE2T(bstrkey), _T("YourLicenceKey"));*/
	return FALSE; 
}

BOOL CWinBlitLicense::GetLicenseKey(DWORD dwRes,	BSTR* pbstrKey)
{
	ATL_TRACE0 (e_LOGDETAIL, "CWinBlitLicense::GetLicenseKey");
	/*USES_CONVERSION;	  
	// Developer Tool (such as LPK_Tool) requests runtime License
    *pbstrKey = SysAllocString( T2OLE(_T("YourLicenceKey"))); */
    return FALSE; 
}

BOOL CWinBlitLicense::IsLicenseValid() 
{
	ATL_TRACE0 (e_LOGDETAIL, "CWinBlitLicense::IsLicenseValid");
	// Very simple test to see if SpindleCtrl.lic exists!
	// If it exists, allow designtime usage
	//return GetFileAttributes("C:\\SpindleCtrl.lic")==(DWORD)-1 
	//		? FALSE : TRUE;
	return TRUE; 
}

STDMETHODIMP CWinBlitReader::get_State(long *pVal)
{
	*pVal = m_eState; 
	return S_OK;
}

void CWinBlitReader::CheckAutoStart()
{
	// Autostart if required in the confoig for the calling application
	bool bAutoStart = false;
	if		( m_iCallingApp == eCalledfromBlitPad && 
			 (m_WinBlitProperties.Cursor() & cAutoStartBlitPad))
	{
		bAutoStart = true;
	}
	else if (m_iCallingApp == eCalledfromExchange && 
			 (m_WinBlitProperties.Cursor() & cAutoStartOutlook))
	{
		bAutoStart = true;
	}
	else if (m_iCallingApp == eCalledfromWebBand && 
			 (m_WinBlitProperties.Cursor() & cAutoStartIE))
	{
		bAutoStart = true;
	}
	else if (m_iCallingApp == eCalledfromWord && 
			 (m_WinBlitProperties.Cursor() & cAutoStartWord))
	{
		bAutoStart = true;
	}

	if (bAutoStart)
	{
		Start(); 
	}
}
