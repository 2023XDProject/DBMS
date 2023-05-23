#pragma once
#include<list>
#include<regex>
#include<iostream>
#include <string>
#include <sstream>

using namespace std;


//SQL语句解析器类

class  SqlParser {
public:
    SqlParser(string sql);
    ~SqlParser();
    void parseCols();
    void parseTables();
    void parseConditions();
    void parseGroupCols();
    void parseOrderCols();
    string toString(); //无法解析则原样返回
    list < string >  getParsedSqlList();//取得解析的SQL字符串列表
    void  setSingleLine(bool  isSingleLine); //设置是否单行显示表，字段，条件等

private:
    //逗号
    string Comma = " , ";

    //四个空格
    string FourSpace = "      ";

    //是否单行显示字段，表，条件的标识量
    bool ISSINGLELINE = true;

    //待解析的SQL语句
    string SQL;

    //SQL中选择的列
    string cols;

    //SQL中查找的表
    string tables;

    //查找条件
    string conditions;

    //Group By的字段
    string groupCols;

    //Order by的字段
    string orderCols;

    //从文本text中找到regex首次匹配的字符串，不区分大小写
    //regex： 正则表达式
    //text：欲查找的字符串
    //return  regex首次匹配的字符串，如未匹配返回空
    string getMatchedString(string regex, string text);

    // //看word是否在lineText中存在，支持正则表达式
    bool isContains(string lineText, string word);

    //在分隔符后加上回车
    string getAddEnterStr(string str, string splitStr);

};

class StringBuffer {  //用c++模拟stringBuffer类
public:
    StringBuffer() {}

    void append(const std::string& str) {
        ss << str;
    }

    std::string toString() const {
        return ss.str();
    }

private:
    std::stringstream ss;
};


