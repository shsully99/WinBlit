// CEventDlg.cpp : Implementation of CCEventDlg
//copyright ashish dhar Jan 2000
//Use this code as is No Warranty is give...
#include "stdafx.h"
#include "ATLLogApp.h"
#include "CoLogger.h"
#include "CEventDlg.h"
#define lchwnd GetDlgItem(IDC_LISTCTRL)
/////////////////////////////////////////////////////////////////////////////
// CCEventDlg

/////////////////////////////////////////////////////////////////////////////
// CCEventDlg
	static BOOL bInitialising(FALSE); 
	LRESULT CCEventDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bInitialising = TRUE; 
		m_Level.m_hWnd = GetDlgItem(IDC_LEVEL);
		SetDlgItemInt(IDC_LEVEL, m_pParent->m_iLogLevel); 

		m_Path.m_hWnd = GetDlgItem(IDC_PATH);
		USES_CONVERSION; 
		TCHAR tch [255]; 
		strcpy(tch, OLE2T(m_pParent->m_bstrLogPath)); 
		::SetDlgItemText(m_hWnd, IDC_PATH, tch );

		m_LogFile.m_hWnd = GetDlgItem(IDC_LOGFILE);
		if (m_pParent->m_bLogFile)
		{
			m_LogFile.SetCheck(TRUE);
			m_Path.EnableWindow(TRUE); 
		}
		else
		{
			m_LogFile.SetCheck(FALSE);
			m_Path.EnableWindow(FALSE); 
		}

		//set the Horizontal extent...
		::SendMessage(GetDlgItem(IDC_LOGBOX),LB_SETHORIZONTALEXTENT,100,0);

		const int lTabArray[] = {300};
		//set tab stops...
		::SendMessage( GetDlgItem(IDC_LOGBOX), LB_SETTABSTOPS,1,(LPARAM)lTabArray);

		//set the Horizontal extent...
		::SendMessage(GetDlgItem(IDC_LOGBOX),LB_SETHORIZONTALEXTENT,100,0);

		LVCOLUMN lCol;
		lCol.mask = LVCF_TEXT|LVCF_WIDTH;
		lCol.cx = 60;
		lCol.pszText = "Severity";
		lCol.cchTextMax  = 7;
		lCol.iSubItem = 0;
		::SendMessage(lchwnd,LVM_INSERTCOLUMN,0,(LPARAM) (const LPLVCOLUMN) &lCol);
		
		lCol.cx = 60;
		lCol.pszText = "ThreadID";		
		::SendMessage(lchwnd,LVM_INSERTCOLUMN,1,(LPARAM) (const LPLVCOLUMN) &lCol);

		lCol.cx = 400;
		lCol.pszText = "Message";
		::SendMessage(lchwnd,LVM_INSERTCOLUMN,2,(LPARAM) (const LPLVCOLUMN) &lCol);

		lCol.cx = 100;
		lCol.pszText = "Time";
		::SendMessage(lchwnd,LVM_INSERTCOLUMN,3,(LPARAM) (const LPLVCOLUMN) &lCol);
		//send back color
		COLORREF clrBk = RGB(244,217,133);
		lCol.cx = LVSCW_AUTOSIZE_USEHEADER;
		::SendMessage(lchwnd,LVM_SETBKCOLOR,0,(LPARAM) (COLORREF) clrBk);

		COLORREF BkFore = RGB(0,256,256);
		LC_SetTextColor(clrBk ,BkFore);

		bInitialising = FALSE; 
		return 1;  // Let the system set the focus
	}

	LRESULT CCEventDlg::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		m_pParent->m_bDialogAlive  = FALSE;
		DestroyWindow()	;
		return 0;
	}

	LRESULT CCEventDlg::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		m_pParent->m_bDialogAlive  = FALSE;
		DestroyWindow()	;
		return 0; 
	}
	LRESULT CCEventDlg::OnDblclkLogbox(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		long lResult = GetCurSel();
			
		
		return 0;
	}
	LRESULT CCEventDlg::OnErrspaceLogbox(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		return 0;
	}

	void CCEventDlg::LC_InsertItem(int nItem,int nSubItem,LPTSTR Text,BOOL bFirstTime )
	{
		int lastItem = 0;
		LVITEM	lItem;
		lItem.mask = LVIF_TEXT ;
		if(!bFirstTime)
			lastItem = ::SendMessage(lchwnd,LVM_GETITEMCOUNT,0,0); 

		lItem.iItem =lastItem;
		lItem.iSubItem = nSubItem;
		lItem.state = 0;
		lItem.pszText = Text;
		lItem.cchTextMax = strlen(Text +1);
		if(nSubItem == 0)
			::SendMessage(lchwnd,LVM_INSERTITEM,0,(LPARAM) (const LPLVITEM) &lItem); 
		::SendMessage(lchwnd,LVM_SETITEM,0,(LPARAM) (const LPLVITEM) &lItem); 

	}
	void CCEventDlg::LC_SetTextColor(COLORREF BkClr,COLORREF BkFore)
	{

		::SendMessage(lchwnd,LVM_SETTEXTCOLOR,0,(LPARAM) (LPARAM)(COLORREF)BkFore); 
		::SendMessage(lchwnd,LVM_SETTEXTBKCOLOR,0,(LPARAM) (LPARAM)(COLORREF)BkClr); 

	}

	LRESULT CCEventDlg::OnColumnclickListctrl(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
		
		return 0;
	}

	LRESULT CCEventDlg::OnChangeLevel (WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		if (!bInitialising)
		{
			m_pParent->m_iLogLevel = GetDlgItemInt(IDC_LEVEL); 
		}
		return 0;
	}
	LRESULT CCEventDlg::OnChangePath (WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		if (!bInitialising)
		{
			TCHAR tch [255]; 
			::GetDlgItemText(m_hWnd,IDC_PATH, &tch[0], 255); 
			USES_CONVERSION;
			m_pParent->put_Path(T2OLE(tch));
		}
		return 0;
	}
	LRESULT CCEventDlg::OnChangeLogFile (WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		if (!bInitialising)
		{
			if (m_LogFile.GetCheck())
			{
				m_pParent->m_bLogFile = true;
				m_Path.EnableWindow(TRUE); 
			}
			else
			{
				m_pParent->m_bLogFile = false;
				m_Path.EnableWindow(FALSE); 
			}
		}
		return 0;
	}