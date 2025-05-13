%{
/* 定义段开始 */
// 包含标准库头文件
#include <stdio.h>   // 标准输入输出函数
#include <stdlib.h>  // 标准库函数，如 exit()
#include <string.h>  // 字符串处理函数，如 strdup()
#include "sql.h"     // 自定义的 SQL 相关头文件
#include "sql.tab.h" // Bison 生成的语法分析器头文件（包含 token 定义）

// 声明外部变量，用于跟踪行号
extern int yylineno;
%}
/* 定义段结束 */

%%

/* 规则段开始 */

/* 关键字处理（不区分大小写） */
/* 匹配 SELECT 或 select，返回 SELECT token */
select | SELECT { return SELECT; }

/* 匹配 DROP 或 drop，返回 DROP token */
drop | DROP { return DROP; }

/* 匹配 TABLE 或 table，返回 TABLE token */
table | TABLE { return TABLE; }

/* 匹配 TABLES 或 tables，返回 TABLES token */
tables | TABLES { return TABLES; }

/* 匹配 DATABASE 或 database，返回 DATABASE token */
database | DATABASE { return DATABASE; }

/* 匹配 DATABASES 或 databases，返回 DATABASES token */
databases | DATABASES { return DATABASES; }

/* 匹配 CREATE 或 create，返回 CREATE token */
create | CREATE { return CREATE; }

/* 匹配 INSERT 或 insert，返回 INSERT token */
insert | INSERT { return INSERT; }

/* 匹配 UPDATE 或 update，返回 UPDATE token */
update | UPDATE { return UPDATE; }

/* 匹配 SET 或 set，返回 SET token */
set | SET { return SET; }

/* 匹配 DELETE 或 delete，返回 DELETE token */
delete | DELETE { return DELETE; }

/* 匹配 FROM 或 from，返回 FROM token */
from | FROM { return FROM; }

/* 匹配 WHERE 或 where，返回 WHERE token */
where | WHERE { return WHERE; }

/* 匹配 INTO 或 into，返回 INTO token */
into | INTO { return INTO; }

/* 匹配 VALUES 或 values，返回 VALUES token */
values | VALUES { return VALUES; }

/* 匹配 AND 或 and，返回 AND token */
and | AND { return AND; }

/* 匹配 OR 或 or，返回 OR token */
or | OR { return OR; }

/* 匹配 INT 或 int，返回 INT token */
int | INT { return INT; }

/* 匹配 CHAR 或 char，返回 CHAR token */
char | CHAR { return CHAR; }

/* 匹配 SHOW 或 show，返回 SHOW token */
show | SHOW { return SHOW; }

/* 匹配 EXIT 或 exit，返回 EXIT token */
exit | EXIT { return EXIT; }

/* 匹配 USE 或 use，返回 USE token */
use | USE { return USE; }

/* 符号处理 */
/* 匹配分号、括号、星号、逗号等符号，直接返回对应字符的 ASCII 值 */
[;] | [(] | [)] | [*] | [,] { return *yytext; }

/* 比较运算符处理 */
"<=" | ">=" | "!" | "<" | ">" | "=" { return *yytext; } 

/* 字符串字面量处理 */
/* 匹配单引号括起的字符串（至少包含一个字母，后接字母/数字/下划线） */
'[A-Za-z][A-Za-z0-9_]*' {
    yylval.strval = strdup(yytext); // 复制字符串内容到 yylval（用于传递值给语法分析器）
    return STRING; // 返回 STRING token
}

/* 标识符处理 */
/* 匹配以字母开头，后接字母/数字/下划线的标识符 */
[A-Za-z][A-Za-z0-9_]* {
    yylval.strval = strdup(yytext); // 复制标识符名称
    return ID; // 返回 ID token
}

/* 数字处理 */
/* 匹配整数 */
[0-9]+ {
    yylval.intval = atoi(yytext); // 将字符串转换为整数值
    return NUMBER; // 返回 NUMBER token
}

/* 换行符处理（可能用于跟踪行号） */
\n {
    return *yytext; // 返回换行符本身（通常建议在此处增加 yylineno）
}

/* 忽略空白字符 */
[ \t]+ { /* 不做任何操作 */ }

%%
/* 规则段结束 */