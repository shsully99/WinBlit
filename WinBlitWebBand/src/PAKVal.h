// PAKVal.h: interface for the CPAKVal class.
//
// This class in inlined in order to 
//////////////////////////////////////////////////////////////////////

#if !defined (_PAKVAL_H_)
#define _PAKVAL_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"

#include "Registry.h"
#include "MD5.h"

#include <string>
#include <vector>
using namespace std;

static unsigned char uchTrialA [] = {0x47, 0x36, 0x44, 0x33, 0x4D, 0x30, 0x54, 0x55, 0x42, 0x38, 0x36, 0x34, 0x43, 0x50, 0x36, 0x50, 0x0};
static unsigned char uchTrialB [] = {0x33, 0x47, 0x31, 0x56, 0x33, 0x57, 0x33, 0x4B, 0x31 , 0x0};

static const int ciBetaPeriod(60);
static const int ciTrialPeriod (32);
static const int ciBetaRuns (1000); 
static const int ciTrialRuns (200);
static const int ciLicMultiplier (1000);		// Clients multiply loaddata by this 
static const int ciLatestVersion (1); 

#define LICENSESWITCH 1					// 1 = Beta ,  2 = Trial, 3 = Full

// License status 
enum eLicStat
{
	eOldLicense = -1, 
	eUnLicensed = 0,					
	eBetaLicense = 1,					
	eTrialLicense = 2, 
	eFullLicense = 3,
	eUnknownLicenseWord	= 10					// Word App requests license
};

const CComBSTR cbstrLicStat [5] = {" ",
								   " - Unlicensed version", 
								   " - Beta version",
								   " - Trial version",
								   " "};


enum eLIC
{
	eWinBlitPad1Beta = 1,
	eWinBlitPad1Trial = 2,
	eWinBlitPad1Licensed = 4,
	eWinBlitExchange1Beta = 8,
	eWinBlitExchange1Trial = 16,
	eWinBlitExchange1Licensed = 32,
	eWinBlitWord1Beta = 64, 
	eWinBlitWord1Trial = 128,
	eWinBlitWord1Licensed = 256,
	eWinBlitWebBand1Beta = 512,
	eWinBlitWebBand1Trial = 1024,
	eWinBlitWebBand1Licensed = 2048,
	eWinBlitControl1Beta = 4096,
	eWinBlitControl1Trial = 8192, 
	eWinBlitControl1Licensed = 16384
};

enum eAPP
{
	eWinBlitPad = 0,
	eWinBlitExchange = 1,
	eWinBlitWord = 2,
	eWinBlitWebBand = 3,
	eWinBlitControl = 4
}; 

enum eCallingAPP
{
	eCalledfromBlitPad  = 100000,
	eCalledfromExchange = 200000,
	eCalledfromWord     = 300000,
	eCalledfromWebBand  = 400000,
	eCalledfromControl  = 500000
}; 

class CProduct 
{
public:
	DWORD  m_dwID;							// a
	DWORD m_dwVersion;						// b
	DWORD m_dwInstallationDate;				// c 
	DWORD m_dwRuns;							// d
	unsigned char m_uchName [64];			// e
	unsigned char m_uchPAK  [40];			// f

	void Decode()
	{
		/* Decoding code here 
		m_dwID = mdwID / 200; 
		m_dwID +=1; 
		m_dwVersion -= 15; 
		m_dwVersion /= 33; 
		*/ 
	}
	void Encode ()
	{
		/*Encoding here 
		m_dwID -=1; 
		m_dwID = mdwID *200; 
		m_dwVersion *= 33;
		m_dwVersion += 15; 

		m_dwInstallationDate += 240562;				
		if (0 == m_dwInstallationData % 2) m_dwInstallationData = 0-m_dwInstallationData;
		DWORD m_dwBetaTimePeriod 
		DWORD m_dwTrialTimePeriod
		DWORD m_dwBetaTimeRuns
		DWORD m_dwTrialTimeRuns
		*/
	}
};

// STL typedefs for vector collections of Word objects 

typedef vector<CProduct>					VECPRODUCTS;
typedef vector<CProduct>::const_iterator	VECPRODUCTSCONST_ITERATOR;
typedef vector<CProduct>::iterator			VECPRODUCTSITERATOR;
typedef vector<CProduct>::reference			VECPRODUCTSREFERENCE;
typedef vector<CProduct>::difference_type	VECPRODUCTSDIFFERENCE; 

typedef vector<string>						VECSTRINGS;
typedef vector<string>::iterator			VECSTRINGSITERATOR;

class CPAKVal  
{
	bool m_bLic;
	VECPRODUCTS m_vecProducts; 
	CMD5 m_MD5; 

public:
	
	// 0 if errror or no licnse found, +ve if no error 
	long Val (eAPP eApp, DWORD dwVersion)
	{
		m_vecProducts.clear(); 
		
		// Load up the system registry.
		CRegistry Reg;
		Reg.SetRootKey(HKEY_LOCAL_MACHINE);
 
		string strProdKey("Software\\PataSucia\\WinBlit\\Products");
		if (!Reg.SetKey (strProdKey.c_str(), FALSE))
		{
			ATLTRACE ("\n Registry error - aborting"); 
			return 0;
		}
		VECSTRINGS vecStrings;

		int iCount = 0;
		int iTotal = Reg.GetSubKeyCount();
		while (iCount < iTotal)
		{
			// Build up string array of all the strings 
			TCHAR chName [255]; 
			if (Reg.EnumKey(iCount, chName))
			{
				vecStrings.push_back(chName);
			}
			iCount++;
		}
		
		VECSTRINGSITERATOR vsit; 
		for (vsit = vecStrings.begin(); vsit != vecStrings.end(); vsit++)
		{
			string strKey(strProdKey); 
			strKey.append("\\"); 
			strKey.append((*vsit).c_str());
			if (Reg.SetKey (strKey.c_str(), FALSE) )
			{
				ATLTRACE ("\n ");
				CProduct Product; 

				Reg.ReadInt ("a",	Product.m_dwID); 
				Reg.ReadInt ("b",	Product.m_dwVersion);
				Reg.ReadInt ("c",	Product.m_dwInstallationDate);
				Reg.ReadInt ("d",	Product.m_dwRuns);	
				DWORD  dwNameLength(64);
				DWORD  dwPAKLength(30);
				Reg.ReadBytes ("e",	&Product.m_uchName[0], dwNameLength);
				Reg.ReadBytes ("f",	&Product.m_uchPAK[0],  dwPAKLength); 

				// Maybe should be done at end. 
				long lRuns = Product.m_dwRuns;
				if (lRuns > 0)
				{
					lRuns--; 
					Reg.SetLazyWrite(FALSE); 
					Reg.WriteInt ("d", lRuns);
					Reg.SetLazyWrite(TRUE); 
				}

				Product.Decode(); 

				m_vecProducts.push_back(Product);
				break; 
			}
			return 0; 
		}
		// Now loop round our products checking for input product

		VECPRODUCTSITERATOR vpit; 
		for (vpit = m_vecProducts.begin(); vpit != m_vecProducts.end(); vpit++)
		{
			if (eApp == eWinBlitPad && vpit->m_dwVersion == dwVersion && 1 == dwVersion)
			{
				if (eWinBlitPad1Beta & vpit->m_dwID)
				{		
					return Check(eBetaLicense,vpit);
				}
				else if (eWinBlitPad1Trial & vpit->m_dwID)
				{
					return Check(eTrialLicense,vpit);
				}
				else if (eWinBlitPad1Licensed & vpit->m_dwID)
				{
					return Check(eFullLicense,vpit);
				}
			}
			else if (eApp == eWinBlitExchange && vpit->m_dwVersion == dwVersion && 1 == dwVersion)
			{
				if (eWinBlitExchange1Beta & vpit->m_dwID)
				{		
					return Check(eBetaLicense,vpit);
				}
				else if (eWinBlitExchange1Trial & vpit->m_dwID)
				{
					return Check(eTrialLicense,vpit);
				}
				else if (eWinBlitExchange1Licensed & vpit->m_dwID)
				{
					return Check(eFullLicense,vpit);
				}
			}
			else if (eApp == eWinBlitWord && vpit->m_dwVersion == dwVersion && 1 == dwVersion)
			{
				if (eWinBlitWord1Beta & vpit->m_dwID)
				{		
					return Check(eBetaLicense,vpit);
				}
				else if (eWinBlitWord1Trial & vpit->m_dwID)
				{
					return Check(eTrialLicense,vpit);
				}
				else if (eWinBlitWord1Licensed & vpit->m_dwID)
				{
					return Check(eFullLicense,vpit);
				}
			}
			else if (eApp == eWinBlitWebBand && vpit->m_dwVersion == dwVersion && 1 == dwVersion)
			{
				if (eWinBlitWebBand1Beta & vpit->m_dwID)
				{		
					return Check(eBetaLicense,vpit);
				}
				else if (eWinBlitWebBand1Trial & vpit->m_dwID)
				{
					return Check(eTrialLicense,vpit);
				}
				else if (eWinBlitWebBand1Licensed & vpit->m_dwID)
				{
					return Check(eFullLicense,vpit);
				}
			}
			else if (eApp == eWinBlitControl && vpit->m_dwVersion == dwVersion && 1 == dwVersion)
			{
				if (eWinBlitControl1Beta & vpit->m_dwID)
				{		
					return Check(eBetaLicense,vpit);
				}
				else if (eWinBlitControl1Trial & vpit->m_dwID)
				{
					return Check(eTrialLicense,vpit);
				}
				else if (eWinBlitControl1Licensed & vpit->m_dwID)
				{
					return Check(eFullLicense,vpit);
				}
			}
		}
		return -1; 
	};

	// -1 - PAX invalid, -2 - system error 
	int Lic(TCHAR* pszName, TCHAR* pszPAK, int iProd = 1, int iVer = 1)
	{
		if (iProd != 1 || iVer != 1) return -1; 

		int iRet = 0; 
		
		if (!m_MD5.ValidatePAK(pszName, pszPAK))
		{
			iRet = -1;
		}
		else
		{
			// We have a full license - update system registry 			
			CRegistry Reg;
			Reg.SetRootKey(HKEY_LOCAL_MACHINE);
 
			if (!Reg.SetKey ("Software\\PataSucia\\WinBlit\\Products\\1", FALSE))
			{
				// Key has been deleted 
				iRet = -2; 
			}
			else 
			{
				DWORD dw = 0;
				dw = dw | eWinBlitPad1Licensed;
				dw = dw | eWinBlitExchange1Licensed;
				dw = dw | eWinBlitWord1Licensed;
				dw = dw | eWinBlitWebBand1Licensed;
				dw = dw | eWinBlitControl1Licensed;

				Reg.SetLazyWrite(FALSE); 

				if (Reg.WriteInt	("a",	dw)											&&
					Reg.WriteBytes	("e",	(unsigned char *) pszName, strlen(pszName)) &&
					Reg.WriteBytes  ("f",	(unsigned char *) pszPAK,  strlen(pszPAK )) )
				{
					iRet = 0;
				}
				else
				{
					iRet = -2;
				}

				Reg.SetLazyWrite(TRUE); 
			}
		}
		return iRet;
	}

	int Check(int iType, VECPRODUCTSITERATOR& vpit )
	{
		SYSTEMTIME SystemTime; 
		GetSystemTime(&SystemTime); 

		int iRet = iType; 
		if (iType == eBetaLicense)
		{
			DWORD dwDays = (SystemTime.wYear - 1998) * 365;
			dwDays += (SystemTime.wMonth * 30);
			dwDays += SystemTime.wDay; 
			if (SystemTime.wMonth > 6) 
			{
				// No Betas allowed after June
				return 0;
			}

			if (dwDays > (vpit->m_dwInstallationDate + ciBetaPeriod)) 
			{
				// Beta Periof expired 
				return 0;
			}
		
			if (vpit->m_dwRuns <= 0)
			{
				// No. of runs exceeded. 
				return 0; 
			}
		}
		else if (eTrialLicense == iType)
		{
			DWORD dwDays = (SystemTime.wYear - 1998) * 365;
			dwDays += (SystemTime.wMonth * 30);
			dwDays += SystemTime.wDay; 

			if (dwDays > (vpit->m_dwInstallationDate + ciTrialPeriod)) 
			{
				// Trial Period expired 
				return 0;
			}
		
			if (vpit->m_dwRuns <= 0)
			{
				// No. of runs exceeded. 
				return 0; 
			}
		}

		if (eBetaLicense == iRet || eTrialLicense == iRet || eFullLicense == iRet)
		{
			// Compare key to licensed key. 
			
			for (int iA = 0; iA <25; iA++)
			{
				if (iA < 16)
				{
					if (vpit->m_uchPAK[iA] != uchTrialA[iA]) break;
				}
				else 
				{
					if (vpit->m_uchPAK[iA] != uchTrialB[iA-16]) break;
				}
			}
			if (iRet == eFullLicense)
			{
				if (iA == 25) iRet = 2;
			}
			else
			{
				if (iA != 25) iRet = 0; 
			}
		}
		// Fully licensed  - must validate it 
		if (eFullLicense == iRet)
		{
			m_bLic = m_MD5.ValidatePAK((const char *) vpit->m_uchName , (char *) vpit->m_uchPAK);
			if (!m_bLic) iRet = eUnLicensed; 

			// Has the date expired on out license 
			// If greater than 3-Aug-2004 then the user must request a new download.

			if ( SystemTime.wYear >= 2005 ||
				(SystemTime.wYear >= 2004 && SystemTime.wMonth >= 8))
			{
				iRet = eOldLicense; 
			}
		}
		return iRet;
	}

	// Currently only does trial product - called when the dll is registered 
	void FirstReg ()
	{
		CRegistry Reg;
		Reg.SetRootKey(HKEY_LOCAL_MACHINE);

		// If key already exists then bomb out 
		if (Reg.SetKey  ("Software\\PataSucia\\WinBlit\\Products\\1", FALSE)) return;

		if (!Reg.SetKey ("Software\\PataSucia\\WinBlit\\Products\\1", TRUE)) return;

		DWORD dw = 0;
/*		dw = dw | eWinBlitPad1Beta;
		dw = dw | eWinBlitExchange1Beta;
		dw = dw | eWinBlitWord1Beta;
		dw = dw | eWinBlitWebBand1Beta;
		dw = dw | eWinBlitControl1Beta;*/

		dw = dw | eWinBlitPad1Trial;
		dw = dw | eWinBlitExchange1Trial;
		dw = dw | eWinBlitWord1Trial;
		dw = dw | eWinBlitWebBand1Trial;
		dw = dw | eWinBlitControl1Trial;

		Reg.SetLazyWrite(FALSE);

		Reg.WriteInt	("a",	dw);
		Reg.WriteInt	("b",	1);

		SYSTEMTIME SystemTime; 
		GetSystemTime(&SystemTime); 
		int iDays = (SystemTime.wYear - 1998) * 365;
		iDays += (SystemTime.wMonth * 30);
		iDays += SystemTime.wDay;		
		Reg.WriteInt	("c",								 iDays); 
		Reg.WriteInt	("d",								 ciTrialRuns); 
		//Reg.WriteString	("e",	"Trial",					 5);

		unsigned char uch [25];
		for (int iA = 0; iA <25; iA++)
		{
			if (iA < 16)
			{
				uch[iA] = uchTrialA[iA];
			}
			else 
			{
				uch[iA] = uchTrialB[iA-16];
			}
		}
		Reg.WriteBytes ("f", uch, 25); 
		Reg.SetLazyWrite(TRUE); 
	}

	CPAKVal():m_bLic (false) 
	{
	};
	virtual ~CPAKVal()
	{
	};

};

#endif // !defined (_PAKVAL_H_)
