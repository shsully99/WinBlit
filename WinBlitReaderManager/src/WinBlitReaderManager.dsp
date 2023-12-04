# Microsoft Developer Studio Project File - Name="WinBlitReaderManager" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=WinBlitReaderManager - Win32 Debugw95
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WinBlitReaderManager.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WinBlitReaderManager.mak" CFG="WinBlitReaderManager - Win32 Debugw95"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WinBlitReaderManager - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WinBlitReaderManager - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WinBlitReaderManager - Win32 Debugw95" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/winblit/WinBlitReaderManager/src", AHAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WinBlitReaderManager - Win32 Debug"

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
# ADD LINK32 version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\Export\Run\WinBlitReaderManagerd.dll" /pdbtype:sept /libpath:"..\import\build"
# Begin Custom Build - Performing registration
OutDir=.\Debug
TargetPath=\Documents and Settings\Sean Sullivan\My Documents\WINBLIT\WinBlitReaderManager\Export\Run\WinBlitReaderManagerd.dll
InputPath=\Documents and Settings\Sean Sullivan\My Documents\WINBLIT\WinBlitReaderManager\Export\Run\WinBlitReaderManagerd.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Distribute
PostBuild_Cmds="C:\Documents and Settings\Sean Sullivan\My Documents\WinBlit\ReaderRedist"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "WinBlitReaderManager - Win32 Release MinDependency"

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
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O1 /I "..\.." /I "..\..\wtlincludes" /I "..\import\build" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /FR /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:windows /dll /machine:I386 /out:"..\Export\Run\WinBlitReaderManager.dll"
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinDependency
TargetPath=\Documents and Settings\Sean Sullivan\My Documents\WINBLIT\WinBlitReaderManager\Export\Run\WinBlitReaderManager.dll
InputPath=\Documents and Settings\Sean Sullivan\My Documents\WINBLIT\WinBlitReaderManager\Export\Run\WinBlitReaderManager.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Redist
PostBuild_Cmds="C:\Documents and Settings\Sean Sullivan\My Documents\WinBlit\ReaderRedist"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "WinBlitReaderManager - Win32 Debugw95"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinBlitReaderManager___Win32_Debugw95"
# PROP BASE Intermediate_Dir "WinBlitReaderManager___Win32_Debugw95"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinBlitReaderManager___Win32_Debugw95"
# PROP Intermediate_Dir "WinBlitReaderManager___Win32_Debugw95"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\wtlincludes" /I "..\import\build" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\wtlincludes" /I "..\import\build" /I "..\..\WinBlitUtils\src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\Export\Run\WinBlitReaderManagerd.dll" /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\Export\Run\WinBlitReaderManagerd.dll" /pdbtype:sept
# Begin Custom Build - Performing registration
OutDir=.\WinBlitReaderManager___Win32_Debugw95
TargetPath=\Documents and Settings\Sean Sullivan\My Documents\WINBLIT\WinBlitReaderManager\Export\Run\WinBlitReaderManagerd.dll
InputPath=\Documents and Settings\Sean Sullivan\My Documents\WINBLIT\WinBlitReaderManager\Export\Run\WinBlitReaderManagerd.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "WinBlitReaderManager - Win32 Debug"
# Name "WinBlitReaderManager - Win32 Release MinDependency"
# Name "WinBlitReaderManager - Win32 Debugw95"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\About.cpp
# End Source File
# Begin Source File

SOURCE=.\BlitUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\BltCreator.cpp
# End Source File
# Begin Source File

SOURCE=.\BrowserWrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\HTMLReader.cpp
# End Source File
# Begin Source File

SOURCE=.\MD5.cpp
# End Source File
# Begin Source File

SOURCE=.\PropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\Reader.cpp
# End Source File
# Begin Source File

SOURCE=.\Reg.cpp
# End Source File
# Begin Source File

SOURCE=.\Registry.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportError.cpp
# End Source File
# Begin Source File

SOURCE=.\Setting.cpp
# End Source File
# Begin Source File

SOURCE=.\Settings.cpp
# End Source File
# Begin Source File

SOURCE=.\Speed.cpp
# End Source File
# Begin Source File

SOURCE=.\Statistic.cpp
# End Source File
# Begin Source File

SOURCE=.\Statistics.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StringReader.cpp
# End Source File
# Begin Source File

SOURCE=.\TextWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\TXTReader.cpp
# End Source File
# Begin Source File

SOURCE=.\W95TRACE.CPP
# End Source File
# Begin Source File

SOURCE=.\WinBlitData.cpp
# End Source File
# Begin Source File

SOURCE=.\WinBlitProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\WinBlitReader.cpp
# End Source File
# Begin Source File

SOURCE=.\WinBlitReaderManager.cpp
# End Source File
# Begin Source File

SOURCE=.\WinBlitReaderManager.def
# End Source File
# Begin Source File

SOURCE=.\WinBlitReaderManager.idl
# ADD MTL /tlb ".\WinBlitReaderManager.tlb" /h "WinBlitReaderManager.h" /iid "WinBlitReaderManager_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\WinBlitReaderManager.rc
# End Source File
# Begin Source File

SOURCE=.\WinBlitRegistry.cpp
# End Source File
# Begin Source File

SOURCE=.\WordReader.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\About.h
# End Source File
# Begin Source File

SOURCE=.\BlitUtils.h
# End Source File
# Begin Source File

SOURCE=.\BltCreator.h
# End Source File
# Begin Source File

SOURCE=.\BrowserWrapper.h
# End Source File
# Begin Source File

SOURCE=.\FullTlb.h
# End Source File
# Begin Source File

SOURCE=.\HTMLReader.h
# End Source File
# Begin Source File

SOURCE=.\IDLConstants.h
# End Source File
# Begin Source File

SOURCE=.\PropPage.h
# End Source File
# Begin Source File

SOURCE=.\Reader.h
# End Source File
# Begin Source File

SOURCE=.\Reg.h
# End Source File
# Begin Source File

SOURCE=.\Registry.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Setting.h
# End Source File
# Begin Source File

SOURCE=.\Settings.h
# End Source File
# Begin Source File

SOURCE=.\Speed.h
# End Source File
# Begin Source File

SOURCE=.\Statistic.h
# End Source File
# Begin Source File

SOURCE=.\Statistics.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StlClasses.h
# End Source File
# Begin Source File

SOURCE=.\StringReader.h
# End Source File
# Begin Source File

SOURCE=.\TextWindow.h
# End Source File
# Begin Source File

SOURCE=.\TXTReader.h
# End Source File
# Begin Source File

SOURCE=.\W95TRACE.H
# End Source File
# Begin Source File

SOURCE=.\WinBlitConstants.h
# End Source File
# Begin Source File

SOURCE=.\WinBlitData.h
# End Source File
# Begin Source File

SOURCE=.\WinBlitDataError.h
# End Source File
# Begin Source File

SOURCE=.\WinBlitProperties.h
# End Source File
# Begin Source File

SOURCE=.\WinBlitReader.h
# End Source File
# Begin Source File

SOURCE=.\WinBlitRegistry.h
# End Source File
# Begin Source File

SOURCE=.\WordReader.h
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

SOURCE=.\BlitScript.rgs
# End Source File
# Begin Source File

SOURCE=.\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\BrowserWrapper.rgs
# End Source File
# Begin Source File

SOURCE=.\Setting.rgs
# End Source File
# Begin Source File

SOURCE=.\Settings.rgs
# End Source File
# Begin Source File

SOURCE=.\Statistic.rgs
# End Source File
# Begin Source File

SOURCE=.\Statistics.rgs
# End Source File
# Begin Source File

SOURCE=.\toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\TrackBarWindow.rgs
# End Source File
# Begin Source File

SOURCE=.\WinBlitData.rgs
# End Source File
# Begin Source File

SOURCE=.\winblitre.bmp
# End Source File
# Begin Source File

SOURCE=.\WinBlitReader.rgs
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=..\Import\Build\htmlhelp.lib
# End Source File
# End Target
# End Project
