#pragma once
#include <NMathObject.h>
/*
	NFunction.h �У������˳��õ�NFunction. ������׼NFunction��.
*/

namespace mathS
{
	namespace NMath
	{
		using NParamsList = std::vector<Ptr<NMathObject>>;
		using NFunction = std::function<Ptr<NMathObject>(const NParamsList&)>;

		// NFunction��Error����.
		NFunction NFunctionError(const std::string info);
		// NFunction��Atom���͡�ֱ�ӷ���ֵ v �ĺ�����
		NFunction NFunctionAtom(const NValueType v);
		
		
		// Declare a shape wise NMathFunction with name o f FUNCNAME

#define DECLARE_NMATHUNC(FUNCNAME) Ptr<NMathObject> FUNCNAME(const NParamsList& params)

		// + - * /
		
		DECLARE_NMATHUNC(Plus);
		DECLARE_NMATHUNC(Subtract);
		DECLARE_NMATHUNC(Multiply);
		DECLARE_NMATHUNC(Divide);
		DECLARE_NMATHUNC(Less);
		DECLARE_NMATHUNC(Greater);
		DECLARE_NMATHUNC(Lesseq);
		DECLARE_NMATHUNC(Greatereq);
		DECLARE_NMATHUNC(Power);

		DECLARE_NMATHUNC(Sin);
		DECLARE_NMATHUNC(Cos);
		DECLARE_NMATHUNC(Tan);
		DECLARE_NMATHUNC(ASin);
		DECLARE_NMATHUNC(ACos);
		DECLARE_NMATHUNC(ATan);
		DECLARE_NMATHUNC(Log);
		DECLARE_NMATHUNC(Exp);
		DECLARE_NMATHUNC(Floor);


	}
}
