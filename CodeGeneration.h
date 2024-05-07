#pragma once

#include <string>
#include <iostream>
using namespace std;
#include <vector>
#include <unordered_map>
using namespace std;

//a class to keep track of the registers, which will eventually be used by the interpreter to keep track of where a peice of data is saved
//a register either keeps track of an int or a bool
class Register
{
public:

	Register();
	Register(bool isbool);
	string toString();
	bool getIsFloat();

private:
	int number;
	bool isBool;
	static int registerCount;
};


//although we could create a new register for each variable, constant, and result of an expression, that is not very efficient. Thus, we create a pool to take registers and then put them back once they are done so we can use them again. object pool is a classic technique in many kinds of programming
class RegisterPool
{
public:

	Register getFloatReg();

	Register getBoolReg();

private:

};

//string to registers. So what variables correspond to what registers.
typedef std::unordered_map<string, Register> VariableContext;
