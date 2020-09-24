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

    public:
	    // ���ַ�����ʼ��
	    Parser(const std::string& c) : lexer(c) { }

		// ��ý����� MathObject ���ű��ʽ����
	    Ptr<MathObject> Parse();
    private:
		Lexer lexer;

	    short level(const std::string& c);
		/// <summary>
		/// �� start λ�ÿ�ʼ����һ������ֱ�����������Ż�ĩβ. ��û�ж����򷵻� EmptyObject. ����⵽�﷨�����򷵻�ErrorObject
		/// </summary>
		/// <param name="tokens"></param>
		/// <param name="start"></param>
		/// <param name="i">���ñ�������������ʱ��i�ڱ������Ķ����Ӧtoken�ĺ�һλ����(���������������ʼ��λ��)</param>
		/// <returns></returns>
		Ptr<MathObject> parseObject(const std::vector<Token>& tokens, const int start, int& i);

		Ptr<MathObject> parseAtom(const std::vector<Token>& tokens, const int start, int& i);
		Ptr<MathObject> parseFunction(const std::vector<Token>& tokens, const int start, int& i);
		Ptr<MathObject> parseLocate(const std::vector<Token>& tokens, const int start, int& i);
		Ptr<MathObject> parsePower(const std::vector<Token>& tokens, const int start, int& i);
		Ptr<MathObject> parseItem(const std::vector<Token>& tokens, const int start, int& i);
		Ptr<MathObject> parsePolynomial(const std::vector<Token>& tokens, const int start, int& i);
		Ptr<MathObject> parseMap(const std::vector<Token>& tokens, const int start, int& i);
		Ptr<MathObject> parseCompare(const std::vector<Token>& tokens, const int start, int& i);
		std::vector<Ptr<MathObject>> parseList(const std::vector<Token>& tokens, const int start, int& i);

	};
}