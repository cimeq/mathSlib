#pragma once

#include<MathObject.h>
#include<NMathObject.h>
#include<NFunction.h>
#include<map>
/*
	In this file, we introduce methods that use lambda expression to
	assemble a NMathFunction(numeric math function) with given MathObject.
	Also, the NMathFunction can be converted into a cpp function if you wish.
*/

namespace mathS
{

	class Assembler
	{

	public:

	
	private:
		
		// ���ǵ���������Ҫ��һ���ű�����ʱ��װ������Ҳ�����Ǵ�function_table, constant_table�������ң�
		// ���Ǵ�����ʱ�Ļ����в�������Ҫ�ĺ����������������ȣ�������ʣ���Ϊ���нű�ʱ���û������Զ����˵���ֵ������
		// �������������Ľű�ִ������û�д������ ������Assembler��洢function_table��constant_table��

		// ��������װʱ��Ҫ�ı�׼����ֱ�Ӹ��ݺ������ƴӺ�������ȡ
		std::map<std::string, NMath::NFunction> function_table;
		// ��������װʱ�����������ţ���ӳ�������ȡ��
		std::map<std::string, NMath::NMathObject> constant_table;

		// ���ݱ��ʽexpr����װһ����expr�еĳ��ֵı���Ϊ�����ĺ�����������˳����param_str�������ġ�
		// �� expr = sin(u)*v, params={u, v}����ô���صĺ�������f(x1,x2)=sin(x1)*x2.
		NMath::NFunction Assemble(Ptr<MathObject> expr, const std::vector<std::string>& params);
		
	};
}