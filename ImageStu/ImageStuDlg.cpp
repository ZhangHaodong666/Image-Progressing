// ImageStuDlg.cpp : implementation file
//

#include "stdafx.h"
#include <windows.h>
#include "ImageStu.h"
#include "ImageStuDlg.h"
#include "DlgShowArray.h"
#include "CConnectedComponent.h"
#include "DlgTask.h"
#include "change.h"
#include "CRGBtoHSI.h"
#include "HuffmanMergeItem.h"
#include "ImgHuffman.h"
#include <math.h>
#include <sstream>
#include <algorithm>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageStuDlg dialog

CImageStuDlg::CImageStuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageStuDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImageStuDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// ͼ���Ѵ򿪱��
	_flag = false;

}

void CImageStuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageStuDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CImageStuDlg, CDialog)
	//{{AFX_MSG_MAP(CImageStuDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDC_FILE_OPEN, OnFileOpen)
	ON_WM_DESTROY()
	ON_COMMAND(IDC_FILE_SHOW_ARRAY, OnFileShowArray)
	ON_COMMAND(IDC_TEST, OnTest)
	ON_COMMAND(IDC_FILE_SAVE, OnFileSave)
	ON_COMMAND(IDC_FULL_RED, OnFullRed)
	ON_COMMAND(IDC_RED_BLUE, OnRedBlue)
	ON_COMMAND(IDC_COLOR_BLACK, OnColorBlack)
	ON_COMMAND(IDC_GRAY_BLACK, OnGrayBlack)
	ON_COMMAND(IDC_DIRECT_ZOOM, OnDirectZoom)
	ON_COMMAND(IDC_GRAY_ADJUST, OnGrayAdjust)
	ON_COMMAND(IDC_NEAREST_INTERPOLATION, OnNearestInterpolation)
	ON_COMMAND(IDC_BILINEAR_INTERPOLATION, OnBilinearInterpolation)
	ON_COMMAND(IDC_move, Onmove)
	ON_COMMAND(IDC_Horizontal_mirroring, OnHorizontalmirroring)
	ON_COMMAND(IDC_Vertical_Mirroring, OnVerticalMirroring)
	ON_COMMAND(IDC_Transpose, OnTranspose)
	ON_COMMAND(IDC_Rotating, OnRotating)
	ON_COMMAND(IDC_NEGATE, OnNegate)
	ON_COMMAND(IDC_LOGARITHM, OnLogarithm)
	ON_COMMAND(IDC_SHIFTING, OnShifting)
	ON_COMMAND(IDC_FEN_DUAN, OnFenDuan)
	ON_COMMAND(IDC_WEI_PING_MIAN, OnWeiPingMian)
	ON_COMMAND(IDC_ZHI_FANG, OnZhiFang)
	ON_COMMAND(IDC_LIN_YU, OnLinYu)
	ON_COMMAND(IDC_JIA_QUAN, OnJiaQuan)
	ON_COMMAND(IDC_JUN_ZHI_QUICK, OnJunZhiQuick)
	ON_COMMAND(ID_JUN_ZHI_YUZHI, OnJunZhiYuzhi)
	ON_COMMAND(IDC_JIA_QUAN_QUICK, OnJiaQuanQuick)
	ON_COMMAND(IDC_FEI_XIAN_XING, OnFeiXianXing)
	ON_COMMAND(IDC_FEI_XIAN_XING_X, OnFeiXianXingX)
	ON_COMMAND(IDC_lpls, Onlpls)
	ON_COMMAND(IDC_ROBERT, OnRobert)
	ON_COMMAND(IDC_SOBEL, OnSobel)
	ON_COMMAND(IDC_GRAY_COLOR, OnGrayColor)
	ON_COMMAND(IDC_RGB_HSI_RGB, OnRgbHsiRgb)
	ON_COMMAND(IDC_FU_SHI, OnFuShi)
	ON_COMMAND(IDC_PEN_ZHANG, OnPenZhang)
	ON_COMMAND(IDC_OPEN, OnOpen)
	ON_COMMAND(IDC_CLOSE, OnClose)
	ON_COMMAND(IDC_BIAN_JIE, OnBianJie)
	ON_COMMAND(IDC_TIAN_CHONG, OnTianChong)
	ON_COMMAND(IDC_LIAN_TONG, OnLianTong)
	ON_COMMAND(IDC_XI_HUA, OnXiHua)
	ON_COMMAND(IDC_Huffman, OnHuffman)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageStuDlg message handlers

BOOL CImageStuDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CImageStuDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CImageStuDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

	// ��ͼ
	CDC * pDC = GetDC();
	if( _flag == true ){
		
		// �Ѿ����ļ�
		SetDIBitsToDevice(
			  pDC->m_hDC  // �豸������
			, 0 // �豸������λͼ�������ʼ�߼�x����
			, 0 // �豸������λͼ�������ʼ�߼�y����
			, _infoHeader.biWidth // DIB�Ŀ��
			, _infoHeader.biHeight // DIB�ĸ߶�
			, 0 // DIB��ʼ��ȡ������������ݵ�xλ��
			, 0 // DIB��ʼ��ȡ������������ݵ�yλ��
			, 0 // DIB�����ص�ˮƽ�к�, ��ӦlpBits�ڴ滺�����ĵ�һ������
			, _infoHeader.biHeight  // DIB������
			, _lpBuf  // ��������
			, _bitmapInfo //BITMAPINFO����
			, DIB_RGB_COLORS // ��ʾ����ɫ
		);

	}
	ReleaseDC( pDC );

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CImageStuDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//////////////////////////////////////////////////////////////////////////
// ���ٶԻ���, ӳ��WM_DESTORY��Ϣ
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here

	if( _flag == true ){
		FreeData();
	}

	
}

/************************************************************************/
/*                           �˵�                                       */
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
// "�ļ�"-->"��"(IDC_FILE_OPEN)
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnFileOpen() 
{
	// TODO: Add your command handler code here
	
	LPCTSTR lpszFilter = "BMP Files(*.bmp)|*.bmp|�κ��ļ�|*.*|";
	CFileDialog dlg( TRUE, lpszFilter, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		lpszFilter, NULL );
	// �ļ���
	CString fileName;
	CFile file;
	// ���ļ�
	if( dlg.DoModal() == IDOK ){

		// �ļ���
		fileName = dlg.GetPathName();
		if( file.Open( fileName, CFile::modeRead | CFile::shareDenyNone, NULL ) == 0 ){
			// ��ȡ�ļ�ʧ��
			AfxMessageBox( "�޷����ļ�", MB_OK, MB_ICONERROR );
			return;
		}

		// ��ȡ�ļ�ͷ
		if( !ReadFileHeader( file ) ){
			return;
		}

		// ��ȡ��Ϣͷ 
		if( !ReadInfoHeader( file ) ){
			return;
		}

		// ��ǰ�������ļ��򿪣����ͷ���Ӧ������
		if( _flag == true ){
			FreeData();
			_flag = false;
		}

		// �����ɫ����ɫ����
		_numQuad = CalcQuadNum();
		// ��ȡ��ɫ������
		ReadQuad( file );

		// �ж�ͼ������
		_imageType = CalcImageType();

		// ����ͼ������
		ReadImageData( file );
		

		

		// ���䴦��������
		_processBuf = ( BYTE * )HeapAlloc( GetProcessHeap(), 0, _infoHeader.biSizeImage );
	
		// ��Ȳ���4�ı�������
		DWORD dwBytes = ((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) / 32;
		if(((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
			dwBytes++;
		}
		dwBytes *= 4;

		
		
		Invalidate( );

		int width = _infoHeader.biWidth;
        int height = _infoHeader.biHeight;

		// ����ռ�
		_colorData = new CBaseColorInfo[ width * height ];
		_grayData = new int[ width * height ];

		// ����ͼ�����ͣ�����ת������Ӧ��ͼ������
		if( _imageType == COLOR_24_BIT ){
			// 24λ��ɫͼ��
			BMPConvertColor24();
			
		}
		else if( _imageType == COLOR_8_BIT ){
			// 256��ɫͼ��
			BMPConvertColor8();
		}
		else if( _imageType == GRAY_8_BIT ){
			// 256�Ҷ�ͼ��
			BMPConvertGray8();
			// ��8λ�Ҷ�����ת����24λ��ɫ
			Gray8ConvertColor24( _grayData, _colorData, width, height );
		}
		else{
			MessageBox( "�ݲ�֧�ָ�ͼ������" );
			// �ر�ͼ��
			file.Close();
			FreeData();
			return;
		}

		// ͼ���ȡ���
		file.Close();
		_flag = true;

	}

}


//////////////////////////////////////////////////////////////////////////
// "�ļ�"-->"��ʾ����ͼ��"
// ��ת�����24λ��ɫ�����ڶԻ�������ʾ
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnFileShowArray() 
{
	// TODO: Add your command handler code here

	if(_flag == FALSE){
		MessageBox("û�д�ͼ��");
		return;
	}

	CDlgShowArray dlg;
	dlg.SetColorData( _colorData );
	dlg.SetWidth( _infoHeader.biWidth );
	dlg.SetHeight( _infoHeader.biHeight );
	dlg.DoModal();

}


//////////////////////////////////////////////////////////////////////////
// "�ļ�"-->"����"�˵�
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnFileSave() 
{
	// TODO: Add your command handler code here
	if( ! _flag  ){
		MessageBox( "û��ͼƬ���޷�����" );
		return;
	}
	
	CFileDialog dlg(false,"*.bmp",NULL,NULL,"*.bmp|*.bmp||");
	if (dlg.DoModal()==IDOK)
	{
		SaveAsBmp( (LPTSTR)(LPCTSTR)dlg.GetPathName(), _lpBuf, _infoHeader.biWidth, _infoHeader.biHeight, _infoHeader.biBitCount,
			_quad );
	}
	
}


/************************************************************************/
/*                         ˽�к���                                     */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
// ��ȡ�ļ�ͷ
// ����:
//   file: CFile &, BMP�ļ�
// ����ֵ:
//   BOOL, TRUE: �ɹ�; FALSE: ʧ��
//////////////////////////////////////////////////////////////////////////
BOOL CImageStuDlg::ReadFileHeader( CFile &file ){

	// ��ȡ�ļ�ͷ
	file.Read( &_fileHeader, sizeof( _fileHeader ) );
	// �ж��Ƿ�ΪBMP�ļ�
	if( _fileHeader.bfType != 0x4d42 ){
		// "BM"
		AfxMessageBox( "����BMP�ļ�", MB_OK, MB_ICONERROR );
		return FALSE;
	}

	// �ж��ļ��Ƿ���(�ļ���С�Ƿ����ļ�ͷ����Ϣһ��)
	if( file.GetLength() != _fileHeader.bfSize ){
		AfxMessageBox( "�ļ�����", MB_OK, MB_ICONERROR );
		return FALSE;
	}

	return TRUE;
	
}


//////////////////////////////////////////////////////////////////////////
// ��ȡ�ļ���Ϣͷ
// ����:
//   file: CFile &, �Ѿ��򿪵�BMP�ļ�
// ����ֵ:
//   BOOL, TRUE�ɹ�; ����ʧ��
//////////////////////////////////////////////////////////////////////////
BOOL CImageStuDlg::ReadInfoHeader( CFile &file ){

	// ��ȡ�ļ���Ϣͷ
	file.Read( &_infoHeader, sizeof( _infoHeader ) );

	// ��ͼƬ��ʽ�޶���8λͼ��
// 	if( _infoHeader.biBitCount != 8 ){
// 		AfxMessageBox( "����Ϊ8λ�Ҷ�ͼ", MB_OK, MB_ICONERROR );
// 		return FALSE;
// 	}

	return TRUE;

}


//////////////////////////////////////////////////////////////////////////
// �ͷ�����
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::FreeData(){

	HeapFree( GetProcessHeap(), 0, _bitmapInfo );
	HeapFree( GetProcessHeap(), 0, _lpBuf );
	// ����������
	HeapFree( GetProcessHeap(), 0, _processBuf );
	// �Ҷ���ɫ����
	delete [] _grayData;
	// ��ɫ��ɫ����
	delete [] _colorData;



}

//////////////////////////////////////////////////////////////////////////
// �����ɫ����ɫ����
// ����: ��
// ����ֵ:
//   int, ��ɫ����ɫ����
//////////////////////////////////////////////////////////////////////////
int CImageStuDlg::CalcQuadNum(){

	// �����ɫ������
	int numQuad = 0;
	if( _infoHeader.biBitCount < 24){
		// �൱��2��biBitCount�η�
		numQuad = ( 1 << _infoHeader.biBitCount );
	}

	return numQuad;

}

//////////////////////////////////////////////////////////////////////////
// ��ȡ��ɫ������
// ����:
//   file: CFile &, BMP�ļ�
// ����ֵ: ��
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ReadQuad( CFile &file ){

	// Ϊͼ����Ϣpbi����ռ�
	_bitmapInfo = ( BITMAPINFO * )HeapAlloc( 
		GetProcessHeap(), 
		0, 
		sizeof( BITMAPINFOHEADER ) + _numQuad * sizeof( RGBQUAD ) 
	);
	memcpy( _bitmapInfo, &_infoHeader, sizeof( _infoHeader ) );
	_quad = ( RGBQUAD * )( ( BYTE *)_bitmapInfo + sizeof( BITMAPINFOHEADER ) );

	// ��ȡ��ɫ��
	if( _numQuad != 0 ){
		file.Read( _quad, sizeof( RGBQUAD ) * _numQuad );
	}

}

//////////////////////////////////////////////////////////////////////////
// �ж��Ƿ�Ϊ256ɫ�Ҷ�ͼ
// �ж����ݣ���ɫ����������ɫ�ĵ�RGB��������Ӧ�����
// BOOL: TRUEΪ256ɫ�Ҷ�ͼ
//////////////////////////////////////////////////////////////////////////
BOOL CImageStuDlg::Is256Gray(){

	BOOL result = TRUE;
	for( int i = 0; i <= _numQuad - 1; i++ ){
		RGBQUAD color = *( _quad + i );
		//TRACE( "%d: %d, %d, %d\n", i, color.rgbRed,  color.rgbGreen, color.rgbBlue );
		if( !( color.rgbRed == color.rgbGreen && color.rgbRed == color.rgbBlue ) ){
			result = FALSE;
			break;
		}
	}
	
	return result;

}

//////////////////////////////////////////////////////////////////////////
// ����ͼ������
// ����:
//   file: CFile &, BMPͼ��
// ����ֵ: ��
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ReadImageData( CFile &file ){

	// Ϊͼ����������ռ�
	_infoHeader.biSizeImage = _fileHeader.bfSize - _fileHeader.bfOffBits;
	_lpBuf = ( BYTE *)HeapAlloc( GetProcessHeap(), 0, _infoHeader.biSizeImage );
	// ��ȡͼ������
	file.Read( _lpBuf, _infoHeader.biSizeImage );

}

//////////////////////////////////////////////////////////////////////////
// �ж�ͼ������
// ����: ��
// ����ֵ: IMAGE_TYPE, ͼ������, ����ö��IMAGE_TYPE�Ķ���
//////////////////////////////////////////////////////////////////////////
IMAGE_TYPE CImageStuDlg::CalcImageType(){

	IMAGE_TYPE type = COLOR_24_BIT;
	if( _infoHeader.biBitCount == IMAGE_TYPE_BIT_24 ){
		// 24��ɫͼ��
		type = COLOR_24_BIT;
		//MessageBox( "24λͼ��" );
	}
	else if( _infoHeader.biBitCount == IMAGE_TYPE_BIT_1 ){
		// ��ֵͼ��
		type = GRAY_1_BIT;
		//MessageBox( "1λͼ��" );
	}
	else if( _infoHeader.biBitCount == IMAGE_TYPE_BIT_8 ){
		// 8λ
		if( Is256Gray() ){
			// 8λ�Ҷ�ͼ��
			type = GRAY_8_BIT;
			//MessageBox( "8λ�Ҷ�ͼ��" );
		}
		else{
			// 8λ��ɫͼ��
			type = COLOR_8_BIT;
			//MessageBox( "8λ��ɫͼ��" );
		}
	}

	return type;

}

//////////////////////////////////////////////////////////////////////////
// ��BMP����ת����24λ��ɫ����
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertColor24(){

	// ��Ȳ���4�ı�������
	DWORD dwBytes = ((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if(((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// �����ɫ����

	int i,j;

	for( i = 0; i <= height - 1; i++ ){
		for( j = 0; j <= width - 1; j++ ){
			
			// BMPͼƬ�����е�����
			DWORD index = i * 3 * width + 3 * j;
			if( dwBytes % 3 != 0 ){
				index = i * dwBytes + 3 * j ;
			}
			// ��ɫ�����е�����
			DWORD resultIndex = ( height - 1 - i ) * width + j;
			_colorData[ resultIndex ].SetRed( _lpBuf[ index  + 2 ] );
			_colorData[ resultIndex ].SetGreen( _lpBuf[ index  + 1 ] );
			_colorData[ resultIndex ].SetBlue( _lpBuf[ index ] );

		}// for j
	}// for i 

}

//////////////////////////////////////////////////////////////////////////
// ��8λ��ɫBMP����ת��24λ��ɫ����
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertColor8(){

	// ��Ȳ���4�ı�������
	DWORD dwBytes = ((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if(((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// �����ɫ����
// 	if( _colorFlag == true ){
// 		delete [] _colorData;
// 	}
// 	_colorData = new CBaseColorInfo[ width * height ];
// 	_colorFlag = true;


	int i,j;
// 	for( i = 0; i <= 100; i++ ){
// 		TRACE( "%d->%d,", i, _lpBuf[ i ] );
// 	}
// 	TRACE( "\n" );
	for( i = 0; i <= height - 1; i++ ){
		for( j = 0; j <= width - 1; j++ ){
			
			// BMPͼƬ�����е�����
			DWORD index = i * dwBytes + j ;

			// ��ɫ�����е�����
			DWORD resultIndex = ( height - 1 - i ) * width + j;
// 			if( index >= _infoHeader.biSizeImage || resultIndex >= _infoHeader.biSizeImage ){
// 				TRACE( "*** i = %d, j = %d, index = %d, resultIndex = %d, widht = %d, height = %d \n", 
// 					i, j, index, resultIndex, width, height );
// 			}

// 			int red = _lpBuf[ index ] + 2;
// 			int green = _lpBuf[ index ] + 1;
// 			int blue = _lpBuf[ index ] + 0;
// 
// 			if( resultIndex <= width * height - 1 ){
// 			_colorData[ resultIndex ].SetRed( red );
// 			_colorData[ resultIndex ].SetGreen( green );
// 			_colorData[ resultIndex ].SetBlue( blue );
// 			}

			_colorData[ resultIndex ].SetRed( _quad[ _lpBuf[ index ] ].rgbRed );
			_colorData[ resultIndex ].SetGreen( _quad[ _lpBuf[ index ] ].rgbGreen );
			_colorData[ resultIndex ].SetBlue( _quad[ _lpBuf[ index ] ].rgbBlue );

// 			TRACE( "%d,%d,%d\t", _colorData[ resultIndex ].GetRed(),
// 				_colorData[ resultIndex ].GetGreen(), 
// 				_colorData[ resultIndex ].GetBlue() );

// 			if( i <= 10 && j <= 10 ){
// 			  TRACE( "(%d,%d,%d)->(%d,%d,%d) ", i,j,index, _colorData[ resultIndex ].GetRed(),
// 				_colorData[ resultIndex ].GetGreen(), 
// 				_colorData[ resultIndex ].GetBlue() );
/*			}*/

		}// for j
	}// for i 

}

//////////////////////////////////////////////////////////////////////////
// ��8λ�Ҷ�BMP����ת��8λ�Ҷ�����
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertGray8(){

	// ��Ȳ���4�ı�������
	DWORD dwBytes = ((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if(((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// �����ɫ����
// 	if( _colorFlag == true ){
// 		delete [] _colorData;
// 	}
// 	_grayData = new BYTE[ width * height ];
// 	_grayFlag = true;


	int i,j;
// 	for( i = 0; i <= 100; i++ ){
// 		TRACE( "%d->%d,", i, _lpBuf[ i ] );
// 	}
// 	TRACE( "\n" );
	for( i = 0; i <= height - 1; i++ ){
		for( j = 0; j <= width - 1; j++ ){
			
			// BMPͼƬ�����е�����
			DWORD index = i * dwBytes + j ;

			// ��ɫ�����е�����
			DWORD resultIndex = ( height - 1 - i ) * width + j;
// 			if( index >= _infoHeader.biSizeImage || resultIndex >= _infoHeader.biSizeImage ){
// 				TRACE( "*** i = %d, j = %d, index = %d, resultIndex = %d, widht = %d, height = %d \n", 
// 					i, j, index, resultIndex, width, height );
// 			}

// 			int red = _lpBuf[ index ] + 2;
// 			int green = _lpBuf[ index ] + 1;
// 			int blue = _lpBuf[ index ] + 0;
// 
// 			if( resultIndex <= width * height - 1 ){
// 			_colorData[ resultIndex ].SetRed( red );
// 			_colorData[ resultIndex ].SetGreen( green );
// 			_colorData[ resultIndex ].SetBlue( blue );
// 			}

			_grayData[ resultIndex ] = _lpBuf[ index ];


// 			TRACE( "%d,%d,%d\t", _colorData[ resultIndex ].GetRed(),
// 				_colorData[ resultIndex ].GetGreen(), 
// 				_colorData[ resultIndex ].GetBlue() );

// 			if( i <= 10 && j <= 10 ){
// 			  TRACE( "(%d,%d,%d)->(%d,%d,%d) ", i,j,index, _colorData[ resultIndex ].GetRed(),
// 				_colorData[ resultIndex ].GetGreen(), 
// 				_colorData[ resultIndex ].GetBlue() );
/*			}*/

		}// for j
	}// for i 

}

//////////////////////////////////////////////////////////////////////////
// ��8λ�Ҷ�����ת����24λ��ɫ
// �Ҷ�ͼ��RGBֵ����ͬ
// ����:
//   grayData: BYTE *, �Ҷ�����
//   colorData: CBaseColorInfo *, 24λ��ɫ����
//   width: ͼƬ���
//   height: ͼƬ�߶�
//  ����ֵ: ��
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::Gray8ConvertColor24( BYTE * grayData, 
										    CBaseColorInfo * colorData, 
											int width, 
											int height ){


	int length = width * height;
	for( int i = 0; i <= length - 1; i++ ){
		colorData[ i ].SetRed( grayData[ i ] );
		colorData[ i ].SetGreen( grayData[ i ] );
		colorData[ i ].SetBlue( grayData[ i ] );
	}

}

// ��8λ�Ҷ�����ת����24λ��ɫ
void CImageStuDlg::Gray8ConvertColor24( int * grayData, CBaseColorInfo * colorData, int width, int height ){

	int length = width * height;
	for( int i = 0; i <= length - 1; i++ ){
		colorData[ i ].SetRed( grayData[ i ] );
		colorData[ i ].SetGreen( grayData[ i ] );
		colorData[ i ].SetBlue( grayData[ i ] );
	}

}

//////////////////////////////////////////////////////////////////////////
// ��ʾͼ��(ͨ��ͼ������,��ɫͼ��)
// ����:
//   colorData: CBaseColorInfo, ��ɫ����
//   width: int, ͼ����
//   height: int, ͼ��߶�
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ShowPicByArray( CBaseColorInfo * colorData, 
								   int width, 
								   int height ){

	CDlgShowArray dlg;
	// ͼ������(24λ��ɫͼ��)
	dlg.SetColorData( colorData );
	// ͼ����
	dlg.SetWidth( width );
	// ͼ��߶�
	dlg.SetHeight( height );
	// ��ʾ�Ի���
	dlg.DoModal();

}




//////////////////////////////////////////////////////////////////////////
// ��ʾͼ��(ͨ��ͼ������, �Ҷ�ͼ��)
// ����:
//   colorData: CBaseColorInfo, �Ҷ�ͼ������
//   width: int, ͼ����
//   height: int, ͼ��߶�
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ShowPicByArray( int * grayData, 
								   int width, 
								   int height ){

	// ���Ҷ�ͼ��ת�ɲ�ɫͼ��
	CBaseColorInfo * colorData = new CBaseColorInfo[ width * height ];
	Gray8ConvertColor24( grayData, colorData, width, height );

	CDlgShowArray dlg;
	// ͼ������(24λ��ɫͼ��)
	dlg.SetColorData( colorData );
	// ͼ����
	dlg.SetWidth( width );
	// ͼ��߶�
	dlg.SetHeight( height );
	// ��ʾ�Ի���
	dlg.DoModal();

	// �ͷŲ�ɫͼ��
	delete [] colorData;

}











void CImageStuDlg::OnTest() 
{
	// TODO: Add your command handler code here
	int x, y;
	int width = 800;
	int height = 600;
	CBaseColorInfo * img = new CBaseColorInfo[ width * height ];
	for( x = 0; x < width; ++x ){
		for( y = 0; y < height; ++y ){
			int index = y * width + x;
			if( x % 10 == 0 ){
				img[ index ] = CBaseColorInfo( 255, 0, 0 );
			}
			else{
				img[ index ] = CBaseColorInfo( 0, 255, 0 );
			}
			
		}
	}

	// ��ʾͼ��
	ShowPicByArray( img, width, height );

	delete []img;
}


//////////////////////////////////////////////////////////////////////////
// ���ܣ�����BMPͼƬ
// ������
//   bmpName: char *, �ļ���(��·�����ļ���׺)
//   imgBuf: unsigned char *, ͼ������
//   width: int, ͼ����
//   height: int, ͼ��߶�
//   biBitCount: int, �������
//   pColorTable: RGBAUAD *, ��ɫ��
//////////////////////////////////////////////////////////////////////////
bool CImageStuDlg::SaveAsBmp( char * bmpName, 
							  unsigned char * imgBuf, 
							  int width, 
							  int height,
							  int biBitCount, 
							  RGBQUAD * pColorTable 
							 ){
	
	// ���λͼ����Ϊ�գ���û�����ݴ���
	if( !imgBuf ){
		return false;
	}
	
	// ��ɫ���С�����ֽ�Ϊ��λ���Ҷ�ͼ����ɫ��Ϊ1024����ɫͼ����ɫ���СΪ0
	int colorTableSize = 0;
	if( biBitCount == 8 ){
		colorTableSize = 1024; // �о���һ����ȷ
	} 
	
	// �����洢ͼ������ÿ���ֽ���תΪ4�ı���
	int lineByte = ( width * biBitCount / 8 + 3 ) / 4 * 4;
	// �Զ����Ƶ�д�ķ�ʽ���ļ�
	FILE *fp = fopen( bmpName, "wb" );
	if( !fp ){
		return false;
	}
	
	// ����λͼ�ļ�ͷ�ṹ��������д�ļ�ͷ��Ϣ
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;// bmp����
	// bfSize��ͼ���ļ�4����ɲ���֮��
	fileHead.bfSize = sizeof( BITMAPFILEHEADER ) 
		+ sizeof( BITMAPINFOHEADER )
		+ colorTableSize 
		+ lineByte * height; // ͼ�������ֽ���
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
	
	// bfOffBits��ͼ���ļ�ǰ����������ռ�֮��
	fileHead.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)  + colorTableSize;
	// �ļ�ͷд���ļ�
	fwrite( &fileHead, sizeof( BITMAPFILEHEADER ) , 1, fp );
	
	// ����λͼ��Ϣͷ�ṹ��������д��Ϣͷ��Ϣ
	BITMAPINFOHEADER head;
	head.biSize = sizeof(BITMAPINFOHEADER); // λͼ��Ϣͷ�ṹ�Ĵ�С(40���ֽ�)
	head.biWidth = width;// ͼ���ȣ�������Ϊ��λ
	head.biHeight = height;// ͼ��߶ȣ�������Ϊ��λ
	head.biPlanes = 1;// ����Ϊ1
	head.biBitCount = biBitCount; // ������ȣ�ÿ�����ص�Ϊ��(bit��)
	head.biCompression = BI_RGB; // ͼ���Ƿ�ѹ����һ����δѹ����
	head.biSizeImage = lineByte * height; // ʵ�ʵ�λͼ����ռ�ݵ��ֽ���
	head.biXPelsPerMeter = 0; // Ŀ���豸��ˮƽ�ֱ���
	head.biYPelsPerMeter = 0; // Ŀ���豸�Ĵ�ֱ�ֱ���
	head.biClrUsed = 0; // ��ͼ��ʵ���õ�����ɫ��
	head.biClrImportant = 0; // ��ͼ����Ҫ����ɫ�����Ϊ0�������е���ɫ����Ҫ 
	
	// дλͼ��Ϣͷ���ڴ�
	fwrite( &head, sizeof( BITMAPINFOHEADER ), 1, fp );
	
	// ���ͼ��ʱ�Ҷ�ͼ������ɫ��д���ļ�
	if( biBitCount == 8 ){
		fwrite( pColorTable, sizeof( RGBQUAD ), 256, fp );
	}
	
	// дλͼ���ݽ��ļ�
	fwrite( imgBuf, height * lineByte, 1, fp );
	
	// �ر��ļ�
	fclose( fp );
	
	return true;
	
}



void CImageStuDlg::OnFullRed() 
{
	// TODO: Add your command handler code here
	int width = 800;
	int height = 600;
	int size = width * height;
	CBaseColorInfo * img = new CBaseColorInfo [size];
	for(int i = 0;i<size;++i){
		img[i]=CBaseColorInfo(255,0,0);
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnRedBlue() 
{
	// TODO: Add your command handler code here
	int width = 800;
	int height = 600;
	CBaseColorInfo * img = new CBaseColorInfo [ width * height ];
	for(int y = 0; y < height; y+=30 ){
		for(int x = 0; x < width; x+=40){	
			for(int h = 0; h < 30; h++){
				for(int w = 0; w < 40; w++){
					int index = (y+h) * width + (x+w);
					if((y%60==0&&x%80==0)||(y%60==30&&x%80==40)){
						img[ index ] = CBaseColorInfo( 255, 0, 0 );
					}
					else{
						img[ index ] = CBaseColorInfo( 0, 0, 255 );
					}
				}
			}
		}
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnColorBlack() 
{
	// TODO: Add your command handler code here
	if(_flag==false){
		MessageBox("ͼƬδ��!");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	CBaseColorInfo * newColor = new CBaseColorInfo [ width * height ];
	for(int y = 0; y < height; y++ ){
		for(int x = 0; x < width; x++ ){	
			int index = y * width + x;
			CBaseColorInfo info = _colorData[index];
			int gray = 0.299*info.GetRed()+ 0.587*info.GetGreen()+ 0.114*info.GetBlue();
			newColor[ index ].SetRed( gray );
			newColor[ index ].SetGreen( gray );
			newColor[ index ].SetBlue( gray );
		}
	}
	ShowPicByArray(newColor,width,height);
	delete [] newColor;
}

void CImageStuDlg::OnGrayBlack() 
{
	// TODO: Add your command handler code here
	if(_flag==false){
		MessageBox("ͼƬδ�򿪣�");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	CBaseColorInfo * newColor = new CBaseColorInfo [ width * height ];
	for(int y = 0; y < height; y++ ){
		for(int x = 0; x < width; x++ ){	
			int index = y * width + x;
			CBaseColorInfo info = _colorData[index];
			int gray = info.GetRed();
			if(gray>=120){
				newColor[ index ] = CBaseColorInfo( 255, 255, 255 );
			}
			else{
				newColor[ index ] = CBaseColorInfo( 0, 0, 0 );
			}
		}
	}
	ShowPicByArray(newColor,width,height);
	delete [] newColor;
}

void CImageStuDlg::OnGrayAdjust() 
{
	// TODO: Add your command handler code here
	if(_flag==false){
		MessageBox("ͼƬδ�򿪣�");
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	
	int level = 256 / 8;
	for(int i = 0; i < size; ++i){
		int oldGray = _grayData[ i ];
		int gray = oldGray / level * level;
		img[i] = gray;
	}

	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnDirectZoom() 
{
	// TODO: Add your command handler code here
	if(_flag==false){
		MessageBox("ͼƬδ�򿪣�");
		return;
	}

	int oldwidth = _infoHeader.biWidth;
	int oldheight = _infoHeader.biHeight;

	double scale = 0.5;
	int width = oldwidth * scale;
	int height = oldheight *scale;
	int size = width * height;
	CBaseColorInfo * img = new CBaseColorInfo[size];

	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			int oldX = x / scale;
			int oldY = y / scale;

			int newIndex = y * width + x;
			int oldIndex = oldY * oldwidth + oldX;
			img[ newIndex ] = _colorData[ oldIndex ];
		}
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}


void CImageStuDlg::OnNearestInterpolation() 
{
	// TODO: Add your command handler code here
	if(_flag==false){
		MessageBox("ͼƬδ�򿪣�");
		return;
	}

	int oldwidth = _infoHeader.biWidth;
	int oldheight = _infoHeader.biHeight;

	double scale = 1.5;
	int width = oldwidth * scale;
	int height = oldheight *scale;
	int size = width * height;
	int * img = new int[size];

	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			int oldX = x / scale +0.5;
			int oldY = y / scale +0.5;

			int newIndex = y * width + x;
			int oldIndex = oldY * oldwidth + oldX;
			img[ newIndex ] = _grayData[ oldIndex ];
		}
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnBilinearInterpolation() 
{
	// TODO: Add your command handler code here
	if(_flag==false){
		MessageBox("ͼƬδ�򿪣�");
		return;
	}

	int oldwidth = _infoHeader.biWidth;
	int oldheight = _infoHeader.biHeight;

	double scale = 1.5;
	int width = oldwidth * scale;
	int height = oldheight *scale;
	int size = width * height;
	int * img = new int[size];

	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			int oldX = x / scale;
			int oldY = y / scale;
			int Cx = oldX,Cy = oldY;
			int Bx = oldX + 1,By = oldY + 1;

			int CIndex = oldY * oldwidth + oldX;
			int DIndex = CIndex + 1;
			int AIndex = CIndex + oldwidth;
			int BIndex = DIndex + oldwidth;
			
			int gA = _grayData[ AIndex ];
			int gB = _grayData[ BIndex ];
			int gC = _grayData[ CIndex ];
			int gD = _grayData[ DIndex ];
			double gE = ( oldX - Cx ) * ( gB - gA ) + gA;
			double gF = ( oldX - Cx ) * ( gD - gC ) + gC;
			double gray = ( oldY - Cy) * ( gF - gE ) + gE;

			int newIndex = y * width + x;
			img[ newIndex ] = gray;

		}
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::Onmove() 
{
	// ƽ��
	if(_flag==false){
		MessageBox("ͼƬδ�򿪣�");
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;	
	int size = width * height;
	CBaseColorInfo * img = new CBaseColorInfo[size];

	int tx = -20, ty = -20;

	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			int oldX = x - tx;
			int oldY = y - ty;
			int newIndex = y * width + x;
			if(oldX<0||oldX>=width||oldY<0||oldY>=height){
				img[ newIndex ] = CBaseColorInfo(255,255,255);
			}else{
				int oldIndex = oldY * width + oldX;
				img[ newIndex ] = _colorData[ oldIndex ];
			}		
		}
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnHorizontalmirroring() 
{
	// ˮƽ����
	if(_flag==false){
		MessageBox("ͼƬδ�򿪣�");
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;	
	int size = width * height;
	CBaseColorInfo * img = new CBaseColorInfo[size];

	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			int newX = - x + width - 1;
			int newIndex = y * width + newX;
			int oldIndex = y * width + x;
			img[ newIndex ] = _colorData[ oldIndex ];
					
		}
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnVerticalMirroring() 
{
	// ��ֱ����
	if(_flag==false){
		MessageBox("ͼƬδ�򿪣�");
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;	
	int size = width * height;
	CBaseColorInfo * img = new CBaseColorInfo[size];

	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			int newY = - y + height - 1;
			int newIndex = newY * width + x;
			int oldIndex = y * width + x;
			img[ newIndex ] = _colorData[ oldIndex ];
					
		}
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnTranspose() 
{
	// ת��
	if(_flag==false){
		MessageBox("ͼƬδ�򿪣�");
		return;
	}

	int width = _infoHeader.biHeight;
	int height = _infoHeader.biWidth;	
	int size = width * height;
	CBaseColorInfo * img = new CBaseColorInfo[size];

	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			int newIndex = y * width + x;
			int oldIndex = x * height + y;
			img[ newIndex ] = _colorData[ oldIndex ];
					
		}
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnRotating() 
{
	// ��ת
	if(_flag==false){
		MessageBox("ͼƬδ�򿪣�");
		return;
	}
	int a = 20;
	int change_a = -a;
	double ca = cos( change_a * acos(-1.0) / 180);
	double sa = sin( change_a * acos(-1.0) / 180);

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];

	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			int oldX = ca * x + sa * y + 0.5;
			int oldY = -sa * x + ca * y + 0.5;
			int newIndex = y * width + x;
			if(oldX<0||oldX>=width||oldY<0||oldY>=height){
				img[ newIndex ] = 255;
			}else{
				//int oldIndex = oldY * width + oldX;
				//img[ newIndex ] = _grayData[ oldIndex ];

				int Cx = oldX,Cy = oldY;
				int Bx = oldX + 1,By = oldY + 1;

				if(Bx>=width||By>=height){
					img[ newIndex ] = 255;
				}else{
					int CIndex = oldY * width + oldX;
					int DIndex = CIndex + 1;
					int AIndex = CIndex + width;
					int BIndex = DIndex + width;
					
					int gA = _grayData[ AIndex ];
					int gB = _grayData[ BIndex ];
					int gC = _grayData[ CIndex ];
					int gD = _grayData[ DIndex ];
					
					double gE = ( oldX - Cx ) * ( gB - gA ) + gA;
					double gF = ( oldX - Cx ) * ( gD - gC ) + gC;
					double gray = ( oldY - Cy) * ( gF - gE ) + gE;

					int newIndex = y * width + x;
					img[ newIndex ] = gray;	
				}
			}		
		}
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnNegate() 
{
	// ͼ��ת
	if(_flag==false){
		MessageBox("ͼƬδ�򿪣�");
		return;
	}

	const int L = 255;
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;	
	int size = width * height;
	int * img = new int[size];

	for(int i = 0; i < size; i++){
		img[i] = L-1-_grayData[i];
	}

	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnLogarithm() 
{
	// �����任
	if(_flag==false){
		MessageBox("ͼƬδ�򿪣�");
		return;
	}

	int c = 40;
	double const LEVEL = 256;
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;	
	int size = width * height;
	int * img = new int[size];

	for(int i = 0; i < size; i++){
		img[i] = c*log(_grayData[i]/(LEVEL-1)+1)*(LEVEL-1);
	}


	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnShifting() 
{
	// ڤ�ɱ任
	if(_flag==false){
		MessageBox("ͼƬδ�򿪣�");
		return;
	}

	double c = 1;
	double y = 4.0;
	double const LEVEL = 256;
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;	
	int size = width * height;
	int * img = new int[size];

	for(int i = 0; i < size; i++){
		img[i] = c*pow(_grayData[i]/(LEVEL-1),y)*(LEVEL-1);
	}


	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnFenDuan() 
{
	// �ֶ����Ա任����
	if(_flag==false){
		MessageBox("ͼƬδ�򿪣�");
		return;
	}
	
	double const LEVEL = 256;
	
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;	
	int size = width * height;
	int * img = new int[size];

	/*int rmin=256,rmax=0;
	for(int i = 0; i < size; i++){
		if(_grayData[i]>rmax){
			rmax = _grayData[i];
		}
		if(_grayData[i]<rmin){
			rmin =_grayData[i];
		}
	}
	
	int r1=rmin,r2=rmax,s1=0,s2=LEVEL-1;
	*/
	int sum=0,avg=0;
	for(int i = 0; i < size; i++){
		sum+=_grayData[i];
	}
	avg = sum/size;
	int r1=avg,r2=avg,s1=0,s2=LEVEL-1;
	for( i = 0; i < size; i++){
		int gray = _grayData[i];
		if(gray <= r1){
			img[i] = gray * s1 / r1;
		}else if(gray >= r2){
			img[i] = (gray-r2) *(LEVEL-1-s2)/(LEVEL-1-r2)+s2;
		}else{
			img[i] = (gray-r1)*(s2-s1)/(r2-r1)+s1;
		}
	}


	ShowPicByArray(img,width,height);
	delete [] img;
	
}

void CImageStuDlg::OnWeiPingMian() 
{
	// λƽ��
	if(_flag==false){
		MessageBox("ͼƬδ�򿪣�");
		return;
	}

	double const LEVEL = 256;
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;	
	int size = width * height;
	int * img = new int[size];

	//����ƽ��8
	for(int i = 0; i < size; i++){
		int gray = _grayData[i];
		if(gray <= 127){
			img[i] = 0;
		}else if(gray >= 128){
			img[i] = LEVEL-1;
		}
	}

	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnZhiFang() 
{
	// ֱ��ͼ���⻯
	if(_flag==false){
		MessageBox("ͼƬδ�򿪣�");
		return;
	}

	int const LEVEL = 256;
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;	
	double size = width * height;
	int * img = new int[size];

	int YuanShi[LEVEL]={0};
	double GuiYi[LEVEL]={0};
	double LeiJi[LEVEL]={0};

	for(int i = 0; i < size; i++){
		YuanShi[_grayData[i]]++;
	}

	for(i = 0; i < LEVEL; i++){
		GuiYi[i]=YuanShi[i]/size;
	}

	LeiJi[0]=GuiYi[0];
	for(i = 1; i < LEVEL; i++){
		LeiJi[i]=GuiYi[i]+LeiJi[i-1];
	}
	
	for(i = 0; i < size; i++){
		int gray=_grayData[i];
		img[i]=(LEVEL-1)*LeiJi[gray];
	}

	ShowPicByArray(img,width,height);
	delete [] img;
	
}

void CImageStuDlg::OnLinYu() 
{
	// �����ֵ�˲�
	if(_flag == false)
	{
		MessageBox("ͼƬδ�򿪣�");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	int sum = 0;

	int scale = 15;
	for(int y = scale/2; y < height - scale/2; y++)
	{
		for(int x = scale/2; x < width - scale/2; x++)
		{
			for(int j = y - scale/2; j <= y + scale/2; j++)
			{
				for(int i = x - scale/2; i <= x + scale/2; i++)
				{
					sum += _grayData[j * width + i];
				}
			}
			int index = y * width + x;
			img[index] = sum / ( scale * scale );
			sum = 0;
		}
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnJiaQuan() 
{
	// �����Ȩ�˲�
	if(_flag == false)
	{
		MessageBox("ͼƬδ�򿪣�");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	int sum = 0;

	int scale = 15;
	int sum_weight=0;
	for(int y = scale/2; y < height - scale/2; y++)
	{
		for(int x = scale/2; x < width - scale/2; x++)
		{
			for(int j = y - scale/2; j <= y + scale/2; j++)
			{
				for(int i = x - scale/2; i <= x + scale/2; i++)
				{
					int power = pow( 2 , scale - 1 - abs( x - i) - abs( y - j));
					sum += _grayData[ j * width + i ] * power;
					sum_weight += power;
				}
			}
			int index = y * width + x;
			img[index] = sum / sum_weight;
			sum = 0;
			sum_weight = 0;
		}
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}



void CImageStuDlg::OnJunZhiQuick() 
{
	// �����ֵ�˲� ���ټ���
	if(_flag == false)
	{
		MessageBox("ͼƬδ�򿪣�");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	memset(img,0,sizeof(int)*size);
	int sum = 0;

	int scale = 15;

	//ˮƽ���
	int * temp= new int[size];
	memset(temp,0,sizeof(int)*size);
	for(int y = 0; y < height ; y++)
	{
		for(int x = scale/2; x < width - scale/2; x++)
		{
			if(x==scale/2)
			{
				for(int m = x - scale/2; m <= x + scale/2; m++)
				{
					temp[y*width+x]+=_grayData[y*width+m];
				}
			}
			else
			{
				temp[y*width+x]=temp[y*width+x-1] - _grayData[y*width+x-scale/2-1] + _grayData[y*width+x+scale/2];
			}
		}
	}

	//��ֱ���
	
	for(y = scale/2; y < height - scale/2 ; y++)
	{
		for(int x = scale/2; x < width- scale/2; x++)
		{
			if(y==scale/2)
			{
				for(int n = y - scale/2; n <= y + scale/2; n++)
				{
					img[y*width+x]+=temp[n*width+x];
				}
			}
			else
			{
				img[y*width+x]=img[(y-1)*width+x]-temp[(y-scale/2-1)*width+x]+temp[(y+scale/2)*width+x];
			}
		}
	}

	//����Ȩ��
	for(int i = 0; i < size;i++)
	{
		img[i] /= scale*scale;
	}

	ShowPicByArray(img,width,height);
	delete [] temp;
	delete [] img;
}

void CImageStuDlg::OnJunZhiYuzhi() 
{
	// �����ֵ�˲� ��ֵ
	if(_flag == false)
	{
		MessageBox("ͼƬδ�򿪣�");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	memset(img,0,sizeof(int)*size);
	int sum = 0;

	int scale = 15;

	int max=0;
	for(int i=0; i < size; i++)
	{
		if(_grayData[i]>max)
		{
			max=_grayData[i];
		}
	}
	//ˮƽ���
	int * temp= new int[size];
	memset(temp,0,sizeof(int)*size);
	for(int y = 0; y < height ; y++)
	{
		for(int x = scale/2; x < width - scale/2; x++)
		{
			if(x==scale/2)
			{
				for(int m = x - scale/2; m <= x + scale/2; m++)
				{
					temp[y*width+x]+=_grayData[y*width+m];
				}
			}
			else
			{
				temp[y*width+x]=temp[y*width+x-1] - _grayData[y*width+x-scale/2-1] + _grayData[y*width+x+scale/2];
			}
		}
	}

	//��ֱ���
	
	for(y = scale/2; y < height - scale/2 ; y++)
	{
		for(int x = scale/2; x < width- scale/2; x++)
		{
			if(y==scale/2)
			{
				for(int n = y - scale/2; n <= y + scale/2; n++)
				{
					img[y*width+x]+=temp[n*width+x];
				}
			}
			else
			{
				img[y*width+x]=img[(y-1)*width+x]-temp[(y-scale/2-1)*width+x]+temp[(y+scale/2)*width+x];
			}
		}
	}

	//����Ȩ��
	for( i = 0; i < size; i++)
	{
		img[i] /= scale*scale;
		if(img[i]>=max*0.4)
		{
			img[i]=_grayData[i];
		}
		else
		{
			img[i]=0;
		}
	}

	ShowPicByArray(img,width,height);
	delete [] temp;
	delete [] img;
	
}

void CImageStuDlg::OnJiaQuanQuick() 
{
	// �����Ȩ�˲� ���ټ���
	if(_flag == false)
	{
		MessageBox("ͼƬδ�򿪣�");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	memset(img,0,sizeof(int)*size);

	int scale = 15;

	int pow_sum=0;
	for(int i = 0; i < scale; i++)
	{
		for(int j = 0; j < scale;j++)
		{
			pow_sum+=pow(2,scale-1-abs(scale/2-i)-abs(scale/2-j));
		}
	}
	//ˮƽ���
	int * temp= new int[size];
	memset(temp,0,sizeof(int)*size);
	for(int y = 0; y < height ; y++)
	{
		for(int x = scale/2; x < width - scale/2; x++)
		{
			for(int m = x - scale/2; m <= x + scale/2; m++)
			{
				temp[y*width+x]+=_grayData[y*width+m]*pow(2,scale/2-abs(x-m));
			}
		}
	}

	//��ֱ���
	
	for(y = scale/2; y < height - scale/2 ; y++)
	{
		for(int x = scale/2; x < width- scale/2; x++)
		{
			for(int n = y - scale/2; n <= y + scale/2; n++)
			{
				img[y*width+x]+=temp[n*width+x]*pow(2,scale/2-abs(y-n));
			}
		}
	}

	//����Ȩ��
	for(i = 0; i < size;i++)
	{
		img[i] /= pow_sum;
	}

	ShowPicByArray(img,width,height);
	delete [] temp;
	delete [] img;
}

void CImageStuDlg::OnFeiXianXing() 
{
	// �������˲� ʮ�ֲ���
	if(_flag == false)
	{
		MessageBox("ͼƬδ�򿪣�");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	memset(img,0,sizeof(int)*size);
	int scale = 5;
	
	int number = 1 + scale/2*4;
	int * sor = new int[number];
	
	for(int y=scale/2;y<height-scale/2; y++)
	{
		for(int x = scale/2;x<width-scale/2; x++)
		{	
			int index=y*width+x;
			for(int i=0,row = -scale/2; row <= scale/2; row++)
			{
				if(row!=0)
				{
					sor[i++]=_grayData[index+row*width];
				}
				else
				{
					for(int column = -scale/2; column <=scale/2;column++)
					{
						sor[i++]=_grayData[index+column];
					}
				}
			}
			sort(sor,sor+number);
			img[index]= sor[number/2+1];
			i=0;
		}
	}
	
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnFeiXianXingX() 
{
	// �������˲� X��
	if(_flag == false)
	{
		MessageBox("ͼƬδ�򿪣�");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	memset(img,0,sizeof(int)*size);

	int scale = 5;
	
	int number = 1 + scale/2*4;
	int * sor = new int[number];
	
	for(int y=scale/2;y<height-scale/2; y++)
	{
		for(int x = scale/2;x<width-scale/2; x++)
		{	
			int index=y*width+x;
			for(int j=0,i=-scale/2; i <= scale/2; i++)
			{
				if(i!=0)
				{
					sor[j++]=_grayData[index+i*width+i];
				}
				sor[j++]=_grayData[index-i*width+i];
			}
			sort(sor,sor+number);
			img[index]= sor[number/2+1];
			j=0;
		}
	}
	
	ShowPicByArray(img,width,height);
	delete [] img;
	
}

void CImageStuDlg::Onlpls() 
{
	// ������˹�㷨
	if(_flag == false)
	{
		MessageBox("ͼƬδ�򿪣�");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	memset(img,0,sizeof(int)*size);
	
	for(int y=1; y<height-1;y++)
	{
		for(int x=1; x < width-1 ; x++)
		{
			for(int m=y-1; m <= y+1;m++)
			{
				for(int n=x-1;n <= x+1;n++)
				{
					if(m==y&&n==x)
					{
						img[y*width+x]+=8*_grayData[m*width+n];
					}else{
						img[y*width+x]-=_grayData[m*width+n];
					}
					
				}
			}
		}
	}
	/*
	for(int i = 0; i < size; i++)
	{
		img[i]=abs(img[i]);
	}*/

	//��ֵ�궨
	int min=0,max=0;
	for(int i = 0; i < size; i++)
	{
		if(img[i]<min)
		{
			min=img[i];
		}
		if(img[i]>max)
		{
			max=img[i];
		}
	}

	for(i = 0; i < size; i++)
	{
		img[i]+=-1*min;
	}
	for(i = 0; i < size; i++)
	{
		img[i]*=255.0/max;
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnRobert() 
{
	// Robert�㷨
	if(_flag == false)
	{
		MessageBox("ͼƬδ�򿪣�");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	memset(img,0,sizeof(int)*size);
	
	for(int y=0; y<height-1;y++)
	{
		for(int x=0; x < width-1 ; x++)
		{
			int index=y*width+x;
			img[index]=abs(-_grayData[index]+_grayData[index+width+1])+abs(-_grayData[index+1]+_grayData[index+width]);
		}
	}

	//��ֵ�궨
	int min=0,max=0;
	for(int i = 0; i < size; i++)
	{
		if(img[i]<min)
		{
			min=img[i];
		}
		if(img[i]>max)
		{
			max=img[i];
		}
	}

	for(i = 0; i < size; i++)
	{
		img[i]+=-1*min;
	}
	for(i = 0; i < size; i++)
	{
		img[i]*=255.0/max;
	}
	ShowPicByArray(img,width,height);
	delete [] img;
	
}

void CImageStuDlg::OnSobel() 
{
	// Sobel�㷨
	if(_flag == false)
	{
		MessageBox("ͼƬδ�򿪣�");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	memset(img,0,sizeof(int)*size);
	
	for(int y=1; y<height-1;y++)
	{
		for(int x=1; x < width-1 ; x++)
		{
			int index=y*width+x;
			int sum_x=0;
			int sum_y=0;
			sum_x+=abs(-_grayData[index-width-1]-2*_grayData[index-width]-_grayData[index-width+1]+_grayData[index+width-1]+2*_grayData[index+width]+_grayData[index+width+1]);
			sum_y+=abs(-_grayData[index-width-1]-2*_grayData[index-1]-_grayData[index+width-1]+_grayData[index-width+1]+2*_grayData[index+1]+_grayData[index+width+1]);
			img[index]=sum_x+sum_y;
		}
	}

	//��ֵ�궨
	int min=0,max=0;
	for(int i = 0; i < size; i++)
	{
		if(img[i]<min)
		{
			min=img[i];
		}
		if(img[i]>max)
		{
			max=img[i];
		}
	}

	for(i = 0; i < size; i++)
	{
		img[i]+=-1*min;
	}
	for(i = 0; i < size; i++)
	{
		img[i]*=255.0/max;
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnGrayColor() 
{
	//  256�Ҷ�ͼ��ӳ���216ɫ��ɫͼ��
	if(_flag == false)
	{
		MessageBox("ͼƬδ�򿪣�");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	CBaseColorInfo * newColor = new CBaseColorInfo[size];

	for(int i = 0; i <size;i++)
	{
		int gray=_grayData[i];
		int red = abs(sin(gray/100.0*3.14)*255);
		int green = abs(sin(gray/100.0*3.14-3.14/4)*255);
		int blue = abs(sin(gray/100.0*3.14-3.14/2)*255);
		newColor[i].SetRed(red);
		newColor[i].SetGreen(green);
		newColor[i].SetBlue(blue);
	}

	ShowPicByArray(newColor,width,height);
	delete [] newColor;
}

void CImageStuDlg::OnRgbHsiRgb() 
{
	// RGB->HSI->RGB
	if(_flag == false)
	{
		MessageBox("ͼƬδ�򿪣�");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	CBaseColorInfo * newColor = new CBaseColorInfo[size];

	for(int i = 0; i <size;i++)
	{
		// ����
		CBaseColorInfo colorInfo = _colorData[i];
			
		CRGBtoHSI bean(colorInfo);
		bean.RGBToHSI();// RGB-->HSI

		bean.HSIToRGB();// HSI-->RGB
		bean.ScaleRGB();// RGB����ӳ��ɡ�0--255��
		CBaseColorInfo hsiInfo = bean.GetResult();
		newColor[i]=hsiInfo;
	}

	ShowPicByArray(newColor,width,height);
	delete [] newColor;
}

//----------------------------------------------ʵ����--------------------------------------------//



void CImageStuDlg::OnFuShi() 
{
	// ��ɫ��ʴ
	if(_flag == false)
	{
		MessageBox("ͼƬδ�򿪣�");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];

	for(int m=0;m<size;m++)
	{
		img[m]=_grayData[m];
	}

	fushi_white(img,height,width);

	ShowPicByArray(img,width,height);
	delete [] img;
}


void CImageStuDlg::OnPenZhang() 
{
	// ��ɫ����
	if(_flag == false)
	{
		MessageBox("ͼƬδ�򿪣�");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];

	for(int m=0;m<size;m++)
	{
		img[m]=_grayData[m];
	}

	penzhang_white(img,height,width);

	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnOpen() 
{
	// ������
	if(_flag == false)
	{
		MessageBox("ͼƬδ�򿪣�");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];

	for(int m=0;m<size;m++)
	{
		img[m]=_grayData[m];
	}

	fushi_white(img,height,width);

	penzhang_white(img,height,width);

	ShowPicByArray(img,width,height);
	delete [] img;
	
}

void CImageStuDlg::OnClose() 
{
	// �ղ���
	if(_flag == false)
	{
		MessageBox("ͼƬδ�򿪣�");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];

	for(int m=0;m<size;m++)
	{
		img[m]=_grayData[m];
	}

	penzhang_white(img,height,width);

	fushi_white(img,height,width);

	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnBianJie() 
{
	// ��ɫ�߽�
	if(_flag == false)
	{
		MessageBox("ͼƬδ�򿪣�");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	int * temp = new int[size];

	for(int m=0;m<size;m++)
	{
		temp[m]=img[m]=_grayData[m];	
	}

	fushi_white(temp,height,width);

	for(int i = 0;i < size; i++)
	{
		img[i]-=temp[i];
	}

	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnTianChong() 
{
	// ���
	if(_flag == false)
	{
		MessageBox("ͼƬδ�򿪣�");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	int * temp = new int[size];
	int * backup = new int[size];
	bool flag = false;
	int number=0;

	for(int m=0;m<size;m++)
	{
		if(_grayData[m]==255)
		{
			temp[m]=0;
		}
		else
		{
			temp[m]=255;
		}
		img[m]=255;
	}	

	img[447*96]=0;
	
	while(!flag)
	{
		fushi_white(img,height,width);

		for(int i = 0; i < size; i++)
		{
			if(img[i]==0&&temp[i]==255)
			{
				img[i]=255;
			}
			if(backup[i]==img[i])
			{
				number++;
			}
			backup[i]=img[i];
		}

		if(number==size)
		{
			flag=true;
		}
		else
		{
			number=0;
		}
	}

	for(int i=0;i<size;i++)
	{
		if(_grayData[i]==0)
		{
			img[i]=_grayData[i];
		}
	}

	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnLianTong() 
{
	// ��ͨ
	if(_flag == false)
	{
		MessageBox("ͼƬδ�򿪣�");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	int * result = new int[size];
	CBaseColorInfo * newColor = new CBaseColorInfo[size];

	for(int i=0;i<size;i++)
	{
		if(_grayData[i]>200)
			{
				img[i]=255;
			}
			else
			{
				img[i]=0;
			}
	}

	//��ʴ
	fushi_white(img,height,width);

	//----------------------------------------- 

	CConnectedComponent lian_tong(img,height,width);

	while(!lian_tong.confirm())
	{
		int index=lian_tong.calc_start();

		/*
		CString str;
		str.Format("%d", index);
		MessageBox(str);
		*/

		if(index==-1)
		{
			break;
		}
		lian_tong.set_start(index);	
		lian_tong.calc_area();
	}

	lian_tong.return_L(result);
	
	for(i = 0; i < size; i++)
	{
		int gray=result[i];
		int red,blue,green;
		if(gray==0)
		{
			red=blue=green=0;
		}
		else
		{
			red = abs(sin(gray/100.0*3.14)*255);
			green = abs(sin(gray/100.0*3.14-3.14/4)*255);
			blue = abs(sin(gray/100.0*3.14-3.14/2)*255);
		}
		newColor[i].SetRed(red);
		newColor[i].SetGreen(green);
		newColor[i].SetBlue(blue);
	}

	ShowPicByArray(newColor,width,height);
	delete [] img;
}

void CImageStuDlg::OnXiHua() 
{
	// ϸ��
	if(_flag == false)
	{
		MessageBox("ͼƬδ�򿪣�");
		return;
	}
	int width = _infoHeader.biWidth+2;
	int height = _infoHeader.biHeight+2;
	int size = width * height;
	int * img = new int[size];
	int * backup = new int[size];
	bool equ=false;
	int count = 0;

	//------��Χ����һ���Ȧ---��ֹ�㷨�ڱ߽���������---------
	for(int i =0;i <size;i++)
	{
		img[i]=255;
	}

	for(int m = 0; m < width-2;m++)
	{
		for(int n = 0; n <height-2;n++)
		{
			int index=n*(width-2)+m;
			int img_index=(n+1)*width+m+1;
			img[img_index]=_grayData[index];
		}
	}
	//----------------------------------------- 

	int point1[3][3]={1,1,1,2,0,2,0,0,0};
	int point2[3][3]={2,1,1,0,0,1,0,0,2};
	int point3[3][3]={0,2,1,0,0,1,0,2,1};
	int point4[3][3]={0,0,2,0,0,1,2,1,1};
	int point5[3][3]={0,0,0,2,0,2,1,1,1};
	int point6[3][3]={2,0,0,1,0,0,1,1,2};
	int point7[3][3]={1,2,0,1,0,0,1,2,0};
	int point8[3][3]={1,1,2,1,0,0,2,0,0};

	while(!equ)
	{
		custom_penzhang_white(point1,img,height,width);
		custom_penzhang_white(point2,img,height,width);
		custom_penzhang_white(point3,img,height,width);
		custom_penzhang_white(point4,img,height,width);
		custom_penzhang_white(point5,img,height,width);
		custom_penzhang_white(point6,img,height,width);
		custom_penzhang_white(point7,img,height,width);
		custom_penzhang_white(point8,img,height,width);

		for(int i=0;i<size;i++)
		{
			if(backup[i]==img[i])
			{
				count++;
			}
			backup[i]=img[i];
		}

		if(count==size)
		{
			equ=true;
		}
		else
		{
			count=0;
		}
	}

	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnHuffman() 
{
	//����������
	if(_flag==false){
		MessageBox("ͼƬδ�򿪣�");
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int pixelCount = width*height;
	int * grayData = new int[pixelCount];
	for(int index=0;index<=pixelCount-1;index++)
	{
		grayData[index]=_grayData[index];
	}

	//�Ҷȵȼ�
	const int GRAY_LEVEL=256;
	//����������
	CImgHuffman huf(grayData,pixelCount,GRAY_LEVEL);
	huf.HuffmanCode();
	//���
	std::string * codeTable = huf.get_codeTable();
	TRACE("���\n");
	for(index = 0;index<=GRAY_LEVEL-1;index++)
	{
		TRACE("%d,%s\n",index,codeTable[index].c_str());
	}
}
