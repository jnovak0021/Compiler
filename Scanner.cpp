#include "Scanner.h"

#include <string>
using namespace std;

string Scanner::toString(TokenType t)
{
	if (t == NONE)
		return "NONE";
	if (t == PLUS)
		return "PLUS";
	if (t == MINUS)
		return "MINUS";
	if (t == EQUALASSIGN)
		return "EQL";
	if (t == LPAREN)
		return "LPAREN";
	if (t == RPAREN)
		return "RPAREN";
	if (t == LBRACE)
		return "LBRACE";
	if (t == RBRACE)
		return "RBRACE";
	if (t == FLOAT)
		return "FLOAT";
	if (t == EE)
		return "EE";
	if (t == GR)
		return "GR";
	if (t == GRE)
		return "GRE";
	if (t == MULTIPLY)
		return "MULTIPLY";
	if (t == DIVIDE)
		return "DIVIDE";
	if (t == MOD)
		return "MOD";
	if (t == COMMA)
		return "COMMA";
	if (t == NOT)
		return "NOT";
	if (t == AND)
		return "AND";
	if (t == OR)
		return "OR";
	if (t == STRING)
		return "STRING";
	if (t == SEMI)
		return "SEMI";
	if (t == ERROR)
		return "error: ";
	if (t == ENDOFFILE)
		return "eof: ";
	return "ERROR in tostring";
}

string Scanner::currentTokenString()
{
	return currents;
}

string Scanner::nextTokenString()
{
	return nexts;
}

TokenType Scanner::currentTokenType()
{
	return currenttt;
}

TokenType Scanner::nextTokenType()
{
	return nexttt;
}

void Scanner::currentStatus()
{
	cout << "CTT: " << toString(currentTokenType()) << "\n";
	cout << "CTS: " << currentTokenString() << "\n";
	cout << "NTT: " << toString(nextTokenType()) << "\n";
	cout << "NTS: " << nextTokenString() << "\n";
}

Scanner::Scanner(string fname)
{
	filestream.open(fname);

	linenext = 1;

	

	if (!filestream.good())
	{
		cout << "Could not open file: "<< fname<<"\n";
		return;
	}

	
	advance(); //fill up first slot
	advance(); //fill up second slot

	/*while (currentTokenType() != ENDOFFILE)
	{
		cout << toString(currentTokenType()) << " " << currentTokenString() << "\n";
		advance();
	}*/
}


void addToBuffer(string & buf, ifstream & stream)
{
	int next = stream.get();

	if (next == -1)
	{
		buf = buf + (char)0; //null signifies eof for today!
	}
	else
	{
		buf = buf + (char)next;
	}

}


void removeFromBuffer(string & buf, ifstream & stream)
{
	char last = buf.back();
	stream.putback(last);
	buf = buf.substr(0, buf.size() - 1);
	
}


bool isNum(char test)
{
	return (test == '0' || test == '1' || test == '2' || test == '3' || test == '4' || test == '5' || test == '6' || test == '7' || test == '8' || test == '9');
}

bool isLowerCharacter(char test)
{
	return (test == 'a' || test == 'b' || test == 'c' || test == 'd' ||
		test == 'e' || test == 'f' || test == 'g' || test == 'h' ||
		test == 'i' || test == 'j' || test == 'k' || test == 'l' ||
		test == 'm' || test == 'n' || test == 'o' || test == 'p' ||
		test == 'q' || test == 'r' || test == 's' || test == 't' ||
		test == 'u' || test == 'v' || test == 'w' || test == 'x' || test == 'y' || test == 'z' || test == '_');
}

bool isUpperCharacter(char test)
{
	return (test == 'A' || test == 'B' || test == 'C' || test == 'D' ||
		test == 'E' || test == 'F' || test == 'G' || test == 'H' ||
		test == 'I' || test == 'J' || test == 'K' || test == 'L' ||
		test == 'M' || test == 'N' || test == 'O' || test == 'P' ||
		test == 'Q' || test == 'R' || test == 'S' || test == 'T' ||
		test == 'U' || test == 'V' || test == 'W' || test == 'X' || test == 'Y' || test == 'Z');
}

bool isWhiteSpace(char test)
{
	return (test == ' ' || test == '\t' || test == '\n');
}




//advance places whatever is in the next variables into the current variables and finds what the next variables are supposed to be
void Scanner::advance()
{
	currents = nexts;
	currenttt = nexttt;
	linecurrent = linenext;


	//set that the scanner has not picked something yet. We will use this later on.
	nexttt = NONE;

	//holds what is currently read in but not yet processed
	string buffer;

	bool start = true;
	while (start)
	{
		start = false;

		buffer = "";

		//add the first thing to the buffer
		addToBuffer(buffer, filestream);

		
		//if the first thing is a {, then say we have an LBrace and set the string representation of it to "{"
		if (buffer[0] == '{')
		{
			nexttt = LBRACE;
			nexts = "{";
		}
		else if (buffer[0] == '}')
		{
			nexttt = RBRACE;
			nexts = "}";
		}
		else if (buffer[0] == '%')
		{
			nexttt = MOD;
			nexts = "%";
		}
		else if (buffer[0] == '(')
		{
			nexttt = LPAREN;
			nexts = "(";
		}
		else if (buffer[0] == ')')
		{
			nexttt = RPAREN;
			nexts = ")";
		}
		else if (buffer[0] == '+')
		{
			nexttt = PLUS;
			nexts = "+";
		}
		else if (buffer[0] == '&')
		{
			nexttt = AND;
			nexts = "&";
		}
		else if (buffer[0] == '|')
		{
			nexttt = OR;
			nexts = "|";
		}
		else if (buffer[0] == '/')
		{
			nexttt = DIVIDE;
			nexts = "/";
		}
		else if (buffer[0] == '*')
		{
			nexttt = MULTIPLY;
			nexts = "*";
		}
		else if (buffer[0] == '!')
		{
			nexttt = NOT;
			nexts = "!";
		}
		else if (buffer[0] == ',')
		{
			nexttt = COMMA;
			nexts = ",";
		}
		else if (buffer[0] == '=')
		{
			//this one is harder because you have to determine if you have an = or if you have ==

			addToBuffer(buffer, filestream);
			if (buffer[1] == '=') //check if both are =
			{
				//if yes then you know you have an ==
				nexttt = EE;
				nexts = "==";
			}
			else //otherwise remove the "bad" character from the buffer and just use =
			{
				removeFromBuffer(buffer, filestream);
				nexttt = EQUALASSIGN;
				nexts = "=";
			}
		}
		else if (buffer[0] == ';')
		{
			nexttt = SEMI;
			nexts = ";";
		}
		else if (buffer[0] == '>')
		{
			//> is the same as ==
			addToBuffer(buffer, filestream);
			if (buffer[1] == '=')
			{
				nexttt = GRE;
				nexts = ">=";
			}
			else
			{
				removeFromBuffer(buffer, filestream);
				nexttt = GR;
				nexts = ">";
			}
		}
		else if (buffer[0] == 0)
		{
			nexttt = ENDOFFILE;
			nexts = "eof";
		}//here is the string. It requres to start with a lowercase or uppercase (_ is marked as a lowercase letter) then the remainder can be lower/upper/ or nums
		else if (isLowerCharacter(buffer[0]) || isUpperCharacter(buffer[0]))
		{
			addToBuffer(buffer, filestream);
			while (isLowerCharacter(buffer[buffer.size() - 1]) || isUpperCharacter(buffer[buffer.size() - 1]) || isNum(buffer[buffer.size() - 1]))
			{
				addToBuffer(buffer, filestream);
			}
			removeFromBuffer(buffer, filestream);

			nexttt = STRING;
			nexts = buffer;
			
		}
		else
		{
			//so something else, basically, num, whitespace, and error are for here.

			//if starts with a - (or is a minus)
			if (buffer[0] == '-')
			{
				addToBuffer(buffer, filestream);
				if (! isNum(buffer[buffer.size() - 1])) //so single minus
				{
					removeFromBuffer(buffer, filestream);
					nexttt = MINUS;
					nexts = buffer;
				}
				else //so a negative number
				{
					while (isNum(buffer[buffer.size() - 1]))
					{
						addToBuffer(buffer, filestream);
					}
					
					if (buffer[buffer.size() - 1] == '.')
					{
						addToBuffer(buffer, filestream);

						if (!isNum(buffer[buffer.size() - 1]))
						{
							dealWithError(buffer);
							break;
						}
						while (isNum(buffer[buffer.size() - 1]))
						{
							addToBuffer(buffer, filestream);
						}
						removeFromBuffer(buffer, filestream);
						nexttt = FLOAT;
						nexts = buffer;

						
					}
					else
					{
						removeFromBuffer(buffer, filestream);
						nexttt = FLOAT;
						nexts = buffer;
					}
				}
			}
			//if starts with a number
			if (isNum(buffer[0]))
			{

				while (isNum(buffer[buffer.size() - 1]))
				{
					addToBuffer(buffer, filestream);
				}

				if (buffer[buffer.size() - 1] == '.')
				{
					addToBuffer(buffer, filestream);

					if (!isNum(buffer[buffer.size() - 1]))
					{
						dealWithError(buffer);
						break;
					}
					while (isNum(buffer[buffer.size() - 1]))
					{
						addToBuffer(buffer, filestream);
					}
					removeFromBuffer(buffer, filestream);
					nexttt = FLOAT;
					nexts = buffer;


				}
				else
				{
					removeFromBuffer(buffer, filestream);
					nexttt = FLOAT;
					nexts = buffer;
				}
				
			}

			//nothing matched so far
			if(nexttt == NONE)
			{
			
				//white space
				if (isWhiteSpace(buffer[0]))
				{
					while (isWhiteSpace(buffer[buffer.size() - 1]))
					{
						
						if (buffer[buffer.size() - 1] == '\n')
						{
							linenext++;
						}
						addToBuffer(buffer, filestream);
					}
					removeFromBuffer(buffer, filestream);
					start = true;
				}
				else
				{
					//or is an error character.
					dealWithError(buffer);
				}
			}
		}
	}
	/*cout << "***"<<endl;
	cout << linecurrent << " " << currentTokenString()<<endl;
	cout << linenext << " " << nextTokenString() << endl;
	cout << "***" << endl;*/
}

void Scanner::dealWithError(string buffer)
{
	while (!isWhiteSpace(buffer[buffer.size() - 1]) && buffer[buffer.size() - 1] != 0)
	{
		addToBuffer(buffer, filestream);
	}
	removeFromBuffer(buffer, filestream);
	nexttt = ERROR;
	nexts = "IT2: Invalid Token detected on line: " + to_string(linenext) + " [ " + buffer + " ]";
}

int Scanner::getLine()
{
	return linecurrent;
}