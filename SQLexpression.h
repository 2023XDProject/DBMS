#pragma once
//头文件 语句解析类
#ifndef SQLEXPRESSION_H_
#define SQLEXPRESSION_H_
#include<string.h>
#include<vector>
#include <boost/regex.hpp>  //这里应该要安装boost函数库才能正常用
#include <algorithm>
#include<iostream>

using namespace std;
using namespace boost;

////////////不知道复杂的sql语句怎么搞（比如嵌套或者求合集差集这种） 只能搞搞比较基础简单的/////////
///////////建议大家都去看看正则语句   CSDN链接：http://t.csdn.cn/XRQVu ///////////////////////////////////////////////////////////////

class SqlEx {
public:
	SqlEx(string ex);  //构造器
	~SqlEx();
	bool check(); //检查并匹配sql命令
	vector<vector<string>> getResult(); //获取解析结果
private:
	bool ForUpdate();
	bool ForDelete();
	bool ForInsert();
	bool ForCreate();
	bool ForSelect();
	bool ForDrop();
	string sql(string str);
	vector<vector<string>> result; //解析结果
	string Ex;
};


#endif 

