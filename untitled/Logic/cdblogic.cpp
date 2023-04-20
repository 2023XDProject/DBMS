#include "cdblogic.h"

CDBLogic::CDBLogic():CFL_(new CFileLogic()),CDBD_(new CDBDao()),
    CDBE_(new CDBEntity()),CFH_(new CFileHelper())
{}

CDBLogic::~CDBLogic(){
    delete CFL_;
    delete CDBD_;
    delete  CDBE_;
    delete CFH_;
}

//创建数据库描述文件
bool CDBLogic::createRuankoFile(){
    //获取绝对路径
    string name=CFL_->GetDBFile();
    QString tempName=CFL_->GetQStringPath(name);
    bool temp=CFH_->CreateDBFile(tempName);
    qDebug()<<tempName;
    //qDebug()<<temp;
    if(temp==false){
        return false;
    }else{
        return true;
    }
}

//创建数据库
bool CDBLogic::CreateDatabase(CDBEntity &db){
    //判断数据库是否已经存在
    string tempPath="";
    tempPath=CFL_->GetDBFolder(db.getBaseName());
    QString tempQPath=CFL_->GetQStringPath(tempPath);

    bool temp =CFH_->IsValidDirector(tempQPath);

    qDebug()<<temp<<" "<<tempQPath;
    //数据库已存在
    if(temp==true){
        return false;
    }else{
        temp=CFH_->CreateDirector(tempQPath);//建立数据库
        if(temp==false){
            return false;
        }else{
            //将数据库信息写入文件
            tempPath=CFL_->GetDBFile();
            tempQPath=CFL_->GetQStringPath(tempPath);
            CDBD_->CreateDB(tempQPath,db);
            //将数据库信息写入当前数据库文件
            tempPath=CFL_->GetNowDBFile();
            tempQPath=CFL_->GetQStringPath(tempPath);
            CDBD_->CreateDB(tempQPath,db,false);
            //建立表描述文件
            tempPath=CFL_->GetTableFile(db.getBaseName());
            tempQPath=CFL_->GetQStringPath(tempPath);
            CFH_->CreateDBFile(tempQPath);
            /*
             * TODO:还要再建立一个数据库日志文件，我摆了
             */
            return true;
        }
    }
}
//查询数据库
bool CDBLogic::GetDatabase(CDBEntity &db){

}

//获取数据库描述文件绝对路径
string CDBLogic::getDefaDBFile(){
    return CFL_->GetDBFile();
}

//获取数据库文件夹路径
string CDBLogic::getDBFolder(const string strDBName){
    return CFL_->GetDBFolder(strDBName);
}




