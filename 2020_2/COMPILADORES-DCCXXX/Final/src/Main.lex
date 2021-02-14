package compiler;

import java_cup.runtime.Symbol;

%%
%cup

LETTER=[A-Za-z]
ASCII_CHARACTER=[\x00-\x7F]
DIGIT=[0-9]
WHITESPACE=[ \t\n\r\n]

SIGN=[+-]?
SCALE_FACTOR="E"{SIGN}{UNSIGNED_INTEGER}

IDENTIFIER={LETTER}({LETTER}|{DIGIT})*
UNSIGNED_INTEGER={DIGIT}+
UNSIGNED_REAL={UNSIGNED_INTEGER}("."{DIGIT}*)?({SCALE_FACTOR})?

INTEGER_CONSTANT={UNSIGNED_INTEGER}
REAL_CONSTANT={UNSIGNED_REAL}
CHAR_CONSTANT="'"{ASCII_CHARACTER}"'"

%%

{WHITESPACE}+       { }

";"                { return new Symbol(sym.SEMICOLON); }
":"                { return new Symbol(sym.COLON); }
","                { return new Symbol(sym.COMMA); }
"("                { return new Symbol(sym.OPEN_PARENTHESIS); }
")"                { return new Symbol(sym.CLOSE_PARENTHESIS); }

"!="                { return new Symbol(sym.NEQ, yytext()); }
"<="                { return new Symbol(sym.LTE, yytext()); }
">="                { return new Symbol(sym.GTE, yytext()); }
"="                 { return new Symbol(sym.EQ, yytext()); }
"<"                 { return new Symbol(sym.LT, yytext()); }
">"                 { return new Symbol(sym.GT, yytext()); }
"NOT"               { return new Symbol(sym.NOT, yytext()); }

"+"                 { return new Symbol(sym.PLUS, yytext()); }
"-"                 { return new Symbol(sym.MINUS, yytext()); }
"or"                { return new Symbol(sym.OR, yytext()); }

":="                { return new Symbol(sym.ATTRIBUTION, yytext()); }

"*"                 { return new Symbol(sym.ASTERISC, yytext()); }
"/"                 { return new Symbol(sym.SLASH, yytext()); }
"div"               { return new Symbol(sym.DIV, yytext()); }
"mod"               { return new Symbol(sym.MOD, yytext()); }
"and"               { return new Symbol(sym.AND, yytext()); }

"sin"               { return new Symbol(sym.FUNCTION, yytext()); }
"log"               { return new Symbol(sym.FUNCTION, yytext()); }
"cos"               { return new Symbol(sym.FUNCTION, yytext()); }
"ord"               { return new Symbol(sym.FUNCTION, yytext()); }
"chr"               { return new Symbol(sym.FUNCTION, yytext()); }
"abs"               { return new Symbol(sym.FUNCTION, yytext()); }
"sqrt"              { return new Symbol(sym.FUNCTION, yytext()); }
"exp"               { return new Symbol(sym.FUNCTION, yytext()); }
"eof"               { return new Symbol(sym.FUNCTION, yytext()); }
"eoln"              { return new Symbol(sym.FUNCTION, yytext()); }

"program"           { return new Symbol(sym.PROGRAM_KEYWORD); }
"integer"           { return new Symbol(sym.INTEGER_KEYWORD); }
"real"              { return new Symbol(sym.REAL_KEYWORD); }
"boolean"           { return new Symbol(sym.BOOLEAN_KEYWORD); }
"char"              { return new Symbol(sym.CHAR_KEYWORD); }
"begin"             { return new Symbol(sym.BEGIN_KEYWORD); }
"end"               { return new Symbol(sym.END_KEYWORD); }
"if"                { return new Symbol(sym.IF_KEYWORD); }
"then"              { return new Symbol(sym.THEN_KEYWORD); }
"else"              { return new Symbol(sym.ELSE_KEYWORD); }
"while"             { return new Symbol(sym.WHILE_KEYWORD); }
"do"                { return new Symbol(sym.DO_KEYWORD); }
"until"             { return new Symbol(sym.UNTIL_KEYWORD); }
"read"              { return new Symbol(sym.READ_KEYWORD); }
"write"             { return new Symbol(sym.WRITE_KEYWORD); }
"goto"              { return new Symbol(sym.GOTO_KEYWORD); }
"false"             { return new Symbol(sym.FALSE_KEYWORD); }
"true"              { return new Symbol(sym.TRUE_KEYWORD); }

{INTEGER_CONSTANT}  { return new Symbol(sym.INTEGER_CONSTANT, yytext()); }
{REAL_CONSTANT}     { return new Symbol(sym.REAL_CONSTANT, yytext()); }
{CHAR_CONSTANT}     { return new Symbol(sym.CHAR_CONSTANT, yytext()); }
{IDENTIFIER}        { return new Symbol(sym.IDENTIFIER, yytext()); }