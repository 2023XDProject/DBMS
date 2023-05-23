
#include<list>
#include<regex>
#include<iostream>
#include <string>
#include"Dql.h"

using namespace std;


    //����������
    SqlParser::SqlParser(string sql)
    {
        SQL = sql;
    }

    //����ѡ�����
    void  SqlParser::parseCols() {
        string regex = " (select)(.+)(from) ";
        cols = getMatchedString(regex, SQL);
    }

    //����ѡ��ı�
    void  SqlParser::parseTables() {
        string regex = "";

        if (isContains(SQL, " //s+where//s+ ")) {
            regex = " (from)(.+)(where) ";
        }
        else {
            regex = " (from)(.+)($) ";
        }

        tables = getMatchedString(regex, SQL);
    }

    //������������
    void  SqlParser::parseConditions() {
        string regex = "";

        if (isContains(SQL, " //s+where//s+ ")) {
            //  ����Where��������

            if (isContains(SQL, " group//s+by ")) {
                //  ������where��group by֮��
                regex = " (where)(.+)(group//s+by) ";
            }
            else   if (isContains(SQL, " order//s+by ")) {
                //  ������where��order by֮��
                regex = " (where)(.+)(order//s+by) ";
            }
            else {
                //  ������where���ַ���ĩβ
                regex = " (where)(.+)($) ";
            }
        }
        else {
            //  ������where�������޴�̸�𣬷��ؼ���
            return;
        }

        conditions = getMatchedString(regex, SQL);
    }

    //����GroupBy���ֶ�
    void  SqlParser::parseGroupCols() {
        string regex = "";

        if (isContains(SQL, " group//s+by ")) {
            //  ����GroupBy���з����ֶ�

            if (isContains(SQL, " order//s+by ")) {
                //  group by ����order by
                regex = " (group//s+by)(.+)(order//s+by) ";
            }
            else {
                //  group by ����order by
                regex = " (group//s+by)(.+)($) ";
            }
        }
        else {
            //  ������GroupBy������ֶ��޴�̸�𣬷��ؼ���
            return;
        }

        groupCols = getMatchedString(regex, SQL);
    }

    //����OrderBy���ֶ�
    void  SqlParser::parseOrderCols() {
        string regex = "";

        if (isContains(SQL, " order//s+by ")) {
            //  ����GroupBy���з����ֶ�
            regex = " (order//s+by)(.+)($) ";
        }
        else {
            //  ������GroupBy������ֶ��޴�̸�𣬷��ؼ���
            return;
        }

        orderCols = getMatchedString(regex, SQL);
    }

    //���ı�text���ҵ�regex�״�ƥ����ַ����������ִ�Сд
    //regex�� ������ʽ
    //text�������ҵ��ַ���
    //return  regex�״�ƥ����ַ�������δƥ�䷵�ؿ�
    string SqlParser::getMatchedString(string regex, string text) {
        std::regex pattern(regex); //������������� ����û�к��Դ�Сд

        //ƥ���ı�
        std::smatch sm;
        std::regex_match(text, sm, pattern);

        while (std::regex_search(text, sm, pattern)) {  //������һ��ƥ����
            //return  matcher.group(2);
            return sm[2]; //���صڶ�����ƥ���Ҳ���ǵڶ���������Ķ����� �����±��0��ʼ
        }

        return NULL;
        //return ""; //���������Է���null�����еĻ����ؿգ�����ʷ��ؿ�""�ǿ��Եģ���Ϊ�����жϳ��õ���string.empty()�������ж�
    }

    //��word�Ƿ���lineText�д��ڣ�֧��������ʽ
    bool SqlParser::isContains(string lineText, string word)
    {
        std::regex pattern(word);
     
        std::smatch sm;
        std::regex_match(lineText, sm, pattern);

        return std::regex_search(lineText, sm, pattern);
    }

    string SqlParser::toString() {
        //  �޷�������ԭ������
        if (cols.empty() && tables.empty() && conditions.empty() && groupCols.empty() && orderCols.empty()) {
            return  SQL;
        }

        StringBuffer sb;
        sb.append(" ԭSQLΪ " + SQL + " /n ");
        sb.append(" �������SQLΪ/n ");


        for (string str : getParsedSqlList()) {
            sb.append(str);
        }

        sb.append(" /n ");

        return  sb.toString();
    }

    //�ڷָ�������ϻس�
    string SqlParser::getAddEnterStr(string str, string splitStr) {
        std::regex p(splitStr);   //splitStr�������� pҲ����������ʽ����

        std::smatch sm;
        std::regex_match(str, sm, p);

        StringBuffer sb;

        //  ʹ��search()�������ҵ�һ��ƥ��Ķ���
        bool result = std::regex_search(str, sm, p);

        //  ʹ��ѭ���ҳ�ģʽƥ��������滻֮,�ٽ����ݼӵ�sb��
        while (result) {
           // m.appendReplacement(sb, m.group(0) + " /n      ");
            //result = m.find();
            result = std::regex_search(str, sm, p);

            string saveResult;//�����滻����ַ���  str����Ҫ���滻������
            string replacement = sm[0].str() + " /n      "; //�滻����
            std::regex_replace(std::back_inserter(saveResult), str.begin(), str.end(), p, replacement);
        }
        //�����һ��ƥ����ʣ���ַ����ӵ�sb��
        //m.appendTail(sb);
        string lastString = sm.suffix(); //��ȡƥ���ʣ����ַ�
        sb.append(lastString);  //��ʣ���ַ�׷�ӵ�sbĩβ

        return  FourSpace + sb.toString();
    }

    //ȡ�ý�����SQL�ַ����б�
    list < string > SqlParser::getParsedSqlList() {
        list < string >  sqlList;

        //  �޷�������ԭ������
        if (cols.empty() && tables.empty() && conditions.empty() && groupCols.empty() && orderCols.empty()) {
            sqlList.push_back(SQL);
            return  sqlList;
        }

        if (! cols.empty()) {
            sqlList.push_back(" select/n ");
            if (ISSINGLELINE) {
                sqlList.push_back(getAddEnterStr(cols, Comma));
            }
            else {
                sqlList.push_back(FourSpace + cols);
            }
        }

        if (! tables.empty()) {
            sqlList.push_back("  /nfrom/n ");

            if (ISSINGLELINE) {
                sqlList.push_back(getAddEnterStr(tables, Comma));
            }
            else {
                sqlList.push_back(FourSpace + tables);
            }
        }

        if (! conditions.empty()) {
            sqlList.push_back("  /nwhere/n ");

            if (ISSINGLELINE) {
                sqlList.push_back(getAddEnterStr(conditions, " (and|or) "));
            }
            else {
                sqlList.push_back(FourSpace + conditions);
            }
        }

        if (! groupCols.empty()) {
            sqlList.push_back("  /ngroup by/n ");

            if (ISSINGLELINE) {
                sqlList.push_back(getAddEnterStr(groupCols, Comma));
            }
            else {
                sqlList.push_back(FourSpace + groupCols);
            }
        }

        if (! orderCols.empty()) {
            sqlList.push_back("  /norder by/n ");

            if (ISSINGLELINE) {
                sqlList.push_back(getAddEnterStr(orderCols, Comma));
            }
            else {
                sqlList.push_back(FourSpace + orderCols);
            }
        }

        return  sqlList;
    }

    //�����Ƿ�����ʾ���ֶΣ�������
    void SqlParser::setSingleLine(bool isSingleLine) {
        ISSINGLELINE = isSingleLine;
    }

    //����
     void  main() {
         list < string >  ls;
        ls.push_back(" select * from dual ");
        ls.push_back(" SELECT * frOm dual ");
        ls.push_back(" Select C1,c2 From tb ");
        ls.push_back(" select c1,c2 from tb ");
        ls.push_back(" select count(*) from t1 ");
        ls.push_back(" select c1,c2,c3 from t1 where condi1=1  ");
        ls.push_back(" Select c1,c2,c3 From t1 Where condi1=1  ");
        ls.push_back(" select c1,c2,c3 from t1,t2 where condi3=3 or condi4=5 order   by o1,o2 ");
        ls.push_back(" Select c1,c2,c3 from t1,t2 Where condi3=3 or condi4=5 Order   by o1,o2 ");
        ls.push_back(" select c1,c2,c3 from t1,t2,t3 where condi1=5 and condi6=6 or condi7=7 group  by g1,g2 ");
        ls.push_back(" Select c1,c2,c3 From t1,t2,t3 Where condi1=5 and condi6=6 or condi7=7 Group  by g1,g2 ");
        ls.push_back(" Select c1,c2,c3 From t1,t2,t3 Where condi1=5 and condi6=6 or condi7=7 Group  by g1,g2,g3 order  by g2,g3 ");

      /*
      * 
      for (string sql : ls) {
            
        }

      */  
    }
