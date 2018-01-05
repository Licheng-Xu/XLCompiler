#include "head.h"
#include <cstdlib>

void buildTable(node* root, Table& table)
{
	if ((root->nodeName) == "Sdecl")
	{
		string type;
		if (root->children[0]->nodeName == "TI") 
			type = "int";
		else 
			type = "char";
		addItem(root->children[1], table, type);
	}
	else
	{
		for (int i = 0; i < 4; i++)
			if (root->children[i] != NULL)
				buildTable(root->children[i], table);
	}
}

void addItem(node* root, Table& table, string type)
{
	if ((root->nodeName)[0] == 'I')
	{
		string name(root->nodeName, 1);
		if (table.find(name) > 0)
		{
			cout << "Line " << root->lineno << ", Redeclare Error: ID \"" << name << "\"." << endl;
			exit(0);
		}
		else table.add(type, name);
		root->nodeType = type;
	}
	else
	{
		for (int i = 0; i < 4; i++)
			if (root->children[i] != NULL)
				addItem(root->children[i], table, type);
	}
}

void checkNoDecl(node* root, Table table)
{
	if ((root->nodeName)[0] == 'N')
	{
		if (root->nodeName == "NI") root->nodeType = "INT";
		else root->nodeType = "CHAR";
	}
	if (((root->nodeName)[0] == 'I') && (root->nodeType == ""))
	{
		string name(root->nodeName, 1);
		if (table.find(name) == -1)
		{
			cout << "Line " << root->lineno << ", Nodeclare Error: ID \"" << name << "\"" << endl;
			exit(0);
		}
		else
		{
			root->nodeType = ((table.items)[table.find(name)]).type;
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
			if (root->children[i] != NULL)
				checkNoDecl(root->children[i], table);
	}
}

void checkExprMatch(node* root, Table table)
{
	if (root->children[0] != NULL) checkExprMatch(root->children[0], table);
	if (root->children[1] != NULL) checkExprMatch(root->children[1], table);

	string exprKind = root->nodeName;
	if ((exprKind == "Eincp") || (exprKind == "Edecp") || (exprKind == "Eincb") || (exprKind == "Edecb"))
	{
		node* child = root->children[0];
		if ((child->nodeType == "int") || (child->nodeType == "char"))
		{
			root->nodeType = child->nodeType;
		}
		else
		{
			cout << "Line " << root->lineno << ", Type Error.(++, --)" << endl;
			exit(0);
		}
	}
	else if ((exprKind == "Eadd") || (exprKind == "Esub") || (exprKind == "Emul") || (exprKind == "Ediv") || (exprKind == "Emod") || (exprKind == "Ebitand") || (exprKind == "Ebitor") || (exprKind == "Ebitxor"))
	{
		string LchildType = root->children[0]->nodeType;
		string RchildType = root->children[1]->nodeType;
		char L, R;
		if ((LchildType == "INT") || (LchildType == "int")) L = 'i';
		if ((LchildType == "CHAR") || (LchildType == "char")) L = 'c';
		if ((RchildType == "INT") || (RchildType == "int")) R = 'i';
		if ((RchildType == "CHAR") || (RchildType == "char")) R = 'c';
		if (L == R)
		{
			if ((LchildType == "INT") && (RchildType == "INT")) root->nodeType = "INT";
			else if ((LchildType == "CHAR") && (RchildType == "CHAR")) root->nodeType = "CHAR";
			else if (L == 'i') root->nodeType = "int";
			else if (L == 'c') root->nodeType = "char";
		}
		else
		{
			cout << "Line " << root->lineno << ", Type Error.(+, -, *, /, %, |, &, ^)" << endl;
			exit(0);
		}
	}
	else if ((exprKind == "Eshl") || (exprKind == "Eshr"))
	{
		string LchildType = root->children[0]->nodeType;
		string RchildType = root->children[1]->nodeType;
		char L, R;
		if ((LchildType == "INT") || (LchildType == "int")) L = 'i';
		if ((LchildType == "CHAR") || (LchildType == "char")) L = 'c';
		if ((RchildType == "INT") || (RchildType == "int")) R = 'i';
		if ((RchildType == "CHAR") || (RchildType == "char")) R = 'c';
		if (L == R)
		{
			root->nodeType = LchildType;
		}
		else
		{
			cout << "Line " << root->lineno << ", Type Error.(<<, >>)" << endl;
			exit(0);
		}
	}
	else if ((exprKind == "Ebitnot") || (exprKind == "Eneg"))
	{
		root->nodeType = root->children[0]->nodeType;
	}
	else if ((exprKind == "El") || (exprKind == "Eg") || (exprKind == "Ele") || (exprKind == "Ege") || (exprKind == "Eeq") || (exprKind == "Ene") || (exprKind == "Eor") || (exprKind == "Eand"))
	{
		string LchildType = root->children[0]->nodeType;
		string RchildType = root->children[1]->nodeType;
		char L, R;
		if ((LchildType == "INT") || (LchildType == "int")) L = 'i';
		if ((LchildType == "CHAR") || (LchildType == "char")) L = 'c';
		if ((RchildType == "INT") || (RchildType == "int")) R = 'i';
		if ((RchildType == "CHAR") || (RchildType == "char")) R = 'c';
		if (L == R)
		{
			root->nodeType = "INT";
		}
		else
		{
			cout << "Line " << root->lineno << ", Type Error.(<, >, <=, >=, ==, !=)" << endl;
			exit(0);
		}
	}
	else if ((exprKind == "Eor") || (exprKind == "Eand"))
	{
		string LchildType = root->children[0]->nodeType;
		string RchildType = root->children[1]->nodeType;
		char L, R;
		if ((LchildType == "INT") || (LchildType == "int")) L = 'i';
		if ((LchildType == "CHAR") || (LchildType == "char")) L = 'c';
		if ((RchildType == "INT") || (RchildType == "int")) R = 'i';
		if ((RchildType == "CHAR") || (RchildType == "char")) R = 'c';
		if (L == R)
		{
			if (L == 'i') root->nodeType = "INT";
			else
			{
				cout << "Line " << root->lineno << ", Bool-Char Error.(&&, ||)" << endl;
				exit(0);
			}
		}
		else
		{
			cout << "Line " << root->lineno << ", Type Error.(&&, ||)" << endl;
			exit(0);
		}
	}
	else if ((exprKind == "Enot"))
	{
		string childType = root->children[0]->nodeType;
		if ((childType == "INT") || (childType == "int"))
		{
			root->nodeType = "INT";
		}
		else
		{
			cout << "Line " << root->lineno << ", Bool-Char Error.(!)" << endl;
			exit(0);
		}
	}
	else if ((exprKind == "Easgn"))
	{
		string LchildType = root->children[0]->nodeType;
		string RchildType = root->children[1]->nodeType;
		char R;
		if ((RchildType == "INT") || (RchildType == "int")) R = 'i';
		if ((RchildType == "CHAR") || (RchildType == "char")) R = 'c';
		if ((LchildType == "int") && (R == 'i'))
		{
			root->nodeType = "int";
		}
		else if ((LchildType == "char") && (R == 'c'))
		{
			root->nodeType = "char";
		}
		else
		{
			cout << "Line " << root->lineno << ", Assign Error." << endl;
			exit(0);
		}
	}
}

void checkMatch(node* root, Table table)
{
	if ((root->nodeName)[0] == 'E')
	{
		checkExprMatch(root, table);
	}
	if (root->nodeName == "Dasgn")
	{
		checkExprMatch(root->children[1], table);
		string LchildType = root->children[0]->nodeType;
		string RchildType = root->children[1]->nodeType;
		char R;
		if ((RchildType == "INT") || (RchildType == "int")) R = 'i';
		if ((RchildType == "CHAR") || (RchildType == "char")) R = 'c';
		if ((LchildType == "int") && (R == 'i'))
		{
			root->nodeType = "int";
		}
		else if ((LchildType == "char") && (R == 'c'))
		{
			root->nodeType = "char";
		}
		else
		{
			cout << "Line " << root->lineno << ", Initialize Error." << endl;
			exit(0);
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
			if (root->children[i] != NULL)
				checkMatch(root->children[i], table);
	}
}

void checkTree(node* root, Table& table)
{
	buildTable(root, table);
	checkNoDecl(root, table);
	checkMatch(root, table);
}