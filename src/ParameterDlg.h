////// ParameterDlg.h : ヘッダー ファイル/
#if !defined(AFX_PARAMETERSETDLG_H__98EE37B8_03E9_42EA_A93A_13A9B0375655__INCLUDED_)
#define AFX_PARAMETERSETDLG_H__98EE37B8_03E9_42EA_A93A_13A9B0375655__INCLUDED_
///////PARAMETERSETDLG_Hがあるのは　なにかおかしいが　どうするか 2009/10/14 /////////////////////////////////////////////////////////////////

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//
#include "ColorPickerButton.h"	// 2009/10/14 色つきボタンにする　助言　by 吉野様
//#include "ChildView.h"	// 2009/10/27 エラーを防ぐためコメントアウト t.yoshino

// CParameterDlg ダイアログ

class CParameterDlg : public CDialog
{
// コンストラクション
public:
	CParameterDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

	// CParameterDlg::Createメソッドをオーバーライド t.yoshino
	BOOL Create(CWnd * pWnd);

// Attributes
public:
	// >
	// パラメータダイアログ側からViewを更新する関数 t.yoshino
	void UpdateView();

	void UpdateViewColor();//2009/12/9 to set ColorDlg

	// 2009/10/09 ColorDialogInEnglish 保持している色
	/*
	void SetColor(COLORREF color)
	{
		m_Color = color;
		if(::IsWindow(m_hWnd)) RedrawWindow();
	}
	COLORREF GetColor() const { return m_Color; }
	*/
	// ダイアログ データ
	//{{AFX_DATA(CParameterDlg)
	enum { IDD = IDD_ParameterDIALOG };

	// 2009/10/14 色つきボタンにする　助言　by 吉野様
	CColorPickerButton	m_BtnFColor;	//	changed from CButton	m_BtnFColo;
	CColorPickerButton	m_BtnAColor;	//	changed from CButton	m_BtnAColo;
	CColorPickerButton	m_BtnTColor;	//	changed from CButton	m_BtnTColo;
	CColorPickerButton	m_BtnGColor;	//	changed from CButton	m_BtnGColo;

//		2009/10/20 カラーピッカーボタンにより不要
//	COLORREF m_GroundColor;		// KoMa ground-color = RGB(150, 100, 0); 
//	COLORREF m_TileColor;		// KoMa tile-color = RGB(190, 130, 0); 
//	COLORREF m_AmiLnColor;		// KoMa amimate-line-color = RGB(250, 30, 0); 
//	COLORREF m_FnlLnColor;		// KoMa final-line-color = RGB( ,  , 0); 

	int m_ImageSizWidth;	//int m_ImageSizHeight
	int m_KomaX_N;
	int m_KomaY_M;
	int m_KomaSize;
	int m_M_Max;	//YJiku 駒数Mの最大
	int m_SleepTime;
	int m_SwellMode;        //m_SwellModeは comboBoxによる入力変数
	short m_KomaType;// 負入力が不都合 int でも同じ　予めの数値にーを入れるとOK
//	CString m_ImageFileName;
	CString m_ImageName;
	CWnd * m_pParent;// 呼び出し元ウィンドウを特定するためのポインタ変数の追加 t.yoshino
	//}}AFX_DATA

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CParameterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL


// インプリメンテーション
protected:

	//COLORREF m_Color;	// 2009/10/09 ColorEnglish 保持している色

	// 生成されたメッセージ マップ関数
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
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_PARAMETERSETDLG_H__98EE37B8_03E9_42EA_A93A_13A9B0375655__INCLUDED_)
