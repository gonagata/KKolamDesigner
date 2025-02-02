// MemDC.cpp: implementation of the CMemDC class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemDC.h"
#include "ijl.h"
//#include <vfw.h> 2009/12/09 無くても良い

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemDC::CMemDC()
{
	memset(&m_bitmapInfo, 0, sizeof(m_bitmapInfo));
	m_pDIBits = NULL;

	m_pMemBitmap = NULL;
	m_pOldBitmap = NULL;
}

CMemDC::~CMemDC()
{
	if (m_pOldBitmap) SelectObject(m_pOldBitmap);
	if (m_pMemBitmap) delete m_pMemBitmap;
}

BOOL CMemDC::ReleaseMem()
{
	memset(&m_bitmapInfo, 0, sizeof(m_bitmapInfo));
	m_pDIBits = NULL;

	if (m_pOldBitmap) SelectObject(m_pOldBitmap);
	if (m_pMemBitmap) delete m_pMemBitmap;

	m_pMemBitmap = NULL;
	m_pOldBitmap = NULL;

	DeleteDC();

	return TRUE;
}

BOOL CMemDC::CreateCompatibleBitmap(CDC* pDC, int nWidth, int nHeight)
{
	ReleaseMem();

	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(pDC, nWidth, nHeight);

	CreateCompatibleDC(NULL);
	m_pOldBitmap = SelectObject(m_pMemBitmap);

	return TRUE;
}

BOOL CMemDC::CreateDIBitmap(int nWidth, int nHeight)
{
	ReleaseMem();

	BITMAPINFOHEADER& bmiHeader = m_bitmapInfo.bmiHeader;
	bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
	bmiHeader.biWidth       = nWidth;
	bmiHeader.biHeight      = nHeight;
	bmiHeader.biPlanes      = 1;
	bmiHeader.biBitCount    = 24;
	bmiHeader.biCompression = BI_RGB;

	HBITMAP hBitmap = ::CreateDIBSection(NULL, &m_bitmapInfo, 
						DIB_RGB_COLORS, &m_pDIBits, NULL, NULL);

	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->Attach(hBitmap);

	CreateCompatibleDC(NULL);
	m_pOldBitmap = SelectObject(m_pMemBitmap);

	return TRUE;
}

CSize CMemDC::GetBitmapSize()
{
	if (m_pMemBitmap == NULL) return CSize(-1, -1);

	BITMAP bitmap;
	m_pMemBitmap->GetBitmap(&bitmap);

	return CSize(bitmap.bmWidth, bitmap.bmHeight);
}
/*
int CMemDC::StretchDIBits(CDC* pDC, int XDest, int YDest, int nDestWidth, 
	int nDestHeight, int XSrc, int YSrc, int nSrcWidth, int nSrcHeight, DWORD dwRop)
{
	return ::StretchDIBits(pDC->m_hDC, XDest, YDest, nDestWidth, nDestHeight, 
		XSrc, YSrc, nSrcWidth, nSrcHeight, m_pDIBits, &m_bitmapInfo, DIB_RGB_COLORS, dwRop);
}
*/
BOOL CMemDC::LoadJPEG(LPCTSTR lpszPathName)
{
	ReleaseMem();

	CWaitCursor wait;

	JPEG_CORE_PROPERTIES jcprops = {0};

	TRY
		if (ijlInit(&jcprops) != IJL_OK)
		{
			TRACE("Cannot initialize Intel JPEG library\n");
			AfxThrowUserException();
		}

		jcprops.JPGFile = (char*)lpszPathName;
		if (ijlRead(&jcprops, IJL_JFILE_READPARAMS) != IJL_OK)
		{
			TRACE("Cannot read JPEG file header from %s file\n", jcprops.JPGFile);
			AfxThrowUserException();
		}

		switch (jcprops.JPGChannels)
		{
			case 1:
				jcprops.JPGColor = IJL_G;
				break;

			case 3:
				jcprops.JPGColor = IJL_YCBCR;
				break;

			default:
				jcprops.DIBColor = (IJL_COLOR)IJL_OTHER;
				jcprops.JPGColor = (IJL_COLOR)IJL_OTHER;
				break;
		}

		jcprops.DIBWidth    = jcprops.JPGWidth;
		jcprops.DIBHeight   = jcprops.JPGHeight;

		jcprops.DIBChannels = 3;
		jcprops.DIBPadBytes = IJL_DIB_PAD_BYTES(jcprops.DIBWidth, jcprops.DIBChannels);

		BITMAPINFOHEADER& bmiHeader = m_bitmapInfo.bmiHeader;
		bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
		bmiHeader.biWidth       = jcprops.DIBWidth;
		bmiHeader.biHeight      = -jcprops.DIBHeight;
		bmiHeader.biPlanes      = 1;
		bmiHeader.biBitCount    = 24;
		bmiHeader.biCompression = BI_RGB;

		HBITMAP hBitmap = ::CreateDIBSection(NULL, &m_bitmapInfo, 
							DIB_RGB_COLORS, &m_pDIBits, NULL, NULL);

		if(m_pDIBits == NULL)
		{
			TRACE("Cannot allocate memory for image\n");
			AfxThrowUserException();
		}

		jcprops.DIBBytes = (BYTE*)m_pDIBits;

		if (ijlRead(&jcprops, IJL_JFILE_READWHOLEIMAGE) != IJL_OK)
		{
			TRACE("Cannot read image data from %s file\n", jcprops.JPGFile);
			delete[] m_pDIBits;
			AfxThrowUserException();
		}

		if (ijlFree(&jcprops) != IJL_OK)
		{
			TRACE("Cannot free Intel(R) JPEG library");
		}

		m_pMemBitmap = new CBitmap;
		m_pMemBitmap->Attach(hBitmap);

		CreateCompatibleDC(NULL);
		m_pOldBitmap = SelectObject(m_pMemBitmap);

	CATCH_ALL(e)

		ijlFree(&jcprops);
		return FALSE;

	END_CATCH_ALL

	return TRUE;
}

BOOL CMemDC::LoadBMP(LPCTSTR lpszPathName)
{
	ReleaseMem();

	HBITMAP hBitmap = (HBITMAP)::LoadImage(NULL, lpszPathName, IMAGE_BITMAP, 
				0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);

	if (hBitmap == NULL) return FALSE;

	m_pMemBitmap = new CBitmap();
	m_pMemBitmap->Attach(hBitmap);

	CreateCompatibleDC(NULL);
	m_pOldBitmap = SelectObject(m_pMemBitmap);

	return TRUE;
}

BOOL CMemDC::LoadBitmap(HINSTANCE hInstance, LPCTSTR lpBitmapName)
{
	ReleaseMem();

	HBITMAP hBitmap = (HBITMAP)::LoadBitmap(hInstance, lpBitmapName);

	if (hBitmap == NULL) return FALSE;

	m_pMemBitmap = new CBitmap();
	m_pMemBitmap->Attach(hBitmap);

	CreateCompatibleDC(NULL);
	m_pOldBitmap = SelectObject(m_pMemBitmap);

	return TRUE;
}

BOOL CMemDC::LoadImage(LPCSTR lpszPathName)
{
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	_splitpath(lpszPathName, drive, dir, fname, ext);

	CString s = ext;
	s.MakeLower();

	BOOL result = FALSE;

	if (s == ".bmp") result = LoadBMP(lpszPathName);
		else

	if (s == ".jpg") result = LoadJPEG(lpszPathName);

	return result;
}

BOOL CMemDC::SaveJPEG(LPCTSTR lpszPathName, int quality)
{
	JPEG_CORE_PROPERTIES jcprops = {0};

	TRY

		if (ijlInit(&jcprops) != IJL_OK)
		{
			TRACE("Cannot initialize Intel JPEG library\n");
			AfxThrowUserException();
		}

		CSize imageSize = GetBitmapSize();
		jcprops.DIBBytes = (BYTE*)m_pDIBits;
		jcprops.DIBWidth = imageSize.cx;
		jcprops.DIBHeight = -imageSize.cy;
		jcprops.DIBPadBytes = IJL_DIB_PAD_BYTES(jcprops.DIBWidth, jcprops.DIBChannels);
		jcprops.DIBChannels = 3;
		jcprops.DIBColor = IJL_BGR;

		jcprops.JPGFile = lpszPathName;
		jcprops.JPGWidth = imageSize.cx;
		jcprops.JPGHeight = imageSize.cy;

		jcprops.JPGThumbWidth = 100;
		jcprops.JPGThumbHeight = 75;

		jcprops.jquality = quality;

		if (ijlWrite(&jcprops, IJL_JFILE_WRITEWHOLEIMAGE) != IJL_OK)
		{
			TRACE("Cannot write image data to %s file\n", jcprops.JPGFile);
			AfxThrowUserException();
		}
		
		if (ijlFree(&jcprops) != IJL_OK)
		{
			TRACE("Cannot free Intel(R) JPEG library");
		}

	CATCH_ALL(e)

		ijlFree(&jcprops);
		return FALSE;

	END_CATCH_ALL
	
	return TRUE;
}

BOOL CMemDC::SaveBMP(LPCTSTR lpszPathName)
{
	CFile file(lpszPathName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	CSize imageSize = GetBitmapSize();

	BITMAPFILEHEADER bmfHdr;
	bmfHdr.bfType = ((WORD) ('M' << 8) | 'B');
	bmfHdr.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (imageSize.cx * imageSize.cy * 3);
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
//	file.WriteHuge(&bmfHdr, sizeof(bmfHdr));
//2009/12/4 WriteHuge は互換性のために残されていますが、現在ではサポートされていません。
//代わりに Write を使用してください。
	file.WriteHuge(&bmfHdr, sizeof(bmfHdr));

	GetDIBits(this->m_hDC, (HBITMAP)m_pMemBitmap, 0, imageSize.cy, NULL, &m_bitmapInfo, DIB_RGB_COLORS);
	BITMAPINFOHEADER& bmiHeader = m_bitmapInfo.bmiHeader;
//	file.WriteHuge(&bmiHeader, sizeof(BITMAPINFOHEADER));
//2009/12/4 WriteHuge は互換性のために残されていますが、現在ではサポートされていません。
//代わりに Write を使用してください。
	file.Write(&bmiHeader, sizeof(BITMAPINFOHEADER));

//	BITMAPINFOHEADER bif = {0};
//	bif.biSize = sizeof(bif);
//	bif.biWidth = imageSize.cx;
//	bif.biHeight = imageSize.cy;
//	bif.biPlanes = 1;
//	bif.biBitCount = 24;
//	bif.biCompression = BI_RGB;
//	bif.biXPelsPerMeter = 72;
//	bif.biYPelsPerMeter = 72;

	BYTE* pImageData = new BYTE[imageSize.cx * imageSize.cy * 3];
	int line = GetDIBits(this->m_hDC, *m_pMemBitmap, 0, imageSize.cy, pImageData, &m_bitmapInfo, DIB_RGB_COLORS);
//	file.WriteHuge(pImageData, imageSize.cx * imageSize.cy * 3);
//2009/12/4 WriteHuge は互換性のために残されていますが、現在ではサポートされていません。
//代わりに Write を使用してください。
	file.Write(pImageData, imageSize.cx * imageSize.cy * 3);
	delete pImageData;

	file.Close();

	return TRUE;
}
