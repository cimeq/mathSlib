#pragma once
#include <MathObject.h>
#include <map>

namespace mathS {

	using Rule = std::function<bool(Ptr<MathObject>, Ptr<MathObject>&)>;
	using Match = std::function<bool(Ptr<MathObject>)>;

	/// <summary>
	/// ���ڸ�����Pattern������һ��ƥ��
	/// </summary>
	/// <param name="pattern"></param>
	/// <returns></returns>
	Match MakeMatch(Ptr<MathObject> pattern);
	/// <summary>
	/// ���ڸ�����source pattern, target pattern������һ��ƥ��-�滻����
	/// </summary>
	/// <param name="src_pattern"></param>
	/// <param name="tar_pattern"></param>
	/// <returns></returns>
	Rule MakeRule(Ptr<MathObject> src_pattern, Ptr<MathObject> tar_pattern);

	/// <summary>
	/// ƥ�䡣�Ը�����pattern��obj����ʽ��������ƥ���
	/// </summary>
	/// <param name="pattern"></param>
	/// <param name="obj"></param>
	/// <param name="table"></param>
	/// <returns></returns>
	bool DoMatch(Ptr<MathObject> pattern, Ptr<MathObject> obj, std::map<std::string, Ptr<MathObject>>& table);
	
	/// <summary>
	/// �滻�����ڸ�����table�����ؽ�pattern�ж�Ӧ���滻�Ľ�����ǿ�������Ӱ��pattern��
	/// </summary>
	/// <param name="pattern"></param>
	/// <param name="table"></param>
	/// <returns></returns>
	Ptr<MathObject> DoReplace(Ptr<MathObject> pattern, std::map<std::string, Ptr<MathObject>>& table);

	/// <summary>
	/// ȫƥ�䣬�������������ʽ��ȫ��ͬ����true��(Ϊʲô���Ƚ�GetString()����ΪGetString()һ��������������ʽ��Ч�ʺܵ͡�)
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	bool FullCompare(Ptr<MathObject> a, Ptr<MathObject> b);


	// ����⣬���������д����ֱ�����ɵĹ��򣬻��Ǳ���Ҫ������еĹ���
	namespace RuleLib {
		
		
		
	};
}