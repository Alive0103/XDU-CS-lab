#ifndef SQL_H
#define SQL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TRUE 1
#define FALSE 0

// 数据库结构
struct mydb {
    char name[50];
    struct table *tbroot;
    struct mydb *next;
};

// 表结构
struct table {
    char name[50];
    struct field *ffield;
    int flen;
    int ilen;
    struct table *next;
};

// 字段结构
struct field {
    char name[50];
    int type;  // 0 for int, 1 for string
    struct key {
        int intkey;
        char skey[50];
    } key[100];
};

// 项目结构
struct item_def {
    char field[50];
    struct field *pos;
    struct item_def *next;
};

// 超项目结构
struct hyper_items_def {
    char field[50];
    int type;
    struct hyper_items_def *next;
};

// 值结构
struct value_def {
    union {
        int intkey;
        char skey[50];
    } value;
    int type;
    struct value_def *next;
};

// 条件结构
struct conditions_def {
    int type;
    struct item_def *litem;
    int intv;
    char strv[50];
    int cmp_op;
    struct conditions_def *left;
    struct conditions_def *right;
};

// 表定义结构
struct table_def {
    char table[50];
    struct table *pos;
    struct table_def *next;
};

// 更新条件结构
struct upcon_def {
    char field[50];
    int type;
    union {
        int intkey;
        char skey[50];
    } value;
    struct upcon_def *next;
};

// 函数声明
void freeHItems(struct hyper_items_def *Hitemroot);
void freeCons(struct conditions_def *conroot);
void freeItems(struct item_def *itemroot);
void freeTables(struct table_def *tableroot);
void freeUpcon(struct upcon_def *uproot);
void freeVal(struct value_def *valroot);
void createDB();
void showDB();
void useDB(char *dbname);
void createTable(char *tableval, struct hyper_items_def *Hitemroot);
void showTable();
void multiInsert(char *tableval, struct item_def *itemroot, struct value_def *valroot);
_Bool whereTF(int i, struct table *tabletemp, struct conditions_def *conroot);
void selectWhere(struct item_def *itemroot, struct table_def *tableroot, struct conditions_def *conroot);
void deletes(char *tableval, struct conditions_def *conroot);
void updates(struct table *tabletemp, struct upcon_def *uptemp, struct conditions_def *conroot);
void dropTable(char *tableval);
void dropDB(char *dbname);
_Bool judge(struct table *tabletemp, int i, struct conditions_def *conroot);

#endif 