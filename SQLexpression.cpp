#include<fstream>
#include "SQLexpression.h"

using namespace std;
using namespace boost;

//构造器
SqlEx::SqlEx(string ex) { // .h中   string Ex;
	Ex = ex;
}

//解析器
SqlEx::~SqlEx() {

}

bool SqlEx::check() {
	transform(Ex.begin(), Ex.end(), Ex.begin(), towlower); //将命令字符串改写成小写并且就存到原来的字符串数组里
	Ex = sql(Ex);  //string sql(string str);
	Ex = Ex + "END";

	string sqlupdate = "update\.+set\.+(where\.+)?END";
	string sqldelete = "delete\.+from\.+where\.+END";
	string sqlinsert = "insert\.+into\.+(\(\.+/)\.*)?values\(.+\)END";
	string sqlcreate = "create table\.+\\(\.+\\)END";
	string sqlselect = "select\.+from\.+(where\.+)?((group by)?|(order by)?|(having)?)END";
	string sqldrop = "drop table\.+END";
	
	//需要boost库
	regex Pupdate(sqlupdate);
	regex Pdelete(sqldelete);
	regex Pinsert(sqlinsert);
	regex Pcreate(sqlcreate);
	regex Pselect(sqlselect);
	regex Pdrop(sqldrop);

	//把命令进行比对
    if (regex_match(Ex, Pupdate)) {
        return  ForUpdate();
    }
    else if (regex_match(Ex, Pdelete)) {
        return  ForDelete();
    }
    else if (regex_match(Ex, Pinsert)) {
        return ForInsert();
    }
    else if (regex_match(Ex, Pcreate)) {
        return ForCreate();
    }
    else if (regex_match(Ex, Pselect)) {
        return ForSelect();
    }
    else if (regex_match(Ex, Pdrop)) {
        return ForDrop();
    }
    else {
        cout << "请检查你的语句是否正确，不支持该语句！！" << endl;
        return false;
    }
    return true;
}

bool SqlEx::ForUpdate(){
    vector<vector<string>> Vupdate;
    string str[3];

    smatch sm[3];  //也需要boost库 容器类，保存在string中的搜索结果
    regex re1("(?<=update )\.+(?= set)");
    regex re2("((?<=set )\.+(?= where))|((?<=set )\.+(?=END))");
    regex re3("(?<=where )\.+(?=END)");
    
    if (regex_search(Ex, sm[0], re1)) {  //regex_search 寻找第一个与正则表达式匹配的子序列
        vector<string>update1;  //用于暂时存放匹配的字符
        str[0] = sm[0].str();  //.str() 获得匹配的字符
        update1.push_back(str[0]); //吧获得匹配的字符添加到vector尾部
        cout << "update:" << endl;
        cout << str[0] << endl;
        cout << endl;
        Vupdate.push_back(update1);
    }
    else {
        cout << "请检查update与set语句间是否存在错误!!" << endl;
        return false;
    }
    if (regex_search(Ex, sm[1], re2)) {
        vector<string>update2;
        str[1] = sm[1].str();
        update2.push_back(str[1]);
        cout << "set:" << endl;
        cout << str[1] << endl;
        cout << endl;
        Vupdate.push_back(update2);
    }
    else {
        cout << "请检查set字段是否存在错误！！" << endl;

        return false;
    }

    if (regex_search(Ex, sm[2], re3)) {
        vector<string>update3;
        cout << "where:" << endl;
        str[2] = sm[2].str();
        regex rr("(\.+?and )|(\.+?or )");  //匹配以任意字符结尾并且包含and或者or的字符串
        smatch rrsm;
        string::const_iterator st = str[2].begin();
        string::const_iterator en = str[2].end();
        bool flag = false;
        while (regex_search(st, en, rrsm, rr)) { //如果能找到符合rr规则的字符串
            flag = true;
            cout << rrsm.str() << endl;
            update3.push_back(rrsm.str());  //就把符合的字符串输出
            st = rrsm[0].second;
        }
        if (flag) {
            regex_search(st, en, rrsm, regex("\.+"));
            cout << rrsm.str() << endl;
            update3.push_back(rrsm.str());
        }
        else {  //如果找不到 那么吧原本的符合要求的表达式输出
            cout << str[2] << endl;
            update3.push_back(str[2]);
        }
        Vupdate.push_back(update3);
    }
    result = Vupdate;
    return true;
}  //bool SqlEx::ForUpdate()  END

bool SqlEx::ForDelete() {
    vector<vector<string>> Vdelete;

    regex re1("(?<=delete from )\.+(?=where )");
    regex re2("(?<=where )\.+(?=END)");

    string dstr[2];
    smatch dsm[2];

    string::const_iterator st = Ex.begin();
    string::const_iterator en = Ex.end();

    if (regex_search(Ex, dsm[0], re1)) {
        vector<string>vdelete1;
        dstr[0] = dsm[0].str();
        vdelete1.push_back(dstr[0]);
        cout << "delete from:" << endl;
        cout << dstr[0] << endl;
        cout << endl;
        Vdelete.push_back(vdelete1);
    }
    else {
        cout << "检查delete from与where之间是否存在错误" << endl;
    }
    if (regex_search(Ex, dsm[1], re2)) {
        vector<string>vdelete1;
        cout << "where:" << endl;

        dstr[1] = dsm[1].str();
        regex rr("(\.+?and )|(\.+?or )");
        smatch rrsm;
        string::const_iterator st = dstr[1].begin();
        string::const_iterator en = dstr[1].end();
        bool flag = false;
        while (regex_search(st, en, rrsm, rr)) {
            flag = true;
            cout << rrsm.str() << endl;
            vdelete1.push_back(rrsm.str());
            st = rrsm[0].second;
        }
        if (flag) {
            regex_search(st, en, rrsm, regex("\.+"));
            cout << rrsm.str() << endl;
            vdelete1.push_back(rrsm.str());
        }
        else {
            cout << dstr[1] << endl;
            vdelete1.push_back(dstr[1]);
        }
        Vdelete.push_back(vdelete1);
    }
    else {
        cout << "检查where语句后是否存在错误！！" << endl;
    }
    result = Vdelete;
    return true;
}  //bool SqlEx::ForDelete() END

bool SqlEx::ForInsert() {
    vector<vector<string>> Vinsert;

    regex re1("(?<=insert into )\.+(?=values)");
    regex re2("(?<=values\\()\.+(?=\\)END)");

    string istr[2];
    smatch ism[2];

    if (regex_search(Ex, ism[0], re1)) {
        vector<string>vinsert1;
        istr[0] = ism[0].str();

        regex rr("(?<=\\()\.+(?=\\))");
        smatch rsm;
        cout << "Insert into:" << endl;
        if (regex_search(istr[0], rsm, rr)) {
            regex rr2("\.+?(?=\\()");
            smatch rsm2;
            regex_search(istr[0], rsm2, rr2);
            cout << rsm2.str() << endl;
            cout << endl;
            vinsert1.push_back(rsm2.str());

            string rstr = rsm.str();

            smatch rsm1;
            regex rr1("(?<=')\.+?(?=')");
            string::const_iterator st = rstr.begin();
            string::const_iterator en = rstr.end();

            while (regex_search(st, en, rsm1, rr1)) {
                if (rsm1.str() != ",") {
                    cout << rsm1.str() << endl;
                    vinsert1.push_back(rsm1.str());
                }
                st = rsm1[0].second;
            }
        }
        else {
            vinsert1.push_back(istr[0]);
            cout << istr[0] << endl;
        }
        Vinsert.push_back(vinsert1);
        cout << endl;
    }
    else {
        cout << "检查insert into语句后是否存在错误！！！" << endl;
        return false;
    }
    if (regex_search(Ex, ism[1], re2)) {
        vector<string>vinsert2;
        istr[1] = ism[1].str();
        cout << "Values:" << endl;
        smatch rsm3;
        regex rr3("(?<=')\.+?(?=')");
        string::const_iterator st = istr[1].begin();
        string::const_iterator en = istr[1].end();

        while (regex_search(st, en, rsm3, rr3)) {
            if (rsm3.str() != ",") {
                cout << rsm3.str() << endl;
                vinsert2.push_back(rsm3.str());
            }
            st = rsm3[0].second;
        }
        Vinsert.push_back(vinsert2);
    }
    else {
        cout << "检查values语句后是否存在错误！！！" << endl;
        return false;
    }
    result = Vinsert;
    return true;
}  //bool SqlEx::ForInsert() END

bool SqlEx::ForCreate() {
    vector<vector<string>> Create;
    regex re1("(?<=create table )\.+?(?=\\()");
    regex re2("(?<=\\()\.+(?=\\))");
    smatch csm1;
    smatch csm2;
    string cstr[2];

    if (regex_search(Ex, csm1, re1)) {
        vector<string>create1;
        cstr[0] = csm1.str();
        cout << "create table:" << endl;
        cout << cstr[0] << endl;
        cout << endl;
        create1.push_back(cstr[0]);
        Create.push_back(create1);
    }
    else {
        cout << "检查create table语句后是否存在错误！！！" << endl;
        return false;
    }
    if (regex_search(Ex, csm2, re2)) {
        cstr[1] = csm2.str();

        regex rer("(\.+?,)|(\.+)");
        smatch rsm;
        string::const_iterator st = cstr[1].begin();
        string::const_iterator en = cstr[1].end();

        while (regex_search(st, en, rsm, rer)) {
            string ss = rsm.str();
            bool isname = true; // 是表名
            bool isatt = false; //是属性名
            bool iscap = false; //是属性“长度” eg. varchar（2）
            string name = "";
            string attribute = "";
            string capacity = "";
            vector<string> create1;
            for (int i = 0; i < ss.length(); i++) {
                if (isname == true && ss[i] != ' ') {
                    name = name + ss[i];
                }
                if (isname == true && name != "" && ss[i] == ' ') {
                    isname = false;
                    isatt = true;
                    cout << name << endl;
                    create1.push_back(name);
                }
                if (isatt == true && ss[i] != ' ' && ss[i] != '(') {
                    attribute = attribute + ss[i];
                }
                if (isatt == true && attribute != "" && ss[i] == '(') {
                    isatt = false;
                    iscap = true;
                    cout << attribute << endl;
                    create1.push_back(attribute);
                }
                if (iscap == true && ss[i] != ' ' && ss[i] != '(' && ss[i] != ')') {
                    capacity = capacity + ss[i];
                }
                if (iscap == true && ss[i] == ')' && capacity != "") {
                    iscap = false;
                    cout << capacity << endl;
                    create1.push_back(capacity);
                }
            }
            Create.push_back(create1);
            cout << endl;
            st = rsm[0].second;
        }
    }
    else {
        cout << "检查括号中语句是否存在错误！！！" << endl;
        return false;
    }
    result = Create;
    return true;
}  //bool SqlEx::ForCreate() END

bool SqlEx::ForSelect() {
    vector<vector<string>> Select;
    regex reg1("(?<=select )\.+?(?= from)");
    regex reg2("((?<=from )\.+?(?= where))|((?<=from )\.+?(?=END))");
    regex reg3("(?<=where )\.+?(?=END)");

    smatch ssm[3];

    if (regex_search(Ex, ssm[0], reg1)) {
        cout << "select:" << endl;
        vector<string> attribute;
        string stt = "";
        string ss = ssm[0].str();
        for (int i = 0; i < ss.size(); i++) {
            if (ss[i] != ' ' && ss[i] != ',') {
                stt = stt + ss[i];
            }
            if ((ss[i] == ',' || i == ss.size() - 1) && stt != "") {
                cout << stt << endl;
                attribute.push_back(stt);
                stt = "";
            }
        }
        Select.push_back(attribute);
    }
    else {
        cout << "检查select from语句后是否存在错误！！！" << endl;
        return false;
    }
    if (regex_search(Ex, ssm[1], reg2)) {
        cout << "from:" << endl;
        vector<string> tablename;
        string stt = "";
        string ss = ssm[1].str();
        for (int i = 0; i < ss.size(); i++) {
            if (ss[i] != ' ' && ss[i] != ',') {
                stt = stt + ss[i];
            }
            if ((ss[i] == ',' || i == ss.size() - 1) && stt != "") {
                cout << stt << endl;
                tablename.push_back(stt);
                stt = "";
            }
        }
        Select.push_back(tablename);
    }
    else {
        cout << "检查from语句后是否存在错误！！！" << endl;
        return false;
    }
    if (regex_search(Ex, ssm[2], reg3)) {
        vector<string>condition;
        cout << "where:" << endl;
        string sst = ssm[2].str();
        regex sr("(\.+?and )|(\.+?or )");
        smatch srsm;
        string::const_iterator st = sst.begin();
        string::const_iterator en = sst.end();
        bool flag = false;
        while (regex_search(st, en, srsm, sr)) {
            flag = true;
            cout << srsm.str() << endl;
            condition.push_back(srsm.str());
            st = srsm[0].second;
        }
        if (flag) {
            regex_search(st, en, srsm, regex("\.+"));
            cout << srsm.str() << endl;
            condition.push_back(srsm.str());
        }
        else {
            cout << sst << endl;
            condition.push_back(sst);
        }
        Select.push_back(condition);
    }
    result = Select;
    return true;
} //bool SqlEx::ForSelect() END

bool SqlEx::ForDrop() {
    vector<vector<string>>drop;
    regex dre("(?<=drop table )\\w+(?=END)");
    smatch dsm;
    cout << "drop table:" << endl;

    if (regex_search(Ex, dsm, dre)) {
        cout << dsm.str() << endl;
        vector<string> name;
        name.push_back(dsm.str());
        drop.push_back(name);
    }
    else {
        cout << "检查drop语句后是否存在错误！！！" << endl;
        return false;
    }

    result = drop;
    return true;
}  //bool SqlEx::ForDrop() END

vector<vector<string>>SqlEx::getResult() {
    return result;
}

string SqlEx::sql(string sql)//语句预处理
{
    const int count = sql.size();
    string b = "";
    int flag = 0;//标记
    int n = 0;
    for (int i = 0; i < count; i++)
    {
        if (sql[i] != ' ')
        {
            b += sql[i];
            n++;
            flag = 1;
        }
        else if (sql[i] == ' ' && flag == 1)
        {
            b += sql[i];
            n++;
            flag = 0;
        }
    }
    if (b[n - 1] == ' ')
        b.erase(n - 1, 1);
    return b;
}











}


