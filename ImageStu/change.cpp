#include "stdafx.h"
#include "change.h"

//�Ҷ�ͼ ��ɫ��ʴ	��ɫ����
//3��3������������Ϊԭ��  ������Ҫ��İ׵㷵��true
void fushi_white(int * img,int height,int width)
{
	int size = width * height;
	int * temp = new int[size];
	bool flag=true;

	for(int m=0;m<size;m++)
	{
		temp[m]=img[m];
	}

	int scale=3;
	for(int i = scale/2; i < width - scale/2; i++)
	{
		for(int j = scale/2; j < height - scale/2; j++)
		{
			int index=j*width+i;
			if(temp[index]==255)
			{
				for(int m = index-width; (m <= index+width)&&flag; m+=width)
				{
					for(int n = m-1; (n <= m+1)&&flag;n++)
					{
						if(temp[n]==0)
						{
							img[index]=0;
							flag=false;
						}
					}
				}
			}
			flag=true;
		}
	}
}

//�Ҷ�ͼ ��ɫ���� ��ɫ��ʴ
//3��3������������Ϊԭ��  ����Ҫ��ĵ㷵��true
void penzhang_white(int * img,int height,int width)
{
	int size = width * height;
	int * temp = new int[size];
	bool flag=true;

	for(int m=0;m<size;m++)
	{
		temp[m]=img[m];
	}

	int scale=3;
	for(int i = scale/2; i < width - scale/2; i++)
	{
		for(int j = scale/2; j < height - scale/2; j++)
		{
			int index=j*width+i;
			if(temp[index]==0)
			{
				for(int m = index-width; (m <= index+width)&&flag; m+=width)
				{
					for(int n = m-1; (n <= m+1)&&flag;n++)
					{
						if(temp[n]==255)
						{
							img[index]=255;
							flag=false;
						}
					}
				}
			}
			flag=true;
		}
	}
}

//�Զ����ɫ����
void custom_penzhang_white(int point[3][3],int *img,int height,int width)
{
	int size = width * height;
	int * temp = new int[size];
	bool flag=true;
	int count=0;

	for(int m=0;m<size;m++)
	{
		temp[m]=img[m];
	}

	int scale=3;
	for(int i = scale/2; i < width - scale/2; i++)
	{
		for(int j = scale/2; j < height - scale/2; j++)
		{
			for(int m=0;m<3;m++)
			{
				for(int n=0;n<3;n++)
				{
					if(point[m][n]==0&&temp[(j+m-1)*width+i+n-1]==0)
					{
						count++;
					}
					else if(point[m][n]==1&&temp[(j+m-1)*width+i+n-1]==255)
					{
						count++;
					}
					else if(point[m][n]==2)
					{
						count++;
					}
				}
			}

			if(count==9)
			{
				img[j*width+i]=255;
			}
			count=0;
		}
	}
}