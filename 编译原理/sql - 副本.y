%{
/* 头文件与全局函数声明 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"  // 包含自定义数据结构声明

/* 接口声明 */
extern int yylex();       // 词法分析器入口
extern int yyparse();     // 语法分析器入口
extern FILE *yyin;        // 输入文件指针
extern char *yytext;      // 当前词法单元文本
extern int yylineno;      // 当前行号计数器

char database[64] = {0};    // 当前使用的数据库名称存储
extern struct mydb *dbroot; // 全局数据库链表头指针

/* 错误处理函数 */
void yyerror(const char *str) {
    fprintf(stderr, "error: %s\n", str);  // 输出带错误定位的提示信息
}

/* 输入结束处理函数 */
int yywrap() {
    return 1;  // 表示输入结束
}

/* 主程序入口 */
int main() {
    printf("SQL>");       // 显示交互提示符
    return yyparse();     // 启动语法分析器
}
%}

/* 联合体定义 - 用于存储不同类型的语义值 */
%union{  
    int intval;              // 整数值存储
    char *strval;            // 字符串值存储
    struct hyper_items_def *Citemsval;  // 表字段定义链表
    struct value_def *valueval;         // 值列表节点
    struct item_def *itemval;           // 查询字段项
    struct conditions_def *conval;      // 条件表达式节点
    struct table_def *tbval;            // 表名链表节点
    struct upcon_def *updateval;        // 更新条件节点
}

/* 终结符声明（词法单元）*/
%token SELECT FROM WHERE AND OR DROP DELETE TABLE CREATE INTO VALUES INSERT UPDATE SET SHOW DATABASE DATABASES TABLES EXIT USE
%token <intval> NUMBER    // 绑定到intval的数值类型
%token <strval> STRING ID INT CHAR  // 绑定到strval的字符串类型

/* 非终结符类型声明 */
%type <intval> comparator          // 比较运算符类型
%type <Citemsval> hyper_items create_items  // 表字段定义相关
%type <valueval> value_list value           // 值列表相关
%type <itemval> item item_list              // 查询字段列表相关
%type <conval> condition conditions         // 条件表达式相关
%type <tbval> tables                        // 表名列表相关
%type <updateval> up_cond up_conds          // 更新条件相关

/* 运算符优先级定义 */
%left OR     // 最低优先级
%left AND    // 高于OR

%%

/* 语法规则部分 */

/* 语句集合规则 */
statements: statements statement  // 多语句递归定义
    | statement                    // 单语句情况
    ;

/* 单个语句类型 */
statement: createsql | showsql | selectsql | insertsql | deletesql | updatesql | dropsql | exitsql | usesql;

/* USE语句规则 */
usesql: USE ID ';' '\n' {          // 语法：USE 数据库名;
    printf("\n");
    useDB($2);                     // 调用数据库切换函数
    printf("\nSQL>");
}

/* SHOW语句规则 */
showsql: SHOW DATABASES ';' '\n' { // 显示所有数据库
    printf("\n");
    showDB();                      // 调用数据库列表显示函数
    printf("\nSQL>");
}
| SHOW TABLES ';' '\n' {          // 显示当前数据库所有表
    printf("\n");
    showTable();                  // 调用表列表显示函数
    printf("\nSQL>");
}

/* CREATE语句规则 */
createsql: CREATE TABLE ID '(' hyper_items ')' ';' '\n' {  // 创建表语法
    printf("\n");
    createTable($3, $5);          // $3=表名，$5=字段定义链表
    printf("\nSQL>");
}
| CREATE DATABASE ID ';' '\n' {  // 创建数据库语法
    strcpy(database, $3);        // 记录当前数据库名
    printf("\n");
    createDB();                  // 调用数据库创建函数
    printf("\nSQL>");
}

/* SELECT语句规则 */
selectsql: SELECT '*' FROM tables ';' '\n' {  // 全字段查询
    printf("\n");
    selectWhere(NULL, $4, NULL); // $4=表名链表，NULL表示无字段列表
    printf("\nSQL>");
}
| SELECT item_list FROM tables ';' '\n' {  // 带字段列表查询
    printf("\n");
    selectWhere($2, $4, NULL);   // $2=字段列表，$4=表名链表
    printf("\nSQL>");
}        
| SELECT '*' FROM tables WHERE conditions ';' '\n' {  // 带条件全字段查询
    printf("\n");
    selectWhere(NULL, $4, $6);  // $6=条件表达式树
    printf("\nSQL>");
}
| SELECT item_list FROM tables WHERE conditions ';' '\n' {  // 完整SELECT语法
    printf("\n");
    selectWhere($2, $4, $6);    // $2=字段列表，$4=表列表，$6=条件
    printf("\nSQL>");
}

/* DELETE语句规则 */
deletesql: DELETE FROM ID ';' '\n' {  // 无条件删除
    printf("\n");
    deletes($3, NULL);         // $3=表名，NULL表示无删除条件
    printf("\nSQL>");
}
| DELETE FROM ID WHERE conditions ';' '\n' {  // 条件删除
    printf("\n");
    deletes($3, $5);          // $5=条件表达式树
    printf("\nSQL>");
}

/* INSERT语句规则 */
insertsql: INSERT INTO ID VALUES '(' value_list ')' ';' '\n' {  // 全字段插入
    printf("\n");
    multiInsert($3, NULL, $6);  // $3=表名，$6=值列表
    printf("\nSQL>");
}
| INSERT INTO ID '(' item_list ')' VALUES '(' value_list ')' ';' '\n' {  // 指定字段插入
    printf("\n");
    multiInsert($3, $5, $9);   // $5=字段列表，$9=值列表
    printf("\nSQL>");
}

/* UPDATE语句规则 */
updatesql: UPDATE ID SET up_conds ';' '\n' {  // 无条件更新
    // 数据库存在性检查
    struct mydb *dbtemp = dbroot;
    struct table *tabletemp = NULL;
    while(dbtemp != NULL) {
        if(strcmp(dbtemp->name, database) == 0) {
            // 遍历表链表查找目标表
            tabletemp = dbtemp->tbroot;
            while(tabletemp != NULL) {
                if(strcmp(tabletemp->name, $2) == 0) {
                    updates(tabletemp, $4, NULL);  // $4=更新条件链表
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
| UPDATE ID SET up_conds WHERE conditions ';' '\n' {  // 条件更新
    // 类似上述数据库/表存在性检查流程
    struct mydb *dbtemp = dbroot;
    struct table *tabletemp = NULL;
    while(dbtemp != NULL) {
        if(strcmp(dbtemp->name, database) == 0) {
            tabletemp = dbtemp->tbroot;
            while(tabletemp != NULL) {
                if(strcmp(tabletemp->name, $2) == 0) {
                    updates(tabletemp, $4, $6);  // $6=WHERE条件表达式
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

/* DROP语句规则 */
dropsql: DROP TABLE ID ';' '\n' {  // 删除表
    printf("\n");
    dropTable($3);          // $3=表名
    printf("\nSQL>");
}
| DROP DATABASE ID ';' '\n' {  // 删除数据库
    printf("\n");
    dropDB($3);            // $3=数据库名
    printf("\nSQL>");
}

/* 退出命令 */
exitsql: EXIT ';' {
    printf("\n");
    printf("exit with code 0!\n");
    exit(0);
}

/* 字段定义规则 */
create_items: ID INT {  // 整数字段定义
    $$ = (struct hyper_items_def *)malloc(sizeof(struct hyper_items_def));
    strcpy($$->field, $1);  // 存储字段名
    $$
->type = 0;           // 类型标记为整数
    $$->next = NULL;        // 初始化链表指针
}
| ID CHAR '(' NUMBER ')' {  // 定长字符字段定义
    $$ = (struct hyper_items_def *)malloc(sizeof(struct hyper_items_def));
    strcpy($$->field, $1);
    $$
->type = 1;           // 类型标记为字符
    $$->next = NULL;
}

/* 字段定义链表构建 */
hyper_items: create_items {  // 单字段情况
    $$
 = $1;
}
| hyper_items ',' create_items {  // 多字段递归组合
    $$ = $3;         // 新节点成为链表头
    $$
->next = $1;   // 原有链表接续
}

/* 查询字段项处理 */
item: ID {  // 单个查询字段
    $$ = (struct item_def *)malloc(sizeof(struct item_def));
    strcpy($$
->field, $1);  // 存储字段名称
    $$->pos = NULL;
    $$
->next = NULL;
}

/* 字段列表链表构建 */
item_list: item {  // 单字段
    $$ = $1;                
}
| item_list ',' item {  // 多字段递归组合
    $$
 = $3;
    $$->next = $1;  // 头插法构建链表
}

/* 值节点处理 */
value: NUMBER {  // 整数值
    $$
 = ((struct value_def *)malloc(sizeof(struct value_def)));
    $$->value.intkey = $1;  // 存储整数值
    $$
->type = 0;           // 类型标记
    $$->next = NULL;
}
| STRING {  // 字符串值
    $$ = ((struct value_def *)malloc(sizeof(struct value_def)));
    strcpy($$->value.skey, $1);  // 复制字符串
    $$
->type = 1;
    $$->next = NULL;
}

/* 值列表链表构建 */
value_list: value {  // 单值
    $$
 = $1;
}
| value_list ',' value {  // 多值递归组合
    $$ = $3;
    $$->next = $1;  // 头插法构建链表
}

/* 比较运算符处理 */
comparator: '=' {$$ = 1; }   // 运算符编码
    | '>' {$$ = 2; }
    | '<' {$$ = 3; }
    | ">=" {$$ = 4; }
    | "<=" {$$ = 5; }
    | '!' '=' {$$
 = 6; }  // 注意：需确保词法分析器支持"!="作为单一token

/* 条件表达式构建 */
condition: item comparator NUMBER {  // 整数比较条件
    $$ = ((struct conditions_def *)malloc(sizeof(struct conditions_def)));
    $$
->type = 0;           // 标记为整数比较
    $$->litem = $1;         // 左操作数（字段）
    $$
->intv = $3;          // 右操作数值
    $$->cmp_op = $2;        // 比较运算符编码
    $$
->left = NULL;
    $$->right = NULL;
}
| item comparator STRING {  // 字符串比较条件
    $$
 = ((struct conditions_def *)malloc(sizeof(struct conditions_def)));
    $$->type = 1;           // 标记为字符串比较
    $$->litem = $1;
    strcpy($$->strv, $3);   // 存储比较字符串
    $$
->cmp_op = $2;
    $$->left = NULL;
    $$
->right = NULL;
}

/* 复杂条件表达式树构建 */
conditions: condition {  // 基础条件
    $$ = $1;
}
| '(' conditions ')' {  // 括号优先级
    $$
 = $2;
}
| conditions AND conditions {  // 逻辑与组合
    $$ = ((struct conditions_def *)malloc(sizeof(struct conditions_def)));
    $$
->cmp_op = 7;       // 自定义AND操作码
    $$->left = $1;        // 左子树
    $$
->right = $3;       // 右子树
}
| conditions OR conditions {  // 逻辑或组合
    $$ = ((struct conditions_def *)malloc(sizeof(struct conditions_def)));
    $$
->cmp_op = 8;       // 自定义OR操作码
    $$->left = $1;
    $$
->right = $3;
}

/* 表名列表处理 */
tables: ID {  // 单表查询
    $$ = ((struct table_def *)malloc(sizeof(struct table_def)));
    strcpy($$
->table, $1);
    $$->next = NULL;
}
| tables ',' ID {  // 多表连接
    $$ = ((struct table_def *)malloc(sizeof(struct table_def)));
    strcpy($$->table, $3);  // 存储新表名
    $$
->next = $1;          // 头插法构建链表
}

/* 更新条件处理 */
up_cond: ID '=' NUMBER {  // 整数字段更新
    $$ = ((struct upcon_def *)malloc(sizeof(struct upcon_def)));
    strcpy($$
->field, $1);  // 目标字段
    $$->type = 0;           // 整数类型标记
    $$
->value.intkey = $3;  // 新值
    $$->next = NULL;
}
| ID '=' STRING {  // 字符串字段更新
    $$ = ((struct upcon_def *)malloc(sizeof(struct upcon_def)));
    strcpy($$->field, $1);
    $$->type = 1;
    strcpy($$->value.skey, $3);  // 存储新字符串值
    $$
->next = NULL;                
}

/* 更新条件链表构建 */
up_conds: up_cond {  // 单个更新条件
    $$ = $1;
}
| up_conds ',' up_cond {  // 多个更新条件
    $$
 = $3;
    $$->next = $1;  // 头插法构建链表
}

%%