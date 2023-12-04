//***************************************************************************
//*
//*		Name		: WinBlitRegistry.cpp
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
//*		Handles all WinBlit's interaction with the system registry
//* 
//*
//***************************************************************************
//***************************************************************************
//***************************************************************************
//*		H I S T O R Y
//***************************************************************************
/*
$Log:$*/
// WinBlitRegistry.cpp: implementation of the CWinBlitRegistry class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WinBlitRegistry.h"
#include "Registry.h"
#include "WinBlitReaderManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWinBlitRegistry::CWinBlitRegistry() 
{
}

CWinBlitRegistry::~CWinBlitRegistry()
{

}

//===========================================================================
//
//	Method :	:	LoadSettings 
//
//	Description :	For a given config of template name load settings from registry 
//					and set up the values supplied WinBlitProperties object 
//
//	Returns :		0 for success
//					-1 if error (registry key does not exist)
//
//===========================================================================

int CWinBlitRegistry::LoadSettings(BSTR bstrKey,					// Setting name 
								  CWinBlitProperties* pProp,		// Pointer to WinBlitProperties object 
								  int iKeyType,					// 0 = Configuration, 1 = template 
								  bool bBasicDetailsOnly)		
{
	int iRet = 0;
	ATL_TRACE0 (e_LOGDETAIL, "\n CWinBlitRegistry::LoadSettings");

	CRegistry Reg;
	Reg.SetRootKey(HKEY_LOCAL_MACHINE);
	
	CComBSTR bstrCurrentValue; 

	CComBSTR bstrWinBlitKey = cbstrWinBlitKey [iKeyType];

	CComBSTR bstrConfigHTMLTagsAllowed; 
	CComBSTR bstrConfigHTMLTagsBarred; 
	{
		// Set up the HTML tags from the Configurations. 
		CRegistry RegCurrent; 
		RegCurrent.SetRootKey(HKEY_LOCAL_MACHINE);
		USES_CONVERSION; 
		if (RegCurrent.SetKey (OLE2T(cbstrWinBlitKey [iKeyType]), FALSE))
		{
			RegCurrent.ReadString(OLE2T(cbstrDefault), &bstrCurrentValue.m_str);
			if (!RegCurrent.ReadString("HTMLTagsAllowed", &bstrConfigHTMLTagsAllowed))
			{
				bstrConfigHTMLTagsAllowed = "<*>"; 
			}
			if (!RegCurrent.ReadString("HTMLTagsBarred", &bstrConfigHTMLTagsBarred))
			{
				bstrConfigHTMLTagsBarred = ""; 
			}
			RegCurrent.ReadInt("HelpType",			pProp->m_lHelpType);
			RegCurrent.ReadString("DemoPath",		&pProp->m_bstrDemoPath);
			RegCurrent.ReadString("HelpPath",		&pProp->m_bstrHelpPath);
			RegCurrent.ReadString("HelpStartPage",	&pProp->m_bstrHelpStartPage);
			RegCurrent.ReadString("HelpContextPage",&pProp->m_bstrHelpContextPage);
		}
	}

	if (NULL == bstrKey)
	{
		// No Key specified - use the default
		USES_CONVERSION; 
		bstrWinBlitKey.Append(bstrCurrentValue);
		pProp->m_bstrName = bstrCurrentValue; 		
	}
	else
	{
		bstrWinBlitKey.AppendBSTR(bstrKey);
		pProp->m_bstrName = bstrKey; 
	}

	CComBSTR bstrWinBlitKeySettings = bstrWinBlitKey;
	bstrWinBlitKeySettings.Append(cbstrSettings);
	USES_CONVERSION; 

	// Clear all exisitng settings 
	CComPtr<IDispatch> pDispatch; 
	CComQIPtr<ISettings> pSettings; 

	HRESULT hr = pProp->get_Settings(&pDispatch); 
	if (S_OK == hr)
	{
		pSettings = pDispatch; 
		if (pSettings.p)
		{
			pSettings->Clear();
		}
	}


	if (Reg.SetKey (OLE2T(bstrWinBlitKey), FALSE))
	{
		FONTDESC lf; 
		
		// If this is a template take the template ID as the name of the template
		// otherwise it is a property in the registry.
		if (1 == iKeyType)
		{
			pProp->m_bstrTemplateID = bstrKey; 
		}
		else
		{
			Reg.ReadString  ("TemplateID",	&pProp->m_bstrTemplateID); 		
		}

		Reg.ReadString("Description",	&pProp->m_bstrDescription); 		

		if (false == bBasicDetailsOnly) 
		{
			Reg.ReadInt  ("TextFontSizeHi",		lf.cySize.Hi);
			Reg.ReadInt ("TextFontSizeLo",		lf.cySize.Lo);
			Reg.ReadInt ("TextFontWeight",		lf.sWeight);
			Reg.ReadInt ("TextFontCharset",		lf.sCharset);
			Reg.ReadBool  ("TextFontItalic",		lf.fItalic);
			Reg.ReadBool  ("TextFontUnderline",		lf.fUnderline);
			Reg.ReadBool  ("TextFontStrikethru",	lf.fStrikethrough);
			Reg.ReadString  ("TextFontName",			&lf.lpstrName);

			if (pProp->m_pTextFont) pProp->m_pTextFont.Release(); 
			OleCreateFontIndirect(&lf, IID_IFontDisp, (void**)&pProp->m_pTextFont);

			if (!Reg.ReadString  ("HTMLTagsAllowed",		&pProp->m_bstrHTMLTagsAllowed))
			{
				pProp->m_bstrHTMLTagsAllowed = bstrConfigHTMLTagsAllowed; 
			}
			if (!Reg.ReadString  ("HTMLTagsBarred",		&pProp->m_bstrHTMLTagsBarred))
			{
				pProp->m_bstrHTMLTagsBarred = bstrConfigHTMLTagsBarred; 
			}
			Reg.ReadInt("ScreenBackColor",pProp->m_clrScreenBackColor);
			Reg.ReadInt("ScreenFillColor",pProp->m_clrScreenFillColor);
			Reg.ReadInt("ScreenTextColor",pProp->m_clrScreenTextColor);
			Reg.ReadInt("CursorFillColor",pProp->m_clrCursorFillColor);
			Reg.ReadInt("CursorTextColor",pProp->m_clrCursorTextColor);

			Reg.ReadInt("DisplayPeriod",	pProp->m_lDisplayPeriod);
			Reg.ReadInt("BlackoutPeriod",	pProp->m_lBlackoutPeriod);
			Reg.ReadInt("HighlightPeriod",	pProp->m_lHighlightPeriod);
			Reg.ReadInt("Cursor",			pProp->m_lCursor);
			Reg.ReadInt("CursorWidth",		pProp->m_lCursorWidth);
			Reg.ReadInt("CursorHeight",		pProp->m_lCursorHeight);
			Reg.ReadInt("BaseTime",			pProp->m_lBaseTime);
			Reg.ReadInt("Top",				pProp->m_lTop);
			Reg.ReadInt("Bottom",			pProp->m_lBottom);
			Reg.ReadInt("Right",			pProp->m_lRight);
			Reg.ReadInt("Left",				pProp->m_lLeft);

			BOOL bShowMetafile = FALSE, 
				 bShowControls = FALSE, 
				 bShowTrackBar = FALSE, 
				 bShowStatusBar = FALSE;

			Reg.ReadInt("LogLevel",		pProp->m_lLogLevel);

			if (  (!Reg.ReadBool("ShowTrackBar",	bShowTrackBar)) ||
				  (TRUE == bShowTrackBar) )
			{
				pProp->m_bShowTrackBar = true;
			}
			else
			{
				pProp->m_bShowTrackBar = false;
			}

			if ( (!Reg.ReadBool("ShowControls",	bShowControls)) ||
				 (TRUE == bShowControls) )
			{
				pProp->m_bShowControls = true;
			}
			else
			{
				pProp->m_bShowControls = false;
			}

			if ( (!Reg.ReadBool("ShowStatusBar",	bShowStatusBar)) ||
				 (TRUE == bShowStatusBar) )
			{
				pProp->m_bShowStatusBar = true;
			}
			else
			{
				pProp->m_bShowStatusBar = false;
			}

			// Intialise Trackbar to true for static cursors if the 
			// property does not exist - i.e  if readbool returns false
			if (!Reg.ReadBool("ShowMetafile",	bShowMetafile))
			{			
				if (cRSVPCursor & pProp->m_lCursor)
				{		
					bShowMetafile = true;	
				}		
			}			
			(bShowMetafile == FALSE) ? pProp->m_bShowMetafile = false: pProp->m_bShowMetafile = true;

			if (pSettings.p)
			{
				// Is there a Settings collection? 
				if (Reg.SetKey (OLE2T(bstrWinBlitKeySettings), FALSE))
				{
					CHAR chSetting [512];
					chSetting[0] = '\0';
					int iA = 1;
					USES_CONVERSION;
					wsprintf (chSetting, "%s\\%d",OLE2T(bstrWinBlitKeySettings.m_str), iA);

					ATL_TRACE2(e_LOGDETAIL, "\n string length %s %d",chSetting,  strlen(chSetting));
					
					while (	Reg.SetKey (chSetting, FALSE)	)
					{
						BSTR bstrKey;
						BSTR bstrValue;
						long lPeriod = 0;
						long lRule = 0;
					
						Reg.ReadInt	("Period",		lPeriod);
						Reg.ReadInt	("Rule",		lRule);
						Reg.ReadString("Value",		&bstrValue);	
						Reg.ReadString("Name",		&bstrKey);
					
						pSettings->Add(bstrKey, 0, lRule, bstrValue, lPeriod);
					
						::SysFreeString(bstrKey);
						::SysFreeString(bstrValue);
						
						iA++;
						wsprintf (chSetting, "%s\\%d",OLE2T(bstrWinBlitKeySettings), iA);
					}					
				}	
			}
			if ( Reg.SetKey (OLE2T(cbstrWinBlitKey [iKeyType]), FALSE))
			{
			}
		}
	}
	else 
	{
		iRet = -1;
	}
	ATL_TRACE0 (e_LOGDETAIL, "\n CWinBlitRegistry::LoadSettings returns ");

	return iRet; 
}

//===========================================================================
//
//	Method :	:	SaveSettings 
//
//	Description :	For a given config or template name save settings to the  registry 
//					for a given WinBlitProperties object 
//
//	Returns :		0 for success
//					-1 if error (could not create registry key)
//
//===========================================================================

int CWinBlitRegistry::SaveSettings(	BSTR bstrKey,				// Config or template name
									CWinBlitProperties* pProp,	// Pointer to properties object 
									int iKeyType)				// 0 = Config or template 
{
	CRegistry Reg;
	Reg.SetRootKey(HKEY_LOCAL_MACHINE);

	CComBSTR bstrCurrentKey; 
	CComBSTR bstrWinBlitKey = cbstrWinBlitKey [iKeyType];
	bstrWinBlitKey.AppendBSTR(bstrKey);
	bstrCurrentKey = bstrKey;

	CComBSTR bstrWinBlitKeySettings = bstrWinBlitKey;
	bstrWinBlitKeySettings.Append(cbstrSettings);
	USES_CONVERSION; 

	if (Reg.SetKey (OLE2T(bstrWinBlitKey), TRUE))
	{
		CComDispatchDriver pDispDriver(pProp->m_pTextFont);
		
		CComVariant cvarSize; 
		pDispDriver.GetPropertyByName ( L"Size", &cvarSize);
		Reg.WriteInt ("TextFontSizeHi",  cvarSize.cyVal.Hi);
		Reg.WriteInt ("TextFontSizeLo",  cvarSize.cyVal.Lo);
		
		CComVariant cvarCharset; 
		pDispDriver.GetPropertyByName( L"Charset", &cvarCharset);
		Reg.WriteInt ("TextFontCharset",	cvarCharset.lVal);

		CComVariant cvarWeight; 
		pDispDriver.GetPropertyByName( L"Weight", &cvarWeight);
		Reg.WriteInt ("TextFontWeight",	cvarWeight.lVal);

		CComVariant cvarItalic; 
		pDispDriver.GetPropertyByName( L"Italic", &cvarItalic);
		Reg.WriteInt ("TextFontItalic",	cvarItalic.boolVal);

		CComVariant cvarStrikethrough; 
		pDispDriver.GetPropertyByName( L"Strikethrough", &cvarStrikethrough);
		Reg.WriteBool("TextFontStrikethrough",	cvarWeight.boolVal);

		CComVariant cvarUnderline; 
		pDispDriver.GetPropertyByName( L"Underline", &cvarUnderline);
		Reg.WriteBool("TextFontUnderline",	cvarUnderline.boolVal);
		
		CComVariant cvarName;
		pDispDriver.GetPropertyByName( L"Name", &cvarName);
		USES_CONVERSION;
		Reg.WriteString("TextFontName", cvarName.bstrVal,::SysStringLen(cvarName.bstrVal));
		::SysFreeString(cvarName.bstrVal);

		if (0 == iKeyType)
		{
			// Only write away if config 
			Reg.WriteString  ("TemplateID",			pProp->m_bstrTemplateID,	pProp->m_bstrTemplateID.Length()); 
		}
		Reg.WriteString  ("Description",		pProp->m_bstrDescription,	pProp->m_bstrDescription.Length()); 

		Reg.WriteInt("ScreenBackColor",pProp->m_clrScreenBackColor);
		Reg.WriteInt("ScreenFillColor",pProp->m_clrScreenFillColor);
		Reg.WriteInt("ScreenTextColor",pProp->m_clrScreenTextColor);
		Reg.WriteInt("CursorFillColor",pProp->m_clrCursorFillColor);
		Reg.WriteInt("CursorTextColor",pProp->m_clrCursorTextColor);

		Reg.WriteInt("DisplayPeriod",	 pProp->m_lDisplayPeriod);
		Reg.WriteInt("BlackoutPeriod",	 pProp->m_lBlackoutPeriod);
		Reg.WriteInt("HighlightPeriod", pProp->m_lHighlightPeriod);
		Reg.WriteInt("Cursor",          pProp->m_lCursor);
		Reg.WriteInt("CursorWidth",     pProp->m_lCursorWidth);
		Reg.WriteInt("CursorHeight",    pProp->m_lCursorHeight);
		Reg.WriteInt("BaseTime",		 pProp->m_lBaseTime);
		Reg.WriteInt("Top",			 pProp->m_lTop);
		Reg.WriteInt("Bottom",			 pProp->m_lBottom);
		Reg.WriteInt("Right",			 pProp->m_lRight);
		Reg.WriteInt("Left",			 pProp->m_lLeft);
		Reg.WriteInt("LogLevel",		 pProp->m_lLogLevel);
		Reg.WriteBool("ShowMetafile",	 pProp->m_bShowMetafile);
		Reg.WriteBool("ShowControls",	 pProp->m_bShowControls);
		Reg.WriteBool("ShowStatusBar",	 pProp->m_bShowStatusBar);
		Reg.WriteBool("ShowTrackBar",	 pProp->m_bShowTrackBar);

		// 1st delete all Setting keys from the registry
		if (Reg.SetKey (OLE2T(bstrWinBlitKeySettings), FALSE))
		{
			CHAR chDeleteKey [3];
			int iA = 1;

			wsprintf (chDeleteKey,"%d", iA);
			while (Reg.DeleteKey(OLE2T(bstrWinBlitKeySettings),chDeleteKey))
			{
				iA++;
				wsprintf (chDeleteKey,"%d", iA);
			}
		}
		long lTotal;

		// Add settings to the registry.
		CComPtr<IDispatch> pDispatch; 

		HRESULT hr = pProp->get_Settings(&pDispatch); 
		if (S_OK == hr)
		{
			CComQIPtr<ISettings> pSettings(pDispatch); 
			if (pSettings.p)
			{
				pSettings->get_Count(&lTotal);
				long lCount = 1;
				while (lCount <= lTotal)
				{
					CComQIPtr<ISetting> pSetting;
					HRESULT hr = pSettings->get_ItemCustom(CComVariant(lCount),  &pSetting);
					if (S_OK == hr && pSetting.p)
					{
						CHAR chSetting [512];
						wsprintf (chSetting, "%s\\%d",OLE2T(bstrWinBlitKeySettings), lCount);
 
						if (Reg.SetKey (chSetting, TRUE))
						{

							BSTR bstrKey;
							BSTR bstrValue;
							long lPeriod = 0;
							long lRule = 0;	

							pSetting->get_Name	(&bstrKey);
							pSetting->get_Value	(&bstrValue);
							pSetting->get_Period	(&lPeriod);
							pSetting->get_Rule	(&lRule);

							Reg.WriteInt	("Period",		lPeriod);
							Reg.WriteInt	("Rule",		lRule);
							if (bstrValue) 	Reg.WriteString("Value",bstrValue, ::SysStringLen(bstrValue));	
							if (bstrKey)    Reg.WriteString("Name", bstrKey , ::SysStringLen(bstrKey));			

							::SysFreeString(bstrValue);
							::SysFreeString(bstrKey);

						}
					}
					lCount++;
				}
			}
		}
	}
	else 
	{
		return -1;
	}
	return 0; 
}

//=========================================================================== 
//						
//	Method :		GetAllSettings
//						
//	Description :	Load all config or template  from the registry 
//
//	Returns			0 if successful
//									
//============================================================================
//
int CWinBlitRegistry::GetAllSettings(vector<CSettingStrings>& vecstring,		// String array to return
									int iKeyType)					// 0 for Configs, 1 for templates
								
{
	ATL_TRACE0 (e_LOGFLOW, "\n CWinBlitRegistry::GetAllSettings");
	vecstring.clear(); 

	CRegistry Reg;
	Reg.SetRootKey(HKEY_LOCAL_MACHINE);
	CComBSTR bstrWinBlitKey = cbstrWinBlitKey [iKeyType];
	USES_CONVERSION; 
	string strWinBlitKey = OLE2T(bstrWinBlitKey);
	string strWinBlitSetting;
	CSettingStrings strSettingStrings;
	if (Reg.SetKey (strWinBlitKey.c_str(), TRUE))
	{
		int iCount = 0;
		int iTotal = Reg.GetSubKeyCount();
		while (iCount < iTotal)
		{
			TCHAR chName [255]; 
			if (Reg.EnumKey(iCount, chName))
			{
				CWinBlitProperties WinBlitProperties;
				// Retrieve just the basic details 
				CComBSTR bstrName(chName); 
				LoadSettings(bstrName, &WinBlitProperties, iKeyType, true);
				if (1 == iKeyType)
				{
					strSettingStrings.m_wstrName.assign			(WinBlitProperties.m_bstrTemplateID);
					strSettingStrings.m_wstrTemplateID.assign	(WinBlitProperties.m_bstrTemplateID);
					strSettingStrings.m_wstrDescription.assign	(WinBlitProperties.m_bstrDescription);
				}
				else
				{
					// Get the template name, description and ID from the associated template 
					CComBSTR bstrTemplate;
					CWinBlitProperties WinBlitTemplateProperties;
					LoadSettings (WinBlitProperties.m_bstrTemplateID, &WinBlitTemplateProperties, 1, true); 
					USES_CONVERSION; 
					strSettingStrings.m_wstrName.assign			(T2OLE(chName));
					strSettingStrings.m_wstrTemplateID.assign	(WinBlitTemplateProperties.m_bstrTemplateID);
					strSettingStrings.m_wstrDescription.assign	(WinBlitTemplateProperties.m_bstrDescription);
				}
				vecstring.push_back(strSettingStrings);
			}
			iCount++;
		}
	}
	else 
	{
		ATL_TRACE ("Setkey Failed ");
	}

	ATL_TRACE0 (e_LOGFLOW, "\n CWinBlitRegistry::GetAllSettings returns");

	return 0;
};

//=========================================================================== 
//						
//	Method :		RemoveSetting
//						
//	Description :	Remove a configuraiton or template from the registry 
//
//	Returns			0 
//									
//============================================================================


int CWinBlitRegistry::RemoveSettings(BSTR bstrRemove, int iKeyType)
{
	CRegistry Reg;
	Reg.SetRootKey(HKEY_LOCAL_MACHINE);
	wstring wstrKey;
	wstring wstrRemove;
	USES_CONVERSION; 
	wstrKey.assign		(cbstrWinBlitKeyDelete [iKeyType]); 
	wstrRemove.assign	(bstrRemove); 

	RemoveRecurse(wstrKey, wstrRemove);
	return 0; 
}

//=========================================================================== 
//						
//	Method :		RemoveRecurse
//						
//	Description :	Delete a regsitry key and everything under it. 
//					Calls itself recursively
//
//	Returns			0 
//									
//============================================================================

int CWinBlitRegistry::RemoveRecurse(wstring& wstrKey,	wstring &wstrRemove, int iKeyType)
{
	CRegistry Reg;
	wstring wstrAppend;
	wstrAppend = wstrKey;
	wstrAppend.append(L"\\"); 
	wstrAppend.append(wstrRemove);
	USES_CONVERSION; 
	if (Reg.SetKey (OLE2T(wstrAppend.c_str()), FALSE))
	{
		int iCount = Reg.GetSubKeyCount();

		while (--iCount >= 0)
		{
			TCHAR chName [255]; 
			if (Reg.EnumKey(iCount, chName))
			{
				wstring wstrDelete;
				wstrDelete.assign(T2OLE(chName));
				RemoveRecurse(wstrAppend, wstrDelete);
			}

		}
		Reg.DeleteKey(OLE2T(wstrKey.c_str()), OLE2T(wstrRemove.c_str())); 
	}
	return 0;
}

//=========================================================================== 
//						
//	Method :		SetDefaultName
//						
//	Description :	Set the Name of the configuration which will be used 
//					as the default configuration
//
//	Returns			0 
//									
//============================================================================

int CWinBlitRegistry::SetDefaultName (wstring &wstrKey, int iKeyType)
{
	CRegistry Reg;
	Reg.SetRootKey(HKEY_LOCAL_MACHINE);
	wstring wstrCurrentKey;
	wstrCurrentKey.assign		(cbstrWinBlitKey [iKeyType]); 
	USES_CONVERSION; 
	if (Reg.SetKey (OLE2T(wstrCurrentKey.c_str()), TRUE))	
	{
		USES_CONVERSION;
		Reg.WriteString(OLE2T(cbstrDefault), OLE2T(wstrKey.c_str()), wstrKey.length());
	}

	return 0;
}; 

//=========================================================================== 
//						
//	Method :		GetDefaultName
//						
//	Description :	Get the Name of the default configuration 
//
//	Returns			0 if success 
//									
//============================================================================

int CWinBlitRegistry::GetDefaultName (wstring &wstrKey, int iKeyType)
{
	ATL_TRACE0 (e_LOGDETAIL, " CWinBlitRegistry::GetDefaultName "); 
	int iRet = 1; 
	CRegistry Reg;
	Reg.SetRootKey(HKEY_LOCAL_MACHINE);
	USES_CONVERSION; 
	wstring wstrCurrentKey;
	wstrCurrentKey.assign(cbstrWinBlitKey [iKeyType]); 
	wstrKey.reserve(255);
	CComBSTR bstrName; 
	
	if (Reg.SetKey (OLE2T(wstrCurrentKey.c_str()), TRUE))
	{
		if (Reg.ReadString(OLE2T(cbstrDefault), &bstrName.m_str))
		{
			wstrKey.assign(bstrName); 
			iRet = 0;
		}
	}
		
	ATL_TRACE0 (e_LOGDETAIL, " CWinBlitRegistry::GetDefaultName returns "); 

	return iRet;
}; 

long  CWinBlitRegistry::GetStartupFlag ()
{
	long lStartup = 0;
	CRegistry Reg;

	Reg.SetRootKey(HKEY_LOCAL_MACHINE);
	CComBSTR bstrWinBlitKey = cbstrWinBlitKey [0];
	USES_CONVERSION; 
	string strWinBlitKey = OLE2T(bstrWinBlitKey);
	if (Reg.SetKey (strWinBlitKey.c_str(), FALSE))
	{
		Reg.ReadInt	("Startup",		lStartup);
	}
	return lStartup; 
}

void  CWinBlitRegistry::SetStartupFlag (long lStartup)
{
	CRegistry Reg;
	Reg.SetRootKey(HKEY_LOCAL_MACHINE);
	CComBSTR bstrWinBlitKey = cbstrWinBlitKey [0];
	USES_CONVERSION; 
	string strWinBlitKey = OLE2T(bstrWinBlitKey);
	if (Reg.SetKey (strWinBlitKey.c_str(), TRUE))
	{
		Reg.WriteInt	("Startup",		lStartup);
	}
}


