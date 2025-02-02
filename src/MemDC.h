// MemDC.h: interface for the CMemDC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMDC_H__218E8F1E_92A2_483A_AE5B_C4A475CA4F7E__INCLUDED_)
#define AFX_MEMDC_H__218E8F1E_92A2_483A_AE5B_C4A475CA4F7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMemDC : public CDC
{
public:
// Attributes
	BITMAPINFO m_bitmapInfo;
	void* m_pDIBits;

	CBitmap* m_pMemBitmap;
	CBitmap* m_pOldBitmap;

public:
	CMemDC();
	virtual ~CMemDC();

	BOOL ReleaseMem();

	BOOL CreateCompatibleBitmap(CDC* pDC, int nWidth, int nHeight);
	BOOL CreateDIBitmap(int nWidth, int nHeight);

	CSize GetBitmapSize();

//	int StretchDIBits(CDC* pDC, int XDest, int YDest, int nDestWidth, int nDestHeight, int XSrc, int YSrc, int nSrcWidth, int nSrcHeight, DWORD dwRop);

	BOOL LoadJPEG(LPCTSTR lpszPathName);
	BOOL LoadBMP(LPCTSTR lpszPathName);
	
	BOOL LoadBitmap(HINSTANCE hInstance, LPCTSTR lpBitmapName);
	BOOL LoadImage(LPCSTR lpszPathName);

	BOOL SaveJPEG(LPCTSTR lpszPathName, int quality = 100); // changed for animation, from int quality = 75);
	BOOL SaveBMP(LPCTSTR lpszPathName);
};

#endif // !defined(AFX_MEMDC_H__218E8F1E_92A2_483A_AE5B_C4A475CA4F7E__INCLUDED_)
