%{
#define YYSTYPE node*

#include "head.h"

int nodeId=-1;
int lineno=1;
node* root;
int yylex();
void yyerror(const char *msg);
%}

%token SEMI LP RP LB RB COMMA
%token PLUS SUB MUL DIV MOD AND OR NOT BITOR BITAND BITXOR BITNOT
%token ASSIGN EQ UNEQ LESS MORE MOREEQ LESSEQ LSHIFT RSHIFT PPLUS SSUB
%token MAIN IF ELSE WHILE FOR 
%token INT CHAR
%token LETTER ID NUMBER 
%token IN OUT
%%

program: 
		MAIN LP RP comp_stmt   			{root=$4;}
	;

comp_stmt:                                 
		LB RB                           {$$=new node(++nodeId,"Scomp",0,lineno);}
	| 	LB stmts RB            			{$$=new node(++nodeId,"Scomp",0,lineno,$2);}
   	;

stmts:                                     
		stmt                       		{$$=$1;}
   	| 	stmt stmts        				{$$=new node(++nodeId,"Slist",0,lineno,$1,$2);}
   	;

stmt:                                            
     	comp_stmt              			{$$=$1;}
   	|	io_stmt							{$$=$1;}
   	| 	expr_stmt                  		{$$=$1;}   
	| 	if_stmt                    		{$$=$1;}
	| 	while_stmt                		{$$=$1;}
	| 	for_stmt                   		{$$=$1;}
	| 	var_decl                 		{$$=$1;}
   	;

io_stmt:
	 	IN LP id RP SEMI				{$$=new node(++nodeId,"Si",0,lineno,$3);}
   	| 	OUT LP or_expr RP SEMI	{$$=new node(++nodeId,"So",0,lineno,$3);}
   	;

expr_stmt:                                      
     	expr SEMI                       {$$=$1;} 
   	; 

if_stmt:                                        
     	IF LP asgn_expr RP stmt						{$$=new node(++nodeId,"Sif",0,lineno,$3,$5);}
   	| 	IF LP asgn_expr RP stmt ELSE stmt			{$$=new node(++nodeId,"SifElse",0,lineno,$3,$5,$7);}
   	;

while_stmt:                                     
     	WHILE LP asgn_expr RP stmt  				{$$=new node(++nodeId,"Swhile",0,lineno,$3,$5);}
   	;

for_stmt:                                       
    	FOR LP expr SEMI expr SEMI expr RP stmt		{$$=new node(++nodeId,"Sfor",0,lineno,$3,$5,$7,$9);}
	|	FOR LP var_decl expr SEMI expr RP stmt		{$$=new node(++nodeId,"Sfor",0,lineno,$3,$4,$6,$8);}
   	;

var_decl:                                      
     	type id_list SEMI 							{ $$=new node(++nodeId,"Sdecl",0,lineno,$1,$2);}
   	;

id_list:                                              
     	id											{$$=$1;}
	| 	id COMMA id_list							{$$=new node(++nodeId,"Dlists",0,lineno,$1,$3);}
	| 	id ASSIGN or_expr							{$$=new node(++nodeId,"Dasgn",0,lineno,$1,$3);}
	| 	id ASSIGN or_expr COMMA id_list 			{ 
														node* temp = new node(++nodeId,"Dasgn",0,lineno,$1,$3);
														$$=new node(++nodeId,"Dlists",0,lineno,temp,$5); 
													}
	;

expr:                                          
     	asgn_expr									{$$=$1;}            
	|												{$$=new node(++nodeId,"Enull",0,lineno);}
   	;

asgn_expr:                                          
     	id ASSIGN or_expr  							{$$=new node(++nodeId,"Easgn",0,lineno,$1,$3);}
	| 	or_expr            							{$$=$1;}    
   	;
      
or_expr:
     	and_expr               						{$$=$1;}
   	| 	or_expr OR and_expr							{$$=new node(++nodeId,"Eor",0,lineno,$1,$3);}
   	;
and_expr:
		bor_expr              						{$$=$1;}
   	|	and_expr AND bor_expr						{$$=new node(++nodeId,"Eand",0,lineno,$1,$3);}
   	;

bor_expr:
		bxor_expr              						{$$=$1;}
   	| 	bor_expr BITOR bxor_expr					{$$=new node(++nodeId,"Ebitor",0,lineno,$1,$3);}
   	;

bxor_expr:
     	band_expr                       			{$$=$1;}
   	| 	bxor_expr BITXOR band_expr					{$$=new node(++nodeId,"Ebitxor",0,lineno,$1,$3);}
   	;

band_expr:
     	equ_expr                  					{$$=$1;}
   	| 	band_expr BITAND equ_expr					{$$=new node(++nodeId,"Ebitand",0,lineno,$1,$3);}
   	;

equ_expr:
     	relational_expr                				{$$=$1;}
   	|	equ_expr EQ relational_expr					{$$=new node(++nodeId,"Eeq",0,lineno,$1,$3);}
   	|	equ_expr UNEQ relational_expr				{$$=new node(++nodeId,"Ene",0,lineno,$1,$3);}
   	;

relational_expr:
     	shift_expr                     				{$$=$1;}
   	|	relational_expr LESS shift_expr				{$$=new node(++nodeId,"El",0,lineno,$1,$3);}
   	|	relational_expr MORE shift_expr				{$$=new node(++nodeId,"Eg",0,lineno,$1,$3);}
   	|	relational_expr LESSEQ shift_expr			{$$=new node(++nodeId,"Ele",0,lineno,$1,$3);}
   	|	relational_expr MOREEQ shift_expr			{$$=new node(++nodeId,"Ege",0,lineno,$1,$3);}
   	;

shift_expr:
     	add_expr                  					{$$=$1;}
   	| 	shift_expr LSHIFT add_expr					{$$=new node(++nodeId,"Eshl",0,lineno,$1,$3);}
   	| 	shift_expr RSHIFT add_expr					{$$=new node(++nodeId,"Eshr",0,lineno,$1,$3);}
   	;

add_expr:
    	mul_expr            						{$$=$1;}
   	|	add_expr PLUS mul_expr						{$$=new node(++nodeId,"Eadd",0,lineno,$1,$3);}
   	|	add_expr SUB mul_expr						{$$=new node(++nodeId,"Esub",0,lineno,$1,$3);}
   	;

mul_expr:
     	unary_expr                     				{$$=$1;}
   	| 	mul_expr MUL unary_expr						{$$=new node(++nodeId,"Emul",0,lineno,$1,$3);}
   	| 	mul_expr DIV unary_expr						{$$=new node(++nodeId,"Ediv",0,lineno,$1,$3);}
   	| 	mul_expr MOD unary_expr						{$$=new node(++nodeId,"Emod",0,lineno,$1,$3);}
   	;

unary_expr:
     	BITNOT minimal_expr							{$$=new node(++nodeId,"Ebitnot",0,lineno,$2);}
   	| 	NOT minimal_expr							{$$=new node(++nodeId,"Enot",0,lineno,$2);}
   	| 	BITAND id									{$$=new node(++nodeId,"Ebitand",0,lineno,$2);}
   	| 	PPLUS id									{$$=new node(++nodeId,"Eincp",0,lineno,$2);}
   	| 	id PPLUS									{$$=new node(++nodeId,"Eincb",0,lineno,$1);}
   	| 	SSUB id										{$$=new node(++nodeId,"Edecp",0,lineno,$2);}
   	| 	id SSUB										{$$=new node(++nodeId,"Edecb",0,lineno,$1);}
   	| 	minimal_expr								{$$=$1;}
   	;

minimal_expr:
     	LP expr RP									{$$=$2;}
   	|	id											{$$=$1;}
   	|	SUB id										{$$=new node(++nodeId,"Eneg",0,lineno,$2);}
   	|	const										{$$=$1;}
   	;

type:
     	INT											{$$=new node(++nodeId,"TI",0,lineno);}
   	|	CHAR										{$$=new node(++nodeId,"TC",0,lineno);} 
   	;

id:
	ID												{$$=new node(++nodeId,"I" + $1->nodeName,0,lineno);}
   	;
   
const:
     	num											{$$=$1;}
   	|	letter										{$$=$1;}
   	;

num:
    	NUMBER										{$$=new node(++nodeId,"NI",$1->value,lineno);}
   	|	SUB NUMBER 									{$$=new node(++nodeId,"NI",-$1->value,lineno);}
   	;

letter:
    	LETTER										{$$=new node(++nodeId,"NC",$1->value,lineno);} 
   	;

%%

int main(int argc, char **argv)
{
    yyparse();
    //showTree(root);
    Table table;
    checkTree(root, table);
    //showTree(root);
    genAsm(root, table);
	return 0;
}

void showTree(node*root){
	if (!root->isNull0()) showTree(root->children[0]);
	if (!root->isNull1()) showTree(root->children[1]);
	if (!root->isNull2()) showTree(root->children[2]);
	if (!root->isNull3()) showTree(root->children[3]);
	root->show();
}