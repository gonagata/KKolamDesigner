// ParameterDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "KolamDesigner.h"
#include "ParameterDlg.h"

//{+ フックのために追加 ColorDlg()関数
#include "DialogFunc.h" //カラーdialogを英語化のため追加
#include "ColorPickerButton.h"	// 色付けボタンのため

//2009/12/9 無くてもOK　#include "ChildView.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParameterDlg ダイアログ ParameterDlg.cc 


CParameterDlg::CParameterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CParameterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParameterDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//	以下初期値
	m_ImageSizWidth = 250; //m_ImageSizHeight;	
	m_KomaX_N = 3;
	m_KomaY_M = 3;
	m_KomaSize = 250/3; // m_ImageSizWidth /m_KomaX_N;
	m_KomaType = 99;	// no change // -1 all nothing,//<0,0-16 one point connection,15-80 two points
	m_M_Max = 1850/3;	// 1850/m_KomaX_N; 50x37 as m_koM[]
	m_SleepTime = 0;	// non animation;
	m_SwellMode = 0;	// 0:Normal 1:Blackground/WhiteStroke ForSwellPaper 2:NightShow 3:ColorButton 4:Edge-line
//	m_ImageFileName = _T("Name"); //= _T("KolamImages\\");
	m_ImageName = _T("Name"); //= _T("KolamImages\\");
	
///*	//  2009/10/20 ColorPickerButton を追加不要になる　
//	m_GroundColor	= RGB(150, 100, 0); // KoMa groundcolor	
//	m_TileColor		= RGB(190, 130, 0); // KoMa tile-color
//	m_AmiLnColor	= RGB(250,  30, 0);	// KoMa amimate-line-color 
//	m_FnlLnColor	= RGB(200, 255, 200); 	// KoMa final-line-color
//*/
	m_pParent = pParent;
	//}}AFX_DATA_INIT
}

void CParameterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParameterDlg)
	DDX_Text(pDX, IDC_EDITImageSizeWidth, m_ImageSizWidth);
	DDX_Text(pDX, IDC_KONO_X_N, m_KomaX_N);
	DDX_Text(pDX, IDC_KONO_Y_M, m_KomaY_M);
	DDX_Text(pDX, IDC_KOMASIZE, m_KomaSize);
	DDX_Text(pDX, IDC_M_MAX, m_M_Max);
	DDX_Text(pDX, IDC_KOMATYPE, m_KomaType); 
	DDX_Text(pDX, IDC_SLEEPTIME, m_SleepTime);
//	DDX_Text(pDX, IDC_EDITImageFileName, m_ImageFileName);
	DDX_Text(pDX, IDC_EDITImageName, m_ImageName);
//	DDX_Text(pDX, IDC_SWELLMODE, m_SwellMode);
	DDX_CBIndex(pDX, IDC_COMBO_COLOR, m_SwellMode);
	DDX_Control(pDX, IDC_BTN1_GCOLOR, m_BtnGColor);// ColorPickerButton用
	DDX_Control(pDX, IDC_BTN2_TCOLOR, m_BtnTColor);// ColorPickerButton用
	DDX_Control(pDX, IDC_BTN3_ACOLOR, m_BtnAColor);// ColorPickerButton用
	DDX_Control(pDX, IDC_BTN4_FCOLOR, m_BtnFColor);// ColorPickerButton用

	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CParameterDlg, CDialog)
	//{{AFX_MSG_MAP(CParameterDlg)
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_EDITImageSizeWidth, OnChangeEdit1)
	ON_EN_CHANGE(IDC_KONO_X_N, OnChangeEdit1)
	ON_EN_CHANGE(IDC_KONO_Y_M, OnChangeEdit1) //2009/11/10 by Nagata
	ON_EN_CHANGE(IDC_KOMATYPE, OnChangeEdit1)
	ON_EN_CHANGE(IDC_SLEEPTIME, OnChangeEdit1) //2009/11/7 by Nagata
	ON_EN_CHANGE(IDC_EDITImageFileName, OnChangeImageName)
	ON_CBN_SELENDOK(IDC_COMBO_COLOR, OnSelendokComboColor)
//2009/12/8	ON_BN_CLICKED(IDC_BTN1_GCOLOR, OnBtn1Gcolor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParameterDlg メッセージ ハンドラ
/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////
// オーバーライドしたCreate()関数
BOOL CParameterDlg::Create(CWnd * pWnd)
{
    m_pParent = pWnd;
    BOOL bret = 
        CDialog::Create( CParameterDlg::IDD, m_pParent);
    if( bret == TRUE){
		// 不可視で生成しておく
        this->ShowWindow( SW_HIDE);
		//this->SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOSIZE);//最前面表示
    }
    return bret;
}
//////////////////////////////////////////
//
//【PostNCDestroyのオーバーライド】
void CParameterDlg::PostNcDestroy() 
{
	CDialog::PostNcDestroy();
}
////////////////////////////////////////////////
//
// 【WM_CLOSEのメッセージマップのオーバーライド】
void CParameterDlg::OnClose() 
{
	// モーダルダイアログとしてCLOSEしてしまわずに、
	// 隠すだけにする
	this->ShowWindow(SW_HIDE);
    
}

////////////////////////////////////////////////////////////////
/*
void CParameterDlg::OnOk() //OKボタンがないから　使用していないのではないか？
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください

	//CDialog::OnOK(); // コメントアウト
	UpdateData(TRUE);
	// Viewを更新する
	UpdateView();
	UpdateData(FALSE); // set the final action
}
*/

/*
void CParameterDlg::OnChangeKoNoYM() 
{
	// TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
	// 内での論理和の ENM_CHANGE フラグ付きで CRichEditCrtl().SetEventMask()
	// メッセージをコントロールへ送るために CDialog::OnInitDialog() 関数をオーバー
	// ライドしない限りこの通知を送りません。
	
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(TRUE);
	UpdateView();
	UpdateData(FALSE);

}
void CParameterDlg::OnChangeKomaType() 
{
	// TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
	// 内での論理和の ENM_CHANGE フラグ付きで CRichEditCrtl().SetEventMask()
	// メッセージをコントロールへ送るために CDialog::OnInitDialog() 関数をオーバー
	// ライドしない限りこの通知を送りません。
	
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(TRUE);
	UpdateView();
	UpdateData(FALSE);
	// 効かないm_KomaType = ((CChildView*)m_pParent)->m_komType; // 2009/11/7
}
*/

void CParameterDlg::OnChangeEdit1() // for write the changed variable
{
	// TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
	// 内での論理和の ENM_CHANGE フラグ付きで CRichEditCrtl().SetEventMask()
	// メッセージをコントロールへ送るために CDialog::OnInitDialog() 関数をオーバー
	// ライドしない限りこの通知を送りません。
	
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	UpdateData(TRUE);

	//以下　本Dialog内で計算結果を直に表示する
	m_KomaSize = m_ImageSizWidth/m_KomaX_N;
	m_M_Max = 1850/m_KomaX_N; //YJiku 駒数Mの最大 max50x37 as m_koM[]
	
	UpdateView();// ここでParameterSet()の役割
	UpdateData(FALSE); // set the final action
}

/////////////////////////////////////////
//
//			Viewをパラメータダイアログ側から更新する関数
//			ここで以前のChildViewのParameterSet()の役割
void CParameterDlg::UpdateView()
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
//	((CChildView*)m_pParent)->UpdateData(FALSE); //　by Yoshino, 2009/11/22 by Nagata

	// 駒が増える場合を想定して、現在データを記録して置く// keep the old pattern in the old matrix
	for( short na = 0; na < (((CChildView*)m_pParent))->m_komaNoX *(((CChildView*)m_pParent))->m_komaNoY; na++)// keep the old pattern in the old matrix
	{
		short knx = na % ((CChildView*)m_pParent)->m_komaNoX;
		short kny = na / ((CChildView*)m_pParent)->m_komaNoX;
		((CChildView*)m_pParent)->m_koMxy[knx][kny] = ((CChildView*)m_pParent)->m_koM[na];
	}
	// 駒が増える場合を想定して、
	short sttX[10], sttY[10], m_komaNoXB= ((CChildView*)m_pParent)->m_komaNoX;// for multiLoop,
	if(((CChildView*)m_pParent)->m_loopNum > 0) // when multiLoop, memorize Number of starting KoMa to New Number
		for( short istt =0; istt <((CChildView*)m_pParent)->m_loopNum; istt++) //keepitng X,Y positions
		{
			sttX[istt] = ((CChildView*)m_pParent)->m_strtKoma[istt]%m_komaNoXB;
			sttY[istt] = ((CChildView*)m_pParent)->m_strtKoma[istt]/m_komaNoXB; 
		}
	// 駒数が変わったら　駒を描き直す

		// 駒数が変わったら　駒を描き直す
	((CChildView*)m_pParent)->drwNln = 0;
	if( ((CChildView*)m_pParent)->m_komaNoX != m_KomaX_N || ((CChildView*)m_pParent)->m_komaNoY != m_KomaY_M)
	{ 

		((CChildView*)m_pParent)->drwNln = 2;// to draw green dot in the rect area set by Key B
		((CChildView*)m_pParent)->LMbX = ((CChildView*)m_pParent)->LMbY = 0;		// to assign the copied rect area 
		((CChildView*)m_pParent)->LMeX = ((CChildView*)m_pParent)->m_komaNoX -1;
		((CChildView*)m_pParent)->LMeY = ((CChildView*)m_pParent)->m_komaNoY -1; 
		((CChildView*)m_pParent)->m_komaNoX = m_KomaX_N;
		((CChildView*)m_pParent)->m_komaNoY = m_KomaY_M;

		for ( short knxa =0; knxa < ((CChildView*)m_pParent)->m_komaNoX; knxa++)
			for ( short knya =0; knya < ((CChildView*)m_pParent)->m_komaNoY; knya++)
			{
				short naa = knxa +knya * ((CChildView*)m_pParent)->m_komaNoX;
				((CChildView*)m_pParent)->m_koM[naa] = ((CChildView*)m_pParent)->m_koMxy[knxa][knya];
			}	
		int ednumb = m_KomaX_N *m_KomaY_M * 2 - m_KomaX_N - m_KomaY_M;//KeyG で　駒が勝手にY軸で増えるのを防ぐ2011/06/10！
		((CChildView*)m_pParent)->m_ednum = ednumb;
		((CChildView*)m_pParent)->m_edpnm = (unsigned long)pow( 2.0, ednumb ) -1; // index edge patterns, except all of 0
		for( short ii = 0; ii < 3613; ii++) ((CChildView*)m_pParent)->m_edcd[ii] =0;

		if(((CChildView*)m_pParent)->m_loopNum > 0) // when multiLoop, change Number of starting KoMa to New Number
		for( short istt =0; istt <((CChildView*)m_pParent)->m_loopNum; istt++)
		{
			((CChildView*)m_pParent)->m_strtKoma[istt] = sttY[istt] * ((CChildView*)m_pParent)->m_komaNoX + sttX[istt];
		}
	}

// 2009/11/5 必要　画像サイズを正す　nagata
	((CChildView*)m_pParent)->m_kks = m_KomaSize;	// = m_ImageSizWidth/m_KomaX_N;  // kolam koma size in pixel
	((CChildView*)m_pParent)->m_imageSiH = ((CChildView*)m_pParent)->m_kks *((CChildView*)m_pParent)->m_komaNoX +45;  // size of image area m_paramDlg.m_ImageSizWidth; //450
	((CChildView*)m_pParent)->m_imageSiV = ((CChildView*)m_pParent)->m_kks *((CChildView*)m_pParent)->m_komaNoY +70;  // size of image area  
	((CChildView*)m_pParent)->m_komType = m_KomaType; // Type Number for all koma  
	//	((CChildView*)m_pParent)->m_swell	= m_SwellMode; 	//m_swell =0 day color, =1 for Swelling paper for braille, =2 night color 

	if( ((CChildView*)m_pParent)->m_komType < 0){
		//memset(m_koM, -1 & ~0xFF, sizeof(m_koM) );// 0< and 8 Lower-bit:0000 
		for( short ii = 0; ii < 1850; ii++)  ((CChildView*)m_pParent)->m_koM[ii] = short(0x8000); //-1 & ~0xFF;
			
	} else	if( ((CChildView*)m_pParent)->m_komType < 81){
		// short m_N81toE8B[81];  // 8bit number= N81toE8B[0-80 number];
		// short m_E8BtoN81[241];  // 0-80 number= E8BtoN81[8bit number Max 240];
		for( short ii = 0; ii < 1850; ii++)  ((CChildView*)m_pParent)->m_koM[ii] = ((CChildView*)m_pParent)->m_N81toE8B[((CChildView*)m_pParent)->m_komType];
			//memset(m_koM, m_komType, sizeof(m_koM) );  
	} else	if( ((CChildView*)m_pParent)->m_komType == 88) 
	{	
		((CChildView*)m_pParent)->m_komaNoX = m_KomaX_N = 10;
		((CChildView*)m_pParent)->m_komaNoY = m_KomaY_M = 9;
		((CChildView*)m_pParent)->m_kks		= m_KomaSize = 70;	// = m_ImageSizWidth/m_KomaX_N;  // kolam koma size in pixel
		((CChildView*)m_pParent)->m_imageSiH = ((CChildView*)m_pParent)->m_kks *((CChildView*)m_pParent)->m_komaNoX +45;  // size of image area m_paramDlg.m_ImageSizWidth; //450
		((CChildView*)m_pParent)->m_imageSiV = ((CChildView*)m_pParent)->m_kks *((CChildView*)m_pParent)->m_komaNoY +70;  // size of image area  
		m_ImageSizWidth = ((CChildView*)m_pParent)->m_kks * ((CChildView*)m_pParent)->m_komaNoX; // pixel size of one KoMa 	
		for( short na = 0; na < ((CChildView*)m_pParent)->m_komaNoX *((CChildView*)m_pParent)->m_komaNoY; na++)
								((CChildView*)m_pParent)->m_koM[na] = ((CChildView*)m_pParent)->m_N81toE8B[na%81];
	} 

	((CChildView*)m_pParent)->knap = 0;  //present and starting Koma number for tracing
	((CChildView*)m_pParent)->m_ednum = ((CChildView*)m_pParent)->m_komaNoX *((CChildView*)m_pParent)->m_komaNoY * 2 - ((CChildView*)m_pParent)->m_komaNoX - ((CChildView*)m_pParent)->m_komaNoY;
	((CChildView*)m_pParent)->m_edpnm = (unsigned long)pow( 2.0, ((CChildView*)m_pParent)->m_ednum ) -1; // index edge patterns, except all of 0
	((CChildView*)m_pParent)->m_memo = "";	
	bAutog = FALSE;

	((CChildView*)m_pParent)->Invalidate();
}//endof UpDateView

void CParameterDlg::UpdateViewColor()	//2009/12/9 to set ColorDlg
{

	((CChildView*)m_pParent)->Invalidate();

}//endof UpDateView

void CParameterDlg::OnChangeImageName() 
{
	// TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
	// 内での論理和の ENM_CHANGE フラグ付きで CRichEditCrtl().SetEventMask()
	// メッセージをコントロールへ送るために CDialog::OnInitDialog() 関数をオーバー
	// ライドしない限りこの通知を送りません。
	
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	// 変数を更新　

	UpdateData(TRUE);
//	UpdateView();　//2009/11/25 UpdateView()から切り離した
//	((CChildView*)m_pParent)->m_strFileTitle = m_ImageFileName; 	
	((CChildView*)m_pParent)->m_strFileTitle = m_ImageName; 	
	((CChildView*)m_pParent)->m_strImgName = m_ImageName; 	
	((CChildView*)m_pParent)->Invalidate();
	UpdateData(FALSE);
	
}

// 　2009/10/20 追加ComboBoxで色Modeを選択したとき　ボタン着色 
void CParameterDlg::OnSelendokComboColor() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

	UpdateData(TRUE);      //manual ( m_SwellMode  == 3)は自動的にColorButtonDialog変数
	if( m_SwellMode == 0) //normal, m_SwellModeは comboBoxによる入力変数
	{
		m_BtnGColor.SetColor(RGB(150, 100, 0));
		m_BtnTColor.SetColor(RGB(190, 130, 0));
		m_BtnAColor.SetColor(RGB(255, 0, 0));
		m_BtnFColor.SetColor(RGB(200, 255, 200));
	} else if( m_SwellMode == 1) //Black and white for swell paper
	{
		m_BtnGColor.SetColor(RGB(255, 255, 255)); 
		m_BtnTColor.SetColor(RGB(255, 255, 255));
		m_BtnAColor.SetColor(RGB(0, 0, 0));
		m_BtnFColor.SetColor(RGB(200, 255, 200));
	} else if( m_SwellMode == 2)	//night show
	{
		m_BtnGColor.SetColor(RGB(0, 0, 100)); 
		m_BtnTColor.SetColor(RGB(0, 0, 150));
		m_BtnAColor.SetColor(RGB(255, 0, 0));
		m_BtnFColor.SetColor(RGB(200, 255, 200));
	} /* else if( m_SwellMode == 4) //edge-line 固定値はないので不必要
	{
		//m_BtnGColor.SetColor(RGB(150, 100, 0));
		//m_BtnTColor.SetColor(RGB(190, 130, 0));
		//m_BtnAColor.SetColor(RGB(255, 0, 0));
		//m_BtnFColor.SetColor(RGB(200, 255, 200));
	} */ 
	((CChildView*)m_pParent)->Invalidate();	// Viewを更新 UpdateView(); の代わり
	UpdateData(FALSE); // set the final action
}///////////////end

/*2009/12/8
void CParameterDlg::OnBtn1Gcolor() //　現在効かない
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

	MessageBox(_T("here pass"));
	UpdateData(TRUE);
	((CChildView*)m_pParent)->m_grdColor = m_BtnGColor.GetColor();
//	((CChildView*)m_pParent)->Invalidate();	// Viewを更新 UpdateView(); の代わり
	 
	CChildView*  Parnet_View = (CChildView*)m_pParent;
	UpdateData(FALSE); // set the final action
	Parnet_View->Invalidate(FALSE);  // 無効にしただけ。そのうちにWM_PAINTが発行されるかもネ・・・の状態
	Parnet_View->UpdateWindow();     // WM_PAINTの発行を強制
	
}
*/
