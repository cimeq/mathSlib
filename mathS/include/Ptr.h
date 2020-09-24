#pragma once
#include <memory>

namespace mathS {
	// ʹ������ָ�룬��ֹ�ڴ�й©
	template<class T>
	using Ptr = std::shared_ptr<T>;  

#define New std::make_shared
	// ǿ���ڴ�ת����������������֮���໥ת��
	template<class T1, class T2>
    Ptr<T1> Dynamic_cast(Ptr<T2> _Arg) {
        return std::dynamic_pointer_cast<T1, T2>(_Arg);
    } 
}
