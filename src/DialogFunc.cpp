#include "StdAfx.h"  // VC++のときインクルード
// StfAfx.hインクルード ﾌﾟﾘｺﾝﾊﾟｲﾙ済み～のエラーを出さないために必要
// ヘッダインクルード
#include "DialogFunc.h"

//////////////////////////////////////////////////////////////////
// フックハンドル用の変数をグローバルで宣言する。
HHOOK MyHookHandle;	// フックハンドル変数

int LangRep = 1;		// 書き換えを行うかどうかのフラグ

// OKの文字列と、キャンセルの文字列
// ボタンの文字を変更したい場合はここを変更してください
LPCSTR strOK = "OK";			// OKボタンの文字
LPCSTR strCancel = "Cancel";	// キャンセルボタンの文字
// フォント情報
LOGFONT rLogfont;			// 論理フォント変数
HFONT hFontSmall=NULL;		// 小さめのフォント
/////////////////////////////
// 置換情報構造体
typedef struct repItem {
	char strBefore[100];	// 置換前文字
	char strAfter[100];		// 置換後文字
	HFONT*	phFont;			// 適用フォントへのポインタ
} stRepItem;
// タイトルの情報と関連付ける置換配列
typedef struct repTitle {
	char strBefore[100];	// 置換前タイトル
	char strAfter[100];		// 置換後タイトル
	HFONT* phFont;			// 適用フォントへのポインタ
	repItem * pRepItem;		// 使用する置換配列
	int aryLength;
} stRepTitle;

// 置換情報を含む構造体配列定義
stRepItem repColDlg[] =
{
	{"キャンセル" , "Cancel" , NULL},
	{"基本色(&B):", "Basic Colors", NULL},
//	{"作成した色(&C):", "Custom Colors(&C) from RightSide", &hFontSmall},
	{"作成した色(&C):", "Custom Colors on Add-Color", NULL},
	{"色の作成(&D) >>" , "Create Color(&D) >>", NULL},
	{"色合い(&E):", "Hue(&E):", NULL},
//	{"鮮やかさ(&S):", "Satulation(&S):", &hFontSmall },
	{"鮮やかさ(&S):", "Satu.(&S):",  NULL},
	{"明るさ(&L):", "Lumi.(&L):", NULL},

	{"赤(&R):", "Red(&R):", NULL},
//	{"緑(&G):", "Green(&G):", &hFontSmall},
	{"緑(&G):", "Gr'n(&G):", NULL},
	{"青(&U):", "Blue(&U):", NULL},
	{"色の追加(&A)", "Add Color(&A) to Custom_Colors", NULL},
	{"色" , "set", NULL},
//	{"| 純色(&O)" , "| pure col(&O)", NULL}
	{"| 純色(&O)" , "Color", NULL}
};
// ファイルを開くダイアログ用
stRepItem repFileDlg[] =
{
	{"ファイルの場所(&I):", "File Location(&I):", NULL},
	{"保存する場所(&I):", "File Saving Location(&I):", NULL},
	{"ファイル名(&N):", "File Name(&N):", NULL},
	{"ファイルの種類(&T):", "File Type(&T):", NULL},
	{"キャンセル", "Cancel", NULL},
	{"開く(&O)", "Open(&O)", NULL},
	{"保存(&S)", "Save(&S)", NULL},
	{"表示メニュー", "Menu" , NULL},
	{"縮小版(&H)", "mini(&H)" , NULL}
};
// タイトルと関連付けの定義
stRepTitle repTitle[] = 
{
	{ "色の設定", "Color Design", NULL , repColDlg,  sizeof(repColDlg)/sizeof(stRepItem) },
	{ "ファイルを開く", "Open File", NULL , repFileDlg,  sizeof(repFileDlg)/sizeof(stRepItem) },
	{ "名前を付けて保存", "Save File", NULL , repFileDlg,  sizeof(repFileDlg)/sizeof(stRepItem) }
};


////////////////////////////////////////////////////////////////////
//
//		ダイアログ内容書き換えのための
//		フック関数（ローカルフック用）
//		※ グローバル関数である必要があります。
//		この関数の中を変えるときは慎重に行って下さい。
//
LRESULT CALLBACK LocalHookProc (int nCode, WPARAM wParam ,LPARAM lParam )
{
	// コード判断
	if (nCode >= 0)
	{
		if ( nCode == HCBT_ACTIVATE)
		{

			if( LangRep == 1 ){
               //論理フォント構造体の指定
               rLogfont.lfHeight= 10 ;// 大きさ
               rLogfont.lfWidth= 0 ;
               rLogfont.lfEscapement= 0 ;
               rLogfont.lfOrientation= 0 ;
               rLogfont.lfWeight= 0 ;
               rLogfont.lfItalic= FALSE ;
               rLogfont.lfUnderline= FALSE ;
               rLogfont.lfStrikeOut= FALSE ;
               rLogfont.lfCharSet= ANSI_CHARSET ;
               rLogfont.lfOutPrecision= OUT_DEFAULT_PRECIS ;
               rLogfont.lfClipPrecision= CLIP_DEFAULT_PRECIS ;
               rLogfont.lfQuality= DEFAULT_QUALITY ;
               rLogfont.lfPitchAndFamily= VARIABLE_PITCH | FF_SWISS ;
               wsprintf(rLogfont.lfFaceName,_T("MS UI Gothic"));

               //フォントを作成
                hFontSmall = CreateFontIndirect(&rLogfont) ;

				int i,numAry;
				stRepItem * pRepItem=NULL;
				char strType[50];
				strcpy(strType, "");
				HWND myWnd;
				// タイトルの照合と書き換え
				for( i = 0; i < (sizeof(repTitle)/sizeof(repItem)) ; i++){
					char buff[50];
					GetWindowText((HWND)wParam,buff, sizeof(buff));
					if( strcmp(buff,repTitle[i].strBefore ) == 0 ){
						// 一致したものがあった場合
						SetWindowText((HWND)wParam, repTitle[i].strAfter );

						pRepItem = repTitle[i].pRepItem;
						numAry	 = repTitle[i].aryLength;
						// 
						strcpy( strType , repTitle[i].strBefore );

						if( strcmp(strType,"Open File") == 0 ){
							HWND hwndTB ;

							hwndTB = FindWindowEx((HWND)wParam,0, "ToolbarWindow32", NULL);
							if( hwndTB != 0)
							{
								::SetWindowText((HWND)wParam,"aa");
								CToolBar tb;
								tb.m_hWnd = hwndTB;
								//tb.Attach(hwndTB);
								CString strTmp;
								tb.SetButtonText(1, "aaaa");

							}
						}
						break;
					}
				}
				for(  i = 0; i < numAry ; i++){
					// FindWindowEx(親ウィンドウ, 開始子ウィンドウ番号, クラス名 , キャプション);
					myWnd =  FindWindowEx( (HWND)wParam,  0, NULL, pRepItem[i].strBefore );
					if( myWnd != 0)
					{
						SetWindowText(myWnd, pRepItem[i].strAfter );
						if( pRepItem[i].phFont != NULL)
						{
							::SendMessage(myWnd,WM_SETFONT,(WPARAM)*pRepItem[i].phFont,(LPARAM) 1);

						}
					}
				}
			}			
			// OKボタン(IDOK)の内容を書き換える
			SetDlgItemText( ( HWND )wParam, IDOK, strOK );
			// キャンセルボタン(IDCANCEL)の内容を書き換える
			SetDlgItemText( ( HWND )wParam, IDCANCEL, strCancel );

			HRESULT ret;
			// フック関数をアンインストール(フック解除！）
			ret = UnhookWindowsHookEx ( MyHookHandle );
			MyHookHandle = NULL;
		}
	}
	// 次のフックに渡す
	return CallNextHookEx ( MyHookHandle, nCode, wParam, lParam);
}
/////////////////////////////////////////////////////////////
//
//			ファイル選択ダイアログをフック付きで呼び出す関数
//
int	HookFileDialogDoModal( CFileDialog * pFileDialog )
{
	MyHookHandle = SetWindowsHookEx ( WH_CBT, LocalHookProc, NULL, GetCurrentThreadId( ) ); 

	return pFileDialog->DoModal();

}

///////////////////////////////////////////////////////////
//
//	ColorDlg() カラー選択ダイアログ関数
//	カスタムカラー配列はstaticで保存されます。
//		@param  hWnd		:   オーナーウィンドウ
//		@param  p_crResult	:	結果を受け取るCOLORREFのポインタ 
//		@param	crFirst		:  初期選択色
//		@param	bUserFirstColor: 初期選択色を使うかどうか
//		@param dwSpCustomColors[] 
//					: カスタムカラー配列を独自に指定する場合(NULL: デフォルト保存)
//		@return TRUE:選択 , FALSE :キャンセル
//
BOOL ColorDlg(HWND hWnd, COLORREF* p_crResult, 
			  COLORREF crFirst, BOOL bUseFirstColor, DWORD dwSpCustomColors[] )
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください

	// CHOOSECOLOR構造体定義
	CHOOSECOLOR cc;
	// カスタムカラーボックスのデータ配列定義
	// 16個のCOLORREF変数の配列 ( staticで宣言すること)
	static DWORD       dwDefaultCustomColors[16];   
	// COLORREF構造体定義
	static COLORREF crDefaultFirst = RGB(255,255,255);

	// CHOOSECOLOR構造体クリア
	ZeroMemory(&cc,sizeof(CHOOSECOLOR));
	// CHOOSECOLOR構造体サイズ設定
	cc.lStructSize = sizeof(CHOOSECOLOR);
	// オーナーウィンドウ設定
	cc.hwndOwner =(HWND ) hWnd;
	// カスタムカラーボックスのデータ配列設定
	cc.lpCustColors = ( dwSpCustomColors != NULL)? dwSpCustomColors: dwDefaultCustomColors;

	// 	初期選択色
	cc.rgbResult =  (bUseFirstColor == TRUE)? crFirst: crDefaultFirst;
	// フラグ設定
	// CC_FULLOPEN : カスタムカラー設定表示
	// CC_RGBINIT  : rgbResultの色を初期選択
	// CC_ANYCOLOR : 使用可能な全ての色を表示する
	cc.Flags = CC_ANYCOLOR|CC_FULLOPEN|CC_RGBINIT;
	

	// フック関数(MsgBoxHookProc)をインストールする SetWindowHookEx
	MyHookHandle = SetWindowsHookEx ( WH_CBT, LocalHookProc, NULL, GetCurrentThreadId( ) ); 

	// カラーダイアログを表示
	if(ChooseColor(&cc)){
		*p_crResult = cc.rgbResult;
		return TRUE;
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////
//
//		AfxMessageBoxHooked(メッセージ, 
//
int AfxMessageBoxHooked( LPCSTR message , UINT nType )
{
	// フック関数(MsgBoxHookProc)をインストールする SetWindowHookEx
	MyHookHandle = SetWindowsHookEx ( WH_CBT, LocalHookProc, NULL, GetCurrentThreadId( ) ); 
	return ( AfxMessageBox(message, nType) ); 

}
///// End ////////////////////////////////////////////////////////////////
