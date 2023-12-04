// CoLogger.cpp : Implementation of CCoLogger
#include "stdafx.h"
#include "ATLLogApp.h"
#include "CoLogger.h"

/////////////////////////////////////////////////////////////////////////////
// CCoLogger

/////////////////////////////////////////////////////////////////////////////
// CCoLogger


HRESULT CCoLogger::FinalConstruct()
{
	m_bDialogAlive =FALSE;
	m_iLogLevel = 1; 
	m_bLogFile = false; 
	m_bstrLogPath.Append("d:\\BlitLog.txt"); 
	return S_OK; 
}

STDMETHODIMP CCoLogger::Initialize()
{
	m_Dlg = new CCEventDlg(this);
	m_Dlg ->Create(NULL);
	m_bDialogAlive = TRUE;
	return S_OK;
}

STDMETHODIMP CCoLogger::DisplayText()
{
	if(!m_bDialogAlive ) return S_FALSE;
	return S_OK;
}

STDMETHODIMP CCoLogger::Log(long lSeverity, long lThreadID, BSTR bstrText)
{
	TCHAR tchNewLine ('\n'); 
	WCHAR wchNewLine ('\n'); 
	if (wchNewLine == bstrText[0])
	{
		bstrText[0] = L' '; 
	}
	if(!m_bDialogAlive ) return S_FALSE;
	_bstr_t Msg(bstrText);

	TCHAR DisplayBfr [9];

	SYSTEMTIME lSysTime;
	::GetSystemTime(&lSysTime);
	sprintf(DisplayBfr,"%02d:%02d:%02d ",
							lSysTime.wHour,
							lSysTime.wMinute,
							lSysTime.wSecond);
	DisplayBfr[8] = ' '; 

	TCHAR tchSeverity [9]; 
	sprintf(tchSeverity,"%3d     ",lSeverity); 

	TCHAR tchThreadID [9]; 
	sprintf(tchThreadID,"%8d ", lThreadID); 
	tchThreadID[7] = ' '; 

	m_Dlg->AddMessage(lSeverity, lThreadID, Msg, DisplayBfr);
	if (m_bLogFile)
	{
		if (!m_ofstream.is_open())
		{
			USES_CONVERSION;
			TCHAR tch [255];
			strcpy (tch, OLE2T(m_bstrLogPath));
			m_ofstream.open(tch, ios_base::out | ios_base::app);
			m_ofstream.write("Severity ThreadID   Time   Message",34);
			m_ofstream.write(&tchNewLine,1);
			m_ofstream.write("-------- --------   ----   -------",34);
			m_ofstream.write(&tchNewLine,1);
		}
		if (m_ofstream.is_open())
		{
			USES_CONVERSION;

			m_ofstream.write(tchSeverity,9);
			m_ofstream.write(tchThreadID,9);
			m_ofstream.write(DisplayBfr,9);
			m_ofstream.write(OLE2T(bstrText),::SysStringLen(bstrText));
			m_ofstream.write(&tchNewLine,1);
		}
	}

	return S_OK;
}

STDMETHODIMP CCoLogger::UnInitialize()
{
	if(!m_bDialogAlive ) return S_FALSE;
	m_Dlg->DestroyWindow();
	if (m_ofstream.is_open())
	{
		m_ofstream.close();
	}
	return S_OK;
}

STDMETHODIMP CCoLogger::get_Level(long *pVal)
{
	*pVal = m_iLogLevel; 
	return S_OK;
}

STDMETHODIMP CCoLogger::put_Level(long newVal)
{
	m_iLogLevel = newVal; 
	return S_OK;
}

STDMETHODIMP CCoLogger::get_Path(BSTR *pVal)
{
	*pVal = ::SysAllocString(m_bstrLogPath); 
	if (*pVal) return E_OUTOFMEMORY; 
	return S_OK;
}

STDMETHODIMP CCoLogger::put_Path(BSTR newVal)
{
	m_bstrLogPath = newVal; 	
	return S_OK;
}