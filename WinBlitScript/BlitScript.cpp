// BlitScript.cpp : Implementation of CBlitScript

#include "stdafx.h"
#include "WinBlitScript.h"
#include "BlitScript.h"

/////////////////////////////////////////////////////////////////////////////
// CBlitScript


STDMETHODIMP CBlitScript::UnloadData()
{
	m_WinBlitReader->UnloadData();
	return S_OK; 
}


STDMETHODIMP CBlitScript::LoadData(long lDataSourceType, VARIANT varDataSource)
{	
	return m_WinBlitReader->LoadData(lDataSourceType, varDataSource);
}

STDMETHODIMP CBlitScript::Display()
{
	return m_WinBlitReader->Display();
}
