// CEventDlg.h : Declaration of the CCEventDlg

#ifndef __CEVENTDLG_H_
#define __CEVENTDLG_H_

#include <comutil.h>
#include <commctrl.h>

#include "resource.h"       // main symbols
#include <atlhost.h>
#include <atlapp.h>
#include <atlctrls.h>


class CCoLogger ;
/////////////////////////////////////////////////////////////////////////////
// CCEventDlg
class CCEventDlg : 
	public CAxDialogImpl<CCEventDlg>
{
public:
	CCoLogger *m_pParent;
	CContainedWindowT<CEdit> m_Level;
	CContainedWindowT<CButton> m_LogFile;
	CContainedWindowT<CEdit> m_Path;
	CCEventDlg(CCoLogger *parent)
	{
		m_bLogHalted = FALSE;
		m_pParent = parent ;
		m_bFirstTime = TRUE;
	}

	~CCEventDlg()
	{
	}

	private:BOOL m_bLogHalted;

	public:	enum { IDD = IDD_CEVENTDLG };

BEGIN_MSG_MAP(CCEventDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	COMMAND_HANDLER(IDC_LOGBOX, LBN_DBLCLK, OnDblclkLogbox)
	COMMAND_HANDLER(IDC_LOGBOX, LBN_ERRSPACE, OnErrspaceLogbox)
	COMMAND_HANDLER(IDC_HALT, BN_CLICKED, OnClickedHalt)
	COMMAND_HANDLER(IDC_RESUME, BN_CLICKED, OnClickedResume)
	COMMAND_HANDLER(IDC_CLEARSCR, BN_CLICKED, OnClickedClearscr)
	COMMAND_HANDLER(IDC_LEVEL, EN_CHANGE, OnChangeLevel)
	COMMAND_HANDLER(IDC_PATH, EN_CHANGE,  OnChangePath)
	COMMAND_HANDLER(IDC_LOGFILE, BN_CLICKED,  OnChangeLogFile)
	NOTIFY_HANDLER(IDC_LISTCTRL, LVN_COLUMNCLICK, OnColumnclickListctrl)
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnDblclkLogbox(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnErrspaceLogbox(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	long GetCurSel()
	{
		return ::SendMessage(GetDlgItem(IDC_LOGBOX),LB_GETCURSEL,0,0);
	}
	BOOL m_bFirstTime;
	void AddMessage(long lSeverity, long lThreadID, LPCTSTR DisplayStr, LPCTSTR DisplayBfr)
	{
		if(m_bLogHalted) return;

		TCHAR DisplaySeverity [30];	
		wsprintf(DisplaySeverity, " %d ", lSeverity); 

		TCHAR DisplayThreadID [30];	
		wsprintf(DisplayThreadID, " %d ", lThreadID); 

		//add string to list box...
		if(m_bFirstTime)
		{
			LC_InsertItem(0,0,const_cast<char*>(DisplaySeverity));
			LC_InsertItem(1,1,const_cast<char*>(DisplayThreadID));
			LC_InsertItem(2,2,const_cast<char*>(DisplayStr));
			LC_InsertItem(3,3,const_cast<char*>(DisplayBfr));
			m_bFirstTime =FALSE;
		}
		else
		{
			LC_InsertItem(0,0,const_cast<char*>(DisplaySeverity),1);
			LC_InsertItem(1,1,const_cast<char*>(DisplayThreadID),1);
			LC_InsertItem(2,2,const_cast<char*>(DisplayStr),1);
			LC_InsertItem(3,3,const_cast<char*>(DisplayBfr),1);
		}
	}

	LRESULT OnClickedHalt(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		m_bLogHalted= TRUE;
		return 0;
	}
	LRESULT OnClickedResume(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		m_bLogHalted = FALSE;
		return 0;
	}
	LRESULT OnClickedClearscr(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		//reset contents of list box...
		::SendMessage(GetDlgItem(IDC_LOGBOX),LB_RESETCONTENT,0,0);

		return 0;
	}
	LRESULT OnChangeLevel (WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnChangePath (WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnChangeLogFile (WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	void LC_InsertItem(int nItem,int nSubItem,LPTSTR Text,BOOL bFirstTime = TRUE);
	void CCEventDlg::LC_SetTextColor(COLORREF BkClr,COLORREF BkFore);
	LRESULT OnColumnclickListctrl(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	
};

#endif //__CEVENTDLG_H_
