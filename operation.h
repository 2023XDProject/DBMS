#ifndef OPERATION_H
#define OPERATION_H
#include<QString>
#include<QRegExp>
#include<Info.h>
#include<iostream>
#include<structures.h>
#include "QStringList"
class Operation
{
public:
    Operation();
    Operation(QString sql);
    QString operation_type;//操作类型：alter，select，update，insert，delete,create
    QString alter_type;//alter table (add,drop,modify)
    QString target_database = "";//目标数据库名
    QString target_table = "";//目标表名
    vector<QString>* target_column;//目标列（QString可以改）
    vector<QString>* conditions;//条件（QString可以改）
    vector<QString>* values;//所有的值
    int error_code;//如果操作是错误的，应给该变量赋值
    QString sql;

    void get_operation_type();//在构造器中调用，用于获取sql语句的类型，并给operation_type赋值
    void handle_select();
    void handle_insert();
    void handle_update();
    void handle_create();
    void handle_delete();
    void handle_alter();
    void parse_column(QString columns);
    void execute();           //执行sql语句
    QString is_int_float_varchar_char(QString value);//这个函数是用来判断一个字符串类型的，返回值是表示类型的字符串
    bool add_modify_attribute(QString attributeString,int type);//add或modify的语法解析是一致的，为了避免代码冗余，通过一个函数来实现
};

#endif // OPERATION_H
