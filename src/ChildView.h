// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__00AB081C_A381_41AA_B5D2_605519F5E69E__INCLUDED_)
#define AFX_CHILDVIEW_H__00AB081C_A381_41AA_B5D2_605519F5E69E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "MemDC.h"
//#include "KolamDesigner.h"		// nagata for KolamDesignerApp
#include "ParameterDlg.h"	// 20021017 for ParameterDilog

//#include <string>   // string in OpenFile
// 2009/12/4 MFC を使用しているので、#include <string> は不要では？
// CString クラスは LPCTSTR のオペレーターを持っていますので･･･。
// これを取ると　変数型のWarningが出る。=（変換型関数)(変数）と修正
/////////////////////////////////////////////////////////////////////////////
// CChildView window

#define TIMER_INTERVAL 0

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:
	//CParameterDlg *	m_pParamDlg;   // transfer DATA from ParameterSetDialog by Nagata
	CParameterDlg   m_wndParam;// パラメータダイアログ

	CString		m_imageD_F_Name;   // a temporary filename with directory 
	CString     m_strPathFileName;// path-name Directory and file names of Kolam Array and Image
	CString     m_strPathName;// only path-name Directory of file of Kolam Array and Image
	CString     m_strFileTitle;// only filename of Kolam Array and image without txt & jpg
	CString		m_strImgName; // only data of Dialog 
	CString     m_strFileName;// only filename of Kolam Array and image with txt & jpg
	CString		m_cdate;
	CString		m_memo;
	CString     m_wstr;// for anotherLoop message

	int m_imageSiH; // image size in Holizontal
	int m_imageSiV; // image size in Vertical
 
	int m_komaNoX; //koma number in X
	int m_komaNoY; //koma number in Y
	int m_kks; // kolam koma size in pixel
	int m_slpt; // sleeping time in msec for animation
	int m_swell; // m_SwellMode:0 normal 1 swell paper  2 night show 3 colorbutton 4 edgeline
	short int m_komType; // all komaType 
	short int m_koM[1850]; // =50x37 at 1200pixel m_koM[]: kolam koma type, kna:koma number at knx,kny  
	short int m_preKoM[1850]; // for backup   
	short int m_koMxy[50][37]; // for Editting matrix data 

	short int checkAll; // checking if every KoMa > 0
 
	// change kna to knax = kna%m_komaNoX; knay = kna/m_komaNoX;
		// 		         kna =  knax + knay*NoX;
		//10 digit number of kolam type 0-F but now 1,2,3 status 16bit so, the upper bits are not used
		//int kedge[1850];	// now not used, edge connection status 
		// bit order:[topup,topdown,leftup,leftdown,bottomup,bottomdown,rightup,rightdown] 
		// edgn:0-4, udidx: up(1)down(0) connection, 0:virgin,1:passed
		// udidx 1:turn round clockwise,0:counterclockwise 
//	int m_fudeNum;	// Fude(Stroke) Number Max10:0-9, [m_fudeNum], the first one m_fudeNum = 0; 
//	int m_chnNo[10];	// chain index [Fude index] accounted as 0-9, Number = m_chnNo +1; 
//	int m_startChainX[10];	// starting point of each fude index
//	int m_startChainY[10];
//	int m_startSide[10];	// starting side and direction
//	int m_startChainXFile[10];	// starting point of each fude index
//	int m_startChainYFile[10];
//	int m_startSideFile[10];	// starting side and direction
//	unsigned int m_edgeChain[10][232]; // [fude number][chain number Max232 ] chains=1850 KoMax4/32bits, MSB: start 32, LSB:last
//	int m_numEdges[10][232]; // order[fude number][chain number Max232] of edges(useful Bits) of each m_edgeChain[10][232]

	int m_loopNum;	//loop(Wa) Number Max10:0-9, [0,1,2 ....m_loopNum-1], the initial=0; 
	int m_strtKoma[10];  // starting KoMa of each loop
	int m_strtKomaX[10];  // starting KoMa X axis of each loop
	int m_strtSide[10]; // common starting edge of starting KoMa of each loop
	COLORREF m_loopColor[10];	// 選択されたloop色 defalt 指定済み　OnPaint() if(m_loopNum > 0) // for loops
	CString	 m_symJudge[10];	//各Loopの形状　対称性の記載に使う	

	short int m_saveDatafl; 
	short int m_gemod; // genration pattern index
	short int m_hitosccd; //index for hitofude succeed

	int m_ednum; // number of edges in order
	short int m_edcd[3613]; // edge data 50x37*2-(50+37), m_komaNoX*m_komaNoY*2 -(m_komaNoX+m_komaNoY)
	short int m_alledge; //index of all edges m_edcd[ all] = 1
	unsigned m_edpnm; // Max possible number of digital of all edges
	//　これに合わせて　piaもunsigned とする
	short int m_N81toE8B[81];  // 8bit number= N81toE8B[0-80 number];
	short int m_E8BtoN81[241];  // 0-80 number= E8BtoN81[8bit number Max 240];

	// Static宣言しないで 設置場所も// Attributes　public:でないと　ChildViewのメンバとならない　m_が付いてない名前であるが。
	// 他の.CPP　ParameterDlg.cppで　((CChildView*)m_pParent)->drwNln = 2;のように使えない。
	short  knap; //present Koma number with Keyin as well as L-MOUSE,from "0" of left-upper 
	short  LMbX, LMbY, LMeX, LMeY; // for N-lines and assign the rect area at Key N and B	
	short  drwNln; // = 1: for drawing Navi-line first Key:beginning, second:ending and draw N-Line
				   // = 2; for also showing a assigned/copy area with green dots
	short fnlimg; //2009/11/28 for keeping finalline image at trce = 3


	int clrRGB[4][3];		// for savefile or readfile
	COLORREF m_grdColor;	// KoMa groundcolor
	COLORREF m_tilColor;	// RGB(190, 130, 0);KoMa tile-color
	COLORREF m_amiColor;	// KoMa amimate-line-color 
	COLORREF m_fnlColor;	// KoMa final-line-color
	
	BOOL m_drawImages; //=0:FALSE  to OnPain() for any commands
	BOOL m_drawMode; // drawing mode 0:KoMa,1:EdgeChain 

	short int m_smoothmod; //tracing Fudemode index 0:smoothmode,1:NonSmooth(SharpBend),2:outline-border 

// Operations
public:
	BOOL PreCreateWindow(CREATESTRUCT& cs, CParameterDlg* pParamDlg);
	BOOL PreCreateWindow(CREATESTRUCT& cs);
	void EndParamDlg();

	//BOOL GetCursorPos(  LPPOINT lpPoint); 

	//int parse(const CString& line, CStringArray& result); 
	short int makeKoma( int knam, int edgm, short status);
	short int rotateKoma( short int  komat);
	int nextEdg( int kna, int nowedg, int lindirct);
	//int edgeStats( int kna, int edgn, int udidx, int virgn);
	//int getStats( int kna, int edgn, int udidx);
		
	double	autoCorr(bool *edg, int suN, int sftL);
	void symMetry();
	void getRepeatSequence();
	void pattnGenrtn(int order);
	void reCursive(int deep);
	void geNeration(int gemodd);
	void connectDiscon(int knp, int edge, short int eval);
	void reArrang(int dtype);
	void saveImage(int ii);
	void saveDatafile(CString strPathName, CString strFileName); 
	void copyArea(); // copy the KoMa in rectangle arear by two 'B'
	void preparingColor(); //set color from ColorDailog
	void SetPatternArc(short int centsign, short int kxkysign, int nmedgn);
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~CChildView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint( );
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnParameterSet();
	afx_msg void OnViewDrawImages();
	afx_msg void OnViewDrawFude();
	afx_msg void OnGeneKolam();
	afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
	afx_msg void OnMouseMove( UINT nFlags, CPoint point );	
	afx_msg void OnOpenKomaFile();	//for file-menu nagata
	afx_msg void OnSaveKomaFile();	//for file-menu nagata
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnViewResetAll();
	afx_msg void OnEditPaste();
	afx_msg void OnEditUndo();
	afx_msg void OnEditRotate();
	afx_msg void OnGenerationRot();
	afx_msg void OnGenerationHvs();
	afx_msg void OnGeneRecursive();
	afx_msg void OnEditCut();
	afx_msg void OnSaveImageStill();
	afx_msg void OnSaveImageAnimation();
	afx_msg void OnSaveImageNline();
	afx_msg void OnOpenFilePrint();
	afx_msg void OnSaveImagesDatafiles();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEditSetBlockArea();
	afx_msg void OnEditMouseL();
	afx_msg void OnGenerationVSym();
	afx_msg void OnEditHSym();
	afx_msg void OnHelpUsage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
// static をヘッダに移動してくる
//static 	int m_komaNoX; //koma number in X
//static 	int m_komaNoY; //koma number in Y
// Static 宣言する 設置場所も// Attributes　public:でないと　ChildViewのメンバとならない　m_が付いてない名前であるが。
// 他の.CPP　ParameterDlg.cppで　((CChildView*)m_pParent)->drwNln = 2;のように使えない。
/* short  knap; //present Koma number with Keyin as well as L-MOUSE,from "0" of left-upper 
short  LMbX, LMbY, LMeX, LMeY; // for N-lines and assign the rect area at Key N and B	
short  drwNln; // = 1: for drawing Navi-line first Key:beginning, second:ending and draw N-Line
				   // = 2; for also showing a assigned/copy area with green dots
short fnlimg; //2009/11/28 for keeping finalline image at trce = 3
*/
static int Lb, Bknap; // Key "B" "N" and Edit_SetBlockArea 
//
static double cospi8th[9],  sinpi8th[9];
static int keyS_M; // index Shiftkey or Mouse action for stopping trace
static int cri;// = (int)(m_kks/2.0*1.41421356/2.0); // circle radius of the arc 
static int pri; // = (int)(1+ m_kks/2.0*1.41421356/20.0); // circle radius of the dot/pulli  
static int whd; // =  m_kks/5;		//nWidth,nHeight 角の丸みの楕円形の幅と高さ
static int iani = 0; // file number of serial images
static unsigned  pia = 0; //number of generated patters inculding KoMa0 
static unsigned  pim = 0; //number of multi fude/loop
static unsigned  pis = 0; //number of single fude/loop
static unsigned  pio = 0; //number fude/loops connecting all Koma (= pim + pis)

static BOOL bAutog = FALSE;	// Key G TRUE for Auto generation
static int cnvEc2KoMa = 0; //index to convert EdgeChain to KoMa Data
//static short int m_koM[1850]; // =50x37 at 1200pixel m_koM[]: kolam koma type, kna:koma number at knx,kny  
//static short int m_preKoM[1850]; // for backup   
//static short int m_koMxy[50][37]; // for matrix data 

	// 以下の変数はAttributesでは AutoGenrationで全て描画するので
    // スタックオーバーフローするためと思われるのでここにStaticに　移動
// 2011/05/01 otherloop, after tracing a loop, to restart to draw an other loop
//static int m_loopNum;	//loop(Wa) Number Max10:0-9, [0,1,2 ....m_loopNum-1], the initial=0; 
//static int m_strtKoma[10];  // starting KoMa of each loop
//static int m_strtKomaX[10];  // starting KoMa X axis of each loop
//static int m_strtSide[10]; // common starting edge of starting KoMa of each loop
//static 	COLORREF m_loopColor[10];	// 選択されたloop色

//static int m_fudeNum;	// Fude(Stroke) Number Max10:0-9 [m_fudeNum], the first m_fudeNum = 0; 
//static int m_chnNo[10];	// chain Number[Fude number]: accounted as 0-9, Number=m_chnNo +1; 
static int m_startChainX[10];	// starting point of each fude index
static int m_startChainY[10];
//static int m_startSide[10];	    // starting side(edge) and direction
static int m_startChainXFile[10];	// ??needs?? file用に別に作った？starting point of each fude index
static int m_startChainYFile[10];   // ??needs??
static int m_startSideFile[10];	    // ??needs?? starting side and direction
//static unsigned int m_edgeChain[10][232]; // [fude number][chain number Max232 ] chains=1850 KoMa数x4/32 bits, MSB:start 32,LSB:last
//static int m_numEdges[10][232]; // order[fude number][chain number Max232] of edges(useful Bits) of each m_edgeChain[10][232]
                                        //m_edgeChain と　m_numEdgesの役割りの違い　前者はedgeのDATA、後者はedgeのDATAの個数
///////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CChildviewScroll ビュー

class CChildviewScroll : public CScrollView
{
protected:
	CChildviewScroll();           // 動的生成に使用されるプロテクト コンストラクタ。
	DECLARE_DYNCREATE(CChildviewScroll)

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CChildviewScroll)
	protected:
	virtual void OnDraw(CDC* pDC);      // このビューを描画するためにオーバーライドしました。
	virtual void OnInitialUpdate();     // 構築後、最初の処理。
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual ~CChildviewScroll();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CChildviewScroll)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__00AB081C_A381_41AA_B5D2_605519F5E69E__INCLUDED_)
