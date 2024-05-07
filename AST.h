#pragma once

#include <vector>
#include <string>
using namespace std;

#include "Type.h"
#include "CodeGeneration.h"

class ASTFunction;
class ASTParam;
class ASTProgram;
class ASTStatements;
class ASTStatement;
class ASTArgs;
class ASTWhile;
class ASTIf;
class ASTAssign;
class ASTFunctionCall;
class ASTBlockStatement;
class ASTDeclaration;
class ASTBooleanExprA;
class ASTBooleanExprB;
class ASTTerm;
class ASTExpr;
class ASTFactor;
class ASTElement;

class ASTNode
{
public:
	
	virtual void print(int depth) = 0;
	virtual Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError) = 0;

	void setLine(int l) { line = l; }
	int getLine() { return line; }
	virtual Register output(VariableContext* vc, ofstream& out) = 0;
protected:
	static RegisterPool regs;
	static Register NOREG;
	static int count;
private:
	
	int line;
};


class ASTProgram : public ASTNode
{
public:
	void addFunction(ASTFunction * theFunction);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	Register output(VariableContext* vc, ofstream& out);
private:
	vector<ASTFunction*> functions;
};


class ASTFunction : public ASTNode
{
public:
	void setParam(ASTParam* params_in);
	void setName(string name);
	void print(int depth);
	void setStatements(ASTNode* stmts);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);

	ASTParam * getParams();

	string getName();
	Register output(VariableContext* vc, ofstream& out);
private:
	ASTParam* params;
	string name;
	ASTNode* stmts;

};

class ASTParam : public ASTNode
{
public:
	void addParam(string type, string name);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);

	vector<string> getTypes();
	vector<string> getNames();
	Register output(VariableContext* vc, ofstream& out);
private:
	vector<string> types;
	vector<string> names;


};



class ASTStatements : public ASTNode
{
public:
	void addStatement(ASTNode* theNode);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	Register output(VariableContext* vc, ofstream& out);
private:
	vector<ASTNode*> statements;
};

class ASTStatement : public ASTNode
{
public:
	void setStatement(ASTNode* theNode);
	ASTNode* getStatement();
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	Register output(VariableContext* vc, ofstream& out);
private:
	ASTNode * statement;
};

class ASTArgs : public ASTNode
{
public:
	void addArg(ASTNode* theNode);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);

	vector<ASTNode*> getArgs();
	Register output(VariableContext* vc, ofstream& out);
private:
	vector<ASTNode*> args;
};

class ASTWhile : public ASTNode
{
public:
	void setStatement(ASTNode* theNode);
	void setCondition(ASTNode* theNode);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	Register output(VariableContext* vc, ofstream& out);
private:
	ASTNode* statement;
	ASTNode* condition;
};


class ASTIf : public ASTNode
{
public:
	void setStatement(ASTNode* theNode);
	void setCondition(ASTNode* theNode);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	Register output(VariableContext* vc, ofstream& out);
private:
	ASTNode* statement;
	ASTNode* condition;
};

class ASTAssign : public ASTNode
{
public:
	void setRHS(ASTNode* theNode);
	void setLHS(string in);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	Register output(VariableContext* vc, ofstream& out);
private:
	ASTNode* rhs;
	string lhs;
};

class ASTFunctionCall : public ASTNode
{
public:
	void setParam(ASTNode* theNode);
	void setName(string in);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	Register output(VariableContext* vc, ofstream& out);
private:
	ASTNode* params;
	string lhs;
};

class ASTBlockStatement : public ASTNode
{
public:
	void setStatement(ASTNode* statementin);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	Register output(VariableContext* vc, ofstream& out);
private:
	ASTNode* statement;
};

class ASTDeclaration : public ASTNode
{
public:
	void setType(string in);
	void setName(string in);
	void setVal(ASTNode* in);
	void print(int depth);
	ASTDeclaration();
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	Register output(VariableContext* vc, ofstream& out);
private:
	string type;
	string name;
	ASTNode* val;
};

class ASTBooleanExprA : public ASTNode
{
public:
	void addOperator(string op);
	void addOperand(ASTNode * val);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	Register output(VariableContext* vc, ofstream& out);
private:
	vector<string> operators;
	vector<ASTNode*> operands;
};

class ASTBooleanExprB : public ASTNode
{
public:
	void addOperator(string op);
	void addOperand(ASTNode* val);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	Register output(VariableContext* vc, ofstream& out);
private:
	vector<string> operators;
	vector<ASTNode*> operands;
};

class ASTTerm : public ASTNode
{
public:
	void addOperator(string op);
	void addOperand(ASTNode* val);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	Register output(VariableContext* vc, ofstream& out);
private:
	vector<string> operators;
	vector<ASTNode*> operands;
};

class ASTExpr : public ASTNode
{
public:
	void addOperator(string op);
	void addOperand(ASTNode* val);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	Register output(VariableContext* vc, ofstream& out);
private:
	vector<string> operators;
	vector<ASTNode*> operands;
};

class ASTFactor : public ASTNode
{
public:
	void setBoolExpr(ASTNode* in);
	void setElement(ASTNode * in);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	ASTFactor();
	Register output(VariableContext* vc, ofstream& out);
private:
	ASTNode* element;
	ASTNode* boolExpr;
};

class ASTElement : public ASTNode
{
public:
	void setElement(string valuein, bool isFloatin);
	void print(int depth);
	Type typeCheck(TypeMap* map, FunctionParamMap* fmap, bool& hadError);
	Register output(VariableContext* vc, ofstream& out);
private:
	bool isFloat;
	string value;
};









