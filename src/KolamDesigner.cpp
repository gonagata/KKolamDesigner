// KolamDesigner.cpp : Defines the class behaviors for the application.
//
// �����̏��Ԃ�ς���ƃG���[������
#include "stdafx.h"
#include "KolamDesigner.h"
//#include "ChildView.h"  2009/12/09 �����Ă��ǂ�
//#include "ParameterDlg.h"  2009/12/09 �����Ă��ǂ�
#include "MainFrm.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// KolamDesignerApp

BEGIN_MESSAGE_MAP(CKolamDesignerApp, CWinApp)
	//{{AFX_MSG_MAP(CKolamDesignerApp)
	
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CKolamDesignerApp construction

CKolamDesignerApp::CKolamDesignerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CKolamDesignerApp object

CKolamDesignerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CKolamDesignerApp initialization

BOOL CKolamDesignerApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object.
	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	// create and load the frame with its resources
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);

	// The one and only window has been initialized, so show and update it.
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	// 2009/11/16 ParameterDialog ���N�����Ɂ@CChildView::OnParameterSet()���N�����ɌĂяo�� by Nagata from Atsushi777
	//pFrame->PostMessage(WM_COMMAND, /*CChildView::OnParameterSet()�̃R�}���hID*/);
	pFrame->PostMessage(WM_COMMAND, ID_PARAMETER_SET);
	//end

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };

	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnUpdateViewDrawImages(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewDrawFude(CCmdUI* pCmdUI);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
//	DDX_Control(pDX, IDOK, m_Switch); m_drawMode ���g������ǂ����H
//	DDX_Control(pDX, IDOK, m_smoothmod); //for check marking
		// for 4.0 menu ��DrawMode �� FudeMode��Check��̂���
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DRAW_IMAGES, OnUpdateViewDrawImages)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DRAW_FUDE, OnUpdateViewDrawFude)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CKolamDesignerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
////////////////////////////////////////////end
// added for alternated check for menu of View DrawMode and FudeMode


void CAboutDlg::OnUpdateViewDrawImages(CCmdUI* pCmdUI) 
{
	// TODO: ���̈ʒu�� command update UI �n���h���p�̃R�[�h��ǉ����Ă�������
// �G���ɂȂ�̂ł͂���
//	if( m_Switch == 1) pCmdUI->SetCheck(1); // on
//	else pCmdUI->SetCheck(0); // off
 
}

void CAboutDlg::OnUpdateViewDrawFude(CCmdUI* pCmdUI) 
{
	// TODO: ���̈ʒu�� command update UI �n���h���p�̃R�[�h��ǉ����Ă�������
//	if( m_smoothmod ==1) pCmdUI->SetCheck(1); // on
//	else pCmdUI->SetCheck(0); // off
// �G���@m_smoothmod : ��`����Ă��Ȃ����ʎq�ł� 	

}

void CAboutDlg::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
	
	CDialog::OnOK();
}
/*end*/
