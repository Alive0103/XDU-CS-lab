%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"
#include "sql.tab.h"

extern int yylineno;
%}

%%
select |
SELECT				{ return SELECT; }
drop |
DROP					{ return DROP; }
table |
TABLE					{ return TABLE; }
tables |
TABLES					{ return TABLES; }
database |
DATABASE				{ return DATABASE; }
databases |
DATABASES				{ return DATABASES; }
create |
CREATE				{ return CREATE; }
insert |
INSERT				{ return INSERT; } 
update |
UPDATE				{ return UPDATE; } 
set |
SET 					{ return SET; } 
delete |
DELETE 				{ return DELETE; } 
from |
FROM					{ return FROM; } 
where |
WHERE					{ return WHERE; } 
into |
INTO 					{ return INTO; } 
values |
VALUES					{ return VALUES; } 
and |
AND						{ return AND; } 
or |
OR						{ return OR; } 
int |
INT   					{ return INT; } 
char |
CHAR 					{ return CHAR; }  
show |
SHOW					{ return SHOW; } 
exit |
EXIT					{ return EXIT; } 
use |
USE						{ return USE; } 
[;]		|				
[(]		|				
[)]		|				
[*]		|				
[,]		|				
"<="	|
">="	|
[!]		|
"<"		|
">"		|
[=]						return *yytext;
[\'][A-Za-z][A-Za-z0-9_]*[\'] 		{ yylval.strval=strdup(yytext); return STRING; }
[A-Za-z][A-Za-z0-9_]*	{ yylval.strval=strdup(yytext); return ID; }
[0-9]+ 		{ yylval.intval=atoi(yytext); return NUMBER;	}			
\n						return *yytext;
[ \t]+					/* ignore whitespace */
%%