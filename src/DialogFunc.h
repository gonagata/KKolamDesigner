// DialogFunc.h
#pragma once

// �J���[�I���_�C�A���O�\���֐�
// (�I�[�i�[�E�B���h�E, ���ʊi�[COLORREF, �����J���[, �����J���[���g�����ǂ���)
BOOL ColorDlg(HWND hWnd, COLORREF* p_crResult, 
			  COLORREF crFirst, BOOL bUseFirstColor, DWORD dwSpCustomColors[] );
// �v���g�^�C�v�錾
LRESULT CALLBACK LocalHookProc (int nCode, WPARAM wParam ,LPARAM lParam );
int AfxMessageBoxHooked( LPCSTR message , UINT nType );

int	HookFileDialogDoModal( CFileDialog * pFileDialog );
/////////end///////////////////////////////////////