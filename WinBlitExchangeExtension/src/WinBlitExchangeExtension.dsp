# Microsoft Developer Studio Project File - Name="WinBlitExchangeExtension" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=WinBlitExchangeExtension - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WinBlitExchangeExtension.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WinBlitExchangeExtension.mak" CFG="WinBlitExchangeExtension - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WinBlitExchangeExtension - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WinBlitExchangeExtension - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/winblit/WinBlitExchangeExtension/src", SGAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WinBlitExchangeExtension - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\wtlincludes" /I "..\import\build" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\export\run\WinBlitExchangeExtension.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Performing registration
OutDir=.\Debug
TargetPath=\Documents and Settings\Sean Sullivan\My Documents\WINBLIT\WinBlitExchangeExtension\export\run\WinBlitExchangeExtension.dll
InputPath=\Documents and Settings\Sean Sullivan\My Documents\WINBLIT\WinBlitExchangeExtension\export\run\WinBlitExchangeExtension.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=DistributeExchange
PostBuild_Cmds="C:\Documents and Settings\Sean Sullivan\My Documents\WinBlit\ExchangeRedist"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "WinBlitExchangeExtension - Win32 Release MinDependency"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinDependency"
# PROP BASE Intermediate_Dir "ReleaseMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinDependency"
# PROP Intermediate_Dir "ReleaseMinDependency"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O1 /I "..\import\build" /I "..\..\wtlincludes" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:windows /dll /machine:I386 /out:"..\export\run\WinBlitExchangeExtension.dll"
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinDependency
TargetPath=\Documents and Settings\Sean Sullivan\My Documents\WINBLIT\WinBlitExchangeExtension\export\run\WinBlitExchangeExtension.dll
InputPath=\Documents and Settings\Sean Sullivan\My Documents\WINBLIT\WinBlitExchangeExtension\export\run\WinBlitExchangeExtension.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Distribute
PostBuild_Cmds="C:\Documents and Settings\Sean Sullivan\My Documents\WinBlit\ExchangeRedist"
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "WinBlitExchangeExtension - Win32 Debug"
# Name "WinBlitExchangeExtension - Win32 Release MinDependency"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ExchangeClient.cpp
# End Source File
# Begin Source File

SOURCE=.\MD5.cpp
# End Source File
# Begin Source File

SOURCE=.\PAKVal.cpp
# End Source File
# Begin Source File

SOURCE=.\Registry.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportError.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WinBlitDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\WinBlitExchangeExtension.cpp
# End Source File
# Begin Source File

SOURCE=.\WinBlitExchangeExtension.def
# End Source File
# Begin Source File

SOURCE=.\WinBlitExchangeExtension.idl
# ADD MTL /tlb ".\WinBlitExchangeExtension.tlb" /h "WinBlitExchangeExtension.h" /iid "WinBlitExchangeExtension_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\WinBlitExchangeExtension.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ExchangeClient.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WinBlitDialog.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\ExchangeClient.rgs
# End Source File
# End Group
# End Target
# End Project
# Section WinBlitExchangeExtension : {002F5448-6C74-0000-2E00-630074006C00}
# 	1:16:IDD_WINBLITDIALOG:102
# End Section
