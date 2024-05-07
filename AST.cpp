#include "AST.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

RegisterPool ASTNode::regs;
Register ASTNode::NOREG;

int ASTNode::count = 0;

//this part is the functions for creating the tree

void ASTProgram::addFunction(ASTFunction* theFunction)
{
	functions.push_back(theFunction);
}

void ASTFunction::setName(string name_in)
{
	name = name_in;
}

void ASTFunction::setParam(ASTParam* theParam)
{
	params = theParam;
}

void ASTFunction::setStatements(ASTNode* stmts)
{
	this->stmts = stmts;
}

void ASTParam::addParam(string type, string name)
{
	types.push_back(type);
	names.push_back(name);
}

void ASTStatements::addStatement(ASTNode* statement)
{
	statements.push_back(statement);
}

void ASTStatement::setStatement(ASTNode* statementin)
{
	statement = statementin;
}

ASTNode* ASTStatement::getStatement()
{
	return statement;
}

void ASTArgs::addArg(ASTNode* statement)
{
	args.push_back(statement);
}

void ASTWhile::setStatement(ASTNode* statementin)
{
	statement = statementin;
}

void ASTWhile::setCondition(ASTNode* statementin)
{
	condition = statementin;
}

void ASTIf::setStatement(ASTNode* statementin)
{
	statement = statementin;
}

void ASTIf::setCondition(ASTNode* statementin)
{
	condition = statementin;
}



void ASTAssign::setLHS(string in)
{
	lhs = in;
}

void ASTAssign::setRHS(ASTNode* statementin)
{
	rhs = statementin;
}

void ASTFunctionCall::setName(string in)
{
	lhs = in;
}

void ASTFunctionCall::setParam(ASTNode* statementin)
{
	params = statementin;
}

void ASTBlockStatement::setStatement(ASTNode* statementin)
{
	statement = statementin;
}

ASTDeclaration::ASTDeclaration()
{
	val = 0;
}

void ASTDeclaration::setName(string in)
{
	name = in;
}

void ASTDeclaration::setType(string in)
{

	type = in;
}

void ASTDeclaration::setVal(ASTNode* in)
{
	val = in;
}

void ASTBooleanExprA::addOperand(ASTNode* in)
{
	operands.push_back(in);
}

void ASTBooleanExprA::addOperator(string in)
{
	operators.push_back(in);
}

void ASTBooleanExprB::addOperand(ASTNode* in)
{
	operands.push_back(in);
}

void ASTBooleanExprB::addOperator(string in)
{
	operators.push_back(in);
}


void ASTTerm::addOperand(ASTNode* in)
{
	operands.push_back(in);
}

void ASTTerm::addOperator(string in)
{
	operators.push_back(in);
}


void ASTExpr::addOperand(ASTNode* in)
{
	operands.push_back(in);
}

void ASTExpr::addOperator(string in)
{
	operators.push_back(in);
}

ASTFactor::ASTFactor()
{
	element = 0;
	boolExpr = 0;
}

void ASTFactor::setBoolExpr(ASTNode* in)
{
	boolExpr = in;
}

void ASTFactor::setElement(ASTNode* in)
{
	element = in;
}

void ASTElement::setElement(string valuein, bool isFloatin)
{
	isFloat = isFloatin;
	value = valuein;
}

ASTParam* ASTFunction::getParams()
{
	return params;
}

vector<string> ASTParam::getNames()
{
	return names;
}

vector<string> ASTParam::getTypes()
{
	return types;
}

string ASTFunction::getName()
{
	return name;
}



//this part is the functions for printing the tree
void ASTProgram::print(int depth)
{
	for (int i = 0; i < functions.size(); i++)
	{
		functions[i]->print(0);

		if (i != functions.size() - 1)
			cout << "\n";
	}
}

void ASTFunction::print(int depth)
{
	cout << name << "(";
	params->print(0);
	cout << ")\n";
	cout << "{\n";
	stmts->print(depth + 1);
	cout << "}\n";
}


void ASTParam::print(int depth)
{
	for (int i = 0; i < names.size(); i++)
	{
		cout << types[i] << " " << names[i];
		if (i != names.size() - 1)
		{
			cout << ", ";
		}
	}
}

void ASTStatements::print(int depth)
{
	for (int i = 0; i < statements.size(); i++)
	{
		statements[i]->print(depth);
	}
}

void ASTStatement::print(int depth)
{
	statement->print(depth);
}

void ASTArgs::print(int depth)
{
	for (int i = 0; i < args.size(); i++)
	{
		args[i]->print(depth);
		if (i != args.size() - 1)
			cout << ", ";
	}
}

void ASTWhile::print(int depth)
{
	for (int i = 0; i < depth; i++)
	{
		cout << "\t";
	}

	cout << "while(";
	condition->print(depth);
	cout << ")\n";

	ASTStatement* stmt = (ASTStatement*)statement;

	if (typeid(*(stmt->getStatement())) == typeid(ASTBlockStatement))
	{
		statement->print(depth);
	}
	else
	{
		statement->print(depth + 1);
	}
}

void ASTIf::print(int depth)
{
	for (int i = 0; i < depth; i++)
	{
		cout << "\t";
	}

	cout << "if(";
	condition->print(depth);
	cout << ")\n";


	ASTStatement* stmt = (ASTStatement*)statement;

	if (typeid(*(stmt->getStatement())) == typeid(ASTBlockStatement))
	{
		statement->print(depth);
	}
	else
	{
		statement->print(depth + 1);
	}



}

void ASTAssign::print(int depth)
{


	for (int i = 0; i < depth; i++)
	{
		cout << "\t";
	}

	cout << lhs << " = ";
	rhs->print(depth);
	cout << ";\n";
}

void ASTFunctionCall::print(int depth)
{
	for (int i = 0; i < depth; i++)
	{
		cout << "\t";
	}

	cout << lhs << "(";
	params->print(depth);
	cout << ");\n";
}

void ASTBlockStatement::print(int depth)
{
	for (int i = 0; i < depth; i++)
	{
		cout << "\t";
	}

	cout << "{\n";
	statement->print(depth + 1);

	for (int i = 0; i < depth; i++)
	{
		cout << "\t";
	}
	cout << "}\n";
}

void ASTDeclaration::print(int depth)
{
	for (int i = 0; i < depth; i++)
	{
		cout << "\t";
	}

	cout << type << " " << name;

	if (val != NULL)
	{
		cout << " = ";
		val->print(depth);
	}

	cout << ";\n";
}

void ASTBooleanExprA::print(int depth)
{

	operands[0]->print(depth);
	for (int i = 1; i < operands.size(); i++)
	{
		cout << " " << operators[i - 1] << " ";
		operands[i]->print(depth);
	}
}

void ASTBooleanExprB::print(int depth)
{
	operands[0]->print(depth);
	for (int i = 1; i < operands.size(); i++)
	{
		cout << " " << operators[i - 1] << " ";
		operands[i]->print(depth);
	}
}


void ASTTerm::print(int depth)
{

	operands[0]->print(depth);
	for (int i = 1; i < operands.size(); i++)
	{
		cout << " " << operators[i - 1] << " ";
		operands[i]->print(depth);
	}
}


void ASTExpr::print(int depth)
{

	operands[0]->print(depth);
	for (int i = 1; i < operands.size(); i++)
	{
		cout << " " << operators[i - 1] << " ";
		operands[i]->print(depth);
	}
}

void ASTFactor::print(int depth)
{
	if (boolExpr == 0)
	{
		element->print(depth);
	}
	else
	{
		cout << "(";
		boolExpr->print(depth);
		cout << ")";
	}
}

void ASTElement::print(int depth)
{
	cout << value;
}

vector<ASTNode*> ASTArgs::getArgs()
{
	return args;
}



void typeError(string code, int line, string message, bool& hasError)
{
	if (!hasError)
	{
		cout << code << " around line: " << line << " ;;; " << message << "\n";
		hasError = true;
	}
}

string typeToString(Type t)
{
	if (t == NULL_T)
		return "Null_Type";
	if (t == ERROR_T)
		return "Error_Type";
	if (t == FLOAT_T)
		return "Float_Type";
	if (t == BOOL_T)
		return "Bool_Type";

	return "Unknown type";
}

//ths function only
Type ASTFunction::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	stmts->typeCheck(map, fmap, hadError);
	return Type::NULL_T;
}

//this function should return null_t but must check the types of the various peices
Type ASTProgram::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	fmap = new FunctionParamMap();

	vector<Type> printa;
	printa.push_back(FLOAT_T);
	fmap->operator[]("print") = printa;

	vector<Type> timea;
	timea.push_back(FLOAT_T);
	fmap->operator[]("time") = timea;


	vector<Type> drawsquare;
	drawsquare.push_back(FLOAT_T);
	drawsquare.push_back(FLOAT_T);
	drawsquare.push_back(FLOAT_T);
	drawsquare.push_back(FLOAT_T);
	drawsquare.push_back(FLOAT_T);
	drawsquare.push_back(FLOAT_T);
	drawsquare.push_back(FLOAT_T);
	fmap->operator[]("drawsquare") = drawsquare;


	for (int i = 0; i < functions.size(); i++)
	{
		//create map
		TypeMap* m = new TypeMap();

		//add the params in
		ASTParam* params = functions[i]->getParams();

		vector<Type> functionParamTypes;

		//check param types and then add the types into the map.
		for (int j = 0; j < params->getNames().size(); j++)
		{
			vector<string> names = params->getNames();
			vector<string> types = params->getTypes();

			if (types[j] == "float")
			{
				string name = names[j];
				if (name == "if" || name == "while" || name == "float" || name == "bool" || name == "TRUE" || name == "FALSE")
				{
					bool hadErrorB = false;
					typeError("T_function06", functions[i]->getLine(), "\"" + name + "\" keyword cannot be used as a function parameter name", hadErrorB);
					hadError = hadError || hadErrorB;
				}
				//please note the weird syntax here, calling the [] operator as if it is the function.
				else if (m->operator[](names[j]) == NULL_T) //in this case null_t is 0 so that is what will be returned if it is empty.
				{
					//we good since it is not prev defined!
					m->operator[](names[j]) = FLOAT_T;
					functionParamTypes.push_back(FLOAT_T);
				}
				else
				{
					//already defined...
					typeError("T_Function01", getLine(), "Variable \"" + names[j] + "\" is already defined", hadError);
				}
			}
			else if (types[j] == "bool")
			{
				string name = names[j];
				if (name == "if" || name == "while" || name == "float" || name == "bool" || name == "TRUE" || name == "FALSE")
				{
					bool hadErrorB = false;
					typeError("T_function07", functions[i]->getLine(), "\"" + name + "\" keyword cannot be used as a function parameter name", hadErrorB);
					hadError = hadError || hadErrorB;
				}
				//please note the weird syntax here, calling the [] operator as if it is the function.
				else if (m->operator[](names[j]) == NULL_T) //in this case null_t is 0 so that is what will be returned if it is empty.
				{
					//we good since it is not prev defined!
					m->operator[](names[j]) = BOOL_T;
					functionParamTypes.push_back(BOOL_T);
				}
				else
				{
					//already defined...
					typeError("T_Function02", getLine(), "Variable \"" + names[j] + "\" is already defined", hadError);
				}
			}
			else
			{
				typeError("T_Function03", getLine(), "Type \"" + types[j] + "\" undefined", hadError);
			}
		}

		string name = functions[i]->getName();

		//see if function already exists
		if (fmap->find(functions[i]->getName()) != fmap->end())
		{
			bool hadErrorB = false;
			typeError("T_function05", functions[i]->getLine(), "\"" + name + "\" already defined", hadErrorB);
			hadError = hadError || hadErrorB;
		}
		else if (name == "if" || name == "while" || name == "float" || name == "bool" || name == "TRUE" || name == "FALSE")
		{
			bool hadErrorB = false;
			typeError("T_function04", functions[i]->getLine(), "\"" + name + "\" keyword cannot be used as a function name", hadErrorB);
			hadError = hadError || hadErrorB;
		}
		else
		{
			//this means it uses the C rules that a function has to be defined before it can be called;
			fmap->operator[](functions[i]->getName()) = functionParamTypes;
		}



		//check the types
		functions[i]->typeCheck(m, fmap, hadError);
	}

	if (fmap->find("main") == fmap->end())
	{
		bool hadErrorB = false;
		typeError("T_function09", -1, "Main function does not exist", hadErrorB);
		hadError = hadError || hadErrorB;
	}


	return Type::NULL_T;
}

//must check all the statements
Type ASTStatements::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	for (int i = 0; i < statements.size(); i++)
	{
		statements[i]->typeCheck(map, fmap, hadError);
	}
	return Type::NULL_T;
}

//must check its statement
Type ASTStatement::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	bool newHasError = false;
	statement->typeCheck(map, fmap, newHasError);
	hadError = hadError || newHasError;
	return Type::NULL_T;
}

//must check if valid variable, valid bool constant (TRUE or FALSE) or number and return the corresponding type
Type ASTElement::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	if (isFloat)
	{
		return Type::FLOAT_T;
	}
	else if (value == "TRUE" || value == "FALSE")
	{
		return Type::BOOL_T;
	}
	else
	{
		if (map->operator[](value) == NULL_T) //in this case null_t is 0 so that is what will be returned if it is empty.
		{
			typeError("T_element01", getLine(), "Variable \"" + value + "\" is not defined", hadError);

		}
		else
		{
			return map->operator[](value);
		}
	}
	return Type::NULL_T;
}

//must verify the types is valid, verify variable not used (and add the variable to the type map not used), then (possibly) verify the left and right sides are the same.
//variables names cannot be a keyword
Type ASTDeclaration::typeCheck(TypeMap* m, FunctionParamMap* fmap, bool& hadError)
{
	Type t = ERROR_T;

	Type right = NULL_T;

	if (val != 0)
	{
		right = val->typeCheck(m, fmap, hadError);
	}


	bool nameError = false;
	bool hadErrorB = false;
	if (name == "if" || name == "while" || name == "float" || name == "bool" || name == "TRUE" || name == "FALSE")
	{
		nameError = true;
		typeError("T_dec05", getLine(), "\"" + name + "\" keyword cannot be used as a variable name", hadErrorB);
		hadError = hadError || hadErrorB;
	}
	if (type == "float")
	{
		//please note the weird syntax here, calling the [] operator as if it is the function.
		if (m->operator[](name) == NULL_T && !nameError) //in this case null_t is 0 so that is what will be returned if it is empty.
		{
			//we good since it is not prev defined!
			m->operator[](name) = FLOAT_T;
			t = FLOAT_T;
		}
		else if (!nameError)
		{
			hadErrorB = false;
			//already defined...
			typeError("T_dec01", getLine(), "Variable \"" + name + "\" is already defined", hadErrorB);
			hadError = hadError || hadErrorB;
		}
	}
	else if (type == "bool")
	{
		//please note the weird syntax here, calling the [] operator as if it is the function.
		if (m->operator[](name) == NULL_T && !nameError) //in this case null_t is 0 so that is what will be returned if it is empty.
		{
			//we good since it is not prev defined!
			m->operator[](name) = BOOL_T;
			t = BOOL_T;
		}
		else if (!nameError)
		{
			hadErrorB = false;
			//already defined...
			typeError("T_dec02", getLine(), "Variable \"" + name + "\" is already defined", hadErrorB);
			hadError = hadError || hadErrorB;
		}
	}
	else
	{
		hadErrorB = false;
		typeError("T_dec03", getLine(), "Type \"" + type + "\" undefined", hadErrorB);
		hadError = hadError || hadErrorB;
	}


	if (t == BOOL_T || t == FLOAT_T)
	{
		if (right != NULL_T && right != ERROR_T)
		{
			if (t != right)
			{
				typeError("T_dec04", getLine(), "Left and right sides of declaration do not agree. Left is \"" + typeToString(t) + "\". Right is \"" + typeToString(right) + "\"", hadError);
			}
		}
	}



	return Type::NULL_T;
}

//returns the check of the element or the expression
Type ASTFactor::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	if (element != 0)
	{
		return element->typeCheck(map, fmap, hadError);
	}
	else
	{
		return boolExpr->typeCheck(map, fmap, hadError);
	}

	return Type::NULL_T;
}



//these are for part 2


Type ASTWhile::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	bool hadErrorB = false;
	Type x = condition->typeCheck(map, fmap, hadErrorB);

	if (x != Type::BOOL_T && !hadErrorB)
	{
		typeError("T_while01", getLine(), "while condition is not bool. Recieved \"" + typeToString(x) + "\" instead.", hadError);
	}

	TypeMap* tm = new TypeMap();

	for (auto it = map->begin(); it != map->end(); it++)
	{
		tm->operator[](it->first) = it->second;
	}

	bool hadErrorC = false;
	statement->typeCheck(tm, fmap, hadErrorC);



	return Type::NULL_T;
}
Type ASTIf::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	bool hadErrorB = false;
	Type x = condition->typeCheck(map, fmap, hadErrorB);

	if (x != Type::BOOL_T && !hadErrorB)
	{
		typeError("T_if01", getLine(), "if condition is not bool. Recieved \"" + typeToString(x) + "\" instead.", hadError);
	}

	TypeMap* tm = new TypeMap();

	for (auto it = map->begin(); it != map->end(); it++)
	{
		tm->operator[](it->first) = it->second;
	}

	bool hadErrorC = false;
	statement->typeCheck(tm, fmap, hadErrorC);



	return Type::NULL_T;
}
Type ASTAssign::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	Type left = Type::NULL_T;

	if (map->find(this->lhs) == map->end())
	{
		bool hadErrorB = false;
		typeError("T_assign01", getLine(), "Variable \"" + lhs + "\" is not defined", hadErrorB);
		hadError = hadErrorB || hadError;

	}
	else
	{
		left = map->operator[](this->lhs);
	}


	bool hadErrorB = false;
	Type t = this->rhs->typeCheck(map, fmap, hadErrorB);
	hadError = hadErrorB || hadError;

	if (t != Type::ERROR_T && left != t)
	{
		bool hadErrorB = false;
		typeError("T_assign02", getLine(), "Left and Right do not agree in assign. Left is " + typeToString(left) + ". Right is " + typeToString(t) + ".", hadErrorB);
		hadError = hadErrorB || hadError;
	}


	return Type::NULL_T;
}
Type ASTFunctionCall::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	//workaround to make print work with either type. No overloaded functions :(
	if (lhs == "print" && ((ASTArgs*)this->params)->getArgs().size() == 1)
	{
		return Type::NULL_T;
	}

	if (fmap->find(lhs) == fmap->end())
	{
		bool hadErrorB = false;
		typeError("t_functioncall01", getLine(), "Function \"" + lhs + "\" does not exist", hadErrorB);
		hadError = hadErrorB || hadError;
	}

	vector<Type> paramTypes;

	for (int i = 0; i < ((ASTArgs*)this->params)->getArgs().size(); i++)
	{
		bool hadErrorB = false;

		paramTypes.push_back(((ASTArgs*)this->params)->getArgs()[i]->typeCheck(map, fmap, hadErrorB));
		hadError = hadErrorB || hadError;
	}

	bool paramerror = false;

	if (fmap->find(lhs) != fmap->end())
	{
		vector<Type> actualTypes = fmap->operator[](lhs);

		bool error = false;

		if (paramTypes.size() != actualTypes.size())
		{
			error = true;
		}
		else
		{
			for (int i = 0; i < paramTypes.size(); i++)
			{
				if (paramTypes[i] != actualTypes[i])
				{
					error = true;

				}
				if (paramTypes[i] == ERROR_T)
				{
					paramerror = true;
				}
			}
		}

		if (error && !paramerror)
		{
			bool hadErrorB = false;

			string wanted = "";
			string actual = "";

			for (int i = 0; i < paramTypes.size(); i++)
			{
				wanted += typeToString(paramTypes[i]);
				if (i != paramTypes.size() - 1)
					wanted += ", ";
			}

			for (int i = 0; i < actualTypes.size(); i++)
			{
				actual += typeToString(actualTypes[i]);
				if (i != actualTypes.size() - 1)
					actual += ", ";
			}

			typeError("t_functioncall02", getLine(), "Function \"" + lhs + "\" recieved arguments \"" + wanted + "\" but wanted \"" + actual + "\"", hadErrorB);
			hadError = hadErrorB || hadError;
		}
	}

	return Type::NULL_T;
}
Type ASTBlockStatement::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	TypeMap* tm = new TypeMap();

	for (auto it = map->begin(); it != map->end(); it++)
	{
		tm->operator[](it->first) = it->second;
	}

	bool hadErrorC = false;
	statement->typeCheck(tm, fmap, hadErrorC);

	return Type::NULL_T;
}

//i had to implement this version of these to make factor and element work. This version must be corrected part 2
Type ASTBooleanExprA::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	Type wantedType = Type::BOOL_T;

	if (operands.size() == 1)
	{
		return operands[0]->typeCheck(map, fmap, hadError);
	}

	for (int i = 0; i < operands.size(); i++)
	{
		Type t = operands[i]->typeCheck(map, fmap, hadError);

		string op;
		if (i == 0)
			op = operators[0];
		else
			op = operators[i - 1];

		if (t != wantedType && !hadError)
		{
			typeError("t_boolA", getLine(), "Operator \"" + op + "\" recieved type " + typeToString(t), hadError);
		}
	}


	if (hadError)
		return ERROR_T;


	return wantedType;
}

#include<list>


Type ASTBooleanExprB::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	Type wantedType = Type::BOOL_T;

	if (operands.size() == 1)
	{
		return operands[0]->typeCheck(map, fmap, hadError);
	}
	vector<Type> types;
	for (int i = 0; i < operands.size(); i++)
	{
		Type t = operands[i]->typeCheck(map, fmap, hadError);
		types.push_back(t);
	}

	int indexToCheck = 1;
	Type left = types[0];
	Type right;
	while (indexToCheck < types.size())
	{
		right = types[indexToCheck];

		if (operators[indexToCheck - 1] == "==")
		{
			if (left == right)
			{

			}
			else
			{
				typeError("t_boolB01", getLine(), "Operator \"" + operators[indexToCheck - 1] + "\" recieved type " + typeToString(left) + " and " + typeToString(right), hadError);

			}
		}
		else
		{
			if (left == FLOAT_T && right == FLOAT_T)
			{

			}
			else
			{
				typeError("t_boolB03", getLine(), "Operator \"" + operators[indexToCheck - 1] + "\" recieved type " + typeToString(left) + " and " + typeToString(right), hadError);

			}
		}

		left = Type::BOOL_T;//always produces a bool.
		indexToCheck++;
	}



	/*	string op;
		if (i == 0)
			op = operators[0];
		else
			op = operators[i - 1];

		if (t != Type::FLOAT_T && !hadError)
		{
			typeError("t_boolB01", getLine(), "Operator \"" + op + "\" recieved type " + typeToString(t), hadError);
		}
	}*/



	if (hadError)
		return ERROR_T;


	return Type::BOOL_T;
}
Type ASTTerm::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	Type wantedType = Type::FLOAT_T;

	if (operands.size() == 1)
	{
		return operands[0]->typeCheck(map, fmap, hadError);
	}

	for (int i = 0; i < operands.size(); i++)
	{
		Type t = operands[i]->typeCheck(map, fmap, hadError);

		string op;
		if (i == 0)
			op = operators[0];
		else
			op = operators[i - 1];

		if (t != wantedType && !hadError)
		{
			typeError("t_astterm01", getLine(), "Operator \"" + op + "\" recieved type " + typeToString(t), hadError);
		}
	}


	if (hadError)
		return ERROR_T;


	return wantedType;
}
Type ASTExpr::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	Type wantedType = Type::FLOAT_T;

	if (operands.size() == 1)
	{
		return operands[0]->typeCheck(map, fmap, hadError);
	}

	for (int i = 0; i < operands.size(); i++)
	{
		Type t = operands[i]->typeCheck(map, fmap, hadError);

		string op;
		if (i == 0)
			op = operators[0];
		else
			op = operators[i - 1];

		if (t != wantedType && !hadError)
		{
			typeError("t_astexpr01", getLine(), "Operator \"" + op + "\" recieved type " + typeToString(t), hadError);
		}
	}


	if (hadError)
		return ERROR_T;


	return wantedType;
}



//this should be unused and handled in functioncall (i.e., function call should check the args itself)
Type ASTArgs::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	return Type::NULL_T;
}
//this function is unused and handled in function (that is, the function declaration)
Type ASTParam::typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError)
{
	return Type::NULL_T;
}



//this part is for outputting the bytecode

Register ASTProgram::output(VariableContext* vc, ofstream& out)
{
	for (int i = 0; i < functions.size(); i++)
	{
		VariableContext* vc = new VariableContext();
		functions[i]->output(vc, out);
	}

	return NOREG;
}

Register ASTFunction::output(VariableContext* vc, ofstream& out)
{
	out << "function " << name << " params ";
	for (int i = 0; i < params->getNames().size(); i++)
	{
		Register r;
		if ((params->getTypes()[i] == "bool"))
			r = regs.getBoolReg();
		else
			r = regs.getFloatReg();

		(*vc)[params->getNames()[i]] = r;

		out << r.toString() << " ";
	}

	out << "endparams " << "\n";

	stmts->output(vc, out);

	out << "endfunction\n" << "\n";

	return NOREG;
}


//for part 1
Register ASTStatements::output(VariableContext* vc, ofstream& out)
{
	for (int i = 0; i < statements.size(); i++)
	{
		statements[i]->output(vc, out);
	}
	return NOREG;
}
Register ASTStatement::output(VariableContext* vc, ofstream& out)
{
	statement->output(vc, out);
	return NOREG;
}

Register ASTDeclaration::output(VariableContext* vc, ofstream& out)
{

	if (type == "bool")
	{
		Register r = regs.getBoolReg();
		out << "bool " << r.toString() << "\n";
		vc->operator[](name) = r;

		if (val != 0)
		{
			Register r2 = val->output(vc, out);
			out << "= " << r.toString() << " " << r2.toString() << "\n";
		}
	}
	else //if (type == "float")
	{
		Register r = regs.getFloatReg();
		out << "float " << r.toString() << "\n";
		vc->operator[](name) = r;

		if (val != 0)
		{
			Register r2 = val->output(vc, out);
			out << "= " << r.toString() << " " << r2.toString() << "\n";
		}
	}


	return NOREG;
}

Register  ASTFactor::output(VariableContext* vc, ofstream& out)
{
	if (element == 0)
	{
		return boolExpr->output(vc, out);
	}
	else
	{
		return element->output(vc, out);
	}


}

//returns a register that contains the value of the element
Register ASTElement::output(VariableContext* vc, ofstream& out)
{
	//delete???
	Register r;
	if (value == "TRUE")
	{
		r = regs.getBoolReg();
		out << "bool " << r.toString() << "\n";
		out << "= " << r.toString() << " TRUE\n";
		return r;
	}

	if (value == "FALSE")
	{
		r = regs.getBoolReg();
		out << "bool " << r.toString() << "\n";
		out << "= " << r.toString() << " FALSE\n";
		return r;
	}

	//so variable
	if (!isFloat)
	{
		return (*vc)[value];
	}

	//otherwise floating num
	float f = stof(value);
	r = regs.getFloatReg();
	out << "float " << r.toString() << "\n";
	out << "= " << r.toString() << " " << f << "\n";

	return r;
}

//this is not complete and the rest of it must be done in part 2 but but I wanted to do these special functions
Register ASTFunctionCall::output(VariableContext* vc, ofstream& out)
{
	if (lhs == "print")
	{
		//get the register that will hold the print result
		Register r = ((ASTArgs*)params)->getArgs()[0]->output(vc, out);
		out << "print " << r.toString() << "\n";
	}
	else if (lhs == "time")
	{
		Register r = ((ASTArgs*)params)->getArgs()[0]->output(vc, out);
		out << "time " << r.toString() << "\n";
	}
	else if (lhs == "drawsquare")
	{
		vector<Register> args;
		for (int i = 0; i < 7; i++)
		{
			Register r = ((ASTArgs*)params)->getArgs()[i]->output(vc, out);
			args.push_back(r);
		}

		out << "callfunction drawsquare args ";

		for (int i = 0; i < 7; i++)
		{
			out << args[i].toString() << " ";
		}

		out << "endargs\n";
	}

    
	else 
	{
		vector <Register> args;
		for (int i = 0; i < ((ASTArgs*)params)->getArgs().size(); i++)
		{
			Register r = ((ASTArgs*)params)->getArgs()[i]->output(vc, out);
			args.push_back(r);
		}
		
		//call function print
		out << "callfunction " << lhs << " args ";

		for (int i = 0; i < args.size(); i++)
		{
			out << args[i].toString() << " ";
		}

		out << "endargs\n";
		
	}


	return NOREG;
}



//for part 2
//create code for while
//if one param create self comparison code
Register ASTWhile::output(VariableContext* vc, ofstream& out)
{
	//store then condition var in a temp register -- call the getBoolReg to create reg
	Register conditionCheck = regs.getBoolReg();
	out << "bool " << conditionCheck.toString() << endl;


	//label to jump to to create loop feature
	out << "label start" << count << endl;

	//register to store the actual value of condition
	Register conditionReg = condition->output(vc,out);



	//make conditioncheck opposite of current condition
	out << "! " << conditionCheck.toString() << " " << conditionReg.toString() << endl;


	//jump if statement -- jump to end if false (i.e conditionCheck is true)
	out << "jumpif " << "end" << count << " " << conditionCheck.toString() << endl;

	//call output of block statement
	statement->output(vc, out);

	//jump statement to go to starat
	out << "jump start" << count << endl;

	//end label to go to if conditionCheck was true -- i.e leave loop
	out << "label end" << count << endl;

	//increment count
	count++;
	return NOREG;
}
Register ASTIf::output(VariableContext* vc, ofstream& out)
{
	//conditional bool register 
	Register conditionCheck = regs.getBoolReg();
	out << "bool " << conditionCheck.toString() << endl;

	//get the output of the condition node
	Register r = condition->output(vc, out);

	//print conditional reg
	out << "! " << conditionCheck.toString() << " " << r.toString() << endl;

	//jump to end if false
	out << "jumpif " << "label" << count << " " << conditionCheck.toString()<< endl;
	

	//block code
	statement->output(vc, out);

	//label 
	out << "label label" << count << endl;

	count = count + 1;
	return NOREG;
}
Register ASTAssign::output(VariableContext* vc, ofstream& out)
{
	//print out assignment of the register in vc at lhs  and get rhs register
	out << "= " << vc->operator[](lhs).toString() << " " << rhs->output(vc, out).toString() << endl;

	//print = LHS_reg RHS_rg
	return NOREG;
}

Register ASTBlockStatement::output(VariableContext* vc, ofstream& out)
{
	//call member output
	statement->output(vc, out);
	return NOREG;
}

//if size of expression is greater than 1, store lhs and rhs in register, then store the result in new register
//set result register to lhs...
Register  ASTBooleanExprA::output(VariableContext* vc, ofstream& out)
{

	// there is only one ASTNode, call output on node and return reg
	if (operands.size() == 1)
	{
		return operands.at(0)->output(vc, out);
	}
	//if more than one operand, loop
	else
	{
		Register r1;
		Register r2;
		Register tempr;	//create register to hold result of 

		//loop over list of operators
		for (int i = 0; i < operators.size(); i++)
		{
			//if it is the first time through, get first two registers
			if (i == 0)
			{
				//call output on regs
				r1 = operands.at(i)->output(vc, out);
				r2 = operands.at(i + 1)->output(vc, out);
			}
			//if not first time through, set lhs equal to result
			//set lhs to next variable
			else
			{
				r1 = tempr;
				r2 = operands.at(i + 1)->output(vc, out);
			}
			tempr = regs.getBoolReg();	/// to store lhs and rhs of bea into register

			out << "bool " << tempr.toString() << endl;

			if (operators.at(i) == "&")
				out << "&& ";
			else if (operators.at(i) == "|")
				out << "|| ";

			out << tempr.toString() << " " << r1.toString() << " " << r2.toString() << endl;

		}
		return tempr;

	}
}


//if size of expression is greater than 1, store lhs and rhs in register, then store the result in new register
//set result register to lhs...
Register  ASTBooleanExprB::output(VariableContext* vc, ofstream& out)
{
	if(operands.size() == 1)
	{
		return operands[0]->output(vc, out);
	}
	else
	{
		Register r1;
		Register r2;
		Register tempr;
		
		//loop through operators
		for (int i = 0; i < operators.size(); i++)
		{
			//if i == 0 just get first two operands
			if (i == 0)
			{
				r1 = operands.at(i)->output(vc, out);
				r2 = operands.at(i + 1)->output(vc, out);
			}
			else
			{
				//set lhs to previous result
				r1 = tempr;
				r2 = operands.at(i + 1)->output(vc,out);
			}
			//get new register to store result
			tempr = regs.getBoolReg();

			//print new variable dec
			out << "bool " << tempr.toString() << endl;

			//operator printing
			if (operators.at(i) == "==")
				out << "== ";
			else if (operators.at(i) == ">")
				out << "> ";
			else if (operators.at(i) == ">=")
				out << ">= ";
			out << tempr.toString() << " " << r1.toString() << " " << r2.toString() << endl;
		}

		return tempr;
	}
}
Register  ASTTerm::output(VariableContext* vc, ofstream& out)
{
	if (operands.size() == 1)
	{
		return operands[0]->output(vc, out);
	}
	else
	{
		Register r1;
		Register r2;
		Register tempr;

		//loop through operators
		for (int i = 0; i < operators.size(); i++)
		{
			//if i == 0 just get first two operands
			if (i == 0)
			{
				r1 = operands.at(i)->output(vc, out);
				r2 = operands.at(i + 1)->output(vc, out);
			}
			else
			{
				//set lhs to previous result
				r1 = tempr;
				r2 = operands.at(i + 1)->output(vc,out);
			}
			//get new register to store result
			tempr = regs.getFloatReg();

			//print new variable dec
			out << "float " << tempr.toString() << endl;


			out << operators.at(i) << " " << tempr.toString() << " " << r1.toString() << " " << r2.toString() << endl;
		}

		return tempr;
	}
}


Register  ASTExpr::output(VariableContext* vc, ofstream& out)
{
	if (operands.size() == 1)
	{
		return operands[0]->output(vc, out);
	}
	else
	{
		Register r1;
		Register r2;
		Register tempr;

		//loop through operators
		for (int i = 0; i < operators.size(); i++)
		{
			//if i == 0 just get first two operands
			if (i == 0)
			{
				r1 = operands.at(i)->output(vc, out);
				r2 = operands.at(i + 1)->output(vc, out);
			}
			else
			{
				//set lhs to previous result
				r1 = tempr;
				r2 = operands.at(i + 1)->output(vc, out);
			}
			//get new register to store result
			tempr = regs.getFloatReg();

			//print new variable dec
			out << "float " << tempr.toString() << endl;


			out << operators.at(i) << " " << tempr.toString() << " " << r1.toString() << " " << r2.toString() << endl;
		}

		return tempr;
	}
}



//unused (at least, unused in my implementation)
Register ASTArgs::output(VariableContext* vc, ofstream& out)
{
	return NOREG;
}

//unused.
Register ASTParam::output(VariableContext* vc, ofstream& out)
{
	return NOREG;
}