#include "sql.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define TRUE 1
#define FALSE 0

extern char database[64];

struct mydb *dbroot = NULL;


/*item链表就地逆置*/
struct item_def *converseItems(struct item_def *ppHead){
    struct item_def *pCurNode = ppHead;
    struct item_def *pPrevNode = NULL;
    struct item_def *pTmpNode = NULL;
    while(pCurNode)
    {
        pPrevNode = pCurNode;
        pCurNode = pCurNode->next;
        pPrevNode->next = pTmpNode;
        pTmpNode = pPrevNode;
    }
    return pTmpNode;
}

/*各种结构链表的内存释放*/
void freeHItems(struct hyper_items_def *Hitemroot){
	struct hyper_items_def *Hitemtemp;
	while(Hitemroot != NULL){
		Hitemtemp = Hitemroot->next;
		free(Hitemroot);
		Hitemroot = Hitemtemp;
	}
}

void freeCons(struct conditions_def *conroot){
	if(conroot == NULL)
		return;
    if (conroot->left != NULL)
        freeCons(conroot->left);
    else if (conroot->right != NULL)
        freeCons(conroot->right);
    else
        free(conroot);
}

void freeItems(struct item_def *itemroot){
	struct item_def *itemtemp;
	while(itemroot != NULL){
		itemtemp = itemroot->next;
		free(itemroot);
		itemroot = itemtemp;
	}
}

void freeTables(struct table_def *tableroot){
	struct table_def *tableptr;
	while(tableroot != NULL){
		tableptr = tableroot->next;
		free(tableroot);
		tableroot = tableptr;
	}
}

void freeUpcon(struct upcon_def *uproot){
	struct upcon_def *uptemp;
	while(uproot != NULL){
		uptemp = uproot->next;
		free(uptemp);
		uproot = uptemp;
	}
}

void freeVal(struct value_def *valroot){
	struct value_def *valtemp;
	while(valroot != NULL){
		valtemp = valroot->next;
		free(valroot);
		valroot = valtemp;
	}
}

/*创建数据库。若数据库根节点为空，则在根结点处创建数据库，若不为空则遍历数据库链表，
若找到同名数据库，提示已存在，返回，若没找到，在链表尾部插入新的数据库*/
void createDB(){
	if(dbroot == NULL){
		dbroot = (struct mydb *)malloc(sizeof(struct mydb));
	    strcpy(dbroot->name,database);
	    dbroot->tbroot = NULL;
	    dbroot->next = NULL;
	    if(dbroot != NULL);
    		printf("Database %s created successfully!\n", database);
	    return;
	}
	struct mydb *newdb;
	newdb = dbroot;
	while(newdb->next != NULL){
		if(strcmp(newdb->name,database) == 0){
			printf("error: The database already exists!\n");
			return;
		}
		newdb = newdb->next;
	}
	if(strcmp(newdb->name,database) == 0){
		printf("error: The database already exists!\n");
		return;
	}
	newdb->next = (struct mydb *)malloc(sizeof(struct mydb));
    strcpy(newdb->next->name,database);
    newdb->next->tbroot = NULL;
    newdb->next->next = NULL;
    if(dbroot->next != NULL);
    	printf("Database %s created successfully!\n", database);
}

/*展示所有数据库。若根节点为空，提示数据库列表为空请先创建一个数据库，否则遍历数据库链表，打印数据库名*/
void showDB(){
	struct mydb *dbtemp = NULL;
	if(dbroot != NULL)
		dbtemp = dbroot;
	else{
		printf("Database list is NULL, Please create a database first!\n");
		return;
	}
	while(dbtemp != NULL){
		printf("%s  ", dbtemp->name);
		dbtemp = dbtemp->next;
	}
	printf("\n");	
}

/*指定使用的数据库，若数据库根节点为空，提示请先创建一个数据库，遍历数据库链表，找到对应数据库，
将全局变量database更新为当前数据库名，否则提示数据库不存在，返回*/
void useDB(char *dbname){
	struct mydb *dbtemp = NULL;
	if(dbroot != NULL)
		dbtemp = dbroot;
	else{
		printf("error: Please create a database first!\n");
		return;
	}
	while(dbtemp != NULL){
		if(strcmp(dbtemp->name, dbname) == 0){
			strcpy(database, dbname);
			printf("Using database %s\n", dbname);
			return;
		}
		dbtemp = dbtemp->next;
	}
	printf("error: Database %s doesn't exist!\n", dbname);
}

/*创建表。
若数据库根节点为空，提示先创建数据库，否则遍历数据库列表，查找当前使用的数据库，若未找到，提示数据库不存在，
若找到，再看当前数据库下的表根节点是否为空，
若为空，在根节点处创建新表，否则遍历表链表，
若找到名字相同的表，提示该表已存在，返回，否则在链表尾部建立新表*/
void createTable(char *tableval, struct hyper_items_def *Hitemroot){
	int i;
	struct mydb *dbtemp = NULL;
	struct table *newtable = NULL;
	struct table *tabletemp = NULL;
	struct hyper_items_def *itemstemp = Hitemroot;
	if(dbroot != NULL)
		dbtemp = dbroot;
	else{
		printf("error: Please create a database first!\n");
		freeHItems(Hitemroot);
		return;
	}
	while(dbtemp != NULL){
		if(strcmp(dbtemp->name,database) == 0){
			if(dbtemp->tbroot == NULL){
				dbtemp->tbroot = (struct table *)malloc(sizeof(struct table));
				strcpy(dbtemp->tbroot->name, tableval);
				dbtemp->tbroot->ffield = (struct field *)malloc(10*sizeof(struct field));
				i = 0;
				while(itemstemp != NULL && i<10){
					strcpy(dbtemp->tbroot->ffield[i].name, itemstemp->field);
					if(itemstemp->type == 0)
						dbtemp->tbroot->ffield[i].type = 0;
					else
						dbtemp->tbroot->ffield[i].type = 1;
					itemstemp = itemstemp->next;
					i++;
				}
				dbtemp->tbroot->flen = i;
				dbtemp->tbroot->ilen = 0;
				dbtemp->tbroot->next = NULL;
				if(dbtemp->tbroot != NULL)
					printf("Table %s created successfully!\n", tableval);
				freeHItems(Hitemroot);
				return;
			}
			newtable = dbtemp->tbroot;
			while(newtable->next != NULL){
				if(strcmp(newtable->name,tableval) == 0){
					printf("error: The table already exists!\n");
					freeHItems(Hitemroot);
					return;
				}
				newtable = newtable->next;
			}
			if(strcmp(newtable->name,tableval) == 0){
				printf("error: The table already exists!\n");
				freeHItems(Hitemroot);
				return;
			}
			newtable->next = (struct table *)malloc(sizeof(struct table));
			strcpy(newtable->next->name, tableval);
			newtable->next->ffield = (struct field *)malloc(10*sizeof(struct field));
			i = 0;
			while(itemstemp != NULL && i<10){
				strcpy(newtable->next->ffield[i].name, itemstemp->field);
				if(itemstemp->type == 0)
					newtable->next->ffield[i].type = 0;
				else
					newtable->next->ffield[i].type = 1;
				itemstemp = itemstemp->next;
				i++;
			}
			newtable->next->flen = i;
			newtable->next->next = NULL;
			printf("Table %s created successfully!\n", tableval);
			freeHItems(Hitemroot);
			return;
		}
		dbtemp = dbtemp->next;
	}
	freeHItems(Hitemroot);
	printf("error: Database %s doesn't exist!\n", database);
}

/*展示表。遍历当前选用的数据库下的表链表，打印表名*/
void showTable(){
	struct mydb *dbtemp = NULL;
	struct table *tabletemp = NULL;
	int i,j,temp;
	if(dbroot != NULL)
		dbtemp = dbroot;
	else{
		printf("error: Please create a database first!\n");
		return;
	}
	while(dbtemp != NULL){
		if(strcmp(dbtemp->name,database) == 0){
			tabletemp = dbtemp->tbroot;
			while(tabletemp != NULL){
				printf("%s  ", tabletemp->name);
				tabletemp = tabletemp->next;
			}
			printf("\n");
			return;
		}
		dbtemp = dbtemp->next;
	}
	printf("error: Database %s doesn't exist!\n", database);	
}

/*插入记录。
找到插入的表，若未找到，提示不存在，
找到以后，若未指定字段及其顺序，将value list中的值依次插入到每个字段的最后，
若指定了字段和顺序，则按顺序查找字段，并依次追加记录，
若未查找到对应字段，则提示字段与表不匹配，返回。
完成插值以后，判断itemlist和valuelist是否同时为空，若不是，则提示两者不匹配，返回，若是，则提示成功，并将该表的条数值加一*/
void multiInsert(char *tableval, struct item_def *itemroot, struct value_def *valroot){
	struct mydb *dbtemp = NULL;
	struct table *tabletemp = NULL;
	struct item_def *itemtemp = NULL;
	struct value_def *valtemp = NULL;
	int i,j,temp;
	if(dbroot != NULL)
		dbtemp = dbroot;
	else{
		printf("error: Please create a database first!\n");
		freeItems(itemroot);
		freeVal(valroot);
		return;
	}
	while(dbtemp != NULL){
		if(strcmp(dbtemp->name,database) == 0){
			tabletemp = dbtemp->tbroot;
			while(tabletemp != NULL){
				if(strcmp(tabletemp->name, tableval) == 0){
					i = 0;
					temp = tabletemp->ilen;
					valtemp = valroot;
					if(itemroot == NULL){
						while(valtemp != NULL){
							if(valtemp->type == 0){
								tabletemp->ffield[i].type = 0;
								tabletemp->ffield[i].key[temp].intkey = valtemp->value.intkey;
							}
							else{
								tabletemp->ffield[i].type = 1;
								strcpy(tabletemp->ffield[i].key[temp].skey, valtemp->value.skey);
							}
							i++;
							valtemp = valtemp->next;
						}
					}
					else{
						itemtemp = itemroot;
						while(itemtemp != NULL && valtemp != NULL){
							for(j = 0; j < tabletemp->flen; j++){
								if(strcmp(tabletemp->ffield[j].name, itemtemp->field) == 0){
									if(valtemp->type == 0){
										tabletemp->ffield[j].type = 0;
										tabletemp->ffield[j].key[temp].intkey = valtemp->value.intkey;
									}
									else{
										tabletemp->ffield[j].type = 1;
										strcpy(tabletemp->ffield[j].key[temp].skey, valtemp->value.skey);
									}
									i++;
									break;
								}
							}
							if(j == tabletemp->flen){
								printf("error: Column name does not match the table definition!\n");
								freeItems(itemroot);
								freeVal(valroot);
								return;
							}
							itemtemp = itemtemp->next;
							valtemp = valtemp->next;
						}
					}
					if(i <= tabletemp->flen && itemtemp == NULL && valtemp == NULL){
						temp++;
						tabletemp->ilen = temp;
						printf("Insert successfully!\n");
					}
					else{
						printf("error: The number of supplied values does not match the table definition!\n");
					}
					freeItems(itemroot);
					freeVal(valroot);
					return;
				}
				tabletemp = tabletemp->next;
			}
			printf("error: The table doesn't exist!\n");
			freeItems(itemroot);
			freeVal(valroot);
			return;
		}
		dbtemp = dbtemp->next;
	}
	freeItems(itemroot);
	freeVal(valroot);
	printf("error: Database %s doesn't exist!\n", database);
}

/*二叉树递归判断条件正误，
i是当前判断的一条记录在表中的位置索引，tabletemp是用于判断的临时表，单表查询时它指向单表，
多表查询时它是多表的笛卡尔乘积，conroot是条件二叉树根节点，当conroot为空时直接判断为TRUE，
主要用于无条件的查询和更新，删除等操作，有条件时，即最初传入的conroot不为空时，不会触发这条判断执行*/
_Bool whereTF(int i, struct table *tabletemp, struct conditions_def *conroot){
	if(conroot == NULL){
		return TRUE;
	}
	if(conroot->cmp_op == 7){
		return whereTF(i, tabletemp, conroot->left) && whereTF(i, tabletemp, conroot->right);
	}
	else if(conroot->cmp_op == 8){
		return whereTF(i, tabletemp, conroot->left) || whereTF(i, tabletemp, conroot->right);
	}
	else{
		if(conroot->litem->pos == NULL){
			int k;
			for(k = 0; k < tabletemp->flen; k++){
				if(strcmp(tabletemp->ffield[k].name, conroot->litem->field) == 0){
					conroot->litem->pos = &tabletemp->ffield[k];
					break;
				}
			}
			if(conroot->litem->pos == NULL){
				printf("error: 	Field %s doesn't exist!\n", conroot->litem->field);
				return FALSE;
			}
		}
		if(conroot->cmp_op == 1){
			if(conroot->type == 0)
				return conroot->litem->pos->key[i].intkey == conroot->intv;
			else
				return strcmp(conroot->litem->pos->key[i].skey, conroot->strv) == 0;
		}
		else if(conroot->cmp_op == 2){
			if(conroot->type == 0){
				return conroot->litem->pos->key[i].intkey > conroot->intv;
			}
			else{
				printf("error: String can not compare!\n");
				return FALSE;
			}
		}
		else if(conroot->cmp_op == 3){
			if(conroot->type == 0)
				return conroot->litem->pos->key[i].intkey < conroot->intv;
			else{
				printf("error: String can not compare!\n");
				return FALSE;
			}			
		}
		else if(conroot->cmp_op == 4){
			if(conroot->type == 0)
				return conroot->litem->pos->key[i].intkey >= conroot->intv;
			else{
				printf("error: String can not compare!\n");
				return FALSE;
			}			
		}
		else if(conroot->cmp_op == 5){
			if(conroot->type == 0)
				return conroot->litem->pos->key[i].intkey <= conroot->intv;
			else{
				printf("error: String can not compare!\n");
				return FALSE;
			}				
		}
		else {
			if(conroot->type == 0)
				return conroot->litem->pos->key[i].intkey != conroot->intv;
			else
				return strcmp(conroot->litem->pos->key[i].skey, conroot->strv) != 0;			
		}
	}
}

/*查询操作
itemroot是选择的字段链表根节点，若为*即全选则传入NULL，tableroot是选择的表根节点，
conroot是条件二叉树根节点，若无条件则传入NULL
首先找到查询的表，找到以后更新每个table_def结构的pos变量，指向对应的表，
然后判断是否是单表，
若为单表，tabletemp指向该表，再判断itemroot是否为空，若为空表示全选，依次将整个表打印出来，
提示成功，返回。若不为单表，即为2个表联合查询，那么先遍历两个表，找到第一组名称相同且数据类型相同的字段，作为主码，
将字段值相同的记录进行合并，构成新表，存入tabletemp中，若没有字段相同的，将笛卡尔乘积存入tabletemp中，然后判断itemroot
是否为空，若为空，判断并打印所有字段记录，若不为空，判断并打印对应的字段记录*/
void selectWhere(struct item_def *itemroot, struct table_def *tableroot, struct conditions_def *conroot){
	struct mydb *dbtemp = NULL;
	struct table_def *tableptr = NULL;
	struct table *tabletemp = NULL;
	struct item_def *itemtemp = NULL;
	int i, j, k, m, n, len1, len2, pk1 = -1, pk2 = -1;
	itemroot = converseItems(itemroot);
	if(dbroot != NULL)
		dbtemp = dbroot;
	else{
		printf("error: Please create a database first!\n");
		freeCons(conroot);
		freeItems(itemroot);
		freeTables(tableroot);
		return;
	}
	while(dbtemp != NULL){
		if(strcmp(dbtemp->name,database) == 0){
			tableptr = tableroot;
			while(tableptr != NULL){
				tabletemp = dbtemp->tbroot;
				while(tabletemp != NULL){
					if(strcmp(tabletemp->name, tableptr->table) == 0){
						tableptr->pos = tabletemp;
						break;
					}
					tabletemp = tabletemp->next;
				}
				if(tabletemp == NULL){
					printf("error: 	Table %s doesn't exist!\n", tableptr->table);
					freeCons(conroot);
					freeItems(itemroot);
					freeTables(tableroot);
					return;
				}
				tableptr = tableptr->next;
			}
			if(tableroot->next == NULL){
				tabletemp = tableroot->pos;
				if(itemroot == NULL){
					for(j = tabletemp->flen - 1; j >= 0; j--){
						printf("%-20s  ", tabletemp->ffield[j].name);
					}
					printf("\n");
					for(i = 0; i < tabletemp->ilen; i++){
						if(whereTF(i, tabletemp, conroot) == TRUE){
							for(j = tabletemp->flen - 1; j >= 0 ; j--){
								if(tabletemp->ffield[j].type == 0)
									printf("%-20d  ", tabletemp->ffield[j].key[i].intkey);
								else
									printf("%-20s  ", tabletemp->ffield[j].key[i].skey);
							}
							printf("\n");
						}
					}
					freeCons(conroot);
					freeTables(tableroot);
					return;
				}
			}
			else{
				tableroot->next->next = tableroot;
				tableroot = tableroot->next;
				tableroot->next->next = NULL;
				len1 = tableroot->pos->flen;
				len2 = tableroot->next->pos->flen;
				tabletemp = (struct table *)malloc(sizeof(struct table));
				for(i = len1 - 1; i >= 0; i--){
					for(j = len2 - 1; j >= 0; j--){
						if(strcmp(tableroot->pos->ffield[i].name, tableroot->next->pos->ffield[j].name) == 0 && tableroot->pos->ffield[i].type == tableroot->next->pos->ffield[j].type){
							pk1 = i;
							pk2 = j;
							break;
						}
					}
					if(strcmp(tableroot->pos->ffield[i].name, tableroot->next->pos->ffield[j].name) == 0)
						break;
				}
				if(pk2 == -1){
					tabletemp->ffield = (struct field *)malloc((len1 + len2)*sizeof(struct field));
					tabletemp->flen = len1 + len2;
					k = 0;
					for(i = len1 - 1; i >= 0; i--){
						strcpy(tabletemp->ffield[k].name, tableroot->pos->ffield[i].name);
						k++;
					}
					for(i = len2 - 1; i >= 0; i--){
						strcpy(tabletemp->ffield[k].name, tableroot->next->pos->ffield[i].name);
						k++;
					}
					n = 0;
					for(i = 0; i < tableroot->pos->ilen; i++){
						for(j = 0; j < tableroot->next->pos->ilen; j++){
							k = 0;
							for(m = len1 - 1; m >= 0; m--){
								tabletemp->ffield[k].type = tableroot->pos->ffield[m].type;
								if(tableroot->pos->ffield[m].type == 0)
									tabletemp->ffield[k].key[n].intkey = tableroot->pos->ffield[m].key[i].intkey;
								else
									strcpy(tabletemp->ffield[k].key[n].skey, tableroot->pos->ffield[m].key[i].skey);
								k++;
							}
							for(m = len2 - 1; m >= 0; m--){
								tabletemp->ffield[k].type = tableroot->next->pos->ffield[m].type;
								if(tableroot->next->pos->ffield[m].type == 0)
									tabletemp->ffield[k].key[n].intkey = tableroot->next->pos->ffield[m].key[j].intkey;
								else
									strcpy(tabletemp->ffield[k].key[n].skey, tableroot->next->pos->ffield[m].key[j].skey);
								k++;
							}
							n++;								
						}
					}
					tabletemp->ilen = n;
				}
				else{
					tabletemp->ffield = (struct field *)malloc((len1 + len2 - 1)*sizeof(struct field));
					tabletemp->flen = len1 + len2 - 1;
					k = 0;
					for(i = len1 - 1; i >= 0; i--){
						strcpy(tabletemp->ffield[k].name, tableroot->pos->ffield[i].name);
						k++;
					}
					for(i = len2 - 1; i >= 0; i--){
						if(i == pk2)
							continue;
						strcpy(tabletemp->ffield[k].name, tableroot->next->pos->ffield[i].name);
						k++;
					}
					n = 0;
					for(i = 0; i < tableroot->pos->ilen; i++){
						for(j = 0; j < tableroot->next->pos->ilen; j++){
							if(tableroot->pos->ffield[pk1].type == 0 && tableroot->pos->ffield[pk1].key[i].intkey == tableroot->next->pos->ffield[pk2].key[j].intkey || tableroot->pos->ffield[pk1].type == 1 && strcmp(tableroot->pos->ffield[pk1].key[i].skey, tableroot->next->pos->ffield[pk2].key[j].skey) == 0){
								k = 0;
								for(m = len1 - 1; m >= 0; m--){
									tabletemp->ffield[k].type = tableroot->pos->ffield[m].type;
									if(tableroot->pos->ffield[m].type == 0)
										tabletemp->ffield[k].key[n].intkey = tableroot->pos->ffield[m].key[i].intkey;
									else
										strcpy(tabletemp->ffield[k].key[n].skey, tableroot->pos->ffield[m].key[i].skey);
									k++;
								}
								for(m = len2 - 1; m >= 0; m--){
									if(m == pk2)
										continue;
									tabletemp->ffield[k].type = tableroot->next->pos->ffield[m].type;
									if(tableroot->next->pos->ffield[m].type == 0)
										tabletemp->ffield[k].key[n].intkey = tableroot->next->pos->ffield[m].key[j].intkey;
									else
										strcpy(tabletemp->ffield[k].key[n].skey, tableroot->next->pos->ffield[m].key[j].skey);
									k++;
								}
								n++;								
							}
						}
					}
					tabletemp->ilen = n;
				}
			}
			itemtemp = itemroot;
			while(itemtemp != NULL){
				for(i = 0; i < tabletemp->flen; i++){
					if(strcmp(itemtemp->field, tabletemp->ffield[i].name) == 0){
						itemtemp->pos = &tabletemp->ffield[i];
						break;
					}
				}
				if(i == tabletemp->flen){
					printf("error: Column name does not match the table definition!\n");
					freeCons(conroot);
					freeItems(itemroot);
					freeTables(tableroot);
					return;
				}
				itemtemp = itemtemp->next;
			}
			if(itemroot == NULL){
				for(j = 0; j < tabletemp->flen; j++){
					printf("%-20s  ", tabletemp->ffield[j].name);
				}
				printf("\n");
			}
			else{
				itemtemp = itemroot;
				while(itemtemp != NULL){
					printf("%-20s  ", itemtemp->field);
					itemtemp = itemtemp->next;
				}
				printf("\n");				
			}
			for(i = 0; i < tabletemp->ilen; i++){
				if(whereTF(i, tabletemp, conroot) == TRUE){
					if(itemroot == NULL){
						for(j = 0; j < tabletemp->flen; j++){
							if(tabletemp->ffield[j].type == 0)
								printf("%-20d  ", tabletemp->ffield[j].key[i].intkey);
							else
								printf("%-20s  ", tabletemp->ffield[j].key[i].skey);
						}
						printf("\n");
					}
					else{
						itemtemp = itemroot;
						while(itemtemp != NULL){
							if(itemtemp->pos->type == 0)
								printf("%-20d  ", itemtemp->pos->key[i].intkey);
							else
								printf("%-20s  ", itemtemp->pos->key[i].skey);
							itemtemp = itemtemp->next;
						}
						printf("\n");				
					}
				}
			}
			freeCons(conroot);
			freeItems(itemroot);
			freeTables(tableroot);
			return;
		}
		dbtemp = dbtemp->next;
	}
	freeCons(conroot);
	freeItems(itemroot);
	freeTables(tableroot);
	printf("error: Database %s doesn't exist!\n", database);
}

/*删除操作。
tableval为做删除的表的名称，conroot为条件二叉树的根节点，若为NULL，表示删除全部记录，
首先找到表，然后遍历表的每一条记录，若符合条件，则将后面的记录统一往前移动一条，将原纪录覆盖*/
void deletes(char *tableval, struct conditions_def *conroot){
	struct mydb *dbtemp = NULL;
	struct table *tabletemp = NULL;
	int i,j,k;
	if(dbroot != NULL)
		dbtemp = dbroot;
	else{
		printf("error: Please create a database first!\n");
		freeCons(conroot);
		return;
	}
	while(dbtemp != NULL){
		if(strcmp(dbtemp->name,database) == 0){
			tabletemp = dbtemp->tbroot;
			while(tabletemp != NULL){
				if(strcmp(tabletemp->name, tableval) == 0){
					for(i = 0; i < tabletemp->ilen; i++){
						if(whereTF(i, tabletemp, conroot) == TRUE){
							for(k = i; k < tabletemp->ilen-1; k++){
								for(j = 0; j < tabletemp->flen; j++){
									if(tabletemp->ffield[j].type == 0)
										tabletemp->ffield[j].key[k].intkey = tabletemp->ffield[j].key[k+1].intkey;
									else
										strcpy(tabletemp->ffield[j].key[k].skey, tabletemp->ffield[j].key[k+1].skey);
								}
							}
							tabletemp->ilen--;
							i--;
						}
					}
					printf("Delete successfully!\n");
					freeCons(conroot);
					return;
				}
				tabletemp = tabletemp->next;
			}
			printf("error: The table doesn't exist!\n");
			freeCons(conroot);
			return;
		}
		dbtemp = dbtemp->next;
	}
	freeCons(conroot);
	printf("error: Database %s doesn not exist!\n", database);	
}

/*更新操作。
tableval是要更新的表名称，uproot为赋值结构链表，conroot为条件二叉树的根节点。
先找到要更新的表，然后遍历赋值结构链表，找到对应的字段，并将其地址赋给每个赋值结构的pos变量，
便于后续操作，然后遍历表的每一条记录，判断符合条件则将对应的字段更新为对应的值*/
void updates(struct table *tabletemp, struct upcon_def *uptemp, struct conditions_def *conroot)
{
    int i, j;
    
    if(tabletemp == NULL)
    {
        printf("表不存在！\n");
        return;
    }
    
    if(uptemp == NULL)
    {
        printf("更新条件为空！\n");
        return;
    }
    
    if(conroot == NULL)
    {
        printf("WHERE条件为空！\n");
        return;
    }
    
    for(i = 0; i < tabletemp->flen; i++)
    {
        if(strcmp(tabletemp->ffield[i].name, uptemp->field) == 0)
        {
            if(tabletemp->ffield[i].type == uptemp->type)
            {
                if(tabletemp->ffield[i].type == 0)
                {
                    for(j = 0; j < tabletemp->ilen; j++)
                    {
                        if(whereTF(j, tabletemp, conroot))
                        {
                            tabletemp->ffield[i].key[j].intkey = uptemp->value.intkey;
                        }
                    }
                }
                else
                {
                    for(j = 0; j < tabletemp->ilen; j++)
                    {
                        if(whereTF(j, tabletemp, conroot))
                        {
                            strcpy(tabletemp->ffield[i].key[j].skey, uptemp->value.skey);
                        }
                    }
                }
                printf("更新成功！\n");
                return;
            }
            else
            {
                printf("类型不匹配！\n");
                return;
            }
        }
    }
    printf("字段不存在！\n");
}

/*丢弃表，即链表的删除节点操作，删除时释放内存*/
void dropTable(char *tableval){
	struct mydb *dbtemp = NULL;
	struct table *tabletemp = NULL;
	struct table *tabletod = NULL;
	int i,j;
	if(dbroot != NULL)
		dbtemp = dbroot;
	else{
		printf("error: Please create a database first!\n");
		return;
	}
	while(dbtemp != NULL){
		if(strcmp(dbtemp->name,database) == 0){
			tabletemp = dbtemp->tbroot;
			if(strcmp(dbtemp->tbroot->name, tableval) == 0){
				tabletod = dbtemp->tbroot;
				dbtemp->tbroot = dbtemp->tbroot->next;
				free(tabletod->ffield);
				free(tabletod);
				printf("Drop table successfully!\n");
				return;
			}
			if(dbtemp->tbroot->next == NULL)
				dbtemp->tbroot = NULL;
			while(tabletemp->next != NULL){
				if(strcmp(tabletemp->next->name, tableval) == 0){
					tabletod = tabletemp->next;
					tabletemp->next = tabletemp->next->next;
					free(tabletod->ffield);
					free(tabletod);
					printf("Drop table successfully!\n");
					return;
				}
				tabletemp = tabletemp->next;
			}
			if(strcmp(tabletemp->name, tableval) == 0){
				free(tabletemp->ffield);
				free(tabletemp);
				printf("Drop table successfully!\n");
				return;
			}			
			printf("error: The table doesn't exist!\n");
			return;
		}
		dbtemp = dbtemp->next;
	}
	printf("error: Database %s doesn not exist!\n", database);		
}

/*丢弃数据库，即链表的删除节点操作，删除时释放内存*/
void dropDB(char *dbname){
	struct mydb *dbtemp = NULL;
	struct mydb *dbtod = NULL;
	struct table *tabletemp = NULL;
	struct table *tabletod = NULL;
	int i,j;
	if(dbroot != NULL)
		dbtemp = dbroot;
	else{
		printf("error: Please create a database first!\n");
		return;
	}
	if(strcmp(dbroot->name, dbname) == 0){
		tabletemp = dbroot->tbroot;
		while(tabletemp != NULL){
			tabletod = tabletemp->next;
			free(tabletemp->ffield);
			free(tabletemp);
			tabletemp = tabletod;				
		}
		dbtod = dbroot;
		dbroot = dbroot->next;
		free(dbtod);
		printf("Drop database successfully!\n");
		return;		
	}
	if(dbroot->next == NULL)
		dbroot = NULL;
	while(dbtemp->next != NULL){
		if(strcmp(dbtemp->next->name, dbname) == 0){
			tabletemp = dbtemp->next->tbroot;
			while(tabletemp != NULL){
				tabletod = tabletemp->next;
				free(tabletemp->ffield);
				free(tabletemp);
				tabletemp = tabletod;				
			}
			dbtod = dbtemp->next;
			dbtemp->next = dbtemp->next->next;
			free(dbtod);
			printf("Drop database successfully!\n");
			return;
		}
		dbtemp = dbtemp->next;
	}
	if(strcmp(dbtemp->name, dbname) == 0){
		tabletemp = dbtemp->tbroot;
		while(tabletemp != NULL){
			tabletod = tabletemp->next;
			free(tabletemp->ffield);
			free(tabletemp);
			tabletemp = tabletod;				
		}
		free(dbtemp);
		printf("Drop database successfully!\n");
		return;
	}	
	printf("error: Database %s doesn not exist!\n", database);	
}