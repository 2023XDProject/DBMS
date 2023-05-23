#pragma once
#include<list>
#include<regex>
#include<iostream>
#include <string>
#include <sstream>

using namespace std;


//SQL����������

class  SqlParser {
public:
    SqlParser(string sql);
    ~SqlParser();
    void parseCols();
    void parseTables();
    void parseConditions();
    void parseGroupCols();
    void parseOrderCols();
    string toString(); //�޷�������ԭ������
    list < string >  getParsedSqlList();//ȡ�ý�����SQL�ַ����б�
    void  setSingleLine(bool  isSingleLine); //�����Ƿ�����ʾ���ֶΣ�������

private:
    //����
    string Comma = " , ";

    //�ĸ��ո�
    string FourSpace = "      ";

    //�Ƿ�����ʾ�ֶΣ��������ı�ʶ��
    bool ISSINGLELINE = true;

    //��������SQL���
    string SQL;

    //SQL��ѡ�����
    string cols;

    //SQL�в��ҵı�
    string tables;

    //��������
    string conditions;

    //Group By���ֶ�
    string groupCols;

    //Order by���ֶ�
    string orderCols;

    //���ı�text���ҵ�regex�״�ƥ����ַ����������ִ�Сд
    //regex�� ������ʽ
    //text�������ҵ��ַ���
    //return  regex�״�ƥ����ַ�������δƥ�䷵�ؿ�
    string getMatchedString(string regex, string text);

    // //��word�Ƿ���lineText�д��ڣ�֧��������ʽ
    bool isContains(string lineText, string word);

    //�ڷָ�������ϻس�
    string getAddEnterStr(string str, string splitStr);

};

class StringBuffer {  //��c++ģ��stringBuffer��
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


