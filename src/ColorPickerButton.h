/****************************************************************************

    Name: ColorPickerButton.h

    Desc: 色選択ボタンクラス．

  Author: reidphoa

****************************************************************************/
#if !defined(AFX_COLORPICKERBUTTON_H__B3199CB3_66EA_4C33_ABD3_291DDEECA87E__INCLUDED_)
#define AFX_COLORPICKERBUTTON_H__B3199CB3_66EA_4C33_ABD3_291DDEECA87E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CColorPickerButton : public CButton
{
public:

	CColorPickerButton();
	virtual ~CColorPickerButton();

	void SetColor(COLORREF color)
	{
		m_Color = color;
		if(::IsWindow(m_hWnd)) RedrawWindow();
	}

	COLORREF GetColor() const { return m_Color; }

	// オーバーライド
	//{{AFX_VIRTUAL(CColorPickerButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

protected:

	COLORREF m_Color;	// 保持している色

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CColorPickerButton)
//2009/11/26	
	afx_msg void OnClicked();
//2009/11/26
//	afx_msg BOOL OnClicked(UINT nID): 
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_COLORPICKERBUTTON_H__B3199CB3_66EA_4C33_ABD3_291DDEECA87E__INCLUDED_)
