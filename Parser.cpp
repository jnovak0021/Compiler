#include "Parser.h"

void Parser::printError(string code, string message, int line)
{
	if(!errorDetected)
		cout << "Error: "<< code << " on line: " << line << " " << message << ". Recieved " << scan->toString(scan->currentTokenType()) << " \"" << scan->currentTokenString() << "\"." << endl;
	errorDetected = true;
}

Parser::Parser(string fname)
{
	scan = new Scanner(fname);
	errorDetected = false;
	program = 0;
}

bool Parser::getErrorDetected()
{
	return errorDetected;
}

ASTProgram* Parser::parse()
{
	program = rdpProgram();
	return program;
}

ASTProgram* Parser::rdpProgram()
{
	ASTProgram* theProg = new ASTProgram();
	theProg->setLine(scan->getLine());

	if (scan->currentTokenType() != STRING)
	{
		printError("ASTProgram02", "Expected String" + scan->toString(scan->currentTokenType()), scan->getLine());
	}

	while (scan->currentTokenType() == STRING) //notice we don't advance. You only advance when you are "eating" the terminal
	{
		theProg->addFunction(rdpFunction());
	}

	//so if its not a string and the final isn't empty...
	if (scan->currentTokenType() != NONE && scan->currentTokenType() != ENDOFFILE)
	{
		printError("ASTProgram01","Expected String or EOF recieved "+scan->toString(scan->currentTokenType()),scan->getLine());
	}
	return theProg;
}

ASTFunction* Parser::rdpFunction()
{
	//create the node
	ASTFunction* theFunction = new ASTFunction();
	theFunction->setLine(scan->getLine());

	//check that the first thing is a string
	string name;
	if (scan->currentTokenType() == STRING)
	{
		name = scan->currentTokenString(); //get it
		theFunction->setName(name); //set it
		scan->advance(); // advance the scanner to look at the next thing
	}
	else //if not a string through an error
	{
		printError("ASTFunction01", "Expected String for function name", scan->getLine());

		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}

	//eat the paren
	if (scan->currentTokenType() == LPAREN)
	{
		scan->advance();
	}
	else
	{
		printError("ASTFunction02", "Expected LPAREN for function name", scan->getLine());
		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}

	//call rdp param. I let param decide if there is any params to read.
	theFunction->setParam(rdpParam());

	//but notice that the function still eats the rparen
	if (scan->currentTokenType() == RPAREN)
	{
		scan->advance();
	}
	else
	{
		printError("ASTFunction03", "Expected RPAREN for function name", scan->getLine());
		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}


	//eat the lbrace
	if (scan->currentTokenType() == LBRACE)
	{
		scan->advance();
	}
	else
	{
		printError("ASTFunction04", "Expected LBRACE for function name", scan->getLine());
		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}



	//this is approximately the function my code has - the only change from part 1 to part 2
	theFunction->setStatements(rdpStatements());

	if (scan->currentTokenType() == RBRACE)
	{
		scan->advance();
	}
	else
	{
		printError("ASTFunction05", "Expected RBRACE for function name", scan->getLine());
		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}

	return theFunction;
}

ASTParam* Parser::rdpParam()
{
	ASTParam* params = new ASTParam();
	params->setLine(scan->getLine());

	while (scan->currentTokenType() == STRING)
	{
		string type = scan->currentTokenString();
		scan->advance();
		string name;
		if (scan->currentTokenType() == STRING)
		{
			name = scan->currentTokenString();
			scan->advance();
		}
		else
		{
			printError("ASTParams01", "Expected String for for param name", scan->getLine());

			scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
		}

		params->addParam(type, name);

		if (scan->currentTokenType() == COMMA)
		{
			scan->advance();
		}
		else if (scan->currentTokenType() == RPAREN)
		{
			//handled by astfunction
		}
		else
		{
			printError("ASTParams02", "Expected COMMA or RPAREN", scan->getLine());
			scan->advance(); // always advance in an error, otherwise you might get stuck in a loop

		}
	}

	return params;
}

//use scan->currentStatus(); to see the scanner's current status (what it is looking at)

ASTStatements* Parser::rdpStatements()
{
	ASTStatements* node = new ASTStatements();
	node->setLine(scan->getLine());

	while (scan->currentTokenType() != ENDOFFILE && scan->currentTokenType() != RBRACE)
	{

		node->addStatement(rdpStatement());
	}

	return node;
}

ASTStatement* Parser::rdpStatement()
{
	ASTStatement* stmt = new ASTStatement();
	stmt->setLine(scan->getLine());

	if (scan->currentTokenString() == "if")
	{
		stmt->setStatement(rdpIf());
	}
	else if (scan->currentTokenString() == "while")
	{
		stmt->setStatement(rdpWhile());
	}
	else if (scan->currentTokenType() == STRING && scan->nextTokenType() == STRING) //declaration
	{
		stmt->setStatement(rdpDeclaration());
	}
	else if (scan->currentTokenType() == STRING && scan->nextTokenType() == LPAREN) //function call
	{
		stmt->setStatement(rdpFunctionCall());
	}
	else if (scan->currentTokenType() == STRING && scan->nextTokenType() == EQUALASSIGN) //assign
	{
		stmt->setStatement(rdpAssign());
	}
	else if (scan->currentTokenString() == "{")
	{
		stmt->setStatement(rdpBlockStatement());
	}
	else
	{
		printError("rdpStatement01", "Expected start of statement", scan->getLine());

		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}

	return stmt;
}

ASTArgs* Parser::rdpArgs()
{
	ASTArgs* args = new ASTArgs();
	args->setLine(scan->getLine());

	while (scan->currentTokenType() != RPAREN && scan->currentTokenType() != ENDOFFILE)
	{
		args->addArg(rdpBooleanExprA());

		if (scan->currentTokenType() == COMMA)
		{
			scan->advance();
		}
		else if (scan->currentTokenType() == RPAREN)
		{
			//handled by astfunctioncall
		}
		else
		{
			printError("ASTargs01", "Expected COMMA or RPAREN", scan->getLine());
			scan->advance(); // always advance in an error, otherwise you might get stuck in a loop

		}
	}

	return args;
}

ASTIf* Parser::rdpIf()
{
	ASTIf* ifnode = new ASTIf();
	ifnode->setLine(scan->getLine());

	string name;
	if (scan->currentTokenString() == "if")
	{
		scan->advance(); // advance the scanner to look at the next thing
	}
	else //if not a string through an error
	{
		printError("rdpif01", "Expected if", scan->getLine());

		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}

	if (scan->currentTokenType() == LPAREN)
	{
		scan->advance(); // advance the scanner to look at the next thing
	}
	else //if not a string through an error
	{
		printError("rdpif02", "Expected (", scan->getLine());

		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}

	ifnode->setCondition(rdpBooleanExprA());

	if (scan->currentTokenType() == RPAREN)
	{
		scan->advance(); // advance the scanner to look at the next thing
	}
	else //if not a string through an error
	{
		printError("rdpif03", "Expected )", scan->getLine());

		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}

	ifnode->setStatement(rdpStatement());

	return ifnode;
}

ASTWhile* Parser::rdpWhile()
{
	ASTWhile* ifnode = new ASTWhile();
	ifnode->setLine(scan->getLine());

	string name;
	if (scan->currentTokenString() == "while")
	{
		scan->advance(); // advance the scanner to look at the next thing
	}
	else //if not a string through an error
	{
		printError("rdpwhile01", "Expected while", scan->getLine());

		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}

	if (scan->currentTokenType() == LPAREN)
	{
		scan->advance(); // advance the scanner to look at the next thing
	}
	else //if not a string through an error
	{
		printError("rdpwhile02", "Expected (", scan->getLine());

		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}

	ifnode->setCondition(rdpBooleanExprA());

	if (scan->currentTokenType() == RPAREN)
	{
		scan->advance(); // advance the scanner to look at the next thing
	}
	else //if not a string through an error
	{
		printError("rdpwhile03", "Expected )", scan->getLine());

		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}

	ifnode->setStatement(rdpStatement());

	return ifnode;
}


ASTAssign* Parser::rdpAssign()
{
	ASTAssign* assign = new ASTAssign();
	assign->setLine(scan->getLine());

	string name;
	if (scan->currentTokenType() == STRING)
	{
		name = scan->currentTokenString(); //get it
		assign->setLHS(name); //set it
		scan->advance(); // advance the scanner to look at the next thing
	}
	else //if not a string through an error
	{
		printError("rdpAssign01", "Expected String for variable name", scan->getLine());

		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}

	if (scan->currentTokenType() == EQUALASSIGN)
	{
		scan->advance(); // advance the scanner to look at the next thing
	}
	else //if not a string through an error
	{
		printError("rdpAssign02", "Expected = for assign name", scan->getLine());

		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}

	assign->setRHS(rdpBooleanExprA());

	if (scan->currentTokenType() == SEMI)
	{
		scan->advance(); // advance the scanner to look at the next thing
	}
	else //if not a string through an error
	{
		printError("rdpAssign03", "Expected ; after RHS", scan->getLine());

		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}

	return assign;
}


ASTFunctionCall* Parser::rdpFunctionCall()
{
	ASTFunctionCall* fcall = new ASTFunctionCall();
	fcall->setLine(scan->getLine());

	string name;
	if (scan->currentTokenType() == STRING)
	{
		name = scan->currentTokenString(); //get it
		fcall->setName(name); //set it
		scan->advance(); // advance the scanner to look at the next thing
	}
	else //if not a string through an error
	{
		printError("rdpFunctionCall01", "Expected String for function name", scan->getLine());

		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}

	if (scan->currentTokenType() == LPAREN)
	{
		scan->advance(); // advance the scanner to look at the next thing
	}
	else //if not a string through an error
	{
		printError("rdpFunctionCall02", "Expected (", scan->getLine());

		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}

	fcall->setParam(rdpArgs());

	if (scan->currentTokenType() == RPAREN)
	{
		scan->advance(); // advance the scanner to look at the next thing
	}
	else //if not a string through an error
	{
		printError("rdpFunctionCall03", "Expected )", scan->getLine());

		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}

	if (scan->currentTokenType() == SEMI)
	{
		scan->advance(); // advance the scanner to look at the next thing
	}
	else //if not a string through an error
	{
		printError("rdpFunctionCall04", "Expected ; after RHS", scan->getLine());

		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}

	return fcall;
}


ASTBlockStatement* Parser::rdpBlockStatement()
{
	ASTBlockStatement* bstatmeent = new ASTBlockStatement();
	bstatmeent->setLine(scan->getLine());

	if (scan->currentTokenType() == LBRACE)
	{
		scan->advance(); // advance the scanner to look at the next thing
	}
	else //if not a string through an error
	{
		printError("rdpBlockStatement01", "Expected {", scan->getLine());

		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}

	bstatmeent->setStatement(rdpStatements());

	if (scan->currentTokenType() == RBRACE)
	{
		scan->advance(); // advance the scanner to look at the next thing
	}
	else //if not a string through an error
	{
		printError("rdpBlockStatement02", "Expected }", scan->getLine());

		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}

	
	return bstatmeent;
}


ASTDeclaration* Parser::rdpDeclaration()
{
	ASTDeclaration* declaration = new ASTDeclaration();
	declaration->setLine(scan->getLine());

	string name,type;

	if (scan->currentTokenType() == STRING)
	{
		type = scan->currentTokenString(); //get it
		declaration->setType(type); //set it
		scan->advance(); // advance the scanner to look at the next thing
	}
	else //if not a string through an error
	{
		printError("rdpDeclaration02", "Expected String for variable type", scan->getLine());

		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}

	if (scan->currentTokenType() == STRING)
	{
		name = scan->currentTokenString(); //get it
		declaration->setName(name); //set it
		scan->advance(); // advance the scanner to look at the next thing
	}
	else //if not a string through an error
	{
		printError("rdpDeclaration01", "Expected String for variable name", scan->getLine());

		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}

	if (scan->currentTokenType() == EQUALASSIGN)
	{
		if (scan->currentTokenType() == EQUALASSIGN)
		{
			scan->advance(); // advance the scanner to look at the next thing
		}
		else //if not a string through an error
		{
			printError("rdpDeclaration04", "Expected =", scan->getLine());

			scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
		}

		declaration->setVal(rdpBooleanExprA());
	}

	if (scan->currentTokenType() == SEMI)
	{
		scan->advance(); // advance the scanner to look at the next thing
	}
	else //if not a string through an error
	{
		printError("rdpDeclaration03", "Expected ;", scan->getLine());

		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}

	return declaration;
}


ASTBooleanExprA* Parser::rdpBooleanExprA()
{
	ASTBooleanExprA* node = new ASTBooleanExprA();
	node->setLine(scan->getLine());

	node->addOperand(rdpBooleanExprB());

	while((scan->currentTokenType() == AND) || (scan->currentTokenType() == OR))
	{
		node->addOperator(scan->currentTokenString());

		scan->advance();

		node->addOperand(rdpBooleanExprB());
	}
	return node;
}

ASTBooleanExprB* Parser::rdpBooleanExprB()
{
	ASTBooleanExprB* node = new ASTBooleanExprB();
	node->setLine(scan->getLine());

	node->addOperand(rdpTerm());

	while ((scan->currentTokenType() == EE) || (scan->currentTokenType() == GR) || (scan->currentTokenType() == GRE))
	{
		node->addOperator(scan->currentTokenString());

		scan->advance();

		node->addOperand(rdpTerm());
	}

	return node;
}


ASTTerm* Parser::rdpTerm()
{
	ASTTerm* node = new ASTTerm();
	node->setLine(scan->getLine());

	node->addOperand(rdpExpr());

	while ((scan->currentTokenType() == PLUS) || (scan->currentTokenType() == MINUS))
	{
		node->addOperator(scan->currentTokenString());

		scan->advance();

		node->addOperand(rdpExpr());
	}

	return node;
}

ASTExpr* Parser::rdpExpr()
{
	ASTExpr* node = new ASTExpr();
	node->setLine(scan->getLine());

	node->addOperand(rdpFactor());

	while ((scan->currentTokenType() == MULTIPLY) || (scan->currentTokenType() == DIVIDE) || (scan->currentTokenType() == MOD))
	{
		node->addOperator(scan->currentTokenString());

		scan->advance();

		node->addOperand(rdpFactor());
	}

	return node;
}



ASTFactor* Parser::rdpFactor()
{
	ASTFactor* theFact = new ASTFactor();
	theFact->setLine(scan->getLine());

	if (scan->currentTokenType() == STRING || scan->currentTokenType() == FLOAT)
	{
		theFact->setElement(rdpElement());
	}
	else if (scan->currentTokenType() == LPAREN)
	{
		scan->advance();

		theFact->setBoolExpr(rdpBooleanExprA());

		if (scan->currentTokenType() == RPAREN)
		{
			scan->advance(); //so eat it
		}
		else
		{
			printError("ASTFactor02", "Expected Rparen after element", scan->getLine());
			scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
		}
	}
	else
	{
		printError("ASTFactor01", "Expected String or Lparen", scan->getLine());
		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop

	}

	return theFact;
}

ASTElement* Parser::rdpElement()
{
	ASTElement* theElement = new ASTElement();
	theElement->setLine(scan->getLine());

	if (scan->currentTokenType() == STRING)
	{
		theElement->setElement(scan->currentTokenString(), false);

		scan->advance(); //so eat it
	}
	else if (scan->currentTokenType() == FLOAT)
	{
		theElement->setElement(scan->currentTokenString(), true);

		scan->advance(); //so eat it
	}
	else
	{
		printError("ASTElement01", "Expected STRING or FLOAT", scan->getLine());
		scan->advance(); // always advance in an error, otherwise you might get stuck in a loop
	}

	return theElement;
}