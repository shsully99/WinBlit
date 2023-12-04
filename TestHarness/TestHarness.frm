VERSION 5.00
Object = "{A1777A94-27A6-11D5-85B6-269F99000000}#1.0#0"; "WinBlitReaderManager.dll"
Begin VB.Form Form1 
   Caption         =   "TestHarness"
   ClientHeight    =   4860
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   10635
   LinkTopic       =   "Form1"
   ScaleHeight     =   4860
   ScaleWidth      =   10635
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox Text 
      Height          =   495
      Left            =   360
      TabIndex        =   3
      Text            =   "Text"
      Top             =   4200
      Width           =   8535
   End
   Begin WINBLITREADERMANAGERLibCtl.WinBlitReader WinBlitReader 
      Height          =   3735
      Left            =   2280
      OleObjectBlob   =   "TestHarness.frx":0000
      TabIndex        =   2
      Top             =   240
      Width           =   7695
   End
   Begin VB.ListBox List 
      Height          =   255
      ItemData        =   "TestHarness.frx":0024
      Left            =   240
      List            =   "TestHarness.frx":0026
      TabIndex        =   1
      Top             =   360
      Width           =   1695
   End
   Begin VB.CommandButton RunTests 
      Caption         =   "RunTests"
      Height          =   495
      Left            =   240
      TabIndex        =   0
      Top             =   720
      Width           =   1695
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Type FILETIME
    dwLowDateTime As Long
    dwHighDateTime As Long
End Type

Dim MyFilea As String
Dim MyFileb As String
Dim MyFilec As String
Dim MyFileLargetxt As String

Private Const WAIT_ABANDONED& = &H80&
Private Const WAIT_ABANDONED_0& = &H80&
Private Const WAIT_FAILED& = -1&
Private Const WAIT_IO_COMPLETION& = &HC0&
Private Const WAIT_OBJECT_0& = 0
Private Const WAIT_OBJECT_1& = 1
Private Const WAIT_TIMEOUT& = &H102&

Private Declare Function CreateWaitableTimer Lib "kernel32" _
    Alias "CreateWaitableTimerA" ( _
    ByVal lpSemaphoreAttributes As Long, _
    ByVal bManualReset As Long, _
    ByVal lpName As String) As Long
    Private Declare Function OpenWaitableTimer Lib "kernel32" _
    Alias "OpenWaitableTimerA" ( _
    ByVal dwDesiredAccess As Long, _
    ByVal bInheritHandle As Long, _
    ByVal lpName As String) As Long
    
Private Declare Function SetWaitableTimer Lib "kernel32" ( _
    ByVal hTimer As Long, _
    lpDueTime As FILETIME, _
    ByVal lPeriod As Long, _
    ByVal pfnCompletionRoutine As Long, _
    ByVal lpArgToCompletionRoutine As Long, _
    ByVal fResume As Long) As Long
    
Private Declare Function CancelWaitableTimer Lib "kernel32" ( _
    ByVal hTimer As Long)
    
Private Declare Function CloseHandle Lib "kernel32" ( _
    ByVal hObject As Long) As Long
    
Private Declare Function WaitForSingleObject Lib "kernel32" ( _
    ByVal hHandle As Long, _
    ByVal dwMilliseconds As Long) As Long
   
Private Declare Function MsgWaitForMultipleObjects Lib "user32" ( _
    ByVal nCount As Long, _
    pHandles As Long, _
    ByVal fWaitAll As Long, _
    ByVal dwMilliseconds As Long, _
    ByVal dwWakeMask As Long) As Long


Private Sub List1_Click()

End Sub

Private Sub Form_Load()

    List.AddItem "All Tests"
    List.AddItem "Test0001"
    List.AddItem "Test0002"
    List.AddItem "Test0003"
    List.AddItem "Test0004"
    List.AddItem "Test0005"
    List.AddItem "Test0006"
    List.AddItem "Test0007"
    List.AddItem "Test0008"
    List.AddItem "Test0009"
    List.AddItem "Test0010"
    List.AddItem "Test0011"
    List.AddItem "Test0012"
    List.AddItem "Test0013"
    List.AddItem "Test0014"
    List.AddItem "Test0015"
    List.AddItem "Test0016"
    List.AddItem "Test0017"
    List.AddItem "Test0018"
    List.AddItem "Test0019"
    List.AddItem "Test0020"
    List.AddItem "Test0021"
    List.AddItem "Test0022"
    List.AddItem "Test0023"
    List.AddItem "Test0024"
    List.AddItem "Test0025"
    
End Sub

Private Sub IETests_Click()

End Sub

Private Sub RunTests_Click()

    Dim Funct As Integer
    Funct = List.ListIndex
    MyFilea = CurDir & "\a.txt"
    MyFileb = CurDir & "\b.txt"
    MyFilec = CurDir & "\c.txt"
    
    MyFileLargetxt = CurDir & "\Large.txt"
    
    If (0 = Funct) Or (1 = Funct) Then
        Call Test0001
    End If
    If (0 = Funct) Or (2 = Funct) Then
        Call Test0002
    End If
    If (0 = Funct) Or (3 = Funct) Then
        Call Test0003
    End If
    If (0 = Funct) Or (4 = Funct) Then
        Call Test0004
    End If
    If (0 = Funct) Or (5 = Funct) Then
        Call Test0005
    End If
    If (0 = Funct) Or (6 = Funct) Then
        Call Test0006
    End If
    If (0 = Funct) Or (7 = Funct) Then
        Call Test0007
    End If
    If (0 = Funct) Or (8 = Funct) Then
        Call Test0008
    End If
    If (0 = Funct) Or (9 = Funct) Then
        Call Test0009
    End If
    If (0 = Funct) Or (10 = Funct) Then
        Call Test0010
    End If
    If (0 = Funct) Or (11 = Funct) Then
        Call Test0011
    End If
    If (0 = Funct) Or (12 = Funct) Then
        Call Test0012
    End If
    If (0 = Funct) Or (13 = Funct) Then
        Call Test0013
    End If
    If (0 = Funct) Or (14 = Funct) Then
        Call Test0014
    End If
    If (0 = Funct) Or (15 = Funct) Then
        Call Test0015
    End If
    If (0 = Funct) Or (16 = Funct) Then
        Call Test0016
    End If
    If (0 = Funct) Or (17 = Funct) Then
        Call Test0017
    End If
    If (0 = Funct) Or (18 = Funct) Then
        Call Test0018
    End If
    If (0 = Funct) Or (19 = Funct) Then
        Call Test0019
    End If
    If (0 = Funct) Or (20 = Funct) Then
        Call Test0020
    End If
    If (0 = Funct) Or (21 = Funct) Then
        Call Test0021
    End If
    If (0 = Funct) Or (22 = Funct) Then
        Call Test0022
    End If
    If (0 = Funct) Or (23 = Funct) Then
        Call Test0023
    End If
    If (0 = Funct) Or (24 = Funct) Then
        Call Test0024
    End If
    If (0 = Funct) Or (25 = Funct) Then
        Call Test0025
    End If
End Sub
Public Sub Test0001()
    i = WinBlitReader.TextFont.Size
    WinBlitReader.TextFont.Size = 10
    WinBlitReader.LoadData 1001, MyFilea
    WinBlitReader.Display
    WinBlitReader.Start
    Text.Text = "Test0001 - Font Size should have shrunk"
    Wait 2
    WinBlitReader.Stop
    WinBlitReader.TextFont.Size = i
    WinBlitReader.UnloadData
End Sub
Public Sub Test0002()
    a = WinBlitReader.CursorTextColor
    b = WinBlitReader.CursorFillColor
    c = WinBlitReader.ScreenTextColor
    D = WinBlitReader.ScreenFillColor
    e = WinBlitReader.ScreenBackColor
    
    WinBlitReader.CursorTextColor = vbBlue
    WinBlitReader.CursorFillColor = vbRed
    WinBlitReader.ScreenTextColor = vbGreen
    WinBlitReader.ScreenFillColor = vbYellow
    WinBlitReader.ScreenBackColor = vbCyan
    WinBlitReader.LoadData 1001, MyFilea
    WinBlitReader.Display
    WinBlitReader.Start
    Text.Text = "Test0002 - Colors should have changed"
    Wait 2
    WinBlitReader.Stop
    WinBlitReader.UnloadData
    
    WinBlitReader.CursorTextColor = a
    WinBlitReader.CursorFillColor = b
    WinBlitReader.ScreenTextColor = c
    WinBlitReader.ScreenFillColor = D
    WinBlitReader.ScreenBackColor = e
    
End Sub
Public Sub Test0003()
    WinBlitReader.ShowAbout
    Text.Text = "Test0003 - Should have shown about box"
    Wait 2
    WinBlitReader.Register
    Text.Text = "Test0003 - Should have shown Register"
    Wait 2
    WinBlitReader.ShowHelp
    Text.Text = "Test0003 - Should be showing help"
    Wait 2
End Sub
Public Sub Test0004()
End Sub
Public Sub Test0005()
    WinBlitReader.LoadData 1001, MyFileb
    WinBlitReader.Display
    WinBlitReader.LoadSettings "Regular - Characters Sample", 0
    WinBlitReader.Start
    Text.Text = "Test0005 - Regular - Characters Sample"
    Wait 3
    WinBlitReader.Stop
    
    WinBlitReader.LoadSettings "Regular - Columns Sample1", 0
    WinBlitReader.Start
    Text.Text = "Test0005 - Regular - Columns Sample1"
    Wait 3
    WinBlitReader.Stop
    
    WinBlitReader.LoadSettings "Regular - Coulmns Sample2", 0
    WinBlitReader.Start
    Text.Text = "Test0005 - Columns Sample2"
    Wait 3
    WinBlitReader.Stop
    
    WinBlitReader.LoadSettings "Regular - Words Sample", 0
    WinBlitReader.Start
    Text.Text = "Test0005 - Regular - Words Sample"
    Wait 3
    WinBlitReader.Stop
    
    WinBlitReader.LoadSettings "S-Shaped Columns Sample", 0
    WinBlitReader.Start
    Text.Text = "Test0005 -S-Shaped Columns Sample"
    Wait 3
    WinBlitReader.Stop
    
    WinBlitReader.LoadSettings "Static - Characters Sample", 0
    WinBlitReader.Start
    Text.Text = "Test0005 - Static - Characters Sample"
    Wait 3
    WinBlitReader.Stop
    
    WinBlitReader.LoadSettings "Static - Columns Sample1", 0
    WinBlitReader.Start
    Text.Text = "Test0005 - Static - Columns Sample1"
    Wait 3
    WinBlitReader.Stop
    
    WinBlitReader.LoadSettings "Static - Columns Sample2", 0
    WinBlitReader.Start
    Text.Text = "Test0005 - Static - Columns Sample2"
    Wait 3
    WinBlitReader.Stop
    
    WinBlitReader.LoadSettings "Static - Words Sample", 0
    WinBlitReader.Start
    Text.Text = "Test0005 - Static - Words Sample"
    Wait 3
    WinBlitReader.Stop
    
    WinBlitReader.UnloadData
    
End Sub
Public Sub Test0006()
    WinBlitReader.LoadSettings "Regular - Words Sample", 0
    Dim i As Integer
    i = WinBlitReader.DisplayPeriod
    WinBlitReader.DisplayPeriod = 1000
    WinBlitReader.LoadData 1001, MyFileb
    WinBlitReader.Display
    Text.Text = "Test0006 - Should Display for a second"
    WinBlitReader.Start
    Wait 4
    WinBlitReader.DisplayPeriod = 0
    WinBlitReader.Pause
    i = WinBlitReader.BaseTime
    WinBlitReader.BaseTime = 50
    Text.Text = "Test0006 - Should get a lot faster now.. "
    WinBlitReader.Pause
    Wait 4
    WinBlitReader.BlackoutPeriod = i
    WinBlitReader.Stop
    WinBlitReader.UnloadData
    WinBlitReader.LoadSettings "Static - Characters Sample", 0
    WinBlitReader.BaseTime = 1000
    WinBlitReader.BlackoutPeriod = -50
    WinBlitReader.LoadData 1001, MyFileb
    WinBlitReader.Display
    WinBlitReader.Start
    Text.Text = "Test0006 - Should blackout for a half-second"
    Wait 4
    WinBlitReader.Stop
    WinBlitReader.UnloadData
End Sub
Public Sub Test0007()

    WinBlitReader.LoadData 1001, MyFilec
    WinBlitReader.Display
    WinBlitReader.LoadSettings "Regular - Words Sample", 0
        
    WinBlitReader.PageDown 1
    WinBlitReader.PageDown 1
    Text.Text = "Test0007 - Should have paged down twice"
    Wait 2
    
    WinBlitReader.LineDown 1
    Text.Text = "Test0007 - Should have gone down one line"
    Wait 2
    
    WinBlitReader.LineUp 2
    Text.Text = "Test0007 - Should have gone up 2 lines"
    Wait 2
    
    WinBlitReader.PageUp 1
    Text.Text = "Test0007 - Should have gone up 1 page"
    Wait 2
    
    WinBlitReader.UnloadData

End Sub
Public Sub Test0008()

    WinBlitReader.LoadSettings "Regular - Words Sample", 0
    
    WinBlitReader.LoadData 1001, MyFileLargetxt
    WinBlitReader.Display
    Text.Text = "Text0008 - Should have loaded large txt file"
    Wait 10
    WinBlitReader.UnloadData

End Sub
Public Sub Test0009()
    WinBlitReader.LoadSettings "Static - Characters Sample", 0
    WinBlitReader.ShowTrackBar (False)
    WinBlitReader.ShowControls (False)
    WinBlitReader.ShowStatusBar (False)
    WinBlitReader.ShowMetafile (True)
    WinBlitReader.LoadData 1001, MyFilea
    WinBlitReader.Display
    Text.Text = "Test0009 - Should be showing no controls  but a metafile"
    Wait 2
    WinBlitReader.ShowTrackBar (True)
    WinBlitReader.ShowControls (True)
    WinBlitReader.ShowStatusBar (True)
    WinBlitReader.ShowMetafile (False)
    WinBlitReader.UnloadData

End Sub
Public Sub Test0010()
End Sub
Public Sub Test0011()
End Sub
Public Sub Test0012()
End Sub
Public Sub Test0013()
End Sub
Public Sub Test0014()
End Sub
Public Sub Test0015()
End Sub
Public Sub Test0016()
End Sub
Public Sub Test0017()
End Sub
Public Sub Test0018()
End Sub
Public Sub Test0019()
End Sub
Public Sub Test0020()
End Sub
Public Sub Test0021()
End Sub
Public Sub Test0022()
End Sub
Public Sub Test0023()
End Sub
Public Sub Test0024()
End Sub
Public Sub Test0025()
End Sub
Public Sub Wait(lNumberOfSeconds As Long)
    Dim ft As FILETIME
    Dim lBusy As Long
    Dim lRet As Long
    Dim dblDelay As Double
    Dim dblDelayLow As Double
    Dim dblUnits As Double
    Dim hTimer As Long
    
    hTimer = CreateWaitableTimer(0, True, App.EXEName & "Timer")
    
    If Err.LastDllError = ERROR_ALREADY_EXISTS Then
        ' If the timer already exists, it does not hurt to open it
        ' as long as the person who is trying to open it has the
        ' proper access rights.
    Else
        ft.dwLowDateTime = -1
        ft.dwHighDateTime = -1
        lRet = SetWaitableTimer(hTimer, ft, 0, 0, 0, 0)
    End If
    
    ' Convert the Units to nanoseconds.
    dblUnits = CDbl(&H10000) * CDbl(&H10000)
    dblDelay = CDbl(lNumberOfSeconds) * 1000 * 10000
    
    ' By setting the high/low time to a negative number, it tells
    ' the Wait (in SetWaitableTimer) to use an offset time as
    ' opposed to a hardcoded time. If it were positive, it would
    ' try to convert the value to GMT.
    ft.dwHighDateTime = -CLng(dblDelay / dblUnits) - 1
    dblDelayLow = -dblUnits * (dblDelay / dblUnits - _
        Fix(dblDelay / dblUnits))
    
    If dblDelayLow < CDbl(&H80000000) Then
        ' &H80000000 is MAX_LONG, so you are just making sure
        ' that you don't overflow when you try to stick it into
        ' the FILETIME structure.
        dblDelayLow = dblUnits + dblDelayLow
    End If
    
    ft.dwLowDateTime = CLng(dblDelayLow)
    lRet = SetWaitableTimer(hTimer, ft, 0, 0, 0, False)
    
    Do
        ' QS_ALLINPUT means that MsgWaitForMultipleObjects will
        ' return every time the thread in which it is running gets
        ' a message. If you wanted to handle messages in here you could,
        ' but by calling Doevents you are letting DefWindowProc
        ' do its normal windows message handling---Like DDE, etc.
        lBusy = MsgWaitForMultipleObjects(1, hTimer, False, _
            INFINITE, QS_ALLINPUT&)
        DoEvents
    Loop Until lBusy = WAIT_OBJECT_0
    
    ' Close the handles when you are done with them.
    CloseHandle hTimer

End Sub
