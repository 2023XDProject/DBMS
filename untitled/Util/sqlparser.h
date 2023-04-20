#ifndef SQLPARSER_H
#define SQLPARSER_H
#include <string>
#include <regex>
using namespace std;

class SQLparser
{
public:
    SQLparser(string text);

private:
    string text;
    const string operators = "+-*/%=&|<>!";
    const string singleword = "(),.;";

//    unordered_map<string,int> keyword{
//        {"create",},{"alter",},{"drop",},{"truncate",},
//        {"add",},
//        {"insert",},{"update",},{"delete",},
//        {"into",},{"values",},{"set",},
//        {"select",},{"from",},{"where",},
//        {"",},
//        {"database",},{"table",},{"view",},{"user",},{"index",},
//        {"column",}
//    };
};

#endif // SQLPARSER_H
