# DBMS
#include<bits/stdc++.h>
using namespace std;

int main() {

    map<int, int> g;

    g[1] = 2;
    g[2] = 4;
    g[3] = 8;

    for(auto& pr: g) {
        auto& key = pr.first;
        auto& value = pr.second;

        cout << key << ": " << value << endl;
    }
    cout << " ----------- " << endl;

    // f["table1"] = 0;
    // f["table2"] = 1;
    // f["table3"] = 2;
    // cout << f["table1"] << endl;
    // cout << f["table2"] << endl;
    // cout << f["table3"] << endl;

    map<string, map<string, map<string, string>>> f;

    f["..."]["..."]["..."] = "..";

    f["学生表"]["2"]["Sname"] = "lxy";
    f["学生表"]["2"]["Sno"] = "21301100";

    f["学生表"]["1"]["Sno"] = "21301115";
    
    // cout << f["学生表"]["1"]["学号"] << endl;
    // cout << f["学生表"]["2"]["学号"] << endl;

    f["tableName"]["numOfRecord"]["Sno"];
    f["tableName"]["numOfRecord"]["Sname"];
    
    // select * from 学生表

    auto& studentTable = f["学生表"];

    for(auto& record: studentTable) {
        cout << "record(" << record.first << "): ";
        for(auto& field: record.second) {
            cout << "(" << field.first << ", " << field.second << ") ";
        }
        cout << endl;
    }

    return 0;
}
