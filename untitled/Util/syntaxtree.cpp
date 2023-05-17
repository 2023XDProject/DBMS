#include "syntaxtree.h"

SyntaxTree::SyntaxTree(): CFL_(new CFileLogic()){

}
SyntaxTree::~SyntaxTree(){
    delete CFL_;
}

//根据sql语句构造CDBEntity
bool SyntaxTree::creatCDBEntity(string text,CDBEntity &te){

}

//根据sql语句构造CTableEntity
/*
 int order;ok//字段顺序
 string name; ok// 名称
 int type; ok// 类型(1:integer,2:bool,3:float,4:varchar2,5:date)
 int param;ok // 参数(VARCHAR几位)
 QDateTime mtime; // 最后修改时间
 int integrityNum; ok// 完整性约束信息条数
 vector<string> integrities; ok// 完整性约束信息(比如 primary key,not null,default 默认值(需要正则表达式自己依据字段类型匹配出来),unique)
*/
bool SyntaxTree::creatCTableEntity(string text,string dbName,CTableEntity &ct,vector<CFieldEntity> &cfe){
    smatch result;
    string temp;
    regex reg("^create\\s+table\\s+(\\w+)\\(");
    bool flag = regex_search(text, result,reg);

    ct.setName(result[1]);//添加表名
    ct.setTdf(CFL_->GetTbDefineFile(dbName,result[1]));//添加表定义文件路径
    ct.setTrd(CFL_->GetTbRecordFile(dbName,result[1]));//添加记录文件路径
    //qDebug()<<QString::fromStdString(result[1]);

    regex r1("\\s*(\\w+)\\s+(bool|date|float|integer|varchar2\\(\\d+\\))(\\s*primary\\s+key|\\s*not\\s+null|\\s*unique|\\s*default\\s+(\\w+)){0,4}");
    regex r2("(primary\\s+key|not\\s+null|unique|default\\s+(\\w+))",regex::icase);
    regex reg2("\\s*(\\w+)\\s+(bool|date|float|integer|varchar2\\(\\d+\\))");
    regex reg3("varchar2\\((\\d+)\\)");
    regex reg4("default\\s+(\\w+)");
    int num=0;

    for (sregex_iterator it(text.begin(), text.end(), r1), end_it;it != end_it; ++it){
        CFieldEntity tempCFE=CFieldEntity();
        temp=it->str();
        flag = regex_search(temp, result,reg2);
        //提取,添加字段顺序,名称，类型
        tempCFE.setOrder(num+1);
        tempCFE.setName(result[1]);
        if(result[2]=="integer"){
            tempCFE.setType(1);
        }else if(result[2]=="bool"){
            tempCFE.setType(2);
        }else if(result[2]=="float"){
            tempCFE.setType(3);
        }else if(result[2]=="date"){
            tempCFE.setType(5);
        }else{
            //varchar2类型
            smatch tempResult;
            string temp=result[2];
            flag = regex_search(temp,tempResult,reg3);
            if(flag==true){
                tempCFE.setType(4);
                string a=tempResult[1];
                tempCFE.setParam(atoi(a.c_str()));//
            }
        }
        //提取字段约束
        ++num;
        int num2=0;
        sregex_iterator it2(temp.begin(), temp.end(), r2);
        for (end_it;it2 != end_it; ++it2){
            ++num2;

            tempCFE.setIntegrity(it2->str());//添加完整性约束信息
            if(it2->str()=="primary key"){
                tempCFE.setIntegrityType(tempCFE.getIntegrityType()+1);
            }else if(it2->str()=="not null"){
                tempCFE.setIntegrityType(tempCFE.getIntegrityType()+10);
            }else if(it2->str()=="unique"){
                tempCFE.setIntegrityType(tempCFE.getIntegrityType()+100);
            }else{
                tempCFE.setIntegrityType(tempCFE.getIntegrityType()+1000);
                temp=it2->str();
                flag = regex_search(temp, result,reg4);
                tempCFE.setIntegrity(result[1]);
            }
            //qDebug()<< QString::fromStdString( it2->str());
        }
        tempCFE.setIntegrityNum(num2);//添加完整性约束信息条数
        tempCFE.setMtime(QDateTime::currentDateTime());//添加最后修改时间
        cfe.push_back(tempCFE);
    }
    ct.setField_num(num);//添加字段数
    ct.setRecord_num(0);//添加记录数
    ct.setCrtime(QDateTime::currentDateTime());//添加表格创建时间
    ct.setMtime(QDateTime::currentDateTime());//添加表格最后修改时间
}

//根据sql语句修改字段,获取要修改的字段的名称，类型，null
bool SyntaxTree::modifyTableField(string text,string& fieldName,int& type,int& param,string& constraint){
    smatch result;
    string temp;
    bool flag;
    regex reg3("varchar2\\((\\d+)\\)");
    regex r1("(\\w+)\\s+(bool|date|float|integer|varchar2\\(\\d+\\))(\\s+null|\\s+not\\s+null)?");
    for (sregex_iterator it(text.begin(), text.end(), r1), end_it;it != end_it; ++it){
        temp=it->str();
        flag = regex_search(text, result,r1);
        fieldName=result[1];
        temp=result[2];
        if(result[2]=="integer"){
            type=1;
        }else if(result[2]=="bool"){
            type=2;
        }else if(result[2]=="float"){
            type=3;
        }else if(result[2]=="date"){
            type=5;
        }else{
            //varchar2类型
            smatch tempResult;
            string temp=result[2];
            flag = regex_search(temp,tempResult,reg3);
            if(flag==true){
                type=4;
                string a=tempResult[1];
                param=atoi(a.c_str());//
            }
        }
        if(result.size()>3){
            constraint=result[3];
        }
        //qDebug()<<result.size();
        qDebug()<<QString::fromStdString(result[1])<<QString::fromStdString(result[2]);
        qDebug()<<QString::fromStdString(result[3]);
    }
}

//根据sql语句添加字段
bool SyntaxTree::addTableField(string text,string dbName, int& fieldNum,vector<CFieldEntity> &cfe){
    smatch result;
    string temp;//alter table emp add(esex varchar2(20),eage number(10));
    bool flag;
    regex r1("\\s*(\\w+)\\s+(bool|date|float|integer|varchar2\\(\\d+\\))(\\s*primary\\s+key|\\s*not\\s+null|\\s*unique|\\s*default\\s+(\\w+)){0,4}");
    regex r2("(primary\\s+key|not\\s+null|unique|default\\s+(\\w+))",regex::icase);
    regex reg2("\\s*(\\w+)\\s+(bool|date|float|integer|varchar2\\(\\d+\\))");
    regex reg3("varchar2\\((\\d+)\\)");
    regex reg4("default\\s+(\\w+)");
    int num=0;

    for (sregex_iterator it(text.begin(), text.end(), r1), end_it;it != end_it; ++it){
        CFieldEntity tempCFE=CFieldEntity();
        temp=it->str();
        flag = regex_search(temp, result,reg2);
        //提取,添加字段顺序,名称，类型
        tempCFE.setOrder(num+1);
        tempCFE.setName(result[1]);
        if(result[2]=="integer"){
            tempCFE.setType(1);
        }else if(result[2]=="bool"){
            tempCFE.setType(2);
        }else if(result[2]=="float"){
            tempCFE.setType(3);
        }else if(result[2]=="date"){
            tempCFE.setType(5);
        }else{
            //varchar2类型
            smatch tempResult;
            string temp=result[2];
            flag = regex_search(temp,tempResult,reg3);
            if(flag==true){
                tempCFE.setType(4);
                string a=tempResult[1];
                tempCFE.setParam(atoi(a.c_str()));//
            }
        }
        //提取字段约束
        ++num;
        int num2=0;
        sregex_iterator it2(temp.begin(), temp.end(), r2);
        for (end_it;it2 != end_it; ++it2){
            ++num2;

            tempCFE.setIntegrity(it2->str());//添加完整性约束信息
            if(it2->str()=="primary key"){
                tempCFE.setIntegrityType(tempCFE.getIntegrityType()+1);
            }else if(it2->str()=="not null"){
                tempCFE.setIntegrityType(tempCFE.getIntegrityType()+10);
            }else if(it2->str()=="unique"){
                tempCFE.setIntegrityType(tempCFE.getIntegrityType()+100);
            }else{
                tempCFE.setIntegrityType(tempCFE.getIntegrityType()+1000);
                temp=it2->str();
                flag = regex_search(temp, result,reg4);
                tempCFE.setIntegrity(result[1]);
            }
            //qDebug()<< QString::fromStdString( it2->str());
        }
        tempCFE.setIntegrityNum(num2);//添加完整性约束信息条数
        tempCFE.setMtime(QDateTime::currentDateTime());//添加最后修改时间
        cfe.push_back(tempCFE);
    }
    fieldNum=cfe.size();
}

//根据sql语句重命名字段
bool SyntaxTree::renameTableField(string text,string& oldName,string& newName){
    smatch result;
    string temp;
    bool flag;
    //alter table emp rename column esex to eesex;
    regex r1("alter\\s+table\\s+\\w+\\s+rename\\s+column\\s+(\\w+)\\s+to\\s+(\\w+)\\s*;$");
    //    for (sregex_iterator it(text.begin(), text.end(), r1), end_it;it != end_it; ++it){
    //        temp=it->str();
    flag = regex_search(text, result,r1);
    if(flag==false){
        return false;
    }else{
        oldName=result[1];
        newName=result[2];
        return true;
    }
}

//根据sql语句删除字段
bool SyntaxTree::dropTableField(string text,vector<string>& column){
    //"\\s*(\\w+)\\s+(bool|date|float|integer|varchar2\\(\\d+\\))(\\s*primary\\s+key|\\s*not\\s+null|\\s*unique|\\s*default\\s+(\\w+)){0,4}
    smatch result;
    string temp;//alter table table_name drop (column column_name1,column_name2,...);
    bool flag;
    regex r1("\\((\\w+,*){1,}");
    regex r2("(\\w+){1,}");
    //    regex reg2("\\s*(\\w+)\\s+(bool|date|float|integer|varchar2\\(\\d+\\))");
    //    regex reg3("varchar2\\((\\d+)\\)");
    //    regex reg4("default\\s+(\\w+)");
    int num=0;

    for (sregex_iterator it(text.begin(), text.end(), r1), end_it;it != end_it; ++it){
        //CFieldEntity tempCFE=CFieldEntity();
        temp=it->str();
        //qDebug()<<QString::fromStdString(temp);
        for (sregex_iterator it2(temp.begin(), temp.end(), r2), end_it;it2 != end_it; ++it2){
            temp=it2->str();
            column.push_back(temp);
            //qDebug()<<QString::fromStdString(temp);
        }
    }
}

////根据sql语句重命名字段
//bool SyntaxTree::renameTableField(string text,string& oldName,string& newName){
//    smatch result;
//    string temp;
//    bool flag;
//    //alter table emp rename column esex to eesex;
//    regex r1("alter\\s+table\\s+\\w+\\s+rename\\s+column\\s+(\\w+)\\s+to\\s+(\\w+)\\s*;$");
//    //    for (sregex_iterator it(text.begin(), text.end(), r1), end_it;it != end_it; ++it){
//    //        temp=it->str();
//    flag = regex_search(text, result,r1);
//    if(flag==false){
//        return false;
//    }else{
//        oldName=result[1];
//        newName=result[2];
//        return true;
//    }
//}
//}
