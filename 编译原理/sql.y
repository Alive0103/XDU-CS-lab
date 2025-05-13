%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"

extern int yylex();
extern int yyparse();
extern FILE *yyin;
extern char *yytext;
extern int yylineno;

char database[64]={0};
extern struct mydb *dbroot;

void yyerror (const char *str) 
{
	fprintf(stderr, "error: %s\n", str);		// error function
}

int yywrap() 
{
	return 1;
}
// main function 
int main() 
{
	printf("SQL>");
	return	yyparse(); // calling parse funtion 
} 

%}

%union{  
	int intval;   
  	char *strval;
  	struct hyper_items_def *Citemsval;
  	struct value_def *valueval;
  	struct item_def *itemval;
  	struct conditions_def *conval;
  	struct table_def *tbval;
  	struct upcon_def *updateval;
}

%token SELECT FROM WHERE AND OR DROP DELETE TABLE CREATE INTO VALUES INSERT UPDATE SET SHOW DATABASE DATABASES TABLES EXIT USE
%token <intval> NUMBER 
%token <strval> STRING ID INT CHAR
%type <intval> comparator
%type <Citemsval> hyper_items create_items
%type <valueval> value_list value
%type <itemval> item item_list
%type <conval> condition conditions
%type <tbval> tables
%type <updateval> up_cond up_conds
%left OR
%left AND


%%

/* production for sql grammar */

statements: statements statement | statement
statement: createsql | showsql | selectsql | insertsql | deletesql | updatesql | dropsql | exitsql | usesql

usesql: 		USE ID ';' '\n' {
					printf("\n");
					useDB($2);
					printf("\nSQL>");
		        }

showsql: 		SHOW DATABASES ';' '\n' {
					printf("\n");
		            showDB();
		            printf("\nSQL>");
		        }
		        |SHOW TABLES ';' '\n' {
		        	printf("\n");
		            showTable();
		            printf("\nSQL>");
		        }

createsql:		CREATE TABLE ID '(' hyper_items ')' ';' '\n' {
					printf("\n");
                	createTable($3, $5);
                	printf("\nSQL>");
				}

				|CREATE DATABASE ID ';' '\n' {
					strcpy(database, $3);
					printf("\n");
					createDB();
					printf("\nSQL>");
				}		        

selectsql: 		SELECT '*' FROM tables ';' '\n'{
					printf("\n");
					selectWhere(NULL, $4, NULL);
					printf("\n");
					printf("SQL>");
				}
				| SELECT item_list FROM tables ';' '\n' {
					printf("\n");
					selectWhere($2, $4, NULL);
					printf("\nSQL>");
				}		
				|SELECT '*' FROM tables WHERE conditions ';' '\n' {
					printf("\n");
					selectWhere(NULL, $4, $6);
					printf("\nSQL>");
				}
				|SELECT item_list FROM tables WHERE conditions ';' '\n' { 
					printf("\n");
					selectWhere($2, $4, $6);
					printf("\nSQL>");
				}

deletesql:		DELETE FROM ID ';' '\n' {
					printf("\n");
					deletes($3, NULL);
					printf("\n");
					printf("SQL>");
				}

				|DELETE FROM ID WHERE conditions ';' '\n' 	{ 
					printf("\n");
					deletes($3, $5);
					printf("\nSQL>");
				}


insertsql:		INSERT INTO ID VALUES '(' value_list ')' ';' '\n' {
					printf("\n");
					multiInsert($3, NULL, $6);
					printf("\nSQL>");
				}
		
				|INSERT INTO ID '(' item_list ')' VALUES '(' value_list ')' ';' '\n' {
					printf("\n");
					multiInsert($3, $5, $9);
					printf("\nSQL>");
				}


updatesql:		UPDATE ID SET up_conds ';' '\n' {
					printf("\n");
					struct mydb *dbtemp = dbroot;
					struct table *tabletemp = NULL;
					while(dbtemp != NULL) {
						if(strcmp(dbtemp->name, database) == 0) {
							tabletemp = dbtemp->tbroot;
							while(tabletemp != NULL) {
								if(strcmp(tabletemp->name, $2) == 0) {
									updates(tabletemp, $4, NULL);
									printf("\nSQL>");
									return 0;
								}
								tabletemp = tabletemp->next;
							}
							printf("error: Table %s doesn't exist!\n", $2);
							printf("\nSQL>");
							return 0;
						}
						dbtemp = dbtemp->next;
					}
					printf("error: Database %s doesn't exist!\n", database);
					printf("\nSQL>");
					return 0;
				}
		
				|UPDATE ID SET up_conds WHERE conditions ';' '\n' {
					printf("\n");
					struct mydb *dbtemp = dbroot;
					struct table *tabletemp = NULL;
					while(dbtemp != NULL) {
						if(strcmp(dbtemp->name, database) == 0) {
							tabletemp = dbtemp->tbroot;
							while(tabletemp != NULL) {
								if(strcmp(tabletemp->name, $2) == 0) {
									updates(tabletemp, $4, $6);
									printf("\nSQL>");
									return 0;
								}
								tabletemp = tabletemp->next;
							}
							printf("error: Table %s doesn't exist!\n", $2);
							printf("\nSQL>");
							return 0;
						}
						dbtemp = dbtemp->next;
					}
					printf("error: Database %s doesn't exist!\n", database);
					printf("\nSQL>");
					return 0;
				}

dropsql:		DROP TABLE ID ';' '\n'	{
					printf("\n");
					dropTable($3);
					printf("\nSQL>");
				}
				| DROP DATABASE ID ';' '\n' {
					printf("\n");
					dropDB($3);
					printf("\nSQL>");
				}

exitsql: 		EXIT ';' {
					printf("\n");
		            printf("exit with code 0!\n");
		            exit(0);
		        }

create_items:	ID INT {
					$$ = (struct hyper_items_def *)malloc(sizeof(struct hyper_items_def));
                    strcpy($$->field, $1);
                    $$->type = 0;	
                    $$->next = NULL;	
				}
				| ID CHAR '(' NUMBER ')'{
					$$ = (struct hyper_items_def *)malloc(sizeof(struct hyper_items_def));
                    strcpy($$->field, $1);
                    $$->type = 1;
                    $$->next = NULL;	
				}

hyper_items: 	create_items {
					$$ = $1;
				}
				| hyper_items ',' create_items {
					$$ = $3;
					$$->next = $1;				
				}

item: 			ID {
					$$ = (struct item_def *)malloc(sizeof(struct item_def));
					strcpy($$->field, $1);
					$$->pos = NULL;
					$$->next = NULL;
				}

item_list: 		item {
					$$ = $1;				
				}
				| item_list ',' item{
					$$ = $3;
					$$->next = $1;
				}

value:			NUMBER {
					$$ = ((struct value_def *)malloc(sizeof(struct value_def)));
					$$->value.intkey = $1;
					$$->type = 0;
					$$->next = NULL;
				}
				| STRING {
					$$ = ((struct value_def *)malloc(sizeof(struct value_def)));
					strcpy($$->value.skey, $1);
					$$->type = 1;
					$$->next = NULL;
				}

value_list:		value {
					$$ = $1;
				}
				| value_list ',' value {
					$$ = $3;
					$$->next = $1;
				}

comparator:		'=' {$$ = 1; }
				| '>' {$$ = 2; }
				| '<' {$$ = 3; }
				| ">=" {$$ = 4; }
				| "<=" {$$ = 5; }
				| '!' '=' {$$ = 6; }

condition: 		item comparator NUMBER {
					$$ = ((struct conditions_def *)malloc(sizeof(struct conditions_def)));
					$$->type = 0;
					$$->litem = $1;
					$$->intv = $3;
					$$->cmp_op = $2;
					$$->left = NULL;
					$$->right = NULL;
				}
				| item comparator STRING {
					$$ = ((struct conditions_def *)malloc(sizeof(struct conditions_def)));
					$$->type = 1;
					$$->litem = $1;
					strcpy($$->strv, $3);
					$$->cmp_op = $2;
					$$->left = NULL;
					$$->right = NULL;
				}

conditions: 	condition {
					$$ = $1;
				}
				|'(' conditions ')' {
					$$ = $2;
				}
				| conditions AND conditions {
					$$ = ((struct conditions_def *)malloc(sizeof(struct conditions_def)));
					$$->cmp_op = 7;
					$$->left = $1;
					$$->right = $3;
				}
				| conditions OR conditions {
					$$ = ((struct conditions_def *)malloc(sizeof(struct conditions_def)));
					$$->cmp_op = 8;
					$$->left = $1;
					$$->right = $3;
				}

tables:			ID {
					$$ = ((struct table_def *)malloc(sizeof(struct table_def)));
					strcpy($$->table, $1);
					$$->next = NULL;
				}
				| tables ',' ID{
					$$ = ((struct table_def *)malloc(sizeof(struct table_def)));
					strcpy($$->table, $3);
					$$->next = $1;				
				}

up_cond:		ID '=' NUMBER {
					$$ = ((struct upcon_def *)malloc(sizeof(struct upcon_def)));
					strcpy($$->field, $1);
					$$->type = 0;
					$$->value.intkey = $3;
					$$->next = NULL;
				}
				| ID '=' STRING {
					$$ = ((struct upcon_def *)malloc(sizeof(struct upcon_def)));
					strcpy($$->field, $1);
					$$->type = 1;
					strcpy($$->value.skey, $3);
					$$->next = NULL;				
				}

up_conds:		up_cond {
					$$ = $1;
				}
				| up_conds ',' up_cond {
					$$ = $3;
					$$->next = $1;
				}

%%
