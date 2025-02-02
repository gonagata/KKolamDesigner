// This file is a mail source code for Kolam designer
// Useful Refereces:  http://nienie.com/~masapico/api_index.html
// 2012/06/10 以後　version 4.5.0とする
// 追加　GenerationのSymmetryをHとVに分ける　
//Last4.6.5のLast Version 4.7.0がLinkエラーのため、4.4.5　から　4.4.8 
//再修完	Red bar Cursorで　最左列左端、最上行上端も　境界のEdge模様を変えられる
//再修完	Key Shift+'X'でLastY行row　LastX列columnを削除 with Cursor at the ROw/Column 　
//未完　Last4.6.5でもEditのMouse-L操作は不便　改良要
//	完	例green beginning pointが明示されない。KeyBはOK
//---追加要　ここから　当面　Diagonalと　MultiLoopは後回し
// 未完　ParameterDig.cpp  Int を shortに
// 未完　H,V SymmetryなどKeyGでrandom発生 現行Shift+
// 未完　Key 'M'でKoMaTypeのchange to selfMirror OnEditMirror()　to get MirrorImage of BlockArea
//  完　OnGenerationHvs()は縦と横対称一緒としているのをそれぞれ独立するOnGenerateHSym OnGenerateVSym
// 2012/05/10 以後　KolamDesigner4.6.5となる OnBlockArea onEditCut,OnEditPaste,OnEditRotateはDiagonalKoMaに適用、未完Undo　
//					Red bar Cursorで　最左列左端、最上行上端も　境界のEdge模様を変えられる
//					Key Shift+'X'でLastY行row　LastX列columnを削除 with Cursor at the ROw/Column 　
// 2013/03/10 以後　KolamDesigner4.6.4となる bloken line of N-lines for two point connects 
// 2011/12/31 以後　KolamDesigner4.6.2となる
// 完（現行不良）　ChainMode　 Key'B'のFudeChainを途中で分割する　
//     KomaTypeの変換したViewModeでどのKoMaかを策定して 
// 完　DiagonalをEditする CutはOK　CopyはOnEditPaste()で処理,Rotate Mouse-L Undoは未完　 　

// 完　KoMaModeでDiagonalをカーソル指定Vertex with Key"Z"で削除　強制-1にする

// 完　KoMaを増設したときに　DiagonalKoMaの移動させない　個別X,Yから通番のXYになったので変更要
			//C言語では、0以外の値は真、0は偽ですから、
		    //慣れたプログラマは、a=1; if(a!=0) を if(a) と記述します。一方、if(a==0)の方はif(!a)と記述します。			// for diagonal data of the same as EdgeChain mode 
// 未完　Key 'S' or Mouse-Lでtraceを途中で止めたときに途中描画を維持する

// 2011/10/15 以後　KolamDesigner4.6.1となる
// 済み	Diagonal Loop は　Chain の場合、m_KmDvx[][]の　数値を両側はやめ、片側２種と、円弧のみにする
// このばあい　描き順　運筆則は新たに導入。正方Loopとの移行
// 4駒・線の対角交差点となるか　２駒・線の対角交差点となるか　あるいは片側対角線　　　
// [Fude No][Chain No][Edge No=m_numEdges[10][140]]  Chaindataの途中は挿入できない
// Chainの終わりに挿入すると決める
//		m_edgeChain と　m_numEdgesの役割りの違い　前者はedgeのDATA、後者はedgeのDATAの個数
// 予め交差の曲がりが同じか否かは指定する
　
//		2011/09/10 以下　KolamDesigner4.5.1となる
// 済み　目標はDiagonal Loopを描く。まず　GreenDotなどPulli/Dot Click領域を狭くする。
//		Diagonalの点をカーソル表示、次いでDaigonalLoopを描く、m_KmDvx[][]の数値を
//　　　-1:no-line 0:only arc 1:left curve 2:right 3:both curve 4:left edge-line
//---追加要　ここまで


//		2011.08.10以下はKolamDesigner4.4.5となる for more versatile Designer since 2011/06/01
// 済み　Chainのデータの形式改善　#コメントを繰り返さない。
// 済み  Loopsのとき　ChainデータにLoop色を保存 ChainModeで既存色をLoop色にする
// 済み　KoMaのMulitLoopのFormat 番号を入れる　version 4.4.4-->4.4.5 　
// 済み　# MultiLoopNum<max10, StartX, Y, Side*2+Direct,Color(R,G,B)
// 済み　04, 00, 00, 03, 000, 000, 160,-->	04-01, 00, 00, 03, 000, 000, 160

//		2011.07.20以下はKolamDesigner4.4.4となる for more versatile Designer since 2011/06/01
// 済み　Autogeneration のとき　最後の発生数を記録する

//		2011.07.05以下はKolamDesigner4.4.3となる for more versatile Designer since 2011/06/01
// 済み　KoMa -1,0 のときもマウス位置の赤Dot表示をする　
// 済み 最後のときのstarting edge　の赤バーをYellowバー　変える

//		2011.07.01以下はKolamDesigner4.4.2となる for more versatile Designer since 2011/06/01
// 済み　Key'N'を同じところですると　左駒(次の行も含め)とつながるようなTypeになるのを排除　
// 済み　AutoGenerate bAutog case 'G':のSingleの計数がおかしいのを直す　OnPaint()の始めでCheck　
//		　} // else	pim++; // 保存モードでも　pimは最後の列のみ櫛型Singleまで飛ばし、Multiも計数される。
//		//2011/6/10 　この方法でなく、KoMa=0が無い条件数＝Multi数+Single数から逆算する
//     version 4.3.4でも  但し全部描画しない不要で　N-Lineのみ　なにが代わったか？
//　　　即スタートする現在の前の4.3.5でも 3x2と2x3で違いいずれも正解より多い
//      一度する後全ての描画はしない。Key Shift+G 初期設定2011/03/11の他の変数を調べること。pim pisの数値がおかしい　配列NxM,MxNによって異なる
// 済み　Multi-loop の　SaveDatafileとOpenKomafile および KoMaMode, saving an animation image 
// 済み　ChainModeへの変換　initialize to convert the edge chain　を改修
// 済み  MultiLoop登録の場合(9本以内）はManualのTraceが第一fudeで、登録分は第二fude以後となる	
//　    　以下はKolamDesigner4.4.1となる for more versatile Designer since 2011/05/01
// 済み　複筆の場合 Key 'W': otherloop index　手動で　色選択と追加のtracingをする　2011/05/01 
// 済み　Multi-loopのときマウスで駒数Xを増しても、正常。connectDiscon(、when multiLoop, change Number　　
// 済み 直接Dialogで駒数Xを増減してもOK。m_strtKoma[]を臨時座標型に置いて　後で変更する

// 済み　FudeMode-Outline　のとき　内外いずれかで止まる or 内外いずれか繰り返す　
//       KolamDesigner4.3.4でも交点・途中で止まる。
//       これは一筆を探索するロジックを見つけないと　必ずしも行かない経路もあるので　できない。 
// 未完　交点2接続のとき　つなぎでずれが起こる　３ｘ３にすると良く分かる

//　    　以下はKolamDesigner4.3.5となる for more versatile Designer since 2011/2/22
//  済み スタートクリック範囲を狭くしたい＋即スタート　2011/03
//　済み　Komaの右下コーナはchainのときのtwo-point connect用

// 済み　combobox 4:edge line で輪郭線を得る。初めに黒線を描き、それより狭い色線を描く
// 済み　交差の黒が狭いを直す　undercrossingの範囲　// back width　の設定再考
//       ColorDialog設定は自動的に３になるが事前bfrswell変数でEdge-line４を選択したら４に強制変化させる　
//  　   Edge line　のとき　開始の線が太くなる？if( m_swell ==4) OK
//　   　smellpaper のとき　左上（０）のPulliのみが白、 直した　 
//       edgeLineの最終像の場合　無くても、交差はわかる　undercrossing線を除く　区間微調整した
//　　　 normalLineの最終像の場合　undercrossing状に　　Kolam状はanimeとfinal同一色選択
//　　
//  未完  ChainModeの第３状態のデータ（0,1,2 two-point & 3 sharpBend）取り扱いと描画 
//　　　　現状データは　(m_edgeChain[m_fudeNum][ m_chnNo[m_fudeNum] ]<<1) +1; 
//		  データが1ビットであるのでもう一つm_edgeChain2用意する
//		m_edgeChain2-m_edgeChain = 0-0:no-connection,0-1:one-point crossing,
//								   1-0:two-point connect,1-1:sharpBend  
//　    　以下はKolamDesigner4.3.4となる for more versatile Designer since 2010/3/22
//  済み  saveImage(　の保存のとき　Trace前の白線図も保存する　　　
//　    　以下はKolamDesigner4.3.3となる for more versatile Designer since 2010/3/22
//  済み  ChainModeの Fude分離はKey 'S'に類して、Chain分離Key 'Q'に変更、Shift+ S/Qのとき既存にデータが追加される　
//　    　以下はKolamDesigner4.3.2となる for more versatile Designer since 2010/3/22
//  報告　ChainModeの描画restartのStartEdgeは最後のFude分が変更する
//  済み  Generation Operation Key G for the original left-upper area including the middle column, 
//        Shift+G for auto-generated pattern,
//        　
//　    　以下はKolamDesigner4.3.1となる for more versatile Designer since 2010/3/22
//  済み  ChainMode マウス・カーソルを動かすと、Kolam曲線が一度消えることを無くす　
//	dc.BitBlt(0, 0, m_imageSiH, m_imageSiV, &memDC, 0, 0, SRCCOPY);// この表示操作をまとめてする
//　    　以下はKolamDesigner4.3.0となる for more versatile Designer since 2010/3/22
//  済み　EditでRotateは正方形以外の長方形は回転する、移動だから残さない。BlockAreaはそのまま
//  済み　set KomaType of Circle with Key 'C' from Key 'O' 

//  済み　ChainMode to Stop animation, During pushing Mouse-L to Keep the trace, and then Mouse-L restart

//　    　以下はKolamDesigner4.2.9となる for more versatile Designer since 2010/3/22
//  済み　ChainMode to Stop animation ( not keepint the trace), and then Mouse-L restart
//　    　以下はKolamDesigner4.2.8となる for more versatile Designer since 2010/3/22
//	済み　ChainMode カーソルが赤点右下隅 right-bottom corner area、青点表示、prsntedg == 10　　
//        そのために右下隅ではTraceスタートをしない
//  済み　ChainMode to stop animation, after moving Mouse, up Mouse-L or Shift+"S" (However last Data will be added) 
//  済み　実行ファイルのファイルバージョンは右窓のResourcesのVersionをクリックして、表の値で変える。
//  済み      FudeMode 順番変える　Smooth/Non-Smooth(sharpbend)/Outline
//　　　  以下はKolamDesigner4.2.7となる for more versatile Designer since 2010/3/22
//           at any sharpbend point with/without a linked adjoining/even surrounding Koma, like a Candle-flame
//　　　  以下はKolamDesigner4.2.6となる for more versatile Designer since 2010/3/22
//  済み　FudeMode Smooth/Outline/Non-Smooth(sharpbend) の場合にも連続する。
//           at a sharpbend point without a linked adjoining Koma (which is necessary), like a Candle-flame
//  済み OnEditMouseL, or OnSetBlockarea()　using MOUSE_L like as well as Key 'B':

//　	  以下はKolamDesigner4.2.5_20091128_ModalessByYByN-Colorfile
//　　　for more versatile Designer since 2009/11/07
//  済み　#include 2009/12/09 無くても良い
//  済み　2009/12/4 ChainMode のX 操作 B:Breakに　 OK
//	済み  2009/11/30 ImageNameを単独にする　fileName がそのままImageNameになってKomaが重ならない
//	済み  2009/11/28 for keeping finalline image at trce = 3 and reset once L-Mouse
//	済み　元に戻す　CallBackButtonの取り付け、無くても良いとする。Colorはfile記録する
//	済み　2009/11/25　ColorDialogはカーソルをViewにしないでも即反映、
//        しかし　Memory leeksのため難しい。無くてもよいとする
//  報告　APPMODUL.CPPはC:\Program Files\Microsoft Visual Studio\VC98\MFC\SRCにあった
//  済み　2009/12/4 Dialogの色を即反映のため必要である。これをこのProject Holderに移植した
//  報告　void Invalidate(  BOOL bErase );
//	bErase が TRUE の場合は、BeginPaint メンバ関数が呼び出されると背景は消去されます。
//	bErase が FALSEの場合　「 Invalidate() と同じ」、背景は変更されずに残されます。
//	Invalidate() はウィンドウズにメッセージを「ポスト(Post)」します。
//	ポストされたメッセージに対応するハンドラは、現在実行中のハンドラや
//	先にポストされていたメッセージに対応するハンドラの実行終了を待って、実行されます。
//	OnLButtonDown() で Invalidate() を呼び出すと WM_PAINT がポストされ、
//	まだ他にポストされたメッセージが無ければ OnLButtonDown() の終了後、 
//	OnEraseBkgnd()、OnDraw() と連続して呼び出されます。
//	この「ポスト」して順番を待つ、で都合が悪いときには、
//	Invalidate() の直後に UpdateWindow() を呼ぶことで、即再描画されます。
//　
//　　　以下はVersion4.1.5となる for more versatile Designer since 2009/11/07
//	済み　2009/11/21 ColorData 色をファイルに 2009/11/22 Colordata をファイルから　
// 	済み　2009/11/16 ParameterDialog を起動時に　呼び出す by Nagata from Atsushi777
//	済み　2009/11/7 Holder"KolamImages" が既存でないときは作成
//	済み　2009/11/01 by Y Dialogの数値は画像に即反映するが　画像操作ではDialogに反映されない
// 　　　 m_wndParam.UpdateData(false); // 2009/11/4 for sending the data to Dialog 
//	m_ImageSizWidth = 250; 即反映　	画像操作OK　
//	m_KomaX_N = 3;  即反映　m_ImageFileName のときOK	画像操作OK　　
//	m_M_Max = 1850/3; 
//	m_KomaSize = m_ImageSizWidth/m_KomaX_N;  
//	m_KomaY_M = 3; 即反映　	画像操作OK　
//	m_KomaType = 99; 
//	m_SleepTime = 0; 即反映	 
//	m_SwellMode = 0;  即反映　
//	m_ImageFileName = _T("Name");  即反映 OpenFile　反映　
//　　　以下はVersion4.1.0となる for more versatile Designer since 2009/11/07
//	済み　2009/11/7 ColorButtonを押すと勝手にm_koM[31]=0;　駒種が変わるの直す
//	済み　Sleeptimeが反映した。ON_EN_CHANGE(IDC_SLEEPTIME, OnChangeEdit1) //2009/11/7 by Nagata
//　済み　KomaTypeは指定入力Xは反映され　その後表示はそのままで、次Dialog変化のときにX値が活きる
//       
//　　　　以下はVersion4.0.3となる for more versatile Designer since 2009/9/29
//	済み　aUtoGenaration のStop はKey G,
//　済み  2009/10/20    ParameterDialogを常時表示にする。この表示方法をモードレス、
//						閉じないと他のウィンドウを操作できない表示方法をモーダル
//　済み  2009/10/20 ColorModeをComboBox入力	初期値の記載　OK　
//  済み　Colorボタンを押したらColorModeが３で表示される
//  済み  2009/10/20 重なったところが消えるのをさける　Dialogの下の画像が消えないようにする
//　済み 　2009/10/17 ColorMode 0,1,2 でも色ボタンに反映させた　一度Onし、描画した再度のDalogで
//　済み 　2009/10/12 色ボタンつき　ParameterDialogで 　CColorDialog　地面、線の色見本より指定
//  済み  ファイルの説明はRes.のVersionで変えた
//  済み　色選択で　白黒(1 for swelling paper)時 常時の線色を灰色に。
//  済み　N-lines shows incident tiles between adjacent tiles  辺赤カーソル　上、左の領域　本来でない　マウス点が　赤点近傍ででる　
//  済み　SaveImage　Still　の説明 save still Image drawn after starting to trace　
//  済み　SaveImage　Still を選択するも　resetがないようだ。　
//　済み　File->Save Still の画面内指示Key S/N のNの内容が合っていない（NはN-Line像の記録）
//　済み　File->Save Still Imageの大文字Sを小文字にする。
//　済み　DataFile.txtの表示　KomaArrayの座標0.1.2と合わせやすいように紋様画面を0,1,2,3,..とする
//  済み　Chain  説明を表示 現行スタートの辺は緑＋赤辺に変わる。緑点のみ同じ辺での2方向変化。
//　済み　Chain　Startスタートの駒=緑点は赤辺＋Sで変わる。
//　済み  ChainMode Startdot をKey 'S'＋RedEdgeで変えて　Startedgeも変わる。
//  済み  Modeを明記する。駒領域傍
//　済み  簡単接続KeyN：直線と全接続Koma"D”、Edit areaSetのみはKey B

//　済み  m_koM[ii] = short int( 0x8000);の16Bit配列？ Yes、初期値は負値　
//　済み  下位4bit KomaType 1点繋ぎ　その上４bitで2点繋ぎ　上位8bitは未使用　上の８bitは空きか？
//　済み  LOW 4bit at eaxh edge 0,1,2,3 bit,=0:No Connection,1: One point connect
//　済み  次の4bit at each edge 4,5,6,7 bit =0: =Low bit,1:two point connect(opposite curve) 
//　済み  　sced = (m_koM[kna]>>edgn)%2 + (m_koM[kna]>>(4+edgn))%2 *2; // lower bit + upper bit= 0,1,2
//					Edge status, 0:no connected,1: line connected, 2: curve connected 
//　済み	ChainMode カーソル赤Edgeでないときは　直前のStarting 点・向きで始まる。
//　済み	Red Edge上で　順繰りに変わる。
//　済み	two point connecting 2点接続指示マウスクリックの領域はタイル間のVertex角右下域に準備した
//			カーソルが　右下隅範囲 right/bottom corner area で　青玉　prsntedg = 10; を使う　

//  未完  	prsntedg = -1; //2009/ 終わりで強制的なEdgeの設定をやめ、restartを容易に
//　未完   円弧が1～２ドットずれる　条件２Openの繋がるで見える　if(sced == 2)で描画 
//　未完　１：拡張子Txtを　データ保存の拡張子も現行.txtから.ngtに変更する。 
//　未完　２：アイコンを専用にする。 ３：そのアイコンをクリックすると、アプリケーションソフトDesignerを起動し、かつアイコンのファイルを取り込
//　未完   ParameterDialogを最少にしたとき　位置はApplicationの下にする　現在はDesktopの下。
//  未完  描画像がWindowより大きくなったときのスクロール機能MFC SetScrollInfoをつけたい
//  未完　ViewのDrawingMode　チェック印が変わるようにする。ViewのFudeModeの　Checkチェックが変わるようにする。

//　済み　 現行　メニュー　FileでOpen File.texのダイアログが出て、Openして　使用データを取り込みます。 
//  済み  release debug 何れも動作は良いが　　実行（F5)で 多数　合致するｼﾝﾎﾞﾙ情報は見つかりませんでした。


// ChildView.cpp : implementation of the CChildView class
// Depends.exe for beeing known which DLL LoadLibraries will be used in this program

#include "stdafx.h"
#include "KolamDesigner.h"
#include "ChildView.h"
#include "MemDC.h"
#include <math.h>
#include <time.h>
//#include <windows.h>	//for Beep(

//{+ フックのために追加 CFileDialog関数
#include "DialogFunc.h" //カラーdialogを英語化のため追加

#include <afx.h>	// CStdioFile, CString, CStringArray　in OnOpenKomaFile
//#include <cstdlib>  // atoi　in OnOpenKomaFile
//2009/12/4 先頭に c が付き、.h の無いファイルは C++ の標準ライブラリで下位互換の為に作成されたヘッダーファイルです。
//ここは単純に #include <stdlib.h> でいいのでは、と思います。
#include <stdlib.h> 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView


//static ic; 2009/9/18 version 4.0 のとき必要ないので消した

// for ChainData
//static をとっても同じ　タダシ　ヘッダーに持っていくとNG ??
short m_fudeNum;	// serialNumber of Fude(Stroke),  Max20:[0-19 m_fudeNum], the first m_fudeNum = 0; 
short m_startChainXY[30];  // m_startChainX[10] + m_komaNoX*m_startChainY[10]; Number index of starting point of each fude 
short m_startSide[30];	    // starting side(edge) and direction
short m_chnNo[30];	// serialNumber of Chain : Max10:0-9, Number=m_chnNo[Fude number] +1; 
short m_numEdges[30][140]; // DataNumber[m_fudeNum][m_chnNo[m_fudeNum]Max232] number of edges(useful Bits) of each m_edgeChain[10][232]
unsigned int m_edgeChain[30][140]; // Data[m_fudeNum][m_chnNo[m_fudeNum]Max232] chain数= KoMa数1850x4/32bits, MSB:start 32,LSB:last
      //m_edgeChainはedgeのDATA itself　m_numEdgesはedgeのDATAの個数の違い
      //配列数を変えたら　合わせて　上のCOLORREF m_loopColor[20];と初期値も、// 選択されたloop色[0-9] common using m_startChainXY[20]; 
//ヘッダー static COLORREF m_loopColor[20];// 選択されたloop色[0-19] common using m_startChainXY[20]; 
//未完 一つFudeでEdgeChain数が232個は多すぎないか？　全駒を一筆にした場合はあり得るが、実際にはない
// Diamond33x33駒で4筆にわけて各筆35chain個, 一筆でも140個


CChildView::CChildView()
{
	/*
	// <<追加
	m_pParamDlg = new CParameterDlg;
    m_pParamDlg->Create(this);
	//>>
	*/

//	m_drawImages = TRUE;	
	m_drawMode = 0;
	m_smoothmod = 0;
	m_gemod = 0;
	keyS_M = 0;
	cnvEc2KoMa = 0;
	//memset(m_koM, -1 & ~0x0F, sizeof(m_koM) );// no-Pulli type, intialization // 指定された文字でバッファを初期化します
	for( int ii = 0; ii < 1850; ii++)  m_koM[ii] = short int( 0x8000); // -1 & ~0xFFFF, 16bitを負値に
	//memset(m_koMxy, -1 & ~0xFF, sizeof(m_koMxy) );// matrix data intialization //文字でなくても0の場合は0になる　０以外はNG
	for(     ii = 0; ii < 50; ii++)  for ( int iii =0; iii<37; iii++) m_koMxy[ii][iii] = short int( 0x8000); 
	m_komaNoX = m_wndParam.m_KomaX_N; // needs as the initial value for release version
	m_komaNoY = m_wndParam.m_KomaY_M;
	m_kks = m_wndParam.m_ImageSizWidth/m_komaNoX; // pixel size of one KoMa 	
	m_ednum = m_komaNoX*m_komaNoY*2 -m_komaNoX-m_komaNoY;
	m_edpnm = (unsigned long)pow( 2.0, m_ednum ) -1; // index edge patterns, except all of 0
	m_imageSiH = m_kks *m_komaNoX +45;  // size of image area m_wndParam.m_ImageSizWidth; //450
	m_imageSiV = m_kks *m_komaNoY +70;  // size of image area  
	m_komType = m_wndParam.m_KomaType; // Type Number for all koma  

	cri = (int)(m_kks/2.0*1.41421356/2.0); // circle radius of the arc	
	pri = (int)( 1+ m_kks/2.0*1.41421356/20.0); // circle radius of the dot/pulli  
	whd =  m_kks/5;		//nWidth,nHeight 角の丸みの楕円形の幅と高さ
	fnlimg = 0; 

	m_fudeNum = 0;  //the first one
	memset(m_edgeChain, 0, sizeof(m_edgeChain) ); // intialization
	memset(m_numEdges, 0, sizeof(m_numEdges) ); // intialization
	memset(m_chnNo, 0, sizeof(m_chnNo) ); // intialization
	memset(m_startChainX, 0, sizeof(m_startChainX) ); // intialization
	memset(m_startChainY, 0, sizeof(m_startChainY) ); // intialization
	memset(m_startSide, 0, sizeof(m_startSide) ); // intialization
	memset(m_startChainXFile, 0, sizeof(m_startChainXFile) ); // intialization
	memset(m_startChainYFile, 0, sizeof(m_startChainYFile) ); // intialization
	memset(m_startSideFile, 0, sizeof(m_startSideFile) ); // intialization

	m_loopNum = 0;
	memset(m_strtKoma, 0, sizeof(m_strtKoma) ); // intialization
	memset(m_strtSide, 0, sizeof(m_strtSide) ); // intialization

	memset(m_edcd, 0, sizeof(m_edcd) ); // 　edge の0,1,2(未）　条件,intialization
	
	bAutog = FALSE;// TRUE for Auto generation
	pia = 0;	pim = 0;	pis = 0;	pio = 0;

	CTime theTime = CTime::GetCurrentTime();	//日付を入れるby Abe 20030630
	m_cdate = theTime.Format("%y%m%d");			// "20%y%m%d"-%Mm");	

	double deg8pi = 45.0*3.1415926535/180.0; //45.0*pi/180.0; a radian of 8th arc= 45 deg
	for(int i=-1; i<8; i++){
		cospi8th[i+1] = cos(i * deg8pi); // [0]-[8],[i+1:負のアレイを避けるため]
		sinpi8th[i+1] = sin(i * deg8pi);
	}
	srand( (unsigned)time( NULL ) );  //rand() == 0<->RAND_MAX(0x7fff=65536) の初期設定  
	//除算は掛算より遅いからrnd =rand();  rnd%100 より rnd*101/65536　として (rnd*101)>>16
	m_ednum = m_komaNoX*m_komaNoY*2 -m_komaNoX-m_komaNoY;
	m_edpnm = (unsigned long)pow( 2.0, m_ednum ) -1; // index edge patterns, except all of 0

	m_slpt = m_wndParam.m_SleepTime; //set again after moving mouse
//	m_strFileTitle = m_wndParam.m_ImageFileName;
	m_strFileTitle = m_wndParam.m_ImageName;
	m_strImgName = m_wndParam.m_ImageName;
 	
	m_swell = m_wndParam.m_SwellMode; 	//m_swell =0 Default color, =1 for swelling paper to braille, =2 night color, =3 color button, =4 edgeline 
 	// カラーモード３ColorButtonの初期色設定 2011/02/11 消してもかわらない　初期色は出る
	//m_wndParam.m_BtnGColor.SetColor(RGB(150, 100, 0) );
	//m_wndParam.m_BtnTColor.SetColor(RGB(190,130,0) );
	//m_wndParam.m_BtnAColor.SetColor(RGB(255, 0, 0) );
	//m_wndParam.m_BtnFColor.SetColor(RGB(200, 255, 200) );
  // for making tables of arrays to converting 0-80 numbers and  8Bit for 3 edge conditions
  //seting short int m_N81toE8B[81];  // 8bit number= N81toE8B[0-80 number];
  //seting short int m_E8BtoN81[241];  // 0-80 number= E8BtoN81[8bit number Max 240];
  for ( int s = 0; s <81; s++) // converting 0-80 numbers to 8Bit, then converting 8Bit to 0-80 numbers
  {
	if( s<16) 		m_N81toE8B[s] = s;	  // m_E8BtoN81[s] = s; 
	else if(s==27) 	m_N81toE8B[s] = 16;		
	else if(s==28) 	m_N81toE8B[s] = 18; 
	else if(s==30) 	m_N81toE8B[s] = 32; 	
	else if(s==31) 	m_N81toE8B[s] = 33; 		
	else if(s==36) 	m_N81toE8B[s] = 48; 
	else if(s==37) 	m_N81toE8B[s] = 20;	 		
	else if(s==39) 	m_N81toE8B[s] = 22;	 	
	else if(s==40) 	m_N81toE8B[s] = 36; 
	else 
	{
		short int D0= (INT(s%3))%2;		//MOD(MOD(s,3),2);		
		short int D1= (INT(s/3)%3)%2;	//MOD(MOD(INT(s/3),3),2);		
		short int D2= (INT(s/9)%3)%2;	//MOD(MOD(INT(s/9),3),2);		
		short int D3= (INT(s/27)%3)%2;	//MOD(MOD(INT(s/27),3),2);		
		short int U0=  INT( INT(s%3)/2);		//INT(MOD(s,3)/2);		
		short int U1=  INT( (INT(s/3)%3)/2 );	//INT(MOD(INT(s/3),3)/2);		
		short int U2=  INT( (INT(s/9)%3)/2 );	//INT(MOD(INT(s/9),3)/2);		
		short int U3=  INT( (INT(s/27)%3)/2 );	//INT(MOD(INT(s/27),3)/2);			
		m_N81toE8B[s] = D0*1+D1*2+D2*4+D3*8+U0*16+U1*32+U2*64+U3*128;
	}	
	m_E8BtoN81[ m_N81toE8B[s] ] = s;
  }

}//endof CChildView::CChildView()

CChildView::~CChildView()
{
}

// パラメータダイアログを閉じる命令関数の作成
void CChildView::EndParamDlg()
{
	//m_pParamDlg = NULL;
}

BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_WM_KEYUP()
	ON_COMMAND(ID_PARAMETER_SET, OnParameterSet)
	ON_COMMAND(ID_VIEW_DRAW_IMAGES, OnViewDrawImages)
	ON_COMMAND(ID_VIEW_DRAW_FUDE, OnViewDrawFude) 
	ON_COMMAND(ID_GENERATION_SET, OnGeneKolam) 
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()  
	ON_COMMAND(ID_FILE_OPEN, OnOpenKomaFile)
	ON_COMMAND(ID_SAVE_FILE, OnSaveKomaFile)
	ON_WM_TIMER()
	ON_COMMAND(ID_VIEW_RESET_ALL, OnViewResetAll)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(ID_EDIT_ROTATE, OnEditRotate)
	ON_COMMAND(ID_GENERATION_ROT, OnGenerationRot)
	ON_COMMAND(ID_GENERATION_HVS, OnGenerationHvs)
	ON_COMMAND(ID_GENE_RECURSIVE, OnGeneRecursive)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_SAVE_IMAGE_STILL, OnSaveImageStill)
	ON_COMMAND(ID_SAVE_IMAGE_ANIMATION, OnSaveImageAnimation)
	ON_COMMAND(ID_SAVE_IMAGE_NLINE, OnSaveImageNline)
	ON_COMMAND(ID_OPEN_FILE_PRINT, OnOpenFilePrint)
	ON_COMMAND(ID_SAVE_IMAGES_DATAFILES, OnSaveImagesDatafiles)
	ON_COMMAND(ID_EDIT_SETBLOCKAREA, OnEditSetBlockArea)
	ON_COMMAND(ID_EDIT_MOUSE_L, OnEditMouseL)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs, CParameterDlg* pParamDlg)  
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)  
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);
	
	return TRUE;
}

BOOL CChildView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	BOOL ret;
	ret = CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);

	return ret;
}
//

//////////////////////////////////////////////
//		【メニュー】パラメータウィンドウの表示
//       to display Modeless Dialog Window
//		モードレスで表示するように変更
//
void CChildView::OnParameterSet() 
{
	// 2009/10/27 t.yoshino モードレス表示
	// m_wndParam.SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOSIZE); // 必要なし
	// m_wndParam.CenterWindow();	// 親ウィンドウに対して中央寄せ 無いと右寄せ
	// m_wndParam.RightWindow();	// 親ウィンドウに対して右寄せ、'RightWindow' : 'CParameterDlg' のﾒﾝﾊﾞではありません。

	//2009/10/29 以下追加 右寄せ　by totoko  
	// http://social.msdn.microsoft.com/Forums/ja-JP/user/threads?user=Shonan%20Hannya
	// 親ウィンドウの位置を得る
	CRect rectParent;
	GetWindowRect(&rectParent);
	// 子ウィンドウの位置を得る
	CRect rectChild;
	m_wndParam.GetWindowRect(&rectChild);
	// 親の右端から子の幅分オフセットさせた位置に配置
	long Childwidth = rectChild.right - rectChild.left;
	rectChild.right = rectParent.right;
	rectChild.left = rectChild.right - Childwidth;
	// 親ウィンドウの中ほどの高さに配置 by ミッヒー
	long parentHeight = rectParent.bottom - rectParent.top;
	long childHeight = rectChild.bottom - rectChild.top;
	rectChild.top = rectParent.top + parentHeight / 4;
	rectChild.bottom = rectChild.top + childHeight;//Top変更後で再設定要
	// 表示制御
	//	m_wndParam.MoveWindow(&rectChild);
	//	m_wndParam.BringWindowToTop();  // 前に持ってくる
	//	m_wndParam.ShowWindow(SW_SHOW); // 表示
	// 上3行の替わり　activeWindowはDialogではなく、本体のViewにしたい。
	m_wndParam.SetWindowPos(
		&wndTop,
		rectChild.left,
		rectChild.top,
		Childwidth,//rectChild.right - rectChild.left,
		childHeight,//rectChild.bottom - rectChild.top,
		SWP_NOACTIVATE | SWP_SHOWWINDOW
	);

} //endof OnParameterSet(

/*
//
// Menu Item Process
//

IDR_MENU1 MENU DISCARDABLE 
BEGIN
    POPUP "サブメニュー"
    BEGIN
        MENUITEM "サブメニューのアイテム０（チェック）", ID_SUB0
        MENUITEM "サブメニューのアイテム１（不可）", ID_SUB1
        MENUITEM "サブメニューのアイテム２（グレー）", ID_SUB2
        MENUITEM "サブメニューのアイテムの状態を全て初期状態に戻す", ID_SUB3
    END
END
/////////////////////////////////////////////////////////////////////////////
/*  Ｃ言語で始めるＷｉｎｄｏｗｓプログラミング  */
/*  ３３章のサンプルプログラム（その１）        */
/*  最も、一般的と思われる方法                  */
/*                      Programmed by Y.Kondo   */
/*　注：ＴＡＢサイズは４で見てください          */
/*  このファイルでは、メインウインドウのウインド*/
/*ウプロシージャが定義されている                */
/*
#define     STRICT
#include    <windows.h>
#include    <stdio.h>
#include    "wndproc.h"
#include    "resource.h"
*/
/*===============================================================================*/

/*  このファイル内でのみ用いられる関数のプロトタイプ宣言     
static  LRESULT Wm_CommandProc(HWND,WORD,WORD,HWND);
static  LRESULT Wm_DestroyProc(void);

/*  メインウインドウのウインドウプロシージャ     
LRESULT CALLBACK WindowProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam)
{
    switch(message)
    {
        case    WM_COMMAND:         /*  メニューに対する処理     
            return  Wm_CommandProc(hwnd,HIWORD(wparam),LOWORD(wparam),(HWND)lparam);
        case    WM_DESTROY:         /*  ウインドウの破壊後処理   
            return  Wm_DestroyProc();
    }
    return  DefWindowProc(hwnd,message,wparam,lparam);
}

static  LRESULT Wm_CommandProc(HWND hwnd,WORD wNotifyCode,WORD wID,HWND hwndCtl)
{
    switch(wID)
    {
        case    ID_SUB0:    /*  メニュー項目にチェックを付けたり外したり     
            if(GetMenuState(GetMenu(hwnd),ID_SUB0,MF_BYCOMMAND)&MF_CHECKED)
            {   /*  メニュー項目がチェックされていたら、チェックを外す   
                CheckMenuItem(GetMenu(hwnd),ID_SUB0,MF_BYCOMMAND|MF_UNCHECKED);
            }
            else
            {   /*  メニュー項目がチェックされていなければ、チェックを付ける     
                CheckMenuItem(GetMenu(hwnd),ID_SUB0,MF_BYCOMMAND|MF_CHECKED);
            }
            break;
     return  0;
}
static  LRESULT Wm_DestroyProc(void)
{
    PostQuitMessage(0);
    return  0;
}
*/


void CChildView::OnViewDrawImages() // tri-alternate to change drawMode of edgeChain
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
  static int SETcnvEc2KoMa;

// 済み　ChainからKoMaの変換（Key'K'と同じ）セットをここで行いたい
//         m_drawMode default 0: Tile/KoMa Mode, 1: edgeChain Mode, +at Once, cnvEc2KoMa = 1;	　
	if(	m_drawMode == 0){
		m_drawMode = 1; SETcnvEc2KoMa = 0;
//		m_fudeNum = m_loopNum -1; 元元なし、これがあるとLoops指定でないときにChainModeが描画なし
		//CString strData; strData.Format("xxxxx");AfxMessageBox(strData); //MessageBox for data
		MessageBox(_T("Sorry, EdgeChainMode doesn't support\ntwo-point Connect,SharpBend and Outline"));	
	} else if( m_drawMode == 1 && SETcnvEc2KoMa == 0)
	{ 
		cnvEc2KoMa = 1; SETcnvEc2KoMa = 1;
//		OnKeyUp('K', 0, 0); // to converte a code of  the pattern	
	} else if( m_drawMode == 1 && SETcnvEc2KoMa == 1)
	{
		m_drawMode = 0; SETcnvEc2KoMa = 0;//ToggleSwitch to 0:draw KoMaTile, 1:EdgeChain
	}
	fnlimg = 0; // reset 2009/11/28 keeping the finalline image 

//	m_drawImages = TRUE;
	Invalidate();//Invalidate(FALSE);これにするとWindow内コメントがきれいに書き換えられない。
}
 
void CChildView::OnViewDrawFude() // 3-statuses toggle switch to tracing Smooth/NonSmooth/Outline mode
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if(m_smoothmod ==2) m_smoothmod =0; else m_smoothmod++;
		 // FudeMode 0:Smooth/1:NonSmooth(SharpBend)/2:Outline-border
	fnlimg = 0; // reset 2009/11/28 keeping the finalline image 

/*	// Check ON/OFF at the Menu Item ID_SUB0
//'GetMenuState' : 1 番目の引数を 'class CMenu *' から 'struct HMENU__ *' に変換できません。 
	if(GetMenuState( GetMenu(), ID_VIEW_DRAW_IMAGES,MF_BYCOMMAND)&MF_CHECKED)
	{   // if checked, Uncheck
		CheckMenuItem(GetMenu(),ID_VIEW_DRAW_IMAGES,MF_BYCOMMAND|MF_UNCHECKED);
	} else
	{   // if unckecked, check
		CheckMenuItem(ID_VIEW_DRAW_IMAGES,MF_BYCOMMAND|MF_CHECKED);
	}
*/
//	m_drawImages = TRUE;
	Invalidate();
}

// generation of Pattern with random and then select available-connections

void CChildView::OnGeneKolam() // set the mode of Generation Kolam
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	fnlimg = 0; // reset 2009/11/28 keeping the finalline image 
 
	for( int ikb = 0; ikb < m_komaNoX*m_komaNoY; ikb++) m_preKoM[ikb] = m_koM[ikb];// for Undo	

	m_ednum = m_komaNoX*m_komaNoY*2 -m_komaNoX-m_komaNoY;// edge number
	m_edpnm = (unsigned long)pow( 2.0, m_ednum ) -1; // index edge patterns, except all of 0

	m_gemod = 0; //KoMa random 0:Sequntial,1:H&V-Sym, 2:Rot-Sym 
	geNeration( m_gemod);// 1:Verti&Hori Sym, 2:RotatedSym, 3:Recursive
//	Invalidate(); // into geNeration()
}//endof 


void CChildView::OnGenerationHvs() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
//	if( fnlimg == 1) fnlimg = 0; // reset 2009/11/28 keeping the finalline image 
	
	for( int ikb = 0; ikb < m_komaNoX*m_komaNoY; ikb++) m_preKoM[ikb] = m_koM[ikb];// for Undo	

	m_gemod = 1; //KoMa random 0:Sequntial,1:H&V-Sym, 2:Rot-Sym 
	geNeration( m_gemod);// 1:Verti&Hori Sym, 2:RotatedSym, 3:Recursive
//	Invalidate();
}

void CChildView::OnGenerationRot() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if( m_komaNoX != m_komaNoY ) // to make square matrix as size as horizontal number
	{
			m_wndParam.m_KomaY_M = m_komaNoY = m_komaNoX; 
			CRect wd_rect;
			GetWindowRect(wd_rect);
			int wnd_yhight = wd_rect.bottom - wd_rect.top;
			if( wnd_yhight -70 < m_kks *m_komaNoY ) 
			{
				m_kks =  (wnd_yhight -70)/m_komaNoY; 
				m_wndParam.m_KomaSize = m_kks;	// = m_ImageSizWidth/m_KomaX_N;
				cri = (short)(m_kks/2.0*1.41421356/2.0); // circle radius of the arc	
				pri = (short)( 1 +m_kks/2.0*1.41421356/20.0); // circle radius of the dot/pulli  
				whd =  m_kks/5;		//nWidth,nHeight 角の丸みの楕円形の幅と高さ
			}
		m_wndParam.m_ImageSizWidth = m_kks *m_komaNoX; 
		m_imageSiH = m_kks *m_komaNoX +45;	// size of image area m_paramDlg.m_ImageSizWidth; //450
		m_imageSiV = m_kks *m_komaNoY +70;  // size of image area  	
		//m_ednum = m_komaNoX*m_komaNoY*2 -m_komaNoX-m_komaNoY;
		//m_edpnm = (unsigned long)pow( 2.0, m_ednum ) -1; // index edge patterns, except all of 0
		m_wndParam.UpdateData(false); // 2009/11/4 for sending the data to Dialog 
	}
	for( int ikb = 0; ikb < m_komaNoX*m_komaNoY; ikb++) m_preKoM[ikb] = m_koM[ikb];// for Undo
				
	m_gemod = 2; //KoMa random 0:Sequntial,1:H&V-Sym, 2:Rot-Sym 
	geNeration( m_gemod);// 1:Verti&Hori Sym, 2:RotatedSym, 3:Recursive
//	Invalidate();
}// endof OnGenerationRot

static deep; 
void CChildView::OnGeneRecursive() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	for( int ikb = 0; ikb < m_komaNoX*m_komaNoY; ikb++) m_preKoM[ikb] = m_koM[ikb];// for Undo
				
	deep++;
	m_gemod = 3; //KoMa random 0:Sequntial,1:H&V-Sym, 2:Rot-Sym, 3: Recursive
	geNeration( m_gemod);// 1:Verti&Hori Sym, 2:RotatedSym, 3:Recursive
//	Invalidate();
}

void CChildView::reCursive( int deep)
{
	CClientDC dc(this); // for dc.Texout
	CString	strc; 
	strc.Format(" deep %d ", deep--);
	dc.TextOut( 0, m_kks*m_komaNoY+70+15*deep, strc);
	
	if( deep > 0) reCursive( deep);
	else 
	{	strc.Format("  end %d ", deep);
		dc.TextOut( 0, m_kks*m_komaNoY+70+15*deep, strc);
	}
}

short int CChildView::rotateKoma( short int komat) 
{
    short int rk, rku;
	if(komat < 0) return komat; 
	else if( komat <16){ return ((komat<<1) & 0x000F) + ((komat & 0x0008)>>3); }
	else 
	{	rk  = ((komat<<1) & 0x000F) + ((komat & 0x0008)>>3);
		rku = (((komat & 0x00F0)<<1) &0x00F0) + ((komat & 0x0080)>>3);
		return (rk + rku); 
	}
	//return rk;
}//endof  CChildView::rotateKoma(



/* now the tree functions are not used
// set the status of virgin or runs the junction point:udidx on the edge:dgn in a KoMa [kna] 
int CChildView::edgeStats( int kna, int edgn, int udidx, int virgn){
	int bnry = (virgn<<udidx)<<(edgn*2); //two bit of up and down
	int mado = 3<<edgn;	// the bits of "11"xxxx(edge number)
	int edgc = kedge[kna] & ~mado; // set 00 at the edgn with complement of mado
	return (edgc + bnry); // kedge[kna] is the new status of the connections
}// endof CChildView::edgeStats(
// get the satus at the connection of Kna-Koma, edgn-side and updidx-updown 
int CChildView::getStats( int kna, int edgn, int udidx){
	int mado = 3<<(edgn*2);
	int bnry = kedge[kna] & mado; // set the bit "11" at the edgn with mado;
		bnry = bnry>>(edgn*2);
	return (bnry>>udidx)%2;
} 
*/

// get next connectable Edge number of the line or the arc
int CChildView::nextEdg( int kna, int nowedg, int lindirct){
	int edn =nowedg;
					
	while(TRUE)
	{
		if( lindirct == 1)
		{ edn++;		//CLOCKWISE 	
			if(edn == 4) edn =0;
			if((m_koM[kna]>>edn) & 1 || (m_koM[kna]>>(4+edn)) & 1) return edn;
		} else if( lindirct == 0)
		{	edn--; //COUNTERCLOCKWISE
			if(edn == -1) edn =3;
			if((m_koM[kna]>>edn) & 1 || (m_koM[kna]>>(4+edn)) & 1) return edn;
		}//endof if( lindirct 
	}// endof while(
}// endof CChildView::nextEdg(

//change the koma with 3 statuses to be connecting/turning in the same tile/reversal turning
short int CChildView::makeKoma( int knam, int edgm, short status)
{
	// m_koM[]= 8bit: 1234,5678,9ABC,DEFG, => 
	short int mk;

	if(status == 0)
	{
		mk = m_koM[knam] & ~(1<<edgm); //logical C-AND to set a no-connect-turning edge
		mk =          mk & ~(1<<(edgm+4));  // the Upper bit to 0 

	} else if( status == 1)
	{	
		if( m_koM[knam] < 0) m_koM[knam] = 0; // change "-X" KoMa to "0" 
		mk = m_koM[knam] | (1<<edgm); //logical OR to set a connection edge
		mk =          mk & ~(1<<(edgm+4)); // the Upper bit to 0 

	} else if(status == 2)
	{
		if( m_koM[knam] < 0) m_koM[knam] = 0; // change "-X" KoMa to "0" 
		mk = m_koM[knam] | 1<<(edgm+4); //logical C-AND to set a reversal turing edge
		mk =          mk & ~(1<<edgm); //the lower bit to 0
	}
	return mk;
}// endof CChildView::makeKoma(


// makeKoma( kna, edgn,  offst); -> makeKoma( kna, edgn, status); 
static int prsntedg;	//present cursol position:0,1,2,3 in edge area, -1 not edge area, -99 out of the window
						// 10 corner of right-bottom at red dot tile						
static int indexreagng; // done arragements for making all round types and delete Drop
static int areaSet; // Index of setting Area for pasting after edit copy or Delete or Key B/N function

void CChildView::reArrang(int dtype)	//dtype = 0: change no-connect KoMa to round types, 
{										//-1: delete Tear(Drop) type with Key Shift+R
										//1: connect between KoMa at both egdes  1 or 2 status   	
	int kna = 0; int knxt; 
	indexreagng = 0;
	while(TRUE)
	{
		int nei; 
		int knx = kna%m_komaNoX;//  m_paramDlg.m_KomaX_N//koma position in number in x-axis
		int kny = kna/m_komaNoX; //koma position in number in y-axis		
		if( dtype == -1) // delete Tear(Drop) / only one connected edge type with Key Shift+R 
		{ 
			nei =0; 
			if( m_koM[kna] ==1 || m_koM[kna] ==2 || m_koM[kna] ==4 || m_koM[kna] ==8 ) nei =1;
			else if( m_koM[kna] ==16 || m_koM[kna] ==32 )	nei =1;
			else if( m_koM[kna] ==64 || m_koM[kna] ==128 )	nei =1;
			if( nei ==1)
			{	
				m_koM[kna] = 0;
				indexreagng = 1;
			}
		} else if( dtype == 0 || dtype == 1) 
		{	//0: change diconnection KoMa to round type, 1:  connect between KoMa at both egdes  1 or 2 status
			for( int edgn=0; edgn<4; edgn++)
			{ // edge number, digital order //edgn :edge number 0:right,1:bottom,2:left,3:top
				nei =1; //index for connectable KoMa
				int sced = (m_koM[kna]>>edgn)%2 + (m_koM[kna]>>(4+edgn))%2 *2; // >>:bit shift 
				if(sced >0)  //sced:1,2 side-connected edge
				{	
					if(edgn ==0 )
					{	knxt =knx+1 + kny *m_komaNoX; //right koma from koma[kna]
						if((knx+1 ==m_komaNoX) || ((m_koM[knxt]>>2)%2==0 && (m_koM[knxt]>>(4+2))%2==0) ) nei =0;
					} else if(edgn ==1 )
					{ 	knxt =knx + (kny+1)*m_komaNoX; //bottom koma from koma[kna]
						if((kny+1 ==m_komaNoY) || ((m_koM[knxt]>>3)%2==0 && (m_koM[knxt]>>(4+3))%2==0) ) nei =0;
					} else if(edgn ==2 )
					{ 	knxt =knx-1 + kny *m_komaNoX; //left koma from koma[kna] 
						if((knx-1 == -1)       || ((m_koM[knxt]>>0)%2==0 && (m_koM[knxt]>>(4+0))%2==0) ) nei =0;
					} else if(edgn ==3 )
					{	knxt =knx + (kny-1)*m_komaNoX; //top koma from koma[kna] 
						if((kny-1 == -1)       || ((m_koM[knxt]>>1)%2==0 && (m_koM[knxt]>>(4+1))%2==0) ) nei =0;
					}//endof if(edgn

					if( nei ==0 /*&& dtype == 0*/) //make KoMa round
					{
						m_koM[kna] = makeKoma( kna, edgn, dtype);//make Koma round 
						indexreagng = 1;
					} else if( nei ==1 && dtype == 1 ) // connect between KoMa at both egdes  1 or 2 status
					{	
						int ednn;  
						if( edgn <2)		ednn =edgn +2;
						else if( edgn >1)	ednn =edgn -2;
						if( (m_koM[kna]>>edgn)%2==1 && (m_koM[knxt]>>(4+ednn))%2==1 )
								connectDiscon( knxt, ednn, 1);// (,,X): 0,1,2 status of edge of KoMa[kna] 	
						indexreagng = 1;
					}
				} // endof if(sced 
			} // endof for( edgn
		} //endof if( dtype
		if( kna++ == m_komaNoX * m_komaNoY){  break; } // all kolam koma were processed		
	}//endof while(

	// 凹凸を削る　after deleting 0 or drop type KoMa
	//if(indexreagng == 0 && dtype == -1)
	kna = 0;	
	if( dtype == -1)
	  while(TRUE)
	  {
		if( m_koM[kna] == 3 && m_koM[kna+1] == 6 && 
							( m_koM[kna+m_komaNoX]%2 == 0 && (m_koM[kna+m_komaNoX]>>4)%2 == 0) ) //up projection
		{	
			connectDiscon( kna,			   0, 0);	
			connectDiscon( kna+m_komaNoX,  0, 1);
			indexreagng = 2;
		} else if( m_koM[kna] == 9 && m_koM[kna+1] == 12 &&
							( m_koM[kna-m_komaNoX]%2 == 0 && (m_koM[kna-m_komaNoX]>>4)%2 == 0)) //bottom projection 
		{
			connectDiscon( kna,			   0, 0);
			connectDiscon( kna-m_komaNoX,  0, 1);
			indexreagng = 2;
		} else if( m_koM[kna] == 6 && m_koM[kna+m_komaNoX] == 12 && 
							( (m_koM[kna-1]>>1)%2 == 0 && (m_koM[kna-1]>>(4+1))%2 == 0 ) ) //rihg projectiont 
		{	
			connectDiscon( kna,		1, 0);	
			connectDiscon( kna-1,	1, 1);
			indexreagng = 2;
		} else if( m_koM[kna] == 3 && m_koM[kna+m_komaNoX] == 9 && 
							( (m_koM[kna+1]>>1)%2 == 0 && (m_koM[kna+1]>>(4+1))%2 == 0 ) ) //left  projection
		{
			connectDiscon( kna,		1, 0);	
			connectDiscon( kna+1,	1, 1);
			indexreagng = 2;
		}
		if( kna++ == m_komaNoX * m_komaNoY){  break; } // all kolam koma were processed
	}//endof while(

	// for slant(? 階段状の繋がる) connections　次のShift+S 処理で！！！元に戻る 
	kna =0;	
	if(indexreagng == 0 && dtype == -1)
	  while(TRUE)
	  {
		if( m_koM[kna-1] == 9 && m_koM[kna] == 6 && m_koM[kna+m_komaNoX] == 9 && m_koM[kna-1+m_komaNoX] < 1) //up right projection
		{	
			connectDiscon( kna,				1, 0);	
			connectDiscon( kna,				2, 0);	
			connectDiscon( kna-1+m_komaNoX, 0, 1);
			connectDiscon( kna-1+m_komaNoX, 3, 1);
			indexreagng = 3;
		} else if( m_koM[kna-1] == 3 && m_koM[kna] == 12 && m_koM[kna-m_komaNoX] == 3 && m_koM[kna-1-m_komaNoX] < 1) //bottom projection 
		{	
			connectDiscon( kna,				2, 0);	
			connectDiscon( kna,				3, 0);	
			connectDiscon( kna-1-m_komaNoX, 0, 1);
			connectDiscon( kna-1-m_komaNoX, 1, 1);
			indexreagng = 3;
		} else if( m_koM[kna-m_komaNoX] == 6 && m_koM[kna] == 9 && m_koM[kna+1] == 6 && m_koM[kna+1-m_komaNoX] < 1) //bottom projection 
		{		
			connectDiscon( kna,				0, 0);
			connectDiscon( kna,				3, 0);
			connectDiscon( kna+1-m_komaNoX, 1, 1);	
			connectDiscon( kna+1-m_komaNoX, 2, 1);
			indexreagng = 3;
		} else if( m_koM[kna+1] == 12 && m_koM[kna] == 3 && m_koM[kna+m_komaNoX] == 12 && m_koM[kna+1+m_komaNoX] < 1) //up left projection 
		{	
			connectDiscon( kna,				0, 0);
			connectDiscon( kna,				1, 0);
			connectDiscon( kna+1+m_komaNoX, 2, 1);
			connectDiscon( kna+1+m_komaNoX, 3, 1);
			indexreagng = 3;
		}
		if( kna++ == m_komaNoX * m_komaNoY) break;  // all kolam koma were processed
	}//endof while(

	// for conner connections !!　左上コーナと後では違う　例DiamondCarpet
	kna =0;	
	if(indexreagng == 0 && dtype == -1)
	  while(TRUE)
	  {
		if( m_koM[kna+1] == 5 && m_koM[kna] == 3 && m_koM[kna+m_komaNoX] == 10 && m_koM[kna+1+m_komaNoX] < 1) //up left projection
		{
			connectDiscon( kna,				0, 0);	
			connectDiscon( kna,				1, 0);	
			connectDiscon( kna+1+m_komaNoX, 2, 1);	
			connectDiscon( kna+1+m_komaNoX, 3, 1);
			indexreagng = 4;
		} else if( m_koM[kna+1] == 5 && m_koM[kna] == 9 && m_koM[kna-m_komaNoX] == 10 && m_koM[kna+1-m_komaNoX] < 1) //bottom left projection 
		{
			connectDiscon( kna,				0, 0);
			connectDiscon( kna,				3, 0);
			connectDiscon( kna+1-m_komaNoX, 1, 1);
			connectDiscon( kna+1-m_komaNoX, 2, 1);
			indexreagng = 4;
		} else if( m_koM[kna-m_komaNoX] == 10 && m_koM[kna] == 12 && m_koM[kna-1] == 5 && m_koM[kna-1-m_komaNoX] < 1) //bottom right projection 
		{	
			connectDiscon( kna,				2, 0);
			connectDiscon( kna,				3, 0);
			connectDiscon( kna-1-m_komaNoX, 0, 1);
			connectDiscon( kna-1-m_komaNoX, 1, 1);
			indexreagng = 4;
		} else if( m_koM[kna-1] == 5 && m_koM[kna] == 6 && m_koM[kna+m_komaNoX] == 10 && m_koM[kna-1+m_komaNoX]  < 1) //up right projection 
		{
			connectDiscon( kna,				1, 0);
			connectDiscon( kna,				2, 0);
			connectDiscon( kna-1+m_komaNoX, 0, 1);
			connectDiscon( kna-1+m_komaNoX, 3, 1);
			indexreagng = 4;
		}
		if( kna++ == m_komaNoX * m_komaNoY) break;  // all kolam koma were processed
	}//endof while(

	// for step conner connections
	kna =0;	
	if(indexreagng == 0 && dtype == -1)
	  while(TRUE)
	  {
		if( m_koM[kna+1] == 5 && m_koM[kna] == 3 && m_koM[kna+m_komaNoX] == 12 && m_koM[kna+1+m_komaNoX] < 1) //up left projection
		{
			connectDiscon( kna,				0, 0);
			connectDiscon( kna,				1, 0);
			connectDiscon( kna+1+m_komaNoX, 2, 1);
			connectDiscon( kna+1+m_komaNoX, 3, 1);
			indexreagng = 5;
		} else if( m_koM[kna+1] == 6 && m_koM[kna] == 9 && m_koM[kna-m_komaNoX] == 10 && m_koM[kna+1-m_komaNoX] < 1) //bottom left projection 
		{
			connectDiscon( kna,				0, 0);
			connectDiscon( kna,				3, 0);
			connectDiscon( kna+1-m_komaNoX, 1, 1);
			connectDiscon( kna+1-m_komaNoX, 2, 1);
			indexreagng = 5;
		} else if( m_koM[kna-m_komaNoX] == 3 && m_koM[kna] == 12 && m_koM[kna-1] == 5 && m_koM[kna-1-m_komaNoX] < 1) //bottom right projection 
		{	
			connectDiscon( kna,				2, 0);
			connectDiscon( kna,				3, 0);
			connectDiscon( kna-1-m_komaNoX, 0, 1);
			connectDiscon( kna-1-m_komaNoX, 1, 1);
			indexreagng = 5;
		} else if( m_koM[kna-1] == 9 && m_koM[kna] == 6 && m_koM[kna+m_komaNoX] == 10 && m_koM[kna-1+m_komaNoX] < 1) //up right projection 
		{
			connectDiscon( kna,				1, 0);
			connectDiscon( kna,				2, 0);
			connectDiscon( kna-1+m_komaNoX, 0, 1);
			connectDiscon( kna-1+m_komaNoX, 3, 1);
			indexreagng = 5;
		}
		if( kna++ == m_komaNoX * m_komaNoY) break;  // all kolam koma were processed
	}//endof while(

}//endof reArrang() 

//最後Y行,X列をShift+'X'で消す　縮める　
// toggle of connect or disconnect the edge between two komas at present cursor point
void CChildView::connectDiscon( int knp, int edge, short int eval)
{								// eval: 0,1,2 status of edge of knp KoMa
	int knx = knp%m_komaNoX;	//koma position number in x-axis
	int kny = knp/m_komaNoX;	//koma position number in Y-axis
	int knm, edgm; // neighbor koma number and edge  
	// for expanding KoMa array 
	//typedef struct tagRECT {
	//   LONG left;
	//   LONG top;
	//   LONG right;
	//   LONG bottom;
	//} RECT;

	if( edge == 0) // to right, set the next koma of knp
	{	
		edgm = 2;	  
		if( knx+1 < m_komaNoX ) knm = knp +1;	 //right koma from koma[knp]
		else // expanding right column KoMa 
		{	
			for( short na = 0; na < m_komaNoX*m_komaNoY; na++)// keep the old pattern in the old matrix
					m_koMxy[na%m_komaNoX][na/m_komaNoX] = m_koM[na];
			//short Dxbk[40], Dybk[40];// change [numger] depend on m_KmDxy[number now 40]
			//for( short ndk = 0; ndk < m_DiaKm; ndk++)//m_DiaKmはDiagonalKoMa数(1-40)				
			//{		
			//	Dxbk[ndk] = m_KmDxy[ndk]%m_komaNoX;
			//	Dybk[ndk] = m_KmDxy[ndk]/m_komaNoX;
			//}
			//if(m_loopNum > 0) // when multiLoop, memorize Number of starting KoMa to New Number
			//int sttX[10], sttY[10];
			//for( int istt =0; istt < m_loopNum; istt++) //keepitng X,Y positions
			//	{
			//		sttX[istt] = m_strtKoma[istt]%m_komaNoX;
			//		sttY[istt] = m_strtKoma[istt]/m_komaNoX; 
			//	}

			m_wndParam.m_KomaX_N = m_komaNoX = m_komaNoX +1;	//expand column KoMa array
			CRect wd_rect;
			GetWindowRect(wd_rect);
			int wnd_xwidth = wd_rect.right - wd_rect.left;
			if( wnd_xwidth -45 < m_kks * m_komaNoX ) 
			{
				m_kks =  (wnd_xwidth -45)/m_komaNoX; 
				m_wndParam.m_KomaSize = m_kks;	// = m_ImageSizWidth/m_KomaX_N;
				cri = (int)(m_kks/2.0*1.41421356/2.0); // circle radius of the arc	
				pri = (int)( 1+ m_kks/2.0*1.41421356/20.0); // circle radius of the dot/pulli  
				whd =  m_kks/5;		//nWidth,nHeight 角の丸みの楕円形の幅と高さ
			}
			m_wndParam.m_ImageSizWidth = m_kks *m_komaNoX; 
			m_wndParam.UpdateData(false); // 2009/11/4 for sending the data to Dialog 
			m_imageSiH = m_kks *m_komaNoX +45;	// size of image area m_paramDlg.m_ImageSizWidth; //450
			
			// reproducing all KoMaTile data
			for( short knya =0; knya < m_komaNoY; knya++)   
			{
				for( short knxa =0; knxa < m_komaNoX-1; knxa++) // without added one row  
				{
					m_koM[knxa + knya*m_komaNoX] = m_koMxy[knxa][knya];
				}	
				m_koM[(m_komaNoX-1) + knya*m_komaNoX] = short(0x8000);//=負最大値,追加列を初期化
			}
			/*for( ndk = 0; ndk < m_DiaKm; ndk++) //reproduing Diagonal KoMa				
					m_KmDxy[ndk] = Dxbk[ndk] +Dybk[ndk]*m_komaNoX;
			if(m_loopNum > 0) // when multiLoop, change Number of starting KoMa to New Number
				for( int istt =0; istt <m_loopNum; istt++)
				{
					m_strtKoma[istt] = sttY[istt] * m_komaNoX + sttX[istt];
				}
            */
			knap = knp = knx +kny*m_komaNoX; //new present cursor KoMa number
 			knm = knap +1;// new cursor neighber KoMa number

 		}
	} else	if( edge == 1)// to bottom
	{	
		edgm = 3;	
		if(kny+1 < m_komaNoY ) knm = knp + m_komaNoX;	 //bottom koma from koma[knp]
		else // expanding bottom  KoMa
		{	
			for( short na = 0; na < m_komaNoX*m_komaNoY; na++)// keep the old pattern in the old matrix
					m_koMxy[na%m_komaNoX][na/m_komaNoX] = m_koM[na];
			//expand row KoMa array
			m_wndParam.m_KomaY_M = m_komaNoY = m_komaNoY + 1;	
			CRect wd_rect;
			GetWindowRect(wd_rect);
			int wnd_yhight = wd_rect.bottom - wd_rect.top;
			if( wnd_yhight -70 < m_kks * m_komaNoY ) 
			{
				m_kks =  (wnd_yhight -70)/m_komaNoY; 
				m_wndParam.m_KomaSize = m_kks;	// = m_ImageSizWidth/m_KomaX_N;
				cri = (int)(m_kks/2.0*1.41421356/2.0); // circle radius of the arc	
				pri = (int)( 1+ m_kks/2.0*1.41421356/20.0); // circle radius of the dot/pulli  
				whd =  m_kks/5;		//nWidth,nHeight 角の丸みの楕円形の幅と高さ
			}
			m_wndParam.m_ImageSizWidth = m_kks *m_komaNoX; 
			m_wndParam.UpdateData(false); // 2009/11/4 for sending the data to Dialog 
			m_imageSiV = m_kks*m_komaNoY +70;  // size of image area  
			// set added row KoMaTile data (0x8000)
			for( short knxa =0; knxa < m_komaNoX; knxa++)   
			{
					short naa = knxa + (m_komaNoY-1)*m_komaNoX;
					m_koM[naa] = short(0x8000);//=負最大値,
			}	
			knm = knp +m_komaNoX;
		}
	} else	if( edge == 2)// to left // set neighber KoMa and edge 
	{	
		if( knx -1 > -1 ){ edgm = 0; knm = knp -1;  }//left koma from koma[knp] 
		else edgm = -1; //return; //2012/05/10 以後　KolamDesigner4.6.5 右端、上端も模様を変えられる
	} else	if( edge == 3)// to top
	{	
		if( kny -1 > -1 ){ edgm =1; knm = knp - m_komaNoX; }//top koma from koma[knp] 
		else edgm = -1; //return;
	}
//	else if( edge == -1) return;	// the same as if( prsntedg == -1),  out of edge area
 //ここから挿入to delete the bottom row and/or right column	
	else if( (edge == -97) || (edge == -99) ) //Key Shift+'X'with cursor at LastY行row,その行を削除 
	{	//Cursor in the row except/including the last corner
		// 最下行なので、それ以上の残る駒のデータ順番は変わらないため　以下のBackUp不要
		//for( short na = 0; na < m_komaNoX*m_komaNoY; na++)// keep the old pattern in the old matrix
		//					m_koMxy[na%m_komaNoX][na/m_komaNoX] = m_koM[na];

		/*short Dxbk[40], Dybk[40], Dvbk[40][4];
		for( short ndk = 0; ndk < m_DiaKm; ndk++)//temporary memorym_DiaKmはDiagonalKoMa数(1-40)				
		{		
				Dxbk[ndk] = m_KmDxy[ndk]%m_komaNoX;
				Dybk[ndk] = m_KmDxy[ndk]/m_komaNoX;
				for( short vrtx =0; vrtx < 4; vrtx++) Dvbk[ndk][vrtx] = m_KmDvx[ndk][vrtx];
		}
		*/
		
		m_wndParam.m_KomaY_M = m_komaNoY = m_komaNoY - 1;	//delete the row KoMa 
		m_wndParam.UpdateData(false); // 2009/11/4 for sending the data to Dialog 
//			CRect wd_rect;
//			GetWindowRect(wd_rect);
//			int wnd_yhight = wd_rect.bottom - wd_rect.top;
		m_imageSiV = m_kks*m_komaNoY +70;  // size of image area  

		//for ( short knxa =0; knxa < m_komaNoX; knxa++) //reproducing all KoMaType data
		//for ( short knya =0; knya < m_komaNoY; knya++)
		//m_koM[knxa + knya*m_komaNoX] = m_koMxy[knxa][knya];

		/*short m_DiaKmB = 0;	
		for( ndk = 0; ndk < m_DiaKm; ndk++)  //reproduing Diagonal KoMa, m_DiaKmはOld DiagonalKoMa数(1-40)				
		{    
			if( Dybk[ndk] < m_komaNoY )// in the New Y range 
			{
				m_KmDxy[m_DiaKmB] = Dxbk[ndk] +Dybk[ndk]*m_komaNoX;
				for( short vrtx =0; vrtx < 4; vrtx++) m_KmDvx[m_DiaKmB][vrtx] = Dvbk[ndk][vrtx];
				m_DiaKmB++;
			} 
		}//endof for( short kndx-1
	    m_DiaKm = m_DiaKmB;
		*/
		if(edge == -97) knap = knx + (m_komaNoY -1)*m_komaNoX; //knp = //new cursor KoMa number
		// else if(edge == -99) 後の == -99)で設定する
		edgm = -2; //これがなくても良いが　揃えるため
			
	}

	if( (edge == -98) || (edge == -99) ) // Key Shift+'X' with cursor at at LastX列Column,その列を削除 
	{ // ここでelse がないのは-99でも処理するため、//Cursor in the column except/including the last corner
		for( short na = 0; na < m_komaNoX*m_komaNoY; na++)// keep the old pattern in the old matrix
					   m_koMxy[na%m_komaNoX][na/m_komaNoX] = m_koM[na];
		/*short Dxbk[40], Dybk[40], Dvbk[40][4];
		//for( short ndk = 0; ndk < m_DiaKm; ndk++)//m_DiaKmはDiagonalKoMa数(1-40)				
		//{		
		//		Dxbk[ndk] = m_KmDxy[ndk]%m_komaNoX;
		//		Dybk[ndk] = m_KmDxy[ndk]/m_komaNoX;
		//		for( short vrtx =0; vrtx < 4; vrtx++) Dvbk[ndk][vrtx] = m_KmDvx[ndk][vrtx];
		//}
			//short sttX[10], sttY[10];
			//if(m_loopNum > 0) // when multiLoop, memorize Number of starting KoMa to New Number
			//for( short istt =0; istt < m_loopNum; istt++) //keepitng X,Y positions
			//{
			//		sttX[istt] = m_strtKoma[istt]%m_komaNoX;
			//		sttY[istt] = m_strtKoma[istt]/m_komaNoX; 
			//}
		*/
		m_wndParam.m_KomaX_N = m_komaNoX = m_komaNoX -1;	//delete last column KoMa 
		m_wndParam.m_ImageSizWidth = m_kks *m_komaNoX; 
		m_wndParam.UpdateData(false); // 2009/11/4 for sending the data to Dialog 
		m_imageSiH = m_kks *m_komaNoX +45;	// size of image area m_paramDlg.m_ImageSizWidth; //450

		for ( short knxa =0; knxa < m_komaNoX; knxa++) //reproducing all KoMaType data
		for ( short knya =0; knya < m_komaNoY; knya++)
		       m_koM[knxa +knya*m_komaNoX] = m_koMxy[knxa][knya];	
		/*short m_DiaKmB = 0;	
		//for( ndk = 0; ndk < m_DiaKm; ndk++)  //reproduing Diagonal KoMa, m_DiaKmはOld DiagonalKoMa数(1-40)				
		//{    
		//	if( Dxbk[ndk] < m_komaNoX )// in the New X range 
		//	{
		//		m_KmDxy[m_DiaKmB] = Dxbk[ndk] +Dybk[ndk]*m_komaNoX;
		//		for( short vrtx =0; vrtx < 4; vrtx++) m_KmDvx[m_DiaKmB][vrtx] = Dvbk[ndk][vrtx];
		//		m_DiaKmB++;
		//	} 
		//}//endof for( short ndx
	    //m_DiaKm = m_DiaKmB;
		*/
		if(edge == -99) knap = m_komaNoX -1 +(kny-1)*m_komaNoX;  //new cursor KoMa number
		else			knap = m_komaNoX -1 +kny*m_komaNoX; //if(edge == -98) 
		edgm = -2; 
			//if(m_loopNum > 0) // when multiLoop, change Number of starting KoMa to New Number
			//for(  istt =0; istt <m_loopNum; istt++)
			//{
			//		m_strtKoma[istt] = sttX[istt] +sttY[istt]*m_komaNoX;
			//}
	}
//ここまで挿入	

	if( edgm > -2 ) m_koM[knp] = makeKoma( knp, edge, eval); // present koMa at cursor
	if( edgm > -1 ) m_koM[knm] = makeKoma( knm, edgm, eval); // neighbor koMa 

	//MessageBeep(MB_ICONEXCLAMATION); 
}//endof connectDiscon(

//now only order 0,  index to order Edge data in 0:random, 1:countup in digit
void CChildView::pattnGenrtn( int order )
{ 	
	int ij;	int ii; int roop = 1;  int ie; 
	
	CClientDC dc(this); // for dc.Texout
	CString	strc; 

	strc.Format(" Shift+G is generating KoMa without 0-Koma, wait it or key G to stop");
	//short m_edcd[ 3613]; // 50x37*2-(50+37), m_komaNoX*m_komaNoY*2 -(m_komaNoX+m_komaNoY)

	dc.TextOut( 0, m_kks*m_komaNoY+70, strc);  //m_kks*m_komaNoY+70the text is not drawn in the saved image, only on the window
	Invalidate(FALSE);// show only the last image nagata 	

	while(roop){
		for( ie = 0; ie < m_ednum; ie++)  // All edges are connected in random with Prob 0.5
		{
			if(order == 0) //now only order 0
			{
				if( (double)rand()/(double)RAND_MAX < 0.5)	m_edcd[ie] = 0; 
				else										m_edcd[ie] = 1;
			} // else if(order ==1)  now moved to geNeration(0) 				
		}
		ie = 0;  
		for(ii = 0; ii < m_komaNoY; ii++)// make KoMa with Edge-code 
		{ 
			knap = m_komaNoX *ii; //ie = (m_komaNoX*2 -1)*ii; 
			for( ij = 1; ij < m_komaNoX; ij++){ // vertical edges
					//prsntedg =0; 
					connectDiscon( knap, 0, m_edcd[ie] );  // 0th & 2nd edge ->1/0 
					ie++;	knap++; 
			}
			if(ii == m_komaNoY-1) break;
			knap = m_komaNoX *ii; //ie = (m_komaNoX*2 -1)*ii +(m_komaNoX -1);
			for( ij = 0; ij < m_komaNoX; ij++){ // horizontal edges
					//prsntedg =1; 
					connectDiscon( knap, 1, m_edcd[ie] );  // 1st & 3rd edge ->1/0 
					ie++;	knap++; 
			}
		}// endof for(ii
		// check a Quadrant(1/4) of all KoMa >0 
		for( ii = 0; ii < (m_komaNoX+1)/2*(m_komaNoY+1)/2; ii++)
		{ 
			int iikx = ii%( (m_komaNoX+1)/2);
			int iiky = ii/( (m_komaNoX+1)/2);
			int iikxy = iikx + iiky *m_komaNoX;
			if( m_koM[iikxy] == 0){	roop = 1;	break; } // there is a 0 KoMa, so again 
			else					roop = 0;
		}
//		if( GetAsyncKeyState('S') & 0x8000) break; //to stop , this not work, Key G to stop autoGeneration
		
	}// endof while
	return; 
}//endof CChildView::ptnGeneration

// Auto-generation of Kolam pattern Mikan !!!!!!!!!!! for 3-status edge
void CChildView::geNeration( int gemod)//KoMa random 0:Sequence,1:H&V-Sym, 2:Rot-Sym
{ 
	// static unsigned long edgvl = 0; //  = long at Windows 32 bit C compiler
	// 5x4 pulli has 31 edges = m_komaNoX*m_komaNoY*2 -(m_komaNoX+m_komaNoY); 
	int ij;	int ii, ie; 
	
	switch(gemod) 
	{	
		case 0:	// countup generating with Edge-code m_edcd[ie]// 31 edges in 5x4 KoMa, 40 edges in 5x5  
				// unsigned long m_ednum 全Bitの組合せパターン数
				// pim は　m_saveDatafl == 1 データ保存のとき　初めのSingleまでのMultiは無視、計数されない
//	m_ednum = m_komaNoX*m_komaNoY*2 -m_komaNoX-m_komaNoY;//G で　駒が勝手にY軸で増えるのを防ぐ2011/06/10！
//	m_edpnm = (unsigned long)pow( 2.0, m_ednum ) -1; // index edge patterns, except all of 0

/* 記録のときもMultiを正確にするため削除
			if( m_saveDatafl == 1 && pia == 0) //pass to set the first single pattern
			{		//初めのSingle櫛型を作るため それまでに起こるMultiは無視　計数しない
				memset(m_edcd, 0, sizeof(m_edcd) ); // 　edge の0,1,2(未）　条件,intialization
				ie = 0;
				for( ij = 1; ij < m_komaNoX; ij++) // first vertical edges between right and left
				{
					m_edcd[ie] = 1;
					pia = pia + (long)pow(2.0, ie); //pia:number of generated patters inculding KoMa0
					ie++;
				}
				for( ii = 1; ii < m_komaNoY; ii++)
				{
					for( ij = 0; ij < m_komaNoX; ij++) // following horizontal edges between lower and upper
					{   
						m_edcd[ie] = 1;
						pia = pia + (long)pow(2.0, ie);  					
						ie++;
					}
				}
			}	else 
*/			if( pia == 0) //pass until the last row of horizontal edges between upper and lower
			{	//　最下部の全横Edgeのみを繋ぐ　そこまでMultiはないので　無視されない　 
			  for( ij = 0; ij < m_komaNoX; ij++) 
			  {										//ie = m_ednum -m_komaNoX
				  ie = m_ednum -m_komaNoX*2 +1 +ij; // for only the last row Koma connected at upper edge
				  m_edcd[ie] = 1; //set the last Koma connected at upper edge
				  pia = pia + (long)pow(2.0, ie);
			  }
			}	else //counting up step by step on digits
			{	
				m_edcd[0]++;
				for( ii = 0; ii < m_ednum; ii++)
					if ( m_edcd[ii] == 2) 					
					{	//edgeDataをbit列とみなして、繰上げ（=2）の場合は次のEdge(bit)に+1する。 
						m_edcd[ii] = 0; 
						m_edcd[ii+1] = m_edcd[ii+1] +1; 
					}
				pia++; 
				m_alledge = 1;//checking the last of all edges =1
				for( ii = 0; ii < m_ednum; ii++) if ( m_edcd[ii]  == 0) { m_alledge = 0;  break; }
			}
  
			ie = 0; // edge index //未完これを修正したら同じ設定をするpattnGenrtn( int order )も修正要　
			for( ii = 0; ii < m_komaNoY; ii++){
				knap = m_komaNoX *ii;  ie = (m_komaNoX*2 -1)*ii; //
				for( ij = 1; ij < m_komaNoX; ij++)
				{ // vertical edges
					connectDiscon( knap, 0, m_edcd[ie] );  //0th/right edge of leftKoMa to 2nd of rightKoma ->1/0 
					ie++;	knap++; 
				}
				if(ii == m_komaNoY -1)  break; 
				knap = m_komaNoX *ii; ie = (m_komaNoX*2 -1)*ii +(m_komaNoX -1);//
				for( ij = 0; ij < m_komaNoX; ij++)
				{ // horizontal edges
 					connectDiscon( knap, 1, m_edcd[ie] );  // 1st/lower edge of upperKoMa to 3rd of lowerKoma ->1/0 
					ie++;	knap++; // the next/neighbor KoMa
				}
				//m_koM[inko] == 0のとき　trace しないのはOnTimer(　で設定　　　
			}// endof for(ii
			drwNln = 1; // set N-lines 
			break; 

		case 1:	// left/right & up/down symmetric 
			// キーが押されるときはGetKeyStateの最上位ビットが1 =0x8000負値、押されていないときは0、
			// if()は　0以外は真(true)となり、0だけが偽(false)
			// リアルタイム性重視ならGetAsyncKeyState()を使う
			// GetKeyState()とGetAsyncKeyState()の区別はキーが押されて,すぐに反映されるのが後者で、
			//（つまりキーが押されて発生するハードウェア割り込みに対応する）リアルタイム性
			// GetKeyState()はメッセージキューに溜まっている物を見るようなので、
			// 何かの処理中にキーが押されてもGetKeyState()は反映されないのです
			if( GetAsyncKeyState( VK_SHIFT ) & 0x8000 ) pattnGenrtn(0);  //Shift+1 set order mode edge data 0 :KoMa random

			// left/right  symmetric from the half of left part
			for(ii = 0; ii < (m_komaNoY+1)/2; ii++) //vertical
			{	
				for( ij = 0; ij < m_komaNoX/2; ij++) // horizontal
				{		
					ie = m_komaNoX-1-ij + ii * m_komaNoX; //  symmetric 
					m_koM[ ie ] = ( m_koM[ij + ii *m_komaNoX] ); // X,Y axis 
					short e0 = (m_koM[ie]>>0)%2 + ((m_koM[ie]>>(4+0))%2) *2; 
					short e2 = (m_koM[ie]>>2)%2 + ((m_koM[ie]>>(4+2))%2) *2;
					m_koM[ie] = makeKoma( ie, 0, e2);
					m_koM[ie] = makeKoma( ie, 2, e0);
 				} 
				if( m_komaNoX%2) //center column of odd Kolam matrix
				{
					ij = m_komaNoX/2;
					ie = ij + ii * m_komaNoX;
					short e2 = (m_koM[ie]>>2)%2 + ((m_koM[ie]>>(4+2))%2) *2;
					m_koM[ie] = makeKoma( ie, 0, e2);
				}
			}// endof for(ii
			drwNln = 2; // to draw green dot of the original part
			LMbX = LMbY = 0;  	// begining KoMa in N-line
			LMeX = (m_komaNoX+1)/2-1;	// ending KoMa in N-line
			LMeY = (m_komaNoY+1)/2-1;	
			Invalidate(FALSE);// show only the last image nagata
			MessageBox(_T("made horizontal sym from upper-left half\nnext is vertical and connected"));	
			// up&down symmetric 
			for( ij = 0; ij < m_komaNoX; ij++) // horizontal
			{	
				for(ii = 0; ii < m_komaNoY/2; ii++) // vertical 
				{		
					ie = ij + (m_komaNoY-1-ii) * m_komaNoX; // vertical symmetric 
					m_koM[ ie ] = ( m_koM[ij + ii *m_komaNoX] ); // X,Y axis 
 					int nn = 0;
					if( m_koM[ie] >15) nn = 4; 
					short e1 = (m_koM[ie]>>1)%2 + ((m_koM[ie]>>(4+1))%2) *2; 
					short e3 = (m_koM[ie]>>3)%2 + ((m_koM[ie]>>(4+3))%2) *2;
					m_koM[ie] = makeKoma( ie, 3, e1);
					m_koM[ie] = makeKoma( ie, 1, e3);
				} 
				if( m_komaNoY%2)// center row of odd Kolam matrix
				{ 
					ii = m_komaNoY/2;
					ie = ij + ii * m_komaNoX;
					short e3 = (m_koM[ie]>>3)%2 + ((m_koM[ie]>>(4+3))%2) *2; 
					m_koM[ie] = makeKoma( ie, 1, e3);
				}
			}// endof for(ij
			reArrang(1); //connect KoMa
			break;

		case 2:	// Rotated Symmetry
			if( GetAsyncKeyState( VK_SHIFT ) & 0x8000 ) pattnGenrtn(0);  //Shift+ set order mode edge data 0 :KoMa random

			for( ij = 0; ij < (m_komaNoX+1)/2; ij++) // horizontal from left area including the center column 縦の行
				for(ii = 0; ii < (m_komaNoY)/2; ii++)	// vertical from upper area except of the center row 横の列
				{
					ie = m_komaNoX-1-ii +ij*m_komaNoX;	// to Rotated  upper-right area  X,Y axis
					m_koM[ ie ] =rotateKoma( m_koM[ij +ii*m_komaNoX] ); // to rotate Koma
				} 
			drwNln = 2; // to draw green dot of the original part
			LMbX = LMbY = 0;  	// begining KoMa in N-line
			LMeX = (m_komaNoX+1)/2-1;	// ending KoMa in N-line
			LMeY = m_komaNoY/2-1;	
			Invalidate(FALSE);// show only the last image nagata
			//MessageBox(_T("rotated left-upper quarter to upper-right\nnext is lower-right then lower-left\nre-makes 1-status edge types"));	
			for( ij = 0; ij < (m_komaNoX+1)/2; ij++) // horizontal from left area including the center column 縦の行
				for(ii = 0; ii < (m_komaNoY)/2; ii++)	// vertical from upper area except of the center row 横の列
				{
					ie = m_komaNoX-1-ij +(m_komaNoY-1-ii)*m_komaNoX;	// to Rotate lower-right area 
					m_koM[ ie ] =rotateKoma(rotateKoma( m_koM[ij +ii*m_komaNoX] )); // to rotatex2 Koma  
				} 
			for( ij = 0; ij < (m_komaNoX+1)/2; ij++) // horizontal from left area including the center column 縦の行
				for(ii = 0; ii < (m_komaNoY)/2; ii++)	// vertical from upper area except of the center row 横の列
				{
					ie = ii +(m_komaNoX-1-ij)*m_komaNoX;	// to Rotate  lower-left area 
					m_koM[ ie ] =rotateKoma(rotateKoma(rotateKoma( m_koM[ij +ii*m_komaNoX] ))); // to rotatex3 Koma
				} 
			reArrang(1); //dtype = 0: change no-connect KoMa to round types,= 1: connect on 1 status-edge

			//to make all edges in the same status 
			if( m_komaNoX%2 ) 		//	in the case of odd Kolam matrix
			{
				ie = m_komaNoX/2 +m_komaNoY/2*m_komaNoX;	//the center Koma 
				short e0 = (m_koM[ie]>>3)%2 + ((m_koM[ie]>>(4+3))%2)*2; //as the upper-edge 
				m_koM[ie] = makeKoma( ie, 0, e0); // the right-edge
				m_koM[ie] = makeKoma( ie, 1, e0); // the lower-edge
				m_koM[ie] = makeKoma( ie, 2, e0); // the left-edge
			}
			reArrang(0); //(dtype = 0): change no-connect KoMa to round types,(= 1): connect on 1 status-edge
			Invalidate();// show only the last image nagata without old image
			break;

		case 3:	// recursive Mikan!!!!!!!!!!!!!!!!
//			static deep = 5; 
//			if( GetAsyncKeyState( VK_SHIFT ) & 0x8000 ) pattnGenrtn(0); //Shift+ set order mode edge data 0 :KoMa random
			reArrang(0);
			reCursive(deep);
			break;
	}// endof switch
		
	prsntedg = -1; 
	Invalidate(FALSE);// show only the last image nagata
	//CChildView::geNeration(gemod); //selfcalling is wrong, Stock over error 
	//'geNeration' : 'CWnd' のﾒﾝﾊﾞではありません。
} // endof CChildView::geNeration(

/* 使い方不明　by nagata
BOOL CChildView::GetCursorPos(LPPOINT lpPoint){
	return TRUE;
}
*/
// Invalidate(TRUE) の場合は、BeginPaint メンバ関数が呼び出されると背景は消去されます。
// (FALSE) の場合は、背景は変更されずに残されます。
// 更新リージョンのあらゆる部分に対して TRUE の場合は、指定した部分のみでなく
// 領域全体の背景が消去されます。

static int saveImg;		// index to set saving any images ON: Key S 
static int animImage;	// index to set saving animation images ON: Key S
static int stilImage;	// index to set saving a still image ON: Key I
static int shftky;		//ShiftKey On
//default :// Key Operation for changing Koma orientation and type
static int strtedg; // starting point; MSB 2 bits:4 sides
					// LSB bit: 2 directions 1:Up crossing & turns round clockwise,0:Down & counterclockwise
static int trce; // draw the trace of stroke Hitofude 0:first line 1:animation 2:final 3:end
static int chnNum;

void CChildView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) // KeyUp で反応させる
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	
	int knx = knap%m_komaNoX;	//koma position number in X-axis
	int kny = knap/m_komaNoX;	//koma position number in Y-axis
	static int  kmty = 0;// for 'V' 
	int ikb; // for undo 

	switch (nChar) // setting Koma position as well as MOUSE
	{	
		case VK_RIGHT: // Allow for moving Koma position 
			if( prsntedg == 0 )
			{
				prsntedg = 1; 
				if(knx+1 < m_komaNoX) knap = knx+1 + kny*m_komaNoX; //right koma from koma[kna]
			} else prsntedg = 0;
//			m_drawImages = TRUE;
			Invalidate(FALSE);
		break;
		case VK_LEFT: // Allow for moving Koma position 
			if( prsntedg == 2 )
			{
				prsntedg = 1; 
				if(knx-1 > -1) knap =  knx-1 + kny*m_komaNoX; //left koma from koma[kna] 
			} else prsntedg = 2;
//			m_drawImages = TRUE;
 			Invalidate(FALSE);
			break;
		case VK_DOWN: // Allow for moving Koma position
			if( prsntedg == 1 )
			{
				prsntedg = 0; 
				if(kny+1 < m_komaNoY) knap =  knx + (kny+1)*m_komaNoX; //bottom koma from koma[kna]
			} else prsntedg = 1;
//			m_drawImages = TRUE;
			Invalidate(FALSE);
		break;
		case VK_UP: // Allow for moving Koma position
			if( prsntedg == 3 )
			{
				prsntedg = 0; 
				if(kny-1 > -1) knap =  knx + (kny-1)*m_komaNoX; //top koma from koma[kna] 
			} else prsntedg = 3;
//			m_drawImages = TRUE;
 			Invalidate(FALSE);
		break;

		// change a type of 6 Kolam Koma and it's oriatation
		case 'C':	// 0= Circle Koma 
			//MessageBeep(MB_ICONEXCLAMATION); 	//MessageBeep(0);
			if( drwNln == 2) break; //avoid onEditPaste() =KeyC
			for( ikb = 0; ikb < m_komaNoX*m_komaNoY; ikb++) m_preKoM[ikb] = m_koM[ikb];// for Undo
			m_koM[knap] = 0;
			Invalidate(FALSE);
		break;
		case 'D':	// 15=Diaond Koma 
			//MessageBeep(MB_ICONEXCLAMATION); 	//MessageBeep(0);
			for( ikb = 0; ikb < m_komaNoX*m_komaNoY; ikb++) m_preKoM[ikb] = m_koM[ikb];// for Undo
			m_koM[knap] = 15;
//			m_drawImages = TRUE;
			Invalidate(FALSE);
		break;
		case 'E':	// initial 5= Eye Pupil Koma 
			//MessageBeep(MB_ICONEXCLAMATION); 	//MessageBeep(0);
			for( ikb = 0; ikb < m_komaNoX*m_komaNoY; ikb++) m_preKoM[ikb] = m_koM[ikb];// for Undo
 			if(m_koM[knap]==5 || m_koM[knap]==10)
					m_koM[knap] = rotateKoma( m_koM[knap]);
			else	m_koM[knap] = 5;
//			m_drawImages = TRUE;
			Invalidate(FALSE);
		break;
		case 'F':	// initial 7= Fan Koma 
			//MessageBeep(MB_ICONEXCLAMATION); 	//MessageBeep(0);
			for( ikb = 0; ikb < m_komaNoX*m_komaNoY; ikb++) m_preKoM[ikb] = m_koM[ikb];// for Undo
			if(m_koM[knap]==7 || m_koM[knap]==13 || m_koM[knap]==14 || m_koM[knap]==11)
					m_koM[knap] = rotateKoma( m_koM[knap]);
			else	m_koM[knap] = 7;
//			m_drawImages = TRUE;
			Invalidate(FALSE);
		break;
		case 'H':	// initial 3= Horse Saddle/Stirrups Koma 
			//MessageBeep(MB_ICONEXCLAMATION); 	//MessageBeep(0);
			for( ikb = 0; ikb < m_komaNoX*m_komaNoY; ikb++) m_preKoM[ikb] = m_koM[ikb];// for Undo
			if(m_koM[knap]==3 || m_koM[knap]==6 || m_koM[knap]==9 || m_koM[knap]==12)
					m_koM[knap] = rotateKoma( m_koM[knap]);
			else	m_koM[knap] = 3;
//			m_drawImages = TRUE;
			Invalidate(FALSE);
		break;
		case 'T':	// initial 1= Tear/Drop Koma 
			//MessageBeep(MB_ICONEXCLAMATION); 	//MessageBeep(0);
			for( ikb = 0; ikb < m_komaNoX*m_komaNoY; ikb++) m_preKoM[ikb] = m_koM[ikb];// for Undo
 			if(m_koM[knap]==1 || m_koM[knap]==2 || m_koM[knap]==4 || m_koM[knap]==8)
					m_koM[knap] = rotateKoma( m_koM[knap]);
			else	m_koM[knap] = 1;
//			m_drawImages = TRUE;
			Invalidate(FALSE);
		break;
		case 'L':	// Leading the Koma Type step by set to all X-D
			//MessageBeep(MB_ICONEXCLAMATION); 	//MessageBeep(0);
			// short int m_N81toE8B[81];  8bit number= N81toE8B[0-80 number];
			// short int m_E8BtoN81[241];  0-80 number= E8BtoN81[8bit number Max 240];
 			short type[25]; 
			type[00] =00; type[01] =01; type[02] =03; type[03] =05; type[04] =07; type[05] =15; 
			type[06] =41; type[07] =44; type[ 8] =53; type[ 9] =31; type[10] =40; type[11] =27; 
			type[12] =36; type[13] =20; type[14] =19; type[15] =26; type[16] =23; type[17] =80; 
			type[18] =50; type[19] =16; type[20] =25; type[21] =17; type[22] =22; type[23] =39; 
			type[24] =-1; 
			for( ikb = 0; ikb < m_komaNoX*m_komaNoY; ikb++) m_preKoM[ikb] = m_koM[ikb];// for Undo
			
			if( GetAsyncKeyState( VK_SHIFT ) & 0x8000 )
			{  // rotation			
				m_preKoM[knap] = m_koM[knap];
				m_koM[knap] = rotateKoma( m_koM[knap]); 
			} else // change the primitive K-cel
			{	
				m_preKoM[knap] = m_koM[knap];
				m_koM[knap] = m_N81toE8B[ type[kmty++] ];	// 1,3,-,-,39,-1				
				if( kmty > 23) kmty = -1;			
			}	
//			m_drawImages = TRUE;
			Invalidate(FALSE);
		break;

		case 'G':// generation of (0) sequential and then Shift+: AutoGenration 
				 // of (1,2,3) re-arrangement or Shift+: random pattern generation 
			//MessageBeep(MB_ICONEXCLAMATION); 	//MessageBeep(0);
			if( m_gemod == 0) // geneMode:sequential
			{
				//if (bAutog)	bAutog = bAutog ? FALSE : TRUE;// toggle switch
				if (bAutog)	
				{
					bAutog = bAutog ? FALSE : TRUE;// toggle switch
					break; 
				
				} else 	if( GetAsyncKeyState( VK_SHIFT ) & 0x8000 ) // When Key Shift, auto generation, //moved to OnSaveImagesDatafiles()
				{			
					bAutog = TRUE;  
					pia = 0;	pim = 0;	pis = 0;	pio = 0; // intialization					
//					memset(m_koM, short int(0x8000), sizeof(m_koM) );//これではー１が入力せず、０となる。
					for( int ii = 0; ii < 1850; ii++)  m_koM[ii] = short int(0x8000); //-1 & ~0xFF;
					memset(m_edcd, 0, sizeof(m_edcd) ); // intialization//初期設定2011/03/11
					memset(m_numEdges, 0, sizeof(m_numEdges) ); // intialization					
					drwNln = 0; // reset N-lines
					SetTimer(10, TIMER_INTERVAL, NULL); // OnTimer(ID,timeout msecond,)
						// timeout should be shorter than process time,
				} else 
				{
					for( ikb = 0; ikb < m_komaNoX*m_komaNoY; ikb++) m_preKoM[ikb] = m_koM[ikb];// for Undo
					geNeration( 0 ); // 0:sequential,
//					drwNln = 1; // set N-lines 
//					m_drawImages = TRUE;
					Invalidate(FALSE);// show only the last image nagata
				}
			} else if( m_gemod > 0 ) //geneMode:Rand V&H Sym, Rot Sym, Recursive
			{
				if( (m_gemod == 2) && (m_komaNoX != m_komaNoY) ) // to make square matrix as size as horizontal number
				{
					m_komaNoY = m_wndParam.m_KomaY_M = m_komaNoX; 
					m_imageSiV = m_kks *m_komaNoY +70;  // size of image area  	
					m_ednum = m_komaNoX*m_komaNoY*2 -m_komaNoX-m_komaNoY;
					m_edpnm = (unsigned long)pow( 2.0, m_ednum ) -1; // index edge patterns, except all of 0
				}
				for( ikb = 0; ikb < m_komaNoX*m_komaNoY; ikb++) m_preKoM[ikb] = m_koM[ikb];// for Undo
				geNeration( m_gemod); // 1:Verti&Hori Sym, 2:RotatedSym, 3:Recursive incluing Random on Shift+
//				drwNln = 1; // set N-lines 
//				m_drawImages = TRUE;
				Invalidate(FALSE);// show only the last image nagata
			}  
		break;

		case '0':	// arc stroke 
			if( m_drawMode ){ // 1: for edgChain mode 
				if(m_numEdges[m_fudeNum][0] == 0)
				{   
					m_startChainX[m_fudeNum] = knap%m_komaNoX;
					m_startChainY[m_fudeNum] = knap/m_komaNoX;
					int udindx = 1- m_startSide[m_fudeNum]%2;// toggleSwitch LSB:1 CLOCKWISE, 0 UNCLOCK
					if(prsntedg <0)	m_startSide[m_fudeNum] = udindx;
					else			m_startSide[m_fudeNum] = prsntedg*2 + udindx;// starting 4 sides x 2 directions, 4 bits: 4 sides,
				}	else if(m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ] >31)
				{				m_chnNo[m_fudeNum]++;
								m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ] = 0; 
				}//for edgeChain 32 bits
				MessageBeep(MB_ICONEXCLAMATION); 	//MessageBeep(0);
				m_edgeChain[m_fudeNum][ m_chnNo[m_fudeNum] ] = m_edgeChain[m_fudeNum][ m_chnNo[m_fudeNum] ]<<1;//shift up to add 0 edge to the LSB
				m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ] = m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ] + 1;
//				m_drawImages = TRUE;
				Invalidate(FALSE);
			}
		break;
		case '1':	// line stroke 
			if( m_drawMode ){ // 1: for edgChain mode 
				if(m_numEdges[m_fudeNum][0] == 0 )
				{   
					m_startChainX[m_fudeNum] = knap%m_komaNoX;
					m_startChainY[m_fudeNum] = knap/m_komaNoX;
					int udindx = 1- m_startSide[m_fudeNum]%2;// toggleSwitch LSB:1 CLOCKWISE, 0 UNCLOCK
					if(prsntedg <0)	m_startSide[m_fudeNum] = udindx;
					else			m_startSide[m_fudeNum] = prsntedg*2 + udindx;// starting 4 sides x 2 directions, 4 bits: 4 sides,
				}	else if(m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ] >31)
				{				m_chnNo[m_fudeNum]++;
								m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ] = 0; 
				}//for edgeChain 32 bits
				MessageBeep(MB_ICONEXCLAMATION); 	//MessageBeep(0);
				m_edgeChain[m_fudeNum][ m_chnNo[m_fudeNum] ] = (m_edgeChain[m_fudeNum][ m_chnNo[m_fudeNum] ]<<1) + 1; // shift up and then add 1 edge to the LSB
				m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ] = m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ] + 1;
//				m_drawImages = TRUE;
				Invalidate(FALSE);
			}
		break;
	// int m_fudeNum;	//Fude(Stroke) Number Max10
	// unsigned int m_edgeChain[10][232]; 232 chains of 32bit edges, MSB:the start, LSB:the last
	// int m_numEdges[10][232]; number of edges(useful Bits) of each m_edgeChain[10][231]; Max 32Bits
	// int m_chnNo[10];	chain Number accounted as first =0, so  Number=m_chnNo +1; Max232 =1850/8
	// str.Format("ChainMax232-32,%2d-%2d-%2d,", m_fudeNum, nchn +1, m_numEdges[10][nchn]);	for(nchn = 0; < m_chnNo[0]+1;) 
		static int indxChn;
		case 'X':	// back stroke , when the cursol is out of the Kolam area, make a negative black/White
			if( !m_drawMode )// !1=0: for KoMaTile mode
			{  			
				if( GetAsyncKeyState(VK_SHIFT) & 0x8000 ) 
				{	//(knap, -97, 0) Cursor in last row except the last corner Koma to delete the row, 
					//(knap, -98, 0)andthen in last column except the last corner to delete the column 
					//(knap, -99, 0) both row and column at the corner KoMa
					if( (knx ==0) || (kny ==0)) break;
					else if( (kny == m_komaNoY-1) & (knx > 0) & (knx < m_komaNoX-1) )  connectDiscon( knap, -97, 0); 
					else if( (knx == m_komaNoX-1) & (kny > 0) & (kny < m_komaNoY-1) )  connectDiscon( knap, -98, 0); 
					else if( (knx == m_komaNoX-1) & (kny == m_komaNoY-1) )			   connectDiscon( knap, -99, 0); 
				} else 
				{ 
				  //m_preKoM[knap] = m_koM[knap];// for Undo //未完　全体のBackUPでないとUndoで他が消える
				  m_koM[knap] = short(0x8000); //=-1; //diagonalも含めないといけないのでUndoはなし
				}
			} else if( m_drawMode )// 1: for edgChain mode 
			{ 
			  // MessageBox(_T("here Key X and Shift+ for initialization"));
			  if( GetAsyncKeyState( VK_SHIFT ) & 0x8000 )
			  {   // set intialization
				memset(m_edgeChain, 0, sizeof(m_edgeChain) ); // intialization
				memset(m_numEdges, 0, sizeof(m_numEdges) ); // intialization
				memset(m_chnNo, 0, sizeof(m_chnNo) ); // intialization
				m_fudeNum = 0;  //the first one
				indxChn = 0; 
			  } else //only Key X
			  {
				if( m_fudeNum == 0 && m_chnNo[m_fudeNum] == 0 && m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ] == 0) 
						break; 	// no-work at 1-1-0 of no stroke
				else 
				{  		 
					if( m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ] > 0) 
					{
						m_edgeChain[m_fudeNum][ m_chnNo[m_fudeNum] ] = m_edgeChain[m_fudeNum][ m_chnNo[m_fudeNum] ]>>1; //shift down 
						m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ]--; 
					} else if( m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ] == 0 )
					{ // m_fudeNumのセット　 
						if( m_chnNo[m_fudeNum] > 0 ) m_chnNo[m_fudeNum]--;
						else if( m_fudeNum > 0 &&  m_chnNo[m_fudeNum] == 0 ) { m_fudeNum--; indxChn--;}
					}
				}// endof if( m_fudeNum,  else if(
			  } // endof if( GetKeyState,  else //only L-Mouse
			} 	// endof  if( m_drawMode )
  			MessageBeep(0);
			Invalidate();//(FALSE)はImageSizeを変更した時　変更前の描画サイズの後が残る
		break;

		case 'Q':	// Q:Break edge-chain and then add one more edge-chain in the same Fude
			if( m_drawMode )
			{	
				if( GetAsyncKeyState( VK_SHIFT ) & 0x8000 )// Key Shift+Q
				{	
					if( indxChn++ == 0)	chnNum = m_chnNo[m_fudeNum]++;
 					for( int nchn = 0; nchn < chnNum; nchn++) // index number of chains 
					{   //coping the edge chains in the same Fude 
						m_edgeChain[m_fudeNum][ m_chnNo[m_fudeNum] +nchn +1] = m_edgeChain[m_fudeNum][ nchn ]; // shift up and then add 1 edge to the LSB
						m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] +nchn +1] = m_numEdges[m_fudeNum][ nchn ];
					}//endof for( int nchn
					m_chnNo[m_fudeNum] = m_chnNo[m_fudeNum] +nchn;  
				} else // only to break chain in the same Fude
				{	
					m_chnNo[m_fudeNum]++; 
				}
				MessageBeep(MB_ICONEXCLAMATION); 	//MessageBeep(0);
				Invalidate(FALSE);
			}//endof if( m_drawMode
		break;

		case 'K':	//２回押す必要がある the first to convert to KoMa and the next to draw the image of KoMa　
			if( m_drawMode ) //convert edgeChain to KoMa-tile type
			{	
				MessageBeep(MB_ICONEXCLAMATION); 	//MessageBeep(0);
				cnvEc2KoMa = 1;
//				m_drawImages = TRUE;
				Invalidate(FALSE);
			}
		break;

		case 'S':	//  twice Key to trace the Hitofude or to set the starting edge chain
					//  reset after stopping 
					// Key Shift to freeze at Hitofude for 6 sec, before KeyIn "S" 
			if( m_drawMode )// 1: edgChain drawing mode 
			{ 
				if( GetAsyncKeyState( VK_SHIFT ) & 0x8000 ) // Key Shift+'S' for copy
				{	// new starting point and Fude number keeping the old edge chains
					m_fudeNum++;
					m_chnNo[m_fudeNum] = m_chnNo[m_fudeNum-1];
					for( int nchn = 0; nchn < m_chnNo[m_fudeNum] +1; nchn++) // index number of chains //to copy the edge chains in the same Fude 
					{	
						m_edgeChain[m_fudeNum][ nchn] = m_edgeChain[m_fudeNum -1][ nchn ]; // shift up and then add 1 edge to the LSB
						m_numEdges[m_fudeNum][ nchn ] = m_numEdges[m_fudeNum -1][ nchn ];

						m_startChainX[m_fudeNum] = knap%m_komaNoX;
						m_startChainY[m_fudeNum] = knap/m_komaNoX;
						int udindx = 1- m_startSide[m_fudeNum]%2;// toggleSwitch LSB:1 CLOCKWISE, 0 UNCLOCK
						m_startSide[m_fudeNum] = prsntedg*2 + udindx; // with the Red edge starting 4 sides x 2 directions, 4 bits: 4 sides,
					}//endof for( int nchn
				} else // only 'S', for draw tracing
				{ 
					if( keyS_M == 0) keyS_M = 1; else { keyS_M = 0;  break; }//if( keyS_M == -1) //to avoid restarting with Stop Key'S'
					if(prsntedg <-1) // mouse out of the area for keeping the file data
					{				 // =starting point of each fude index
						m_startChainX[m_fudeNum] = m_startChainXFile[m_fudeNum];
						m_startChainY[m_fudeNum] = m_startChainYFile[m_fudeNum];
						m_startSide[m_fudeNum]   = m_startSideFile[m_fudeNum];
					} else if(prsntedg == -1){ 	// not mouse edge pointing in the area
						  // only start from same starting point  
				  //} else if(prsntedg == -1 && keyS_M == 1){ 
				  //	keyS_M = 0; 	  break;// avoind to restart from same starting point  
					} else if(prsntedg > -1)// mouse edge pointing
					{	// change starting point  
						m_startChainX[m_fudeNum] = knap%m_komaNoX;
						m_startChainY[m_fudeNum] = knap/m_komaNoX;
						int udindx = 1- m_startSide[m_fudeNum]%2;// toggleSwitch LSB:1 CLOCKWISE, 0 UNCLOCK
						m_startSide[m_fudeNum] = prsntedg*2 + udindx; // with the Red edge starting 4 sides x 2 directions, 4 bits: 4 sides,
					}
					m_slpt = m_wndParam.m_SleepTime *7; //set again after moving mouse and speed adjasting
					getRepeatSequence(); //to get some repeating edgeChain sequences 
					symMetry();	// check the symmetry 
				} //endof if( GetAsyncKeyState
			} else if( m_drawMode == 0)// KoMa drawing Mode,
			{	 
				if( GetAsyncKeyState( VK_SHIFT ) & 0x8000 ) shftky = 1; // waiting some minutes intermission 
				if( m_koM[knap] <1 || prsntedg <= -99) break; // out of the edge area
				else if( fnlimg == 1 ) 
				{	//2009/11/28 reset of keeping finalline image at trce = 3
					fnlimg = 0; prsntedg = -1;  
				} 
				else 
				{	// starting the connection edge point of Koma m_koM[knap]
					if( keyS_M == 0) keyS_M = 1; else {	keyS_M = 0;   break; } //if( keyS_M == -1) // to avoid restarting with Stop Key'S'
//2011/03/14 removed	m_slpt = m_wndParam.m_SleepTime; //set again after moving mouse
					while(TRUE)	// set strtedg: the starting point,	
					{	// LSB, 1:Up crossing & turns clockwise red(?)-color 0:Down & counterclockwise green(?)-color
						strtedg ++; if(strtedg > 7) strtedg = 0; //alternately direction and then change side
						if( ((m_koM[knap]>>strtedg/2) &1) || ((m_koM[knap]>>(4+strtedg/2)) &1) )// m_koM[knap]の接続がある接続点で一筆開始する
						{
							prsntedg = strtedg/2;
//							drwNln = 0; 
							trce = 1; // index of tracing hitofude
							break; 
						} 
					}//endof while  
				}  //endof if( m_koM[knap] >0
			} //endof if( m_drawmode else
			drwNln = 0; // offset N-lines 
			Invalidate(FALSE);
		break;

//		static int Lb, Bknap;
		int kkm;
		case 'N': // make a line or matrix of connecting Komas showing N-lines,
			     //  first KeyIn to set beginning KoMa and second KeyIn ending KoMa  
				if(Lb == 0) // the first N-keyIn
				{	
					MessageBeep(MB_ICONEXCLAMATION); 	//MessageBeep(0);
					Lb = 1;	drwNln = 2; // to draw green dot in this KoMa by Key N
					LMbX = LMeX = knap%m_komaNoX;  	// begining KoMa in N-line
					LMbY = LMeY = knap/m_komaNoX;
					Bknap = knap;		
//					m_drawImages = TRUE;
					Invalidate(FALSE);
					break;			
				} else if(Lb == 1) // the second N-KeyIn
				{		
					MessageBeep(MB_ICONASTERISK);
					Lb = 0;	
					for( ikb = 0; ikb < m_komaNoX*m_komaNoY; ikb++) m_preKoM[ikb] = m_koM[ikb];// for Undo
					LMeX = knap%m_komaNoX; // ending KoMa in N-line
					LMeY = knap/m_komaNoX;
					if( LMeX < LMbX)
					{  
						int LMeXb = LMeX;  LMeX = LMbX; LMbX = LMeXb; Bknap = knap;  
					}	
					if( LMeY < LMbY)
					{  
						int LMeYb = LMeY;  LMeY = LMbY; LMbY = LMeYb; Bknap = knap;  
					}
					if( LMeY == LMbY)
					{	
						if( LMeX == LMbX) break; //Key'N'を同じところ		
						kkm = Bknap; 
						if( m_koM[kkm] < 0) m_koM[kkm] = 0; // change "-X" KoMa to "0" 
						else if(  m_koM[kkm] >15) m_koM[kkm] = m_koM[kkm] & (short)~(1<<4); 
						m_koM[kkm] = m_koM[kkm] | 1; // get LSB
						kkm++;
						for( int i =LMbX +1; i <LMeX; i++, kkm++)
						{
							if( m_koM[kkm] <0) m_koM[kkm] =0; // change "-X" KoMa to "0" 
							else if(  m_koM[kkm] >15) m_koM[kkm] = m_koM[kkm] & (short)~(5<<4); 
							m_koM[kkm] = m_koM[kkm] | 5;
						}
						if( m_koM[kkm] <0) m_koM[kkm] =0; // change "-X" KoMa to "0" 
						else if(  m_koM[kkm] >15) m_koM[kkm] = m_koM[kkm] & (short)~(4<<4); 
						m_koM[kkm] = m_koM[kkm] | 4;
					} else	if( LMeX == LMbX)
					{
						kkm =Bknap; 
						if( m_koM[kkm] < 0) m_koM[kkm] = 0; // change "-X" KoMa to "0" 
						else if(  m_koM[kkm] >15) m_koM[kkm] = m_koM[kkm] & (short)~(2<<4); 
						m_koM[kkm] = m_koM[kkm] | 2; 
						for( int i =LMbY +1; i <LMeY; i++)
						{
							kkm = m_komaNoX *i + LMeX;
							if( m_koM[kkm] <0) m_koM[kkm] =0; // change "-X" KoMa to "0" 
							else if(  m_koM[kkm] >15) m_koM[kkm] = m_koM[kkm] & (short)~(10<<4); 
							m_koM[kkm] = m_koM[kkm] | 10;
						}
						kkm = m_komaNoX *i + LMeX;
						if( m_koM[kkm] <0) m_koM[kkm] =0; // change "-X" KoMa to "0" 
						else if(  m_koM[kkm] >15) m_koM[kkm] = m_koM[kkm] & (short)~(8<<4); 
						m_koM[kkm] = m_koM[kkm] | 8;
					} else	//if( LMeX > LMbX) or if( LMeY > LMbY) 
					{		// Matrix connection　
						for( int ixy = LMbY; ixy < LMeY + 1; ixy++) 
						{				// Y行をつなぐ LMeY == LMbY
							for( int i = LMbX; i < LMeX + 1; i++)
							{	
								kkm = m_komaNoX *ixy + i;
								m_koM[kkm] = 15;
								//m_koM[kkm] = makeKoma( kkm, 0, 1);m_koM[kkm] = makeKoma( kkm, 1, 1);
								//m_koM[kkm] = makeKoma( kkm, 2, 1);m_koM[kkm] = makeKoma( kkm, 3, 1);
								// return fuction = makeKoma( int KoMa number, int edge, short edgestatus)	
								// edge number 0:right,1:bottom,2:left,3:top
							}
						}
						//reArrang(1);// connect between KoMa at both egdes 1 or 2 status
						reArrang(0); // change no-connected edge"1" to "0" in KoMa  
					}
//					m_drawImages = TRUE;
					Invalidate(FALSE);
				}//endof if(Lb == 0){} else 
		break;
		case 'B': //  to set KoMa Editting Block area,  

/*			if( m_drawMode )// move to case 'Q'  from here, 1: edgChain drawing mode Break edge-chain 
			{	
				if( GetAsyncKeyState( VK_SHIFT ) & 0x8000 )// Key Shift+B, add one more edge-chain in the same Fude and move the starting point
				{	
					if( indxChn++ == 0)	chnNum = m_chnNo[m_fudeNum]++;
 					for( int nchn = 0; nchn < chnNum; nchn++)  // index number of chains
					{  //coping the edge chains in the same Fude 
						m_edgeChain[m_fudeNum][ m_chnNo[m_fudeNum] +nchn +1] = m_edgeChain[m_fudeNum][ nchn ]; // shift up and then add 1 edge to the LSB
						m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] +nchn +1] = m_numEdges[m_fudeNum][ nchn ];
					}
					m_chnNo[m_fudeNum] = m_chnNo[m_fudeNum] +nchn;  
				} else      // move the starting point
				{	
					m_chnNo[m_fudeNum]++; 
				}
				MessageBeep(MB_ICONEXCLAMATION); 	//MessageBeep(0);
				Invalidate(FALSE);
			}//endof if( m_drawMode
			else 
*/			
			if( m_drawMode == 0) // Koma Mode
			{				//  first KeyIn to set beginning KoMa as the diagonal and second KeyIn ending KoMa 
				if(Lb == 0) // the first B-keyIn
				{	
//MessageBox(_T("here first B-keyIn"));					
					Lb = 1;	
					drwNln = 2; // to draw green dot in this KoMa by Key B
					MessageBeep(MB_ICONEXCLAMATION); 	//MessageBeep(0);
					LMbX = LMeX = knap%m_komaNoX;  	// begining KoMa in N-line
					LMbY = LMeY = knap/m_komaNoX;
//					Bknap = knap;
//					m_drawImages = TRUE;
					Invalidate(FALSE);
					break;			
				} else if(Lb == 1) // the second B-KeyIn
				{		
//MessageBox(_T("here second B-KeyIn"));					
					Lb = 0;	
					areaSet = 1; // index for edit Pasting using MouseL 
					MessageBeep(MB_ICONASTERISK);
					LMeX = knap%m_komaNoX; // ending KoMa in N-line
					LMeY = knap/m_komaNoX;
					if( LMeX < LMbX)
					{  
						int LMeXb = LMeX;  LMeX = LMbX; LMbX = LMeXb; Bknap = knap;  
					}	
					if( LMeY < LMbY)
					{  
						int LMeYb = LMeY;  LMeY = LMbY; LMbY = LMeYb; Bknap = knap;  
					}
					copyArea();
//					m_drawImages = TRUE;
					Invalidate(FALSE);
				}//endof if(Lb == 0){} else 
			}//endof if( m_drawMode  
		break;
		case 'R': // re-arrangement for changing Kolam-type  
			if( drwNln == 2) break; //avoid double operation in Menu-OnEditRotate 
			MessageBeep(MB_ICONEXCLAMATION); 	//MessageBeep(0);
			for( ikb = 0; ikb < m_komaNoX*m_komaNoY; ikb++) m_preKoM[ikb] = m_koM[ikb];// for Undo
			if( GetAsyncKeyState( VK_SHIFT ) & 0x8000 ) reArrang(-1);// change Tear(Drop) type to Zero with Shift+'R'
			reArrang(1);// connect between KoMa at both egdes  1 or 2 status
			reArrang(0); // change no-connected edge"1" to "0" in KoMa  
			drwNln = 1; // set N-lines and keep the assigned area 
//			m_drawImages = TRUE;
			Invalidate(FALSE);
		break;
		case 'A':	// toggle switch to connect/twopoint connect/disconnect between KolamTiles assinged with the cursor 
					// connections of which were not used  
			if( fnlimg == 1 ) 
			{	//2009/11/28 reset of keeping finalline image at trce = 3
					fnlimg = 0; prsntedg = -1;  Invalidate(FALSE); break;
			} 
			for( ikb = 0; ikb < m_komaNoX*m_komaNoY; ikb++) m_preKoM[ikb] = m_koM[ikb];// for Undo
			// change the edge status to 1:crossing, 0:turning in a tile, 2:opposite turning
			short int stts;
			stts = (m_koM[knap]>>prsntedg)%2 + ( m_koM[knap]>>(4+prsntedg) )%2 *2;
			if( stts <2) stts++; else stts = 0;  
			connectDiscon( knap, prsntedg, stts); // 0,1,2 edge status,  // old -1: toggle of connect/discon with a cursol
			drwNln = 1; // set N-lines 
//			m_drawImages = TRUE;
 			Invalidate(FALSE);
		break;

		case 'W':	//  2011/05/01 after tracing another(addtional) loop, then KeyW to set the loop(Wa in Japanese)  
			//　未完　カーソルが(なんの？）領域のとき　避ける
//			if(prsntedg == -1){ break; } // not mouse edge pointing in the area
			if( GetAsyncKeyState( VK_SHIFT ) & 0x8000 )
			{  
				if(m_loopNum > 0) 
				{ 
					m_loopNum--;  MessageBeep(MB_ICONEXCLAMATION); //delete the last Loop 
					m_wstr.Format("the last was removed, then now LoopNumber=%3d", m_loopNum); 
				}
			} else  
			{		//static int m_loopNum;	// loop(Wa) Number Max10: [0,1,2....m_loopNum -1] 
				if(m_loopNum < 10) // max10,// この時点以前で追加の一筆を描画しておく
				{ 
				 //fnlimg = 0;     // いずれにしても　赤マーカを得るには前のLoopsは消える
				 //m_loopNum++;    // counting from 1 to Max10 
//				 m_strtKoma[m_loopNum -1] = knap;  // starting KoMa of each loop
//				 m_strtSide[m_loopNum -1] = strtedg; // common starting edge of starting KoMa of each loop
//				 m_loopColor[m_loopNum -1] = m_wndParam.m_BtnFColor.GetColor();	// m_fnlColor =選択されたloopfinal色
//				 m_wstr.Format("another loop of the point and finalColor\n loopNum=%3d strtKoma=%3d strtSide=%2d\n colorR=%3d colorG=%3d colorB=%3d",
//					m_loopNum, m_strtKoma[m_loopNum-1], m_strtSide[m_loopNum-1], 
//					GetRValue(m_loopColor[m_loopNum-1]), GetGValue(m_loopColor[m_loopNum-1]), GetBValue(m_loopColor[m_loopNum-1]) ); 
				 m_strtKoma[m_loopNum] = knap;  // starting KoMa of each loop
				 m_strtSide[m_loopNum] = strtedg; // common starting edge of starting KoMa of each loop
				 m_loopColor[m_loopNum] = m_wndParam.m_BtnFColor.GetColor();	// m_fnlColor =選択されたloopfinal色
				 m_wstr.Format("another loop of the point and finalColor\n loopNum=%3d strtKoma=%3d strtSide=%2d\n colorR=%3d colorG=%3d colorB=%3d",
					m_loopNum +1, m_strtKoma[m_loopNum], m_strtSide[m_loopNum], 
					GetRValue(m_loopColor[m_loopNum]), GetGValue(m_loopColor[m_loopNum]), GetBValue(m_loopColor[m_loopNum]) ); 
				 m_loopNum++;    // counting from 1 to Max10 
//				 MessageBox(_T(m_wstr));
				} else
				{
				 //memset(wstr,'\0',100); //wstrの初期化 int val = 2008;
				 //_itoa(val,wstr,10);//10進法	// 変換関数 atoi ←→_itoa,or sprintf(str, "%d", val);
				 m_wstr.Format("the last loop is over Max10, Shift+W to delete it"); 
				}
			}
			MessageBox(_T(m_wstr)); 	
	        Invalidate(FALSE);
		break;
    }//endof switch (
	CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}// endof void CChildView::OnKeyUp

//映像を保存 save an image to a jpg file in "KolamImages" holder
// static int ii = 0; // file number of serial images
// not work why ??
void CChildView::saveImage(int iik)
{  
			MessageBeep(MB_ICONEXCLAMATION); 	//MessageBeep(0);
			CMemDC memDC;
			m_imageD_F_Name.Format("KolamImages\\%s-%03d.jpg", m_strFileTitle,iik); 
			memDC.SaveJPEG(m_imageD_F_Name);	//saveImage(iik);
}	//endof CChildView::saveImage
//*/

/*
OnMouseMove なり何なりで、随時最新の座標を保存しておく、
任意のタイミングで GetCursorPos する等の方法が考えられます。
afx_msg void OnMouseMove( UINT nFlags, CPoint point );
引数:nFlags:どの種類の仮想キーが押されているかを示します 
MK_CONTROL   Ctrl キーが押されている場合にセットします。
MK_LBUTTON   マウスの左ボタンが押されている場合にセットします。
MK_MBUTTON   マウスの中央ボタンが押されている場合にセットします。
MK_RBUTTON   マウスの右ボタンが押されている場合にセットします。
MK_SHIFT   Shift キーが押されている場合にセットします。 
point:カーソルの x 座標と y 座標を指定します。座標は、常にウィンドウの左上隅からの相対位置になります。
解説: マウス カーソルが移動すると、フレームワークからこのメンバ関数が呼び出されます。マウス キャプチャがない場合は、マウス カーソルのある CWnd オブジェクトが WM_MOUSEMOVE メッセージを受け取ります。それ以外では、メッセージはマウス キャプチャのあるウィンドウに送られます。
メモ: このメンバ関数は、アプリケーションが Windows メッセージを処理できるようにするためにフレームワークにより呼び出されます。引数には、フレームワークが受け取ったメッセージの引数が反映されています。この関数の基本クラスのインプリメントを呼び出すと、そのインプリメントは、この関数に渡した引数ではなく、メッセージと共に渡したオリジナルの引数を使用します。
*/
static short csrx, csry; 
static short offstx = 23, offsty = 20; // offset the position of points from Windows axis
static short centxb, centyb, prvedge; //  the center and edge of the previous pointed koma	
static short knapb;	
	//CString str;			// for dc.Texout
    //CClientDC dc(this);	// for dc.Texout
	//str.Format("Now coursol in the corner of Koma as the cursor position x=%2d y=%2d", csrx, csry);
	//dc.TextOut( 0, 12, str); 
 
void CChildView::OnMouseMove( UINT nFlags, CPoint point )
{
	// TODO: Add your message handler code here
	if( !m_alledge && bAutog) return; //m_alledge == 0, bAutog  == TRUE, pass here at autogenerating 
	if( fnlimg )  return; // //== 1, 2009/11/28 to keep the finallineimage after just trace  
	
	csrx = (short)point.x; // present position in X
	csry = (short)point.y; // present position in Y
	short knx = knap%m_komaNoX;	//koma position number in X-axis
	short kny = knap/m_komaNoX;	//koma position number in Y-axis
	short centx = (int)(m_kks*(0.5+knx)) + offstx;
	short centy = (int)(m_kks*(0.5+kny)) + offsty;

//	 if( csrx > offstx*1.5 + m_kks*m_komaNoX || csry > offsty*1.5 + m_kks*m_komaNoY)
//	 2009/10/20 このOutOfWindowにすると	左下へのEdgeカーソルが出る
// 　cursor out of the tile area Koma ground 下と右限界内活かす
	if( csrx >= offstx + m_kks*m_komaNoX || csry >= offsty + m_kks*m_komaNoY)
	{		    
		prvedge = prsntedg;  prsntedg = -100; // no pointing, for writing Chain Data
		if( prsntedg != prvedge ) //refresh the new image
		{ 
			Invalidate(FALSE);
		}
		return;
//	} else if( csrx < offstx + m_kks/4 || csry < offsty + m_kks/4 )
	} else if( csrx < offstx || csry < offsty )//2011/9/01 Ver.4.5.1 Diagonal point のため
	{	//  cursor out of left and top side of Koma ground　　上と左も活かす
		prvedge = prsntedg;  prsntedg = -99; //no pointing, cursor out Koma ground
		if( prsntedg != prvedge ) //refresh the new image
		{ 
			Invalidate(FALSE);
		}
		return;
	} else	if( csrx > (centxb + m_kks/2) || csrx < (centxb - m_kks/2) )
	{ 		// x posion into the new neighbor koma, right || left side   
		centxb = centx; centyb = centy; knapb = knap; 
		knap = (csrx - offstx)/m_kks +( (csry -offsty)/m_kks )*m_komaNoX; // new koma number
 		prvedge = prsntedg; 
 		if( knapb != knap )
		{
			if( prvedge == 0)		prsntedg =2; //now Just on the edge line, previous edge is drawn why ? 
 			else if( prvedge == 2)	prsntedg =0;
			Invalidate(FALSE);
		}
		return;
	} else if( csry > (centyb + m_kks/2) || csry < (centyb - m_kks/2) )
	{		// y posion into the new neighbor koma, down || upper side 
		centxb = centx; centyb = centy; knapb = knap;
		knap = (csrx - offstx)/m_kks +( (csry -offsty)/m_kks )*m_komaNoX; // new koma number
		prvedge = prsntedg;  
 		if( knapb != knap )
		{
			if( prvedge == 1)		prsntedg =3;
			else if( prvedge == 3)	prsntedg =1;
			Invalidate(FALSE);
		}
		return;
	} else	if( csrx > centxb + m_kks*0.25 && csrx < centxb + m_kks*0.75 && csry > centyb + m_kks*0.25 && csry < centyb + m_kks*0.75 )
	{	// right/bottom vertex corner area for two point connecting in ChainMode and DiagomalLoop 
		prvedge = prsntedg;  prsntedg = 10; //arcln = -1; cursor in the right/bottom corner area 
		if( prsntedg != prvedge ) Invalidate(FALSE);//refresh the new image
		return;
	} else	if( csrx > centxb - m_kks*0.75 && csrx < centxb - m_kks*0.25 && csry > centyb + m_kks*0.25 && csry < centyb + m_kks*0.75 )
	{	// left/bottom vertex corner area for DiagonalLoop Ver.4.5.1
		prvedge = prsntedg;  prsntedg = 11; //arcln = -1; cursor in the left/bottom corner area 
		if( prsntedg != prvedge )  Invalidate(FALSE);//refresh the new image
		return;
	} else	if( csrx > centxb - m_kks*0.75 && csrx < centxb - m_kks*0.25 && csry > centyb - m_kks*0.75 && csry < centyb - m_kks*0.25 )
	{	// left/top vertex corner area for DiagonalLoop Ver.4.5.1
		prvedge = prsntedg;  prsntedg = 12; //arcln = -1; cursor in the left/top corner area 
		if( prsntedg != prvedge ) Invalidate(FALSE);//refresh the new image
		return;
	} else	if( csrx > centxb + m_kks*0.25 && csrx < centxb + m_kks*0.75 && csry > centyb - m_kks*0.75 && csry < centyb - m_kks*0.25 )
	{	// right/top vertex corner area for DiagonalLoop Ver.4.5.1
		prvedge = prsntedg;  prsntedg = 13; //arcln = -1; cursor in the right/top  corner area 
		if( prsntedg != prvedge ) Invalidate(FALSE);//refresh the new image
		return;
//	} else	if( csrx > centx -m_kks*0.25 && csrx < centx +m_kks*0.25 && csry > centy -m_kks*0.25 && csry < centy +m_kks*0.25 )
	} else	if( csrx > centx -m_kks*0.15 && csrx < centx +m_kks*0.15 && csry > centy -m_kks*0.15 && csry < centy +m_kks*0.15 )
//	} else	if( csrx > centx -m_kks*0.1 && csrx < centx +m_kks*0.1 && csry > centy -m_kks*0.1 && csry < centy +m_kks*0.1 )
	{	// around the pulli to sart tracing in KoMa mode//　点の周りのみでスタートさせる　2011/09/10 ver.4.5.1
		// さらに狭く点のまわりに  m_kks*0.3では広すぎ　m_kks*0.15が良いか　m_kks*0.1狭すぎ　
		//  但し、その場合　Default値　prsntedg = -1 がStart条件になっているので変更= -2;
//		centxb = centx; centyb = centy; knapb = knap;
		prvedge = prsntedg;  //  2011/03/02 around the pulli to sart tracing
		if( m_drawMode ) prsntedg = -1; else prsntedg = -2; //0:CainMode のときは変更なし
//		if( prsntedg != prvedge ) //refresh the new image
		{ 
			Invalidate(FALSE);
		}
		return;
	} else  // in the other area,  check the cursor position on an edge ?
	{	
		prvedge = prsntedg;  prsntedg = -1; // not in edge area, but the next status
		short cri2 = cri/2; // cri = circle radius of the arc	
 		short cntxcr = centxb +cri; int cntycr = centyb +cri; //int cntxcr = centx +cri2; int cntycr = centy +cri2; 
 		short cntxcn = centxb -cri; int cntycn = centyb -cri; //int cntxcn = centx -cri2; int cntycn = centy -cri2; 
		if( csry < cntycr && csry > cntycn)//left or right edge
		{ 
			if( csrx > cntxcr && csrx < (centxb +m_kks) - cri2)			prsntedg = 0; //right edge of koma[knap]
			else if( csrx < cntxcn && csrx > (centxb -m_kks) + cri2)	prsntedg = 2; //left edge of koma[knap]
		} else if( csrx < cntxcr && csrx > cntxcn)// bottom or top edge
		{ 
			if( csry > cntycr && csry < (centyb +m_kks) - cri2)			prsntedg = 1; // bottom edge of koma[knap]
			else if( csry < cntycn && csry > (centyb -m_kks) + cri2)	prsntedg = 3; // top edge of koma[knap]
		} 
		if( prsntedg != prvedge ) //refresh the new image
		{ 
			Invalidate(FALSE);
		}
		return;
	}   
	//CWnd::OnMouseMove( nFlags, point );	//在ってもなくてもOK,なんの役割するか？未勉強
}// endof void CChildView::OnMouseMove

void CChildView::OnLButtonUp( UINT nFlags, CPoint point )
{
	// TODO: Add your message handler code here and/or call default
	short knxap = knap%m_komaNoX;
	short knyap = knap/m_komaNoX;

	if( m_drawMode )//	1: edgChain drawing mode 
	{	
		if( fnlimg ) //== 1  // reset keeping finalimage
		{	
			fnlimg = 0; prsntedg = -1;
			Invalidate(FALSE);
			return;
		} else if( csrx > m_imageSiH || csry > m_imageSiV){ return; //cursor out of drawing Image  area   
		
		} else if( csrx > offstx + m_kks*m_komaNoX || csry > offsty + m_kks*m_komaNoY)   
		{	//cursor of KoMa area but in drawing Image area
//	     	if( m_fudeNum == 0 && m_chnNo[0] == 0 && m_numEdges[0][0] == 0) 
//			if( m_fudeNum < 0 ) //どうしてか　これでは　音がする
	     	if( m_numEdges[0][0] == 0) 
			{		return; // no-work at 1-1-0 of no chainData
			} else // deleting at the cursor out as the same function as Key'Z' // Copy from Keyup'Z'
			{ 
				if( m_numEdges[m_fudeNum][m_chnNo[m_fudeNum]] > 0) 
				{
					m_edgeChain[m_fudeNum][m_chnNo[m_fudeNum]] = m_edgeChain[m_fudeNum][m_chnNo[m_fudeNum]]>>1; //shift down 
					m_numEdges[m_fudeNum][m_chnNo[m_fudeNum]]--;
				}
				//ver.4.4.5に戻した　これでFudeを第一Dataを交点か円弧かを選択できる　Startとは現行赤KoMa
				else if( m_numEdges[m_fudeNum][m_chnNo[m_fudeNum]] == 0 )
				{	// m_fudeNumのセット 
					if( m_chnNo[m_fudeNum] > 0 ) m_chnNo[m_fudeNum]--;
					else if( m_fudeNum > 0 && m_chnNo[m_fudeNum] == 0 ) m_fudeNum--; //{m_fudeNum--; indxChn--;}
				}
			}// endof if( m_fudeNum,  else if(
			MessageBeep(0);
			Invalidate(FALSE);
			return;
		} else if(prsntedg <10 && m_numEdges[m_fudeNum][0] == 0) //丁度ChainDataが０の場合
		{ //　完　　円と円弧の交互で初期値化されるのを防いだ
			// set the starting when no edge-chain // cursor in the area  
			m_startChainXY[m_fudeNum] = knap;
			short udindx = 1- m_startSide[m_fudeNum]&1; //toggleSwitch LSB:1 CLOCKWISE, 0 UNCLOCK
			if(prsntedg == -1)// add a chain code 0 
			{	
				m_startSide[m_fudeNum] = udindx; // with the Red edge starting 4 sides x 2 directions, 4 bits: 4 sides,
				m_edgeChain[m_fudeNum][m_chnNo[m_fudeNum]] =  m_edgeChain[m_fudeNum][m_chnNo[m_fudeNum]]<<1; // shift up to add 0 edge to LSB
			} else if( prsntedg > -1 && prsntedg <4)// On Edge to add a chain code 1 
			{
				m_startSide[m_fudeNum] = prsntedg*2 + udindx; // with the Red edge starting 4 sides x 2 directions, 4 bits: 4 sides,
				m_edgeChain[m_fudeNum][m_chnNo[m_fudeNum]] = (m_edgeChain[m_fudeNum][m_chnNo[m_fudeNum]]<<1) + 1; // shift up and then add 1 edge to LSB
			} // then increase/increment the number of the chain code  
			m_numEdges[m_fudeNum][m_chnNo[m_fudeNum]] = m_numEdges[m_fudeNum][m_chnNo[m_fudeNum]] + 1;
			MessageBeep(0);
			Invalidate(FALSE);
			return;
		} else if( m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ] == 0) 
		{		// set the starting when no edge-chain // cursol in the area  
			m_startChainX[m_fudeNum] = knap%m_komaNoX;
			m_startChainY[m_fudeNum] = knap/m_komaNoX;
			int udindx = 1- m_startSide[m_fudeNum]&1; //  toggleSwitch LSB:1 CLOCKWISE, 0 UNCLOCK
			if(prsntedg <0)	m_startSide[m_fudeNum] = udindx;
			else			m_startSide[m_fudeNum] = prsntedg*2 + udindx; // with the Red edge starting 4 sides x 2 directions, 4 bits: 4 sides,
		} else if(m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ] >31) 
		{	//for edgeChain 32 bits
			m_chnNo[m_fudeNum]++;	
			m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ] = 0; 
		} else if( m_numEdges[m_fudeNum][ m_chnNo[0] ] != 0 && knap == m_startChainY[m_fudeNum]*m_komaNoX +m_startChainX[m_fudeNum] )
		{		//cursol in the green dot starting Koma
			if( keyS_M == 0) keyS_M = 1; else { keyS_M = 0;  return; } //  to starting trace

			int udindx = 1- m_startSide[m_fudeNum]&1;// toggleSwitch LSB:1 CLOCKWISE, 0 UNCLOCK
			if(prsntedg == -1){ 	// 未完　この処理を上のIf(に入れる　not mouse edge pointing in the area
									// only start from same starting point  
			} else	m_startSide[m_fudeNum] = prsntedg*2 + udindx;// with the Red edge starting 4 sides x 2 directions, 4 bits: 4 sides,
			
			m_slpt = m_wndParam.m_SleepTime *7; //set again after moving mouse and speed adjasting
			getRepeatSequence(); //to get some repeating edgeChain sequences 
			symMetry();
			MessageBeep(MB_ICONEXCLAMATION); 	//MessageBeep(0);
			Invalidate(FALSE);
			return; 
		// add an other Arc or line chain 
		//} else if( prsntedg == 10 ) {} // 未完　two point connecting at vertec area 	
		} else if( prsntedg == -1 )//mouse pointing not on edge, and not if( knap == m_startChainXY[ 
		{	// add a chain code 0 // increase/increment the number of the chain code  
			if(m_numEdges[m_fudeNum][m_chnNo[m_fudeNum]] >31) 
			{	//for edgeChain 32 bits
				m_chnNo[m_fudeNum]++;	
				m_numEdges[m_fudeNum][m_chnNo[m_fudeNum]] = 0; //初期値０ m_numEdgesが31とは32bit目埋まった
			} 
			m_edgeChain[m_fudeNum][m_chnNo[m_fudeNum]] =  m_edgeChain[m_fudeNum][m_chnNo[m_fudeNum]]<<1; // shift up to add 0 edge to LSB
			m_numEdges[m_fudeNum][m_chnNo[m_fudeNum]] = m_numEdges[m_fudeNum][m_chnNo[m_fudeNum]] + 1;
			MessageBeep(0); 
			Invalidate(FALSE);
			return;
		} else if(prsntedg > -1 && prsntedg < 4)// mouse edge pointing
		{   // add a chain code 1 
			if(m_numEdges[m_fudeNum][m_chnNo[m_fudeNum]] >31) 
			{	//for edgeChain 32 bits
				m_chnNo[m_fudeNum]++;	
				m_numEdges[m_fudeNum][m_chnNo[m_fudeNum]] = 0; //初期値０ m_numEdgesが31とは32bit目埋まった
			} 
			m_edgeChain[m_fudeNum][m_chnNo[m_fudeNum]] = (m_edgeChain[m_fudeNum][m_chnNo[m_fudeNum]]<<1) + 1; // shift up and then add 1 edge to LSB
			m_numEdges[m_fudeNum][m_chnNo[m_fudeNum]] = m_numEdges[m_fudeNum][m_chnNo[m_fudeNum]] + 1;
			MessageBeep(0); 
			Invalidate(FALSE);
			return;
		}  
	} else  if( !m_drawMode ) //== 0, KoMa drawing mode 
	{ 
		if( csrx > offstx + m_kks*m_komaNoX || csry > offsty + m_kks*m_komaNoY)  return; //cursor out of the window 
		else if( fnlimg ) //== 1  
		{	//2009/11/28 reset of keeping finalline image at trce = 3
			fnlimg = 0; prsntedg = -1; bAutog = FALSE; //keep to re-sart with no MouseMove
			Invalidate(FALSE);
			return;
		} else if(Lb == 9 && areaSet == 0) // set  begining BlockArea using Mouse_L 
		{	
			Lb = 10;	//
			drwNln = 2; //draw N-Line and assigned area with greenDot
			LMeX = LMbX  = knxap; //= knap%m_komaNoX;  	//= LMeX begining KoMa in N-line
			LMeY = LMbY  = knyap; //= knap/m_komaNoX; = LMeY

		} else if(Lb == 10 && areaSet == 0) // set ending BlockArea
		{					
			LMeX = knxap; //= knap%m_komaNoX;  ending KoMa in N-line
			LMeY = knyap; //= knap/m_komaNoX;
			copyArea();
			Lb = 9;	
			areaSet = 1; // index for edit Pasting using Mouse_L 
			MessageBeep(MB_ICONEXCLAMATION);
			Invalidate(FALSE);
		} else if(Lb == 9 && areaSet == 1) // past using Mouse_L 
		{	
			// 未完　配列が描画域を超えた場合　onEditPaste参照
			for( short ikb = 0; ikb < m_komaNoX*m_komaNoY; ikb++) m_preKoM[ikb] = m_koM[ikb];// for Undo

			for( short knx = LMbX; knx < (LMeX +1); knx++)	
			for( short kny = LMbY; kny < (LMeY +1); kny++)	//m_koMxy[50][37];
			{
				short knapp = (knxap + knx -LMbX) +(knyap + kny -LMbY)*m_komaNoX;
				m_koM[knapp] = m_koMxy[knx][kny];
			}
			areaSet = 0; // index for end of Edit Pasting using MouseL 
			Invalidate();//new Image
			//未完　DiagonalKoMaのPaste　
		} else if( m_koM[knap] < 0 && prsntedg < 0 ){ return; //  no connection KoMa  
		} else if( m_koM[knap] == 0 && prsntedg < 0){ m_koM[knap] = (short)0x8000; //delete 0 KoMa  
		} else if( prsntedg > -1 && prsntedg < 5 ) // connect/disconnect/turn-connect the edge of KoMa at a cursor
		{	
			for( short ikb = 0; ikb < m_komaNoX*m_komaNoY; ikb++) m_preKoM[ikb] = m_koM[ikb];// for Undo
			// change the edge status to 1:crossing, 0:turning in a tile, 2:opposite turning
			short stts = (m_koM[knap]>>prsntedg)%2 + ( m_koM[knap]>>(4+prsntedg) )%2 *2;
			if( stts <2) stts++; else stts = 0;  
			connectDiscon( knap, prsntedg, stts); // 0,1,2 edge status, // old  -1: toggle of connect/discon with a cursor
			drwNln = 1; // set N-lines 
			Invalidate(FALSE);
		} else if(prsntedg > 9 && prsntedg <14)// Cursor at diagonal vertex
		{								
		} else if( m_koM[knap] > 0 && (prsntedg == -2 || prvedge == -2))  //2011/03/02 点の周りに指定
		{								
				//MessageBeep(MB_ICONEXCLAMATION);
				if( !keyS_M ) keyS_M = 1; else { keyS_M = 0; return; } //== 0
				m_slpt = m_wndParam.m_SleepTime; //set again after moving mouse
				while(TRUE)// strtedg: starting point; MSB 2 bits:4 sides 
				{	// LSB, 1:Up crossing & turns clockwise red-color 0:Down & counterclockwise green-color
					strtedg++; if(strtedg > 7) strtedg = 0; //alternately direction and then change side
					if( ((m_koM[knap]>>strtedg/2) &1) || ((m_koM[knap]>>(4+strtedg/2)) &1) )// m_koM[knap]の接続があるかの判定、接続点で一筆開始する
					{ 
						prsntedg = strtedg/2;
						drwNln = 0; // offset N-lines 
						trce = 1;	
						break; // index of tracing hitofude
					}
				} //endof while  
				Invalidate(FALSE);
		} //endof if( m_koM[
		//Invalidate();	//(FALSE)はImageSizeを変更した時　変更前の描画サイズの後が残る
	}// endof if if( m_drawMode 
}//end of CChildView::OnLButtonUp

static double repCoeff[3]; // to use in repeatSequence()
static int	repLength[3]; // to use in repeatSequence()
static int	suNo; //Number of All Edges

bool edges[7400];	//  Max X50 xY37 KoMA x4 Edges =7400bits

double CChildView::autoCorr(bool *edg, int suN, int sftL)
{
	double aC;
	bool lgcA, lgcB, *ei; 
	int sum = 0, ie;
	for( ie = 0, ei = edg; ie< suN; ie++, ei++) 
	{ 
		lgcA = *ei;	
		if(ie +sftL < suN )	lgcB = *(ei +sftL);	
		else				lgcB = *(ei +sftL -suN); //if(i +sftL >= suN )	over Number of Edges in the Chain
		sum += !(lgcA ^ lgcB);	//lgcA == lgcB? 1:0;  NOT(XOR(lgcA,lgcB)) get the same bit
	}//endof for( int i
	aC =  (double)sum/(double)(suN);
	return aC;
}//endof void CChildView::autoCorrelation

void CChildView::getRepeatSequence()
{ 
	// to get the largest autoCoEfficency 5 sequences and their shiftL=length
	bool edges[7400];	//  X50 KoMa xY37 KoMA x4 Edges =7400bits
 	memset( edges, 0, sizeof(edges) ); // intialization

	suNo = 0;		// index number of all edges 
	for ( int nchn =0; nchn < m_chnNo[m_fudeNum] +1; nchn++)
		for (int nmch = m_numEdges[m_fudeNum][nchn] - 1; nmch > -1; nmch--)
		{ 
			edges[suNo] = (m_edgeChain[m_fudeNum][nchn] >>nmch) & 1;	// pick up the LSB
					//str += edge[suNo]? "1" : "0"; //for print to check
			suNo++;
		}//endof for ( int nmch 

	for( int ir=0; ir<3; ir++) { repCoeff[ir]= 0; repLength[ir]= suNo; } // intialization

	for( int sl =1; sl < suNo; sl++)// sl: for shift phase or length
	{ 
		double acef = autoCorr( edges, suNo, sl);
		int noc =0; //index to re-order under neglecting any  sequrnces of mulitpex Length[] 
		for( int ir =0; ir <3; ir++)//to sort/re-order with value
		{   
			for( int ij =0; ij <3; ij++)
			{ 
				if(  acef <= repCoeff[ir] && sl%repLength[ij] == 0 )
				{  noc = 1;		break; }
			} // check a sequence of multiplex Length 

			if( noc == 1)  break; 
			else 
			{	
				if( acef > repCoeff[ir] )
				{
					for ( int ii =2; ii>ir; ii--)
					{ 
						repCoeff[ii]  = repCoeff[ii-1];
						repLength[ii] = repLength[ii-1];
					}//endoffor ( int ii
					repCoeff[ir]  = acef; 
					repLength[ir] = sl;
					break;
				} //endof if( acef
			}//for if(noc
		}//for ( int ir
	}//endof for ( int sl
	m_memo.Format("AllEdges%d 1:Co%5.3fwithLen%2d, 2:%5.3fwith%2d ", suNo, repCoeff[0],repLength[0], repCoeff[1],repLength[1] ); //for print to check
	// to print m_memo in the Window in OnPaint() 
} //endof void CChildView::repeatSequence

void CChildView::symMetry() // checking autocorrelation with a half lenght with shift(sftL)
{
 	memset( edges, 0, sizeof(edges) ); // intialization

	suNo = 0;		// index number of all edges 
	for ( int nchn =0; nchn < m_chnNo[m_fudeNum] +1; nchn++)
		for (int nmch = m_numEdges[m_fudeNum][nchn] - 1; nmch > -1; nmch--)
		{ 
			edges[suNo] = (m_edgeChain[m_fudeNum][nchn] >>nmch) & 1;	// pick up the LSB
			suNo++;
		}//endof for ( int nmch 

	bool lgcA, lgcB, *ei;  
	double aCs;	
	int noc = 0, sftL; //index to re-order under neglecting any  sequrnces of mulitpex Length[] 
	//45degSym beginning String 
	for( sftL =0; sftL < suNo/2; sftL++)// sl: for shift phase or length
	{ 
		int sum = 0, ie;
		for( ie = 0, ei = edges; ie < suNo/2; ie++, ei++) //45degSym beginning String 
		{ 
			lgcA = *( ei +sftL);	
			if( sftL -ie > 0 )	lgcB = *(edges +sftL -ie -1);		// over the ALL number	
			else				lgcB = *(edges +suNo +sftL -ie -1);	// back to the middle
			sum += !(lgcA ^ lgcB);	//lgcA == lgcB? 1:0;  NOT(XOR(lgcA,lgcB)) get the same bit
		}//endof for( int i/
		aCs =  (double)sum/(double)(suNo/2);
		if( aCs == 1.0) // print Symmetry at the number string from the start
		{
			m_memo.Format("AllEdges%d 1:Co%5.3fwithLen%2d, 45degSym beginningString%2d ", suNo, repCoeff[0],repLength[0], sftL+1); //for print to check
			noc = 1;  return;
		} 
	}// endof for( int sftL
	//V-H-Sym in Arc String
	for( sftL =0; sftL < suNo/2; sftL++)// sl: for shift phase or length
	{ 
		int sum = 0, ie;
		for( ie = 1, ei = edges; ie < suNo/2; ie++, ei++) // pass the first and the opposite 
		{ 
			lgcA = *( ei +sftL +1);	
			if( sftL -ie +1> 0 )	lgcB = *(edges +sftL -ie );		// over the ALL number	
			else					lgcB = *(edges +suNo +sftL -ie );	// back to the middle
			sum += !(lgcA ^ lgcB);	//lgcA == lgcB? 1:0;  NOT(XOR(lgcA,lgcB)) get the same bit
		}//endof for( int ie
		aCs =  (double)sum/(double)(suNo/2-1);
		if( aCs == 1.0) // print Symmetry at the number string from the start
		{
			m_memo.Format("AllEdges%d 1:Co%5.3fwithLen%2d, V-H-SymAtArcString%2d ", suNo, repCoeff[0],repLength[0], sftL+1); //for print to check
			noc = 1;  return;
		} 
	}// endof for( int sftL
	//未完　V-H-Sym in line String　繰り返し検出　これでは　軸がとれない
	for( sftL =0; sftL < suNo/2; sftL++)// sl: for shift phase or length
	{ 
		int sum = 0, ie;
		for( ie = 0, ei = edges; ie < suNo/2; ie++, ei++) // pass the first and the opposite 
		{ 
			lgcA = *( ei +sftL);	
			if( sftL +ie > suNo/2 )	lgcB = *(ei +sftL);		// over the ALL number	
			else				    lgcB = *(ei +sftL +suNo/2);	// the following half
			sum += !(lgcA ^ lgcB);	//lgcA == lgcB? 1:0;  NOT(XOR(lgcA,lgcB)) get the same bit
		}//endof for( int ie
		aCs =  (double)sum/(double)(suNo/2);
		if( aCs == 1.0) // print Symmetry at the number string from the start
		{
			if( repLength[0] == suNo/4)		 m_memo.Format("AllEdges%d 1:Co%5.3fwithLen%2d, Swastika 90degRotated-Sym sftL%2d ", suNo, repCoeff[0],repLength[0], sftL); //for print to check
			else if( repLength[0] == suNo/2 && m_komaNoX%2 == 1) m_memo.Format("AllEdges%d 1:Co%5.3fwithLen%2d,180deg Rotated-Sym sftL%2d ", suNo, repCoeff[0],repLength[0], sftL); //for print to check
			else if( repLength[0] == suNo/2 && m_komaNoX%2 == 0) m_memo.Format("AllEdges%d 1:Co%5.3fwithLen%2d,V-H-SymAtEdgeString%2d axis? ", suNo, repCoeff[0],repLength[0], sftL); //for print to check
			else					 m_memo.Format("AllEdges%d 1:Co%5.3fwithLen%2d,V-H/Rotated-Sym, sftL%2d axis? ", suNo, repCoeff[0],repLength[0], sftL); //for print to check
			noc = 1;  break;
		} 
	}// endof for( int sftL

	if ( noc ==0) m_memo.Format("AllEdges%d 1:Co%5.3fwithLen%2d, Non Symmetric", suNo, repCoeff[0],repLength[0]); //for print to check

}//endof ChildView::symMtry

//描画関数
	//ReleaseDC(pDC);
	//memDC.MoveTo(-m_kks/2+m_center,  m_kks/2+m_center); // set Horizontal line at upper left  
	//memDC.LineTo( m_kks/2+m_center,  m_kks/2+m_center); //Horizontal to upper right 
	//memDC.Rectangle( x1, y1, x2, y2);//長方形を描画
	//memDC.Ellipse(-ri+center, -ri+center, ri+center, ri+center); // (楕)円を描く
	// inside white as default color 				
	// other way
	//CRect rect(-ri, -ri, ri, ri); rect.OffsetRect(m_center, m_center); 
	//memDC.Ellipse(rect); // white inside as default color
	//memDC.SetPixel( x3, y3, RGB(255, 255, 255)); //  arc starting point too small
	//SetPixelV関数は、実際に描画された点の色を返さないため、SetPixel関数より高速に動作します。
	//すべてのデバイスがSetPixelV関数をサポートするわけではありません。
	//SetPixelV関数がサポートされているかどうかを調べるには、GetDeviceCaps関数を呼び出してRC_BITBLTを
	//チェックしてください。

	// 楕円の代わりに扇を描く
	//memDC.Pie( x1, y1, x2, y2, x3, y3, x4, y4 );	//扇を描く
	/* BOOL Pie( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4 );
		x1,y1:外接する四角形の左上隅の x 、ｙ座標を指定します (論理単位)
		x2,y2:外接する四角形の右下隅の x 、ｙ座標を指定します (論理単位)
		x3,y3:弧の始点のx,y座標を指定します(論理単位)。点は正確に弧の上にある必要はありません
		x4,y4:弧の終点のx,y座標を指定します(論理単位)。点は正確に弧の上にある必要はありません
	*/
	//memDC.SetArcDirection(AD_CLOCKWISE);	
	//Default AD_COUNTERCLOCKWISE Windwos98 doesnot change 
	//memDC.Arc( kx1, ky1, kx2, ky2, x4, y4 , x3, y3); draw an arc x4 to x3 in counterclockwise 
	// 描画方向のmemDC.SetArcDirection(AD_CLOCKWISE);//　defualtは　AD_COUNTERCLOCKWISE 
	// はじめWindowsXｐで　時計回りに切り替えて描いたが
	//Windows98ではこの切り替えが出来ず、常に半時計方向であるために　
	//始点終点を逆にした　こうすればWindows98,XPいずれでも共通に使える
	//点滅　SetTimer関数とWM_TIMERを

	
static int bfrSwell=0; // 2011/02/22  keep index beforSwell=4 and then m_swell=4, after colorCombobox select 4/edge-line,

void CChildView::preparingColor() //set color from ColorDailog
{
	// <2009/10/27 追加 t.yoshino>
	m_swell = m_wndParam.m_SwellMode;
	// </追加>
//2009/11/10 効果なし	m_slpt = m_wndParam.m_SleepTime; //set again after moving mouse
	if( m_swell == 0) //default 
	{
		bfrSwell=0; 
		m_grdColor = RGB(150, 100, 0);
		m_tilColor = RGB(190, 130, 0);
		m_amiColor = RGB(255, 0, 0);
		m_fnlColor = RGB(200, 255, 200); 
	} else if( m_swell == 1) //Black and white for swell paper
	{
		bfrSwell=1; 
		m_grdColor = RGB(255, 255, 255); 
		m_tilColor = RGB(255, 255, 255);
		m_amiColor = RGB(0, 0, 0);
		m_fnlColor = RGB(200, 255, 200);
	} else if( m_swell == 2)	//night show
	{
		bfrSwell=2; 
		m_grdColor = RGB(0, 0, 100); 
		m_tilColor = RGB(0, 0, 150);
		m_amiColor = RGB(255, 0, 0);
		m_fnlColor = RGB(200, 255, 200);
	} else 	if( ( m_swell == 3 && bfrSwell== 4) || m_swell == 4) //2011/02/22  Edge-line color
	{
		m_swell =4; bfrSwell=4; 
		m_grdColor = m_wndParam.m_BtnGColor.GetColor();
		m_tilColor = m_wndParam.m_BtnTColor.GetColor();	
		m_amiColor = m_wndParam.m_BtnAColor.GetColor();	
		m_fnlColor = m_wndParam.m_BtnFColor.GetColor();	
	} else if( m_swell == 3 ) //ColorButton 
	{
		// パラメータダイアログ内のカラーピッカーボタンからブラシ色を設定
		// 直接のコード例　ground2Brush.CreateSolidBrush(m_paramDlg.m_BtnGColor.GetColor());
		m_grdColor = m_wndParam.m_BtnGColor.GetColor();
		m_tilColor = m_wndParam.m_BtnTColor.GetColor();	
		m_amiColor = m_wndParam.m_BtnAColor.GetColor();	
		//if(m_loopNum < 1) m_fnlColor = m_wndParam.m_BtnFColor.GetColor();	//2011/05/01  
		m_fnlColor = m_wndParam.m_BtnFColor.GetColor();	//2011/05/01  
	}

	if( m_swell != 3) //set color in colorbutton from fixed color data 
	{
		m_wndParam.m_BtnGColor.SetColor(m_grdColor);
		m_wndParam.m_BtnTColor.SetColor(m_tilColor);
		m_wndParam.m_BtnAColor.SetColor(m_amiColor);
		m_wndParam.m_BtnFColor.SetColor(m_fnlColor);
	} 	
}// endof preparingColor

// 2011/05/01 for memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);//draw x3 to x4 arc clockwise	
int centx, centy; int kx1, ky1, kx2, ky2; int x3, y3, x4, y4; //for memDC.Arc(

void CChildView::SetPatternArc(short int centsign, short int kxkysign, int nmedgn)
{ 	
	short sgx1,sgx2,sgy1,sgy2; short cnrx,cnry; int acentx, acenty;

	if(centsign ==0){        cnrx = 0; cnry = 0;
	} else if(centsign ==1){ cnrx = 1; cnry = 1; // upper/lower-right/left corner
	} else if(centsign ==2){ cnrx = 1; cnry = -1; // upper/lower-right/left corner
	} else if(centsign ==3){ cnrx = -1; cnry = 1; // upper/lower-right/left corner
	} else if(centsign ==4){ cnrx = -1; cnry = -1; // upper/lower-right/left corner
	}
	acentx = (int)(centx + cnrx*m_kks/2);	acenty = (int)(centy + cnry*m_kks/2); 

	if( kxkysign == 1){        sgx1=1;  sgy1=1;  sgx2=-1; sgy2=-1;
	} else if( kxkysign == 2){ sgx1=-1; sgy1=-1; sgx2=1;  sgy2=1;
	} 

	kx1 = (int)(acentx +sgx1*cri);    ky1 = (int)(acenty +sgy1*cri);// set the Ellipse for Arc
	kx2 = (int)(acentx +sgx2*cri);    ky2 = (int)(acenty +sgy2*cri);
		
	x3 = (int)(acentx + (cri * cospi8th[nmedgn +1]) ); //[1,odd] just axis at edge
	y3 = (int)(acenty + (cri * sinpi8th[nmedgn +1]) );  
	x4 = (int)(acentx + (cri * cospi8th[nmedgn]) );    //[0,even] 45 deg  
	y4 = (int)(acenty + (cri * sinpi8th[nmedgn]) ); 
}//endof void CChildView::SetPatternArc(

void CChildView::OnPaint()
{
	// TODO: Add your message handler code here

	CPaintDC dc(this); // device context for painting

//	/* 2009/10/20 ColorDialogWindowとの重なったところが消えるのを避ける
//2011/06/10　で消す	if( fnlimg == 1 && m_drawImages == FALSE ) return; // avoiding re-painting this window all the time
//	else m_drawImages = FALSE;			// = FALSE　defalt.  すべてm_drawImages = TRUE;を無効にしている
//	但し　未完　ChainModeで　途中止まる事が出来ず、即再スタートする
//	*/
// 未完　ColorDialogWindowとの重なったところがtrace=1 では消えないが　trace=2 では消える？

/*	if( bAutog == TRUE) // 自動化のときの選択	
	{	
		int checkAll = 1;// checking if every KoMa > 0
		for( int inko = 0; inko < m_komaNoX*m_komaNoY; inko++) 
			{	if(m_koM[inko] < 1){	checkAll = 0; return; } 
		}// MessageBox(_T("here checkAll = 0"));	break;for using allKoma
	}
*/	if( bAutog == TRUE && checkAll == 0)  return;//  checkAllをHeaderに入れたので　上の代わりになる

	CString str; 
	int kna;	// Koma operating order-number  
	int edgn;	// side number of Koma edge number 0:right,1:bottom,2:left,3:top
	int sced;	// Edge status, 0:no connected,1: line connected, 2: curve connected   
	               
	// set Pen for drawing lines and Brush for filling shapes // don't use RGB(values) of e.g 080 for 80 
	CPen redPen(PS_SOLID, 4+m_kks/30, RGB(255, 0, 0));  // pulli, Chain line 
	CPen redPenW(PS_SOLID, 8+m_kks/30, RGB(255, 0, 0)); //for red assigned edge  
	CPen greenPen(PS_SOLID, 4+m_kks/30, RGB(0, 255, 0)); //second value line width 
	//CPen greenPen(PS_SOLID, 8+m_kks/30, RGB(0, 255, 0)); //second value line width 
						// also for starting pulli of edgeChain, and copied area
	CPen yellowPen(PS_SOLID, 4+m_kks/30, RGB(255, 230, 100)); // used Pulli, edge bar finalimage 
	CPen yellow2Pen(PS_SOLID, 5+m_kks/30, RGB(100, 100, 0)); // undercrossing line
	CPen bluePen(PS_SOLID, 4+m_kks/30, RGB(0, 0, 255)); //second value line width 
	CPen blue2Pen(PS_SOLID, 1, RGB(0, 0, 150)); // for night show KoMa frame
	CPen whitePen(PS_SOLID, 4+m_kks/30, RGB(255, 255, 255)); // start color Kolam pattern
	CPen edgePen(PS_SOLID, 8+m_kks/30, RGB(0, 0, 0)); // comBox4: edge-line black color Kolam pattern
	CPen grayPen(PS_SOLID, 2+m_kks/40, RGB(220, 220, 220)); 
	CPen gray2Pen(PS_SOLID, 4+m_kks/30, RGB(220, 220, 220)); 
	CPen blackPen(PS_SOLID, 4+m_kks/30, RGB(0, 0, 0)); // Swelling paper for braille Kolam pattern
	CPen blackSPen(PS_SOLID, 2, RGB(0, 0, 0)); // aided cutting line in Swelling paper
	CPen blackSDPen(PS_DOT, 1, RGB(0, 0, 0)); // bloken line of blackSPen for two point crossings
	CPen skyPen(PS_SOLID, 4+m_kks/30, RGB(255, 250, 150)); // DiagonalLine

	CBrush redBrush( RGB(255, 0, 0));					// red pulli,
	CBrush yellowBrush( RGB(255, 255, 100));// KoMa amimate-line-color
	CBrush greenBrush( RGB(0, 255, 0)); //second value line width 
	CBrush blue2Brush( RGB(0, 0, 150)); // for night show KoMa
	CBrush whiteBrush( RGB(255, 255, 255)); // Kolam pattern line 
	CBrush grayBrush( RGB(200, 200, 200));
	CBrush skyBrush( RGB(255, 250, 150)); // vertex corner

	preparingColor();  // set color from ColorDailog
	
	CPen ground2Pen(PS_SOLID, 1, m_tilColor); // Koma tile frame line 
	CBrush ground2Brush( m_tilColor);	//  KoMa tile
	CPen animLnPen(PS_SOLID, 4+m_kks/30, m_amiColor); // trace =1 初めてのtrace
//One-stage-method CPen fnlLnPen(PS_SOLID, 4+m_kks/30, m_fnlColor); // trace =2　終わりのtrace　
//Two-stage-method: first construct the pen
    CPen fnlLnPen, *pOldPen;    // second Then initialize it then Use the pen
//    if( fnlLnPen.CreatePen(PS_SOLID, 4+m_kks/30, m_fnlColor) ) {} 
// 		 fnlLnPen.CreatePen(PS_SOLID, 4+m_kks/30, m_fnlColor);
	// 条件で変わるので while(trce 内で設定する


//平行・菱形 アフィン変換　左下に60度傾ける　斜辺長さが等しく　正方格子を正三角格子、正五角格子Hexagonになるべく、
//転送先平行四角形の 3 つの角を識別する論理空間内の 3 つの点の配列へのポインタ。
//転送元四角形の左上隅がこの配列の最初の点に、右上隅が配列の 2 番目の点に、
//左下隅が配列の 3 番目の点にそれぞれ割り当てられます。右下隅は、平行四角形の 4 番目の点に自動的に割り当てられます。
// dc.PlgBlt(plgpnts, &memDC, 0, 0, width, height, CBitmap(), 0, 0);
	//縦が縮む　POINT plgpnts[3] = { m_imageSiV/4,0,  m_imageSiV/4 +m_imageSiH,0,　　　　　　　　　m_imageSiV/4 -m_imageSiV/2,LONG((m_imageSiV *sqrt(3.0)/2) +0.5) }; //m_kks/4 下左傾き 
	//斜線が長いPOINT plgpnts[3] = { m_imageSiV/4, 0,  m_imageSiV/4 +m_imageSiH, 0,  m_imageSiV/4 -LONG(m_imageSiV/sqrt(3.0) +0.5), m_imageSiV }; //下左傾き 
	POINT plgpnts[3] = { m_kks, 0,  m_kks +LONG(m_imageSiH*2/sqrt(3.0) +0.5), 0,  m_kks -LONG(m_imageSiV/sqrt(3.0) +0.5), m_imageSiV }; //下左傾き 
		//m_kks 全体中心を右シフト
	CMemDC memDC;
	memDC.CreateDIBitmap( m_imageSiH, m_imageSiV );	// creat an image area in the window
	memDC.FillSolidRect(0, 0, m_imageSiH, m_imageSiV, m_grdColor); //ground color
  //memDC.FillRect(CRect(0, 0, m_imageSiH, m_imageSiV), &CBrush(RGB(255, 0, 255))); // color background

	// write Axis values and Filename etc  
	for( short ixys = 0; ixys <m_komaNoX +1; ixys++)
	{	//X-Axis values
 		str.Format("%2d", ixys);
		memDC.TextOut( ixys*m_kks+8,             0, str); // horizontal number
		memDC.TextOut( ixys*m_kks+8, m_imageSiV-55, str); // horizontal number
	}
	for( ixys = 1; ixys <m_komaNoY +1; ixys++)
	{	//Y-Axis values
 		str.Format("%2d", ixys);
		memDC.TextOut(              5, ixys*m_kks+6, str); // vertical number
		memDC.TextOut( m_imageSiH -21, ixys*m_kks+6, str); // vertical number
	}
	if( m_drawMode )       str.Format(" Edge-%s", m_strImgName); // == 1, 2009/11/29 DrawMode の表記とFilename
	else if( !m_drawMode ) str.Format(" KoMa-%s", m_strImgName); // m_strFileTitle only of DialogEDitBox data
	memDC.TextOut( 0, m_imageSiV-45, str); // color is black always 	
	str.Format(" Nagata.Shoji(KASF/InterVision) KolamDesigner'%s", m_cdate);
	memDC.TextOut( 0, m_imageSiV-23, str); 

	// draw all Kolam Koma in image area
	// write KoMa type, no-type -> 0 here 
	//str.Format("Type %2d, Upper%2x,Lower%2x  ", m_E8BtoN81[m_koM[knap]&0xFF], (m_koM[knap]&0xF0)>>4, m_koM[knap]&0x0F);
	//dc.TextOut( m_imageSiH, 50, str); 
	// <2009/11/3 追加 Nagata これで線形状が正常>
	m_kks = m_wndParam.m_KomaSize;
	cri = (int)(m_kks/2.0*1.41421356/2.0); // circle radius of the arc	
	pri = (int)( 1+ m_kks/2.0*1.41421356/20.0); // circle radius of the dot/pulli  
	whd =  m_kks/5;		//nWidth,nHeight 角の丸みの楕円形の幅と高さ
	// </追加>

	kna = 0;  // processing koma number
	while( TRUE ) // drawing all setted kolam koma
	{	
		if( bAutog && !m_saveDatafl && !m_alledge) break; 
		    //bAutog == TRUE, m_saveDatafl == 0,m_alledge == 1 pass while( TRUE ) at auto-generation and no images
 			//m_alledge == 1 the last pattern,all edges m_edcd[ all] = 1
		//if( bAutog == TRUE && m_saveDatafl == 0 ) break; // pass while( TRUE ) at auto-generation and no images
		// drawing the rectangle frame of Kolam Koma 
		int knx = kna%m_komaNoX;	//koma position number in x-axis
		int kny = kna/m_komaNoX;	//koma position number in Y-axis
			centx = (int)(m_kks*(0.5+knx)) +offstx; //m_kks: Kolam Koma size pixel number in side
			centy = (int)(m_kks*(0.5+kny)) +offsty;
		int x1 = centx -m_kks/2;	//nLeftRect 外接する四角形の左上隅の x 座標
		int y1 = centy -m_kks/2;	//nTopRect  外接する四角形の左上隅の ｙ座標
		int x2 = centx +m_kks/2;	//nRightRect 外接する四角形の右下隅の x 座標
		int y2 = centy +m_kks/2;	//nBottomRect 外接する四角形の右下隅の ｙ座標
		if( m_swell == 0 || m_swell == 2 || m_swell == 3 || m_swell == 4 ) 
		{	                      //normal color print and night show color
			if( m_koM[kna] > -1 )
			{ 			
				if( m_swell == 0 || m_swell == 3 || m_swell == 4 )
				{	
					memDC.SelectObject(&ground2Pen); memDC.SelectObject(&ground2Brush);//  daylight show color filling 					
				}	
				else if( m_swell == 2)
				{	
					memDC.SelectObject(&blue2Pen);	memDC.SelectObject(&blue2Brush); //  nightshow color filling
				}
				memDC.RoundRect(x1, y1, x2, y2, whd, whd);//角の丸い長方形を描画
			}
			// drawing Pulli of Using KoMa
			short usedK = m_koMxy[knx][kny]; // anytype used KoMa in Chian mode 
			// Attenton!, このデータはEdit BlockAreaにも使っているので初期値は0ならず　int(0x8000); //= 負最大値
			short assd; // for drwNln BlockArea to largeer Dots
			if( drwNln == 2 && ( knx >= LMbX && knx < LMeX +1 && kny >= LMbY && kny < LMeY +1) )
			{	    // pointing green Pulli dots in BlockArea by Key B/N or OnEdit
					memDC.SelectObject(&greenPen); memDC.SelectObject(&greenBrush);
					assd = 1;
			} else if(m_koM[kna] > 0 || usedK == 1) //  draw Pulli Used KoMa in KoMa/ChainMode
			{
					memDC.SelectObject(&yellowPen);	memDC.SelectObject(&yellowBrush);
					assd = 0;			
			} else if( m_koM[kna] < 1) //no-connecting KoMa
			{
					memDC.SelectObject(&grayPen); memDC.SelectObject(&grayBrush);
					assd = 0;			}//endof if( drwNln == 2 &&   else
			if( m_koM[kna] > 0 && assd == 1 ) memDC.Ellipse(centx-pri*2, centy-pri*2, centx+pri*2, centy+pri*2); //drawing Pulli-GreenDots
			else if( m_koM[kna] > 0 || usedK == 1) memDC.Ellipse(centx-pri, centy-pri, centx+pri, centy+pri); //drawing Pulli-Dots
			else if( m_koM[kna] < 1)           memDC.Ellipse(centx-1, centy-1, centx+1, centy+1); 
		} else if( m_swell ==1)   //black and white for swell paper print
		{				 
			memDC.SelectObject(&grayPen); memDC.SelectObject(&grayBrush);  //2011/02/11				
			if( m_koM[kna] > -1)	memDC.Ellipse(centx-pri, centy-pri, centx+pri, centy+pri); //drawing Pulli-Dots
			else					memDC.Ellipse(centx-1, centy-1, centx+1, centy+1);//中央の点	
			memDC.SelectObject(&blackSPen);	// ２隅　後で切り取り線を描くための黒点
			memDC.Ellipse(x1-1, y1-1, x1+1, y1+1); 				
			memDC.Ellipse(x2-1, y2-1, x2+1, y2+1); 				
		}//endof if( m_swell  								
		
		// drawing 4 strokes in one KoMa
		if( m_swell ==1)		memDC.SelectObject(&gray2Pen);	  // swelling paper print 
		else if(m_koM[kna] ==0)	memDC.SelectObject(&grayPen); 
		else { 
			   if( m_swell ==4)	memDC.SelectObject(&edgePen);
		       else             memDC.SelectObject(&whitePen);
		}
		   	
		// drawing 8 arc/lines of a Kolam pattern	
		if( m_koM[kna] > -1) 
		{ 	
		  for( edgn=0; edgn<4; edgn++) // draw lines at 4 edges 0:right,1:bottom,2:left,3:top
		  { 
			// drawing the Kolam stroke one arc or line  
			sced = (m_koM[kna]>>edgn)%2 + (m_koM[kna]>>(4+edgn))%2 *2; // lower bit + upper bit= 0,1,2
			if(sced == 0) // 0: open=no connection Kolam, draw arc stroke 
			{ 
				SetPatternArc( 0, 2, edgn*2);//(short int centsign,int acenty,short kxkysign,int nmedgn)
				memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);	//円弧を描く,Windows98では始点終点を逆

				SetPatternArc( 0, 2, edgn*2+1);//(short int centsign,int acenty,short kxkysign,int nmedgn)
				memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);	//円弧を描く,Windows98では始点終点を逆
			} else if(sced == 1) //connects to the neighbor KoMa, draw line 
			{  
				//8th line for 45 deg, 
				x3 = (int)(centx + (cri     * cospi8th[edgn*2  ]) ); 
				y3 = (int)(centy + (cri     * sinpi8th[edgn*2  ]) ); 
				x4 = (int)(centx + (m_kks/2 * cospi8th[edgn*2 +1]) ); // here is a connecting point on the edge
				y4 = (int)(centy + (m_kks/2 * sinpi8th[edgn*2 +1]) ); 
				memDC.MoveTo( x3,  y3); memDC.LineTo( x4,  y4); // set  starting point and then make a line
				// 
				x3 = (int)(centx + (cri     * cospi8th[edgn*2 +2]) ); 
				y3 = (int)(centy + (cri     * sinpi8th[edgn*2 +2]) ); 
				x4 = (int)(centx + (m_kks/2 * cospi8th[edgn*2 +1]) ); 
				y4 = (int)(centy + (m_kks/2 * sinpi8th[edgn*2 +1]) ); 
				memDC.MoveTo( x3,  y3); memDC.LineTo( x4,  y4); // set  starting point and then make a line
				// 
			} else if(sced == 2) //connects to the neighbor KoMa, draw opposite curves 
			{ 			// set the Ellipse for Arc
				if( edgn == 0 ) 
				{
				  SetPatternArc( 1, 1, 6);//(short int centsign, int acenty, short int kxkysign, int nmedgn)
				  memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);

				  SetPatternArc( 2, 1, 3);//( short int centsign, short int kxkysign, int nmedgn)
				  memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);
				} else if( edgn == 1)
				{
				  SetPatternArc( 3, 1, 0);//( short int centsign, short int kxkysign, int nmedgn)
				  memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);

				  SetPatternArc( 1, 1, 5);//( short int centsign, short int kxkysign, int nmedgn)
				  memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);
				} else if( edgn == 2)
				{
				  SetPatternArc( 4, 1, 2);//( short int centsign, short int kxkysign, int nmedgn)
				  memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);

				  SetPatternArc( 3, 1, 7);//( short int centsign, short int kxkysign, int nmedgn)
				  memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);
				} else if( edgn == 3)
				{
				  SetPatternArc( 2, 1, 4);//(short int centsign, short int kxkysign, int nmedgn)
				  memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);

				  SetPatternArc( 4, 1, 1);//(short int centsign, short int kxkysign, int nmedgn)
				  memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);
				}
			} //endof else if(sced == 2 
		  } //endof for( edgn
		} //endof else if( m_koM[kna] > -1) 
		if( ++kna == m_komaNoX*m_komaNoY) break;  // all kolam koma were processed
	}// endof while(1, until break for drawing koma
//	dc.BitBlt(0, 0, m_imageSiH, m_imageSiV, &memDC, 0, 0, SRCCOPY);// add Y-area 50 to Kolam Area

	// to draw the Pulli for Fude or Multi-Loops
	for(short nfu =0; nfu < m_fudeNum +1; nfu++)
	{
			//short knx = m_startChainXY[nfu]%m_komaNoX;//koma position number in x-axis
			//short kny = m_startChainXY[nfu]/m_komaNoX;//koma position number in Y-axis
		// 未完　以下は臨時　4,6.5では上の変数順番を使う　変数宣言を変更
		int knx = m_startChainX[nfu];	//koma position number in x-axis
		int kny = m_startChainY[nfu];	//koma position number in y-axis		
			centx = (short)(m_kks*(0.5+knx)) +offstx; //m_kks: Kolam Koma size pixel number in side
			centy = (short)(m_kks*(0.5+kny)) +offsty;
			//short priw = (pri*2);
		if( m_drawMode && nfu == m_fudeNum )// only in ChainMode //change starting Koma/Edge of the 最後の筆last fude
		{ 		//in Chain mode, show the starting KoMa Pulli of the last Fude to do tracing
				memDC.SelectObject(&greenPen); memDC.SelectObject(&greenBrush);
				//short priw = (pri*2);
				memDC.Ellipse(centx-pri*2, centy-pri*2, centx+pri*2, centy+pri*2); //drawing Pulli-Dots
		} else	if( m_drawMode && nfu == 0 )// only in ChainMode
		{ 		// 始めの筆
				memDC.SelectObject(&redPen); memDC.SelectObject(&redBrush);
				memDC.Ellipse(centx-pri, centy-pri, centx+pri, centy+pri); //drawing Pulli-Dots
		} else	if( m_loopNum >0 || m_fudeNum >0)
		{		//in Chain mode, show the starting Pulli of the Fude  // Fudeの数を指定しないには？
				fnlLnPen.DeleteObject(); // 一旦破棄してからでないと再作成できない
				fnlLnPen.CreatePen(PS_SOLID, 4+m_kks/20, m_loopColor[nfu]);
				pOldPen = dc.SelectObject(&fnlLnPen);//元のpenを覚えておく
				memDC.SelectObject(&fnlLnPen); // for back trace
				dc.SelectObject( pOldPen ); //元のpenに戻す	
				memDC.Ellipse(centx-pri, centy-pri, centx+pri, centy+pri); //drawing Pulli-Dots
		} 	
	}// endof for(short nfu 

	//2011/03/01 ここで　マウス位置の赤Dot表示をする　
	short knxp = knap%m_komaNoX;	//present koma position number in x-axis
	short knyp = knap/m_komaNoX;			
	short centpx = (short)(m_kks*(0.5+knxp)) +offstx;
	short centpy = (short)(m_kks*(0.5+knyp)) +offsty;
	memDC.SelectObject(&redPen);  memDC.SelectObject(&redBrush);//Showing the present Koma position with only Pulli	
	memDC.Ellipse(centpx-pri, centpy-pri, centpx+pri, centpy+pri); //drawing Pulli-Dots
//済み 描画後のstarting edgeの赤バーを広幅とせず狭い赤バーのまま　2012/04/22変更、元はYellowバー 
//showing red edge bar in KomaMode or, blue corner in ChainMode assigned by cursor
//済み 最後のときのstarting edge　の赤バーをYellowバー　変える
	if (trce != 1)// trace 以外では太いEdgeバー＆Vertex丸を表示
	{
		memDC.SelectObject(&redPenW); //else memDC.SelectObject(&yellowPen);//for finalImage
		if(prsntedg == 0 || prsntedg == 2)	// to draw red edge bar 
		{		
			x3 = centpx +(1-prsntedg)*m_kks/2;//iedgx1
			y3 = centpy -cri;//iedgy1 up to the down of the neighbor
			x4 = centpx +(1-prsntedg)*m_kks/2;//iedgx2 
			y4 = centpy +cri; //iedgy2
			memDC.MoveTo( x3,  y3); memDC.LineTo( x4,  y4); // set  starting point and then make a line
		} else if(prsntedg == 1 || prsntedg == 3)// to draw red edge bar 
		{ 
			x3 = centpx -cri;// left to right of the neighbor
			y3 = centpy+ (2-prsntedg)*m_kks/2;
			x4 = centpx +cri;
			y4 = centpy+ (2-prsntedg)*m_kks/2;
			memDC.MoveTo( x3,  y3); memDC.LineTo( x4,  y4); // set  starting point and then make a line
		} else if(m_drawMode == 1 && prsntedg == 10)	// to draw Blue right-bottom corner area of red dot Koma for outside turning line
		{	
			memDC.SelectObject(&blue2Pen);	//Showing the present Koma position 	
			memDC.SelectObject(&skyBrush);	//set the color for filling for two-point connect
			int cnrxu = (int)(centpx+m_kks*0.40);
			int cnrxd = (int)(centpx+m_kks*0.60); 
			int cnryu = (int)(centpy+m_kks*0.40);
			int cnryd = (int)(centpy+m_kks*0.60);
			memDC.Ellipse(cnrxu, cnryu, cnrxd, cnryd);
		} //end of if(m_drawMode == 1 && prsntedg ==  
	}//end of if (trce != 1)

	// drawing EdgeChain Keyin S:start, 0&1:stroke for edges, E:set a next
	if( m_drawMode ) //( keyS_M == 0 && m_slpt == 1)to start and stop for Mouse-L
	{	 	  
	  if(m_slpt > 0 && m_komaNoX*m_komaNoY > 24) m_slpt = 1; 	

	  if( animImage == 1 )// for saving an animation image
	  {	
					iani = 0; //save animation image number	
					dc.BitBlt(0, 0, m_imageSiH, m_imageSiV, &memDC, 0, 0, SRCCOPY);				
					m_imageD_F_Name.Format("KolamImages\\%s-a%03d.jpg", m_strFileTitle, iani++); 
					memDC.SaveJPEG(m_imageD_F_Name);	//saveImage(ii++); 
	  }
	  for( int nfu = 0; nfu < m_fudeNum +1; nfu++)// draw multi-fude(stroke)
	  {		//　//m_fudeNum は既に本数よりー１である。検討済み　nfu = 0から始まるから　<m_fudeNum +1ではなく　< m_fudeNumではないか　
		int knx = m_startChainX[nfu];	//koma position number in x-axis
		int kny = m_startChainY[nfu];	//koma position number in y-axis		
		short udidx = m_startSide[nfu]&1;	// LSB:1 CLOCKWISE, 0 UNCLOCK
		      edgn  = m_startSide[nfu]/2;   // edge side of left/right/upper/lower
		for( int nchn = 0; nchn < m_chnNo[nfu] +1; nchn++) // index number of chains 
		{ 
		  memDC.SelectObject(&yellowPen); 
		  for( int nmch = 0; nmch < m_numEdges[nfu][nchn]; nmch++) // edge number in the chain 
		  {
			sced = m_edgeChain[nfu][nchn]>>(m_numEdges[nfu][nchn] -nmch -1);// >>:bit shift,
			sced = sced&1;  // 0:no side-connection,1:connection at the side edge
			// drawing the Kolam stroke one arc or line 
			centx = (int)(m_kks*(0.5+knx)) +offstx;
			centy = (int)(m_kks*(0.5+kny)) +offsty;

			if(sced == 0)
			{	// arc drawing 0: open= no side-connected edge with an arc stroke 
				SetPatternArc( 0, 2, edgn*2 +1-udidx);//(short int centsign, short int kxkysign, int nmedgn)
				memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);	//円弧を描くWindows98では始点終点を逆

				SetPatternArc( 0, 2, edgn*2 +udidx);//(short int centsign, short int kxkysign, int nmedgn)
				memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);	//円弧を描くWindows98では始点終点を逆
				if( animImage == 1 )// for saving an animation image
				{	
					dc.BitBlt(0, 0, m_imageSiH, m_imageSiV, &memDC, 0, 0, SRCCOPY);				
					m_imageD_F_Name.Format("KolamImages\\%s-a%03d.jpg", m_strFileTitle, iani++); 
					memDC.SaveJPEG(m_imageD_F_Name);	//saveImage(ii++); 
				}
					if( cnvEc2KoMa == 1)
					{	
						int kkm = knx +kny*m_komaNoX; // convert to KoMa
						if( m_koM[kkm] <0 ) m_koM[kkm] = 0;
						m_koM[kkm] = m_koM[kkm] & ~(1<<edgn); //logical AND with Nega
					}
			} else	if(sced == 1) // line drawing  connects to the neighbor KoMa with a line stroke
			{			       // 8th line for 45 deg, edge number 0:lower,1:left,2:upper,3:right
				if( nchn == 0 && nmch == 0)	// only starting edge
				{
					int knnx = knx; int knny = kny; int edgnn; // previous KoMa
					if(edgn <2)
					{	edgnn = edgn +2;
						if( edgnn ==2)	knnx =knx+1; else	knny =kny+1; //previous right side, else upper 
					} else 
					{	edgnn = edgn -2;
						if( edgnn ==0)	knnx =knx-1; else	knny =kny-1; //previous left side, else lower
					}
					int centxn = (int)(m_kks*(0.5+knnx)) +offstx;
					int centyn = (int)(m_kks*(0.5+knny)) +offsty;
					x3 = (int)(centxn + (cri     * cospi8th[edgnn*2 +udidx*2]) ); // [0,even] 45 deg line
					y3 = (int)(centyn + (cri     * sinpi8th[edgnn*2 +udidx*2]) ); //udidx 1:up point,0:down point
					x4 = (int)(centxn + (m_kks/2 * cospi8th[edgnn*2 +1]) ); //[1,odd] just axis at edge
					y4 = (int)(centyn + (m_kks/2 * sinpi8th[edgnn*2 +1]) ); 
					if(udidx ==0) { x4 = x4 +(x3 -x4)/5; y4 = y4 +(y3 -y4)/5; } // for undercrossing without gray 
					memDC.MoveTo( x3,  y3); memDC.LineTo( x4,  y4); // set  starting point and then make a line

					if( animImage == 1 )// for saving an animation image
					{	
						dc.BitBlt(0, 0, m_imageSiH, m_imageSiV, &memDC, 0, 0, SRCCOPY);				
						m_imageD_F_Name.Format("KolamImages\\%s-a%03d.jpg", m_strFileTitle, iani++); 
						memDC.SaveJPEG(m_imageD_F_Name);	//saveImage(ii++); 
					}
					if( cnvEc2KoMa == 1)
					{	
						int kkm = knnx +knny*m_komaNoX; // convert to KoMa
						if( m_koM[kkm] <0 ) m_koM[kkm] = 0;
						m_koM[kkm] = m_koM[kkm] | (1<<edgnn); // logical OR
					}
					centx = (int)(m_kks*(0.5+knx)) +offstx;
					centy = (int)(m_kks*(0.5+kny)) +offsty;
					x3 = (int)(centx + (cri     * cospi8th[edgn*2 +udidx*2]) ); //[0,even] 45 deg line 
					y3 = (int)(centy + (cri     * sinpi8th[edgn*2 +udidx*2]) ); //udidx 1:up point,0:down point
					x4 = (int)(centx + (m_kks/2 * cospi8th[edgn*2 +1]) ); //[1,odd] just axis at edge
					y4 = (int)(centy + (m_kks/2 * sinpi8th[edgn*2 +1]) ); 
					if(udidx ==0) { x4 = x4 +(x3 -x4)/5; y4 = y4 +(y3 -y4)/5; } // for undercrossing without gray 
					memDC.MoveTo( x3,  y3); memDC.LineTo( x4,  y4); // set  starting point and then make a line

					if( animImage == 1 )// for saving an animation image
					{	
						dc.BitBlt(0, 0, m_imageSiH, m_imageSiV, &memDC, 0, 0, SRCCOPY);				
						m_imageD_F_Name.Format("KolamImages\\%s-a%03d.jpg", m_strFileTitle, iani++); 
						memDC.SaveJPEG(m_imageD_F_Name);	//saveImage(ii++); 
					}
					if( cnvEc2KoMa == 1)
					{ 
						int kkm = knx +kny*m_komaNoX; // convert to KoMa
						if( m_koM[kkm] <0 ) m_koM[kkm] = 0;
						m_koM[kkm] = m_koM[kkm] | (1<<edgn); // logical OR
					}
				} else // endof if( nchn  the following lines
				{	
					x3 = (int)(centx + (cri     * cospi8th[edgn*2 +(1-udidx)*2]) ); // [0,even] 45 deg line
					y3 = (int)(centy + (cri     * sinpi8th[edgn*2 +(1-udidx)*2]) ); //udidx 1:up point,0:down point
					x4 = (int)(centx + (m_kks/2 * cospi8th[edgn*2 +1]) ); //[1,odd] just axis at edge
					y4 = (int)(centy + (m_kks/2 * sinpi8th[edgn*2 +1]) );
					if(udidx ==1) { x4 = x4 +(x3 -x4)/5; y4 = y4 +(y3 -y4)/5; } // for undercrossing without gray
					memDC.MoveTo( x3,  y3); memDC.LineTo( x4,  y4); // set  starting point and then make a line
				// 
					if( animImage == 1 )// for saving an animation image
					{	
						dc.BitBlt(0, 0, m_imageSiH, m_imageSiV, &memDC, 0, 0, SRCCOPY);				
						m_imageD_F_Name.Format("KolamImages\\%s-a%03d.jpg", m_strFileTitle, iani++); 
						memDC.SaveJPEG(m_imageD_F_Name);	//saveImage(ii++); 
					}
					if( cnvEc2KoMa == 1)
					{ 
						int kkm = knx +kny*m_komaNoX; // convert to KoMa
						if( m_koM[kkm] <0 ) m_koM[kkm] = 0;
						m_koM[kkm] = m_koM[kkm] | (1<<edgn); // logical OR
					}		
					if(edgn <2)
					{	edgn = edgn +2;
						if( edgn ==2)	knx =knx+1;	else kny =kny+1; //next right side, else upper
					} else 
					{	edgn = edgn -2;
						if( edgn ==0)	knx =knx-1;	else kny =kny-1; //next left side, else lower
					}
					udidx = 1 -udidx;	//alternate the directions of the next KoMa
					centx = (int)(m_kks*(0.5+knx)) +offstx;
					centy = (int)(m_kks*(0.5+kny)) +offsty;
					x3 = (int)(centx + (cri     * cospi8th[edgn*2 +udidx*2]) ); //[0,even] 45 deg line 
					y3 = (int)(centy + (cri     * sinpi8th[edgn*2 +udidx*2]) ); //udidx 1:up point,0:down point
					x4 = (int)(centx + (m_kks/2 * cospi8th[edgn*2 +1]) ); //[1,odd] just axis at edge
					y4 = (int)(centy + (m_kks/2 * sinpi8th[edgn*2 +1]) ); 
					if(udidx ==0) {	x4 = x4 +(x3 -x4)/5; y4 = y4 +(y3 -y4)/5; } // for undercrossing without gray
					memDC.MoveTo( x3,  y3); memDC.LineTo( x4,  y4); // set  starting point and then make a line

					if( animImage == 1 )// for saving an animation image
					{	
						dc.BitBlt(0, 0, m_imageSiH, m_imageSiV, &memDC, 0, 0, SRCCOPY);				
						m_imageD_F_Name.Format("KolamImages\\%s-a%03d.jpg", m_strFileTitle, iani++); 
						memDC.SaveJPEG(m_imageD_F_Name);	//saveImage(ii++); 
					}
					if( cnvEc2KoMa == 1)
					{	
						int kkm = knx +kny*m_komaNoX; // convert to KoMa
						if( m_koM[kkm] <0 ) m_koM[kkm] = 0;
						m_koM[kkm] = m_koM[kkm] | (1<<edgn); // logical OR
					}
				}//endof if( nchn == 0 && nmch == 0) else
			} //endof else { //if(sced == 1 
			if( m_slpt != 0)
			{	
				double randf = 0.5 + (double)rand()/(double)RAND_MAX *1.5;
				Sleep( int(m_slpt * randf) ); // Sleep(m_slpt);sleeping in msecond for animation
				dc.BitBlt(0, 0, m_imageSiH, m_imageSiV, &memDC, 0, 0, SRCCOPY);				
			}
			if( udidx )
			{	edgn = edgn +1; 
				if(edgn == 4) edgn = 0; //neighbor KoMa
			} else 
			{	edgn = edgn -1; 
				if(edgn == -1) edgn = 3;
			}
			// change the color after the first crossing/ stroke at the edge
			if(m_loopNum > 0) // for loops 
			{
				fnlLnPen.DeleteObject(); // 一旦破棄してからでないと再作成できない
				//fnlLnPen.CreatePen(PS_SOLID, 4+m_kks/30, m_loopColor[loopNo]);
				fnlLnPen.CreatePen(PS_SOLID, 4+m_kks/30, m_loopColor[nfu]);
				pOldPen = dc.SelectObject(&fnlLnPen);//元のpenを覚えておく
				memDC.SelectObject(&fnlLnPen); // for back trace
				dc.SelectObject( pOldPen ); //元のpenに戻す	
			} else 
			{
	    	 	 if( nfu == 0)	memDC.SelectObject(&redPen);
			else if( nfu == 1)	memDC.SelectObject(&greenPen);
			else if( nfu == 2)  memDC.SelectObject(&bluePen);
			else if( nfu == 3)	memDC.SelectObject(&gray2Pen);
			else if( nfu == 4)	memDC.SelectObject(&yellowPen);
			else if( nfu == 5)	memDC.SelectObject(&whitePen);			
			else if( nfu == 6)	memDC.SelectObject(&redPen);			
			else if( nfu == 7)	memDC.SelectObject(&greenPen);			
			else if( nfu == 8)	memDC.SelectObject(&bluePen);			
			else if( nfu == 9)	memDC.SelectObject(&gray2Pen);			
			else if( nfu == 10)	memDC.SelectObject(&yellowPen);				
			else				memDC.SelectObject(&whitePen);
			}

			if( GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState(VK_LBUTTON) & 0x8000 )// force to stop drawing //VK_ESCAPE
			{ 
				m_slpt = 0; cnvEc2KoMa = 0; keyS_M = 0;  fnlimg = 1; //  未完keeping the trace,　version 4.2.9 for stop OK
				dc.BitBlt(0, 0, m_imageSiH, m_imageSiV, &memDC, 0, 0, SRCCOPY);// not only Kolam Area added to Y 50
				Invalidate(FALSE);// show only the last image nagata 	
				return; 
			}
		  }//endof for( int nmch
		}//endof for( int nchn
	  }//endof for( int nfu
	  animImage = 0; iani = 0;  keyS_M = 0;
	  m_slpt = 0; cnvEc2KoMa = 0; // reset for the following 
	  dc.BitBlt(0, 0, m_imageSiH, m_imageSiV, &memDC, 0, 0, SRCCOPY);// not only Kolam Area added to Y 50
	  if( stilImage == 1)
	  {		
			m_imageD_F_Name.Format("KolamImages\\%s.jpg", m_strFileTitle); 
			memDC.SaveJPEG(m_imageD_F_Name);	//saveImage(0);
			stilImage = 0;
	  }	  	  
	} //endof if( m_drawMode edgeChain
	dc.BitBlt(0, 0, m_imageSiH, m_imageSiV, &memDC, 0, 0, SRCCOPY);// add Y-area 50 to Kolam Area
	
	// m_drawMode KomaTile drawing hitoFude single stroke with "S" Keyin //紋様を全部描き終わった上に一筆を重ね描きする
	// trce = 1 -> start to trace the kolam pattern on pointing,  0->set kolam koma arrangement and draw all Kolam
	double npwroot = pow( 2.0, 1.0/m_komaNoY *2.0 );// for 2x N-tone sound between KomaNoY
  
	short int komaCo, udidx, passindx; 
// set multi-loop drawing here 2011/05/01 問題　while() で良いか？？？？
//    [loopNo =0,...,m_loopNum -1] Loop array数 m_loopNum > 0、初期値は0本
/* m_loopNum, loopNo, trce,   kna, finalcolor,  drawing
           -,      -,    0,     -,       -,     no,while( break
		   0,     -1,    1,   mouse, anima,     yes
		   0,     -1,    2,   mouse, final,     yes
		   1,      0,    1,  [loopNo],[loopNo], yes, or pass
		   1,      0,    2,  [loopNo],[loopNo], yes
		   1,     -1,    1,   mouse, anima,     yes
		   1,     -1,    2,   mouse, final,     yes
		   2,      1,    1,  [loopNo],[loopNo], yes, or pass
		   2,      1,    2,  [loopNo],[loopNo], yes
		   2,      0,    1,  [loopNo],[loopNo], yes, or pass
		   2,      0,    2,  [loopNo],[loopNo], yes
		   2,     -1,    1,   mouse, anima,     yes
		   2,     -1,    2,   mouse, final,     yes
           -,      -,    3,                     no, while( break
	課題　現行カーソルからのLoop即表示とLoop記録全表示と重なる　どうするか？
	      現行接続操作用赤Edgeとスタート赤Edgeと同じ。
		  スタートEdgeを操作するのが改修か（Key矢印で決めるか？マウスのみでは？）、
		  現行の自動切替が良いか　検討すべき　
*/
    int loopNo = -1;
	int sttKoma; // set starting Koma for instead of knap(presnet Koma)
	int strtedgback;
		// 未登録＝新規の筆輪のスタートEdgeが固定されている　なぜか？

	while(trce >0 && trce <3)	//trce 1:1st trace Red/Green(Final in Dialog) 2:2nd Final
	{	 
		// no^work	if(trce == 1 && bAutog == TRUE && m_saveDatafl == 0) trce = 2; // add 2011/03/07 pass trce=1  at auto-generation and no images
		//if( prsntedg < 0 ) break; // out of the edge area 
//for check proccess	 str.Format("1                    "); //
	 if(0 < m_loopNum) trce = 2; //臨時 trce=1のアニメーションを省く

	 if( loopNo == -1 ) 
	 {
		 // if(0 < m_loopNum) trce = 2;途中でエラー
		 kna = sttKoma = knap;; //knap; to set starting koma of red present koma[knap]
		 strtedgback = strtedg;

//for check proccess	 str.Format("3 trce%2d loopNo%2d of Num%2d kna%2d edg%2d ", trce, loopNo, m_loopNum, kna, strtedg); //
//		 dc.SelectObject( pOldPen ); //元のpenに戻す		 
		 fnlLnPen.DeleteObject(); // 一旦破棄してからでないと再作成できない
		 fnlLnPen.CreatePen(PS_SOLID, 4+m_kks/30, m_fnlColor);
		 pOldPen = dc.SelectObject(&fnlLnPen);//元のpenを覚えておく
	 } else if(trce == 2 && -1 < loopNo ) //set multi-loop drawing here 2011/05/01  to draw multi-loop
	 {	
		 kna = sttKoma = m_strtKoma[loopNo];	//
		 strtedg =  m_strtSide[loopNo];//strtedgback =
//for check proccess	 str.Format("2 trce%2d loopNo%2d of Num%2d kna%2d edg%2d ", trce, loopNo, m_loopNum, kna, strtedg); //
//		 dc.SelectObject( pOldPen ); //元のpenに戻す		 
		 fnlLnPen.DeleteObject(); // 一旦破棄してからでないと再作成できない
		 fnlLnPen.CreatePen(PS_SOLID, 4+m_kks/30, m_loopColor[loopNo]);
		 pOldPen = dc.SelectObject(&fnlLnPen);//元のpenを覚えておく
	 }  	 
//		 dc.TextOut( m_imageSiH, 100, str); //for check proccess
	 
	 	komaCo = udidx = strtedg&1; //LSB bit udidx=0:Down/counterclockwise,1:Up crossing/turns round clockwise 
		edgn  = strtedg/2; // 2nd,3rd bit:edgeNumber of starting connection at starting Koma

		if( trce == 1 && stilImage == 1 ) // including  animImage == 1
		{
				iani = 0; //save animation image number	
				m_imageD_F_Name.Format("KolamImages\\%s-a%03d.jpg", m_strFileTitle, iani++); 
				memDC.SaveJPEG(m_imageD_F_Name);	//saveImage(0);
		} else if( trce == 2 ) // initialize to convert the edge chain
		{ 
			if(m_loopNum > 0 &&  -1 < loopNo)  m_fudeNum = loopNo; //2011/08/10 LoopのあるときのFude番号
			else m_fudeNum = loopNo +1; //m_fudeNum:0-Max9, added for mulitLoop
			m_startChainX[m_fudeNum] = sttKoma%m_komaNoX; // edgeChain data,= kna%m_komaNoXでOKか？後で調べる
			m_startChainY[m_fudeNum] = sttKoma/m_komaNoX;
			m_startSide[m_fudeNum]   = strtedg; 
			m_chnNo[m_fudeNum] = 0; //the first one
			m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ] = 0; // for making an edgechain
			m_edgeChain[m_fudeNum][ m_chnNo[m_fudeNum] ] = 0;
		}
				
		while( TRUE )// change an edge in the same Koma and then the next KoMa until stopping Hitofude   
		{				
			int knx = kna%m_komaNoX;	//koma position number in x-axis
			int kny = kna/m_komaNoX;	//koma position number in y-axis		
				centx = (int)(m_kks*(0.5+knx)) +offstx;
				centy = (int)(m_kks*(0.5+kny)) +offsty;
			passindx = 0;
			// stroke line color
			int colori = (int)( (double)kny/(double)m_komaNoY*200.0 );	//color-tone changes as virtical position
			CPen red2Pen(PS_SOLID, 4+m_kks/30, RGB(255-colori/2, 0, colori/2)); //second value line width 
			CPen bluGrPen(PS_SOLID, 4+m_kks/30, RGB( 0, 255-colori, colori));	//second value line width 
			
			if( trce == 1 )			// 初めのTrace 色決め
			{	
				if( m_swell !=1)	//m_swell  = 0,2,3 and 4 Edgeline
				{	
					if(komaCo ==1) // line color in a Koma alternately changing
					{						
						if( m_swell ==3 || m_swell ==4)	memDC.SelectObject(&animLnPen); // 2011/2/22 ColorButton in one Kolam	
						else                            memDC.SelectObject(&red2Pen);   // day show
						
					} else 
					{	
						if( m_swell ==0)		memDC.SelectObject(&bluGrPen);  // day show
						else if( m_swell ==2)	memDC.SelectObject(&yellowPen); // night show
						else if( m_swell ==3){	memDC.SelectObject(&fnlLnPen); 		 
//												dc.SelectObject( pOldPen ); //元のpenに戻す		 
						}                        // ColorButton color in next Kolam
						else if( m_swell ==4)	memDC.SelectObject(&animLnPen); // 2011/2/22 edge-line
					}// endof if(komaCo
				} else if( m_swell ==1)			memDC.SelectObject(&blackPen); // swelling paper print
			} else if( trce == 2 ){ 			memDC.SelectObject(&fnlLnPen); // for back trace
												dc.SelectObject( pOldPen ); //元のpenに戻す		 
			}                      
			//drawing the line from the starting point 		
			sced = (m_koM[kna]>>edgn)%2 + (m_koM[kna]>>(4+edgn))%2 *2; // lower bit + upper bit= 0,1,2			
			if( sced < 2) //connects to the neighbor KoMa, draw line at a point
			{
				x3 = (int)(centx + (cri     * cospi8th[edgn*2 +udidx*2]) ); //[0,even] 45 deg line 
				y3 = (int)(centy + (cri     * sinpi8th[edgn*2 +udidx*2]) ); //udidx 1:up point,0:down point
				x4 = (int)(centx + (m_kks/2 * cospi8th[edgn*2 +1]) );		//[1,odd] just axis at edge
				y4 = (int)(centy + (m_kks/2 * sinpi8th[edgn*2 +1]) ); 
				if(udidx ==0) 
				{	
					if( trce == 2 && m_swell == 0)	memDC.SelectObject(&yellow2Pen);// undercrossing
					if( m_swell ==4){
						x4 = x4 +(x3 -x4)/5 +(x3 -x4)/abs(x3-x4)*3; 
					    y4 = y4 +(y3 -y4)/5 +(y3 -y4)/abs(y3-y4)*3;		// back width 
					} else {
						x4 = x4 +(x3 -x4)/5;
					    y4 = y4 +(y3 -y4)/5;		// back width 
					}
				} 
				memDC.MoveTo( x3,  y3); memDC.LineTo( x4,  y4); // set  starting point and then make a line
			} else if(sced == 2) //connects to the neighbor KoMa, draw opposite curves
			{	 //2011/05/01 
				if( edgn == 0 ) 
				{
				  if( udidx ==0)
				  {
					SetPatternArc( 1, 1, 6);//(short int centsign, short int kxkysign, int nmedgn)
				  } else if( udidx ==1)
				  {
					SetPatternArc( 2, 1, 3);//(short int centsign, short int kxkysign, int nmedgn)
				  }//endof if( udidx 
				    memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);
				} else if( edgn == 1)
				{
				  if( udidx ==0)
				  {
					SetPatternArc( 3, 1, 0);//(short int centsign, short int kxkysign, int nmedgn)
				  } else if( udidx ==1)
				  {
					SetPatternArc( 1, 1, 5);//(short int centsign, short int kxkysign, int nmedgn)
				  }//endof if( udidx 
				    memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);
				} else if( edgn == 2)
				{
				  if( udidx ==0)
				  {
					SetPatternArc( 4, 1, 2);//(short int centsign, short int kxkysign, int nmedgn)
				  } else if( udidx ==1)
				  {
					SetPatternArc( 3, 1, 7);//(short int centsign, short int kxkysign, int nmedgn)
 				  }//endof if( udidx 
				    memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);
				} else if( edgn == 3)
				{
				  if( udidx ==0)
				  {
					SetPatternArc( 2, 1, 4);//(short int centsign, short int kxkysign, int nmedgn)
				  } else if( udidx ==1)
				  {
					SetPatternArc( 4, 1, 1);//(short int centsign, short int kxkysign, int nmedgn)
				  }//endof if( udidx 
				    memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);
				}//endof if( edgn ==
				udidx = 1 -udidx;	//alternate the directions
			} //endof else if(sced == 2 
			if( trce == 2 ) // convert the edge chain
			{
				m_edgeChain[m_fudeNum][ m_chnNo[m_fudeNum] ] = (m_edgeChain[m_fudeNum][ m_chnNo[m_fudeNum] ]<<1) +1; //to get EdgeChain, shift up to add 1 edge to the LSB; 
				m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ]++; //for edgeChain m_chnNo; 
				if(m_numEdges[m_fudeNum][m_chnNo[m_fudeNum]] >31)
				{
					m_chnNo[m_fudeNum]++;	
					m_numEdges[m_fudeNum][m_chnNo[m_fudeNum]] = 0; 
				}//for edgeChain m_chnNo;
			}
			if( m_slpt !=0)
			{	
				if( trce ==1) 
				{
					int slptt =m_slpt*(unsigned long)(1.0 +9.0*(double)rand()/(double)RAND_MAX); 
					Sleep( slptt); // Sleep(m_slpt);sleeping in msecond for animation
					int tone = (int)( 131.0 * pow( npwroot, (double)(m_komaNoY-kny)) );
					Beep( tone, slptt);
				}
				dc.BitBlt(0, 0, m_imageSiH, m_imageSiV, &memDC, 0, 0, SRCCOPY);	
			}
				// tone changes as virtical position , DWORD dwFreq:音の周波数ヘルツ単位 37(0x25)から32767(0x7FFF)まで
				//ドBeep(262,レ(294,ミ(330,ファ(349,ソ(392,ラ(440,シ(494,ド(523,
				// 12 tones, 12log10*X= log10(2)=log10２, ratio X=1.06 
			if( animImage == 1 && (trce ==1 || m_smoothmod ==2 && trce ==2 || m_loopNum > 0) ) //for saving an animation image// old version m_smoothmod ==1
			{	// Multi-Loopのアニメはここだけでして　後は駒飛ばす
				m_imageD_F_Name.Format("KolamImages\\%s-a%03d.jpg", m_strFileTitle, iani++); 
				memDC.SaveJPEG(m_imageD_F_Name);	//saveImage(ii++); 
			}
			// drawing the arcs in the same koma
			int	nxtedg = nextEdg( kna, edgn, udidx); //next edge at the contact point in the same Koma
			int edga = edgn; //tempolary edge to set the direction of arc

			if( trce == 2 ) 	memDC.SelectObject(&fnlLnPen); 
			while(TRUE){ // arcs in the same koma// set the Ellipse for Arc
//				if( trce == 2 ) 	memDC.SelectObject(&fnlLnPen); 
				edga = edga +(udidx*2 -1); //case of up point ++, down point --
				if(edga == 4) edga = 0;	else if(edga == -1) edga = 3;  //case of up point, down point
				if(edga == nxtedg) break; // stop to trace 
				SetPatternArc( 0, 2, edga*2 +1-udidx);
				memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);//draw x3 to x4 arc clockwise	

				if( m_slpt !=0)
				{	
					if( trce ==1) 
					{
						Sleep( m_slpt*(unsigned long)(1.0 +9.0*(double)rand()/(double)RAND_MAX) ); // Sleep(m_slpt);sleeping in msecond for animation
						if(udidx ==0) MessageBeep(MB_ICONQUESTION); else MessageBeep(MB_ICONEXCLAMATION);
					}
 					dc.BitBlt(0, 0, m_imageSiH, m_imageSiV, &memDC, 0, 0, SRCCOPY);	
				}
				if( animImage == 1 && (trce ==1 || m_smoothmod ==2 && trce ==2) )// for saving an animation image
				{	
					m_imageD_F_Name.Format("KolamImages\\%s-a%03d.jpg", m_strFileTitle, iani++); 
					memDC.SaveJPEG(m_imageD_F_Name); 	//saveImage(ii++); 
				}
				SetPatternArc( 0, 2, edga*2 +udidx);
				memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);//draw x3 to x4 arc clockwise	

				if( trce == 2 ) // convert the edge chain
				{
					m_edgeChain[m_fudeNum][ m_chnNo[m_fudeNum] ] = m_edgeChain[m_fudeNum][ m_chnNo[m_fudeNum] ]<<1; //shift up to add 0 edge to the LSB; 
					m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ]++;  
					if(m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ] >31)
					{  
						m_chnNo[m_fudeNum]++;	
						m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ] = 0; //for edgeChain
					}
				}
				if( m_slpt !=0)
				{	
					if( trce ==1) 
					{
						Sleep( m_slpt*(unsigned long)(1.0 +9.0*(double)rand()/(double)RAND_MAX) ); // Sleep(m_slpt);sleeping in msecond for animation
						if(udidx ==0) MessageBeep(MB_ICONQUESTION);	else MessageBeep(MB_ICONEXCLAMATION);
 					}
					dc.BitBlt(0, 0, m_imageSiH, m_imageSiV, &memDC, 0, 0, SRCCOPY);	
				}
				if( animImage == 1 && (trce ==1 || m_smoothmod ==2 && trce ==2) )// for saving an animation image
				{	
					m_imageD_F_Name.Format("KolamImages\\%s-a%03d.jpg", m_strFileTitle, iani++); 
					memDC.SaveJPEG(m_imageD_F_Name); 	//saveImage(ii++); 
				}
			} //endof while( edge for arcs in the same Koma 
			
			sced = (m_koM[kna]>>edga)%2 + (m_koM[kna]>>(4+edga))%2 *2; // edge crossing statuses =lowerbit + upperbit= 0,1,2			
			if( sced == 1)	//draw the line to the next connecting point
			{	
				x3 = (int)(centx + (cri     * cospi8th[edga*2 +(1-udidx)*2]) );	// [0,even] 45 deg line
				y3 = (int)(centy + (cri     * sinpi8th[edga*2 +(1-udidx)*2]) );	//udidx 1:up point,0:down point
				x4 = (int)(centx + (m_kks/2 * cospi8th[edga*2 +1]) );		//[1,odd] just axis at edge
				y4 = (int)(centy + (m_kks/2 * sinpi8th[edga*2 +1]) ); 
				if(udidx ==1) 
				{	
					if( m_swell ==4){
						x4 = x4 +(x3 -x4)/5 +(x3 -x4)/abs(x3-x4)*3; 
					    y4 = y4 +(y3 -y4)/5 +(y3 -y4)/abs(y3-y4)*3;		// back width 
					} else {
						x4 = x4 +(x3 -x4)/5;
					    y4 = y4 +(y3 -y4)/5;		// back width 
					}
					if( trce == 2 && m_swell == 0)	memDC.SelectObject(&yellow2Pen); // undercrossing
				}  
				memDC.MoveTo( x3,  y3); memDC.LineTo( x4,  y4); // set  starting point and then make a line
				// 
			} else if(sced == 2) //connects at two points to the neighbor KoMa, with opposite curves
			{	 
				if( nxtedg == 0 ) 
				{
				  if(udidx ==0) 
				  {  
					SetPatternArc( 1, 1, 6);//(short int centsign, short int kxkysign, int nmedgn)
				    memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);
				  } else if(udidx ==1)
			      { 
					SetPatternArc( 2, 1, 3);//( short int centsign, short int kxkysign, int nmedgn)
				    memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);
				  }//endof if(udidx 
				} else if( nxtedg == 1)
				{
				  if(udidx ==0)
			      { 
					SetPatternArc( 3, 1, 0);//( short int centsign, short int kxkysign, int nmedgn)
					memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);
				  } else if(udidx ==1) 
				  {  
					SetPatternArc( 1, 1, 5);//( short int centsign, short int kxkysign, int nmedgn)
				    memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);
				  }//endof if(udidx 
				} else if( nxtedg == 2)
				{
				  if(udidx ==0)
			      { 
					SetPatternArc( 4, 1, 2);//( short int centsign, short int kxkysign, int nmedgn)
				    memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);
				  } else if(udidx ==1) 
				  {  
					SetPatternArc( 3, 1, 7);//( short int centsign, short int kxkysign, int nmedgn)
				    memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);
				  } //endof if(udidx 
				} else if( nxtedg == 3)
				{
				  if(udidx ==0) 
				  {  
					SetPatternArc( 2, 1, 4);//( int acentx, int acenty, short int kxkysign, int nmedgn)
				    memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);
				  } else if(udidx ==1)
			      { 
					SetPatternArc( 4, 1, 1);//( int acentx, int acenty, short int kxkysign, int nmedgn)
				    memDC.Arc( kx1, ky1, kx2, ky2, x3, y3, x4, y4);
				  }//endof if(udidx 
				}//endof if( edga ==
				if( m_smoothmod ==2) udidx = 1 -udidx; //for outline tracing
			} //endof else if(sced == 2 
			if( m_slpt !=0)
			{	
				if( trce ==1) 
				{
					Sleep( m_slpt*(unsigned long)(1.0 +9.0*(double)rand()/(double)RAND_MAX) ); // Sleep(m_slpt);sleeping in msecond for animation
					if(udidx ==0)	MessageBeep(MB_ICONASTERISK);	else MessageBeep(MB_ICONHAND);
				}
				dc.BitBlt(0, 0, m_imageSiH, m_imageSiV, &memDC, 0, 0, SRCCOPY);	
			}
			if( animImage == 1 && (trce ==1 || m_smoothmod ==2 && trce ==2) )// for saving an animation image
			{	
				m_imageD_F_Name.Format("KolamImages\\%s-a%03d.jpg", m_strFileTitle, iani++); 
				memDC.SaveJPEG(m_imageD_F_Name); 	//saveImage(ii++); 
			}

			// find a number of the adjoining/adjacent/neighbor Koma edge, edgeの数え方は右廻り
			short int knaback = kna;
			passindx = 0; 
			if( nxtedg == 0) // present edge of the right koma		
			{
				if( knx+1 <m_komaNoX ) //隣接Komaがあれば passindx=1, continue to trace
				{	edgn =2;	kna = kna +1; // connect to the left koma
					passindx = 1;  
				} else if( m_smoothmod >0 && sced ==1 )  passindx = 2; // at sharpbend in surrounding Koma
			} else if( nxtedg == 1) //the bottom koma
			{	
				if( kny+1 <m_komaNoY )//隣接Komaがあれば passindx=1, continue to trace 
				{	edgn =3;	kna = kna +m_komaNoX; // to the top koma
					passindx = 1; 
				} else if( m_smoothmod >0 && sced ==1 )  passindx = 2; // at sharpbend 
			} else if( nxtedg == 2) //the left koma
			{	
				if( knx-1 >-1 )//隣接Komaがあれば passindx=1, continue to trace
				{	edgn =0;	kna = kna -1;// to the right koma
					passindx = 1;  
				} else if( m_smoothmod >0 && sced ==1 )  passindx = 2; // at sharpbend 
			} else if( nxtedg == 3) //the top koma
			{	
				if( kny-1 >-1 )//隣接Komaがあれば passindx=1, continue to trace 
				{	edgn =1;	kna = kna -m_komaNoX;// to the bottom koma
					passindx = 1; 
				} else if( m_smoothmod >0 && sced ==1 )  passindx = 2; // at sharpbend in surrounding Koma 
			}  

			if( passindx == 1)  // in the adjoining Koma, check the same edge status  
			{	
				if( (sced ==1 && (m_koM[kna]>>edgn)&1)    || // edge status one crossing point	 
				    (sced ==2 && (m_koM[kna]>>(edgn+4))&1) ) // two point connect
				{  // keep passindx = 1;
				} else if( m_smoothmod >0 && sced ==1 && (((m_koM[kna]>>edgn)&1) ==0)  )  // at sharpbend in inside Koma 
				{  // keep passindx = 1;
					kna = knaback; edgn = nxtedg; // back to the same Koma
					if( m_smoothmod ==1) udidx = 1 -udidx;
					komaCo = 1 -komaCo; //line color
//	CString strData; strData.Format("sharpbend kna=%d sced=%d edgn=%d",kna,sced,edgn); AfxMessageBox(strData); //MessageBox for data	
				} else // the adjoining Koma, but it is not linked to continue the trace
				{	
					passindx = 0;    //	MessageBox(_T("here passindx check passindx =0"));	
				} 
			} else if( passindx == 2 )  // at sharpBend in surrounding Koma 
			{	
					edgn = nxtedg;// back to the same Koma
					if( m_smoothmod <2) udidx = 1 -udidx; // for Smooth and NonSmoot 
					komaCo = 1 -komaCo; 
					passindx = 1;
			} 

			if( m_smoothmod <2 ) // 0: tracing in Smooth or nonSmooth(sharpBend) mode 
			{	
				udidx = 1 -udidx;	// change the up-down connection in the next koma  
				komaCo = 1 -komaCo; 
				if( passindx == 0 || (kna == sttKoma && strtedg == edgn*2+udidx) ) // stoping at starting edge in 1st,2nd trce 
				{		
//	CString strData; strData.Format("m_smoothmod=%d sced=%d nxtedg=%d edgn=%d",m_smoothmod,sced,nxtedg,edgn); AfxMessageBox(strData); //MessageBox for data	
					keyS_M = 0;	 break; //  to stop the trace  while(TRUE){ // arcs in the same koma
				}							
			} else if( m_smoothmod ==2) // tracing in outline mode 
			{
				komaCo = 1 -komaCo; 
				if( passindx == 0 || (kna == sttKoma && strtedg/2 == edgn) )	// stoping at starting edge 
				{	// change the turning direction
					strtedg = (1- strtedg%2) +(strtedg/2)*2; // opposit crossing point	
					break;
				}
			}
			if( GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState(VK_LBUTTON) & 0x8000) 	
			{	// not work for stoping the trace,
				keyS_M = 0;  trce = 1; m_slpt = 0;	prsntedg = -99;	break; // 
			}  else if( prsntedg != -99 ) keyS_M = 0; // to avoid to restart at onKeyUp() with Key 'S' 
			
			dc.SelectObject( pOldPen ); //元のpenに戻す	2011/05/01 	 

		} // endof while( TRUE  // change an edge in the same Koma and then the next KoMa until breaking for Hitofude
		dc.BitBlt(0, 0, m_imageSiH, m_imageSiV, &memDC, 0, 0, SRCCOPY);

		if( bAutog ) //== TRUE
		{ 
			if( m_alledge == 1 ){ fnlimg = 1;	checkAll = 0; }//to keep finalimage with all-edge connected 
			trce = 0;	break; 
		}// out from while(trce >0) to stop after once tracing at Autogeneration
		trce = trce++; // trce = 1,2, and escape of 3;  

		while( TRUE)
		{	//intermission before trace back // Stop to KeyDown ShiftKey, before KeyIn "S"  
			if( shftky == 1 )
			{	//  = GetAsyncKeyState( VK_SHIFT )
				shftky = 0;	Sleep(6000); break; 
			} else {		Sleep( 500); break;	} 
		}//endof while( TRUE) tracing one stroke  

		if( stilImage )//== 1 only trce == 1,2,3
		{	
			//if( trce == 2 ) // saving the final still image in animation
			//{		
			//	MessageBeep(MB_ICONEXCLAMATION);
			//	m_imageD_F_Name.Format("KolamImages\\%s.jpg", m_strFileTitle); 
			//	memDC.SaveJPEG(m_imageD_F_Name); 	//saveImage(0); 
			//} else 
			if( trce == 3 && loopNo == m_loopNum-1)	 // saving the last color still image
			{	
				MessageBeep(MB_ICONEXCLAMATION);
				stilImage = 0;  // trce = 0; saveImg =0; OFF save image どこでOFFにするか？
				m_imageD_F_Name.Format("KolamImages\\%s-C.jpg", m_strFileTitle); 
				memDC.SaveJPEG(m_imageD_F_Name); 	//saveImage(0); 
			}			
		}//endof if(stilImage			
		
		if( animImage == 1 && (m_smoothmod ==0 && trce ==2 || m_smoothmod ==1 && trce ==3 || m_smoothmod ==2 && trce ==3) )  
		{													//ここのtrce　の選択が違うのは？
			animImage = 0; 	stilImage = 0; iani = 0; // reset file number
			trce = 0;  
		} // to end while(trce

		if(m_slpt > 0 && m_komaNoX*m_komaNoY >24) m_slpt =1; else m_slpt = m_wndParam.m_SleepTime/2;

		if( trce == 3 && m_loopNum == 0) { trce = 0; fnlimg = 1; } // to end while(trce  // 2009/11/28 keeping the finalline image 
		else if(trce == 3 && loopNo < m_loopNum) 
		{ 
			trce = 2; loopNo++; //
			if(loopNo == m_loopNum) {	strtedg = strtedgback;//knap = sttKoma; 
										trce = 0; fnlimg = 1; break; }
		} //2011/05/01 for multiloop OK??
	}//endof while(trce >0 && trce <3)  for tracing in m_drawMode Koma


    //drawing  N-lines navigating a koma connected to another koma 
	if( drwNln > 0 )// Input Key "N" 2011/03/08 AutoGeneration では使わない
	{	
		short kna = 0, knxt;
		while(TRUE)// break, if( ++kna == m_komaNoX*m_komaNoY)
		{
			int knx = kna%m_komaNoX;	//koma position in number in x-axis
			int kny = kna/m_komaNoX;	//koma position in number in y-axis		
			int kend = kna; // ending koma number for navigating line
			int centx = (int)(m_kks*(0.5+knx)) +offstx;
			int centy = (int)(m_kks*(0.5+kny)) +offsty;
			for( edgn=0; edgn<4; edgn++)
			{	// edge number, digital order //edgn :edge number 0:right,1:bottom,2:left,3:top
			    short nindx = 0;
				if( m_koM[kna] > 0 ) sced = (m_koM[kna] >>edgn)%2 +(m_koM[kna] >>(4+edgn))%2 *2; //>>:bit shift, //sced:1 connecting edge
				else break;
				if(edgn ==0 )
				{	knxt =(knx+1) +kny*m_komaNoX; //right koma from koma[kna]
						if( m_koM[knxt] >0 && (knx+1 <m_komaNoX) )
							if( (sced == 1 && (m_koM[knxt] >>2)%2) ||	//connect to right koma
							    (sced == 2 && (m_koM[knxt] >>(4+2))%2) ) nindx =1; //or two point crossing
				} else if(edgn ==1 )
				{ 	knxt =knx +(kny+1)*m_komaNoX; //bottom koma from koma[kna]
						if( m_koM[knxt] >0 && (kny+1 <m_komaNoY) )
							if( (sced == 1 && (m_koM[knxt] >>3)%2) ||	//connect to bottom 
							    (sced == 2 && (m_koM[knxt] >>(4+3))%2) ) nindx =1; //or two point crossing
/*　// edge=2,3は片側同じであるので不必要
　				} else if(edgn ==2 )
				{	knxt =(knx-1) +kny*m_komaNoX; //left koma from koma[kna] 
						if( m_koM[knxt] >0 && (knx-1 >-1) )
							if( (sced == 1 && (m_koM[knxt] >>0)%2) ||	//connect to left 
							    (sced == 2 && (m_koM[knxt] >>(4+0))%2) ) nindx =1; //or two point crossing
				} else if(edgn ==3 )
				{	knxt =knx +(kny-1)*m_komaNoX; //upper koma from koma[kna] 
						if( m_koM[knxt] >0 && (kny-1 >-1) )
							if( (sced == 1 && (m_koM[knxt] >>1)%2) ||	//connect to upper 
							    (sced == 2 && (m_koM[knxt] >>(4+1))%2) ) nindx =1; //or two point crossing
*/				}//endof if(edgn
				if( nindx == 1 )
				{ 
				  memDC.MoveTo( centx,  centy);//x3 = centx; //y3 = centy;// set starting point 
				  short knxq = knxt%m_komaNoX;	//koma position number in x-axis
				  short knyq = knxt/m_komaNoX;	//koma position number in y-axis
				  x4 = (int)(m_kks*(0.5+knxq)) +offstx;
				  y4 = (int)(m_kks*(0.5+knyq)) +offsty; 
				  if( sced == 1 ){      memDC.SelectObject(&blackSPen); }// to make a solid line to the crossing connected KoMa
				  else if( sced == 2 ){ memDC.SelectObject(&blackSDPen);}// 2013/03/10 add to make a broken line for two point connectings
				  memDC.LineTo( x4,  y4);
				}// endof if( nindx
			}// endof for( edgn
			if( ++kna == m_komaNoX*m_komaNoY) break;  // all kolam koma were processed
		}//endof while(
		dc.BitBlt(0, 0, m_imageSiH, m_imageSiV, &memDC, 0, 0, SRCCOPY);// not only Kolam Area added to Y 50
		if(stilImage == 1)// saving the final still image
		{		// Key"I" before drawing "S" or "W" 
				stilImage = 0;	//saveImg =0; OFF save image
				MessageBeep(MB_ICONEXCLAMATION); 
				m_imageD_F_Name.Format("KolamImages\\%s-N.jpg", m_strFileTitle); 
				memDC.SaveJPEG(m_imageD_F_Name); 	//saveImage(0); 
		}	// else for one more to trace backward
		//drwNln = 1; removed for drwNln=2 after setting an area
	}// endof if(drwNln

	// writing memo and saveing the SingleKolam data at AutoGeneration 
	if( animImage == 1 )
	{
			str.Format("Key S:save Animation, on %s-a000.jpg", m_strFileTitle);
			dc.TextOut( 0, 12, str);  //the text is not drawn in the saved image, only on the window
	} else 	if( stilImage == 1 )
	{
			str.Format("Key S:save StillImage, on %s.jpg", m_strFileTitle);
			dc.TextOut( 0, 12, str);  //the text is not drawn in the saved image, only on the window
	} else if( !m_drawMode) // KoMa mode
	{	// checking the hitofude one-string drawing succeed 
		// index hitofude succeed as a string runs around all KoMas > 0 of 4 strings
		int numKoma = 0;
		for ( int ink = 0; ink < m_komaNoX*m_komaNoY; ink++) if( m_koM[ink] > 0) numKoma++;
		int strgall = 0;  
		for ( int chan =0; chan < m_chnNo[m_fudeNum] +1; chan++) 
	                            strgall = strgall + m_numEdges[m_fudeNum][chan]; // fude number:m_fudeNum =1
		if( numKoma > 1 && strgall == numKoma*4 ) m_hitosccd = 1; else m_hitosccd = 0;

		if( !bAutog ) //== FALSE
		{ 	

			if( m_smoothmod ==0)		str  = " Fude-Mode Smooth ";
			else if( m_smoothmod ==1)	str  = " Fude-Mode NonSmooth ";
			else if( m_smoothmod ==2)	str  = " Fude-Mode Outline ";
			dc.TextOut( m_imageSiH, 30, str); 
 									
			if( fnlimg ) //== 1 
			{
			  if( m_hitosccd )	str  = " SingleCycle/Knot                    　 ";//== 1
//			  else					str  = " MultiCycle/Link,Key　W:　anotherloop ";
			  else					str.Format(" MultiLoop,Key W:add to loop=%2d", m_loopNum);
            } else					str  = " Single/ Multi-Cycle?                 　"; 
			dc.TextOut( m_imageSiH, 50, str); 

			     if( m_gemod == 0)  str =" geneMode:Sequence      ";
			else if( m_gemod == 1)	str =" geneMode:Rand V&H Sym ";
			else if( m_gemod == 2)	str =" geneMode:Rand Rot Sym ";
			else if( m_gemod == 3)	str =" geneMode:Recursive     ";
			dc.TextOut( m_imageSiH, 70, str); 
			
			//if( prsntedg < -1) //out of the window
			//{	
				//str.Format("Key S:start/stop trace at dot");
				//dc.TextOut( 0, 12, str); 
				//str.Format("Key A:1:cross/2:turnIn/0:Out3 at edge");
				//dc.TextOut( 0, 30, str);
			//} 
		} else if( bAutog ) //== TRUE,  auto-generation 
		{ 	 
 			CString strM;  //2012/06/01	static を除いてもOK,　ここOnPaintのこのときだけ使用
			if( m_hitosccd ) //== 1　hitofude single loop
			{	// 保存モードではpimは初めの櫛型SingleまでのMultiを無視、計数されない。
				// 2011/6/10　この方法でなく、KoMa=0が無い条件数pio＝Multi数pim + Single数pis から逆算する
				pis++;	pim = pio - pis;
				if(m_ednum >32)
						str.Format("%d/over2^%d, Sgl %d Mlt %d  ", pia, m_ednum, pis, pim);
				else	str.Format("%d/%d, Sgl %d Mlt %d  ", pia, m_edpnm, pis, pim);//, pio%d, pio
				dc.TextOut( 0, m_imageSiV, str);//画像下の外に表示
				memDC.TextOut( 0, -1, str); //画像内上に表示
				dc.BitBlt(0, 0, m_imageSiH, m_imageSiV, &memDC, 0, 0, SRCCOPY);// not only Kolam Area added to Y 50
				if( m_saveDatafl ) //== 1 
				{
					strM = m_strPathFileName;
					strM = strM.Left( strM.ReverseFind( '.' ) );
					m_imageD_F_Name.Format("%s-%d.jpg", strM, pis); 
					memDC.SaveJPEG(m_imageD_F_Name);	//saveImage(ii++);		
					str.Format("%s-%d.txt", strM, pis); 
					saveDatafile( str, m_strFileTitle);
				}   
			} // else 最後でも一筆あり   
			if( m_alledge ) //== 1  the last pattern,all edges m_edcd[ all] = 1
			{	
				if(m_ednum >32)
						str.Format("%d/over2^%d, Sgl %d Mlt %d  ", pia, m_ednum, pis, pim);
				else	str.Format("%d/%d, Sgl %d Mlt %d  ", pia, m_edpnm, pis, pim);//, pio%d, pio
				dc.TextOut( 0, m_imageSiV, str);//画像下の外に表示
				memDC.TextOut( 0, -1, str); //画像内上に表示
				dc.BitBlt(0, 0, m_imageSiH, m_imageSiV, &memDC, 0, 0, SRCCOPY);// not only Kolam Area added to Y 50
				//if( m_saveDatafl )//== 1 
				//{ //最後だから　OnSaveImagesData()でも Autogenerationのみの場合でもいずれも動作させる　
					//最後の発生数を記録する 画像に残る
				strM = m_strPathFileName; // autoGnen のときは　saveDataflで既に最後にここをとおり初期化されている
				if(strM == "") strM.Format("KolamImages\\KoMa-%s",m_wndParam.m_ImageName);
				else           strM = strM.Left( strM.ReverseFind( '.' ) );
				m_imageD_F_Name.Format("%s-All.jpg", strM); 
				memDC.SaveJPEG(m_imageD_F_Name); 
				str.Format("%s-All.txt", strM ); 
				saveDatafile( str, m_strFileTitle);

				m_strPathFileName.Format("");
				m_saveDatafl = 0;
				m_alledge = 0;
				bAutog = FALSE; //to unstop auto generation by Key G again
			} // endof if( m_alledge == 1 at the last 
		} 	// end of if( bAutog == TRUE )	
	} else if( prsntedg == -100) //Mouse out of Window/Tile area in ChainMode
	{	// write instruction messages and chain data 
		str.Format("Key0:arc/Key1:line,KeyS:atGreenDot with RedEdge,to startTrace,KeyS:atRedDot,to changeStartPoint");
		dc.TextOut(0, 7, str);  //the text is not saved in the image
		str.Format("KeyQ at anyDot,to break&Divide in sameFude-chain,Shift+Q:to add previousChain in sameFude"); 
		dc.TextOut(0, 29, str);
		str.Format("KeyShift+S:atAnyDot,to add a newFude and changeStartPoint,X:to delete&Back"); 
		dc.TextOut(0, 51, str);
		int strYp = 52;
		for( int nfu = 0; nfu < m_fudeNum +1; nfu++)
		{	// draw multi-fude(stroke)
			for( int nchn = 0;  nchn < m_chnNo[nfu] +1; nchn++)
			{
					if(nchn ==10)
					{	str.Format(" neglect 11-%2d chains",  m_chnNo[0]+1); 
						strYp = strYp +19;		
						dc.TextOut( 0, strYp, str); break;
					} else 
					{	
//						str.Format("ChainMax232-32,%2d-%2d-%2d-%2d,", m_fudeNum+1, nfu+1, nchn+1, m_numEdges[nfu][nchn]); 
						str.Format("ChainMax232-32,%2d-%2d-%2d,", nfu+1, nchn+1, m_numEdges[nfu][nchn]); 
						// nfu+1 = the ordering number from m_fudeNum+1 
						for(int nmch = m_numEdges[nfu][nchn] -1; nmch > -1; nmch--) 
								str += (m_edgeChain[nfu][nchn] >>nmch) & 1? "1" : "0";
						str += "-";
						strYp = strYp +19;		
						dc.TextOut( 0, strYp, str);
					}
				} //endof for( int nchn
			} //endof for( int nfu
			dc.TextOut( 0, strYp+20, m_memo); //data of repeatSequence()
	} //endof if( stilImage ==1 else
	
	// ParameteDialog OK Buttonがないので効かない, nagata
	m_wndParam.m_KomaType = 99; //画面上変化を維持するために８１以上の数値に。９を打つと即実行９＝HorseSaddleとおなじ
								//負を正数の後書き込む
/*　2009/10/20 重なったところが消えるのを避ける
	Invalidate(FALSE);// show only the last image nagata 	
	// Do not call in the original Why?? for painting messages
	CWnd::OnPaint(); // CChildView:: 
*/
}// endof void CChildView::OnPaint() ////////////////////////////


/* Sound for MessageBeep()
    Beep(262, 500);  // ド    Beep(294, 500);  // レ    Beep(330, 500);  // ミ
    Beep(349, 500);  // ファ  Beep(392, 500);  // ソ    Beep(440, 500);  // ラ
    Beep(494, 500);  // シ    Beep(523, 500);  // ド
てつや＞#include <mmsystem.h>を追加し、winmm.lib をリンクしてください。
//Sound wavファイルをリソースに追加します。
::PlaySound(MAKEINTRESOURCE(IDR_WAVE //リソース名//),::AfxGetApp()->m_hInstance,SND_RESOURCE) ;　
PlaySound(MAKEINTRESOURCE(IDR_WAVE //リソース名//), AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC) ;
> 現行MessageBeep()；となっている所には何と書きますか
> XX();
> でしょうか？
シャノンさん> PlaySound に SND_ASYNC フラグを指定してやれば、スレッド立てなくても鳴りませんか？
シャノンさんの意見を参考にすると、
PlaySound(MAKEINTRESOURCE(IDR_WAVE //リソース名//), AfxGetApp()->m_hInstance,SND_RESOURCE|SND_ASYNC) ;
となります。
てつや＞	音が終わるまで次の処理はされませんから、私は以下の様にスレッド
	で音を出してます。
UINT DoWav(LPVOID pParam)	//スレッド関数
{	 ::PlaySound(MAKEINTRESOURCE(IDR_WAVE),::AfxGetApp()->m_hInstance,SND_RESOURCE) ;
   //::は省略してもかまいません。その関数がグローバルである事を明示しているだけです
  return 0 ;
}
void CXX::OnXX()
{
   ::AfxBeginThread(DoWav,this) ;
} 
*/
/* sample
#include <stdio.h>
 FILE *stream;
void main( void )
{
   long lg;
   float fp;
   char s[81];
   char c;
   int result;
   stream = fopen( "fscanf.out", "w+" );
   if( stream == NULL ) printf( "ファイル fscanf.out を開けません。\n" );
   else
   {
      fprintf( stream, "%s %ld %f%c", "a-文字列", 65000, 3.14159, 'x' );
      fseek( stream, 0L, SEEK_SET ); // ファイルの先頭にファイル ポインタを設定 
      fscanf( stream, "%s", s ); // ファイルからデータを読み出す 
      fscanf( stream, "%ld", &l );
      fscanf( stream, "%f", &fp );
      fscanf( stream, "%c", &c );
      printf( "%s\n", s );  // 読み出したデータの表示
      printf( "%ld\n", lg );
      printf( "%f\n", fp );
      printf( "%c\n", c );

  fclose( stream );
   }
}
 // an other sample
派生クラスのメンバ変数に CEditEngine m_ee; 
  m_ee.removeAll();       //  エディットバッファをクリア

if( !fp )  return FALSE;
    char buf[4096];
    while( fgets(buf, sizeof(buf), fp) != NULL )  m_ee.addText(buf);
    fclose(fp);
    return TRUE;

	// CStdioFile::WriteString の例
	extern CStdioFile f;
	char buf[ m_chnNo[0] ] = "test string";

	f.WriteString( buf );
	
	// CStdioFile::ReadString の例
	extern CStdioFile f;
	char buf[100];
	f.ReadString( buf, 99 );

//////////////////////
*/
//	m_paramDlg.m_ImageFileName = fileDlg.GetFileName();// to read only the filename
//	m_paramDlg.m_ImageFileName = fileDlg.GetPathName();// to read the filename including the path
//	if(strcmp(string, "value") == 0) { /* 文字列が"value"と一致した	... }

// http://www.kouno.jp/home/c_faq/c8.html for charcter operation
// open KolamKoma array data file in TXT format
/*
int parse(const CString& line, CStringArray& result) {
  result.RemoveAll();
  CString token;
  int pos = 0;
  while ( (token = line.Tokenize(" ,", pos)) != "" ) {
    result.Add(token);
  }
  return result.GetSize();
}
*/

static char BASED_CODE szFilter[] = "Text Files(*.txt), use (PrintImage) for printing Image|*.txt|";

void CChildView::OnOpenKomaFile()	// open Tile-KomaFile or Edge-ChainFile in TXT format
{	// TODO: Add your command handler code here

	int clGR, clGG, clGB, clTR, clTG, clTB, clAR, clAG, clAB, clFR, clFG, clFB; //colorData
	int clR, clG, clB;
	int colorData = 0, MultiLoop = 0;
	
	// ここにWindowで選択するようにする
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_NOCHANGEDIR, szFilter, this /*AfxGetMainWnd()*/);

	// if (fileDlg.DoModal() == IDOK) // コメントアウト
	if (HookFileDialogDoModal(&fileDlg) == IDOK)// 日本語->英語置換ファイルダイアログ
	{	

 		char fname[30], buf[201], dats[9]; // 200 < 4 char x 50 KoMa in a line
		int size, xno, yno; //, dat; long pntpos;
		int kna = 0;	int io = 0;		int fudex = 0;
		for( int ii = 0; ii < 1850; ii++)  m_koM[ii] = short int( 0x8000); //-1 & ~0xFF;
		//memset(m_koM, -1 & ~0xFF, sizeof(m_koM) );
		m_loopNum = 0;

		CStdioFile ftxt;	// for read a text file 
		CString cStrng;
		m_strPathFileName = fileDlg.GetPathName();//ディレクトリ、ファイル名を含めフルパス名

//		m_strFileName = fileDlg.GetFileName(); //GetFileNameは、拡張子付きのファイル名を返します。
//		m_strFileName.Left( m_strFileName.Find('.'); //m_paramDlg.m_ImageFileName = m_strFileName;
//		m_paramDlg.m_ImageFileName = 
		m_strFileTitle = fileDlg.GetFileTitle(); //GetFileTitle は、拡張子を除いたファイル名を返します。	

		//FILE *pf = fopen(fileDlg.GetPathName(),"r"); 
		//if( !pf ) printf( "Sorry but the file %s could not be opened !\n", fileDlg.GetPathName() );
		ftxt.Open( m_strPathFileName, CFile::modeRead | CFile::typeText );
 
		while( ftxt.ReadString( buf, 200 ) )
		{
			cStrng = buf;	cStrng = cStrng.Left(6);
			if( buf[0] == '#' ) 
			{
				if( cStrng == "# KoMa"){		m_drawMode = 0; continue;} // get KoMa type data
				else if( cStrng == "# Edge"){	m_drawMode = 1; fudex = 0; continue;} // get Edge type data
				// 2009/11/22 ColorData を
				else if( cStrng == "# Colo"){	colorData = 1; continue;}
				// 2011/05/01 MultiLoop を
				else if( cStrng == "# Mult"){	MultiLoop = 1; fudex = 0; continue;}
				else 			                               continue;						 
			} else if( io == 0 ) // first data-line
			{
				io++;  
				sscanf( buf, "%d, %d, %d, %s %s", &size, &xno, &yno, fname, dats); // char[]のとき、','は不要
				m_wndParam.m_ImageSizWidth = size;
				m_wndParam.m_KomaX_N = m_komaNoX = xno;
				m_wndParam.m_KomaY_M = m_komaNoY = yno;
				m_wndParam.m_KomaSize = m_kks	 = size / xno;
				m_imageSiH = m_kks *m_komaNoX +45;  // size of image area m_paramDlg.m_ImageSizWidth; //450
				m_imageSiV = m_kks *m_komaNoY +70;  // size of image area  					//m_cdate = dats; ////m_cdate for print to check
				m_ednum = m_komaNoX*m_komaNoY*2 - m_komaNoX - m_komaNoY;
				m_edpnm = (unsigned long)pow( 2.0, m_ednum ) -1; // index edge patterns, except all of 0
				cri = (int)(m_kks/2.0*1.41421356/2.0); // circle radius of the arc	
				pri = (int)(1+ m_kks/2.0*1.41421356/20.0); // circle radius of the dot/pulli  
				whd =  m_kks/5;		//nWidth,nHeight 角の丸みの楕円形の幅と高さ

				CString cFname = fname; //　CString にコピーする //int pos = cFname.Find(',');// ','の位置を知る
//				m_wndParam.m_ImageFileName = cFname.Left( cFname.Find(',') ); // .TrimRight(','); 文字",”を除く
				m_wndParam.m_ImageName = cFname.Left( cFname.Find(',') ); // .TrimRight(','); 文字",”を除く
				m_wndParam.UpdateData(false); // 2009/11/4 for sending the data to Dialog 
				m_strImgName = m_wndParam.m_ImageName;// 2009/11/30 ImageNameを単独にする 
			} else if(colorData == 1)// 2009/11/22 ColorData を
			{	
				sscanf( buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", &clGR, &clGG, &clGB, &clTR, &clTG, &clTB, &clAR, &clAG, &clAB, &clFR, &clFG, &clFB); // 
				m_grdColor = RGB(clGR, clGG, clGB);
				m_tilColor = RGB(clTR, clTG, clTB);
				m_amiColor = RGB(clAR, clAG, clAB);
				m_fnlColor = RGB(clFR, clFG, clFB);
				m_wndParam.m_BtnGColor.SetColor(m_grdColor);
				m_wndParam.m_BtnTColor.SetColor(m_tilColor);
				m_wndParam.m_BtnAColor.SetColor(m_amiColor);
				m_wndParam.m_BtnFColor.SetColor(m_fnlColor);
				m_wndParam.m_SwellMode = m_swell = 3;
				m_wndParam.UpdateData(false); // 2009/11/4 for sending the data to Dialog 
				colorData = 0;	
			} else if(MultiLoop == 1)// // 2011/05/01 MultiLoop を
			{	
				int KomaX,KomaY;	
				sscanf( buf, "%d-%d, %d, %d, %d, %d, %d, %d", &m_loopNum, &fudex, &KomaX, &KomaY, &m_strtSide[fudex], &clFR, &clFG, &clFB); // 
//				sscanf( buf, "%d, %d, %d, %d, %d, %d, %d", &m_loopNum, &KomaX, &KomaY, &m_strtSide[fudex], &clFR, &clFG, &clFB); // 
//				version 4.4.4 　KoMaのMulitLoopのFormat
				m_strtKoma[fudex-1] = KomaX + KomaY*m_komaNoX;
				m_loopColor[fudex-1] = RGB(clFR, clFG, clFB);
				m_wndParam.m_BtnFColor.SetColor(m_loopColor[fudex-1]);
				m_wndParam.m_SwellMode = m_swell = 3;
				m_wndParam.UpdateData(false); // 2009/11/4 for sending the data to Dialog 
				if(m_loopNum == fudex) MultiLoop = 0;
			} else // if( io > 0 && colorData == 0)
			{ // following data-lines
			   cStrng = buf; // convert a buf to a cStrng
			  if( m_drawMode == 0 )// get KoMa type data
			  { 
				//cStrng = cStrng.Right( 4 * xno );	//old file 同じ操作cStrng.Mid( cStrng.Find("-,") +2, 4*xno +1 ) ; // 文字"-,”より後の文字列を読み出す
				cStrng = cStrng.Right( 3*xno +1); //get rightpart of 3*xno +1(NuLL) chars from the end　	
				int ix = 1;
				while( TRUE )
				{ 
					//int pos = cStrng.Find(','); 
					//CString cNum = cStrng.Left( pos );	//初めの','より左・前の数文字列を取り出す
					CString cNum = cStrng.Left( cStrng.Find(',') );	//初めの','より左・前の数文字列を取り出す
					//m_koM[kna] = atol(cNum); //atoi(tokens.GetAt(0)); // = atoi(buf); //cNum.Format("%d", m_koM[kna++] ); 						
					short int komm = (short)atol(cNum);
					if( komm < 0) m_koM[kna] = short int( 0x8000); else  m_koM[kna] = m_N81toE8B[ atol(cNum) ];
					//if( m_koM[kna] < 0) m_koM[kna] = short int( 0x8000); //-1 & ~0xFF;
					kna++;
						//if( ix < xno)	cStrng = cStrng.Mid( pos +1, 4*(xno -ix) +1 ); //old file, m_cdate = cStrng; //','より後の数文字列を取り出す、next String
					if( ix < xno) 
					{ 
						cStrng = cStrng.Right( 3*(xno -ix)+1); 
						ix++;
					}   else	break; 
				} // endof while( 
			  }	else if( m_drawMode == 1)   //get edgeChain data
			  {  
				/*	old format version 
				if( io == 1 )
				{  io++; // for the second line
					int side, dirct;
					sscanf( buf, "%d, %d, %d, %d", &m_startChainX[0], &m_startChainY[0], &side, &dirct);					
					m_startSide[0]   = side*2 + dirct; //= m_startSideKoMa 
					m_fudeNum = 0; //the first one 
				} else 
				{	//	if( io > 1 
					m_chnNo[m_fudeNum] = io -2;		io++;  
					int pos = cStrng.Find('-'); 
					CString cNum = cStrng.Mid( pos+1, 2); 
					m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ] = atol(cNum);  
					cStrng = cStrng.Right( 2 *m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ] +1 ); //m_cdate =m_cdate +cStrng;//m_cdate for print to check
				*/
			
				///* new format since 2005/09/10
					int pos = cStrng.Find(','); 
//					if( pos == 2 || pos == 1) // Fude condition data line "\n01" or old Format"\n1", 
					if( pos == 2 ) // Fude condition data line "\n01", 
					{   
						io = 2;	clR = clG = clB = 0;
//						sscanf( buf, "%d, %d, %d, %d", &m_fudeNum, &m_startChainX[fudex], &m_startChainY[fudex], &m_startSide[fudex]);					
						sscanf( buf, "%d, %d, %d, %d, %d, %d, %d", &m_fudeNum, &m_startChainX[fudex], &m_startChainY[fudex], &m_startSide[fudex], &clR, &clG, &clB);					
						m_startChainXFile[fudex] = m_startChainX[fudex];
						m_startChainYFile[fudex] = m_startChainY[fudex];
						m_startSideFile[fudex]	 = m_startSide[fudex];
						if(clR == 0 && clG == 0 && clB == 0){ m_loopNum = 0;}// BlackColor
						else {
							m_strtKoma[fudex] = m_startChainX[fudex] + m_startChainY[fudex]*m_komaNoX;
							m_strtSide[fudex] = m_startSide[fudex];
							m_loopColor[fudex] = RGB(clR, clG, clB);
							m_loopNum = m_fudeNum;
						}
						m_fudeNum = m_fudeNum -1; // change 1-10 to 0-9 for Array[m_fudeNum]
						fudex++;  
					} else // chain data lines
					{	 
						m_chnNo[m_fudeNum] = io -2;	io++;  
						//pos = cStrng.Find('-'); 
						//CString cNum = cStrng.Mid( pos+1, 2); 
						CString cNum = cStrng.Mid( cStrng.Find('-') +1, 2); 	
						m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ] = (short)atol(cNum);  
						cStrng = cStrng.Right( 2 *m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ] +1 ); //m_cdate =m_cdate +cStrng;//m_cdate for print to check
				//*/
						int ix = 1; 
						while( TRUE ) 
						{
							pos = cStrng.Find(','); 
							cNum = cStrng.Left( pos );	//初めの','より左・前の数文字列を取り出す
							m_edgeChain[m_fudeNum][ m_chnNo[m_fudeNum] ] = (m_edgeChain[m_fudeNum][ m_chnNo[m_fudeNum] ]<<1) +atol(cNum);
							if( ix < m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ])	
							{
								cStrng = cStrng.Mid( pos +1, 2*(m_numEdges[m_fudeNum][ m_chnNo[m_fudeNum] ] -ix) +1 ); 
								ix++;
							} else	break;
						}//endof while(	
					}//endof if( io  else
			  }//endof if( m_drawMode else			
			} //endof if( io > 0 , else { 	
		} //endof while( ftxt.ReadString
		//fclose(pf);
	} //endof if (fileDlg.DoMod
	MessageBeep(MB_ICONEXCLAMATION); 
//	m_drawImages = TRUE;
	Invalidate(); // refresh the drawn image
}//endof void CChildView::OoOpenKomaFile
/////////////////////////

	//CStringArray tokens; // set an array 
	//tokens.Add(cNum); // CNum to tokens
	//初めの','より左・前の数文字列を取り出す
	//atoi(tokens.GetAt(0)); // = atoi(buf); 						
	//cNum.Format("%d", m_koM[kna++] );   
	/*tokens.RemoveAll();*/ 
	/*　//.h の付かないのは標準C++ライブラリのヘッダ　*/
/* Visual C++ 7.1
#include <afx.h>    // CStdioFile, CString, CStringArray
#include <iostream> // cout, endl
#include <cstdlib>  // atoi

int parse(const CString& line, CStringArray& result) {
  result.RemoveAll();
  CString token;
  int pos = 0;
  while ( (token = line.Tokenize(" ,", pos)) != "" ) {
    result.Add(token);
  }
  return result.GetSize();
}

int main() {
  int size;
  int xno;
  int yno;
  CString fname;
  CString dats;
  int k[1000];
  int rows = 0;
  int count = 0;
  CString line;
  bool header = true;
  CStringArray tokens;

  CStdioFile file("foo.txt", CFile::modeRead); // ファイルを食わす
  while ( file.ReadString(line) ) {
    if ( line[0] == '#' ) continue;
    int columns = parse(line, tokens);
    if ( header ) {
      header = false;
      size = std::atoi(tokens.GetAt(0));
      xno  = std::atoi(tokens.GetAt(1));
      yno  = std::atoi(tokens.GetAt(2));
      fname = tokens.GetAt(3);
      dats  = tokens.GetAt(4);

    } else {
      ++rows;
      for ( int i = 1; i < columns; ++i ) {
        k[count++] = std::atoi(tokens.GetAt(i));
      }
    }
  }
  /* 確認 
  std::cout << '#' << size 
            << '(' << xno << ',' << yno << ')' 
            << static_cast<const char*>(fname) << ' ' 
            << static_cast<const char*>(dats)
            << std::endl;

  std::cout << rows << " rows\n";
  for ( int i = 0; i < count; ++i ) {
    std::cout << k[i] << ' ';
  }
  return 0;
}
*/////////////////////////////////////////

// 書き込みファイルの予備名を自動的にDailogに書き出す
// txtが着けずに記述しても、自動的に追加する

void CChildView::saveDatafile( CString strPathFlName, CString strFileTtl)
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CString     strFileExt( "txt" );
	CString     strDir;
		//CString		strDrFlNm;
	CFileStatus fsOption;
	int  nFileIndex( 1 );	// nFileIndex = 1;
	while ( true ) /* to add (n) at the end of the same filename */
	{
		if ( !CFile::GetStatus( strPathFlName, fsOption ) )	break; 
		strDir.Format("%s", strPathFlName.Left( strPathFlName.ReverseFind( '\\' ) + 1 ) );
		nFileIndex++;
		strPathFlName.Format( "%s%s(%d).%s", strDir, strFileTtl, nFileIndex, strFileExt );
	}

	FILE *pf = fopen(strPathFlName,"a+"); 
	if( pf )
	{
//		CString fname = strFileTtl; // m_paramDlg.m_ImageFileName;
		CString fname = m_wndParam.m_ImageName;
		int size = m_wndParam.m_ImageSizWidth;
		int NoX	 = m_wndParam.m_KomaX_N; 
		int NoY	 = m_wndParam.m_KomaY_M; 
		fprintf( pf,"# ImageSize pixel, KomaXNo, KomaYNo, Image-Name, Date\n");
		fprintf( pf,"%10d, %10d, %10d, %20s, %8s\n", size, NoX, NoY, fname, m_cdate);
//2009/11/21 Colordata 		
		fprintf( pf,"# Color(R,G,B) of Ground, Tile, Anime-Line, Final-Line\n");
		clrRGB[0][0] = GetRValue(m_grdColor); 
		clrRGB[0][1] = GetGValue(m_grdColor);
		clrRGB[0][2] = GetBValue(m_grdColor);
		clrRGB[1][0] = GetRValue(m_tilColor);
		clrRGB[1][1] = GetGValue(m_tilColor);
		clrRGB[1][2] = GetBValue(m_tilColor);
		clrRGB[2][0] = GetRValue(m_amiColor);
		clrRGB[2][1] = GetGValue(m_amiColor);
		clrRGB[2][2] = GetBValue(m_amiColor);
		clrRGB[3][0] = GetRValue(m_fnlColor);
		clrRGB[3][1] = GetGValue(m_fnlColor);
		clrRGB[3][2] = GetBValue(m_fnlColor);//int clrRGB[4][3]; 
		for( int ic = 0; ic<3; ic++) fprintf( pf," %03d,", clrRGB[0][ic]);
		for(     ic = 0; ic<3; ic++) fprintf( pf," %03d,", clrRGB[1][ic]);
		for(     ic = 0; ic<3; ic++) fprintf( pf," %03d,", clrRGB[2][ic]);
		for(     ic = 0; ic<3; ic++) fprintf( pf," %03d,", clrRGB[3][ic]);
		fprintf( pf,"\n" ); 	

		if( !m_drawMode ) // KoMa mode
		{			
		  if( m_loopNum > 0 )/* here writing multi-loop data */
		  {
			fprintf( pf,"# This KomaMode multi-loop format is new since 2011/05/01/,09/09/30\n");
			fprintf( pf,"# MultiLoopNum<max10, StartX, Y, Side*2+Direct,Color(R,G,B)\n"); 
			for( int nfu = 0; nfu < m_loopNum; nfu++)
			{	
				fprintf( pf,"%02d-%02d, %02d, %02d, %02d,", m_loopNum, nfu +1, m_strtKoma[nfu]%m_komaNoX, m_strtKoma[nfu]/m_komaNoX, m_strtSide[nfu]);
				clrRGB[3][0] = GetRValue(m_loopColor[nfu]);
				clrRGB[3][1] = GetGValue(m_loopColor[nfu]);
				clrRGB[3][2] = GetBValue(m_loopColor[nfu]);
				for( int ic = 0; ic<3; ic++) fprintf( pf," %03d,", clrRGB[3][ic]);
				fprintf( pf,"\n" ); 			
			} // endof for( int nfu
		  } // endof if( m_loopNum 

			if( bAutog == TRUE ){ 
				if(m_ednum >32)
					 fprintf( pf,"# Autogeneration KoMaArray Single %d Multi %d allover2^%d\n", pis, pim, m_ednum);
				else fprintf( pf,"# Autogeneration KoMaArray Single %d Multi %d all %u\n", pis, pim, m_edpnm); 
			}
			fprintf( pf,"# KoMa Array Type in 10 digit with 3 statuses \n"); 
			fprintf( pf,"#V-H");
			for( int knx=0; knx <NoX; knx++) fprintf(pf,"%02d ", knx); //X-number 印刷でずらさないため
					fprintf( pf,"\n");
			for( int kny=0; kny <NoY; kny++)//Y-number 
			{		
				fprintf(pf," %02d-, ",  kny); //Y-number
				for( int knx=0; knx <NoX; knx++)//X-number
				{  
					int kna =knx +kny*NoX;
					if( m_koM[kna] < 0 ) fprintf(pf,"%02d,", -1 ); //m_koM[kna] ); 	
					else fprintf(pf,"%02d,", m_E8BtoN81[ m_koM[kna] ] );//m_koM[kna] ); 	
						// short int m_N81toE8B[81];  // 8bit number= N81toE8B[0-80 number];
						// short int m_E8BtoN81[241];  // 0-80 number= E8BtoN81[8bit number Max 240];
				}
				fprintf( pf,"\n" ); 	
			}// endof for( int kny=0;
			fprintf( pf,"#\n" ); 	
		} else //endof if( !m_drawmode KoMa mode,
		{	// Chain mode
			CString str; 
			fprintf( pf,"# Edge ChainMode.This format is new since 2005/09/10/,09/09/30,11/8/10\n");// 先頭のEdgeは必要

			if(m_loopNum > 0) m_fudeNum = m_loopNum -1; //m_fudeNum は既に本数よりー１である。
			fprintf( pf,"# ChainFudeNo<max10, StartX, Y, Side*2+Direct,if loops,Color(R,G,B)\n"); 
			fprintf( pf,"# ChainNo<max232-EdgeNumber, Edgedata<max32\n");
			fprintf( pf,"# 3 largest sequence-autoCoEfficiencies with shiftLength\n" );
			for( int nfu = 0; nfu < m_fudeNum +1; nfu++)
			{	// m_fudeNum は既にfude数よりー１である。検討済み　nfu = 0から始まるから　<m_fudeNum +1ではなく　< m_fudeNumではないか　
				fprintf( pf,"%02d, %02d, %02d, %02d,", nfu +1, m_startChainX[nfu], m_startChainY[nfu], m_startSide[nfu]);
				if( m_loopNum > 0 )/* here writing multi-loop data */
				{
					clrRGB[3][0] = GetRValue(m_loopColor[nfu]);
					clrRGB[3][1] = GetGValue(m_loopColor[nfu]);
					clrRGB[3][2] = GetBValue(m_loopColor[nfu]);
				if(clrRGB[3][0] == 0 && clrRGB[3][1] == 0 && clrRGB[3][2] == 0) clrRGB[3][0] = clrRGB[3][1] = clrRGB[3][2] = 1;//Blackは読むとき無視される
					for( int ic = 0; ic<3; ic++) fprintf( pf," %03d,", clrRGB[3][ic]);
				 } // endof for( m_loopNum and color-data
				fprintf( pf,"\n" ); 			
				for( int nchn =0; nchn < m_chnNo[nfu] +1; nchn++)
				{
					str.Format("%03d-%02d, ", nchn +1, m_numEdges[nfu][nchn]); 
					for (int nmch = m_numEdges[nfu][nchn] -1; nmch > -1; nmch--)
						str += (m_edgeChain[nfu][nchn] >>nmch) & 1? "1," : "0,";
						fprintf( pf,"%s\n", str);
				}//endof for ( int nchn
				fprintf( pf,"# AllEdges of %5d, ", suNo);
				for (int i=0; i<3; i++)
				{	if (repCoeff[i] == 0) break; 
					else fprintf( pf," %5.3fwith%d,", repCoeff[i], repLength[i] );
				}
				fprintf( pf,"\n" );  	
			} // endof for( int nfu
		    fprintf( pf,"#\n" ); 
		} // endof else of if( !m_drawmode
	}// endof if(pf) 
	fclose(pf);	
}	// endof void CChildView::saveDatafile(


void CChildView::OnSaveKomaFile()	// Save Tile-Koma or Edge-Chain datafile in TXT format
{		
	// TODO: Add your command handler code here
//	CString fname = m_wndParam.m_ImageFileName; // data from DialogEditBox
	CString fname = m_wndParam.m_ImageName; // data from DialogEditBox
	CString fnmdat;
	if( m_drawMode == 0) fnmdat= "KoMa-" + fname; else  fnmdat= "Chain-" + fname; 

	CreateDirectory("KolamImages", NULL);//2009/11/7 Holder"KolamImages" が既存でないときは作成

	//ここにWindowで選択するようにする	//CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_NOCHANGEDIR, szFilter, this);
	CFileDialog fileDlg( FALSE, "txt", fnmdat, OFN_HIDEREADONLY | OFN_NOCHANGEDIR, szFilter, this /*AfxGetMainWnd()*/ );
	// if (fileDlg.DoModal() == IDOK) // コメントアウト
	if (HookFileDialogDoModal(&fileDlg) == IDOK)// 日本語->英語置換ファイルダイアログ
	{
		// add (n) to the end of the same fileName 
		m_strPathFileName = fileDlg.GetPathName();	//ディレクトリ、ファイル名を含め、フル パス名を取り出します
		m_strFileName = fileDlg.GetFileName();		//GetFileName は、拡張子付きのファイル名を返します。
		m_strFileTitle = fileDlg.GetFileTitle();	//GetFileTitle は、拡張子を除いたファイル名を返します。
		//	CString     strFileExt( fileDlg.GetFileExt() ); //	same as CString	strFileExt( "txt" );
		saveDatafile( m_strPathFileName, m_strFileTitle );
	}//endof if (fileDlg.DoModal()
	MessageBeep(MB_ICONEXCLAMATION); 
}//endof void CChildView::OnSaveKomaFile

		
/*	// Ct is Sigma{ x1*x(1+shit) + x2*x(2+shift) +... xn*x(n+shift)+...+xN*x(N+shift) } /N,
	// where shift means is a shifting phase and #*#: NOT(XOR(#,#)).
	// and also when n+shift >N, "n+shift" changes "n+shift-N",
*/
/* 保存時の既存ファイル名と重なるとき　
一応ＭＦＣで書いてみました。パスの区切り文字は \ にしてあります。

  CFileDialog FileDlg(TRUE, "txt", "", OFN_HIDEREADONLY | OFN_NOCHANGEDIR, "テキストファイル(*.txt)|*.txt|" );

   if ( FileDlg.DoModal() == IDOK )
   {
       CString     strPathName( FileDlg.GetPathName() );
       CString     strFileTitle( FileDlg.GetFileTitle() );
       CString     strFileExt( FileDlg.GetFileExt() );
       CString     strDir( strPathName.Left( strPathName.ReverseFind( '\\' ) + 1 ) );
       CFileStatus fsOption;
       int         nFileIndex( 1 );

       while ( true )
       {
           if ( !CFile::GetStatus( strPathName, fsOption ) )
           {
               break;
           }
           nFileIndex++;
           strPathName.Format( "%s%s(%d).%s", strDir, strFileTitle, nFileIndex, strFileExt );
       }
       TRY
       {
           CStdioFile fStream( strPathName, CFile::modeWrite | CFile::modeCreate );
           // 書き込み処理
           fStream.Close();
       }
       CATCH ( CFileException, fe )
       {
       }
       END_CATCH
   } 

*/

	
/*		SetTimer(1, 1, NULL);  // (identifier, normal= not 0, time-out msecond, address of time procedure)
		SetTimer(2, 1, NULL);  // (identifier, normally return= not 0, time-out msecond, address of time procedure)		
		KillTimer(2);	// (identifier=2)
		WM_LBUTTONUP     CWnd::OnLButtonUp()
		ON_WM_LBUTTONUP( ) afx_msg void OnLButtonUp( UINT, CPoint ); 
		ON_WM_LBUTTONDBLCLK( ) afx_msg void OnLButtonDblClk( UINT, CPoint ); 		
		> DIMOUSESTATE が定義されているヘッダファイルは何ですか？
		> そのヘッダをインクルードしていますか？
//BOOL GetCursorPos(  LPPOINT lpPoint) 
//void ScreenToClient( LPPOINT lpPoint ) const;
//void ScreenToClient( LPRECT lpRect ) const;
//マウスクリック時カーソル座標よみとり
//　CWnd::On{L/R/M}Button{Down/Up}( UINT nFlags, CPoint point )
// afx_msg void On{L/R/M}Button{Down/Up} ( UINT nFlags, CPoint point );
*/
/*  void CChildView::OnTimer(UINT nIDEvent) 
{
	static int ClickHandledL;

	switch (nIDEvent) //nIDEVENT = the identifier of setTime(
	{
		case 1: 
			DIMOUSESTATE dims;
			if (!(dims.rgbButtons[0] & 0x80))  // clicking Left mouse		
			{			
				//if (m_mouseMode == MM_NORMAL) 
				//{
					if (ClickHandledL == TRUE) // when Off, Beep 
					{
						ClickHandledL = FALSE;  
						MessageBeep(MB_ICONEXCLAMATION); 
			connectDiscon( , , -1); // -1: toggle of connect or disconnect the edge with a cursol
			drwNln =1; // set N-lines 
//			m_drawImages = TRUE;
			Invalidate(FALSE);
					}
				//}
			}
	}//endof switch (
	CWnd::OnTimer(nIDEvent);
}//end of CChildView::OnTimer
*/

/* Sample
void CChildView::OnTimer(UINT nIDEvent)
{
 switch (nIDEvent)
 {
   case 10:
     KillTimer(10);
     geNeration( m_gemod);
     if( bAuto != FALSE )
     {
       SetTimer(10, n, null);
     }
     break;
 }
}
*/
void CChildView::OnTimer(UINT nIDEvent) // SetTimer(10,
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください

	CClientDC dc(this); // for dc.Texout
	CString	str; 
	switch (nIDEvent)
	{
		case 10:
			KillTimer(10);	//		OnKeyUp('G', 0, 0); //genarating pattern
			geNeration( m_gemod);   // 0:sequential,1:Verti&Hori Sym, Shift+:random, 2:Rotated Sym
			
			checkAll = 1;// checking if e]very KoMa > 0
			for( int inko = 0; inko < m_komaNoX*m_komaNoY; inko++) 
			{	if(m_koM[inko] < 1){	checkAll = 0;  break; } }// for using allKoma

			if( checkAll == 1)	// OnKeyUp('S', 0, 0); // to trace the pattern
			{	  
//			ここでは　Check=0は生じない　正常				
				pio++; 
				pim = pio - pis;//MultiNum pim = AllusingNum pio - SingleNum pis; //number of all KoMa connecting patterns  
				strtedg = 4;  //only left-4 or upper-6 edge at the last KoMa
				while(TRUE)// set strtedg: the starting point in the last m_koM[knap]の接続点で一筆開始する
				{		
					if( (m_koM[knap]>>strtedg/2) &1){ trce = 2; break; } //index of tracing hitofude
					strtedg +=2;
				}//endof while  
// 				m_drawImages = TRUE;
				Invalidate(FALSE);// void CChildView::OnPaint()が働く
			} // endof if(checkAll

			//if( m_saveDatafl == 1)
			//{
				if(m_ednum >32)
						str.Format("%d/over2^%d, S %d, M %d  ", pia, m_ednum, pis, pim);
				else	str.Format("%d/%u, S %d, M %d  ", pia, m_edpnm, pis, pim);//pio%d, , pio
				dc.TextOut( 0, m_imageSiV, str);// これはパターン毎に表示するため

			if( !m_alledge && bAutog ) //m_alledge == 0 bAutog == TRUE,non-final pattern. m_alledge = 1 all-edge connected pattern
			{
				SetTimer(10, TIMER_INTERVAL, NULL);
			} 
			break;
	}
	CWnd::OnTimer(nIDEvent);
}//endof CWnd::OnTimer

/*void CChildView::OnOk() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	//UpdateData(TRUE);
//	CParameterDlg ParaDlg; //nagata
	if(ParaDlg.DoModal() == IDOK) //nagata
	{
	}
	//MessageBeep(MB_ICONEXCLAMATION); // MessageBeep(0);
	//UpdateData(FALSE); // set the final action
}
*/


void CChildView::OnViewResetAll() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください

	for( int ii = 0; ii < 1850; ii++)  m_koM[ii] = short int( 0x8000); //-1 & ~0xFF;
	//memset(m_koM, -1 & ~0xFF, sizeof(m_koM) );// no-Pulli type, intialization // 指定された文字でバッファを初期化します
	for(     ii = 0; ii < 50; ii++)  for ( int iii =0; iii<37; iii++) m_koMxy[ii][iii] = short int( 0x8000); //-1 & ~0xFF;
	m_fudeNum = 0;  //the first one
	memset(m_edgeChain, 0, sizeof(m_edgeChain) ); // intialization
	memset(m_numEdges, 0, sizeof(m_numEdges) ); // intialization
	memset(m_chnNo, 0, sizeof(m_chnNo) ); // intialization
	memset(m_startChainX, 0, sizeof(m_startChainX) ); // intialization
	memset(m_startChainY, 0, sizeof(m_startChainY) ); // intialization
	memset(m_startSide, 0, sizeof(m_startSide) ); // intialization
	memset(m_startChainXFile, 0, sizeof(m_startChainXFile) ); // intialization
	memset(m_startChainYFile, 0, sizeof(m_startChainYFile) ); // intialization
	memset(m_startSideFile, 0, sizeof(m_startSideFile) ); // intialization

	m_loopNum = 0; // Number of Loops
	memset(m_strtKoma, 0, sizeof(m_strtKoma) ); // intialization
	memset(m_strtSide, 0, sizeof(m_strtSide) ); // intialization
	memset(m_edcd, 0, sizeof(m_edcd) ); // intialization

	bAutog = FALSE;// Key G for Auto generation
	pia = 0;	pim = 0;	pis = 0;	pio = 0;
	
	// no-Pulli type, intialization // 指定された文字でバッファを初期化します
	// memset(m_koMxy, 0, sizeof(m_koMxy) );// matrix data intialization //文字でなくても０の場合は０になる　０以外はNG
	m_komaNoX = m_wndParam.m_KomaX_N; // needs as the initial value for release version
	m_komaNoY = m_wndParam.m_KomaY_M;
	m_kks	= m_wndParam.m_ImageSizWidth / m_komaNoX; // pixel size of one KoMa 	
	m_ednum = m_komaNoX*m_komaNoY*2 -m_komaNoX-m_komaNoY;
	m_edpnm = (unsigned long)pow( 2.0, m_ednum ) -1; // index edge patterns, except all of 0

	CTime theTime = CTime::GetCurrentTime();	//日付を入れるby Abe 20030630
	m_cdate = theTime.Format("%y%m%d");			// "20%y%m%d"-%Mm");	

	srand( (unsigned)time( NULL ) );  //rand() == 0<->RAND_MAX(0x7fff=65536) の初期設定  

//	m_drawMode = 0;
	fnlimg = 0; 
	m_swell = 0;
	m_wndParam.m_SwellMode = m_swell;	// Dialog表示も戻す
	m_smoothmod = 0;
	m_gemod = 0;
	keyS_M = 0;
	prsntedg = -1;
	knap = 0;
//	m_strFileTitle = m_wndParam.m_ImageFileName;
	m_strFileTitle = m_wndParam.m_ImageName;
	iani = 0; // save file number
	m_wndParam.UpdateData(false); // 2009/11/4 for sending the data to Dialog 
//	m_drawImages = TRUE;
	Invalidate(FALSE);
}// endof void CChildView::OnViewResetAll() 

//2010/3/22
void CChildView::OnEditMouseL() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if( m_drawMode ) return; 
	if(Lb == 0) 
	{
		Lb = 9; // index for Edit using Mouse_L
	} else if(Lb == 1 || Lb == 9 || Lb == 10) 
	{
		Lb = 0;  areaSet = 0; drwNln = 0;// relaease 
	}
}

// assign BlockArea for editting with Key B and then B,  only all edge connection(Mat) Pattern with N and then N,
void CChildView::OnEditSetBlockArea() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if( m_drawMode ) return; 
		if(Lb == 0) // the first B-keyIn
		{	
// MessageBox(_T("here Edit_B first"));					
			Lb = 1;	
			drwNln = 2; // to draw green dot in this KoMa by Key B
			LMbX = LMeX = knap%m_komaNoX;  	// begining KoMa BlockArea
			LMbY = LMeY = knap/m_komaNoX;
			Invalidate(FALSE);
//					break;			
		} else if(Lb == 1) // the second B-KeyIn
		{		
// MessageBox(_T("here Edit_B second"));					
			Lb = 0;	
			areaSet = 1; // index for edit Pasting using MouseL 
			LMeX = knap%m_komaNoX; // ending KoMa BlockArea
			LMeY = knap/m_komaNoX;
			if( LMeX < LMbX)// Area の座標の大小を正規化
			{  
				int LMeXb = LMeX;  LMeX = LMbX; LMbX = LMeXb;  
			}	
			if( LMeY < LMbY)
			{  
				int LMeYb = LMeY;  LMeY = LMbY; LMbY = LMeYb; 
			}
			copyArea();
//			m_drawImages = TRUE;
			Invalidate(FALSE);
		}//endof if(Lb == 0){} else 
}// end of CChildView::OnEditSetBlockArea()

void CChildView::copyArea() // copy the KoMa in rectangle arear by two 'B'
{  // not on-Command type for using this funtion at other places

	if( m_drawMode ) return; // now only 0: KoMa mode, while 1:edgChain drawing mode 
//	for( int ii = 0; ii < 50; ii++)  
//	for( int iii =0; iii<37; iii++) 
//		m_koMxy[ii][iii] = short(0x8000); 
	/*　for( ii = 0; ii < 40; ii++)  
		for ( short iii =0; iii<4; iii++) m_KmDvxEC[ii][iii] = short(0x8000); 
	*/
	//m_DiaKmEC = 0;

	// copy original BlockArea data to Editting array
	for( short na = 0; na < m_komaNoX*m_komaNoY; na++)
			m_koMxy[na%m_komaNoX][na/m_komaNoX] = m_koM[na];
	// copy Original Diagonal KoMa in BlockArea

}//endof copyArea

void CChildView::OnEditCut() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if( m_drawMode ) return; // now only 0: KoMa mode, while 1:edgChain drawing mode 
	for( int ikb = 0; ikb < m_komaNoX*m_komaNoY; ikb++) m_preKoM[ikb] = m_koM[ikb];// for Undo

	//for( int ii = 0; ii < 50; ii++)  
	//for ( int iii =0; iii<37; iii++) 
	//	m_koMxy[ii][iii] = short (0x8000); 

	// keep all data to Editting Matrix
	for( short na = 0; na < m_komaNoX*m_komaNoY; na++)
			m_koMxy[na%m_komaNoX][na/m_komaNoX] = m_koM[na];
	// change BlockArea to No-KoMaTile
	for( int knx = LMbX; knx < (LMeX +1); knx++)	
	for( int kny = LMbY; kny < (LMeY +1); kny++)
	{
			//m_koMxy[knx][kny] = short(0x8000);// m_koMxy[50][37]; copy the assigned rec area to matrix
			m_koM[knx + kny*m_komaNoX] = short(0x8000); //-1 & ~0x0F; // change to cut 
	}

	areaSet = 0; // index for edit Pasting using MouseL 
//	m_drawImages = TRUE;	
	Invalidate(FALSE);
}//endof OnEditCut()

// Paste コピー先の指定は　ここではALT＋Eで赤点を動かさず　
// Cursor pointing は　Using Mouse_Lを指定
void CChildView::OnEditPaste() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if( m_drawMode ) return; // now only 0: KoMaTile mode, while 1:edgChain drawing mode 
	for( int ikb = 0; ikb < m_komaNoX*m_komaNoY; ikb++) m_preKoM[ikb] = m_koM[ikb];// for Undo
	//未完DiagonalKoMaについてfor Undo

	//移転域がImageSizeを超える
	//　m_wstr.Format("Check KoMaTileX-orY-Number or Red cursor position, as needs more tiles for this action"); 
	//	MessageBox(_T("Check KoMaTile X or Y-Number or Red cursor position, as needs more tiles for this action"));  return; 
	//完　versiom 4.4.8 自動的にサイズ拡張　 DiagonalはBackupを要する
//　未完　次で　OnEditSetBlockArea＝copyArea とか　EditCutでのm_koMxy[knx][kny]が無視されている
//上のm_koMxy[knx][kny]を使う
// keep old pattern in editting matrix
//	for( short na = 0; na < m_komaNoX*m_komaNoY; na++)
//			m_koMxy[na%m_komaNoX][na/m_komaNoX] = m_koM[na];

	// to expand X number of right column
	int knxap = knap%m_komaNoX;// cursor red KoMa
	int knyap = knap/m_komaNoX;
	if( knxap +(LMeX -LMbX +1) > m_komaNoX ) 
	{
			m_wndParam.m_KomaX_N = m_komaNoX = m_komaNoX +( knxap +(LMeX -LMbX +1) -m_komaNoX);// 追加段数を揃えるため
			CRect wd_rect;
			GetWindowRect(wd_rect);
			int wnd_xwidth = wd_rect.right - wd_rect.left;
			if( wnd_xwidth -45 < m_kks * m_komaNoX ) 
			{
				m_kks =  (wnd_xwidth -45)/m_komaNoX; 
				m_wndParam.m_KomaSize = m_kks;	// = m_ImageSizWidth/m_KomaX_N;
				cri = (int)(m_kks/2.0*1.41421356/2.0); // circle radius of the arc	
				pri = (int)( 1+ m_kks/2.0*1.41421356/20.0); // circle radius of the dot/pulli  
				whd =  m_kks/5;		//nWidth,nHeight 角の丸みの楕円形の幅と高さ
			}
			m_wndParam.m_ImageSizWidth = m_kks *m_komaNoX; 
			m_imageSiH = m_kks *m_komaNoX +45;	// Hsize of image area m_paramDlg.m_ImageSizWidth; //450
			m_imageSiV = m_kks *m_komaNoY +70;  // Vsize of image area  
	}// endof if( knxap
	//reproducing old pattern KoMaTile into New array
	for( short	knx =0; knx < m_komaNoX; knx++) 
	for( short	kny =0; kny < m_komaNoY; kny++)
			m_koM[knx + kny*m_komaNoX] = m_koMxy[knx][kny];

	//paste BlockArea to destinacion
	for(		knx = LMbX; knx < (LMeX +1); knx++)	
	for( short	kny = LMbY; kny < (LMeY +1); kny++)	//m_koMxy[50][37];
	{
			short knapp = (knxap + knx -LMbX) +(knyap + kny -LMbY)*m_komaNoX;//Destination KoMa for pasting
			m_koM[knapp] = m_koMxy[knx][kny];
	}//endof for( short knx paste of column KoMaTile
	
	// expand Y number of bottom row KoMa
	if( knyap +(LMeY -LMbY +1) > m_komaNoY ) 
	{	
			m_wndParam.m_KomaY_M = m_komaNoY = m_komaNoY +(knyap +(LMeY -LMbY +1) -m_komaNoY); 
			CRect wd_rect;
			GetWindowRect(wd_rect);
			int wnd_yhight = wd_rect.bottom - wd_rect.top;
			if( wnd_yhight -70 < m_kks *m_komaNoY ) 
			{
				m_kks =  (wnd_yhight -70)/m_komaNoY; 
				m_wndParam.m_KomaSize = m_kks;	// = m_ImageSizWidth/m_KomaX_N;
				cri = (short)(m_kks/2.0*1.41421356/2.0); // circle radius of the arc	
				pri = (short)( 1 +m_kks/2.0*1.41421356/20.0); // circle radius of the dot/pulli  
				whd =  m_kks/5;		//nWidth,nHeight 角の丸みの楕円形の幅と高さ
			}
			m_wndParam.m_ImageSizWidth = m_kks *m_komaNoX; 
			m_imageSiH = m_kks *m_komaNoX +45;	// Hsize of image area m_paramDlg.m_ImageSizWidth; //450
			m_imageSiV = m_kks *m_komaNoY +70;  // Vsize of image area  
	}// endof if( knyap	
	m_wndParam.UpdateData(false); // 2009/11/4 for sending the data to Dialog 
	
	//paste BlockArea to destinacion
	for(       knx = LMbX; knx < (LMeX +1); knx++)	
	for( short kny = LMbY; kny < (LMeY +1); kny++)	//m_koMxy[50][37];
	{
		short knapp = (knxap + knx -LMbX) +(knyap + kny -LMbY)*m_komaNoX;//Destination KoMa for pasting
		m_koM[knapp] = m_koMxy[knx][kny];
	}//endof paste of KoMatile row

	areaSet = 0; // index for end of edit Pasting using MouseL 
//	m_drawImages = TRUE;	
	Invalidate(FALSE);
}// endof void CChildView::OnEditPaste

/*
void CChildView::OnEditPaste() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if( m_drawMode ) return; // now only 0: KoMaTile mode, while 1:edgChain drawing mode 
	for( int ikb = 0; ikb < m_komaNoX*m_komaNoY; ikb++) m_preKoM[ikb] = m_koM[ikb];// for Undo
	//未完DiagonalKoMaについてfor Undo

	//移転域がImageSizeを超える
	//　m_wstr.Format("Check KoMaTileX-orY-Number or Red cursor position, as needs more tiles for this action"); 
	//	MessageBox(_T("Check KoMaTile X or Y-Number or Red cursor position, as needs more tiles for this action"));  return; 
	//完　versiom 4.4.8 自動的にサイズ拡張　 DiagonalはBackupを要する
//　未完　次で　OnEditSetBlockArea＝copyArea とか　EditCutでのm_koMxy[knx][kny]が無視されている
	// keep old pattern in editting matrix
	for( short na = 0; na < m_komaNoX*m_komaNoY; na++)
			m_koMxy[na%m_komaNoX][na/m_komaNoX] = m_koM[na];

	// to expand X number of right column
	int knxap = knap%m_komaNoX;// cursor red KoMa
	int knyap = knap/m_komaNoX;
	if( knxap +(LMeX -LMbX +1) > m_komaNoX ) 
	{
			m_wndParam.m_KomaX_N = m_komaNoX = m_komaNoX +( knxap +(LMeX -LMbX +1) -m_komaNoX);// 追加段数を揃えるため
			CRect wd_rect;
			GetWindowRect(wd_rect);
			int wnd_xwidth = wd_rect.right - wd_rect.left;
			if( wnd_xwidth -45 < m_kks * m_komaNoX ) 
			{
				m_kks =  (wnd_xwidth -45)/m_komaNoX; 
				m_wndParam.m_KomaSize = m_kks;	// = m_ImageSizWidth/m_KomaX_N;
				cri = (int)(m_kks/2.0*1.41421356/2.0); // circle radius of the arc	
				pri = (int)( 1+ m_kks/2.0*1.41421356/20.0); // circle radius of the dot/pulli  
				whd =  m_kks/5;		//nWidth,nHeight 角の丸みの楕円形の幅と高さ
			}
			m_wndParam.m_ImageSizWidth = m_kks *m_komaNoX; 
			m_imageSiH = m_kks *m_komaNoX +45;	// Hsize of image area m_paramDlg.m_ImageSizWidth; //450
			m_imageSiV = m_kks *m_komaNoY +70;  // Vsize of image area  
	}// endof if( knxap
	//reproducing old pattern KoMaTile into New array
	for( short	knx =0; knx < m_komaNoX; knx++) 
	for( short	kny =0; kny < m_komaNoY; kny++)
			m_koM[knx + kny*m_komaNoX] = m_koMxy[knx][kny];

	//paste BlockArea to destinacion
	for(		knx = LMbX; knx < (LMeX +1); knx++)	
	for( short	kny = LMbY; kny < (LMeY +1); kny++)	//m_koMxy[50][37];
	{
			short knapp = (knxap + knx -LMbX) +(knyap + kny -LMbY)*m_komaNoX;//Destination KoMa for pasting
			m_koM[knapp] = m_koMxy[knx][kny];
	}//endof for( short knx paste of column KoMaTile
	
	// expand Y number of bottom row KoMa
	if( knyap +(LMeY -LMbY +1) > m_komaNoY ) 
	{	
			m_wndParam.m_KomaY_M = m_komaNoY = m_komaNoY +(knyap +(LMeY -LMbY +1) -m_komaNoY); 
			CRect wd_rect;
			GetWindowRect(wd_rect);
			int wnd_yhight = wd_rect.bottom - wd_rect.top;
			if( wnd_yhight -70 < m_kks *m_komaNoY ) 
			{
				m_kks =  (wnd_yhight -70)/m_komaNoY; 
				m_wndParam.m_KomaSize = m_kks;	// = m_ImageSizWidth/m_KomaX_N;
				cri = (short)(m_kks/2.0*1.41421356/2.0); // circle radius of the arc	
				pri = (short)( 1 +m_kks/2.0*1.41421356/20.0); // circle radius of the dot/pulli  
				whd =  m_kks/5;		//nWidth,nHeight 角の丸みの楕円形の幅と高さ
			}
			m_wndParam.m_ImageSizWidth = m_kks *m_komaNoX; 
			m_imageSiH = m_kks *m_komaNoX +45;	// Hsize of image area m_paramDlg.m_ImageSizWidth; //450
			m_imageSiV = m_kks *m_komaNoY +70;  // Vsize of image area  
	}// endof if( knyap	
	m_wndParam.UpdateData(false); // 2009/11/4 for sending the data to Dialog 
	
	//paste BlockArea to destinacion
	for(       knx = LMbX; knx < (LMeX +1); knx++)	
	for( short kny = LMbY; kny < (LMeY +1); kny++)	//m_koMxy[50][37];
	{
		short knapp = (knxap + knx -LMbX) +(knyap + kny -LMbY)*m_komaNoX;//Destination KoMa for pasting
		m_koM[knapp] = m_koMxy[knx][kny];
	}//endof paste of KoMatile row

	areaSet = 0; // index for end of edit Pasting using MouseL 
	drwNln = 2;	// index for assignment of a copy area 
//	m_drawImages = TRUE;	
	Invalidate(FALSE);
}// endof void CChildView::OnEditPaste
*/


void CChildView::OnEditUndo() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if( m_drawMode ) return; // now only 0: KoMa mode, while 1:edgChain drawing mode 
	for( int ikb = 0; ikb < m_komaNoX*m_komaNoY; ikb++)
	{	
			short int koma = m_koM[ikb];
			m_koM[ikb] = m_preKoM[ikb];
			m_preKoM[ikb] = koma;
	}
	MessageBeep(MB_ICONEXCLAMATION); 	//MessageBeep(0);
//	m_drawImages = TRUE;
	Invalidate(FALSE);
}// endof void CChildView::OnEditUndo

//右周り回転 左上角⇒右上角　右上角⇒右下角　右下角⇒左下角　左下角⇒左上角へと回転移動　正方形の場合中央を中心に回転
//長方形では　左上角を固定して回転移動する　縦長で横幅サイズが不足する場合、横長で縦幅不足で　不良　今後サイズ拡張可能
void CChildView::OnEditRotate() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if( m_drawMode ) return; 
	for( int ikb = 0; ikb < m_komaNoX*m_komaNoY; ikb++) m_preKoM[ikb] = m_koM[ikb];// for Undo
	//未完DiagonalKoMaについてfor Undo
	
	//移転域がImageSizeを超える
	// keep old pattern in edtting matrix	
	for( short na = 0; na < m_komaNoX*m_komaNoY; na++)
				m_koMxy[na%m_komaNoX][na/m_komaNoX] = m_koM[na];
	// to expand X number of column
	if( LMbX +(LMeY-LMbY +1) > m_komaNoX ) 
	{
			m_wndParam.m_KomaX_N = m_komaNoX = m_komaNoX +(LMbX +(LMeY-LMbY +1) -m_komaNoX);
			CRect wd_rect;
			GetWindowRect(wd_rect);
			int wnd_xwidth = wd_rect.right - wd_rect.left;
			if( wnd_xwidth -45 < m_kks * m_komaNoX ) 
			{
				m_kks =  (wnd_xwidth -45)/m_komaNoX; 
				m_wndParam.m_KomaSize = m_kks;	// = m_ImageSizWidth/m_KomaX_N;
				cri = (int)(m_kks/2.0*1.41421356/2.0); // circle radius of the arc	
				pri = (int)( 1+ m_kks/2.0*1.41421356/20.0); // circle radius of the dot/pulli  
				whd =  m_kks/5;		//nWidth,nHeight 角の丸みの楕円形の幅と高さ
			}
			m_wndParam.m_ImageSizWidth = m_kks *m_komaNoX; 
			m_wndParam.UpdateData(false); // 2009/11/4 for sending the data to Dialog 
			m_imageSiH = m_kks *m_komaNoX +45;	// size of image area m_paramDlg.m_ImageSizWidth; //450
	}// endof if( LMbX 

	
	// to expand Y number of row
	if( LMbY +(LMeX-LMbX +1) > m_komaNoY ) 
	{
			m_wndParam.m_KomaY_M = m_komaNoY = m_komaNoY +(LMbY +(LMeX-LMbX +1) -m_komaNoY);
			CRect wd_rect;
			GetWindowRect(wd_rect);
			int wnd_yhight = wd_rect.bottom - wd_rect.top;
			if( wnd_yhight -70 < m_kks *m_komaNoY ) 
			{
				m_kks =  (wnd_yhight -70)/m_komaNoY; 
				m_wndParam.m_KomaSize = m_kks;	// = m_ImageSizWidth/m_KomaX_N;
				cri = (short)(m_kks/2.0*1.41421356/2.0); // circle radius of the arc	
				pri = (short)( 1 +m_kks/2.0*1.41421356/20.0); // circle radius of the dot/pulli  
				whd =  m_kks/5;		//nWidth,nHeight 角の丸みの楕円形の幅と高さ
			}
			m_wndParam.m_ImageSizWidth = m_kks *m_komaNoX; 
			m_wndParam.UpdateData(false); // 2009/11/4 for sending the data to Dialog 
			m_imageSiH = m_kks *m_komaNoX +45;	// Hsize of image area m_paramDlg.m_ImageSizWidth; //450
			m_imageSiV = m_kks *m_komaNoY +70;  // Vsize of image area  
	}// endof if( LMbY 

	// reforce BlockArea to Squar on the same m_komaNoX and m_komaNoY 
	if( (LMeY-LMbY) > (LMeX-LMbX) )			LMeX = LMbX+(LMeY-LMbY);
	else if( (LMeY-LMbY) < (LMeX-LMbX) )	LMeY = LMbY+(LMeX-LMbX);	
	//delete original BlockArea of any rectangular area
	for( short knx = LMbX; knx < (LMeX +1); knx++)		
	for( short kny = LMbY; kny < (LMeY +1); kny++)
	{
			short knapp = knx + kny*m_komaNoX;
			m_koM[knapp] = short(0x8000); //=負最大値 // change to cut 
	}// endof delete
	// copy EditArrayData to new KoMa array on rotate symmetric 
	for( short iy = 0; iy < (LMeY-LMbY+1); iy++)// vertical
	for( short ix = 0; ix < (LMeX-LMbX+1); ix++)// horizontal
	{	
			short ie = (LMbX +(LMeY-LMbY) -iy) +(LMbY +ix)*m_komaNoX; // rotate symmetric 
			m_koM[ie] =rotateKoma( m_koMxy[ LMbX +ix][ LMbY +iy] ); // X,Y axis 
	} // endof rotate	
	// keep rotated pattern
	for( ikb = 0; ikb < m_komaNoX*m_komaNoY; ikb++)
	{
		m_koMxy[ikb%m_komaNoX][ikb/m_komaNoX] = m_koM[ikb]; 
	} // endof for( ikb =  keep  rotated original pattern 
 
	areaSet = 0; // index for edit Pasting using MouseL 
//	m_drawImages = TRUE;	
	Invalidate();//draw last image without old image
}

//孫：GIFに対してのMemDCソースコードはないですが、WindowsのGDI+ APIはあります
//   Save Images
void CChildView::OnSaveImageStill() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
		MessageBeep(MB_ICONEXCLAMATION); 	
		CreateDirectory("KolamImages", NULL);//2009/11/7 Holderを既存でないとき作成
			//_mkdir() は CRT(Cランタイム ライブラリ)、CreateDirectory() は プラットフォーム SDK の関数です。
			//CRT はC言語や他のOSでも動作する、より汎用性の高いライブラリ
			//SDK は Windows 専用の API を提供するライブラリ
//		fnlimg = 0; // reset 2009/11/28 keeping the finalline image 

		stilImage = 1;	
		animImage = 0;
		drwNln = 0; // to draw N-lines
		OnKeyUp('S', 0, 0); // to trace the pattern
//		m_drawImages = TRUE;
		Invalidate(FALSE);
}

void CChildView::OnSaveImageAnimation() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
		MessageBeep(MB_ICONEXCLAMATION); 	//MessageBeep(0);
		CreateDirectory("KolamImages", NULL);//2009/11/7 Holderを既存でないとき作成

//		fnlimg = 0; // reset 2009/11/28 keeping the finalline image 
		animImage = 1;	
		stilImage = 1;	
		drwNln = 0; // to draw N-lines
		iani = 0; // file number of serial images
		//ii = 0;		//image number
		OnKeyUp('S', 0, 0); // to trace the pattern
//		m_drawImages = TRUE;
		//Invalidate(FALSE);
}
	
void CChildView::OnSaveImageNline() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
		MessageBeep(MB_ICONEXCLAMATION); 	//MessageBeep(0);
		CreateDirectory("KolamImages", NULL);//2009/11/7 Holderを既存でないとき作成

		fnlimg = 0; // reset 2009/11/28 keeping the finalline image 
		drwNln = 1; // to draw N-lines
		stilImage = 1;	
		animImage = 0;	
//		m_drawImages = TRUE;
		//Invalidate(FALSE);
}


// this code is only for Opening File in a Dialog to print an Image of Jpg file 
static char BASED_CODE szFilter2[] = "Image File(*.jpg), Only use Right-Mouse Menu|*.jpg|";
void CChildView::OnOpenFilePrint() 
{
		// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_NOCHANGEDIR, szFilter2, this /*AfxGetMainWnd()*/);
	fileDlg.DoModal();

}

void CChildView::OnSaveImagesDatafiles() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
//	CString fname = m_wndParam.m_ImageFileName;
	CString fname = m_wndParam.m_ImageName; //2009/11/29
	CString fnmdat;
	
	if( m_drawMode == 0) fnmdat= "KoMa-" + fname; else return;	
	
	m_saveDatafl = 1; // set to save data during autogeneration
	
	//ここにWindowで選択するようにする	//CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_NOCHANGEDIR, szFilter, this);
	CFileDialog fileDlg( FALSE, "txt", fnmdat, OFN_HIDEREADONLY | OFN_NOCHANGEDIR, szFilter, this /*AfxGetMainWnd()*/ );

	// if (fileDlg.DoModal() == IDOK) // コメントアウト
	if (HookFileDialogDoModal(&fileDlg) == IDOK)// 日本語->英語置換ファイルダイアログ
	{	
		/* add (n) to the end of the same fileName */
		m_strPathFileName = fileDlg.GetPathName(); //ディレクトリ、ファイル名を含め、フル パス名を取り出します
		m_strFileName = fileDlg.GetFileName(); //GetFileName は、拡張子付きのファイル名を返します。
		m_strFileTitle = fileDlg.GetFileTitle(); //GetFileTitle は、拡張子を除いたファイル名を返します。
				//	CString     strFileExt( fileDlg.GetFileExt() ); //	same as CString	strFileExt( "txt" );
				//saveDatafile( m_strPathFileName, m_strFileTitle );
	}//endof if (fileDlg.DoModal()
	
				//else if( GetAsyncKeyState( VK_SHIFT ) & 0x8000 )	// auto generation
				//{		以下必要か？　2011/03/11 元はあるが　Key Shift+Gのときと二重ではないか？	
						bAutog = TRUE;  
						pia = 0;	pim = 0;	pis = 0;	pio = 0;
						memset(m_edcd, 0, sizeof(m_edcd) ); // intialization
						drwNln = 0; //1; reset N-lines 
						SetTimer(10, TIMER_INTERVAL, NULL); // OnTimer(ID,timeout msecond,)
						// timeout should be shorter than process time,
				//} else 
}//endof OnSaveImagesDatafiles


/*　from Sun-san
void CChildView::OnFilePrint()
{
	// TODO: Add your command handler code here
	static TCHAR DocName[MAX_PATH] = _T("doc name");
	static DOCINFO docinfo;

	if (m_printDlg.DoModal() == IDOK)
	{
		HDC hDC = m_printDlg.GetPrinterDC();

		if (hDC)
		{
			CWaitCursor wait;

			CDC dc;
			dc.Attach(hDC);

			memset(&docinfo, 0, sizeof(docinfo));
			docinfo.cbSize = sizeof(docinfo);
			docinfo.lpszDocName = DocName;

			dc.StartDoc(&docinfo);
			dc.StartPage();

			// do your dc drawing here

			dc.EndPage();
			dc.EndDoc();

			SetPaperFrame(&dc, &m_printDlg.m_pd);
			dc.Detach();
		}
	}
}
*/
/////////////end/////////////////////////////

