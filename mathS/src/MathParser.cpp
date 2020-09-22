#include <MathParser.h>
#include <stack>
#include <string-switch.h>

using namespace mathS;

// �������ʽ
Ptr<MathObject> Parser::Parse() {

    std::vector<Token> tokens;
    Token tok;
    while (true) {
        lexer.get(tok);
        if (tok.type == Token::END) break;
        tokens.push_back(tok);
    }
    
    int i;
    auto obj = parseObject(tokens, 0, i);
    if (i < tokens.size()) {
        return New<ErrorObject>("Parse: Syntax Error. Unexpected Symbol " + tokens[i].text);
    }
    
    return obj;
}

short Parser::level(const std::string &c) {
    SWITCH(c.c_str()) {
        CASE(c, "(") return MathObject::LEVEL_FUNCTION;
        CASE(c, "<<") return MathObject::LEVEL_FUNCOPERATOR;
        CASE(c, "[") return MathObject::LEVEL_LOCATE;
        CASE(c, "^") return MathObject::LEVEL_POWER;
        CASE(c, "/") return MathObject::LEVEL_ITEM;
        CASE(c, "*") return MathObject::LEVEL_ITEM;
        CASE(c, "-") return MathObject::LEVEL_POLYNOMIAL;
        CASE(c, "+") return MathObject::LEVEL_POLYNOMIAL;
        CASE(c, "==") return MathObject::LEVEL_COMPARE;
        CASE(c, "<") return MathObject::LEVEL_COMPARE;
        CASE(c, ">") return MathObject::LEVEL_COMPARE;
        CASE(c, "<=") return MathObject::LEVEL_COMPARE;
        CASE(c, ">=") return MathObject::LEVEL_COMPARE;
        CASE(c, ",") return MathObject::LEVEL_LIST;
        CASE(c, "->")return MathObject::LEVEL_MAP;

        CASE(c, ")") return MathObject::LEVEL_CLOSED;
        CASE(c, "|") return MathObject::LEVEL_CLOSED;
        CASE(c, ">>") return MathObject::LEVEL_CLOSED;
        CASE(c, "]") return MathObject::LEVEL_CLOSED;
        CASE(c, "}") return MathObject::LEVEL_CLOSED;

        default: return MathObject::LEVEL_ERROR;
    }
    return 0;
}

#define ERROR_CHECK(x) if (x->GetType() == MathObject::ERROR) return x
Ptr<MathObject> mathS::Parser::parseObject(const std::vector<Token>& tokens, const int start, int& i)
{
    i = start;
    // EmptyObject
    if (i >= tokens.size() || level(tokens[i].text) == MathObject::LEVEL_CLOSED) 
        return New<EmptyObject>();
    return parseList(tokens, i, i);
}
Ptr<MathObject> mathS::Parser::parseAtom(const std::vector<Token>& tokens, const int start, int& i)
{
    Ptr<MathObject> obj;
    i = start;
    if (i >= tokens.size())
        return New<ErrorObject>("Parse: Expression is incompleted.");
    if (tokens[i].type == Token::NUMORSYMB || tokens[i].type == Token::STRING) {
        obj = New<Atom>(tokens[i].text);
        i++;
        return obj;
    }
    else if (tokens[i].type == Token::OPERATOR) {
        // ����ǲ���������ô������(_OBJECT)��{_OBJECT}
        if (tokens[i].text == "(") {
            obj = parseObject(tokens, start + 1, i);
            ERROR_CHECK(obj);
            if (i < tokens.size() && tokens[i].text == ")") {
                i++;
                return obj;
            }
            else {
                return New<ErrorObject>("Parser: Unmatched brace (");
            }
        }
        else if(tokens[i].text == "{")
        {
            auto lst = parseList_forced(tokens, start + 1, i);
            if (lst->GetType() == MathObject::EMPTY)
                return New<ErrorObject>("Parser: Unmatched brace {");
            ERROR_CHECK(lst);

            Ptr<Vector> vobj = New<Vector>();
            vobj->list = Dynamic_cast<ListObject, MathObject>(lst);
            if (i < tokens.size() && tokens[i].text == "}") {
                i++;
                return vobj;
            }
            else {
                return New<ErrorObject>("Parser: Unmatched brace {");
            }
        }
    }
    return  New<ErrorObject>("Parse: Syntax Error. Unexpected Symbol. " + tokens[i].text);
}


Ptr<MathObject> mathS::Parser::parseFunction(const std::vector<Token>& tokens, const int start, int& i)
{
    i = start;

    auto f = parseAtom(tokens, start, i);
    ERROR_CHECK(f);
    if (i >= tokens.size()) 
        return f;
    
    if (tokens[i].text == "(") {
        // ( ) ��ʾ����
        auto p = parseObject(tokens, i + 1, i);
        if (p->GetType() == MathObject::ERROR) {
            return p;
        }
        if (i < tokens.size() && tokens[i].text == ")") {
            i++;
            Ptr<Function> fobj = New<Function>();
            fobj->function = f;
            fobj->parameter = p;
            return fobj;
        }
        else {
            return New<ErrorObject>("Parse: Syntax Error. Unmatched brace (");
        }
    }
    else if (tokens[i].text == "<<") {
        // << | >>( ) ��ʾ��������
        std::vector<Ptr<Atom>> vars;
        // variables
        while (true) {
            auto v = parseAtom(tokens, i + 1, i);
            ERROR_CHECK(v);
            vars.push_back(Dynamic_cast<Atom, MathObject>(v));
            if (i >= tokens.size())
                return New<ErrorObject>("Parse: Syntax Error. Unmatched <<. ");
            
            if (tokens[i].text == "|") 
                break;
            else if (tokens[i].text != ",") 
                return New<ErrorObject>("Parse: Syntax Error. Unmatched <<. ");
        }
        auto fpara = parseObject(tokens, i + 1, i);
        ERROR_CHECK(fpara);
        if (!(i < tokens.size() && tokens[i].text == ">>"))
            return New<ErrorObject>("Parser: Unmatched <<");
        
        i++;
        if (!(i < tokens.size() && tokens[i].text == "("))
            return New<ErrorObject>("Parser: Incompleted Functional Operator");
        
        auto para = parseObject(tokens, i + 1, i);
        ERROR_CHECK(para);
        if (!(i < tokens.size() && tokens[i].text == ")")) 
            return New<ErrorObject>("Parser: Unmatched brace (");

        Ptr<FunctionalOperator> fop = New<FunctionalOperator>();

        fop->function = f;
        fop->variables = vars;
        fop->fparameter = fpara;
        fop->parameter = para;
        i++;
        return fop;
    }
    else if (level(tokens[i].text) > MathObject::LEVEL_FUNCTION) {
        // �����Ѿ��ضϣ�˵�������Ǻ�����ʽ���� f ���ؼ���
        return f;
    }
    else {
        return New<ErrorObject>("Parse: Syntax Error. Unexpected symbol " + tokens[i].text);
    }

}

Ptr<MathObject> mathS::Parser::parseLocate(const std::vector<Token>& tokens, const int start, int& i)
{
    i = start;
    auto obj = parseFunction(tokens, start, i);
    ERROR_CHECK(obj);
    if (i >= tokens.size() || level(tokens[i].text) > MathObject::LEVEL_LOCATE) {
        return obj;
    }
    if (tokens[i].text != "[") {
        auto loc = parseObject(tokens, i + 1, i);
        ERROR_CHECK(loc);

        if (!(i < tokens.size() && tokens[i].text == "]")) 
            return New<ErrorObject>("Parse: Syntax Error. Unmatched brace [");
        
        Ptr<Locate> lc = New<Locate>();
        lc->object = obj;
        lc->location = loc;
        return lc;
    }
    else {
        return New<ErrorObject>("Parse: Syntax Error. Unexpected symbol " + tokens[i].text);
    }
       
}

Ptr<MathObject> mathS::Parser::parsePower(const std::vector<Token>& tokens, const int start, int& i)
{
    i = start;
    auto b = parseLocate(tokens, start, i);
    ERROR_CHECK(b);
    // �Ƿ���ָ����ʽ
    if (!(i < tokens.size() && tokens[i].text == "^")) {
        return b;
    }
    auto e = parsePower(tokens, i + 1, i);
    ERROR_CHECK(e);
    // parsePower �� parseAtom һ�����᷵�� Empty
    Ptr<Power> pw = New<Power>();
    pw->base = b;
    pw->exponent = e;
    return pw;
}

Ptr<MathObject> mathS::Parser::parseItem(const std::vector<Token>& tokens, const int start, int& i)
{
    i = start;
    auto fct = parsePower(tokens, start, i);
    ERROR_CHECK(fct);
    if (i >= tokens.size() || level(tokens[i].text) > MathObject::LEVEL_ITEM) {
        // �������ֻ��һ��factor����ô��ֱ�ӷ������factor������������һ��item
        return fct;
    }

    Ptr<Item> itm = New<Item>();
    itm->push_back(fct);
    while (true) {
        if (tokens[i].text == "*") {
            // ���ӳ�����
            auto t = parsePower(tokens, i + 1, i);
            ERROR_CHECK(t);
            itm->push_back(t);
            if (i >= tokens.size() || level(tokens[i].text) > MathObject::LEVEL_ITEM)
                return itm;
        }
        else if (tokens[i].text == "/") {
            // ���ӳ�����
            auto t = parsePower(tokens, i + 1, i);
            ERROR_CHECK(t);
            itm->push_back(New<Inverse>(t));
            if (i >= tokens.size() || level(tokens[i].text) > MathObject::LEVEL_ITEM)
                return itm;
        }
        else {
            return New<ErrorObject>("Parse: Syntax Error. Unexpected Symbol " + tokens[i].text);
        }
        
    }
    
}

Ptr<MathObject> mathS::Parser::parsePolynomial(const std::vector<Token>& tokens, const int start, int& i)
{
    i = start;
    if (i >= tokens.size() || level(tokens[i].text) > MathObject::LEVEL_POLYNOMIAL) {
        return New<ErrorObject>("Parse: Syntax Error. Incomplete expression.");
    }
    Ptr<MathObject> itm;
    Ptr<Polynomial> poly = New<Polynomial>();
    if (tokens[i].text != "+" || tokens[i].text != "-") {
        itm = parseItem(tokens, i, i);
        ERROR_CHECK(itm);
        poly->push_back(itm);
    }
    while (true) {
        if (i >= tokens.size() || level(tokens[i].text) > MathObject::LEVEL_POLYNOMIAL) {
            // ��ֻ��һ��򻯱��ʽ
            if (poly->items.size() > 1)
                return poly;
            else 
                return poly->items[0];
        }
        if (tokens[i].text == "+") {
            // ��������
            auto t = parseItem(tokens, i + 1, i);
            ERROR_CHECK(t);
            poly->push_back(t);
        }
        else if (tokens[i].text == "-") {
            // ���Ӹ���
            auto t = parseItem(tokens, i + 1, i);
            ERROR_CHECK(t);
            poly->push_back(New<Opposite>(t));
        }
        else {
            // ����ʽû����ֹ������һ���ַ��޷�ʶ����Ч������
            return New<ErrorObject>("Parse: Syntax Error. Unexpected Symbol " + tokens[i].text);
        }
    }
}

Ptr<MathObject> mathS::Parser::parseMap(const std::vector<Token>& tokens, const int start, int& i)
{
    i = start;
    auto a = parsePolynomial(tokens, i, i);
    ERROR_CHECK(a);
    if (i >= tokens.size() || level(tokens[i].text) > MathObject::LEVEL_MAP)
        return a;
    if (tokens[i].text != "->")
        return New<ErrorObject>("Parse: Syntax Error. Unexpected Symbol " + tokens[i].text);
    
    auto b = parsePolynomial(tokens, i + 1, i);
    ERROR_CHECK(b);

    Ptr<Map> mp = New<Map>(a, b);
    return mp;
}

Ptr<MathObject> mathS::Parser::parseCompare(const std::vector<Token>& tokens, const int start, int& i)
{
    i = start;
    auto a = parseMap(tokens, i, i);
    ERROR_CHECK(a);
    if (i >= tokens.size() || level(tokens[i].text) > MathObject::LEVEL_COMPARE)
        return a;
    if (level(tokens[i].text) != MathObject::LEVEL_COMPARE) {
        return New<ErrorObject>("Parse: Syntax Error. Unexpected Symbol " + tokens[i].text);
    }
    auto b = parseMap(tokens, i + 1, i);
    ERROR_CHECK(b);

    Ptr<Compare> cmp = New<Compare>(a, b);
    return cmp;
}

Ptr<MathObject> mathS::Parser::parseList(const std::vector<Token>& tokens, const int start, int& i)
{
    i = start;
    auto obj = parseCompare(tokens, start, i);
    ERROR_CHECK(obj);
    if (i >= tokens.size() || level(tokens[i].text) > MathObject::LEVEL_LIST) {
        // �������ֻ��һ��obj����ô��ֱ�ӷ������obj������������һ��List
        return obj;
    }

    Ptr<ListObject> lst = New<ListObject>();
    lst->push_back(obj);
    while (true) {
        if (tokens[i].text == ",") {
            auto t = parseCompare(tokens, i + 1, i);
            ERROR_CHECK(t);

            lst->push_back(t);
            if (i >= tokens.size() || level(tokens[i].text) > MathObject::LEVEL_LIST)
                return lst;
        }
        else {
            return New<ErrorObject>("Parse: Syntax Error. Unexpected Symbol " + tokens[i].text);
        }
    }
}

Ptr<MathObject> mathS::Parser::parseList_forced(const std::vector<Token>& tokens, const int start, int& i)
{
    i = start;
    auto obj = parseCompare(tokens, start, i);
    ERROR_CHECK(obj);

    Ptr<ListObject> lst = New<ListObject>();
    lst->push_back(obj);
    while (true) {
        if (i >= tokens.size() || level(tokens[i].text) > MathObject::LEVEL_LIST)
            return lst;
        if (tokens[i].text == ",") {
            auto t = parseCompare(tokens, i + 1, i);
            if (t->GetType() == MathObject::ERROR) {
                return t;
            }
            lst->push_back(t);
        }
        else {
            return New<ErrorObject>("Parse: Syntax Error. Unexpected Symbol " + tokens[i].text);
        }
    }
}
