#pragma once
#include <memory>

namespace mathS {
	// ʹ������ָ�룬��ֹ�ڴ�й©
	template<class T>
	using Ptr = std::shared_ptr<T>;  

#define New std::make_shared
	// ǿ���ڴ�ת����������������֮���໥ת��
#define Dynamic_cast std::dynamic_pointer_cast
}
