#pragma once

#include <MathObject.h>
#include <string>
#include <lexer.h>

/*
	In this file, we introduce methods that parse text input of expressions 
	and transform them into MathObject.

	
*/
namespace mathS
{
	class Parser
	{
		/* 
		ע��parser�Ǻ�ʱ�᷵�� nullptr����ʱ���� MathErrorObject:

		* ���ַǷ��﷨ʱ��parse���ص���MathErrorObject���������﷨�������Ϣ�����������MathErrorObject���յ��÷���ֵ��ĸ��������ֹͣ���������Ѵ�����Ϣ������ȥ
		* ������parse_numberʶ�𵽵Ĳ������֣����Ǳ���������һ���������﷨���᷵��nullptr. �յ��÷���ֵ��ĸ���������������������parser������
		
		*/
    public:
	    Parser(const std::string& c) : lexer(c) { }
	    MathObject* Parse();
    private:
	    short priority(const std::string& c);
	    Lexer lexer;
	};
}