#ifndef SCANNER

#define SCANNER



#include <iostream>
#include <fstream>
using namespace std;

enum TokenType{ERROR, ENDOFFILE, LBRACE, RBRACE, SEMI, EQUALASSIGN,LPAREN,RPAREN, EE, GRE, GR, MULTIPLY,DIVIDE,PLUS,MINUS,MOD,COMMA,AND,OR,NOT, FLOAT, STRING,NONE /*this is for if the file is empty*/};

class Scanner
{
public:
	Scanner(string filename);

	TokenType currentTokenType();
	TokenType nextTokenType();
	string currentTokenString();
	string nextTokenString();

	void advance();

	void currentStatus();

	string toString(TokenType t);

	int getLine();
private:
	ifstream filestream;
	string currents;
	string nexts;
	TokenType currenttt;
	TokenType nexttt;

	void dealWithError(string buffer);

	int linenext;
	int linecurrent;
};

#endif // !