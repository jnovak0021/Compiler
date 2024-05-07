#include "CodeGeneration.h"
#include <string>
#include <iostream>
using namespace std;

Register::Register() { number = -1; }

Register::Register(bool isbool)
{
	number = registerCount++;
	isBool = isbool;
}

//my naming convention: b means bool, f means float
string Register::toString()
{
	string temp = "" + to_string(number);
	if (isBool)
	{
		temp = "b" + (temp);
	}
	else
	{
		temp = "f" + (temp);
	}
	return temp;
}
bool Register::getIsFloat()
{
	return !isBool;
}


//intializing static variable for the class
int Register::registerCount = 0;


Register RegisterPool::getFloatReg()
{

	Register temp(false);

	return temp;
}

Register RegisterPool::getBoolReg()
{
	Register temp(true);

	return temp;
}


