#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>
using namespace std;

enum Type { NULL_T = 0, ERROR_T, FLOAT_T, BOOL_T }; //if the thing does not exist in the map, it will return a 0

typedef std::unordered_map<string, Type> TypeMap; //this is the "environment"
typedef std::unordered_map<string, vector<Type> > FunctionParamMap; //this will hold the function parameters