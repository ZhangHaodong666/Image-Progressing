#if !defined(__ObjectOrientedModel_1_CHuffmanMergeItem_h)
#define __ObjectOrientedModel_1_CHuffmanMergeItem_h

#include <vector>
class CHuffmanMergeItem
{
public:
	//�Ҷ�����
	std::vector<int> get_grayVec(void);
	void set_grayVec(std::vector<int> new_grayVec);
	//�Ҷ�������
	int get_num(void);
	void set_num(int new_num);

protected:
private:
	//�Ҷ�����
	std::vector<int> _grayVec;
	//�Ҷ�������
	int _num;
};

#endif