#include <Compute.h>

using namespace mathS;

Ptr<MathObject> mathS::Compute(const Ptr<Item>& input)
{
	// �ȿ���һ��
	Ptr<Item> rst = Dynamic_cast<Item>(input->DeepCopy());
}
