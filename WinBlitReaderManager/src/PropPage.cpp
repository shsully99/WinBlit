//***************************************************************************
//*
//*		Name		: PropPage.cpp
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
//*	
//*
//* 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/


#include "stdafx.h"
#include "PropPage.h"
#include "WinBlitReader.h"
#include "htmlhelp.h"
#include "DialogMap.h"
static const int ciMinConfigs(1);
static const int ciMaxConfigs(99);

//#include "htmlhelp.h"

/////////////////////////////////////////////////////////////////////////////
//
//			CAddRuleDialog methods
//
/////////////////////////////////////////////////////////////////////////////

LRESULT CAddRuleDialog::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{

	CComPtr<IDispatch> pDispatch; 
	HRESULT hr = m_pLPS->m_Properties.get_Settings(&pDispatch); 
	if (S_OK == hr)
	{
		m_pSettings = pDispatch;
	}
	// Error - no settings collection returned 
	if (!m_pSettings.p) 
	{
		MessageBox("System error retrieving breakpoints","Error", MB_OK| MB_ICONERROR);
		return 0; 
	}

	m_RuleNamedit.m_hWnd = GetDlgItem(IDC_NAME_EDIT);
	m_PeriodEdit.m_hWnd = GetDlgItem(IDC_PERIOD_EDIT);
	m_TextEdit.m_hWnd = GetDlgItem(IDC_TEXT_EDIT);

	// If in modify and this is the same as the input 
	if (m_iSelectedRule >= 0)
	{
		CComPtr<ISetting> pSetting;
		CComVariant varIndex(m_iSelectedRule+1);
		HRESULT hr = m_pSettings->get_ItemCustom(varIndex, &pSetting);
		if (S_OK == hr)
		{
			BSTR bstrName;
			BSTR bstrValue;
			long lPeriod = 0;
			long lRule = 0;	

			pSetting->get_Name	 ( &bstrName	);
			pSetting->get_Value	 ( &bstrValue	);
			pSetting->get_Period ( &lPeriod		);
			pSetting->get_Rule	 ( &lRule		);

			USES_CONVERSION; 
			SetDlgItemText(IDC_NAME_EDIT, OLE2T(bstrName));
			SetDlgItemText(IDC_TEXT_EDIT, OLE2T(bstrValue));
			if (2 == lRule)
			{
				SetDlgItemInt(IDC_PERIOD_EDIT, lPeriod);
				CheckRadioButton(IDC_PAUSE_RADIO, IDC_DELAY_RADIO, IDC_DELAY_RADIO);
				m_PeriodEdit.EnableWindow(TRUE); 

			}
			else
			{
				CheckRadioButton(IDC_PAUSE_RADIO, IDC_DELAY_RADIO, IDC_PAUSE_RADIO);
				m_PeriodEdit.EnableWindow(FALSE); 
				SetDlgItemInt(IDC_PERIOD_EDIT, 0);
			}

			::SysFreeString(bstrName);
			::SysFreeString(bstrValue);			
		}
	}
	else 
	{
		// Adding a new rule

		// Calculate a default name for the new rule
		TCHAR tchRuleName [13];
		for (int iA = 1; iA < 99; iA++)
		{
			wsprintf(tchRuleName, "Breakpoint#%0d", iA); 
			CComPtr<ISetting> pSetting;
			CComBSTR bstrVal(tchRuleName); 
			CComVariant varRuleName(bstrVal.m_str);
			HRESULT hr = m_pSettings->get_ItemCustom(varRuleName,  &pSetting);
			if (S_OK != hr)
			{
				break; 
			}
		}
		
		CheckRadioButton(IDC_PAUSE_RADIO, IDC_DELAY_RADIO, IDC_PAUSE_RADIO);
		m_PeriodEdit.EnableWindow(FALSE); 
		SetDlgItemText(IDC_NAME_EDIT, tchRuleName);
	}
	
	return 0;
}

LRESULT CAddRuleDialog::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}

LRESULT CAddRuleDialog::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComBSTR bstrName;
	CComBSTR bstrText; 
	long lRule;
	long lPeriod; 

	GetDlgItemText(IDC_NAME_EDIT, bstrName.m_str);
	if (bstrName.Length() <= 0) 
	{
		MessageBox("Must enter a name for the rule","Error", MB_OK| MB_ICONERROR);
		return 0; 
	}
	GetDlgItemText(IDC_TEXT_EDIT, bstrText.m_str);
	if (bstrText.Length() <= 0 || bstrText == " ") 
	{
		MessageBox("Must enter Text for the rule","Error", MB_OK| MB_ICONERROR);
		return 0; 
	}
	if (IsDlgButtonChecked(IDC_PAUSE_RADIO))
	{
		lRule = 1; 
	}
	else 
	{
		lRule = 2; 
	}

	if (2 == lRule)
	{
		TCHAR tchPeriod [255];
		GetDlgItemText(IDC_PERIOD_EDIT,tchPeriod,255);
		if (strlen(tchPeriod) <= 0)
		{
			MessageBox("Must enter a delay period for this rule. ","Error", MB_OK| MB_ICONERROR);
			return 0; 
		}
		float f = ::atof(tchPeriod);
		lPeriod = f * 1000; 
		if (0 == lPeriod )
		{
			MessageBox("Must enter a delay period greater than 0 as a decimal value ","Error", MB_OK| MB_ICONERROR);
			return 0; 
		}
	}

	// Check rule with this name not already entered if in add
	CComVariant varRuleName(bstrName);
	CComPtr<ISetting> pSetting;

	HRESULT hr = m_pSettings->get_ItemCustom(varRuleName,  &pSetting);
	if (S_OK == hr)
	{
		if (-1 == m_iSelectedRule)
		{
			MessageBox("A rule with this name has already been entered ","Error", MB_OK| MB_ICONERROR);
			return 0; 
		}
		else
		{
			CComVariant var (m_iSelectedRule+1);
			m_pSettings->Remove(var);
		}
	}	
	m_pSettings->Add(bstrName,0, lRule, bstrText, lPeriod);
	EndDialog(wID);
	return 0;
}

LRESULT CAddRuleDialog::OnSelChange(WORD wNotifyCode, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(wNotifyCode == BN_CLICKED)
	{
		if (IsDlgButtonChecked(IDC_PAUSE_RADIO))
		{
			m_PeriodEdit.EnableWindow(FALSE); 
		}
		else 
		{
			m_PeriodEdit.EnableWindow(TRUE); 
		}
	}
	return 0;
}

LRESULT CAddRuleDialog::OnHelpCalled(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return m_pLPS->OnHelpCalled( uMsg,  wParam, lParam,  bHandled, m_hWnd, L"AddRuleDialog");
}


/////////////////////////////////////////////////////////////////////////////
//
//			CAddSettingDialog methods
//
/////////////////////////////////////////////////////////////////////////////

void CAddSettingDialog::SetUpSettingName()
{
	USES_CONVERSION; 
	int iA = m_TemplateCombo.GetCurSel();
	ATL_TRACE2 (e_LOGFLOW, "\n  CAddSettingDialog::SetUpSettingName() %d %s ",iA , m_vecName[iA].m_wstrTemplateID.c_str());
	CComBSTR bstrTemplate (m_vecName[iA].m_wstrTemplateID.c_str());
	SetDlgItemText(IDC_TEMPLATEDESCRIPTION_STATIC, OLE2T(m_vecName[iA].m_wstrDescription.c_str()));

	TCHAR tch [255]; 

	// Strip out commas from template name
	int iB = 0; 
	for (iA = 0; iA< bstrTemplate.Length(); iA++)
	{
		if (bstrTemplate[iA] != ',') 
		{
			tch[iB] = (TCHAR) bstrTemplate[iA];
			iB++;
		}
	}
	int iPos = iB; 
	// Loop from 2 to 99 trying to find a name that does not already exist 
	// 
	for (iA = 2; iA < 99; iA++)
	{
		wsprintf(&tch[iPos],"#%d", iA);
		tch [iPos+3] = TCHAR('/0');			// NULL terminate 
		bool bSettingExists = false; 

		for (vector<CSettingStrings>::iterator
			it =  m_pLPS->m_vecstring.begin();
			it != m_pLPS->m_vecstring.end();
			it++ )
		{
			USES_CONVERSION; 
			if (0 == strcmp(OLE2T(it->m_wstrName.c_str()), tch))
			{
				bSettingExists = true;
				break; 
			}
		}
		// Have found a unique name so break
		if (bSettingExists == false) break; 
	}
	// Set up default value for new name 
	SetDlgItemText(IDC_CONFIGNAME_EDIT,tch); 
}


LRESULT CAddSettingDialog::OnTemplateComboChanged (int, int , HWND h, BOOL& bHandled)
{
	SetUpSettingName(); 
	return 0; 
}


LRESULT CAddSettingDialog::OnFixWidthComboChanged (int, int wID, HWND h, BOOL& bHandled)
{
	USES_CONVERSION; 
	SetDlgItemText (IDC_FIXWIDTHDESCRIPTION_STATIC, OLE2T(cawchFixWidthDescriptions[m_FixWidthCombo.GetCurSel()]));
	return 0; 
}


LRESULT CAddSettingDialog::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_TemplateCombo.m_hWnd = GetDlgItem(IDC_TEMPLATE_COMBO); 	
	m_ConfigNameEdit.m_hWnd = GetDlgItem(IDC_CONFIGNAME_EDIT);
	m_ConfigDescriptionEdit.m_hWnd = GetDlgItem(IDC_CONFIGDESCRIPTION_EDIT);
	m_FixWidthCombo.m_hWnd = GetDlgItem(IDC_FIXWIDTHTYPE_COMBO);

	// Load all of the template names  from the registry 
	m_WinBlitRegistry.GetAllSettings(m_vecName, 1);

	USES_CONVERSION; 
	for (int iA = 0; iA < m_vecName.size(); iA++)
	{		
		m_TemplateCombo.InsertString(iA, OLE2T(m_vecName[iA].m_wstrName.c_str()));
	}
	m_TemplateCombo.SetCurSel(0);
	
	for (iA = 0; iA < ciMaxFixWidthTypes; iA++)
	{
		m_FixWidthCombo.InsertString(iA, OLE2T(cawchFixWidthTypes[iA]));
	}
	m_FixWidthCombo.SetCurSel(0);
	SetDlgItemText (IDC_FIXWIDTHDESCRIPTION_STATIC, OLE2T(cawchFixWidthDescriptions[m_FixWidthCombo.GetCurSel()]));


	SetUpSettingName();

	return 0;
}

LRESULT CAddSettingDialog::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}


LRESULT CAddSettingDialog::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	bHandled = true; 
	CComBSTR bstrSettingName;

	GetDlgItemText(IDC_CONFIGURATIONNAME_EDIT, bstrSettingName.m_str);

	if (bstrSettingName.Length() <= 0) 
	{
		// Check length 
		MessageBox("Must select setting name","Error", MB_OK| MB_ICONERROR);
		return 0; 
	}

	// Check not already added 
	for (vector<CSettingStrings>::iterator
		it =  m_pLPS->m_vecstring.begin();
		it != m_pLPS->m_vecstring.end();
		it++ )
	{
		USES_CONVERSION; 
		if (0 == wcscmp(it->m_wstrName.c_str(), bstrSettingName))
		{
			MessageBox("Name already exists","Error", MB_OK| MB_ICONERROR);
			return 0; 
		}
	}
	USES_CONVERSION;
	int iA = m_TemplateCombo.GetCurSel();
	CComBSTR bstrTemplate (m_vecName[iA].m_wstrTemplateID.c_str());

	// Load template into properties
	m_WinBlitRegistry.LoadSettings(bstrTemplate, &m_WinBlitProperties,  1);

	// Set up the cursor according to the setting of the fixation width 
	// combo box 
	long lCursor = m_WinBlitProperties.Cursor(); 
	if	    (e_CHARS  == m_FixWidthCombo.GetCurSel())
	{
		lCursor = lCursor | cCharDivisions; 
	}
	else if (e_COLUMNS  == m_FixWidthCombo.GetCurSel())
	{
		lCursor = lCursor | cLineDivisions; 
	}
	else if (e_WORDS  == m_FixWidthCombo.GetCurSel())
	{
		lCursor = lCursor | cWordDivisions; 
		if (cTachistoscopicCursor & lCursor ||
			cSlowHandCursor   & lCursor)
		{
			lCursor = lCursor | cEqualiseWordDivisions; 
		}
	}
	m_WinBlitProperties.put_Cursor(lCursor); 

	// Write properties to the registry
	m_WinBlitRegistry.SaveSettings(bstrSettingName, &m_WinBlitProperties, 0);

	// Set new Configuration to be the default 
	wstring wstrDefaultName;
	wstrDefaultName.assign(bstrSettingName);

	m_WinBlitRegistry.SetDefaultName(wstrDefaultName); 

	// Todo 0 Check alphanumeric
	EndDialog(wID);

	return 0;
}

LRESULT CAddSettingDialog::OnHelpCalled(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return m_pLPS->OnHelpCalled( uMsg,  wParam, lParam,  bHandled, m_hWnd, L"AddSettingDialog");
}


/////////////////////////////////////////////////////////////////////////////
//
//			CPropPageDisplay methods
//
/////////////////////////////////////////////////////////////////////////////


LRESULT  CPropPageDisplay::OnClicked(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (wID == IDC_BACKCOLOR)
	{
		CColorDialog Color(m_pLPS->m_Properties.ScreenBackColor());
		if (IDOK == Color.DoModal())
		{
			m_pLPS->m_Properties.put_ScreenBackColor(Color.GetColor());
			CPropInit::SetActive();
			SetModified(TRUE);
		}
	}
	else if (wID == IDC_SCREENFILLCOLOR)
	{
		CColorDialog Color(m_pLPS->m_Properties.ScreenFillColor());
		if (IDOK == Color.DoModal())
		{
			m_pLPS->m_Properties.put_ScreenFillColor(Color.GetColor());
			CPropInit::SetActive();
			SetModified(TRUE);
		}
	}
	else if(wID == IDC_FIXATIONFILLCOLOR)
	{
		CColorDialog Color(m_pLPS->m_Properties.CursorFillColor());
		if (IDOK == Color.DoModal())
		{
			m_pLPS->m_Properties.put_CursorFillColor(Color.GetColor());
			CPropInit::SetActive();
			SetModified(TRUE);
		}
	}
	else if (wID == IDC_SCREENTEXTCOLOR)
	{
		CColorDialog Color(m_pLPS->m_Properties.ScreenTextColor());
		if (IDOK == Color.DoModal())
		{
			m_pLPS->m_Properties.put_ScreenTextColor(Color.GetColor());
			CPropInit::SetActive();
			SetModified(TRUE);
		}
	}
	else if (wID == IDC_FIXATIONTEXTCOLOR)
	{
		CColorDialog Color(m_pLPS->m_Properties.CursorTextColor());
		if (IDOK == Color.DoModal())
		{
			m_pLPS->m_Properties.put_CursorTextColor(Color.GetColor());
			CPropInit::SetActive();
			SetModified(TRUE);
		}
	}	
	else if (wID == IDC_FONT)
	{
		// Create a font handle and set up its value with a handle to the
		// currently selected font. 
		CFontT<false> FontHandle; 
		CComPtr<IFontDisp> pFontDisp; 
		m_pLPS->m_Properties.get_TextFont(&pFontDisp); 
		CComQIPtr<IFont> pFont(pFontDisp);
		HFONT hFont;
		pFont->get_hFont(&hFont); 
		FontHandle.Attach(hFont); 

		// Get the logical font and use it to initialise the Font Dialog
		LOGFONT lf;
		FontHandle.GetLogFont(&lf);
		CFontDialog dlg(&lf);
		dlg.m_cf.Flags |= CF_INITTOLOGFONTSTRUCT;
		dlg.m_cf.Flags ^= CF_EFFECTS;						// No colors

		// Show Font dialog
		if (TRUE == dlg.DoModal())
		{
			// User has pressed OK so set up a FONT structure fron the dialog values
			FONTDESC fd;
			fd.cbSizeofstruct = sizeof(fd);
			fd.sCharset = dlg.m_cf.lpLogFont->lfCharSet;
			fd.sWeight = dlg.GetWeight();
			fd.fItalic = dlg.IsItalic();
			fd.fStrikethrough = dlg.IsStrikeOut();
			fd.fUnderline = dlg.IsUnderline();
			fd.sCharset = dlg.m_cf.lpLogFont->lfCharSet;
			fd.cySize.int64 = dlg.GetSize() * 1000;
			USES_CONVERSION;
			CComBSTR bstrVal (T2OLE(dlg.GetFaceName()));
			fd.lpstrName = bstrVal.m_str;

			// Create an ole font and set it up as our new font 
			CComPtr<IFontDisp> pFontDisp;
			::OleCreateFontIndirect(&fd,IID_IFontDisp,(void **)&pFontDisp);
			m_pLPS->m_Properties.put_TextFont(pFontDisp);

			// Update and repaint the demo screen. 
			CPropInit::SetActive();
			SetModified(TRUE);
		}
	}
	return 0;
}

LRESULT CPropPageDisplay::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CPropInit::Initialise(m_hWnd); 
	return TRUE;
}

BOOL CPropPageDisplay::OnSetActive ()
{
	CPropInit::SetActive();
	return TRUE;
}

BOOL CPropPageDisplay::OnKillActive	()
{
	CPropInit::KillActive();
	return TRUE;
}

LRESULT CPropPageDisplay::OnHelpCalled(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return m_pLPS->OnHelpCalled( uMsg,  wParam, lParam,  bHandled, m_hWnd, L"PropPageDisplay");
}

/////////////////////////////////////////////////////////////////////////////
//
//			CPropPageRules methods
//
/////////////////////////////////////////////////////////////////////////////

LRESULT CPropPageRules::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_list.m_hWnd = GetDlgItem(IDC_BREAKPOINTS_LIST);
	m_list.AddColumn	(_T("Name"), 0);	
	m_list.AddColumn	(_T("Type"), 1);
	m_list.AddColumn	(_T("Text"), 2);
	m_list.AddColumn	(_T("Period"), 3);
	RECT rc;
	::GetClientRect(m_list.m_hWnd, &rc);
	m_list.SetColumnWidth(0, (rc.right-rc.left) / 4);
	m_list.SetColumnWidth(1, (rc.right-rc.left) / 4);
	m_list.SetColumnWidth(2, (rc.right-rc.left) / 4);
	m_list.SetColumnWidth(3, (rc.right-rc.left) / 4);
	
	CComPtr<IDispatch> pDispatch; 
	HRESULT hr = m_pLPS->m_Properties.get_Settings(&pDispatch); 
	if (S_OK == hr)
	{
		m_pSettings = pDispatch;
	}
	// Error - no setrtings collection returned 
	if (!m_pSettings.p) 
	{
		MessageBox("System error retrieving breakpoints","Error", MB_OK| MB_ICONERROR);
		return 0; 
	}

	/*m_list.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_list.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_list.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_list.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);*/

	return TRUE;
}

LRESULT CPropPageRules::OnClickedAddrulebutton(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CAddRuleDialog AddRule(-1);
	AddRule.SetPropertySheet(m_pLPS); 

	if (IDOK == AddRule.DoModal())
	{
		OnSetActive();
		SetModified (TRUE);
	}
	bHandled = true; 
	return 0; 
}


LRESULT CPropPageRules::OnClickedRemoverulebutton(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int iA = m_list.GetSelectionMark();

	if (iA >= 0)
	{
		if  (IDOK == MessageBox("Are you sure you want to completely remove this breakpoint from the system","Remove Breakpoint",MB_OKCANCEL | MB_ICONWARNING))
		{
			HRESULT hr = m_pSettings->Remove(CComVariant(iA+1));
			OnSetActive();
			SetModified (TRUE);
		}
	}
	else 
	{
		MessageBox ("Error. Select the name of a breakpoint you wish to remove","Remove Configuration", MB_OK);
	}

	bHandled = true; 
	return 0; 
}

LRESULT CPropPageRules::OnClickedModrulebutton(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int iA = m_list.GetSelectionMark();

	if (iA >= 0)
	{
		CAddRuleDialog AddRule(iA);
		AddRule.SetPropertySheet(m_pLPS); 
		if (IDOK == AddRule.DoModal())
		{
			OnSetActive();
			SetModified (TRUE);
		}
	}
	else 
	{
		MessageBox ("Error. Select the name of a breakpoint you wish to modify","Remove Configuration", MB_OK);
	}

	bHandled = true; 

	return 0;
}



BOOL CPropPageRules::OnSetActive ()
{
	// Todo Populate the list box 
	// Clear contents 
	m_list.DeleteAllItems();

	long lTotal;
	m_pSettings->get_Count(&lTotal);
	long lCount = 1;
	while (lCount <= lTotal)
	{
		CComQIPtr<ISetting> pSetting;
		HRESULT hr = m_pSettings->get_ItemCustom(CComVariant(lCount),  &pSetting);
		if (S_OK == hr && pSetting.p)
		{
			BSTR bstrName;
			BSTR bstrValue;
			long lPeriod = 0;
			long lRule = 0;	

			pSetting->get_Name	 ( &bstrName	);
			pSetting->get_Value	 ( &bstrValue	);
			pSetting->get_Period ( &lPeriod		);
			pSetting->get_Rule	 ( &lRule		);
			
			USES_CONVERSION;
			m_list.AddItem(lCount-1, 0, OLE2T(bstrName)); 
			m_list.AddItem(lCount-1, 1, tchRuleType[lRule-1]); 
			m_list.AddItem(lCount-1, 2, OLE2T(bstrValue)); 			
			if (2 == lRule)
			{	
				TCHAR tchPeriod [20];
				sprintf (tchPeriod, "%.3f seconds", float(lPeriod)/1000);				
				m_list.AddItem(lCount-1, 3, tchPeriod); 
			}
			::SysFreeString(bstrName);
			::SysFreeString(bstrValue);
		}
		lCount++;
	}

	return TRUE;
}

BOOL CPropPageRules::OnKillActive	()
{
	return TRUE;
}

LRESULT CPropPageRules::OnHelpCalled(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return m_pLPS->OnHelpCalled( uMsg,  wParam, lParam,  bHandled, m_hWnd, L"PropPageRules");
}

/////////////////////////////////////////////////////////////////////////////
//
//			CPropPageSpeed methods
//
/////////////////////////////////////////////////////////////////////////////

LRESULT CPropPageSpeed::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CPropInit::Initialise(m_hWnd);
	return 0; 
}

BOOL CPropPageSpeed::OnSetActive	()
{
	m_bSetActive = true; 

	m_SpeedSlider.m_hWnd = GetDlgItem(IDC_SPEED_SLIDER);
	m_FixTimeSlider.m_hWnd = GetDlgItem(IDC_FIXTIME_SLIDER);

	SetDlgItemInt(IDC_SPEED_EDIT, (int) (60000.00 / (float)m_pLPS->m_Properties.BaseTime()) );
	SetDlgItemInt(IDC_HIGHLIGHTEDIT, abs(m_pLPS->m_Properties.HighlightPeriod()));

	if (m_pLPS->m_Properties.Cursor() & cTachistoscopicCursor ||
		m_pLPS->m_Properties.Cursor() & cSlowHandCursor)
	{
		SetDlgItemText(IDC_STATIC_COFFTYPE, "Display time :");
	}
	else
	{
		SetDlgItemText(IDC_STATIC_COFFTYPE, "Blackout time :");
	}

	UpdateDisplay();

	CPropInit::SetActive(); 

	m_bSetActive = false; 

	return TRUE;
}

BOOL CPropPageSpeed::OnKillActive	()
{
	CPropInit::KillActive(); 
	return TRUE;
}

LRESULT CPropPageSpeed::OnHScroll			(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_SpeedSlider.m_hWnd == (HWND) lParam)
	{
		ATL_TRACE ("\n Cracked base %d", m_SpeedSlider.GetPos());
		SetDlgItemInt(IDC_SPEED_EDIT, m_SpeedSlider.GetPos());	
		m_pLPS->m_Properties.put_BaseTime(60000 / m_SpeedSlider.GetPos()); 
		if (!m_bSetActive)
		{
			CPropInit::SetActive(false);
			SetModified(TRUE);
		}
		UpdateDisplay();
	}
	return 0; 
}

LRESULT CPropPageSpeed::OnVScroll			(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_FixTimeSlider.m_hWnd == (HWND) lParam)
	{
		m_pLPS->m_Properties.put_HighlightPeriod(0-m_FixTimeSlider.GetPos()); 
		if (m_pLPS->m_Properties.Cursor() & cTachistoscopicCursor ||
			m_pLPS->m_Properties.Cursor() & cSlowHandCursor)
		{
			m_pLPS->m_Properties.put_DisplayPeriod (0- (ciPercentMax - m_FixTimeSlider.GetPos())); 
		}
		else
		{
			m_pLPS->m_Properties.put_BlackoutPeriod (0- (ciPercentMax - m_FixTimeSlider.GetPos())); 
		}
		SetDlgItemInt(IDC_HIGHLIGHTEDIT, abs(m_pLPS->m_Properties.HighlightPeriod()));
		if (!m_bSetActive)
		{
			CPropInit::SetActive(false);
			SetModified(TRUE);
		}
		UpdateDisplay(); 
	}
	return 0; 
}

LRESULT CPropPageSpeed::OnChangeSpeedEdit	(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int iVal = GetDlgItemInt(IDC_SPEED_EDIT);
	if (iVal < ciSpeedMin) 
	{
		iVal = ciSpeedMin;
	}
	else if (iVal > ciSpeedMax)
	{
		iVal = ciSpeedMax;
	}
	ATL_TRACE ("\n CPropPageSpeed::OnChangeSpeedEdit SetPos %d ", iVal); 
		m_SpeedSlider.SetRangeMin(ciSpeedMin);
	m_SpeedSlider.SetRangeMax(ciSpeedMax);
	m_SpeedSlider.SetPos(iVal);
	m_pLPS->m_Properties.put_BaseTime(60000/iVal); 
	if (!m_bSetActive)
	{
		CPropInit::SetActive(false);
		SetModified(TRUE);
	}
	UpdateDisplay();
	bHandled = true;

	return 0; 
}

LRESULT CPropPageSpeed::OnChangeHighlightEdit	(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	
	int iVal = GetDlgItemInt(IDC_HIGHLIGHTEDIT);
	if (iVal < ciPercentMin) 
	{
		iVal = ciPercentMin;
	}
	else if (iVal > ciPercentMax)
	{
		iVal = ciPercentMax;
	}

	m_pLPS->m_Properties.put_HighlightPeriod(0-iVal); 

	if (m_pLPS->m_Properties.Cursor() & cTachistoscopicCursor ||
		m_pLPS->m_Properties.Cursor() & cSlowHandCursor)
	{
		m_pLPS->m_Properties.put_DisplayPeriod (0 - (ciPercentMax - iVal)); 
	}
	else 
	{
		m_pLPS->m_Properties.put_BlackoutPeriod (0 - (ciPercentMax - iVal)); 
	}

	if (!m_bSetActive)
	{
		CPropInit::SetActive(false);
		SetModified(TRUE);
	}
	UpdateDisplay();
	bHandled = true;
	
	return 0; 
}


LRESULT CPropPageSpeed::OnHelpCalled		(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return m_pLPS->OnHelpCalled( uMsg,  wParam, lParam,  bHandled, m_hWnd, L"PropPageSpeed");
}

void CPropPageSpeed::UpdateDisplay()
{
	int iHighlight,iCOff, iVal;

	m_SpeedSlider.SetRangeMin(ciSpeedMin);
	m_SpeedSlider.SetRangeMax(ciSpeedMax);
	m_SpeedSlider.SetPos (60000/m_pLPS->m_Properties.BaseTime()); 

	ATL_TRACE ("\n CPropPageSpeed::UpdateDisplay  SetPos %d ", 60000/m_pLPS->m_Properties.BaseTime()); 

	iHighlight = abs(m_pLPS->m_Properties.HighlightPeriod());

	m_FixTimeSlider.SetTicFreq(ciFreq);
	m_FixTimeSlider.SetPos(iHighlight);

	SetDlgItemInt(IDC_FIXTIMESTATIC, m_pLPS->m_Properties.BaseTime()); 
	iVal = (abs(iHighlight) * m_pLPS->m_Properties.BaseTime()) / 100; 
	SetDlgItemInt(IDC_STATIC_HIGHLIGHTTIME, iVal);
	SetDlgItemInt(IDC_STATIC_HIGHLIGHTTIME, iVal);
	SetDlgItemInt(IDC_STATIC_COFFTIME, m_pLPS->m_Properties.BaseTime()-iVal );

	if (m_pLPS->m_Properties.Cursor() & cTachistoscopicCursor ||
		m_pLPS->m_Properties.Cursor() & cSlowHandCursor)
	{
		iCOff = abs(m_pLPS->m_Properties.DisplayPeriod());
	}
	else
	{
		iCOff = abs(m_pLPS->m_Properties.BlackoutPeriod());
	}
	SetDlgItemInt(IDC_STATIC_COFFVALUE, iCOff);
}


/////////////////////////////////////////////////////////////////////////////
//
//			CPropPageConfiguration methods
//
/////////////////////////////////////////////////////////////////////////////

LRESULT CPropPageConfiguration::OnHelpCalled(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return m_pLPS->OnHelpCalled( uMsg,  wParam, lParam,  bHandled, m_hWnd, L"PropPageConfiguration" );
}

LRESULT CPropPageConfiguration::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATL_TRACE ("\n CPropPageConfiguration::OnInitDialog"); 
	m_Combobox.m_hWnd = GetDlgItem(IDC_COMBO_CURRENTSETTING);
	m_Combobox.SwitchMessageMap(1);

	m_RemoveButton.m_hWnd = GetDlgItem(IDC_REMOVECONFIGURATIONBUTTON); 
	m_RemoveButton.SwitchMessageMap(2); 

	m_AddButton.m_hWnd = GetDlgItem(IDC_ADDCONFIGURATIONBUTTON); 
	m_AddButton.SwitchMessageMap(3); 

	// PropInit Initialisation 
	Initialise(m_hWnd); 

	return TRUE;
}

BOOL CPropPageConfiguration::OnKillActive()
{
	ATL_TRACE ("\n CPropPageConfiguration::OnKillActive");
	KillActive(); 

	return TRUE;
}

BOOL CPropPageConfiguration::OnSetActive()
{
	ATL_TRACE ("\n CPropPageConfiguration::OnSetActive");
	m_bSetActive =  true;	
	
	if (m_pLPS->IsDirty())
	{
		m_Combobox.EnableWindow(FALSE); 
		m_AddButton.EnableWindow(FALSE); 
		m_RemoveButton.EnableWindow(FALSE); 
	}
	else 
	{
		m_Combobox.EnableWindow(TRUE); 
		m_AddButton.EnableWindow(TRUE); 
		m_RemoveButton.EnableWindow(TRUE); 
	}

	// Do not allow add config in demo mode. 
	if (2 == m_pLPS->m_lDemoMode)
	{
		m_RemoveButton.EnableWindow(FALSE);	
		m_AddButton.EnableWindow(FALSE);
	}

	m_Combobox.ResetContent();

	vector<CSettingStrings>::iterator it; 

	int iA = 0;

	wstring wstrDefault;
	USES_CONVERSION; 
	for (it = m_pLPS->m_vecstring.begin(); it != m_pLPS->m_vecstring.end(); it++)
	{		
		m_Combobox.AddString(OLE2T(it->m_wstrName.c_str()));
		iA++;
	}

	// This is due to unsloved sort problem on combobox- We should be able 
	// just to set it using m_iCurrentSetting
	m_Combobox.SetCurSel (m_Combobox.FindString(-1, OLE2T(m_pLPS->m_vecstring[m_pLPS->m_iCurrentSetting].m_wstrName.c_str())));
	
	SetDlgItemText(IDC_TEMPLATETYPE, OLE2T(m_pLPS->m_vecstring[m_pLPS->m_iCurrentSetting].m_wstrTemplateID.c_str())); 

	if (m_Combobox.GetCount() <= ciMinConfigs) m_RemoveButton.EnableWindow(FALSE); 
	
	if (m_Combobox.GetCount() >= ciMaxConfigs) m_AddButton.EnableWindow(FALSE); 

	SetDlgItemText(IDC_TEMPLATEDESCRIPTION_STATIC,	OLE2T(m_pLPS->m_vecstring[m_pLPS->m_iCurrentSetting].m_wstrDescription.c_str()));  

	eFIXWIDTHTYPE eFixWidthType = e_CHARS; 
	if	    ( m_pLPS->m_Properties.Cursor() & cLineDivisions)
	{
		eFixWidthType = e_COLUMNS; 
	}
	else if	 ( m_pLPS->m_Properties.Cursor() & cWordDivisions)
	{
		eFixWidthType = e_WORDS; 
	}
	SetDlgItemText(IDC_FIXWIDTHTYPE_STATIC,		   OLE2T(cawchFixWidthTypes			[eFixWidthType]));
	SetDlgItemText(IDC_FIXWIDTHDESCRIPTION_STATIC, OLE2T(cawchFixWidthDescriptions	[eFixWidthType]));

	m_bSetActive = false; 

	// CPropInit  SetActive 
	CPropInit::SetActive(); 
	return TRUE; 
}

LRESULT CPropPageConfiguration::OnComboChanged (int, int, HWND h, BOOL& bHandled)
{
	// If the combox has changed tell the property sheet about it. 
	BSTR bstrSel = NULL; 
	m_Combobox.GetLBTextBSTR (m_Combobox.GetCurSel(), bstrSel);
	int iLen = ::SysStringLen(bstrSel);

	if (m_pLPS->ChangeSel(bstrSel))
	{
		//SetModified(TRUE);
		OnSetActive(); 
	}

	::SysFreeString(bstrSel);


	return 1;
}

BOOL CPropPageConfiguration::OnApply	()
{
	m_pLPS->SetDefault(m_pLPS->m_iCurrentSetting);

	m_pLPS->Update();

	return TRUE;
}


LRESULT  CPropPageConfiguration::OnClickedAddbutton (WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	ATL_TRACE("\n CPropPageConfiguration::OnClickedAddbutton");

	CAddSettingDialog Add;

	Add.SetPropertySheet(m_pLPS); 
	if (IDOK == Add.DoModal())
	{
		m_pLPS->Initialise(0);
		OnSetActive();
	}

	return 0;
}

LRESULT CPropPageConfiguration::OnClickedRemovebutton(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	ATL_TRACE("\n CPropPageConfiguration::OnClickedRemovebutton");
	bHandled = TRUE;

	USES_CONVERSION; 
	if (m_Combobox.GetCount() <= 1)
	{
		MessageBox ("Cannot remove - only one Configuration remains on the system","Remove Configuration",MB_ICONWARNING); 
		return 0; 
	}

	if  (IDOK == MessageBox("Are you sure you want to completely remove this Configuration from the system?","Remove Configuration",MB_OKCANCEL | MB_ICONWARNING))
	{
		m_pLPS->RemoveCurrent();
		m_Combobox.SelectString(0,OLE2T(m_pLPS->m_vecstring[m_pLPS->m_iCurrentSetting].m_wstrName.c_str()));
		m_pLPS->SetDefault(0);
		OnSetActive();
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
//
//			CPropPageFixations methods
//
/////////////////////////////////////////////////////////////////////////////

LRESULT CPropPageFixations::OnChangeCursorheightorwidth	(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (wID == IDC_FIXATIONWIDTHEDIT)
	{
		int iFixationWidthEdit = GetDlgItemInt(IDC_FIXATIONWIDTHEDIT);

		if (iFixationWidthEdit > 0 &&
			iFixationWidthEdit != 	m_pLPS->m_Properties.CursorWidth())
		{
			m_pLPS->m_Properties.put_CursorWidth(GetDlgItemInt(IDC_FIXATIONWIDTHEDIT));
			if (!m_bSetActive) 
			{
				CPropInit::SetActive();
				SetModified(TRUE); 
			}
		}
	}
	else if (wID == IDC_FIXATIONHEIGHTEDIT)
	{
		int iFixationHeightEdit = GetDlgItemInt(IDC_FIXATIONHEIGHTEDIT);

		if (iFixationHeightEdit > 0 &&
			iFixationHeightEdit !=  m_pLPS->m_Properties.CursorHeight())
		{
			m_pLPS->m_Properties.put_CursorHeight(GetDlgItemInt(IDC_FIXATIONHEIGHTEDIT));
			if (!m_bSetActive) 
			{
				CPropInit::SetActive();
				SetModified(TRUE); 
			}
		}
	}

	if (wID == IDC_FIXATIONWIDTHEDIT)
	{
		if (m_pLPS->m_Properties.Cursor() & cLineDivisions) 
		{
			if (1 >= GetDlgItemInt(IDC_FIXATIONWIDTHEDIT))
			{
				SetDlgItemText (	IDC_STATIC_CURSORWIDTH, tchWidthText[1]);
			}
			else
			{
				SetDlgItemText (	IDC_STATIC_CURSORWIDTH, tchWidthText[2]);
			}
		}
	}
	
	return 0;
}

LRESULT CPropPageFixations::OnChangeSoundClick (WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	BOOL bChecked = FALSE;
	if (m_pLPS->m_Properties.Cursor() & cCursorSound)
	{
		bChecked = TRUE; 
	}
	if (m_SoundClickCheck.GetCheck() == BST_CHECKED && bChecked == FALSE)
	{
		m_pLPS->m_Properties.put_Cursor(m_pLPS->m_Properties.Cursor() | cCursorSound);
		if (!m_bSetActive) 
		{	
			CPropInit::SetActive();
			SetModified(TRUE); 
		}
	}
	else if (m_SoundClickCheck.GetCheck() == BST_UNCHECKED && bChecked == TRUE)
	{
		m_pLPS->m_Properties.put_Cursor(m_pLPS->m_Properties.Cursor() ^ cCursorSound);

		if (!m_bSetActive) 
		{	
			CPropInit::SetActive();
			SetModified(TRUE); 
		}
	}

	

	return 0; 
}


LRESULT CPropPageFixations::OnChangeLeaveCursorHighlighted (WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	BOOL bChecked = FALSE;
	if (m_pLPS->m_Properties.Cursor() & cLeaveCursorHighlighted)
	{
		bChecked = TRUE; 
	}
	if (m_LeaveCursorHighlightedCheck.GetCheck() == BST_CHECKED && bChecked == FALSE)
	{
		m_pLPS->m_Properties.put_Cursor(m_pLPS->m_Properties.Cursor() | cLeaveCursorHighlighted);
		if (!m_bSetActive) 
		{	
			CPropInit::SetActive();
			SetModified(TRUE); 
		}
	}
	else if (m_LeaveCursorHighlightedCheck.GetCheck() == BST_UNCHECKED && bChecked == TRUE)
	{
		m_pLPS->m_Properties.put_Cursor(m_pLPS->m_Properties.Cursor() ^ cLeaveCursorHighlighted);

		if (!m_bSetActive) 
		{	
			CPropInit::SetActive();
			SetModified(TRUE); 
		}
	}

	return 0; 
}

LRESULT CPropPageFixations::OnHelpCalled(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return m_pLPS->OnHelpCalled( uMsg,  wParam, lParam,  bHandled, m_hWnd, L"PropPageFixations");
}
 
LRESULT CPropPageFixations::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATL_TRACE ("\n CPropPageFixations::OnInitDialog"); 

	m_CursorWidthEdit.m_hWnd = GetDlgItem(IDC_FIXATIONWIDTHEDIT); 
	m_CursorWidthEdit.SwitchMessageMap(5); 

	m_CursorHeightEdit.m_hWnd  = GetDlgItem(IDC_FIXATIONHEIGHTEDIT); 
	m_CursorHeightEdit.SwitchMessageMap(6); 

	m_LeaveCursorHighlightedCheck.m_hWnd = GetDlgItem(IDC_LEAVEHIGHLIGHTEDCHECK);
	m_LeaveCursorHighlightedCheck.SwitchMessageMap(7); 

	m_SoundClickCheck.m_hWnd = GetDlgItem(IDC_SOUNDCLICKCHECK); 
	m_SoundClickCheck.SwitchMessageMap(8); 

	CPropInit::Initialise(m_hWnd);

	return TRUE;
}

BOOL CPropPageFixations::OnKillActive()
{
	ATL_TRACE ("\n CPropPageFixations::OnKillActive");

	int iFixationWidthEdit = GetDlgItemInt(IDC_FIXATIONWIDTHEDIT);
	int iFixationHeightEdit = GetDlgItemInt(IDC_FIXATIONHEIGHTEDIT);

	if (m_pLPS->m_Properties.Cursor() & cLineDivisions)
	{
		if (iFixationHeightEdit <= 0)
		{
			MessageBox("Fixation Height must be greater than 0", "Error", MB_OK);
			return FALSE;
		}
	}
	if (iFixationWidthEdit <= 0)
	{
		MessageBox("Fixation Width must be greater than 0", "Error", MB_OK);
		return FALSE;
	}

	CPropInit::KillActive(); 

	return TRUE;
}

BOOL CPropPageFixations::OnSetActive()
{
	ATL_TRACE ("\n CPropPageFixations::OnSetActive");
	m_bSetActive =  true;	
	
	SetDlgItemInt(	IDC_FIXATIONWIDTHEDIT, m_pLPS->m_Properties.CursorWidth());
	m_CursorWidthEdit.EnableWindow(TRUE);

	// Set up static text box explaining the width and height fields of the cursor 
	if (m_pLPS->m_Properties.Cursor() & cLineDivisions) 
	{
		if (1 == m_pLPS->m_Properties.CursorWidth())
		{
			SetDlgItemText (	IDC_STATIC_CURSORWIDTH, tchWidthText[1]);
		}
		else
		{
			SetDlgItemText (	IDC_STATIC_CURSORWIDTH, tchWidthText[2]);
		}
	}
	else if (m_pLPS->m_Properties.Cursor() & cCharDivisions) 
	{
		SetDlgItemText (	IDC_STATIC_CURSORWIDTH, tchWidthText[3]);
	}
	else if (m_pLPS->m_Properties.Cursor() & cWordDivisions) 
	{
		SetDlgItemText (	IDC_STATIC_CURSORWIDTH, tchWidthText[4]);
	}
	else
	{
		SetDlgItemText (	IDC_STATIC_CURSORWIDTH, tchWidthText[0]);
	}

	if (m_pLPS->m_Properties.Cursor() & cWordDivisions	|| 
		m_pLPS->m_Properties.Cursor() & cCharDivisions)
	{
		// Disable height box as multiple lines is not set 
		SetDlgItemInt(	IDC_FIXATIONHEIGHTEDIT, 1);
		m_CursorHeightEdit.EnableWindow(FALSE);
		SetDlgItemText(IDC_STATICROW, tchRowText[1]);
	}
	else
	{
		SetDlgItemInt(	IDC_FIXATIONHEIGHTEDIT, m_pLPS->m_Properties.CursorHeight());
		m_CursorHeightEdit.EnableWindow(TRUE);
		SetDlgItemText(IDC_STATICROW, tchRowText[2]);
	}

	if (m_pLPS->m_Properties.Cursor() & cRSVPCursor ||
		m_pLPS->m_Properties.Cursor() & cTachistoscopicCursor)
	{
		// Disable "leave cursor highlighted" flag for static and random cursors
		m_LeaveCursorHighlightedCheck.SetCheck(BST_UNCHECKED);
		m_LeaveCursorHighlightedCheck.EnableWindow(FALSE); 
		::EnableWindow(GetDlgItem(IDC_LEAVEHIGHLIGHTEDSTATIC),FALSE);
	}
	else
	{
		if (cLeaveCursorHighlighted & m_pLPS->m_Properties.Cursor() )
		{
			m_LeaveCursorHighlightedCheck.SetCheck(BST_CHECKED);
		}
		else
		{
			m_LeaveCursorHighlightedCheck.SetCheck(BST_UNCHECKED);
		}
		m_LeaveCursorHighlightedCheck.EnableWindow(TRUE); 
		::EnableWindow(GetDlgItem(IDC_LEAVEHIGHLIGHTEDSTATIC), TRUE);
	}


	if (cCursorSound & m_pLPS->m_Properties.Cursor() )
	{
		m_SoundClickCheck.SetCheck(BST_CHECKED);
	}
	else
	{
		m_SoundClickCheck.SetCheck(BST_UNCHECKED);
	}

	m_bSetActive = false; 

	CPropInit::SetActive(); 

	return TRUE; 
}


///////////////////////////////////////////////////////////////////////////////
//
//			CWinBlitPropertySheet methods
//
///////////////////////////////////////////////////////////////////////////

CWinBlitPropertySheet::CWinBlitPropertySheet()
{
	//m_psh.dwFlags |= PSH_NOAPPLYNOW;
	AddPage(m_PageConfiguration);
	m_PageConfiguration.SetPropertySheet(this); 
	AddPage(m_PageFixations);
	m_PageFixations.SetPropertySheet(this); 
	AddPage(m_PageDisplay);
	m_PageDisplay.SetPropertySheet(this);
	AddPage(m_PageSpeed);
	m_PageSpeed.SetPropertySheet(this); 
	AddPage(m_PageRules);
	m_PageRules.SetPropertySheet(this); 
	AddPage(m_PageGeneral);
	m_PageGeneral.SetPropertySheet(this); 

	SetActivePage(0);
	SetTitle(_T("WinBlit Configuration"));
	m_bIsDirty = false; 
	m_bWasDirty = false; 
	m_bClearStatsRequired = false; 
}

void CWinBlitPropertySheet::Initialise(long lDemoMode)
{
	ATL_TRACE ("CWinBlitPropertySheet::Initialise");
	m_WinBlitRegistry.GetAllSettings(m_vecstring); 

	wstring wstrDefaultName; 
	if (0 != m_WinBlitRegistry.GetDefaultName(wstrDefaultName))
	{
		// If no default set up then use the first setting 
		m_WinBlitRegistry.SetDefaultName(m_vecstring[0].m_wstrName);
	}

	vector<CSettingStrings>::iterator it;

	m_iCurrentSetting = 0; 
	int iA = 0;

	LPSTR pszSetting = NULL;

	for (it = m_vecstring.begin(); it != m_vecstring.end(); ++it, iA++)
	{
		if (wstrDefaultName == (*it).m_wstrName)
		{
			m_iCurrentSetting = iA;
		}
	}	
	// Load Default setting unless supplied with a name of a setting to load 
	CComBSTR bstrLoad(wstrDefaultName.c_str());

	m_WinBlitRegistry.LoadSettings(bstrLoad, &m_Properties);

	m_lDemoMode = lDemoMode; 
}

BOOL CWinBlitPropertySheet::Update() 
{
	if (m_bIsDirty)
	{
		CComBSTR bstrSetting(m_vecstring[m_iCurrentSetting].m_wstrName.c_str());
		m_WinBlitRegistry.SaveSettings(bstrSetting, &m_Properties); 
		m_bIsDirty = false;
		m_bWasDirty = true; 
	}
	return TRUE;
}

BOOL CWinBlitPropertySheet::ChangeSel(BSTR bstrSel) 
{
	BOOL bRet = FALSE; 

	vector<CSettingStrings>::iterator vit;
	int iCurrentSetting = 0;

	for (vit = m_vecstring.begin(); vit != m_vecstring.end(); vit++)
	{
		if (wcscmp( vit->m_wstrName.c_str(), bstrSel ) == 0)
		{
			iCurrentSetting = distance(m_vecstring.begin(), vit);
		}
	}
	if (m_iCurrentSetting != iCurrentSetting)
	{
		m_iCurrentSetting = iCurrentSetting; 
		CComBSTR bstrSetting(m_vecstring[iCurrentSetting].m_wstrName.c_str());
		// Load settings for new selection. 
		m_WinBlitRegistry.LoadSettings(bstrSetting, &m_Properties);
	}

	return TRUE;
}

BOOL CWinBlitPropertySheet::SetDefault (int iSel) 
{
	m_WinBlitRegistry.SetDefaultName(m_vecstring[iSel].m_wstrName);

	return TRUE;
}

BOOL CWinBlitPropertySheet::RemoveCurrent() 
{
	CComBSTR bstrRemove; 
	bstrRemove.Append (m_vecstring[m_iCurrentSetting].m_wstrName.c_str());
	m_WinBlitRegistry.RemoveSettings(bstrRemove);

	Initialise(0);

	return TRUE;
}

CWinBlitPropertySheet::~CWinBlitPropertySheet()
{
	ATLTRACE ("\n CWinBlitPropertySheet::~CWinBlitPropertySheet()");
	// Move focus back to the main window. 
}

LRESULT CWinBlitPropertySheet::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATL_TRACE0 (e_LOGDETAIL, "\n CWinBlitPropertySheet::OnKillFocus");

	HWND hWnd = ::GetParent(m_hWnd); 
	::SendMessage(hWnd,uMsg, wParam, lParam);
	ATL_TRACE0 (e_LOGDETAIL," Lost focus in Property sheet");

	return 0;
}

LRESULT CWinBlitPropertySheet::OnHelpCalled(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled, HWND hWndDialog, WCHAR* pwchDialog )
{
	ATL_TRACE ("\n  CPropPageConfiguration::OnHelp");

	if (2 != m_lDemoMode)
	{

		USES_CONVERSION; 
		CComBSTR bstrPath(*(m_Properties.HelpPath()));

		if (2 == m_Properties.HelpType())
		{
			CComBSTR bstrHelpPath(bstrPath); 

			for (int iA = 0; iA  < ciDialogCount; iA++)
			{
				if (0 == wcscmp(pwchDialog,	cawchDialogs[iA]))
				{
					bstrHelpPath.Append(cawchHelpPaths[iA]); 
				}
			}

			HWND hWnd = ::GetDlgItem(hWndDialog,  ((LPHELPINFO) lParam)->dwContextId);
			::HtmlHelp(    NULL,      NULL,       HH_CLOSE_ALL,   0) ;
			::HtmlHelp(hWnd, OLE2T(bstrHelpPath), HH_DISPLAY_TOPIC, 0);
		}
		else 
		{
			WinHelp(OLE2T(bstrPath), HELP_CONTEXT, ((LPHELPINFO) lParam)->dwContextId); 
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//
//			CPropInit methods
//
///////////////////////////////////////////////////////////////////////////

static const CComBSTR bstrWinBlit ("WinBlitReaderManager.WinBlitReader.1");

void CPropInit::Initialise(HWND hWnd)
{
	m_wndView.m_hWnd = GetDlgItem(hWnd,IDC_STATIC_WINBLIT); 
	m_wndView.CreateControl(bstrWinBlit,NULL, NULL);
	m_wndView.QueryControl(IID_IWinBlitReader, (void**) &m_WinBlitReader);

	m_PreviewStartButton.m_hWnd = GetDlgItem(hWnd,IDC_PREVIEWSTART_BUTTON); 
	m_PreviewStartButton.SetBitmap(::LoadBitmap(_Module.m_hInst, MAKEINTRESOURCE(IDB_PREVIEW_START))); 

	m_PreviewStopButton.m_hWnd = GetDlgItem(hWnd,IDC_PREVIEWSTOP_BUTTON); 
	m_PreviewStopButton.SetBitmap(::LoadBitmap(_Module.m_hInst, MAKEINTRESOURCE(IDB_PREVIEW_STOP)));
}

void CPropInit::SetActive (bool bRedisplay)
{
	CComBSTR bstrSetting(m_pLPS->m_vecstring[m_pLPS->m_iCurrentSetting].m_wstrName.c_str());

	CComPtr<CWinBlitReader> pWinBlitReader;
	if (SUCCEEDED(m_WinBlitReader->QueryInterface(CLSID_WinBlitReader, (void **)&pWinBlitReader)))
	{
		pWinBlitReader->LoadSettings(bstrSetting, 0); 

		pWinBlitReader->ShowStatusBar	(FALSE);
		pWinBlitReader->ShowMetafile	(FALSE);
		pWinBlitReader->ShowTrackBar	(FALSE);
		pWinBlitReader->ShowControls	(FALSE);

		pWinBlitReader->put_HighlightPeriod	(m_pLPS->m_Properties.HighlightPeriod());
		pWinBlitReader->put_BaseTime		(m_pLPS->m_Properties.BaseTime());
		pWinBlitReader->put_Cursor			(m_pLPS->m_Properties.Cursor());
		pWinBlitReader->put_CursorHeight	(m_pLPS->m_Properties.CursorHeight());
		pWinBlitReader->put_CursorWidth		(m_pLPS->m_Properties.CursorWidth());
		pWinBlitReader->put_ScreenBackColor	(m_pLPS->m_Properties.ScreenBackColor());
		pWinBlitReader->put_ScreenFillColor	(m_pLPS->m_Properties.ScreenFillColor());
		pWinBlitReader->put_ScreenTextColor	(m_pLPS->m_Properties.ScreenTextColor());
		CComPtr<IFontDisp> pTextFontDisp; 
		m_pLPS->m_Properties.get_TextFont(&pTextFontDisp);
		pWinBlitReader->put_TextFont		(pTextFontDisp);
		pWinBlitReader->put_BlackoutPeriod	(m_pLPS->m_Properties.BlackoutPeriod());
		pWinBlitReader->put_DisplayPeriod	(m_pLPS->m_Properties.DisplayPeriod());
		pWinBlitReader->put_CursorFillColor	(m_pLPS->m_Properties.CursorFillColor());
		pWinBlitReader->put_CursorTextColor	(m_pLPS->m_Properties.CursorTextColor());
		pWinBlitReader->put_SDKMode			(TRUE); 
		pWinBlitReader->put_DemoMode		(1); 

		if (bRedisplay)
		{
			CComVariant varData (L" aaaa bbbb cccc dddd eeee ffff gggg hhhh iiii jjjj kkkk llll mmmm nnnn oooo pppp qqqq rrrr ssss tttt uuuu vvvv wwww xxxx yyyy zzzz");
			pWinBlitReader->Stop(); 
			pWinBlitReader->UnloadData(); 

			pWinBlitReader->LoadData(1000, varData); 
			pWinBlitReader->Display(); 
		}
	}
}

void CPropInit::KillActive ()
{
	CComPtr<CWinBlitReader> pWinBlitReader;
	if (SUCCEEDED(m_WinBlitReader->QueryInterface(CLSID_WinBlitReader, (void **)&pWinBlitReader)))
	{
		pWinBlitReader->Stop(); 
		pWinBlitReader->UnloadData(); 
	}
}

void CPropInit::PreviewClicked (WORD wID)
{
	CComPtr<CWinBlitReader> pWinBlitReader;
	if (SUCCEEDED(m_WinBlitReader->QueryInterface(CLSID_WinBlitReader, (void **)&pWinBlitReader)))
	{
		if (wID == IDC_PREVIEWSTART_BUTTON)
		{
			pWinBlitReader->Stop(); 
			pWinBlitReader->Start(); 
		}
		else if (wID == IDC_PREVIEWSTOP_BUTTON)
		{
			pWinBlitReader->Stop(); 
		}
	}
}



///////////////////////////////////////////////////////////////////////////////
//
//			CPropPageGeneral methods
//
///////////////////////////////////////////////////////////////////////////


LRESULT CPropPageGeneral::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_BlitPadCheck.m_hWnd = GetDlgItem(IDC_AUTOSTART_BLITPADCHECK);
	m_IECheck.m_hWnd = GetDlgItem(IDC_AUTOSTART_IECHECK);
	m_OutlookCheck.m_hWnd = GetDlgItem(IDC_AUTOSTART_OUTLOOKCHECK);
	m_WordCheck.m_hWnd = GetDlgItem(IDC_AUTOSTART_WORDCHECK);

	m_ShowMetafile.m_hWnd = GetDlgItem(IDC_SHOWMETAFILECHECK);
	m_ShowToolBar.m_hWnd = GetDlgItem(IDC_SHOWTOOLBARCHECK);
	m_ShowTrackBar.m_hWnd = GetDlgItem(IDC_SHOWTRACKBARCHECK);
	m_ShowStatusBar.m_hWnd = GetDlgItem(IDC_SHOWSTATUSBARCHECK);

	m_ClearStatistics.m_hWnd = GetDlgItem(IDC_CLEARSTATISTICS); 
	
	return TRUE;
}

BOOL CPropPageGeneral::OnSetActive ()
{
	m_bSetActive = true;

	if (m_pLPS->m_bClearStatsRequired)
	{
		m_ClearStatistics.EnableWindow(FALSE);
	}
	else
	{
		m_ClearStatistics.EnableWindow(TRUE);
	}

	
	if (cAutoStartIE & m_pLPS->m_Properties.Cursor() )
	{
		m_IECheck.SetCheck(BST_CHECKED);
	}
	else
	{
		m_IECheck.SetCheck(BST_UNCHECKED);
	}

	if (cAutoStartWord & m_pLPS->m_Properties.Cursor() )
	{
		m_WordCheck.SetCheck(BST_CHECKED);
	}
	else
	{
		m_WordCheck.SetCheck(BST_UNCHECKED);
	}

	if (cAutoStartOutlook & m_pLPS->m_Properties.Cursor() )
	{
		m_OutlookCheck.SetCheck(BST_CHECKED);
	}
	else
	{
		m_OutlookCheck.SetCheck(BST_UNCHECKED);
	}

	if (cAutoStartBlitPad & m_pLPS->m_Properties.Cursor() )
	{
		m_BlitPadCheck.SetCheck(BST_CHECKED);
	}
	else
	{
		m_BlitPadCheck.SetCheck(BST_UNCHECKED);
	}

	BOOL bShowControls; 
	m_pLPS->m_Properties.get_ShowControls(&bShowControls);

	if (TRUE == bShowControls)
	{
		m_ShowToolBar.SetCheck(BST_CHECKED);
	}
	else
	{
		m_ShowToolBar.SetCheck(BST_UNCHECKED);
	}

	BOOL bShowTrackBar; 
	m_pLPS->m_Properties.get_ShowTrackBar(&bShowTrackBar);

	if (TRUE == bShowTrackBar)
	{
		m_ShowTrackBar.SetCheck(BST_CHECKED);
	}
	else
	{
		m_ShowTrackBar.SetCheck(BST_UNCHECKED);
	}


	if (cRSVPCursor & m_pLPS->m_Properties.Cursor())
	{
		m_ShowMetafile.EnableWindow(TRUE)	; 

		BOOL bShowMetafile; 
		m_pLPS->m_Properties.get_ShowMetafile(&bShowMetafile);

		if (TRUE == bShowMetafile)
		{
			m_ShowMetafile.SetCheck(BST_CHECKED);
		}
		else
		{
			m_ShowMetafile.SetCheck(BST_UNCHECKED);
		}
		::EnableWindow(GetDlgItem(IDC_SHOWMETAFILESTATIC),TRUE);	
	}
	else
	{
		m_ShowMetafile.SetCheck(BST_UNCHECKED);
		m_ShowMetafile.EnableWindow(FALSE); 
		::EnableWindow(GetDlgItem(IDC_SHOWMETAFILESTATIC),FALSE);	
	}

	BOOL bShowStatusBar; 
	m_pLPS->m_Properties.get_ShowStatusBar(&bShowStatusBar);

	if (TRUE == bShowStatusBar)
	{
		m_ShowStatusBar.SetCheck(BST_CHECKED);
	}
	else
	{
		m_ShowStatusBar.SetCheck(BST_UNCHECKED);
	}

	m_bSetActive = false; 

	
	return TRUE;
}

BOOL CPropPageGeneral::OnKillActive	()
{
	return TRUE;
}

LRESULT CPropPageGeneral::OnHelpCalled(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return m_pLPS->OnHelpCalled( uMsg,  wParam, lParam,  bHandled, m_hWnd, L"PropPageGeneral");
}

LRESULT CPropPageGeneral::OnAutoStartCheck (WORD wNotifyCode, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	BOOL bChecked = FALSE;
	
	if (wID == IDC_AUTOSTART_IECHECK)
	{
		if (m_pLPS->m_Properties.Cursor() & cAutoStartIE)
		{
			bChecked = TRUE; 
		}
		if (m_IECheck.GetCheck() == BST_CHECKED && bChecked == FALSE)
		{
			m_pLPS->m_Properties.put_Cursor(m_pLPS->m_Properties.Cursor() | cAutoStartIE);

			if (!m_bSetActive) 	SetModified(TRUE); 		
		}
		else if (m_IECheck.GetCheck() == BST_UNCHECKED && bChecked == TRUE)
		{
			m_pLPS->m_Properties.put_Cursor(m_pLPS->m_Properties.Cursor() ^ cAutoStartIE);

			if (!m_bSetActive) 	SetModified(TRUE); 
		}
	}
	else if (wID == IDC_AUTOSTART_BLITPADCHECK)
	{
		if (m_pLPS->m_Properties.Cursor() & cAutoStartBlitPad)
		{
			bChecked = TRUE; 
		}
		if (m_BlitPadCheck.GetCheck() == BST_CHECKED && bChecked == FALSE)
		{
			m_pLPS->m_Properties.put_Cursor(m_pLPS->m_Properties.Cursor() | cAutoStartBlitPad);

			if (!m_bSetActive) 	SetModified(TRUE); 		
		}
		else if (m_BlitPadCheck.GetCheck() == BST_UNCHECKED && bChecked == TRUE)
		{
			m_pLPS->m_Properties.put_Cursor(m_pLPS->m_Properties.Cursor() ^ cAutoStartBlitPad);

			if (!m_bSetActive) 	SetModified(TRUE); 
		}
	}
	else if (wID == IDC_AUTOSTART_WORDCHECK)
	{
		if (m_pLPS->m_Properties.Cursor() & cAutoStartWord)
		{
			bChecked = TRUE; 
		}
		if (m_WordCheck.GetCheck() == BST_CHECKED && bChecked == FALSE)
		{
			m_pLPS->m_Properties.put_Cursor(m_pLPS->m_Properties.Cursor() | cAutoStartWord);

			if (!m_bSetActive) 	SetModified(TRUE); 		
		}
		else if (m_WordCheck.GetCheck() == BST_UNCHECKED && bChecked == TRUE)
		{
			m_pLPS->m_Properties.put_Cursor(m_pLPS->m_Properties.Cursor() ^ cAutoStartWord);

			if (!m_bSetActive) 	SetModified(TRUE); 
		}
	}
	else if (wID == IDC_AUTOSTART_OUTLOOKCHECK)
	{
		if (m_pLPS->m_Properties.Cursor() & cAutoStartOutlook)
		{
			bChecked = TRUE; 
		}
		if (m_OutlookCheck.GetCheck() == BST_CHECKED && bChecked == FALSE)
		{
			m_pLPS->m_Properties.put_Cursor(m_pLPS->m_Properties.Cursor() | cAutoStartOutlook);

			if (!m_bSetActive) 	SetModified(TRUE); 		
		}
		else if (m_OutlookCheck.GetCheck() == BST_UNCHECKED && bChecked == TRUE)
		{
			m_pLPS->m_Properties.put_Cursor(m_pLPS->m_Properties.Cursor() ^ cAutoStartOutlook);

			if (!m_bSetActive) 	SetModified(TRUE); 
		}
	}

	return 0; 
}

LRESULT CPropPageGeneral::OnClickedClearStatistics(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_pLPS->m_bClearStatsRequired = true;
	MessageBox("Speed reading statistics will be cleared when the Configuration dialog box is closed","Clear Satistics",MB_ICONWARNING);

	m_ClearStatistics.EnableWindow(FALSE); 
	return 0;
}


LRESULT CPropPageGeneral::OnDisplayCheck (WORD wNotifyCode, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if		(wID == IDC_SHOWSTATUSBARCHECK)
	{
		BOOL bShowStatusBar; 
		m_pLPS->m_Properties.get_ShowStatusBar(&bShowStatusBar);

		if (!m_ShowStatusBar.GetCheck() && bShowStatusBar == TRUE)
		{
			m_pLPS->m_Properties.put_ShowStatusBar(FALSE); 
			if (!m_bSetActive) 	SetModified(TRUE); 		
		}
		else if (m_ShowStatusBar.GetCheck() && bShowStatusBar == FALSE)
		{
			m_pLPS->m_Properties.put_ShowStatusBar(TRUE); 
			if (!m_bSetActive) 	SetModified(TRUE); 
		}
	}
	else if (wID == IDC_SHOWMETAFILECHECK)
	{
		BOOL bShowMetafile; 
		m_pLPS->m_Properties.get_ShowMetafile(&bShowMetafile);

		if (!m_ShowMetafile.GetCheck() && bShowMetafile == TRUE)
		{
			m_pLPS->m_Properties.put_ShowMetafile(FALSE); 
			if (!m_bSetActive) 	SetModified(TRUE); 		
		}
		else if (m_ShowMetafile.GetCheck() && bShowMetafile == FALSE)
		{
			m_pLPS->m_Properties.put_ShowMetafile(TRUE); 
			if (!m_bSetActive) 	SetModified(TRUE); 
		}
	}
	else if (wID == IDC_SHOWTRACKBARCHECK)
	{
		BOOL bShowTrackBar; 
		m_pLPS->m_Properties.get_ShowTrackBar(&bShowTrackBar);

		if (!m_ShowTrackBar.GetCheck() && bShowTrackBar == TRUE)
		{
			m_pLPS->m_Properties.put_ShowTrackBar(FALSE); 
			if (!m_bSetActive) 	SetModified(TRUE); 		
		}
		else if (m_ShowTrackBar.GetCheck() && bShowTrackBar == FALSE)
		{
			m_pLPS->m_Properties.put_ShowTrackBar(TRUE); 
			if (!m_bSetActive) 	SetModified(TRUE); 
		}
	}
	else if (wID == IDC_SHOWTOOLBARCHECK)
	{
		BOOL bShowToolBar; 
		m_pLPS->m_Properties.get_ShowControls(&bShowToolBar);

		if (!m_ShowToolBar.GetCheck() && bShowToolBar == TRUE)
		{
			m_pLPS->m_Properties.put_ShowControls(FALSE); 
			if (!m_bSetActive) 	SetModified(TRUE); 		
		}
		else if (m_ShowToolBar.GetCheck() && bShowToolBar == FALSE)
		{
			m_pLPS->m_Properties.put_ShowControls(TRUE); 
			if (!m_bSetActive) 	SetModified(TRUE); 
		}
	}
	return 0;
}