#include "crkdbmsdoc.h"

CRKDBMSDoc::CRKDBMSDoc():CDBL_(new CDBLogic()),
    CTL_(new CTableLogic()),STree_(new SyntaxTree()),
    DBName("")
{}

CRKDBMSDoc::~CRKDBMSDoc(){
    delete CDBL_;
}

//新建文档，创建默认数据库
bool CRKDBMSDoc::OnNewDocument(){
    //创建Runako.db文件
    CDBL_->createRuankoFile();
    DBName="Ruanko";

    //创建默认数据库
    QDateTime time=QDateTime::currentDateTime();
    string temp=CDBL_->getDefaDBFile();
    CDBEntity defCDBE=CDBEntity(true,"Ruanko","./data/Ruanko",time);
    bool finished=CDBL_->CreateDatabase(defCDBE);
    if(finished==true){
        return true;
    }else{
        return false;
    }
}

//新建数据库
bool CRKDBMSDoc::newDocument(string strName){
    //创建数据库
    QDateTime time=QDateTime::currentDateTime();
    string temp=CDBL_->getDBFolder(strName);
    CDBEntity defCDBE=CDBEntity(true,strName,temp,time);
    bool finished=CDBL_->CreateDatabase(defCDBE);

    if(finished==true){
        DBName=QString::fromStdString(strName);
        return true;
    }else{
        return false;
    }
}

//匹配sql语句类型
bool CRKDBMSDoc::matchQSLType(QString text){
     string temp=text.toLower().toStdString();

     if(regex_search (temp, regex("create\\s+table"))){
          //新建表
//         CTableEntity te;
//         STree_->creatCTableEntity(text,te);
//         CTL_->CreateTable(DBName,te);
         qDebug()<<" create table ok";
     }else if(regex_search (temp, regex("drop\\s+table"))){
          //删除表
         qDebug()<<" drop table ok";
     }else if(regex_search (temp, regex("alter[ ]*table"))){
         //更改表
         qDebug()<<" alter table ok";
     }else if(regex_search (temp, regex("select[ ]*"))){
         //查询表
         qDebug()<<" select table ok";
     }else if(regex_search (temp, regex("create[ ]*database"))){
         //新建数据库
         qDebug()<<" create database ok";
     }else if(regex_search (temp, regex("drop[ ]*database"))){
         //删除数据库
         qDebug()<<" drop database ok";
     }
}
