#pragma once
#include <NMathObject.h>
/*
	NFunction.h �У������˳��õ�NFunction. ������׼NFunction��.
*/

namespace mathS
{
	namespace NMath
	{
		typedef std::function<Ptr<NMathObject>(Ptr<NMathObject>)> NFunction;

		// NFunction��Error����.
		NFunction NFunctionError(const std::string info);
		// NFunction��Atom���͡�ֱ�ӷ���ֵ v �ĺ�����
		NFunction NFunctionAtom(const NValueType v);

		// Declare a shape wise NMathFunction with name o f FUNCNAME
#define DECLARE_SHAPE_WISE_NMATHUNC_OP(FUNCNAME) Ptr<NMathObject> FUNCNAME(Ptr<NMathObject> const a, Ptr<NMathObject> const b);

		// + - * /
		DECLARE_SHAPE_WISE_NMATHUNC_OP(Plus)
		DECLARE_SHAPE_WISE_NMATHUNC_OP(Subtract)
		DECLARE_SHAPE_WISE_NMATHUNC_OP(Multiply)
		DECLARE_SHAPE_WISE_NMATHUNC_OP(Divide)

		// Basic NMath Functions

#define DECLARE_SHAPE_WISE_NMATHUNC_MONO(FUNCNAME) Ptr<NMathObject> FUNCNAME(Ptr<NMathObject> const a);

		DECLARE_SHAPE_WISE_NMATHUNC_MONO(Sin)
		DECLARE_SHAPE_WISE_NMATHUNC_MONO(Cos)
		DECLARE_SHAPE_WISE_NMATHUNC_MONO(Tan)
		DECLARE_SHAPE_WISE_NMATHUNC_MONO(ArcSin)
		DECLARE_SHAPE_WISE_NMATHUNC_MONO(ArcCos)
		DECLARE_SHAPE_WISE_NMATHUNC_MONO(ArcTan)
		DECLARE_SHAPE_WISE_NMATHUNC_MONO(Log)
		DECLARE_SHAPE_WISE_NMATHUNC_MONO(Exp)
		DECLARE_SHAPE_WISE_NMATHUNC_MONO(Floor)

	}
}
