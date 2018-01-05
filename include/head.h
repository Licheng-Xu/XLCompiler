#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

class TableItem
{
public:
	string type;
	string name;

	TableItem(string type = "",string name = "")
	{
		this->type = type;
		this->name = name;
	}
};

class Table{
public:
	int length;
	TableItem items[100];
	
	Table()
	{
		length = 0;
	}
	
	int find(string toFind)
	{
		for (int i = 1; i <= length; i++) 
		{
			if (toFind == items[i].name)
				return i;
		}
		return -1;
	}
	
	bool add(string type,string name) 
	{
		if (find(name) > 0) return false;
		else {
			TableItem newItem = TableItem( type,name );
			items[++length] = newItem;
			return true;
		}
	}

	void show() 
	{
		cout << "Display the Table :"<<endl;
		for (int i = 1; i <= length; i++) 
			cout<< i << ": " << items[i].type << "\t" << items[i].name << endl;
		cout <<endl;
	}
};

class node
{
public:
	int nodeId;  
	int value;
	int lineno;
	string nodeType;
	string nodeName;
	node*children[4];

	node()
	{
		nodeId=-1;
	    nodeType="";
		nodeName="";
	    value=0;
		lineno=0;
	    children[0]=NULL;
		children[1]=NULL;
		children[2]=NULL;
		children[3]=NULL;
	}
	node(int nodeId, string nodeName, int value = 0, int lineno = 0, node*children0 = NULL, node*children1 = NULL, node*children2 = NULL, node*children3 = NULL)
	{
		this->nodeId=nodeId;
		this->nodeName=nodeName;
	    this->value=value;
		this->lineno=lineno;
	    children[0]=children0;
		children[1]=children1;
		children[2]=children2;
		children[3]=children3;
	}

	bool isNull0() {return (children[0]==NULL);}
	bool isNull1() {return (children[1]==NULL);}
	bool isNull2() {return (children[2]==NULL);}
	bool isNull3() {return (children[3]==NULL);}
	
	void show()
	{
		cout<<nodeId<<":";
		cout<<"\t"<<nodeName;
		cout<<"\t"<<value;
		cout<<"\t"<<nodeType;
		cout<<"\tChildren: ";
		if(!isNull0()) cout<<children[0]->nodeId<<"  ";
		if(!isNull1()) cout<<children[1]->nodeId<<"  ";
		if(!isNull2()) cout<<children[2]->nodeId<<"  ";
		if(!isNull3()) cout<<children[3]->nodeId<<"  ";
		cout<<endl;
	}
};

void showTree(node*root);

void addItem(node* root, Table& table, string type);
void buildTable(node* root, Table& table);
void checkNoDecl(node* root, Table table);
void checkExprMatch(node* root, Table table);
void checkMatch(node* root, Table table);
void checkTree(node* root, Table& table);

void genExpr(node* root, Table table);
void genPre(node* root, Table table);
void genPost(node* root, Table table);
void genScomp(node* root, Table table);
void genCode(node* root, Table table);
void genTemp(node* root);
void genHead(node* root, Table table);
void genAsm(node* root, Table table);
