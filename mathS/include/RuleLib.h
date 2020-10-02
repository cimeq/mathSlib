#pragma once

#include <Rule.h>

namespace mathS {
	// ����⣬���������д����ֱ�����ɵĹ��򣬻��Ǳ���Ҫ������еĹ���
	namespace RuleLib {

		// �� Item �еĵ�һ�������˷�չ��
		bool VectorMultiply(Ptr<MathObject> obj, Ptr<MathObject>& rst);
		// ���˷������ɶ� Item �е�һ��Polynomial�ӷ�չ��
		bool ExpandDistributive(Ptr<MathObject> obj, Ptr<MathObject>& rst);

		// Item ͬ�����ݺϲ�
		static Rule Power_reduction_1 = MakeRule(Parse("_a/_a*_RES_"), Parse("_RES_"));
		static Rule Power_reduction_2 = MakeRule(Parse("_a*_a*_RES_"), Parse("_a^2_RES_"));
		static Rule Power_reduction_3 = MakeRule(Parse("_a^_e*_a*_RES_"), Parse("_RES_*_a^(_e+1)"));
		static Rule Power_reduction_4 = MakeRule(Parse("_a^_e/_a^_*_RES_"), Parse("_RES_*_a^(_e-1)"));
		static Rule Power_reduction_5 = MakeRule(Parse("_a^_e1*_a^_e2*_RES_"), Parse("_RES_*_a^(_e1+_e2)"));
		static Rule Power_reduction_6 = MakeRule(Parse("_a^_e1/_a^_e2*_RES_"), Parse("_RES_*_a^(_e1-_e2)"));

		// ������˷�����
		bool ConstantMultiply(Ptr<MathObject> obj, Ptr<MathObject>& rst);
		// ��������ӷ�ĸԼ��
		bool ConstantFractionReduction(Ptr<MathObject> obj, Ptr<MathObject>& rst);

	};
}