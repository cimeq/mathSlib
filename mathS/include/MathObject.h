#pragma once

#include <vector>
#include <string>
#include <functional>
#include <Ptr.h>

namespace mathS
{
	class MathObject;
	class ListObject;
	class Atom;
	class Vector;
	class Function;
	class FunctionalOperator;
	class Locate;
	class Power;
	class Inverse;
	class Item;
	class Opposite;
	class Polynomial;
	class Map;
	class Compare;
	class List;
	class ErrorObject;
	class EmptyObject;

	class MathObject
	{
	public:
		enum Type
		{
			// The structure of math objects is something like an expression tree.
			// We assign different levels to each type of math objects.
			// The levels indicate the priority of operations,
			// also the implicit structures of of text form expression input.
			// In contrast, brackets indicate the explicit structures.

			// Level 1: Atom element. 
			// NUMBER,VARIABLE,STRING are deprecated!!! Now we use ATOM.
			// NUMBER:		Starts with a figure from '0'-'9', maybe containing a point, end with space, any operator or bracket.
			//				NOTE: complex are not actually supported YET. But we allow number text with suffix 'i', 
			//				which represents unit complex.
			//
			// VARIABLE:	Usually starts with an aphabet, end with any operator or bracket. 
			//				When starts with _, it acts as an OBJECT PLACEHOLDER, which matches any math object.
			//				When starts with @, it acts as a NAME PLACEHOLDER, which matches any name variable.
			//				NOTE: Its use is more than a variable. For example, it can also represent a name of a function.
			//
			// STRING:		Enclosed with "". The Char \ has the same meaning in C++ string. 
			//
			// ATOM:		Basic element, including number, variable, string. Since all of them can be represented by std::string.
			//				Specific type of ATOM are distinguished only when it is needed.
			//
			// VECTOR:		Enclosed with {}. Inside a vector, there is a list of all elements.
			ATOM, VECTOR, EMPTY, NUMBER, STRING, VARIABLE,
			// Level 2: _FUNCTION(_PARAMETER)
			//		  : _FOPERATOR<<@VAR1,@VAR2,...|_FPARAMETER>>(_PARAMETER)
			FUNCTION, FUNCOPERATOR,
			// Level 3: _OBJECT[_LOC]
			LOCATE,
			// Level 4: _BASE^_EXPONENT
			POWER,
			// Level 5: /_COMPONENT
			INVERSE, 
			// Level 6: _A*_B/_C*...*_Z
			ITEM, 
			// Level 7: -_COMPONENT
			OPPOSITE,
			// Level 8: _A+_B-_C...+_Z
			POLYNOMIAL,
			// Level 9: _KEY->_VALUE
			MAP, 
			// Level 10: _LEFT==_RIGHT; _LEFT<=_RIGHT; _LEFT>=_RIGHT; _LEFT<_RIGHT; _LEFT>_RIGHT ...
			COMPARE, 
			// Level 11:  _A;_B;_C;
			// Not implemented yet.
			// SENTENCE_LIST
			
			// Level 12: _A,_B,_C,...,_Z
			// LIST,
			// ListObject is deprecated now!

			// Level -1: 
			ERROR
		};
		static const int LEVEL_EMPTY = 1;
		static const int LEVEL_ATOM = 1;
		static const int LEVEL_VECTOR = 1;
		static const int LEVEL_FUNCTION = 2;
		static const int LEVEL_FUNCOPERATOR = 2;
		static const int LEVEL_LOCATE = 3;
		static const int LEVEL_POWER = 4;
		static const int LEVEL_INVERSE= 5;
		static const int LEVEL_ITEM = 6;
		static const int LEVEL_OPPOSITE = 7;
		static const int LEVEL_POLYNOMIAL = 8;
		static const int LEVEL_MAP = 9;
		static const int LEVEL_COMPARE = 10;
		static const int LEVEL_LIST = 12;
		static const int LEVEL_CLOSED = 99;
		static const int LEVEL_ERROR = -1;
	public:

		//MathObject() {};
		virtual ~MathObject() {};

		virtual Type GetType() const = 0;
		virtual std::string GetString() const = 0;
		virtual int Level() const = 0;


		virtual Ptr<MathObject> DeepCopy() const = 0;
	};

	/*
	// list type math object. 
	// Elements are separated by comma ",".
	class ListObject : public MathObject
	{
	public:
		std::vector<Ptr<MathObject>> components;

		ListObject() {}
		~ListObject() {}

		Type GetType() const { return Type::LIST; };
		int Level() const { return LEVEL_LIST; };
		std::string GetString() const;

		Ptr<MathObject> DeepCopy() const;

		void push_back(Ptr<MathObject> const obj) { components.push_back(obj); }
	};
	*/
	std::string ListGetString(const std::vector<Ptr<MathObject>>& lst);
	std::vector<Ptr<MathObject>> ListDeepCopy(const std::vector<Ptr<MathObject>>& lst);

	class Atom : public MathObject
	{
		// 2020-7-3 �ܹ�����. ԭ�ȵ�Number, Variable, String��ȫ��������Atom.
		// Atom.str ��ʾ�����ݣ�
		// �����һ��number,��ôstr����һ�����ֶ�Ӧ���ַ����������һ��variable����������ĸ��ͷ���ַ��������������η����������string����һ����""�������ַ���.
		// ��������������ǣ�Number, Variable, String��������ֻ��std::string���洢�ģ���Level(),GetString(),DeepCopy()�ȷ���һģһ��
		//					������һ��ı��ʽ�����У����ض������������֡�ֻ��Ҫ�ڻ�����ֵ���漰�����������ʱ����Ҫ���֡�
		//					��˲���Atomͳһ��ʾ���﷨����������򵥡����漰��������ʱ������ʶ��Atom�����֡����������ַ���.
	public:
		std::string str;

		Atom() {};
		Atom(const std::string name_str) :str{ name_str } {};
		~Atom() {}

		Type GetType() const { return Type::ATOM; };

		Type AtomType() const;
		// ������ֵ. ��ʱֻ֧��double. ����Ժ�֧���˸���������Ҫ�޸Ĵ˴�.
		double NumberValue() const;

		int Level() const { return LEVEL_ATOM; };
		std::string GetString() const;

		Ptr<MathObject> DeepCopy() const;
	};

	class Vector : public MathObject
	{
		// eg. {7,x,y}
	public:
		Vector() {}
		~Vector() {}
	public:
		std::vector<Ptr<MathObject>> components;

		Type GetType() const { return Type::VECTOR; };
		int Level() const { return LEVEL_VECTOR; };
		std::string GetString() const;

		Ptr<MathObject> DeepCopy() const;
	};

	class Function : public MathObject
	{
		// eg. f[x], Sin[u]
	public:
		Function() {}
		~Function() {}
	public:
		Ptr<MathObject> function ;
		std::vector<Ptr<MathObject>> parameter ;

		Type GetType() const { return Type::FUNCTION; };
		int Level() const { return LEVEL_FUNCTION; };
		std::string GetString() const;

		Ptr<MathObject> DeepCopy() const;
	};
	
	class FunctionalOperator : public MathObject
	{
	public:
		FunctionalOperator() {};
		~FunctionalOperator() { }
	public:
		Ptr<MathObject> function ;
		std::vector<Ptr<Atom>> variables;
		std::vector<Ptr<MathObject>> fparameter;
		std::vector<Ptr<MathObject>> parameter;

		Type GetType() const { return Type::FUNCOPERATOR; };
		int Level() const { return LEVEL_FUNCTION; };
		std::string GetString() const;
		
		Ptr<MathObject> DeepCopy() const;
	};

	class Locate : public MathObject
	{
		// eg: arr[3], {a,b,3}[2]
	public:
		Locate() {}
		~Locate() {};
	public:
		Ptr<MathObject> object;
		std::vector<Ptr<MathObject>> location;

		Type GetType() const { return Type::LOCATE; };
		int Level() const { return LEVEL_LOCATE; };
		std::string GetString() const;

		Ptr<MathObject> DeepCopy() const;
	};
	class Power : public MathObject
	{
		// eg. a^5, x^y, y^p^q (this is equivalent to y^(p^q))
	public:
		Power() {}
		~Power() {}
	public:
		Ptr<MathObject> base;
		Ptr<MathObject> exponent;

		Type GetType() const { return Type::POWER; };
		int Level() const { return LEVEL_POWER; };
		std::string GetString() const;

		Ptr<MathObject> DeepCopy() const;
	};

	class Inverse : public MathObject
	{
		// eg. /y   /(x+y*z)
	public:
		Inverse() {}
        Inverse(Ptr<MathObject> const c) : component(c) {}
		~Inverse() {}
	public:
		Ptr<MathObject> component;

		Type GetType() const { return Type::INVERSE; };
		int Level() const { return LEVEL_INVERSE; };
		std::string GetString() const;

		Ptr<MathObject> DeepCopy() const;
	};

	class Item : public MathObject
	{
	public:
		Item() {}
		~Item() {}
        void push_back(Ptr<MathObject> const f) { factors.push_back(f); }
		// eg. x1*x2   x/y
	public:
		std::vector<Ptr<MathObject>> factors;

		Type GetType() const { return Type::ITEM; };
		int Level() const { return LEVEL_ITEM; };
		std::string GetString() const;

		Ptr<MathObject> DeepCopy() const;
	};

	class Opposite : public MathObject 
	{
	public:
		Opposite() {};
		Opposite(Ptr<MathObject> const component) :component{ component } {};
		~Opposite() {}
		// -x, -y*z, -{1,2}*u/p
	public:
		Ptr<MathObject> component;
		
		Type GetType() const { return Type::OPPOSITE; };
		int Level() const { return LEVEL_OPPOSITE; };
		std::string GetString() const;

		Ptr<MathObject> DeepCopy() const;
	};
	class Polynomial : public MathObject
	{
		// eg. 3.2+4*y+6/(x+1)
	public:
		Polynomial() {}
		~Polynomial() {}
	public:
		std::vector<Ptr<MathObject>> items;

		Type GetType() const { return Type::POLYNOMIAL; };
		int Level() const { return LEVEL_POLYNOMIAL; };
		std::string GetString() const;

		Ptr<MathObject> DeepCopy() const;

		void push_back(Ptr<MathObject> const itm) { items.push_back(itm); };
	};

	class Map : public MathObject
	{
		// eg. attr -> 1
	public:
		Map() {}
		Map(Ptr<MathObject> const a, Ptr<MathObject> const b) :key{ a }, value{ b }{};
		~Map() {}
	public:
		Ptr<MathObject> key;
		Ptr<MathObject> value;

		Type GetType() const { return Type::MAP; };
		int Level() const { return LEVEL_MAP; };
		std::string GetString() const ;

		Ptr<MathObject> DeepCopy() const;
	};

	class Compare : public MathObject
	{
		// eg. a==b, u<v,
	public:
		Compare() {}
		Compare(Ptr<MathObject> const a, const std::string op, Ptr<MathObject> const b) :left{ a }, op{ op }, right{ b }{};
		~Compare() {}
	public:
		std::string op;
		Ptr<MathObject> left;
		Ptr<MathObject> right;

		Type GetType() const { return Type::COMPARE; };
		int Level() const { return LEVEL_COMPARE; };
		std::string GetString() const ;

		Ptr<MathObject> DeepCopy() const;
	};

	class ErrorObject : public MathObject
	{
	public:
		std::string info;

		ErrorObject() {}
		ErrorObject(const std::string info) :info{ info } {};
		~ErrorObject() {};

		Type GetType() const { return Type::ERROR; };
		int Level() const { return LEVEL_ERROR; };
		std::string GetString() const { return info; };

		Ptr<MathObject> DeepCopy() const;
	};

	class EmptyObject : public MathObject
	{
	public:
		EmptyObject(){}
		~EmptyObject() {}

	public:

		Type GetType() const { return Type::EMPTY; };
		int Level() const { return LEVEL_EMPTY; };
		std::string GetString() const { return std::string(); };

		Ptr<MathObject> DeepCopy() const;
	};
	/*
	class Matrix : public MathObject
	{
	public:
		std::vector<Vector*> rowVectors;
	};
	
	*/




	// Math Function Type : MathObject -> MathObject
	typedef std::function<Ptr<MathObject>(Ptr<MathObject>)> MathFunction;
	
	class Rule
	{
	public:
		Ptr<MathObject> fromForm;
		Ptr<MathObject> toForm;
		
		static void Apply()
		{

		}
	};
	
	
}