// ColorPickerButton.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"

#include "ColorPickerButton.h"
#include "resource.h"  // 2009/10/22 下の"ParameterDlg.h" を活かすため
#include "ParameterDlg.h" // 2009/10/20 色ボタンが押されたら
#include "ChildView.h" // 2009/10/27
//{+ フックのために追加 ColorDlg()関数
#include "DialogFunc.h"
//+}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
    Name: CColorPickerButton()
    Desc: コンストラクタ.
     Arg: ---
  Return: ---
****************************************************************************/
CColorPickerButton::CColorPickerButton():
	m_Color(::GetSysColor(COLOR_APPWORKSPACE))
{
}

/****************************************************************************
    Name: CColorPickerButton()
    Desc: デストラクタ.
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
    Desc: オーナードロー．ボタンを描画する．
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
    Desc: クリックされたとき，色選択ダイアログを表示する．
     Arg: ---
  Return: ---
****************************************************************************/
//2009/11/26 
void CColorPickerButton::OnClicked() 
//2009/11/26
//BOOL CColorPickerButton::OnClicked(UINT nID)
{
/* コメントアウトした呼び出し部分
	CColorDialog dlg(m_Color);
	if(dlg.DoModal() != IDOK) return;
	SetColor(dlg.GetColor());
*/
	//+{ 追加
	COLORREF crSelected;	// 選択された色
	COLORREF crFirst;		// 初期色
	
	crFirst = m_Color;	// 初期選択色の設定
	// カスタムカラー配列を最初から独自指定する場合
	static DWORD dwCustomColor[16];
	static int first = 1;
	// 初期カスタムカラーの設定(最初の１回だけ実行)
	if(first == 1)
	{
		for(int i=0; i < 16 ; i++)
		{
			// 全部白から始める場合
			dwCustomColor[i] = RGB(255,255,255);
			// 肌色系の階のカスタムカラー配列にする場合
			//dwCustomColor[i] = RGB(255, 150+ i*5, 100 + i* 5);	
		}
		first =2;
	}

	crSelected = m_Color;

	// カスタムカラー配列を独自指定して呼び出し
	if( ColorDlg( this->m_hWnd, &crSelected, crFirst ,TRUE, dwCustomColor ) )
	{
		// 選択された色をcrSelectedから受け取ります。
		SetColor(crSelected);
		
		// 2009/10/22 色ボタンが押されたら m_SwellMode に強制的に=3 を与える
		// 2009/10/27 t.yoshino
		// m_SwellModeはパラメータダイアログの変数であり、これを変えただけでは
		// 描画キャンバスであるChildViewの表示は更新されない。
		// 親ウィンドウであり描画キャンバスであるChildViewの
		// m_swellも更新してはじめて描画毎(OnPaint)に色が更新されるようになる。
		CParameterDlg* pParamDlg = (CParameterDlg*)GetParent(); // パラメータダイアログの参照を取得
		pParamDlg->m_SwellMode = 3;	// m_SwellModeを3に
		pParamDlg->UpdateData(FALSE); // コントロールボックス表示に反映させる

/*
	//2009/11/25 ColorDialogはカーソルをViewにしないでも即反映
	//	但し　これを入れると　Windowを閉じたとき　エラーが起こる。
	//  例外処理 (初回) は KolamDesigner.exe (MSVCRTD.DLL) にあります: 0xC0000005: Access Violation。
	CChildView* pChildView = (CChildView*)GetParent(); // 参照を取得
	pChildView->m_grdColor = pParamDlg->m_BtnGColor.GetColor();
	pChildView->m_tilColor = pParamDlg->m_BtnTColor.GetColor();
	pChildView->m_amiColor = pParamDlg->m_BtnAColor.GetColor();
	pChildView->m_fnlColor = pParamDlg->m_BtnFColor.GetColor();
	pParamDlg->UpdateViewColor();  //2009/12/9 to set ColorDlg、
	//UpdateViewの最後の((CChildView*)m_pParent)->Invalidate(); の代わり、
//	pChildView->Invalidate(); これでは即反映しない
*/

//2009/11/26'OnClicked' : 関数は 'void' 型として宣言されていますが、値を返しました。
// それでコメント化	return FALSE;
	}
}
/////////////end