%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"

// interface
void debug_flex(char ipt_message[]);
void show_error(char ipt_message[]);
%}

comment                 (#.*(\n\r|\n))
data_float              [0-9]+[.]{1}[0-9]+
data_integer            [0-9]+
data_string             ([']{1}.*[']{1}|["]{1}.*["]{1})
end_line                "\n\r"|"\n"|";"
white_space             ([ \t])
symbol                  [=()-+*/^.]{1}
variable                (\$[a-zA-Z_][a-zA-Z_0-9]*)
k_word_print            "print"

%%


{comment}               {debug_flex("comment");}
{data_string}           {strcpy(yylval.type_string,yytext); return DATA_STRING;}
{k_word_print}          {return K_WORD_PRINT;}
{variable}              {strcpy(yylval.type_string,yytext); return VARIABLE;}
{symbol}                {return yytext[0];}
{data_float}            {yylval.type_float = atof(yytext); return DATA_FLOAT;}
{data_integer}          {yylval.type_float = atof(yytext); return DATA_INTEGER;}
{end_line}              {return END_LINE;}
{white_space}           {;}
.                       {printf("invalid character %c",yytext[0]); return yytext[0];}

%%


void debug_flex(char *ipt_message){
  char res[100] = "<< ";
  strcat(res, ipt_message);
  strcat(res, "\n");
  fputs(res, stderr);
}

void show_error(char ipt_message[]){
  printf("ERROR: %s\n", ipt_message);
}

int yywrap (void) {return 1;}