#include <string>
#include <cctype>
#include "crecordlogic.h"
//#include "stdafx.h"
//#include "RecordLogic.h"
//#include "RecordDAO.h"
//#include "FieldDAO.h"
//#include "Global.h"
//#include "SystemLogic.h"

CRecordLogic::CRecordLogic(string dbname,string tableName)
{
    this->tdfPath=DEFAULT_ROOT+string("/")+dbname+string("/")+tableName+string(".tdf");
    this->trdPath=DEFAULT_ROOT+string("/")+dbname+string("/")+tableName+string(".trd");
    this->dbName = dbname;
    this->tbName = tableName;
}


CRecordLogic::~CRecordLogic(void)
{
}




int CRecordLogic::IntegrityVerify(string &val,CFieldEntity &field)
{
    //MessageBox(NULL,CUtil::IntegerToString(field.GetType())+" "+val,L"",MB_OK);
    //验证基本的完整性
    switch (field.GetType())
    {
    case DB_INTEGER:
    {
        if (CUtil::OnlyHaveNumber(val))
        {
            int iVal=CUtil::StringToInteger(val);

            if (field.GetMax()!=-1)
            {
                if(iVal>field.GetMax())
                    return INTEGRITY_OVER_RANGE;

            }

            if (field.GetMin()!=-1)
            {
                if(iVal<field.GetMin())
                    return INTEGRITY_OVER_RANGE;

            }
        }
        else
        {
            return INTEGRITY_ERROR_TYPE;
        }

        break;
    }
    case DB_BOOL:
    {
        if(val!="true" && val!="false")
            return INTEGRITY_ERROR_TYPE;
        break;
    }
    case DB_VARCHAR:
    {
        Varchar varchars(val);
        if (!CUtil::ValidStr(varchars.GetValue()))
            return INTEGRITY_ERROR_CHAR;

        if (varchars.GetLength()>field.GetLength())
        {
            return INTEGRITY_TOO_LONG;
        }
        break;
    }
    case DB_DATETIME:
    {
        if (val != val.SpanIncluding(L"1234567890-") || val.GetLength()!=10)
            return INTEGRITY_ERROR_TYPE;
        else
        {
            //2014-09-02
            for (int i = 0; i < 10; i++)
            {
                if (i!=4&&i!=7)
                {
                    if(val[i]>'9'||val[i]<'0')
                        return INTEGRITY_ERROR_DATETYPE;
                }
            }

            if (val[4]!='-'||val[7]!='-')
                return INTEGRITY_ERROR_DATETYPE;
            string date = val;
            vector<string> ymd=CUtil::StrSplit(date,CString("-"));
            int m = CUtil::StringToInteger(ymd[1]);
            int d = CUtil::StringToInteger(ymd[2]);
            if(m>12 || (m==2&&d>28))
                return INTEGRITY_ERROR_DATETYPE;

            if( ((m==1||m==3||m==5||m==7||m==8||m==10||m==12)&&d>31)||
                ((m==2||m==4||m==6||m==9||m==11)&&d>30))
                return INTEGRITY_ERROR_DATETYPE;
        }
        break;
    }
    case DB_DOUBLE:
    {
        if (CUtil::OnlyHaveNumberAndDot(val))
        {
            double iVal=CUtil::StringToDouble(val);
            if (field.GetMax()!=-1)
            {
                if(iVal>field.GetMax()){
                    return INTEGRITY_OVER_RANGE;
                }
            }

            if (field.GetMin()!=-1)
            {
                if(iVal<field.GetMin()){
                    return INTEGRITY_OVER_RANGE;
                }
            }
        }
        else
            return INTEGRITY_ERROR_TYPE;

        break;
    }
    default:
        break;
    }

    //验证主键
    if (field.GetIsPK()==YES)
    {
        if (this->IsNull(val)==YES||this->IsUnique(val,field.GetName())==NO)
        {
            return INTEGRITY_NOT_PK;
        }
    }
    else
    {
        //验证非空
        if (field.GetIsNull()==NO)
        {
            if (this->IsNull(val)==YES)
            {
                return INTEGRITY_NULL_VALUE;
            }
        }
        //验证唯一
        if (field.GetIsUnique()==YES)
        {
            if (this->IsUnique(val,field.GetName())==NO)
            {
                return INTEGRITY_NOT_UNIQUE;
            }
        }
    }


    return INTEGRITY_OK;
}

//完整性约束
int CRecordLogic::IntegrityVerify(CRecordEntity &record,CFieldEntity &field)
{
    string val=record.GetValue(field.GetName());
    return this->IntegrityVerify(val,field);
}

//判断是否为空
int CRecordLogic::IsNull(string &value)
{
    if (value==string(""))
    {
        return YES;
    }
    else
    {
        return NO;
    }
}

/***********************************
* 判断是否唯一
************************************/
int CRecordLogic::IsUnique(string &value,string &fieldName)
{
    vector<CRecordEntity> list=CRecordDAO::ReadRecordList(trdPath,CFieldDAO::ReadFieldList(this->tdfPath));
    for (vector<CRecordEntity>::iterator ite=list.begin(); ite != list.end(); ++ite)
    {
        if (ite->GetValue(fieldName)==value)
        {
            return NO;
        }
    }
    return YES;
}

//增加记录
int CRecordLogic::AddRecord(CRecordEntity &record, vector<CFieldEntity> &fieldList)
{
    //vector<CFieldEntity> flist=CFieldDAO::ReadFieldList(tdfPath);
    //for (vector<CFieldEntity>::iterator ite=flist.begin();ite!=flist.end();++ite)
    //{
    //	int res=CRecordLogic::IntegrityVerify(record,*ite);
    //	if(res!=INTEGRITY_OK)
    //		return res;
    //}
    int count = CRecordDAO::GetRcdCounter(this->trdPath);
    record.SetId(++count);

    if (!CRecordDAO::WriteAnRecord(record, trdPath, fieldList))
        return ADD_ERROR;

    if(!CRecordDAO::SaveRcdCounter(this->trdPath,count))
        return SAVE_COUNTER_ERROR;

    CSystemLogic sysLogic;
    sysLogic.WriteLog(string("add an record.")+string("database: ")+dbName+string(" table: ")+tbName);

    return YES;

}

//删除记录
int CRecordLogic::DeleteRecord(int id)
{
    if (CRecordDAO::DeleteRecord(id, trdPath))
    {
        CSystemLogic sysLogic;
        sysLogic.WriteLog(string("deleted an record.")+string("database: ")+dbName+string(" table: ")+tbName);
        return YES;
    }
    else
        return DELETE_ERROR;
}

//删除所有记录
int CRecordLogic::DeleteAllRecord()
{
    if(CRecordDAO::DeleteAllRecord(trdPath))
    {
        CSystemLogic sysLogic;
        sysLogic.WriteLog(string("deleted all record.")+string("database: ")+dbName+string(" table: ")+tbName);
        return YES;
    }
    else
        return DELETE_ERROR;
}


//修改记录
int CRecordLogic::ModifyRecord(CRecordEntity &record)
{
    if(CRecordDAO::ModifyRecord(record,trdPath,tdfPath))
    {
        CSystemLogic sysLogic;
        sysLogic.WriteLog(string("modified record,record id:")+CUtil::IntegerToString(record.GetId())
                        +string("database: ")+dbName+string(" table: ")+tbName);
        return YES;
    }
    else
        return MODIFY_ERROR;
}


vector<CRecordEntity> CRecordLogic::GetRecordList()
{
    return CRecordDAO::ReadRecordList(trdPath,CFieldDAO::ReadFieldList(this->tdfPath));
}


vector<CRecordEntity> CRecordLogic::ConditionQuery(vector<CFieldEntity> fieldList,
                                                   vector<CString> compare,
                                                   vector<CString> values)
{
    vector<CRecordEntity> rcdList = CRecordDAO::ReadRecordList(trdPath,fieldList);
    vector<CRecordEntity> res;
    for (vector<CRecordEntity>::iterator ite=rcdList.begin();ite!=rcdList.end();++ite)
    {
        bool condition = true;
        for (int i = 0; i < compare.size(); i++)
        {
            if(values[i]!=L"")
            {
                if (compare[i]==L"="&&ite->GetValue(fieldList[i].GetName())!=values[i])
                    { condition = false; break; }
                else if(compare[i]==L">"&&ite->GetValue(fieldList[i].GetName())<=values[i])
                    { condition = false; break; }
                else if(compare[i]==L"<"&&ite->GetValue(fieldList[i].GetName())>=values[i])
                    { condition = false; break; }
            }
        }
        if (condition)
            res.push_back(*ite);
    }
    return res;
}

