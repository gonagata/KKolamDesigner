// ColorPickerButton.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"

#include "ColorPickerButton.h"
#include "resource.h"  // 2009/10/22 ����"ParameterDlg.h" ������������
#include "ParameterDlg.h" // 2009/10/20 �F�{�^���������ꂽ��
#include "ChildView.h" // 2009/10/27
//{+ �t�b�N�̂��߂ɒǉ� ColorDlg()�֐�
#include "DialogFunc.h"
//+}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
    Name: CColorPickerButton()
    Desc: �R���X�g���N�^.
     Arg: ---
  Return: ---
****************************************************************************/
CColorPickerButton::CColorPickerButton():
	m_Color(::GetSysColor(COLOR_APPWORKSPACE))
{
}

/****************************************************************************
    Name: CColorPickerButton()
    Desc: �f�X�g���N�^.
     Arg: ---
  Return: ---
****************************************************************************/
CColorPickerButton::~CColorPickerButton()
{
}

/****************************************************************************
    Name: PreSubclassWindow()
    Desc: ---
     Arg: ---
  Return: ---
****************************************************************************/
void CColorPickerButton::PreSubclassWindow() 
{
	ModifyStyle(0, BS_OWNERDRAW);

	CButton::PreSubclassWindow();
}

/****************************************************************************
    Name: DrawItem()
    Desc: �I�[�i�[�h���[�D�{�^����`�悷��D
     Arg: ---
  Return: ---
****************************************************************************/
void CColorPickerButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	ASSERT(lpDrawItemStruct);

	CDC*	pDC		= CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect	rcBtn	= lpDrawItemStruct->rcItem;
	UINT	nState	= lpDrawItemStruct->itemState;
	UINT	nStyle	= GetStyle();

	//-----------------------------------------------------------------------
	// Draw outer edge.

	UINT nFrameState = DFCS_BUTTONPUSH | DFCS_ADJUSTRECT;

	if(nState & ODS_SELECTED) nFrameState |= DFCS_PUSHED;
	if(nState & ODS_DISABLED) nFrameState |= DFCS_INACTIVE;
	if(nStyle & BS_FLAT) nFrameState |= DFCS_FLAT;
	
	pDC->DrawFrameControl(&rcBtn, DFC_BUTTON, nFrameState);

	if(nState & ODS_SELECTED) rcBtn.OffsetRect(1, 1);

	//-----------------------------------------------------------------------
	// Draw focus.

	if(nState & ODS_FOCUS) pDC->DrawFocusRect(&rcBtn);

	//-----------------------------------------------------------------------
	// Draw color selected in the control.

	rcBtn.DeflateRect(::GetSystemMetrics(SM_CXEDGE), ::GetSystemMetrics(SM_CYEDGE));

	pDC->FillSolidRect(&rcBtn, m_Color);

	::FrameRect(pDC->m_hDC, &rcBtn, (HBRUSH)::GetStockObject(BLACK_BRUSH));

}

/****************************************************************************

    Message Handlers

****************************************************************************/
BEGIN_MESSAGE_MAP(CColorPickerButton, CButton)
	//{{AFX_MSG_MAP(CColorPickerButton)
//2009/11/26	
ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
//2009/11/26
//	ON_CONTROL_REFLECT_EX(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/****************************************************************************
    Name: OnClicked()
    Desc: �N���b�N���ꂽ�Ƃ��C�F�I���_�C�A���O��\������D
     Arg: ---
  Return: ---
****************************************************************************/
//2009/11/26 
void CColorPickerButton::OnClicked() 
//2009/11/26
//BOOL CColorPickerButton::OnClicked(UINT nID)
{
/* �R�����g�A�E�g�����Ăяo������
	CColorDialog dlg(m_Color);
	if(dlg.DoModal() != IDOK) return;
	SetColor(dlg.GetColor());
*/
	//+{ �ǉ�
	COLORREF crSelected;	// �I�����ꂽ�F
	COLORREF crFirst;		// �����F
	
	crFirst = m_Color;	// �����I��F�̐ݒ�
	// �J�X�^���J���[�z����ŏ�����Ǝ��w�肷��ꍇ
	static DWORD dwCustomColor[16];
	static int first = 1;
	// �����J�X�^���J���[�̐ݒ�(�ŏ��̂P�񂾂����s)
	if(first == 1)
	{
		for(int i=0; i < 16 ; i++)
		{
			// �S��������n�߂�ꍇ
			dwCustomColor[i] = RGB(255,255,255);
			// ���F�n�̊K�̃J�X�^���J���[�z��ɂ���ꍇ
			//dwCustomColor[i] = RGB(255, 150+ i*5, 100 + i* 5);	
		}
		first =2;
	}

	crSelected = m_Color;

	// �J�X�^���J���[�z���Ǝ��w�肵�ČĂяo��
	if( ColorDlg( this->m_hWnd, &crSelected, crFirst ,TRUE, dwCustomColor ) )
	{
		// �I�����ꂽ�F��crSelected����󂯎��܂��B
		SetColor(crSelected);
		
		// 2009/10/22 �F�{�^���������ꂽ�� m_SwellMode �ɋ����I��=3 ��^����
		// 2009/10/27 t.yoshino
		// m_SwellMode�̓p�����[�^�_�C�A���O�̕ϐ��ł���A�����ς��������ł�
		// �`��L�����o�X�ł���ChildView�̕\���͍X�V����Ȃ��B
		// �e�E�B���h�E�ł���`��L�����o�X�ł���ChildView��
		// m_swell���X�V���Ă͂��߂ĕ`�斈(OnPaint)�ɐF���X�V�����悤�ɂȂ�B
		CParameterDlg* pParamDlg = (CParameterDlg*)GetParent(); // �p�����[�^�_�C�A���O�̎Q�Ƃ��擾
		pParamDlg->m_SwellMode = 3;	// m_SwellMode��3��
		pParamDlg->UpdateData(FALSE); // �R���g���[���{�b�N�X�\���ɔ��f������

/*
	//2009/11/25 ColorDialog�̓J�[�\����View�ɂ��Ȃ��ł������f
	//	�A���@���������Ɓ@Window������Ƃ��@�G���[���N����B
	//  ��O���� (����) �� KolamDesigner.exe (MSVCRTD.DLL) �ɂ���܂�: 0xC0000005: Access Violation�B
	CChildView* pChildView = (CChildView*)GetParent(); // �Q�Ƃ��擾
	pChildView->m_grdColor = pParamDlg->m_BtnGColor.GetColor();
	pChildView->m_tilColor = pParamDlg->m_BtnTColor.GetColor();
	pChildView->m_amiColor = pParamDlg->m_BtnAColor.GetColor();
	pChildView->m_fnlColor = pParamDlg->m_BtnFColor.GetColor();
	pParamDlg->UpdateViewColor();  //2009/12/9 to set ColorDlg�A
	//UpdateView�̍Ō��((CChildView*)m_pParent)->Invalidate(); �̑���A
//	pChildView->Invalidate(); ����ł͑����f���Ȃ�
*/

//2009/11/26'OnClicked' : �֐��� 'void' �^�Ƃ��Đ錾����Ă��܂����A�l��Ԃ��܂����B
// ����ŃR�����g��	return FALSE;
	}
}
/////////////end