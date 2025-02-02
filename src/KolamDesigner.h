//  : main header file for the KolamDesigner application
//

#if !defined(AFX_KolamDesigner_H__23D156D8_23D7_41E1_997D_2947200F92F6__INCLUDED_)
#define AFX_KolamDesigner_H__23D156D8_23D7_41E1_997D_2947200F92F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "ChildView.h"
/////////////////////////////////////////////////////////////////////////////
// CKolamDesignerApp:
// See KolamDesigner.cpp for the implementation of this class
//

class CKolamDesignerApp : public CWinApp
{
// Construction			//nagata
public:					//nagata
	CKolamDesignerApp();	//nagata

// Attributes
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKolamDesignerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CKolamDesignerApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CKolamDesigner : public CWnd
{

// Attributes
public:
	CKolamDesigner();


// Generated message map functions
protected:
	//{{AFX_MSG(CKolamDesigner)

	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KolamDesigner_H__23D156D8_23D7_41E1_997D_2947200F92F6__INCLUDED_)
