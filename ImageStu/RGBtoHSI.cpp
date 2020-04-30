#include "StdAfx.h"
#include "CRGBtoHSI.h"
#include "ImagePara.h"
#include <cmath>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


double MIN_NUM=0.0;

CRGBtoHSI::CRGBtoHSI( CBaseColorInfo & colorInfo)
{
		_colorInfo = colorInfo;
}


CRGBtoHSI::CRGBtoHSI( CColorSpaceInfo & hsiInfo)
{
		_hsi = hsiInfo;
		_h = _hsi.GetPara1();
		_s = _hsi.GetPara2();
		_i = _hsi.GetPara2();
}

CRGBtoHSI::~CRGBtoHSI(){

}

void CRGBtoHSI::RGBToHSI(){

	//RGB��һ��
	RGBPercent();

	int red = _colorInfo.GetRed();
	int green = _colorInfo.GetGreen();
	int blue = _colorInfo.GetBlue();

	//ǿ��
	_i = (_r + _g + _b) / 3.0;

	//���Ͷ�
	int sum = red + green + blue;
	if(sum != 0 && ! (red == blue && red == green && blue == green ))
	{
		int minV = _colorInfo.GetRed();
		if(minV > _colorInfo.GetGreen())
		{
			minV = _colorInfo.GetGreen();
		}
		if(minV > _colorInfo.GetBlue())
		{
			minV = _colorInfo.GetBlue();
		}
		//���Ͷ�
		_s = 1 - minV * 3.0 / sum;
	}
	else{
		_s = 0;
	}

	//��ɫ��H
	if( (red == blue && red == green && green == blue))
	{
		_h = 0.0;
	}
	else{
		//ת����HSI
		if(blue <= green)
			_h = acos( CalcMedium() );
		else
			_h = 2 * PI - acos( CalcMedium() );
		
	}

	//����hsiϵ��
    _hsi.SetPara1(_h);
	_hsi.SetPara2(_s);
	_hsi.SetPara3(_i);

}

//��HSI��ֵӳ�䵽0~255֮��
void CRGBtoHSI::ScaleHSI(){
	int red = (int)(_h * 255.0 / (2 * PI));
	int green = (int)_s * 255;
	int blue = (int)_i * 255;

	_result.SetRed(red);
	_result.SetBlue(blue);
	_result.SetGreen(green);

}

//��ȡ���
CBaseColorInfo CRGBtoHSI::GetResult() const{
	return _result;
}

//��ȡHSI
CColorSpaceInfo CRGBtoHSI::GetHSI() const{
	return _hsi;
}

void CRGBtoHSI::SetHSI(CColorSpaceInfo info)
{
	_hsi = info;
	_h = info.GetPara1();
	_s = info.GetPara2();
	_i = info.GetPara3();

}

//��ȡRGB
CColorSpaceInfo CRGBtoHSI::GetRGB() const{

	return _rgb;
}

//��HSIת����RGB
void CRGBtoHSI::HSIToRGB(){
	double r,g,b;

	//�޸�H�Ƕ�
	//_h+=PI/3*3;
	//�޸ı��Ͷ�S
	//_s*=0.5;
	//�޸�����I
	//_i*=0.5;
	CString str;
	if(fabs(_i) < MIN_NUM)
	{
		//��ɫͼ��
		r = 0;
		g = 0;
		b = 0;
	}
	else if(fabs(_s) < MIN_NUM)
	{
		//���Ͷ�Ϊ0���Ҷ�ͼ��
		r = g = b = _i; 
	}
	else{
		if( _h - 2 * PI / 3 < MIN_NUM){
			b = _i * (1.0 - _s);
			r = _i * (1 + _s * cos(_h) / cos(PI / 3 - _h));
			g = 3 * _i - (b + r);
			
		}
		else if(_h - 4 * PI / 3 < MIN_NUM) 
		{
			r = _i * (1 - _s);
			g=_i* (1+(_s*cos(_h-2*PI/3)/cos(PI-_h)));
			b = 3 * _i - (r + g);
		}
		else if(_h - 2 * PI < MIN_NUM)
		{
			g = _i * (1 - _s);
			b=_i*(1+_s*cos(_h-4*PI/3)/cos(5*PI/3-_h));
			r = 3 * _i - (g + b);
		}
	
	}
	
	_rgb.SetPara1(r);
	_rgb.SetPara2(g);
	_rgb.SetPara3(b);
}

//��RGB��ֵӳ�䵽0~255֮��
void CRGBtoHSI::ScaleRGB(){
	int red = int (_rgb.GetPara1() * 255 + 0.5);
	int green = int (_rgb.GetPara2() * 255 + 0.5);
	int blue = int (_rgb.GetPara3() * 255 + 0.5);

	_result.SetRed(red);
	_result.SetGreen(green);
	_result.SetBlue(blue);

}

//-------------------------˽�к���-------------------------------//

//RGB��һ��
//��RGB��������ת����
void CRGBtoHSI::RGBPercent(){

	//��һ��
	_r = _colorInfo.GetRed() * 1.0 / 255;
	_g = _colorInfo.GetGreen() * 1.0 / 255;
	_b = _colorInfo.GetBlue() * 1.0 / 255;

}

//�����Сֵ
double CRGBtoHSI::MinRGB(){

	int min = _colorInfo.GetRed();
	if(min > _colorInfo.GetGreen() )
	{
		min = _colorInfo.GetGreen();
	}
	if(min > _colorInfo.GetBlue() )
	{
		min = _colorInfo.GetBlue();
	}
	return min * 1.0 / 255.0;
}

//������ֵ
double CRGBtoHSI::MaxRGB(){

	int max = _colorInfo.GetRed();
	if(max < _colorInfo.GetGreen() )
	{
		max = _colorInfo.GetGreen();
	}
	if(max < _colorInfo.GetBlue() )
	{
		max = _colorInfo.GetBlue();
	}
	return max * 1.0 / 255.0;
}


//����м�ֵ
double CRGBtoHSI::CalcMedium(){
	//����
	double son = 0.5 * ((_r - _g) + (_r - _b));
	//��ĸ
	double mother = sqrt((_r - _g)*(_r - _g) + (_r - _b) * (_g - _b));

	if(fabs(mother) < MIN_NUM){
		return 0;
	}	
	else{
		return son / mother;
	}
}
