// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__4100275A_6FC1_11D5_862B_D445D2000000__INCLUDED_)
#define AFX_STDAFX_H__4100275A_6FC1_11D5_862B_D445D2000000__INCLUDED_

// Change these values to use different versions
#define WINVER		0x0400
#define _WIN32_IE	0x0400
#define _RICHEDIT_VER	0x0100

#include <atlbase.h>
#include <atlapp.h>

extern CAppModule _Module;

#include <atlcom.h>
#include <atlhost.h>
#include <atlwin.h>
#include <atlctl.h>
#include <atlmisc.h>

#include "W95trace.h"
#include "LogInclude.h"

static LPCTSTR lpcstrFilter = 
	_T("All Files (*.*)\0*.*\0")
	_T("Text Files (*.txt)\0*.txt\0")
	_T("HTML Files (*.htm)\0*.htm\0")
	_T("");


static LPCTSTR lpcstrWinBlitPadRegKey = _T("Software\\PataSucia\\WinBlit\\WinBlitPad");

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__4100275A_6FC1_11D5_862B_D445D2000000__INCLUDED_)
