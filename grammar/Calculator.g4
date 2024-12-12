grammar Calculator;

// 程序的起始规则
prog: (statement NEWLINE+)* EOF;

// 基础表达式
primaryExpr: '(' expr ')' | INT | FLOAT;

// 乘除表达式
mulDivExpr:
	primaryExpr
	| mulDivExpr op = ('*' | '/') primaryExpr;

// 加减表达式
addSubExpr: mulDivExpr | addSubExpr op = ('+' | '-') mulDivExpr;

// 最顶层表达式
expr: addSubExpr;

// 函数调用语句
statement: FUNCTION_PRINT '(' expr ')';

// 定义数字
INT: [0-9]+;
FLOAT: [0-9]+ '.' [0-9]*;

// 打印函数
FUNCTION_PRINT: 'print';

// 忽略空格和换行符
NEWLINE: '\n' | '\r\n' | '\r';
WS: ' '+ -> skip;