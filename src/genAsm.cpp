#include "head.h"

void genExpr(node* root, Table table)
{
	for (int i = 0; i < 4; i++)
		if (root->children[i] != NULL)
			genExpr(root->children[i], table);

	if ((root->nodeName)[0] == 'N')
	{
		cout << "\tmov _Node" << root->nodeId << ", " << root->value << endl;
	}
	else if ((root->nodeName)[0] == 'I')
	{
		string name(root->nodeName, 1);
		TableItem item = (table.items)[table.find(name)];
		if (item.type == "int")
		{
			cout << "\tmov eax, _" << item.name << endl;
			cout << "\tmov _Node" << root->nodeId << ", eax" << endl;
		}
		else if (item.type == "char")
		{
			cout << "\tmov ax, _" << item.name << endl;
			cout << "\tmov _Node" << root->nodeId << ", ax" << endl;
		}
	}
	else if (root->nodeName == "Eadd")
	{
		if ((root->nodeType == "INT") || (root->nodeType == "int"))
		{
			cout << "\tmov eax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tadd eax, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", eax" << endl;
		}
		else if ((root->nodeType == "CHAR") || (root->nodeType == "char"))
		{
			cout << "\tmov ax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tadd ax, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", ax" << endl;
		}
	}
	else if (root->nodeName == "Esub")
	{
		if ((root->nodeType == "INT") || (root->nodeType == "int"))
		{
			cout << "\tmov eax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tsub eax, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", eax" << endl;
		}
		else if ((root->nodeType == "CHAR") || (root->nodeType == "char"))
		{
			cout << "\tmov ax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tsub ax, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", ax" << endl;
		}
	}
	else if (root->nodeName == "Emul")
	{
		if ((root->nodeType == "INT") || (root->nodeType == "int"))
		{
			cout << "\tmov eax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov ebx, _Node" << root->children[1]->nodeId << endl;
			cout << "\timul ebx" << endl;
			cout << "\tmov _Node" << root->nodeId << ", eax" << endl;
		}
		else if ((root->nodeType == "CHAR") || (root->nodeType == "char"))
		{
			cout << "\tmov ax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov bx, _Node" << root->children[1]->nodeId << endl;
			cout << "\timul bx" << endl;
			cout << "\tmov _Node" << root->nodeId << ", ax" << endl;
		}
	}
	else if (root->nodeName == "Ediv")
	{
		if ((root->nodeType == "INT") || (root->nodeType == "int"))
		{
			cout << "\tmov eax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov ebx, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov edx, 0" << endl;
			cout << "\tidiv ebx" << endl;
			cout << "\tmov _Node" << root->nodeId << ", eax" << endl;
		}
		else if ((root->nodeType == "CHAR") || (root->nodeType == "char"))
		{
			cout << "\tmov ax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov bx, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov dx, 0" << endl;
			cout << "\tidiv bx" << endl;
			cout << "\tmov _Node" << root->nodeId << ", ax" << endl;
		}
	}
	else if (root->nodeName == "Emod")
	{
		if ((root->nodeType == "INT") || (root->nodeType == "int"))
		{
			cout << "\tmov eax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov ebx, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov edx, 0" << endl;
			cout << "\tidiv ebx" << endl;
			cout << "\tmov _Node" << root->nodeId << ", edx" << endl;
		}
		else if ((root->nodeType == "CHAR") || (root->nodeType == "char"))
		{
			cout << "\tmov ax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov bx, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov dx, 0" << endl;
			cout << "\tidiv bx" << endl;
			cout << "\tmov _Node" << root->nodeId << ", dx" << endl;
		}
	}
	else if (root->nodeName == "Eshl")
	{
		if ((root->nodeType == "INT") || (root->nodeType == "int"))
		{
			cout << "\tmov eax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tshl eax, " << root->children[1]->value << endl;
			cout << "\tmov _Node" << root->nodeId << ", eax" << endl;
		}
		else if ((root->nodeType == "CHAR") || (root->nodeType == "char"))
		{
			cout << "\tmov ax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tshl ax, " << root->children[1]->value << endl;
			cout << "\tmov _Node" << root->nodeId << ", ax" << endl;
		}
	}
	else if (root->nodeName == "Eshr")
	{
		if ((root->nodeType == "INT") || (root->nodeType == "int"))
		{
			cout << "\tmov eax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tshr eax, " << root->children[1]->value << endl;
			cout << "\tmov _Node" << root->nodeId << ", eax" << endl;
		}
		else if ((root->nodeType == "CHAR") || (root->nodeType == "char"))
		{
			cout << "\tmov ax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tshr ax, " << root->children[1]->value << endl;
			cout << "\tmov _Node" << root->nodeId << ", ax" << endl;
		}
	}
	else if (root->nodeName == "Ebitand")
	{
		if ((root->nodeType == "INT") || (root->nodeType == "int"))
		{
			cout << "\tmov eax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov ebx, _Node" << root->children[1]->nodeId << endl;
			cout << "\tand eax, ebx" << endl;
			cout << "\tmov _Node" << root->nodeId << ", eax" << endl;
		}
		else if ((root->nodeType == "CHAR") || (root->nodeType == "char"))
		{
			cout << "\tmov ax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov bx, _Node" << root->children[1]->nodeId << endl;
			cout << "\tand ax, bx" << endl;
			cout << "\tmov _Node" << root->nodeId << ", ax" << endl;
		}
	}
	else if (root->nodeName == "Ebitor")
	{
		if ((root->nodeType == "INT") || (root->nodeType == "int"))
		{
			cout << "\tmov eax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov ebx, _Node" << root->children[1]->nodeId << endl;
			cout << "\tor eax, ebx" << endl;
			cout << "\tmov _Node" << root->nodeId << ", eax" << endl;
		}
		else if ((root->nodeType == "CHAR") || (root->nodeType == "char"))
		{
			cout << "\tmov ax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov bx, _Node" << root->children[1]->nodeId << endl;
			cout << "\tor ax, bx" << endl;
			cout << "\tmov _Node" << root->nodeId << ", ax" << endl;
		}
	}
	else if (root->nodeName == "Ebitxor")
	{
		if ((root->nodeType == "INT") || (root->nodeType == "int"))
		{
			cout << "\tmov eax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov ebx, _Node" << root->children[1]->nodeId << endl;
			cout << "\txor eax, ebx" << endl;
			cout << "\tmov _Node" << root->nodeId << ", eax" << endl;
		}
		else if ((root->nodeType == "CHAR") || (root->nodeType == "char"))
		{
			cout << "\tmov ax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov bx, _Node" << root->children[1]->nodeId << endl;
			cout << "\txor ax, bx" << endl;
			cout << "\tmov _Node" << root->nodeId << ", ax" << endl;
		}
	}
	else if (root->nodeName == "Ebitnot")
	{
		if ((root->nodeType == "INT") || (root->nodeType == "int"))
		{
			cout << "\tmov eax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tnot eax" << endl;
			cout << "\tmov _Node" << root->nodeId << ", eax" << endl;
		}
		else if ((root->nodeType == "CHAR") || (root->nodeType == "char"))
		{
			cout << "\tmov ax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tnot ax" << endl;
			cout << "\tmov _Node" << root->nodeId << ", ax" << endl;
		}
	}
	else if (root->nodeName == "Eeq")
	{
		if ((root->children[0]->nodeType == "INT") || (root->children[0]->nodeType == "int"))
		{
			cout << "\tmov eax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov ebx, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 1" << endl;
			cout << "\tcmp eax, ebx" << endl;
			cout << "\tje @" << root->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 0" << endl;
			cout << "@" << root->nodeId << ":" << endl;
		}
		else if ((root->children[0]->nodeType == "CHAR") || (root->children[0]->nodeType == "char"))
		{
			cout << "\tmov ax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov bx, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 1" << endl;
			cout << "\tcmp ax, bx" << endl;
			cout << "\tje @" << root->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 0" << endl;
			cout << "@" << root->nodeId << ":" << endl;
		}
	}
	else if (root->nodeName == "Ene")
	{
		if ((root->children[0]->nodeType == "INT") || (root->children[0]->nodeType == "int"))
		{
			cout << "\tmov eax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov ebx, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 1" << endl;
			cout << "\tcmp eax, ebx" << endl;
			cout << "\tjne @" << root->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 0" << endl;
			cout << "@" << root->nodeId << ":" << endl;
		}
		else if ((root->children[0]->nodeType == "CHAR") || (root->children[0]->nodeType == "char"))
		{
			cout << "\tmov ax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov bx, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 1" << endl;
			cout << "\tcmp ax, bx" << endl;
			cout << "\tjne @" << root->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 0" << endl;
			cout << "@" << root->nodeId << ":" << endl;
		}
	}
	else if (root->nodeName == "Eg")
	{
		if ((root->children[0]->nodeType == "INT") || (root->children[0]->nodeType == "int"))
		{
			cout << "\tmov eax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov ebx, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 1" << endl;
			cout << "\tcmp eax, ebx" << endl;
			cout << "\tjg @" << root->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 0" << endl;
			cout << "@" << root->nodeId << ":" << endl;
		}
		else if ((root->children[0]->nodeType == "CHAR") || (root->children[0]->nodeType == "char"))
		{
			cout << "\tmov ax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov bx, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 1" << endl;
			cout << "\tcmp ax, bx" << endl;
			cout << "\tjg @" << root->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 0" << endl;
			cout << "@" << root->nodeId << ":" << endl;
		}
	}
	else if (root->nodeName == "El")
	{
		if ((root->children[0]->nodeType == "INT") || (root->children[0]->nodeType == "int"))
		{
			cout << "\tmov eax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov ebx, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 1" << endl;
			cout << "\tcmp eax, ebx" << endl;
			cout << "\tjl @" << root->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 0" << endl;
			cout << "@" << root->nodeId << ":" << endl;
		}
		else if ((root->children[0]->nodeType == "CHAR") || (root->children[0]->nodeType == "char"))
		{
			cout << "\tmov ax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov bx, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 1" << endl;
			cout << "\tcmp ax, bx" << endl;
			cout << "\tjl @" << root->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 0" << endl;
			cout << "@" << root->nodeId << ":" << endl;
		}
	}
	else if (root->nodeName == "Ege")
	{
		if ((root->children[0]->nodeType == "INT") || (root->children[0]->nodeType == "int"))
		{
			cout << "\tmov eax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov ebx, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 1" << endl;
			cout << "\tcmp eax, ebx" << endl;
			cout << "\tjge @" << root->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 0" << endl;
			cout << "@" << root->nodeId << ":" << endl;
		}
		else if ((root->children[0]->nodeType == "CHAR") || (root->children[0]->nodeType == "char"))
		{
			cout << "\tmov ax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov bx, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 1" << endl;
			cout << "\tcmp ax, bx" << endl;
			cout << "\tjge @" << root->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 0" << endl;
			cout << "@" << root->nodeId << ":" << endl;
		}
	}
	else if (root->nodeName == "Ele")
	{
		if ((root->children[0]->nodeType == "INT") || (root->children[0]->nodeType == "int"))
		{
			cout << "\tmov eax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov ebx, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 1" << endl;
			cout << "\tcmp eax, ebx" << endl;
			cout << "\tjle @" << root->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 0" << endl;
			cout << "@" << root->nodeId << ":" << endl;
		}
		else if ((root->children[0]->nodeType == "CHAR") || (root->children[0]->nodeType == "char"))
		{
			cout << "\tmov ax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov bx, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 1" << endl;
			cout << "\tcmp ax, bx" << endl;
			cout << "\tjle @" << root->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 0" << endl;
			cout << "@" << root->nodeId << ":" << endl;
		}
	}
	else if (root->nodeName == "Eor")
	{
		if ((root->children[0]->nodeType == "INT") || (root->children[0]->nodeType == "int"))
		{
			cout << "\tmov eax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov ebx, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 1" << endl;
			cout << "\tcmp eax, 0" << endl;
			cout << "\tjne @" << root->nodeId << endl;
			cout << "\tcmp ebx, 0" << endl;
			cout << "\tjne @" << root->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 0" << endl;
			cout << "@" << root->nodeId << ":" << endl;
		}
	}
	else if (root->nodeName == "Eand")
	{
		if ((root->children[0]->nodeType == "INT") || (root->children[0]->nodeType == "int"))
		{
			cout << "\tmov eax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov ebx, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 0" << endl;
			cout << "\tcmp eax, 0" << endl;
			cout << "\tje @" << root->nodeId << endl;
			cout << "\tcmp ebx, 0" << endl;
			cout << "\tje @" << root->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 1" << endl;
			cout << "@" << root->nodeId << ":" << endl;
		}
	}
	else if (root->nodeName == "Enot")
	{
		if ((root->children[0]->nodeType == "INT") || (root->children[0]->nodeType == "int"))
		{
			cout << "\tmov eax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 0" << endl;
			cout << "\tcmp eax, 0" << endl;
			cout << "\tjne @" << root->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", 1" << endl;
			cout << "@" << root->nodeId << ":" << endl;
		}
	}
	else if (root->nodeName == "Eneg")
	{
		if ((root->children[0]->nodeType == "INT") || (root->children[0]->nodeType == "int"))
		{
			cout << "\tmov eax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tneg eax" << endl;
			cout << "\tmov _Node" << root->nodeId << ", eax" << endl;
		}
		else if ((root->children[0]->nodeType == "CHAR") || (root->children[0]->nodeType == "char"))
		{
			cout << "\tmov ax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tneg ax" << endl;
			cout << "\tmov _Node" << root->nodeId << ", ax" << endl;
		}
	}
	else if (root->nodeName == "Easgn")
	{
		string idName(root->children[0]->nodeName, 1);
		string idType = (table.items)[table.find(idName)].type;
		if (idType == "int")
		{
			cout << "\tmov eax, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov _" << idName << ", eax" << endl;
		}
		else if (idType == "char")
		{
			cout << "\tmov ax, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov _" << idName << ", ax" << endl;
		}
	}
	else if ((root->nodeName == "Eincp") || (root->nodeName == "Edecp") || (root->nodeName == "Eincb") || (root->nodeName == "Edecb"))
	{
		if (root->children[0]->nodeType == "int")
		{
			cout << "\tmov eax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", eax" << endl;
		}
		else if (root->children[0]->nodeType == "char")
		{
			cout << "\tmov ax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tmov _Node" << root->nodeId << ", ax" << endl;
		}
	}
}

void genPre(node* root, Table table)
{
	for (int i = 0; i < 4; i++)
		if (root->children[i] != NULL)
			genPre(root->children[i], table);
	if (root->nodeName == "Eincp")
	{
		string idName(root->children[0]->nodeName, 1);
		string idType = (table.items)[table.find(idName)].type;
		if (idType == "int")
		{
			cout << "\tmov eax, _" << idName << endl;
			cout << "\tinc eax" << endl;
			cout << "\tmov _" << idName << ", eax" << endl;
		}
		else if (idType == "char")
		{
			cout << "\tmov ax, _" << idName << endl;
			cout << "\tinc ax" << endl;
			cout << "\tmov _" << idName << ", ax" << endl;
		}
	}
	if (root->nodeName == "Edecp")
	{
		string idName(root->children[0]->nodeName, 1);
		string idType = (table.items)[table.find(idName)].type;
		if (idType == "int")
		{
			cout << "\tmov eax, _" << idName << endl;
			cout << "\tdec eax" << endl;
			cout << "\tmov _" << idName << ", eax" << endl;
		}
		else if (idType == "char")
		{
			cout << "\tmov ax, _" << idName << endl;
			cout << "\tdec ax" << endl;
			cout << "\tmov _" << idName << ", ax" << endl;
		}
	}
}

void genPost(node* root, Table table)
{
	for (int i = 0; i < 4; i++)
		if (root->children[i] != NULL)
			genPost(root->children[i], table);
	if (root->nodeName == "Eincb")
	{
		string idName(root->children[0]->nodeName, 1);
		string idType = (table.items)[table.find(idName)].type;
		if (idType == "int")
		{
			cout << "\tmov eax, _" << idName << endl;
			cout << "\tinc eax" << endl;
			cout << "\tmov _" << idName << ", eax" << endl;
		}
		else if (idType == "char")
		{
			cout << "\tmov ax, _" << idName << endl;
			cout << "\tinc ax" << endl;
			cout << "\tmov _" << idName << ", ax" << endl;
		}
	}
	if (root->nodeName == "Edecb")
	{
		string idName(root->children[0]->nodeName, 1);
		string idType = (table.items)[table.find(idName)].type;
		if (idType == "int")
		{
			cout << "\tmov eax, _" << idName << endl;
			cout << "\tdec eax" << endl;
			cout << "\tmov _" << idName << ", eax" << endl;
		}
		else if (idType == "char")
		{
			cout << "\tmov ax, _" << idName << endl;
			cout << "\tdec ax" << endl;
			cout << "\tmov _" << idName << ", ax" << endl;
		}
	}
}

void genScomp(node* root, Table table)
{
	if ((root->nodeName)[0] == 'E')
	{
		genPre(root, table);
		genExpr(root, table);
		genPost(root, table);
	}
	else if (root->nodeName == "Dasgn")
	{
		genPre(root->children[1], table);
		genExpr(root->children[1], table);
		genPost(root->children[1], table);
		string idName(root->children[0]->nodeName, 1);
		string idType = (table.items)[table.find(idName)].type;
		if (idType == "int")
		{
			cout << "\tmov eax, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov _" << idName << ", eax" << endl;
		}
		else if (idType == "char")
		{
			cout << "\tmov ax, _Node" << root->children[1]->nodeId << endl;
			cout << "\tmov _" << idName << ", ax" << endl;
		}
	}
	else if (root->nodeName == "Si")
	{
		string idName(root->children[0]->nodeName, 1);
		string idType = (table.items)[table.find(idName)].type;
		cout << "\tpush eax" << endl;
		cout << "\tpush ebx" << endl;
		cout << "\tpush ecx" << endl;
		cout << "\tpush edx" << endl;
		if (idType == "int")
		{
			cout << "\tinvoke crt_scanf, addr integer, addr _" << idName << endl;
		}
		else if (idType == "char")
		{
			cout << "\tinvoke crt_scanf, addr character, addr _" << idName << endl;
		}
		cout << "\tpop edx" << endl;
		cout << "\tpop ecx" << endl;
		cout << "\tpop ebx" << endl;
		cout << "\tpop eax" << endl;
	}
	else if (root->nodeName == "So")
	{
		genPre(root->children[0], table);
		genExpr(root->children[0], table);
		cout << "\tpush eax" << endl;
		cout << "\tpush ebx" << endl;
		cout << "\tpush ecx" << endl;
		cout << "\tpush edx" << endl;
		if ((root->children[0]->nodeType == "int") || (root->children[0]->nodeType == "INT"))
		{
			cout << "\tmov eax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tinvoke crt_printf, addr integer, eax" << endl;
		}
		else if ((root->children[0]->nodeType == "char") || (root->children[0]->nodeType == "CHAR"))
		{
			cout << "\tmov eax, 0" << endl;
			cout << "\tmov ax, _Node" << root->children[0]->nodeId << endl;
			cout << "\tinvoke crt_printf, addr character, eax" << endl;
		}
		cout << "\tpop edx" << endl;
		cout << "\tpop ecx" << endl;
		cout << "\tpop ebx" << endl;
		cout << "\tpop eax" << endl;
		genPost(root->children[0], table);
	}
	else if (root->nodeName == "Sif")
	{
		node* judgeExpr = root->children[0];
		genPre(judgeExpr, table);
		genExpr(judgeExpr, table);
		genPost(judgeExpr, table);
		if ((judgeExpr->nodeType == "INT") || (judgeExpr->nodeType == "int"))
		{
			cout << "\tmov edx, _Node" << judgeExpr->nodeId << endl;
		}
		else if ((judgeExpr->nodeType == "CHAR") || (judgeExpr->nodeType == "char"))
		{
			cout << "\tmov edx, 0" << endl;
			cout << "\tmov dx, _Node" << judgeExpr->nodeId << endl;
		}
		cout << "\tcmp edx, 0" << endl;
		cout << "\tje SifNode" << judgeExpr->nodeId << "_end" << endl;
		genScomp(root->children[1], table);
		cout << "SifNode" << judgeExpr->nodeId << "_end:" << endl;
	}
	else if (root->nodeName == "SifElse")
	{
		node* judgeExpr = root->children[0];
		node* thenStmt = root->children[1];
		node* elseStmt = root->children[2];
		genPre(judgeExpr, table);
		genExpr(judgeExpr, table);
		genPost(judgeExpr, table);
		if ((judgeExpr->nodeType == "INT") || (judgeExpr->nodeType == "int"))
		{
			cout << "\tmov edx, _Node" << judgeExpr->nodeId << endl;
		}
		else if ((judgeExpr->nodeType == "CHAR") || (judgeExpr->nodeType == "char"))
		{
			cout << "\tmov edx, 0" << endl;
			cout << "\tmov dx, _Node" << judgeExpr->nodeId << endl;
		}
		cout << "\tcmp edx, 0" << endl;
		cout << "\tje SifElse" << judgeExpr->nodeId << "_else" << endl;
		genScomp(thenStmt, table);
		cout << "\tjne SifElse" << judgeExpr->nodeId << "_end" << endl;
		cout << "SifElse" << judgeExpr->nodeId << "_else:" << endl;
		genScomp(elseStmt, table);
		cout << "SifElse" << judgeExpr->nodeId << "_end:" << endl;
	}
	else if (root->nodeName == "Swhile")
	{
		node* judgeExpr = root->children[0];
		cout << "WhileNode" << judgeExpr->nodeId << "_begin:" << endl;
		genPre(judgeExpr, table);
		genExpr(judgeExpr, table);
		genPost(judgeExpr, table);

		if ((judgeExpr->nodeType == "INT") || (judgeExpr->nodeType == "int"))
		{
			cout << "\tmov edx, _Node" << judgeExpr->nodeId << endl;
		}
		else if ((judgeExpr->nodeType == "CHAR") || (judgeExpr->nodeType == "char"))
		{
			cout << "\tmov edx, 0" << endl;
			cout << "\tmov dx, _Node" << judgeExpr->nodeId << endl;
		}

		cout << "\tcmp edx, 0" << endl
			<< "\tje WhileNode" << judgeExpr->nodeId << "_end" << endl;
		genScomp(root->children[1], table);
		cout << "\tjmp WhileNode" << judgeExpr->nodeId << "_begin" << endl;
		cout << "WhileNode" << judgeExpr->nodeId << "_end:" << endl;
	}
	else if (root->nodeName == "Sfor")
	{
		node* initialUnit = root->children[0];
		node* judgeExpr = root->children[1];
		node* updateUnit = root->children[2];
		node* stmtUnit = root->children[3];

		genPre(initialUnit, table);
		genExpr(initialUnit, table);
		genPost(initialUnit, table);

		cout << "ForNode" << judgeExpr->nodeId << "_begin:" << endl;
		genPre(judgeExpr, table);
		genExpr(judgeExpr, table);
		genPost(judgeExpr, table);

		if ((judgeExpr->nodeType == "INT") || (judgeExpr->nodeType == "int"))
		{
			cout << "\tmov edx, _Node" << judgeExpr->nodeId << endl;
		}
		else if ((judgeExpr->nodeType == "CHAR") || (judgeExpr->nodeType == "char"))
		{
			cout << "\tmov edx, 0" << endl;
			cout << "\tmov dx, _Node" << judgeExpr->nodeId << endl;
		}
		cout << "\tcmp edx, 0" << endl;
		cout << "\tje ForNode" << judgeExpr->nodeId << "_end" << endl;

		genScomp(stmtUnit, table);

		genPre(updateUnit, table);
		genExpr(updateUnit, table);
		genPost(updateUnit, table);
		cout << "\tjmp ForNode" << judgeExpr->nodeId << "_begin" << endl;
		cout << "ForNode" << judgeExpr->nodeId << "_end:" << endl;
	}
	else
	{
		for (int i = 0; i < 4; i++)
			if (root->children[i] != NULL) 
				genScomp(root->children[i], table);
	}
}

void genCode(node* root, Table table)
{
	genScomp(root, table);
	cout << "\n\tinvoke crt__getch" << endl;
	cout << "\tinvoke crt__exit, 0" << endl;
	cout << "end start" << endl;
}

void genTemp(node* root)
{
	for (int i = 0; i < 4; i++)
		if (root->children[i] != NULL)
			genTemp(root->children[i]);
	if ((root->nodeType == "char") || (root->nodeType == "CHAR"))
		cout << "\t_Node" << root->nodeId << " dw 0000H" << endl;
	if ((root->nodeType == "INT") || (root->nodeType == "int"))
		cout << "\t_Node" << root->nodeId << " dd 00000000H" << endl;
}

void genHead(node* root, Table table)
{
	cout << ".486" << endl;
	cout << ".model flat,stdcall" << endl;
	cout << "option casemap:none" << endl;
	cout << endl;
	cout << "include  \\masm32\\include\\windows.inc" << endl;
	cout << "include  \\masm32\\include\\kernel32.inc" << endl;
	cout << "include  \\masm32\\include\\masm32.inc" << endl;
	cout << "include  \\masm32\\include\\msvcrt.inc" << endl;
	cout << "includelib  \\masm32\\lib\\kernel32.lib" << endl;
	cout << "includelib  \\masm32\\lib\\masm32.lib" << endl;
	cout << "includelib  \\masm32\\lib\\msvcrt.lib" << endl;
	cout << endl;
	cout << ".data" << endl;
	cout << "\tinteger db '%d', 0" << endl;
	cout << "\tcharacter db '%c', 0" << endl;
	cout << endl;

	for (int i = 1; i <= table.length; i++)
	{
		TableItem item = table.items[i];
		if (item.type == "char")
			cout << "\t_" << item.name << " dw 0000H" << endl;
		else if (item.type == "int")
			cout << "\t_" << item.name << " dd 00000000H" << endl;
	}
	cout << endl;

	genTemp(root);

	cout << endl;
	cout << ".code" << endl;
	cout << "start:" << endl;
}

void genAsm(node* root, Table table)
{
	genHead(root, table);
	genCode(root, table);
}