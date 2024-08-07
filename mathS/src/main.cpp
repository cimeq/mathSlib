// mathS.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "MathParser.h"
#include "LBAssembler.h"
#include "Rule.h"
#include "Evaluate.h"

using namespace mathS;

int main() {
    
    
    std::string str;
    Assembler assembler;
   
    // Evaluate测试
    while (true) {
        std::cout << ">>> ";
        getline(std::cin, str);
        auto obj = Parse(str);
        while (Evaluate(obj, obj));
        std::cout << obj->GetString() << std::endl;
    } 
    /*// Rule模块测试
    while (true) {
        std::cout << "Source pattern: ";
        getline(std::cin, str);
        auto srcpattern = Parse(str);

        std::cout << "Target pattern: ";
        getline(std::cin, str);
        auto tarpattern = Parse(str);

        std::cout << "Object: ";
        getline(std::cin, str);
        auto obj = Parse(str);

        auto rule = MakeRule(srcpattern, tarpattern);
        Ptr<MathObject> rst;
        if (rule(obj, rst))
            std::cout << rst->GetString() << std::endl;
        else
            std::cout << "No" << std::endl;
    }*/
              
    // 计算器程序；测试LBAssembler
    while (true) {
        std::cout << ">>> ";
        getline(std::cin, str);
        auto mobj = Parse(str);

        // 检查表达式是否合法，并输出错误信息
        if (mobj->GetType() == MathObject::ERROR) {
            std::cout << mobj->GetString() << std::endl;
            continue;
        }
        // 计算器程序不需要变量参数，空的参数表
        std::vector<std::string> params = {"x"};
        // 组装
        auto f = assembler.Assemble(mobj, params);
        // 输出结果
        std::cout << f({})->GetString() << std::endl;
        // std::cout << "Latex = " << mobj->GetLaTeXString() << std::endl;
    }
    return 0;
}