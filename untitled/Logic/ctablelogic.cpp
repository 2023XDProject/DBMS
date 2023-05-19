#include "ctablelogic.h"

CTableLogic::CTableLogic():CTD_(new CTableDao()),CFL_(new CFileLogic()),
    CFH_(new CFileHelper())
{}

CTableLogic::~CTableLogic(){
    delete CTD_;
    delete CFL_;
    delete CFH_;
}

/*
 * 创建表
 * @param:QString strDBName:表所在的数据库名称
 *        CTableEntity &te:表信息实体
 */
bool CTableLogic::CreateTable(const QString strDBName,CTableEntity &te){
    //向表描述文件写入表信息
    QString temp=CFL_->GetQStringPath(CFL_->GetTableFile(strDBName.toStdString()));
    //创建（.tdf）文件，写入字段信息
    CTD_->Create(temp,te);
}

//添加字段
bool CTableLogic::AddField(const QString strDBName,string tableName,CFieldEntity &fe){
    QString temp=CFL_->GetQStringPath(CFL_->GetTbDefineFile(strDBName.toStdString(),tableName));
    CTD_->AddField(temp,fe);
}

//添加字段约束
bool CTableLogic::addFieldConstrait(const QString strDBName,const string tableName,CFieldEntity &fe){
    QString temp=CFL_->GetQStringPath(CFL_->GetTbConstraitFile(strDBName.toStdString(),tableName));
    CTD_->AddFieldConstrain(temp,fe);
}

//获取字段信息
bool CTableLogic::GetField(const QString strDBName,const QString tableName,vector<CFieldEntity> &fe){
    string temp=CFL_->GetTbDefineFile(strDBName.toStdString(),tableName.toStdString());
    CTD_->GetFields(QString::fromStdString(temp),fe);
}

//写入修改后的字段
bool CTableLogic::alterField(const QString strDBName,const string tableName,vector<CFieldEntity> &cfe){
    string temp=CFL_->GetTbDefineFile(strDBName.toStdString(),tableName);
    CTD_->writeField(QString::fromStdString(temp),cfe);
}

//获取表信息
bool CTableLogic::GetTables(const QString strDBName,vector<CTableEntity> &cte){
    string temp=CFL_->GetTableFile(strDBName.toStdString());
    CTD_->GetTables(QString::fromStdString(temp),cte);
}

//覆写表信息
bool CTableLogic::writeTables(const QString strDBName,vector<CTableEntity> &cte){
    string temp=CFL_->GetTableFile(strDBName.toStdString());
    CTD_->writeTable(QString::fromStdString(temp),cte);
}


//删除表
bool CTableLogic::dropTable(const QString strDBName,const string tableName){
    //获取表定义文件(.trf)，表记录文件(.trd)，完整性描述文件(.tic)，索引描述文件（to do)绝对路径
    string TbDFileName;
    bool isExist=true;

    //获取这几个文件的绝对路径,删除文件
    //表定义文件(.trf)
    TbDFileName=CFL_->GetTbDefineFile(strDBName.toStdString(),tableName);
    isExist=CFH_->IsValidFile(QString::fromStdString(TbDFileName));
    if(isExist==false){
        //发信号：表不存在
        return false;
    }else{
        isExist=CTD_->dropTable(QString::fromStdString(TbDFileName));
        if(isExist==false){
            //发信号：文件(.trf)删除失败
            return false;
        }
    }

    //表记录文件
    TbDFileName=CFL_->GetTbRecordFile(strDBName.toStdString(),tableName);
    isExist=CFH_->IsValidFile(QString::fromStdString(TbDFileName));
    if(isExist==false){
        //发信号：表不存在
        return false;
    }else{
        isExist=CTD_->dropTable(QString::fromStdString(TbDFileName));
        if(isExist==false){
            //发信号：文件(.tdf)删除失败
            return false;
        }
    }

    TbDFileName=CFL_->GetTbConstraitFile(strDBName.toStdString(),tableName);
    isExist=CFH_->IsValidFile(QString::fromStdString(TbDFileName));
    if(isExist==false){
        //发信号：表不存在
        return false;
    }else{
        isExist=CTD_->dropTable(QString::fromStdString(TbDFileName));
        if(isExist==false){
            //发信号：文件(.tic)删除失败
            return false;
        }
    }

    /*
     * TODO:删除索引文件
     */
}
