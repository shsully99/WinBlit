[Components]
component0=SelfRegDlls
component1=TargetDir
component2=ExchangeExtension

[TopComponents]
component0=TargetDir
component1=ExchangeExtension
component2=SelfRegDlls

[SetupType]
setuptype0=Typical

[SelfRegDlls]
SELECTED=Yes
FILENEED=STANDARD
HTTPLOCATION=
STATUS=
UNINSTALLABLE=Yes
TARGET=<TARGETDIR>
FTPLOCATION=
VISIBLE=Yes
DESCRIPTION=
DISPLAYTEXT=
IMAGE=
DEFSELECTION=Yes
filegroup0=ReaderManager
COMMENT=
INCLUDEINBUILD=Yes
filegroup1=WebBand
INSTALLATION=ALWAYSOVERWRITE
COMPRESSIFSEPARATE=No
MISC=
ENCRYPT=No
DISK=ANYDISK
TARGETDIRCDROM=
PASSWORD=
TARGETHIDDEN=General Application Destination

[Info]
Type=CompDef
Version=1.00.000
Name=

[SetupTypeItem-Typical]
Comment=
item0=SelfRegDlls
item1=TargetDir
item2=ExchangeExtension
Descrip=
DisplayText=

[TargetDir]
SELECTED=Yes
FILENEED=CRITICAL
HTTPLOCATION=
STATUS=
UNINSTALLABLE=Yes
TARGET=<TARGETDIR>
FTPLOCATION=
VISIBLE=Yes
DESCRIPTION=
DISPLAYTEXT=
IMAGE=
DEFSELECTION=Yes
filegroup0=BlitPad
COMMENT=
INCLUDEINBUILD=Yes
filegroup1=Help Files
INSTALLATION=NEWERVERSION\NEWERDATE
filegroup2=Reg
filegroup3=Word Template
COMPRESSIFSEPARATE=No
MISC=
ENCRYPT=No
DISK=ANYDISK
TARGETDIRCDROM=
PASSWORD=
TARGETHIDDEN=General Application Destination

[ExchangeExtension]
SELECTED=Yes
FILENEED=CRITICAL
HTTPLOCATION=
STATUS=
UNINSTALLABLE=Yes
TARGET=<WINSYSDIR>
FTPLOCATION=
VISIBLE=Yes
DESCRIPTION=
DISPLAYTEXT=
IMAGE=
DEFSELECTION=Yes
filegroup0=ExchangeExtension
COMMENT=
INCLUDEINBUILD=Yes
INSTALLATION=NEWERVERSION\NEWERDATE
COMPRESSIFSEPARATE=No
MISC=
ENCRYPT=No
DISK=ANYDISK
TARGETDIRCDROM=
PASSWORD=
TARGETHIDDEN=Windows Operating System\Windows System Folder

