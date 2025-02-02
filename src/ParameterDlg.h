////// ParameterDlg.h : �w�b�_�[ �t�@�C��/
#if !defined(AFX_PARAMETERSETDLG_H__98EE37B8_03E9_42EA_A93A_13A9B0375655__INCLUDED_)
#define AFX_PARAMETERSETDLG_H__98EE37B8_03E9_42EA_A93A_13A9B0375655__INCLUDED_
///////PARAMETERSETDLG_H������̂́@�Ȃɂ������������@�ǂ����邩 2009/10/14 /////////////////////////////////////////////////////////////////

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//
#include "ColorPickerButton.h"	// 2009/10/14 �F���{�^���ɂ���@�����@by �g��l
//#include "ChildView.h"	// 2009/10/27 �G���[��h�����߃R�����g�A�E�g t.yoshino

// CParameterDlg �_�C�A���O

class CParameterDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CParameterDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

	// CParameterDlg::Create���\�b�h���I�[�o�[���C�h t.yoshino
	BOOL Create(CWnd * pWnd);

// Attributes
public:
	// >
	// �p�����[�^�_�C�A���O������View���X�V����֐� t.yoshino
	void UpdateView();

	void UpdateViewColor();//2009/12/9 to set ColorDlg

	// 2009/10/09 ColorDialogInEnglish �ێ����Ă���F
	/*
	void SetColor(COLORREF color)
	{
		m_Color = color;
		if(::IsWindow(m_hWnd)) RedrawWindow();
	}
	COLORREF GetColor() const { return m_Color; }
	*/
	// �_�C�A���O �f�[�^
	//{{AFX_DATA(CParameterDlg)
	enum { IDD = IDD_ParameterDIALOG };

	// 2009/10/14 �F���{�^���ɂ���@�����@by �g��l
	CColorPickerButton	m_BtnFColor;	//	changed from CButton	m_BtnFColo;
	CColorPickerButton	m_BtnAColor;	//	changed from CButton	m_BtnAColo;
	CColorPickerButton	m_BtnTColor;	//	changed from CButton	m_BtnTColo;
	CColorPickerButton	m_BtnGColor;	//	changed from CButton	m_BtnGColo;

//		2009/10/20 �J���[�s�b�J�[�{�^���ɂ��s�v
//	COLORREF m_GroundColor;		// KoMa ground-color = RGB(150, 100, 0); 
//	COLORREF m_TileColor;		// KoMa tile-color = RGB(190, 130, 0); 
//	COLORREF m_AmiLnColor;		// KoMa amimate-line-color = RGB(250, 30, 0); 
//	COLORREF m_FnlLnColor;		// KoMa final-line-color = RGB( ,  , 0); 

	int m_ImageSizWidth;	//int m_ImageSizHeight
	int m_KomaX_N;
	int m_KomaY_M;
	int m_KomaSize;
	int m_M_Max;	//YJiku �M�̍ő�
	int m_SleepTime;
	int m_SwellMode;        //m_SwellMode�� comboBox�ɂ����͕ϐ�
	short m_KomaType;// �����͂��s�s�� int �ł������@�\�߂̐��l�Ɂ[�������OK
//	CString m_ImageFileName;
	CString m_ImageName;
	CWnd * m_pParent;// �Ăяo�����E�B���h�E����肷�邽�߂̃|�C���^�ϐ��̒ǉ� t.yoshino
	//}}AFX_DATA

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CParameterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL


// �C���v�������e�[�V����
protected:

	//COLORREF m_Color;	// 2009/10/09 ColorEnglish �ێ����Ă���F

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CParameterDlg)
	afx_msg void OnChangeEdit1();
	afx_msg void OnSelendokComboColor();
	afx_msg void OnClose();
//	afx_msg void OnChangeKoNoYM();
//	afx_msg void OnChangeKomaType();
//	afx_msg void OnChangeEDITImageFileName();
	afx_msg void OnChangeImageName();
//2009/12/8	afx_msg void OnBtn1Gcolor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_PARAMETERSETDLG_H__98EE37B8_03E9_42EA_A93A_13A9B0375655__INCLUDED_)
