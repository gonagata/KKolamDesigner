#include "StdAfx.h"  // VC++�̂Ƃ��C���N���[�h
// StfAfx.h�C���N���[�h ��غ��ٍ߲ς݁`�̃G���[���o���Ȃ����߂ɕK�v
// �w�b�_�C���N���[�h
#include "DialogFunc.h"

//////////////////////////////////////////////////////////////////
// �t�b�N�n���h���p�̕ϐ����O���[�o���Ő錾����B
HHOOK MyHookHandle;	// �t�b�N�n���h���ϐ�

int LangRep = 1;		// �����������s�����ǂ����̃t���O

// OK�̕�����ƁA�L�����Z���̕�����
// �{�^���̕�����ύX�������ꍇ�͂�����ύX���Ă�������
LPCSTR strOK = "OK";			// OK�{�^���̕���
LPCSTR strCancel = "Cancel";	// �L�����Z���{�^���̕���
// �t�H���g���
LOGFONT rLogfont;			// �_���t�H���g�ϐ�
HFONT hFontSmall=NULL;		// �����߂̃t�H���g
/////////////////////////////
// �u�����\����
typedef struct repItem {
	char strBefore[100];	// �u���O����
	char strAfter[100];		// �u���㕶��
	HFONT*	phFont;			// �K�p�t�H���g�ւ̃|�C���^
} stRepItem;
// �^�C�g���̏��Ɗ֘A�t����u���z��
typedef struct repTitle {
	char strBefore[100];	// �u���O�^�C�g��
	char strAfter[100];		// �u����^�C�g��
	HFONT* phFont;			// �K�p�t�H���g�ւ̃|�C���^
	repItem * pRepItem;		// �g�p����u���z��
	int aryLength;
} stRepTitle;

// �u�������܂ލ\���̔z���`
stRepItem repColDlg[] =
{
	{"�L�����Z��" , "Cancel" , NULL},
	{"��{�F(&B):", "Basic Colors", NULL},
//	{"�쐬�����F(&C):", "Custom Colors(&C) from RightSide", &hFontSmall},
	{"�쐬�����F(&C):", "Custom Colors on Add-Color", NULL},
	{"�F�̍쐬(&D) >>" , "Create Color(&D) >>", NULL},
	{"�F����(&E):", "Hue(&E):", NULL},
//	{"�N�₩��(&S):", "Satulation(&S):", &hFontSmall },
	{"�N�₩��(&S):", "Satu.(&S):",  NULL},
	{"���邳(&L):", "Lumi.(&L):", NULL},

	{"��(&R):", "Red(&R):", NULL},
//	{"��(&G):", "Green(&G):", &hFontSmall},
	{"��(&G):", "Gr'n(&G):", NULL},
	{"��(&U):", "Blue(&U):", NULL},
	{"�F�̒ǉ�(&A)", "Add Color(&A) to Custom_Colors", NULL},
	{"�F" , "set", NULL},
//	{"| ���F(&O)" , "| pure col(&O)", NULL}
	{"| ���F(&O)" , "Color", NULL}
};
// �t�@�C�����J���_�C�A���O�p
stRepItem repFileDlg[] =
{
	{"�t�@�C���̏ꏊ(&I):", "File Location(&I):", NULL},
	{"�ۑ�����ꏊ(&I):", "File Saving Location(&I):", NULL},
	{"�t�@�C����(&N):", "File Name(&N):", NULL},
	{"�t�@�C���̎��(&T):", "File Type(&T):", NULL},
	{"�L�����Z��", "Cancel", NULL},
	{"�J��(&O)", "Open(&O)", NULL},
	{"�ۑ�(&S)", "Save(&S)", NULL},
	{"�\�����j���[", "Menu" , NULL},
	{"�k����(&H)", "mini(&H)" , NULL}
};
// �^�C�g���Ɗ֘A�t���̒�`
stRepTitle repTitle[] = 
{
	{ "�F�̐ݒ�", "Color Design", NULL , repColDlg,  sizeof(repColDlg)/sizeof(stRepItem) },
	{ "�t�@�C�����J��", "Open File", NULL , repFileDlg,  sizeof(repFileDlg)/sizeof(stRepItem) },
	{ "���O��t���ĕۑ�", "Save File", NULL , repFileDlg,  sizeof(repFileDlg)/sizeof(stRepItem) }
};


////////////////////////////////////////////////////////////////////
//
//		�_�C�A���O���e���������̂��߂�
//		�t�b�N�֐��i���[�J���t�b�N�p�j
//		�� �O���[�o���֐��ł���K�v������܂��B
//		���̊֐��̒���ς���Ƃ��͐T�d�ɍs���ĉ������B
//
LRESULT CALLBACK LocalHookProc (int nCode, WPARAM wParam ,LPARAM lParam )
{
	// �R�[�h���f
	if (nCode >= 0)
	{
		if ( nCode == HCBT_ACTIVATE)
		{

			if( LangRep == 1 ){
               //�_���t�H���g�\���̂̎w��
               rLogfont.lfHeight= 10 ;// �傫��
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

               //�t�H���g���쐬
                hFontSmall = CreateFontIndirect(&rLogfont) ;

				int i,numAry;
				stRepItem * pRepItem=NULL;
				char strType[50];
				strcpy(strType, "");
				HWND myWnd;
				// �^�C�g���̏ƍ��Ə�������
				for( i = 0; i < (sizeof(repTitle)/sizeof(repItem)) ; i++){
					char buff[50];
					GetWindowText((HWND)wParam,buff, sizeof(buff));
					if( strcmp(buff,repTitle[i].strBefore ) == 0 ){
						// ��v�������̂��������ꍇ
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
					// FindWindowEx(�e�E�B���h�E, �J�n�q�E�B���h�E�ԍ�, �N���X�� , �L���v�V����);
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
			// OK�{�^��(IDOK)�̓��e������������
			SetDlgItemText( ( HWND )wParam, IDOK, strOK );
			// �L�����Z���{�^��(IDCANCEL)�̓��e������������
			SetDlgItemText( ( HWND )wParam, IDCANCEL, strCancel );

			HRESULT ret;
			// �t�b�N�֐����A���C���X�g�[��(�t�b�N�����I�j
			ret = UnhookWindowsHookEx ( MyHookHandle );
			MyHookHandle = NULL;
		}
	}
	// ���̃t�b�N�ɓn��
	return CallNextHookEx ( MyHookHandle, nCode, wParam, lParam);
}
/////////////////////////////////////////////////////////////
//
//			�t�@�C���I���_�C�A���O���t�b�N�t���ŌĂяo���֐�
//
int	HookFileDialogDoModal( CFileDialog * pFileDialog )
{
	MyHookHandle = SetWindowsHookEx ( WH_CBT, LocalHookProc, NULL, GetCurrentThreadId( ) ); 

	return pFileDialog->DoModal();

}

///////////////////////////////////////////////////////////
//
//	ColorDlg() �J���[�I���_�C�A���O�֐�
//	�J�X�^���J���[�z���static�ŕۑ�����܂��B
//		@param  hWnd		:   �I�[�i�[�E�B���h�E
//		@param  p_crResult	:	���ʂ��󂯎��COLORREF�̃|�C���^ 
//		@param	crFirst		:  �����I��F
//		@param	bUserFirstColor: �����I��F���g�����ǂ���
//		@param dwSpCustomColors[] 
//					: �J�X�^���J���[�z���Ǝ��Ɏw�肷��ꍇ(NULL: �f�t�H���g�ۑ�)
//		@return TRUE:�I�� , FALSE :�L�����Z��
//
BOOL ColorDlg(HWND hWnd, COLORREF* p_crResult, 
			  COLORREF crFirst, BOOL bUseFirstColor, DWORD dwSpCustomColors[] )
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������

	// CHOOSECOLOR�\���̒�`
	CHOOSECOLOR cc;
	// �J�X�^���J���[�{�b�N�X�̃f�[�^�z���`
	// 16��COLORREF�ϐ��̔z�� ( static�Ő錾���邱��)
	static DWORD       dwDefaultCustomColors[16];   
	// COLORREF�\���̒�`
	static COLORREF crDefaultFirst = RGB(255,255,255);

	// CHOOSECOLOR�\���̃N���A
	ZeroMemory(&cc,sizeof(CHOOSECOLOR));
	// CHOOSECOLOR�\���̃T�C�Y�ݒ�
	cc.lStructSize = sizeof(CHOOSECOLOR);
	// �I�[�i�[�E�B���h�E�ݒ�
	cc.hwndOwner =(HWND ) hWnd;
	// �J�X�^���J���[�{�b�N�X�̃f�[�^�z��ݒ�
	cc.lpCustColors = ( dwSpCustomColors != NULL)? dwSpCustomColors: dwDefaultCustomColors;

	// 	�����I��F
	cc.rgbResult =  (bUseFirstColor == TRUE)? crFirst: crDefaultFirst;
	// �t���O�ݒ�
	// CC_FULLOPEN : �J�X�^���J���[�ݒ�\��
	// CC_RGBINIT  : rgbResult�̐F�������I��
	// CC_ANYCOLOR : �g�p�\�ȑS�Ă̐F��\������
	cc.Flags = CC_ANYCOLOR|CC_FULLOPEN|CC_RGBINIT;
	

	// �t�b�N�֐�(MsgBoxHookProc)���C���X�g�[������ SetWindowHookEx
	MyHookHandle = SetWindowsHookEx ( WH_CBT, LocalHookProc, NULL, GetCurrentThreadId( ) ); 

	// �J���[�_�C�A���O��\��
	if(ChooseColor(&cc)){
		*p_crResult = cc.rgbResult;
		return TRUE;
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////
//
//		AfxMessageBoxHooked(���b�Z�[�W, 
//
int AfxMessageBoxHooked( LPCSTR message , UINT nType )
{
	// �t�b�N�֐�(MsgBoxHookProc)���C���X�g�[������ SetWindowHookEx
	MyHookHandle = SetWindowsHookEx ( WH_CBT, LocalHookProc, NULL, GetCurrentThreadId( ) ); 
	return ( AfxMessageBox(message, nType) ); 

}
///// End ////////////////////////////////////////////////////////////////
