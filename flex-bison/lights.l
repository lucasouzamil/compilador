%{
#include "ast.h"
#include "lights.tab.h"
#include <stdlib.h>
#include <string.h>

#define SET_INT(v)  (yylval.ival = (v))
#define SET_STR(v)  (yylval.sval = strdup(v))
%}

/* ----------  TOKENS  ---------- */
%%
[ \t\r]+                 ;                       /* espaços            */
"//".*                   ;                       /* comentários linha  */
\n                       { return NEWLINE; }

"strip"                  { return T_STRIP; }
"if"                     { return T_IF; }
"else"                   { return T_ELSE; }
"while"                  { return T_WHILE; }
"for"                    { return T_FOR; }
"loop"                   { return T_LOOP; }
"forever"                { return T_FOREVER; }
"set"                    { return T_SET; }
"color"                  { return T_COLOR; }     
"wait"                   { return T_WAIT; }
"rotate"                 { return T_ROTATE; }
"dir"                    { return T_DIR; }
"fade"                   { return T_FADE; }
"hsv"                    { return T_HSV; }
"left"                   { return T_LEFT; }
"right"                  { return T_RIGHT; }

"=="                     { return EQ;  }
"!="                     { return NEQ; }
"<="                     { return LE;  }
">="                     { return GE;  }
"&&"                     { return AND; }
"||"                     { return OR;  }
".."                     { return DOTDOT; }

"#"[0-9a-fA-F]{6}        { SET_STR(yytext); return COLOR_HEX; }   /* cor #RRGGBB */
[0-9]+ms                 { SET_STR(yytext); return TIME_LIT; }    /* tempo em ms */
[0-9]+s                  { SET_STR(yytext); return TIME_LIT; }    /* tempo em  s */

[0-9]+                   { SET_INT(atoi(yytext)); return INT; }

[+]                      { return '+'; }
[-]                      { return '-'; }
[*]                      { return '*'; }
[/]                      { return '/'; }
[%]                      { return '%'; }
[!]                      { return '!'; }
[<]                      { return '<'; }
[>]                      { return '>'; }
[=]                      { return '='; }
[(]                      { return '('; }
[)]                      { return ')'; }
[{]                      { return '{'; }
[}]                      { return '}'; }
[,]                      { return ','; }
[;]                      { return ';'; }

[a-zA-Z_][a-zA-Z0-9_]*   { SET_STR(yytext); return ID; }

.                        { fprintf(stderr,"Caractere inválido: %s\n",yytext); }
%%

int yywrap(void) { return 1; }
