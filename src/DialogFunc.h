// DialogFunc.h
#pragma once

// カラー選択ダイアログ表示関数
// (オーナーウィンドウ, 結果格納COLORREF, 初期カラー, 初期カラーを使うかどうか)
BOOL ColorDlg(HWND hWnd, COLORREF* p_crResult, 
			  COLORREF crFirst, BOOL bUseFirstColor, DWORD dwSpCustomColors[] );
// プロトタイプ宣言
LRESULT CALLBACK LocalHookProc (int nCode, WPARAM wParam ,LPARAM lParam );
int AfxMessageBoxHooked( LPCSTR message , UINT nType );

int	HookFileDialogDoModal( CFileDialog * pFileDialog );
/////////end///////////////////////////////////////