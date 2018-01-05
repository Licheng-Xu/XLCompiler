%{
#define YYSTYPE node*

#include "head.h"
#include "parser.hpp"
#include <string>
#include <cstring>

extern int lineno;
node temp;
void yyerror(const char *msg);

%}

delim       [ \r\t]
space       {delim}+
letter      [A-Za-z]
digIT       [0-9]
id          ({letter}|[_])({letter}|{digIT}|[_])*
number      {digIT}+(\.{digIT}+)?(E[+-]?{digIT}+)?
character   '.'
comment     (\/\/.*)|(\/\*(.|[\r\n])*?\*\/)

%%

"\n"        {lineno++;}

{comment}   {}
{space}     {}

";"		    { return SEMI; }
"("		    { return LP; }
")"		    { return RP; }
"{"		    { return LB; }
"}"		    { return RB; }
","		    { return COMMA;}

"+"		    { return PLUS; }
"-"		    { return SUB; }
"*"		    { return MUL; }
"/"		    { return DIV; }
"%"		    { return MOD; }
"&&"	    { return AND; }
"||"	    { return OR; }
"!"		    { return NOT; }
"|"		    { return BITOR; }
"&"		    { return BITAND; }
"^"		    { return BITXOR; }
"~"		    { return BITNOT; }
"="		    { return ASSIGN; }
"=="	    { return EQ; }
"!="	    { return UNEQ; }
"<"		    { return LESS; }
">"		    { return MORE; }
">="	    { return MOREEQ; }
"<="	    { return LESSEQ; }
"<<"	    { return LSHIFT; }
">>"	    { return RSHIFT; }
"++"        { return PPLUS; }
"--"        { return SSUB; }

main	    { return MAIN; }
if		    { return IF; }
else	    { return ELSE; }
while	    { return WHILE; }
for		    { return FOR; }

int		    { return INT ;}
char	    { return CHAR ;}

scan	    { return IN; }
print	    { return OUT; }

{character} {
                yylval = &temp;
                yylval->value = yytext[1];
				return LETTER; 
			}
{id} 		{
                yylval = &temp;
				yylval->nodeName=yytext;
				return ID;
			}
{number} 	{
                yylval = &temp;
                yylval->value = atoi(yytext);
				return NUMBER; 
			}
%%

int yywrap(void) { 
    return 1;
}

void yyerror(const char *msg) {
    printf("Error: %s in %d.\n", msg, lineno);
    exit(1);
}