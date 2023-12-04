//***************************************************************************
//*
//*		Name		: WinBlitPadview.cpp
//*							
//*		$Revision:$
//*
//*		Date        : 20-Feb-2002
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
//*		Implementation for CWinBlitPadview
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/
#include "stdafx.h"
#include "WinBlitPadView.h"
#include <atlhost.h>
#include <atldlgs.h>

#include <ExDispID.h>
#include "WinBlitConstants.h"
#include "ReportError.cpp"
#include "WinBlitConstants.h"
#include "WarningDialog.h"
#include "Registry.h"
#include "PakVal.h"


#include <string>
using namespace std;

static const ciMaxWait(30000);

static LPCTSTR strTxt = _T(".txt");
static LPCTSTR strHtm = _T(".htm");
static LPCTSTR strDoc = _T(".doc");

LRESULT CWinBlitPadView::OnFileOpen(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CFileDialog dlg(TRUE, NULL, _T(""), OFN_OVERWRITEPROMPT, lpcstrFilter);
	int nRet = dlg.DoModal();

	if(nRet == IDOK)
	{

	}
	return 0;
}

void CWinBlitPadView::SetLic(int iLic)
{
	m_iLic = iLic;
	// If we dont have a full license then tell WinBlit
	// Todo - this should not be hardcoded. 
	if (m_iLic < 3000)
	{
		CComVariant var; 
		var.vt = VT_EMPTY; 
		m_WinBlitReader->LoadData(m_iLic+1, var);
	}
}

int CWinBlitPadView::GetLic()
{
	return m_iLic; 
}

BOOL CWinBlitPadView::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == 256 && m_wndView) 
	{
		HWND hWnd = m_wndView.m_hWnd;
		return (::SendMessage (hWnd, WM_FORWARDMSG, 0, (LPARAM)pMsg ));
	}
	pMsg;
	return FALSE;
}

// Required to forward messages to the control
BOOL  CWinBlitPadView::PreTranslateAccelerator(MSG* pMsg)
{
	return FALSE; 
}

int CWinBlitPadView::ShowHelp(long lHelpType)
{
	m_WinBlitReader->ShowHelp(lHelpType); 
	return 0; 
}

int CWinBlitPadView::About()
{
	m_WinBlitReader->ShowAbout(); 
	return 0; 
}

void CWinBlitPadView::Register()
{
	m_WinBlitReader->Register(); 
}

////////////////////////////////////////////////////////////////////
//
//	Initialise
//
//
//	Returns  0 = Success
//			-1 = Failure 
//			 1 = Document not opened
//
////////////////////////////////////////////////////////////////////

int CWinBlitPadView::Initialise (LPCTSTR pszDataSource)
{
	ATL_TRACE0 (2, "\n CWinBlitPadView::Initialise"); 
	int iRet = -1; 

	// Put WinBlit into a known state 
	m_WinBlitReader->Stop();
	m_WinBlitReader->UnloadData();
	m_pBrowserWrapper = NULL; 
	CComVariant var(pszDataSource); 

	// Convert string to lowercase prior to determining the extension 
	string strDataSource (pszDataSource);

	// Convert string to lower case. 		
	for(int iA = 0; iA < strDataSource.size(); iA++)
	{
		if (::isupper(strDataSource[iA]))
		{
			strDataSource[iA] = ::tolower(strDataSource[iA]);
		}
	}
	
	if (strDataSource.find(strDoc) != std::string::npos)
	{
		if (!m_bRegWordWarning)
		{
			CWarningDialog dlg(1);
			int iA = dlg.DoModal();
			if (iA < 0)
			{
				CRegistry Reg;
				Reg.SetRootKey(HKEY_CURRENT_USER);
				Reg.SetKey(lpcstrWinBlitPadRegKey , TRUE);	
				Reg.WriteBool("WordWarning", TRUE);
				m_bRegWordWarning = TRUE; 
			}
			if (IDC_WARNING_NO == abs(iA) || 
				IDCANCEL == abs(iA))
			{
				return 1;
			}
		}
	}
	else if (strDataSource.find(strHtm) != std::string::npos)
	{
		if (!m_bRegHTMLWarning)
		{
			CWarningDialog dlg(2);
			int iA = dlg.DoModal();
			if (iA < 0)
			{
				CRegistry Reg;
				Reg.SetRootKey(HKEY_CURRENT_USER);
				Reg.SetKey(lpcstrWinBlitPadRegKey , TRUE);	
				Reg.WriteBool("HTMLWarning", TRUE);
				m_bRegHTMLWarning = TRUE; 
			}
			if (IDC_WARNING_NO == abs(iA) || 
				IDCANCEL == abs(iA))
			{
				return 1;
			}
		}
	}

	
	if ( strDataSource.find("<<paste>>") != std::string::npos)
	{
		char * buffer = NULL;
		//open the clipboard
		if ( OpenClipboard() ) 
		{
			HANDLE hData = GetClipboardData( CF_TEXT );
			char * buffer = (char*) GlobalLock( hData );
			if (buffer)
			{
				int iA = strlen(buffer); 
				USES_CONVERSION; 
				BSTR bstrMem = NULL;
				bstrMem = ::SysAllocStringLen(NULL, iA);
				if (bstrMem)
				{
					int iC = ::SysStringLen(bstrMem);
					for (int iB = 0; iB < iC; iB++)
					{
						bstrMem[iB] = (WCHAR) *(buffer+iB); 
					}
					if (SUCCEEDED(m_WinBlitReader->LoadData(eCalledfromBlitPad + m_iLic + 0, 	CComVariant(bstrMem))))
					{
						if (SUCCEEDED (m_WinBlitReader->Display()))
						{
							m_bInitialised = true; 
							iRet = 0;
						}
					}
					::SysFreeString(bstrMem); 
				}
				GlobalUnlock( hData );
				CloseClipboard();
			}
		}
	}
	/*else if (strDataSource.find(strHtm) != std::string::npos)
	{
		HRESULT hr = S_OK; 
		if (!m_pBrowserWrapper)
		{
			// First time in so co-create the browser wrapper 
			hr = CoCreateInstance(CLSID_BrowserWrapper, NULL, CLSCTX_INPROC_SERVER, IID_IBrowserWrapper,
				       (void**)&m_pBrowserWrapper);
		}

		if (SUCCEEDED(hr))
		{
			// Dummy call to loaddata to update status bar. 
			CComVariant var; 
			var.vt = VT_EMPTY; 
			hr = m_WinBlitReader->LoadData(e_INFO_LOADINGDATA, var); 
			if (SUCCEEDED(hr))
			{
				CComBSTR bstr (pszDataSource);
				
				hr = m_pBrowserWrapper->Run(bstr); 
				if (SUCCEEDED(hr))
				{
					if (::SetTimer(m_hWnd, 1, 50, NULL))
					{
						m_dwTickCount = GetTickCount();
						iRet = 0;
					}
					else
					{
						Report_Error ("System error starting windows timer \n If this problem persists please contact Product Support", GetLastError());
					}
				}
			}
			else 
			{
				Report_Error("System error starting html reader %X \n If this problem persists please contact Product Support", hr);
			}
		}
		else 
		{
			Report_Error("System error starting html reader %X \n If this problem persists please contact Product Support", hr);
		}
	}*/
	else 
	{
		if (SUCCEEDED(m_WinBlitReader->LoadData(eCalledfromBlitPad + m_iLic + 1, 	var)))
		{
			if (SUCCEEDED(m_WinBlitReader->Display()))
			{
				m_bInitialised = true; 
				iRet = 0;
			}
		}
	}
	return iRet; 
}

int CWinBlitPadView::UnInitialise	()
{
	m_WinBlitReader->Stop();
	m_WinBlitReader->UnloadData();
	if (m_pBrowserWrapper)
	{
		m_pBrowserWrapper.Release();
		m_pBrowserWrapper = NULL; 
	}
	return 0;
}

LRESULT CWinBlitPadView::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CPaintDC dc(m_hWnd);
	return 0;
}

void CWinBlitPadView::OnFinalMessage(HWND /*hWnd*/)
{
	/*PostQuitMessage(0);*/

}

LRESULT CWinBlitPadView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_bInitialised == true)
	{
		UnInitialise ();
	}
	::CoUninitialize();
	return 0;
}

LRESULT CWinBlitPadView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATL_TRACE("\n WinBlitPadview::OnCreate ");
	CoInitialize(0);

	m_bInitialised = false; 
	AtlAxWinInit();
	IUnknown *pUnk; 
	m_wndView = m_hWnd;
	CComBSTR bstr ("WinBlitReaderManager.WinBlitReader.1");
	HRESULT hr = m_wndView.CreateControl(bstr, NULL,  &pUnk);
	if (SUCCEEDED(hr))
	{
		hr = m_wndView.QueryControl(IID_IWinBlitReader, (void**) &m_WinBlitReader);			
	}
	if (!SUCCEEDED(hr))
	{
		Report_Error("System error starting speed reader %X \n If this problem persists please contact Product Support", hr);
	}
	
	//m_wndView.MoveWindow(0,10,10,10);

	CRegistry Reg;

	m_bRegWordWarning = FALSE; 
	m_bRegHTMLWarning = FALSE; 
	Reg.SetRootKey(HKEY_CURRENT_USER);
	Reg.SetKey(lpcstrWinBlitPadRegKey , FALSE);	
	BOOL bRegWordWarning;
	BOOL bRegHTMLWarning;
	if (Reg.ReadBool("WordWarning", bRegWordWarning))
	{
		m_bRegWordWarning = bRegWordWarning; 
	}
	if (Reg.ReadBool("HTMLWarning", bRegHTMLWarning))
	{
		m_bRegHTMLWarning = bRegHTMLWarning; 
	}

	return 0;
}

LRESULT CWinBlitPadView::OnErase(UINT /* uMsg */, WPARAM /* wParam */, LPARAM /* lParam */, BOOL& bHandled)
{
	return 1;
}

LRESULT CWinBlitPadView::OnSize(UINT /* uMsg */, WPARAM /* wParam */, LPARAM /* lParam */, BOOL& /* lResult */)
{
	RECT rcClient;
	GetClientRect(&rcClient);
	ATL_TRACE("\n WinBlitPadView::OnSize %d %d %d %d ",rcClient.left,rcClient.top+30, rcClient.bottom, rcClient.right); 
	return 0;
}

LRESULT CWinBlitPadView::OnFileOpen(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
/*{
	CFileDialog dlg(TRUE, NULL, _T(""), OFN_OVERWRITEPROMPT, lpcstrFilter);
	int nRet = dlg.DoModal();
	if(nRet == IDOK)
	{
	}
	return 0;
}*/

LRESULT CWinBlitPadView::OnFileExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return 0;
}

LRESULT CWinBlitPadView::OnMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATL_TRACE ("\n CWinBlitPadView::OnMover");
	// TODO : Add Code for message handler. Call DefWindowProc if necessary.
	return 0;
}

LRESULT CWinBlitPadView::OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATL_TRACE ("CWinBlitPadView::OnChar"); 
	// TODO : Add Code for message handler. Call DefWindowProc if necessary.
	return 0;
}
LRESULT CWinBlitPadView::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATL_TRACE ("\n CWinBlitPadView::OnKeyDown");
	// TODO : Add Code for message handler. Call DefWindowProc if necessary.
	return 0;
}
LRESULT CWinBlitPadView::OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATL_TRACE ("\n CWinBlitPadView::OnKeyDown");
	// TODO : Add Code for message handler. Call DefWindowProc if necessary.
	return 0;
}
LRESULT CWinBlitPadView::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// Check top see if our dos has finished loading 
	DWORD dwTickCount  = GetTickCount();

	ATL_TRACE0 (e_LOGDETAIL, "CWinBlitPadView::OnTimer"); 
	VARIANT_BOOL bDone(VARIANT_FALSE);
	IDispatch *pDispatch; 
	m_pBrowserWrapper->GetDoc(&bDone,	&pDispatch); 
	if (VARIANT_TRUE == bDone)
	{
		ATL_TRACE0 (e_LOGDETAIL, "fOUND IT"); 

		KillTimer(1); 
		m_pBrowserWrapper->Stop(); 
		CComVariant var (pDispatch); 
		m_WinBlitReader->LoadData(m_iLic + 5, var);
		m_WinBlitReader->Display();
		m_bInitialised = true; 
	}

	if (dwTickCount - m_dwTickCount > ciMaxWait)
	{
		MessageBox ("Failed to load web page", "System Error" , MB_OK); 
		CComVariant var; 
		var.vt = VT_EMPTY; 
		m_WinBlitReader->LoadData(e_INFO_NONE, var); 
		ATL_TRACE ("CWinBlitPadView::OnTimer - timed out"); 
		KillTimer(1); 
	}
	return 0;
}