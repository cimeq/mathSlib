#pragma once

#include <Rule.h>

/*
	ʹ��ĳЩ��������һϵ��Rule������һ��MathObject�����ǰ����ΪCompute��Compute�Ĳ����ͷ���������Rule��ͬ�������ò�һ��
	
	����ÿ��MathObject������Ĭ�ϵ�Compute����
	
	Power��(a*b)^e=a^e*b^eչ����(a^e1)^e2=a^(e1*e2)�������Զ����㣬����ʽ��������չ��������
	Item: Vec������չ��(a+b)*c=a*c+b*c�����򣺵�������a/a=1�������Զ�����
	Polynomial�������Զ����㣬�ϲ�ͬ����
	
	Function FunctionalOperator���ݺ������ƵĲ�ͬ������ͬ�ļ��㡣δ֪�ĺ����������㡣

	Compare ���򵥵Ļ��������ȫ�ǳ�����ֱ��������



*/

namespace mathS{

	/// <summary>
	/// �� Compute�� �����������
	/// </summary>
	/// <param name="input"></param>
	/// <returns></returns>
	Ptr<MathObject> Compute(const Ptr<MathObject>& input);

	Ptr<MathObject> Compute(const Ptr<Item>& input);


}