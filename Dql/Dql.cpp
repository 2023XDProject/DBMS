
#include<list>
#include<regex>
#include<iostream>
#include <string>
#include"Dql.h"

using namespace std;


    //构造器函数
    SqlParser::SqlParser(string sql)
    {
        SQL = sql;
    }

    //解析选择的列
    void  SqlParser::parseCols() {
        string regex = " (select)(.+)(from) ";
        cols = getMatchedString(regex, SQL);
    }

    //解析选择的表
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

    //解析查找条件
    void  SqlParser::parseConditions() {
        string regex = "";

        if (isContains(SQL, " //s+where//s+ ")) {
            //  包括Where，有条件

            if (isContains(SQL, " group//s+by ")) {
                //  条件在where和group by之间
                regex = " (where)(.+)(group//s+by) ";
            }
            else   if (isContains(SQL, " order//s+by ")) {
                //  条件在where和order by之间
                regex = " (where)(.+)(order//s+by) ";
            }
            else {
                //  条件在where到字符串末尾
                regex = " (where)(.+)($) ";
            }
        }
        else {
            //  不包括where则条件无从谈起，返回即可
            return;
        }

        conditions = getMatchedString(regex, SQL);
    }

    //解析GroupBy的字段
    void  SqlParser::parseGroupCols() {
        string regex = "";

        if (isContains(SQL, " group//s+by ")) {
            //  包括GroupBy，有分组字段

            if (isContains(SQL, " order//s+by ")) {
                //  group by 后有order by
                regex = " (group//s+by)(.+)(order//s+by) ";
            }
            else {
                //  group by 后无order by
                regex = " (group//s+by)(.+)($) ";
            }
        }
        else {
            //  不包括GroupBy则分组字段无从谈起，返回即可
            return;
        }

        groupCols = getMatchedString(regex, SQL);
    }

    //解析OrderBy的字段
    void  SqlParser::parseOrderCols() {
        string regex = "";

        if (isContains(SQL, " order//s+by ")) {
            //  包括GroupBy，有分组字段
            regex = " (order//s+by)(.+)($) ";
        }
        else {
            //  不包括GroupBy则分组字段无从谈起，返回即可
            return;
        }

        orderCols = getMatchedString(regex, SQL);
    }

    //从文本text中找到regex首次匹配的字符串，不区分大小写
    //regex： 正则表达式
    //text：欲查找的字符串
    //return  regex首次匹配的字符串，如未匹配返回空
    string SqlParser::getMatchedString(string regex, string text) {
        std::regex pattern(regex); //创建正则表达对象 但是没有忽略大小写

        //匹配文本
        std::smatch sm;
        std::regex_match(text, sm, pattern);

        while (std::regex_search(text, sm, pattern)) {  //查找下一个匹配项
            //return  matcher.group(2);
            return sm[2]; //返回第二个子匹配项（也就是第二个括号里的东西） 数组下标从0开始
        }

        return NULL;
        //return ""; //这里先试试返回null，不行的话返回空，大概率返回空""是可以的，因为条件判断出用的是string.empty()方法做判断
    }

    //看word是否在lineText中存在，支持正则表达式
    bool SqlParser::isContains(string lineText, string word)
    {
        std::regex pattern(word);
     
        std::smatch sm;
        std::regex_match(lineText, sm, pattern);

        return std::regex_search(lineText, sm, pattern);
    }

    string SqlParser::toString() {
        //  无法解析则原样返回
        if (cols.empty() && tables.empty() && conditions.empty() && groupCols.empty() && orderCols.empty()) {
            return  SQL;
        }

        StringBuffer sb;
        sb.append(" 原SQL为 " + SQL + " /n ");
        sb.append(" 解析后的SQL为/n ");


        for (string str : getParsedSqlList()) {
            sb.append(str);
        }

        sb.append(" /n ");

        return  sb.toString();
    }

    //在分隔符后加上回车
    string SqlParser::getAddEnterStr(string str, string splitStr) {
        std::regex p(splitStr);   //splitStr正则条件 p也就是正则表达式对象

        std::smatch sm;
        std::regex_match(str, sm, p);

        StringBuffer sb;

        //  使用search()方法查找第一个匹配的对象
        bool result = std::regex_search(str, sm, p);

        //  使用循环找出模式匹配的内容替换之,再将内容加到sb里
        while (result) {
           // m.appendReplacement(sb, m.group(0) + " /n      ");
            //result = m.find();
            result = std::regex_search(str, sm, p);

            string saveResult;//保存替换后的字符串  str就是要被替换的内容
            string replacement = sm[0].str() + " /n      "; //替换内容
            std::regex_replace(std::back_inserter(saveResult), str.begin(), str.end(), p, replacement);
        }
        //将最后一次匹配后的剩余字符串加到sb里
        //m.appendTail(sb);
        string lastString = sm.suffix(); //获取匹配后剩余的字符
        sb.append(lastString);  //将剩余字符追加到sb末尾

        return  FourSpace + sb.toString();
    }

    //取得解析的SQL字符串列表
    list < string > SqlParser::getParsedSqlList() {
        list < string >  sqlList;

        //  无法解析则原样返回
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

    //设置是否单行显示表，字段，条件等
    void SqlParser::setSingleLine(bool isSingleLine) {
        ISSINGLELINE = isSingleLine;
    }

    //测试
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
