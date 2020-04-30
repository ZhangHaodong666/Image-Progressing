#if !defined(__ObjectOrientedModel_1_CImgHuffman_h)
#define __ObjectOrientedModel_1_CImgHuffman_h

#include "HuffmanMergeItem.h"
#include <vector>
#include <bitset>
#include <string>

class CImgHuffman
{
public:
	/*���캯��*/
	CImgHuffman(int * grayData, int pixelCount, int grayLevel);
	/*��������*/
	~CImgHuffman();

	/*�Ҷ�ͳ��*/
	void CalcGrayStat(void);
	/*��ʼ�����ϲ��Ĺ�����Ԫ��*/
	void InitMergeVec(void);
	void MakeCode(std::vector<int> * grayVec, bool flag);
	/*�ϲ�����Ԫ��*/
	void MergeItem(CHuffmanMergeItem & first, CHuffmanMergeItem & second,CHuffmanMergeItem & result);
	/*����Ԫ�ز�����ʵ�λ��*/
	void InsertItem(CHuffmanMergeItem & item);
	/*�������λ����λ��*/
	int CalcSumBitCount(void);
	/*����ƽ���볤*/
	float CalcAvgBitLen(void);
	/*����ƽ���볤*/
	float CalcEntropy(void);
	/*����������*/
	void HuffmanCode(void);
	/*���ɱ���λ��(�ַ�����ʽ)*/
	void GeneCodeString();
	//��ʼ���Ҷ��ַ���(ǰ1000��,�Զ��Ÿ���)
	void InitGrayStr();

	//����ӿ�
	//���
	std::string * get_codeTable(void);
	//�ַ�����ʽ��λ��
	std::string get_codeString(void);
	//�����Ʊ���λ��
	std::vector< std::bitset<8> > * get_codeBitSet(void);
	//ƽ���볤
	float get_avgCodeLen(void);
	//���볤
	int get_sumBitCount(void);
	//�Ҷ�ͳ��
	int * get_GrayStat(void);
	//��
	float get_entropy(void);
	/*�������*/
	std::string get_mergeStr();
	//�Ҷ��ַ���(�Զ��Ÿ���)
	std::string GetGrayStr() const{
			return _grayStr;
	}

protected:
private:
	/*��ʼ�����*/
	void InitCodeTable(void);
	//����Ҷ�����
	void PrintGrayVec(CHuffmanMergeItem item);
	//���úϲ�����
	void MakeMergeStr(CHuffmanMergeItem iteml, CHuffmanMergeItem item2, CHuffmanMergeItem newItem, int num); 

private:
	/*�Ҷ�����*/
	int * _grayData;
	/*��������*/
	int _pixelCount;
	/*ͼ��Ҷȼ�����*/
	int _grayLevel;

	/*���鲢��Ԫ��(��������С��������)*/
	std::vector<CHuffmanMergeItem> * _waitMergeVec;

	/*�Ҷȵ�ͳ������*/
	int * _grayStat;
	/*�Ҷ����,��С��������,���ַ�����ʾ*/
	std::string * _codeTable;
	/*����λ��,�ַ�����ʽ*/
	std::string _codeString;	
	/*����λ��(������λ��)*/
	std::vector< std::bitset<8> > * _codeBitSet;
	/*ƽ���볤(��BitΪ��λ)*/
	float _avgCodeLen;
	/*������λ��*/
	int _sumBitCount;
	/*��*/
	float _entropy;
	/*�������*/
	std::string _mergeStr;
	//�Ҷ��ַ���(�Զ��Ÿ���)
	std::string _grayStr;

	//�����Ԫ�ش�С�ıȽ�(��������)
	class CElemCompare{
	public:
		bool operator()(CHuffmanMergeItem elem1, CHuffmanMergeItem elem2)
		{
			return elem1.get_num() < elem2.get_num();

		}
	};
};

#endif