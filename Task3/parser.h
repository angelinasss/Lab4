#ifndef PARSER_H
#define PARSER_H
#include <regex>
#include <set>
#include <QString>
using namespace std;

class Parser
{
    QString inputStr;
    vector<string> input;
    vector<string> classes;
    vector<string> structs;
    vector<string> arrays;
    vector<pair<string, pair<size_t, size_t>>> variables;
    vector<pair<pair<string, string>, pair<size_t, size_t>>> prototypes;
    vector<int> branchLevel;
    set<string> types {
    "int", "double", "float", "short", "char", "bool", "unsigned int", "unsigned long", "unsigned long long", "unsigned short", "size_t", "long long", "unsigned char", "void", "auto"
    };
    string someType = "int|double|float|long long|unsigned int|unsigned short|unsigned long|unsigned long long|size_t|unsigned char|short|char|bool|void|auto";
    void variablesCount();
    void classorstructCount();
    void arrayCount();
    void prototypesCount();
public:
    explicit Parser(const vector<string>&);
    vector<pair<string, pair<size_t, size_t>>> variablesChanges();
    pair<vector<pair<string, pair<size_t, size_t>>>, size_t> overloadedCount();
    vector<pair<string, pair<size_t, size_t>>> logicErrors();
    void countBranсh(size_t);
    void findBranches();
    pair<size_t, size_t> place(const string&, size_t);
    vector<int> get_branchesCount() const;
    set<string> get_types() const;
    vector<string> get_classes() const;
    vector<string> get_structs() const;
    vector<pair<string, pair<size_t, size_t>>> get_variables() const;
    vector<string> get_arrays() const;
    const vector<pair<pair<string, string>, pair<size_t, size_t>>>& get_prototypes() const;
};

#endif // PARSER_H
