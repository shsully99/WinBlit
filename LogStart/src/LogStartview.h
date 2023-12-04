// LogStartView.h : interface of the CLogStartView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGSTARTVIEW_H__83819EA3_6B90_45A3_A9FF_EFEDC9778D00__INCLUDED_)
#define AFX_LOGSTARTVIEW_H__83819EA3_6B90_45A3_A9FF_EFEDC9778D00__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CLogStartView : public CWindowImpl<CLogStartView>
{
public:
	DECLARE_WND_CLASS(NULL)

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		pMsg;
		return FALSE;
	}

	BEGIN_MSG_MAP(CLogStartView)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
	END_MSG_MAP()

	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CPaintDC dc(m_hWnd);

		//TODO: Add your drawing code here

		return 0;
	}
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGSTARTVIEW_H__83819EA3_6B90_45A3_A9FF_EFEDC9778D00__INCLUDED_)
