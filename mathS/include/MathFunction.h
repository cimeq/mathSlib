#pragma once


#include <MathObject.h>

namespace mathS {

	// MathFunction : MathObject -> MathObject
	// MathFunction �Ƕ���ѧ��������һЩ�������õ������
	using MathFunction = std::function<Ptr<MathObject>(std::vector<Ptr<MathObject>>)>;
	
}