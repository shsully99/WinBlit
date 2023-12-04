VERSION 5.00
Begin VB.Form LicenseProviderForm 
   Caption         =   "Provide a License"
   ClientHeight    =   4455
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8685
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   12
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   ScaleHeight     =   4455
   ScaleWidth      =   8685
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton ValidatePAK 
      Caption         =   "ValidatePAK"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   2520
      TabIndex        =   4
      Top             =   3240
      Width           =   1215
   End
   Begin VB.CommandButton GeneratePAK 
      Caption         =   "GeneratePAK"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   2520
      TabIndex        =   3
      Top             =   2520
      Width           =   1215
   End
   Begin VB.ListBox ProductSelect 
      Height          =   420
      IntegralHeight  =   0   'False
      ItemData        =   "VBPatLic.frx":0000
      Left            =   2520
      List            =   "VBPatLic.frx":000A
      TabIndex        =   2
      Top             =   1320
      Width           =   2535
   End
   Begin VB.TextBox PAK 
      Height          =   375
      Left            =   2520
      TabIndex        =   1
      Top             =   1920
      Width           =   6015
   End
   Begin VB.TextBox Key 
      Height          =   390
      Left            =   2520
      TabIndex        =   0
      Top             =   720
      Width           =   6015
   End
   Begin VB.Label ValText 
      Height          =   495
      Left            =   4080
      TabIndex        =   8
      Top             =   3240
      Width           =   3015
   End
   Begin VB.Label Label3 
      Caption         =   "PAK"
      Height          =   495
      Left            =   480
      TabIndex        =   7
      Top             =   1920
      Width           =   1215
   End
   Begin VB.Label ProductLabel 
      Caption         =   "Product"
      Height          =   495
      Left            =   480
      TabIndex        =   6
      Top             =   1320
      Width           =   1215
   End
   Begin VB.Label KeyLabel 
      Caption         =   "Key"
      Height          =   495
      Left            =   480
      TabIndex        =   5
      Top             =   720
      Width           =   1215
   End
End
Attribute VB_Name = "LicenseProviderForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub GeneratePAK_Click()

    ' Check key text entered
    If Key.Text = "" Then
        MsgBox "Please enter Key text"
        Exit Sub
    End If
    
    Dim iPSel As Integer
    iPSel = ProductSelect.ListIndex
    ' If no product selected then report error
    If iPSel = -1 Then
        MsgBox "Please select product"
        Exit Sub
    End If
   
    ' Create License Provider object
    Dim PatLic As LicenseProvider
    Set PatLic = CreateObject("PatLic.LicenseProvider.1")
    
    Dim iProduct As Integer
    iProduct = ProductSelect.ItemData(iPSel)
    
    Dim strPAK As String
    ' Get the PAK from the License Provider object
    PatLic.GeneratePAK Key.Text, iProduct, strPAK
    
    ' Display PAK
    PAK.Text = strPAK
    PAK.Refresh

End Sub


Private Sub ValidatePAK_Click()

    ' Check key text and PAK text entered
    If Key.Text = "" Then
        MsgBox "Please enter Key text"
        Exit Sub
    End If
    If PAK.Text = "" Then
        MsgBox "Please enter PAK text"
        Exit Sub
    End If
    
    
    Dim iPSel As Integer
    iPSel = ProductSelect.ListIndex
    ' If no product selected then report error
    If iPSel = -1 Then
        MsgBox "Please select product"
        Exit Sub
    End If
   
    
    
    ' Create License Provider object
    Dim PatLic As LicenseProvider
    Set PatLic = CreateObject("PatLic.LicenseProvider.1")
    
    Dim iProduct As Integer
    iProduct = ProductSelect.ItemData(iPSel)
    
    Dim strPAK As String
    
    ' Call ValidatePAK method on license provider
    Dim bValid As Long
    bValid = PatLic.ValidatePAK(Key.Text, iProduct, PAK.Text)
    
    ' Output success/failure string and refresh to display it
    If bValid = 0 Then
        ValText.Caption = " ** Failed **"
    Else
        ValText.Caption = " ** Succeeded **"
    End If
    
    ValText.Refresh
    
 End Sub
