%{

#include <stdio.h>
#include <string.h>

int yylex();
int yyerror(char *s);

#include "functions.h"
#include "declaration.h"

void str_to_lower(char s[]);
void str_delete_at_index(char *ipt_str, int ipt_index);
void float_to_string(double ipt_1, char *ret);
char* str_combine(const char *s1, const char *s2);

int symbols[52];
int symbolVal(char symbol);
void updateSymbolVal(char symbol, int val);
void debug(char *ipt_message);


void var_set_number(char *ipt_name, double ipt_value);
void var_set(char *ipt_name, char *ipt_value);

void var_set_default(struct var *p_ipt_var);
void var_alloc_memory(void);
struct var * var_find_by_name(char *ipt_name);
void var_print(char *ipt_var_name);
void var_print_all();
enum var_type var_get_value_type(char *ipt_value, struct var *p_ipt_var);

void var_main(void);


%}

%token DATA_STRING
%token DATA_FLOAT
%token DATA_INTEGER
%token END_LINE
%token VARIABLE
%token K_WORD_PRINT

%type <type_string> DATA_STRING
%type <type_float> DATA_INTEGER
%type <type_float> DATA_FLOAT
%type <type_string> VARIABLE


%type <type_float> math_expression math_term

%start line

%left '+' '-'
%left '*' '/'
%right '^' '.'


%union {
  char type_string[100];
  int type_integer;
  double type_float;
};



//       | line DATA_STRING {
//           debug("STRING");
//           printf("Value: %s\n",$2);
//         }
//       | line DATA_INTEGER {
//           debug("INTEGER");
//           printf("Value: %f\n",$2);
//         }
//       | line DATA_FLOAT {
//           debug("FLOAT");
//           printf("Value: %f\n",$2);
//         }

%%

line  :
      | line END_LINE
      | line assignment
      | line K_WORD_PRINT DATA_STRING {
          printf("PRINT %s", $3);
        }
      | line K_WORD_PRINT math_expression {
          printf("PRINT %f", $3);
        }
      | line K_WORD_PRINT VARIABLE {
          printf("PRINT %s\n", $3);

          var_print_all();
          // struct var *p_var = var_find_by_name($3);
          // printf("VAR GET VALUE BY NAME %s - TYPE: %p", $3, p_var->type);
          // if(p_var != NULL){
          //   printf("VAR GET VALUE BY NAME - TYPE: %d",p_var->type);
          //   if(p_var->type==TYPE_STRING){
          //     printf("\n\nprint: %s\n\n",p_var->value_string);
          //   }
          //   if(p_var->type==TYPE_INTEGER){
          //     printf("\n\nprint: %d\n\n",p_var->value_integer);
          //   }
          //   if(p_var->type==TYPE_FLOAT){
          //     printf("\n\nprint: %f\n\n",p_var->value_float);
          //   }
          // }
          // else {
          //   printf("\n\nERROR: Variable %s is doesn't exist\n\n",$3);
          // }
        }
      ;

assignment  : VARIABLE '=' math_expression {
                debug("assignment number");
                var_set_number($1,$3);
                // var_print($1);
              }
            | VARIABLE '=' DATA_STRING {
                debug("assignment string");
                var_set($1,$3);
              }
            ;

math_expression : math_term {
                    $$ = $1;
                  }
                | math_expression '+' math_expression {
                    $$ = $1 + $3;
                  }
                | math_expression '-' math_expression {
                    $$ = $1 - $3;
                  }
                | math_expression '*' math_expression {
                    $$ = $1 * $3;
                  }
                | math_expression '/' math_expression {
                    $$ = $1 / $3;
                  }
                | math_expression '^' math_expression {
                    $$ = pow($1,$3);
                  }
                | '(' math_expression ')' {
                    $$ = $2;
                  }
                ;

math_term : DATA_INTEGER
          | DATA_FLOAT
          ;


%%

int yyerror(char *s){
	printf("ERROR: %s\n", s);
	return 0;
}

int main(void){
  return yyparse();
}