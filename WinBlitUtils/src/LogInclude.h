#ifndef LOG_INCLUDE
#define LOG_INCLUDE
#import "..\import\build\ATLLogApp.tlb" no_namespace named_guids

enum {
	e_LOGERROR = 1,
	e_LOGFLOW = 2, 
	e_LOGDETAIL = 3};

extern long lLogLevel; 
extern ICoLoggerPtr m_Log;

#ifdef WIN95TEST
	#define ATL_TRACE OutputDebugStringW95
#else 
	#define ATL_TRACE ATLTRACE
	
	#define ATL_TRACE0(iLevel,string)\
	if (iLevel<=lLogLevel) MyLog(iLevel,string);\
	ATLTRACE(string);

	#define ATL_TRACE1(iLevel,string,nID1)\
	if (iLevel<=lLogLevel) MyLog(iLevel,string,nID1);\
	ATLTRACE(string, nID1);

	#define ATL_TRACE2(iLevel,string,nID1,nID2)\
	if (iLevel<=lLogLevel) MyLog(iLevel,string,nID1,nID2);\
	ATLTRACE(string,nID1,nID2);

	#define ATL_TRACE3(iLevel,string,nID1,nID2,nID3)\
	if (iLevel<=lLogLevel) MyLog(iLevel,string,nID1,nID2,nID3);\
	ATLTRACE(string,nID1,nID2,nID3);

	#define ATL_TRACE4(iLevel,string,nID1,nID2,nID3,nID4)\
	if (iLevel<=lLogLevel) MyLog(iLevel,string,nID1,nID2,nID3,nID4);\
	ATLTRACE(string,nID1,nID2,nID3,nID4);

	#define ATL_TRACE5(iLevel,string,nID1,nID2,nID3,nID4,nID5)\
	if (iLevel<=lLogLevel) MyLog(iLevel,string,nID1,nID2,nID3,nID4,nID5);\
	ATLTRACE(string,nID1,nID2,nID3,nID4,nID5);

	#define ATL_TRACE6(iLevel,string,nID1,nID2,nID3,nID4,nID5,nID6)\
	if (iLevel<=lLogLevel) MyLog(iLevel,string,nID1,nID2,nID3,nID4,nID5,nID6);\
	ATLTRACE(string,nID1,nID2,nID3,nID4,nID5,nID6);
	
	#define ATL_TRACE7(iLevel,string,nID1,nID2,nID3,nID4,nID5,nID6,nID7)\
	if (iLevel<=lLogLevel) MyLog(iLevel,string,nID1,nID2,nID3,nID4,nID5,nID6,nID7);\
	ATLTRACE(string,nID1,nID2,nID3,nID4,nID5,nID6,nID7);

	#define ATL_TRACE8(iLevel,string,nID1,nID2,nID3,nID4,nID5,nID6,nID7,nID8)\
	if (iLevel<=lLogLevel) MyLog(iLevel,string,nID1,nID2,nID3,nID4,nID5,nID6,nID7,nID8);\
	ATLTRACE(string,nID1,nID2,nID3,nID4,nID5,nID6,nID7,nID8);

	#define ATL_TRACE9(iLevel,string,nID1,nID2,nID3,nID4,nID5,nID6,nID7,nID8,nID9)\
	if (iLevel<=lLogLevel) MyLog(iLevel,string,nID1,nID2,nID3,nID4,nID5,nID6,nID7,nID8,nID9);\
	ATLTRACE(string,nID1,nID2,nID3,nID4,nID5,nID6,nID7,nID8,nID9);

#endif 


void MyLog(INT, LPCSTR , ...);

#define ATL_TRACE_LEVEL 0

#endif 