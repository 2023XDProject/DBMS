/*
 * 统一定义程序中的数据类型
 * CDBEntity类存放数据库基本信息,查询，修改（没有容错）数据库信息
 */

#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <string>
#include <QDateTime>
using namespace std;

//数据库信息块
struct DatabaseBlock{
 bool type; // 数据库类型：true系统数据库，false用户自定义数据库
 string name; // 数据库名称
 string filepath; // 数据库文件路径
 QDateTime crtime; // 创建时间
};

//表信息块
struct TableBlock
{
 string name; // 名称
 int record_num; // 记录数
 int field_num; // 字段数
 string tdf; // 表定义文件路径
 string trd; // 记录文件路径
 QDateTime crtime; // 表格创建时间
 QDateTime mtime; // 最后修改时间
};

//字段信息块
struct FieldBlock
{
 string name; // 名称
 int type; // 类型
 int param; // 参数
 QDateTime mtime; // 最后修改时间
 int integrities; // 完整性约束信息
};

/*
 * 存放数据库基本信息,查询，修改（没有容错）数据库信息
 */
class CDBEntity{
public:
    CDBEntity(){};
    CDBEntity(bool type,string n,string f, QDateTime t){
        DB_.type=type;
        DB_.name=n;
        DB_.filepath=f;
        DB_.crtime=t;
    };

    string getBaseName(){return DB_.name;}
    bool getBaseType(){return DB_.type;}
    string getBaseFilepath(){return DB_.filepath;}
    QDateTime getBaseCrtime(){return DB_.crtime;}

    void setBaseName(string n){DB_.name=n;};
    void setBaseType(bool t){DB_.type=t;};
    void setBaseFilepath(string f){DB_.filepath=f;}
    void getBaseCrtime(QDateTime b){DB_.crtime=b;}

private:
   DatabaseBlock DB_;
};

/*
 * 存放表信息，查询，修改（没有容错）表信息
 */
class CTableEntity{
public:
    CTableEntity(){};
    CTableEntity(string name,int record_num,int field_num,string tdf,string trd,QDateTime crtime,QDateTime mtime){
        TB_.name=name; // 名称
        TB_.record_num= record_num; // 记录数
        TB_.field_num =field_num; // 字段数
        TB_.tdf =tdf; // 表定义文件路径
        TB_.trd =trd; // 记录文件路径
        TB_.crtime =crtime; // 表格创建时间
        TB_.mtime =mtime; // 最后修改时间
    }
    string getName(){return TB_.name;}
    int getRecord_num(){return TB_.record_num; }
    int getField_num(){return TB_.field_num;}
    string getTdf(){return TB_.tdf;}
    string getTrd(){return TB_.trd;}
    QDateTime getCrtime(){return TB_.crtime;}
    QDateTime getMtime(){return TB_.mtime;}

    void setName(string n){TB_.name=n;}
    void setRecord_num(int r){TB_.record_num=r;}
    void setField_num(int f){TB_.field_num=f;}
    void setTdf(string t){TB_.tdf=t;}
    void setTrd(string t){TB_.trd=t;}
    void setCrtime(QDateTime c){TB_.crtime=c;}
    void setMtime(QDateTime m){TB_.mtime=m;}

private:
     TableBlock TB_;
};

/*
 * 存放字段信息，查询，修改（没有容错）字段信息
 */
class CFiledEntity{
    CFiledEntity(){};
    CFiledEntity(string name,int type,int param,QDateTime mtime,int integrities){
        FB_.name=name; // 名称
        FB_.type=type; // 类型
        FB_.param=param; // 参数
        FB_.mtime=mtime; // 最后修改时间
        FB_.integrities=integrities; // 完整性约束信息
    }
    string getName(){return FB_.name;}
    int getType(){return FB_.type; }
    int getParam(){return FB_.param;}
    QDateTime getMtime(){return FB_.mtime;}
    int getIntegrities(){return FB_.integrities;}

    void setName(string n){FB_.name=n;}
    void getType(int t){FB_.type=t;}
    void getParam(int p){FB_.param=p;}
    void getMtime(QDateTime m){FB_.mtime=m;}
    void getIntegrities(int i){FB_.integrities=i;}

private:
     FieldBlock FB_;
};

#endif // DATASTRUCTURE_H
