//////////////////////////////////////////////////////////////////////////
// ImageStuDlg.h : header file
// ͼ����ʵ��ѧ��ƽ̨
// ������: �˷�
// ����ʱ��: 2008-8-31
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGESTUDLG_H__8B975AD1_2A07_4F7F_B0EC_1B03621056BF__INCLUDED_)
#define AFX_IMAGESTUDLG_H__8B975AD1_2A07_4F7F_B0EC_1B03621056BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "BaseColorInfo.h"

class CImageStuDlg : public CDialog
{
// Construction
public:
	CImageStuDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CImageStuDlg)
	enum { IDD = IDD_IMAGESTU_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageStuDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CImageStuDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFileOpen();
	afx_msg void OnDestroy();
	afx_msg void OnFileShowArray();
	afx_msg void OnTest();
	afx_msg void OnFileSave();
	afx_msg void OnFullRed();
	afx_msg void OnRedBlue();
	afx_msg void OnColorBlack();
	afx_msg void OnGrayBlack();
	afx_msg void OnDirectZoom();
	afx_msg void OnGrayAdjust();
	afx_msg void OnNearestInterpolation();
	afx_msg void OnBilinearInterpolation();
	afx_msg void Onmove();
	afx_msg void OnHorizontalmirroring();
	afx_msg void OnVerticalMirroring();
	afx_msg void OnTranspose();
	afx_msg void OnRotating();
	afx_msg void OnNegate();
	afx_msg void OnLogarithm();
	afx_msg void OnShifting();
	afx_msg void OnFenDuan();
	afx_msg void OnWeiPingMian();
	afx_msg void OnZhiFang();
	afx_msg void OnLinYu();
	afx_msg void OnJiaQuan();
	afx_msg void OnJunZhiQuick();
	afx_msg void OnJunZhiYuzhi();
	afx_msg void OnJiaQuanQuick();
	afx_msg void OnFeiXianXing();
	afx_msg void OnFeiXianXingX();
	afx_msg void Onlpls();
	afx_msg void OnRobert();
	afx_msg void OnSobel();
	afx_msg void OnGrayColor();
	afx_msg void OnRgbHsiRgb();
	afx_msg void OnFuShi();
	afx_msg void OnPenZhang();
	afx_msg void OnOpen();
	afx_msg void OnClose();
	afx_msg void OnBianJie();
	afx_msg void OnTianChong();
	afx_msg void OnLianTong();
	afx_msg void OnXiHua();
	afx_msg void OnHuffman();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
		// ��ȡ�ļ�ͷ
	BOOL ReadFileHeader( CFile & file );
	// ��ȡ�ļ���Ϣͷ
	BOOL ReadInfoHeader( CFile & file );
	// �ͷ�����
	void FreeData();
	// �����ɫ����ɫ����
	int CalcQuadNum();
	// ��ȡ��ɫ������
	void ReadQuad( CFile &file );
	// �ж��Ƿ�Ϊ256ɫ�Ҷ�ͼ
	BOOL Is256Gray();
	// ����ͼ������
	void ReadImageData( CFile &file );
	// �ж�ͼ������
	IMAGE_TYPE CalcImageType();
	// ��24λ��ɫBMP����ת����24λ��ɫ����
	void BMPConvertColor24();
	// ��8λ��ɫBMP����ת��24λ��ɫ����
	void BMPConvertColor8();
	// ��8λ�Ҷ�BMP����ת��8λ�Ҷ�����
	void BMPConvertGray8();
	// ��8λ�Ҷ�����ת����24λ��ɫ
	void Gray8ConvertColor24( BYTE * grayData, CBaseColorInfo * colorData, int width, int height );
	// ��8λ�Ҷ�����ת����24λ��ɫ
	void Gray8ConvertColor24( int * grayData, CBaseColorInfo * colorData, int width, int height );


	// ��ʾͼ��(ͨ��ͼ������, ��ɫͼ��)
	void ShowPicByArray( CBaseColorInfo * colorData, int width, int height );
	// ��ʾͼ��(ͨ��ͼ������, �Ҷ�ͼ��)
	void ShowPicByArray( int * grayData, int width, int height );

	// ����BMPͼƬ
	bool SaveAsBmp( char * bmpName, unsigned char * imgBuf, int width, int height, int biBitCount, RGBQUAD * pColorTable );

//-------------------�Զ��庯��------------------------------------------//
	

//-----------------------------------------------------------------------//
public:
	// �ļ�ͷ
	BITMAPFILEHEADER _fileHeader;
	
	// ��ɫ��
	RGBQUAD * _quad;
	// ��ɫ����Ŀ
	int _numQuad;
	// ͼ������
	BYTE * _lpBuf;
	BITMAPINFO * _bitmapInfo;
	// ������ͼ������
	BYTE * _processBuf;
	// �Ƿ����bmp�ļ�
	bool _flag;
	
	// ��Ϣͷ
	BITMAPINFOHEADER _infoHeader;

	// ͼ������
	IMAGE_TYPE _imageType;
	// �Ҷ�(256�Ҷ�����, �����ϵ���, �����ҵ�˳������,һά��������)
	int * _grayData;
	// ��ɫ����(�����ϵ���, �����ҵ�˳������,һά��������)
	CBaseColorInfo * _colorData;
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGESTUDLG_H__8B975AD1_2A07_4F7F_B0EC_1B03621056BF__INCLUDED_)
