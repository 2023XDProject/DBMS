#include "crkdbmsdoc.h"

CRKDBMSDoc::CRKDBMSDoc():CDBL_(new CDBLogic()),
    CTL_(new CTableLogic()),STree_(new SyntaxTree()),
    CRL_(new CRecordLogic()),
    DBName("")
{}

CRKDBMSDoc::~CRKDBMSDoc(){
    delete CDBL_;
    delete CTL_;
    delete STree_;
    delete CRL_;
}

//新建文档，创建默认数据库
bool CRKDBMSDoc::OnNewDocument(){
    //创建Runako.db文件
    CDBL_->createRuankoFile();
    DBName="Ruanko";

    //创建data文件夹
    bool finished=CDBL_->createDataDBFolder();
    if(finished==true){
        //创建默认数据库
        QDateTime time=QDateTime::currentDateTime();
        string temp=CDBL_->getDefaDBFile();
        CDBEntity defCDBE=CDBEntity(true,"Ruanko","./data/Ruanko",time);

        finished=CDBL_->CreateDatabase(defCDBE);
        if(finished==true){
            return true;
        }else{
            return false;
        }
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

//获取数据库
CDBEntity CRKDBMSDoc::GetDBEntity(string DBName){

}

CDBEntity CRKDBMSDoc::GetDBEntity(){
    CDBEntity db;
    CDBL_->GetDatabase(db);
    allDB_.push_back(db);
}

//加载数据库
bool CRKDBMSDoc::loadDataBase(){

}

//匹配sql语句类型
bool CRKDBMSDoc::matchQSLType(QString text){
    //全小写
    smatch result;
    string temp=text.toLower().toStdString();

    if(regex_search (temp, regex("^create\\s+table"))){
        //新建表
        CTableEntity te;
        vector<CFieldEntity> fe;
        //解析sql语句构造表实体和字段实体
        STree_->creatCTableEntity(temp,DBName.toStdString(),te,fe);
        //将表信息写入（.tb）文件
        CTL_->CreateTable(DBName,te);
        //将表定义信息写入（.tdf ）文件,字段约束信息写入（.tic）文件
        for(int i=0;i<fe.size();++i){
            CTL_->AddField(DBName,te.getName(),fe[i]);
            CTL_->addFieldConstrait(DBName,te.getName(),fe[i]);
        }
        //qDebug()<<" create table ok";
    }else if(regex_search (temp, regex("drop\\s+table"))){
        //删除表
        // qDebug()<<" drop table ok";
    }else if(regex_search (temp,result,regex("alter\\s+table"))){
        vector<CFieldEntity> cfe;
        string fieldName,constraint;
        int type,param;
        string tempTableName=result[1];//修改的表信息
        //获取该表格的所有字段定义信息
        CTL_->GetField(DBName,QString::fromStdString(tempTableName),cfe);
        bool temp2=false;

        if(regex_search (temp, regex("alter\\s+table\\s+(\\w+)\\s+add\\("))){
            //添加字段
            //读取所有表信息（.db）
            vector<CTableEntity> cte;
            CTL_->GetTables(DBName,cte);
            int fieldNum=0;
            temp2=STree_->addTableField(temp,DBName.toStdString(),fieldNum,cfe);
            //修改表信息并写入文件
            temp2=alterTableEntity(cte,tempTableName,fieldNum);

            //将新增字段追加写入文件
            for(int i;i<cfe.size();++i){
                CTL_->AddField(DBName,tempTableName,cfe[i]);
            }
        }else if(regex_search (temp,regex("alter\\s+table\\s+(\\w+)\\s+modify"))){
            //修改字段
            //获取修改列的name,type,param,constraint
            temp2=STree_->modifyTableField(temp,fieldName,type,param,constraint);
            if(temp2==true){
                //查找修改CFieldEntity
                alterFieldEntity(cfe,fieldName,type,param,constraint);
                //覆写（.tdf）
                CTL_->alterField(DBName,tempTableName,cfe);
            }else{
                //发个信号报错：不存在该字段
                return false;
            }
            //            vector<CFieldEntity> cfe2;
            //            CTL_->GetField(DBName,QString::fromStdString(tempTableName),cfe2);
        }else if(regex_search (temp, regex("alter\\s+table\\s+(\\w+)\\s+rename\\("))){
            //重命名字段


        }else if(regex_search (temp, regex("alter\\s+table\\s+(\\w+)\\s+drop\\s+column\\("))){
            //删除字段

        }
        //更改表
        //qDebug()<<" alter table ok";
    }else if(regex_search (temp, regex("select\\s+"))){
        //查询表
        qDebug()<<" select table ok";
    }else if(regex_search (temp, regex("create\\s+database"))){
        //新建数据库

        qDebug()<<" create database ok";
    }else if(regex_search (temp, regex("drop\\s+database"))){
        //删除数据库
        qDebug()<<" drop database ok";
    }else if(regex_search (temp, regex("insert\\s+into\\s+"))){
        //插入记录
        //找tablename.tb
        //找.tdf找到field
    }
}

//创建表
CTableEntity* CRKDBMSDoc::CreateTable(string strName){

}

//修改字段信息
bool CRKDBMSDoc::alterFieldEntity(vector<CFieldEntity> &cfe,string& fieldName,int& type,int& param,string& constraint){
    for(int i=0;i<cfe.size();++i){
        if(cfe[i].getName()==fieldName){
            cfe[i].setType(type);
            if(type==4){
                cfe[i].setParam(param);
            }
            if(!constraint.empty()){
                cfe[i].setIntegrity(constraint);
                cfe[i].setIntegrityNum(cfe[i].getIntegrityNum()+1);
                //按理来说应该修改IntegrityType,没定义好，摆先
                //cfe[i].setIntegrityType();
            }
            return true;
        }
    }
    return false;
}

//修改表信息
bool CRKDBMSDoc::alterTableEntity(vector<CTableEntity> &cte,string name,int fieldNum){
    for(int i=0;i<cte.size();++i){
        if(cte[i].getName()==name){
            cte[i].setField_num(cte[i].getField_num()+fieldNum);
            return true;
        }
    }
    return false;
}
