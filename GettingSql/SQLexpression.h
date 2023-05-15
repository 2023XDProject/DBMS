#pragma once
//ͷ�ļ� ��������
#ifndef SQLEXPRESSION_H_
#define SQLEXPRESSION_H_
#include<string.h>
#include<vector>
#include <boost/regex.hpp>  //����Ӧ��Ҫ��װboost���������������
#include <algorithm>
#include<iostream>

using namespace std;
using namespace boost;

////////////��֪�����ӵ�sql�����ô�㣨����Ƕ�׻�����ϼ�����֣� ֻ�ܸ��Ƚϻ����򵥵�/////////
///////////�����Ҷ�ȥ�����������   CSDN���ӣ�http://t.csdn.cn/XRQVu ///////////////////////////////////////////////////////////////

class SqlEx {
public:
	SqlEx(string ex);  //������
	~SqlEx();
	bool check(); //��鲢ƥ��sql����
	vector<vector<string>> getResult(); //��ȡ�������
private:
	bool ForUpdate();
	bool ForDelete();
	bool ForInsert();
	bool ForCreate();
	bool ForSelect();
	bool ForDrop();
	string sql(string str);
	vector<vector<string>> result; //�������
	string Ex;
};


#endif 

