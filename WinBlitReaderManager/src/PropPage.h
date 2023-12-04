//***************************************************************************
//*
//*		Name		: PropPage.h
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

//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/


#ifndef _PROPPAGE_H
#define _PROPPAGE_H

#include "resource.h"

#include <atlctrls.h>
#include <atldlgs.h>

#include <atlhost.h>

#include "WinBlitProperties.h"
#include "WinBlitRegistry.h"

#include <vector>
#include <string>

using namespace std;

class CWinBlitReader;
class CWinBlitPropertySheet;

class CPropInit
{
protected: 
	CComQIPtr<IWinBlitReader> m_WinBlitReader;
	RECT m_Rect; 
	CAxWindow m_wndView;
	CButton m_PreviewStartButton;
	CButton m_PreviewStopButton;
	CWinBlitPropertySheet* m_pLPS; 
public:
	CPropInit () : m_pLPS(NULL) {};
	virtual ~CPropInit (){};
	void SetPropertySheet(CWinBlitPropertySheet* pLPS)
	{
		m_pLPS  = pLPS;
	};
	void Initialise(HWND hWnd); 
	void SetActive (bool bRedisplay = true); 
	void KillActive (); 
	void PreviewClicked(WORD wID); 

	LRESULT OnPreviewClicked(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		PreviewClicked(wID); 
		return 0;
	}


};

class CAddRuleDialog :	public CDialogImpl<CAddRuleDialog>,
						public CPropInit
{
public:

	int m_iSelectedRule; 
	CContainedWindowT<CEdit> m_RuleNamedit;
	CContainedWindowT<CEdit> m_PeriodEdit;
	CContainedWindowT<CEdit> m_TextEdit;

	enum { IDD = IDD_ADDRULE_DIALOG };

	CAddRuleDialog (int iSelectedRule):m_iSelectedRule(iSelectedRule) {};
	virtual ~CAddRuleDialog() {};
	
	BEGIN_MSG_MAP(CAddRuleDialog )
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_HANDLER(IDOK, BN_CLICKED, OnOK)
		COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnCancel)
		COMMAND_RANGE_HANDLER(IDC_PAUSE_RADIO, IDC_DELAY_RADIO, OnSelChange)
 		MESSAGE_HANDLER(WM_HELP, OnHelpCalled)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnCancel (WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnSelChange(WORD wNotifyCode, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	LRESULT OnHelpCalled(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

protected:
	CComQIPtr<ISettings> m_pSettings; 

};

class CAddSettingDialog : public CDialogImpl<CAddSettingDialog>,
						  public CPropInit
{
public:
	CContainedWindowT<CComboBox, CWinTraitsOR<CBS_DROPDOWNLIST> >	m_TemplateCombo;
	CContainedWindowT<CEdit>										m_ConfigNameEdit;
	CContainedWindowT<CEdit>										m_ConfigDescriptionEdit;
	CContainedWindowT<CComboBox, CWinTraitsOR<CBS_DROPDOWNLIST> >	m_FixWidthCombo;

	CWinBlitRegistry		m_WinBlitRegistry; 
	CWinBlitProperties	m_WinBlitProperties; 
	vector<CSettingStrings> m_vecName;

	enum { IDD = IDD_ADDSETTING_DIALOG };

	CAddSettingDialog () {};
	virtual ~CAddSettingDialog() {};

	BEGIN_MSG_MAP(CAddSettingDialog )
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
 		MESSAGE_HANDLER(WM_HELP, OnHelpCalled)
		COMMAND_HANDLER(IDOK, BN_CLICKED, OnOK)
		COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnCancel)
		COMMAND_HANDLER(IDC_CONFIGURATIONTYPE_COMBO,CBN_SELCHANGE, OnTemplateComboChanged)		
		COMMAND_HANDLER(IDC_FIXWIDTHTYPE_COMBO,		CBN_SELCHANGE, OnFixWidthComboChanged)		
	END_MSG_MAP()

	void CAddSettingDialog::SetUpSettingName();

	LRESULT OnTemplateComboChanged (int, int, HWND h, BOOL& bHandled);

	LRESULT OnFixWidthComboChanged (int, int, HWND h, BOOL& bHandled);

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnCancel (WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnHelpCalled(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

class CPropPageDisplay	: public CPropertyPageImpl<CPropPageDisplay>,
						  public CPropInit
					   
{
public:
	enum { IDD = IDD_PROPPAGE_DISPLAY };

	bool m_bFont;
	CPropPageDisplay () : m_bFont(false)
	{ }

	BEGIN_MSG_MAP(CPropPageDisplay )
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_RANGE_HANDLER(IDC_BACKCOLOR, IDC_FIXATIONTEXTCOLOR, OnClicked)
 		MESSAGE_HANDLER(WM_HELP, OnHelpCalled)
		COMMAND_RANGE_HANDLER(IDC_PREVIEWSTART_BUTTON, IDC_PREVIEWSTOP_BUTTON, OnPreviewClicked)
		CHAIN_MSG_MAP(CPropertyPageImpl<CPropPageDisplay>)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	BOOL OnSetActive	();
	BOOL OnKillActive	(); 

	LRESULT OnClicked(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnHelpCalled(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

};

class CPropPageRules : public CPropertyPageImpl<CPropPageRules>,
					   public CPropInit
{
public:
	enum { IDD = IDD_PROPPAGE_RULES };
	CContainedWindowT<CListViewCtrl, CWinTraitsOR<LVS_REPORT | LVS_EX_GRIDLINES | LVS_NOSORTHEADER | LVS_SINGLESEL, 0/*WS_EX_CLIENTEDGE*/> > m_list;

	CPropPageRules () 
	{ }

	BEGIN_MSG_MAP(CPropPageRules )
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
 		MESSAGE_HANDLER(WM_HELP, OnHelpCalled)
		COMMAND_HANDLER(IDC_REMOVEBREAKPOINTBUTTON, BN_CLICKED, OnClickedRemoverulebutton)
		COMMAND_HANDLER(IDC_ADDBREAKPOINTBUTTON, BN_CLICKED, OnClickedAddrulebutton)
		CHAIN_MSG_MAP(CPropertyPageImpl<CPropPageRules>)
		COMMAND_HANDLER(IDC_MODBREAKPOINTBUTTON, BN_CLICKED, OnClickedModrulebutton)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	BOOL OnSetActive	();
	BOOL OnKillActive	(); 
	LRESULT OnClickedRemoverulebutton(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickedAddrulebutton(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickedModrulebutton(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnHelpCalled(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
protected:
	CComQIPtr<ISettings> m_pSettings; 

};

class CPropPageConfiguration : public CPropertyPageImpl<CPropPageConfiguration>,
	 						   public CPropInit
{
public:
	enum { IDD = IDD_PROPPAGE_SETTINGS };
	CContainedWindowT<CComboBox, CWinTraitsOR<CBS_DROPDOWNLIST> > m_Combobox;
	CContainedWindowT<CButton>	m_RemoveButton;
	CContainedWindowT<CButton>	m_AddButton;
	
	bool m_bSetActive; 
	CPropPageConfiguration () : m_bSetActive (false) 
	{ };

	BEGIN_MSG_MAP(CPropPageConfiguration )
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_HANDLER(IDC_COMBO_CURRENTSETTING, CBN_SELCHANGE, OnComboChanged)		
		COMMAND_HANDLER(IDC_REMOVECONFIGURATIONBUTTON, BN_CLICKED, OnClickedRemovebutton)
		COMMAND_HANDLER(IDC_ADDCONFIGURATIONBUTTON, BN_CLICKED, OnClickedAddbutton)
		COMMAND_RANGE_HANDLER(IDC_PREVIEWSTART_BUTTON, IDC_PREVIEWSTOP_BUTTON, OnPreviewClicked)
 		MESSAGE_HANDLER(WM_HELP, OnHelpCalled)
 		//MESSAGE_HANDLER(WM_PAINT, OnPaint)
		CHAIN_MSG_MAP(CPropertyPageImpl<CPropPageConfiguration>)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
	END_MSG_MAP()
	BOOL OnApply		();
	BOOL OnSetActive	();
	BOOL OnKillActive	(); 


	LRESULT OnComboChanged (int, int, HWND h, BOOL& bHandled);
	LRESULT OnInitDialog				(UINT /*uMsg*/,		WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	
	LRESULT OnClickedRemovebutton		(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	
	LRESULT OnClickedAddbutton			(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnHelpCalled(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);;
     

	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		ATL_TRACE0 (e_LOGDETAIL, "\n OnKillFocus ");
		return 0;
	}
};

class CPropPageFixations : public CPropertyPageImpl<CPropPageFixations>,
						  public CPropInit
{
public:
	enum { IDD = IDD_PROPPAGE_FIXATIONS };
	CContainedWindowT<CEdit>	m_CursorHeightEdit;
	CContainedWindowT<CEdit>	m_CursorWidthEdit;
	CContainedWindowT<CButton>	m_LeaveCursorHighlightedCheck;
	CContainedWindowT<CButton>	m_SoundClickCheck;

	bool m_bSetActive; 
	CPropPageFixations () : m_bSetActive (false) 
	{ };

	BEGIN_MSG_MAP(CPropPageFixations )
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_HANDLER(IDC_FIXATIONHEIGHTEDIT, EN_CHANGE, OnChangeCursorheightorwidth)
		COMMAND_HANDLER(IDC_FIXATIONWIDTHEDIT, EN_CHANGE, OnChangeCursorheightorwidth)
		COMMAND_HANDLER(IDC_LEAVEHIGHLIGHTEDCHECK, BN_CLICKED,  OnChangeLeaveCursorHighlighted)
		COMMAND_HANDLER(IDC_SOUNDCLICKCHECK, BN_CLICKED,	OnChangeSoundClick)
		COMMAND_RANGE_HANDLER(IDC_PREVIEWSTART_BUTTON, IDC_PREVIEWSTOP_BUTTON, OnPreviewClicked)
		MESSAGE_HANDLER(WM_HELP, OnHelpCalled)
		CHAIN_MSG_MAP(CPropertyPageImpl<CPropPageFixations>)
	END_MSG_MAP()
	BOOL OnSetActive	();
	BOOL OnKillActive	(); 

	LRESULT OnComboChanged (int, int, HWND h, BOOL& bHandled);

	LRESULT OnInitDialog				(UINT /*uMsg*/,		WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	LRESULT OnChangeCursorheightorwidth	(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnChangeLeaveCursorHighlighted	(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnChangeSoundClick				(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnHelpCalled(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);;

};



class CPropPageSpeed : public CPropertyPageImpl<CPropPageSpeed>,
					   public CPropInit
{
	bool m_bSetActive; 
public:
	enum { IDD = IDD_PROPPAGE_SPEED };
	CContainedWindowT<CTrackBarCtrl> m_SpeedSlider;
	CContainedWindowT<CEdit> m_SpeedEdit;
	
	CContainedWindowT<CTrackBarCtrl> m_FixTimeSlider;

	CContainedWindowT<CEdit> m_HighlightEdit;
	CContainedWindowT<CEdit> m_CoffEdit;

	CPropPageSpeed () : m_bSetActive(false) { }

	BEGIN_MSG_MAP(CPropPageSpeed )
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_HSCROLL, OnHScroll)
		MESSAGE_HANDLER(WM_VSCROLL, OnVScroll)
 		MESSAGE_HANDLER(WM_HELP, OnHelpCalled)
		COMMAND_HANDLER(IDC_SPEED_EDIT,			EN_CHANGE, OnChangeSpeedEdit)
		COMMAND_HANDLER(IDC_HIGHLIGHTEDIT,		EN_CHANGE, OnChangeHighlightEdit)
		COMMAND_RANGE_HANDLER(IDC_PREVIEWSTART_BUTTON, IDC_PREVIEWSTOP_BUTTON, OnPreviewClicked)
		CHAIN_MSG_MAP(CPropertyPageImpl<CPropPageSpeed>)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	BOOL OnSetActive	();
	BOOL OnKillActive	(); 
	LRESULT OnHScroll				(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);	
	LRESULT OnVScroll				(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);	
	LRESULT OnChangeSpeedEdit		(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnChangeHighlightEdit	(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnHelpCalled			(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

protected:
	void UpdateDisplay(); 
};


class CPropPageGeneral : public CPropertyPageImpl<CPropPageGeneral>,
						   public CPropInit
{
public:
	enum { IDD = IDD_PROPPAGE_GENERAL };

	CContainedWindowT<CButton>	m_ShowMetafile;
	CContainedWindowT<CButton>	m_ShowToolBar;
	CContainedWindowT<CButton>	m_ShowTrackBar;
	CContainedWindowT<CButton>	m_ShowStatusBar;

	CContainedWindowT<CButton>	m_BlitPadCheck;
	CContainedWindowT<CButton>	m_IECheck;
	CContainedWindowT<CButton>	m_OutlookCheck;
	CContainedWindowT<CButton>	m_WordCheck;

	CContainedWindowT<CButton>	m_ClearStatistics;

	bool m_bSetActive; 

	CPropPageGeneral () : m_bSetActive(false) { }

	BEGIN_MSG_MAP(CPropPageGeneral )
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
 		MESSAGE_HANDLER(WM_HELP, OnHelpCalled)
		COMMAND_RANGE_HANDLER(IDC_AUTOSTART_IECHECK, IDC_AUTOSTART_OUTLOOKCHECK, OnAutoStartCheck)
		COMMAND_RANGE_HANDLER(IDC_SHOWSTATUSBARCHECK , IDC_SHOWTOOLBARCHECK, OnDisplayCheck)
		CHAIN_MSG_MAP(CPropertyPageImpl<CPropPageGeneral>)
		COMMAND_HANDLER(IDC_CLEARSTATISTICS, BN_CLICKED, OnClickedClearStatistics)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	BOOL OnSetActive	();
	BOOL OnKillActive	(); 
	LRESULT OnHelpCalled			(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnAutoStartCheck (WORD wNotifyCode, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnDisplayCheck	 (WORD wNotifyCode, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

protected:
	LRESULT OnClickedClearStatistics(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};


class CWinBlitPropertySheet : public CPropertySheetImpl<CWinBlitPropertySheet>
{
public:
	CPropPageDisplay	m_PageDisplay;
	CPropPageSpeed		m_PageSpeed;
	CPropPageConfiguration	m_PageConfiguration;
	CPropPageFixations	m_PageFixations;
	CPropPageRules		m_PageRules;
	CPropPageGeneral	m_PageGeneral;
	CWinBlitRegistry		m_WinBlitRegistry; 
	CWinBlitProperties   m_Properties; 
	vector<CSettingStrings>		m_vecstring; 	
	bool				m_bIsDirty; 
	bool				m_bWasDirty; 
	int  				m_iCurrentSetting; 
	long				m_lDemoMode; 
	bool				m_bClearStatsRequired; 

	CWinBlitPropertySheet() ;

	virtual ~CWinBlitPropertySheet() ;

	void Initialise (long lDemoMode); 

	BEGIN_MSG_MAP(CWinBlitPropertySheet)
		MESSAGE_HANDLER		(PSM_CHANGED, OnDirty)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
		CHAIN_MSG_MAP(CPropertySheetImpl<CWinBlitPropertySheet>)	
	END_MSG_MAP()

	LRESULT OnHelpCalled(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled, HWND hWndDialog, WCHAR* pwchDIALOG);

	LRESULT OnDirty(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		ATLTRACE  ("\n CWinBlitPropertySheet::OnDirty"); 
		bHandled = false;
		m_bIsDirty = true; 
		return 0;
	}

	bool IsDirty()
	{
		return m_bIsDirty; 
	}
	bool WasDirty()
	{
		return m_bWasDirty; 
	}

	BOOL Update();

	BOOL RemoveCurrent(); 
	BOOL ChangeSel	(BSTR bstrSel); 
	BOOL SetDefault (int iSel);
	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};
#endif