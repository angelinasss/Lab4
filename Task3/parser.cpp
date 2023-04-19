#include "parser.h"
#include <algorithm>
#include <iostream>
#include <thread>
#include <QDebug>
using namespace std;

Parser::Parser(const vector<string> &input) {
    this->input = input;
    thread classesThread(&Parser::classorstructCount, this);
    classesThread.join();
    thread variablesThread(&Parser::variablesCount, this);
    variablesThread.join();
    thread arraysThread(&Parser::arrayCount, this);
    arraysThread.join();
    thread prototypesThread(&Parser::prototypesCount, this);
    prototypesThread.join();
    size_t newsize = input.size() + 1;
    branchLevel.resize(newsize);
}

void Parser::variablesCount() {
    for (size_t i = 0; i < input.size(); i++) {
        regex reg(R"(((const\s)?()" + someType + R"()\**(<\D+>)*\s+(\**\s*\w+(\s=\s[-+]?(?:\d+|\d*.\d+)(?:[-+]?\d+)?\b)*(,*\s*))*(;)))");
        smatch coincidence;
        if (regex_search(input[i], coincidence, reg)) {
            variables.emplace_back(coincidence[0], place(coincidence[0], i));
        }
    }
}

void Parser::classorstructCount() {
    for (size_t i = 0; i < input.size(); i++) {
        regex reg(R"((class|struct)\s+(\w+)\s*\{)");
        smatch coincidence;
        if (regex_search(input[i], coincidence, reg)) {
            types.insert(coincidence[2]);
            if (coincidence[1] == "class")
                classes.emplace_back(coincidence[2]);
            else if (coincidence[1] == "struct")
                structs.emplace_back(coincidence[2]);
        }
    }
}

void Parser::arrayCount() {
    for (size_t i = 0; i < input.size(); i++) {
        regex reg("((" + someType + R"(\**)\s+(\w+\[\d+\]+)\s*((\{(.)*\})*)(;)))");
        smatch coincidence;
        if (regex_search(input[i], coincidence, reg)) {
            arrays.emplace_back(coincidence[0]);
        }
    }
}

void Parser::prototypesCount() {
    for (size_t i = 0; i < input.size(); i++) {
        regex reg("(const\s)?(" + someType + R"()&*\s*&*(\w+\d*\:\:)*(\w+\d*)(\s*)(\(((const\s)?()" + someType + R"()(&*\.*\s*&*\.*\w*)(\s=\s[-+]?(?:\d+|\d*.\d+)(?:[eE][-+]?\d+)?\b)*,*\s*)*\)))");
        smatch coincidence;
        if (regex_search(input[i], coincidence, reg)) {
            prototypes.emplace_back(make_pair(coincidence[0], coincidence[4]), place(coincidence[0], i));
        }
    }
}

set<string> Parser::get_types() const
{
    return types;
}

vector<string> Parser::get_classes() const
{
    return classes;
}

vector<string> Parser::get_structs() const
{
    return structs;
}

vector<int> Parser::get_branchesCount() const
{
    return branchLevel;
}

vector<pair<string, pair<size_t, size_t>>> Parser::get_variables() const {
    return variables;
}

vector<string> Parser::get_arrays() const {
    return arrays;
}

const vector<pair<pair<string, string>, pair<size_t, size_t>>> &Parser::get_prototypes() const {
    return prototypes;
}

vector<pair<string, pair<size_t, size_t>>> Parser::logicErrors()
{
    vector<pair<string, pair<size_t, size_t>>> errors;
    for (size_t i = 0; i < input.size(); i++) {
        regex reg(R"(((while|if|else if)\s*\((true|false)\))|(for\s*\(\s*((\w+\s+)*\w+(\s=\s.+)*)*;\s*;.*\)))");
        smatch coincidence;
        if (regex_search(input[i], coincidence, reg)) {
            errors.emplace_back(coincidence[0], place(coincidence[0], i));
        }
    }
    return errors;
}

vector<pair<string, pair<size_t, size_t>>> Parser::variablesChanges()
{
    vector<pair<string, pair<size_t, size_t>>> changes;
    for (size_t i = 0; i < input.size(); i++) {
        regex reg(R"(((\+\+|--)\w+)|(\w+(\+\+|--))|(\w+\s(=|\+=|-=)\s*([^\s\)])+\s*;))");
        smatch coincidence;
        if (regex_search(input[i], coincidence, reg)) {
            changes.emplace_back(coincidence[0], place(coincidence[0], i));
        }
    }
    return changes;
}

pair<size_t, size_t> Parser::place(const string &match, size_t ind) {
    return {ind + 1, input[ind].find(match) + 1};
}

bool IsUnique(const vector<pair<pair<string, string>, pair<size_t, size_t>>> &vec, size_t ind) {
    bool unique = true;
    for (size_t i = 0; i < vec.size(); i++) {
        if (vec[i].first.second == vec[ind].first.second) {
            unique = false;
            break;
        }
    }
    return unique;
}

bool IsChecked(const vector<pair<pair<string, string>, pair<size_t, size_t>>> &vec, size_t ind) {
    bool check = false;
    for (size_t i = 0; i < ind; i++) {
        if (vec[i].first.second == vec[ind].first.second) {
            check = true;
        }
    }
    return check;
}

pair<vector<pair<string, pair<size_t, size_t>>>, size_t> Parser::overloadedCount() {
    size_t count = 0;
    pair<vector<pair<string, pair<size_t, size_t>>>, size_t> _count;
    for (size_t i = 0; i < prototypes.size(); i++) {
        if (!IsChecked(prototypes, i) && !IsUnique(prototypes, i)) {
            count++;
        }
        if (!IsUnique(prototypes, i)) {
            _count.first.emplace_back(prototypes[i].first.first, make_pair(prototypes[i].second.first, prototypes[i].second.second));
        }
    }
    _count.second = count;
    return _count;
}

void Parser::countBranсh(size_t i)
{
    regex reg(R"(((while|if|else if|else)\s?\(.+\)\s*\{)|(for\s?\(.+\)\s*\{))");
    smatch coincidence;
    if (regex_search(input[i], coincidence, reg)) {
        branchLevel[i]++;
        size_t j = i + 1;
        while (place("}", j).second != place(coincidence[0], i).second && j < input.size() - 1) {
            countBranсh(j);
            j++;
        }
    }
}

void Parser::findBranches()
{
    size_t i = 0;
    while(i < input.size()) {
        countBranсh(i);
        i++;
    }
}
