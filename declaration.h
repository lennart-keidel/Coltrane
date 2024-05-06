#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// variable type enum
enum var_type {
  TYPE_STRING,
  TYPE_INTEGER,
  TYPE_FLOAT,
  TYPE_BOOLEAN,
  TYPE_EMPTY
};


// boolean value enum
enum var_value_boolean {
  FALSE,
  TRUE
};


// variable struct
struct var {
  char *name;
  enum var_type type;
	long value_integer;
  double value_float;
  char *value_string;
  enum var_value_boolean value_boolean;
  struct var *next_node;
	struct var *prev_node;
};

struct var *variable_first_node = NULL;
struct var *variable_last_node = NULL;


long int variable_cnt = 0; // global count of amount of saved variables
struct var *p_variable; // pointer to variable struct, dynmacily allocate new memory





// allocate new memory for a variable
void var_alloc_memory(void){
  p_variable = malloc(sizeof(struct var) * (variable_cnt + 1)); // allocate amount of byte per struct times the amount of variables stored
}




// get pointer to variable-struct by name of variable
struct var * var_find_by_name(char *ipt_name){

  // iterate through linked list
  // compare name value
  // return pointer if equal
  // return NULL if not found
  struct var *p_next = variable_last_node;
	while(p_next != NULL){

		if(p_next->name == ipt_name){
      return p_next;
    }

		p_next = (p_next->prev_node);
	}
  return NULL;
}



// delete variable
void var_delete(struct var *p_ipt_var){

  // if input is no pointer
  if(p_ipt_var == NULL){
    debug("DELETE VARIBALE: NO POINTER");
    return;
  }

  // if not only one item in list
  if(p_ipt_var->prev_node != NULL && p_ipt_var->next_node != NULL){

    // if last item
    if(p_ipt_var->next_node == NULL){
      variable_last_node = p_ipt_var->prev_node;
      p_ipt_var->prev_node->next_node = p_ipt_var->next_node;
    }

    // if first item
    else if(p_ipt_var->prev_node == NULL){
      p_ipt_var->next_node->prev_node = p_ipt_var->prev_node;
    }

    // if not first, not last item
    else {
      p_ipt_var->prev_node->next_node = p_ipt_var->next_node;
      p_ipt_var->next_node->prev_node = p_ipt_var->prev_node;
    }
  }

  // if only one item in list
  else {
    variable_last_node = NULL;
  }

  // set global variable count
  variable_cnt--;

  // free allocated space
  free(p_ipt_var);
}





// print all values of variable
void var_print(char *ipt_var_name){

  struct var *p_var = var_find_by_name(ipt_var_name);
  if(p_var == NULL){
    return;
  }


  printf("\n");
  printf("---- DEBUG VARIABLE: %s\n",p_var->name);
  printf("Name: %s\n",p_var->name);
  printf("Type: %d\n",(int)p_var->type);
  printf("Val Int: %d\n",p_var->value_integer);
  printf("Val Float: %f\n",p_var->value_float);
  printf("Val String: %s\n",p_var->value_string);
  printf("Val Boolean: %d\n",p_var->value_boolean);
  printf("prev_node: %p\n",p_var->prev_node);
  printf("self_node: %p\n",p_var);
  printf("next_node: %p\n",p_var->next_node);
  printf("\n");
}





void var_print_all(){
  struct var *p_var = variable_last_node;

	while(p_var != NULL){
		printf("\n");
    printf("---- DEBUG VARIABLE: %s\n",p_var->name);
    printf("Name: %s\n",p_var->name);
    printf("Type: %d\n",(int)p_var->type);
    printf("Val Int: %d\n",p_var->value_integer);
    printf("Val Float: %f\n",p_var->value_float);
    printf("Val String: %s\n",p_var->value_string);
    printf("Val Boolean: %d\n",p_var->value_boolean);
    printf("prev_node: %p\n",p_var->prev_node);
    printf("self_node: %p\n",p_var);
    printf("next_node: %p\n",p_var->next_node);
    printf("\n");

		p_var = (p_var->prev_node);
	}
}



// get data-type of value in string format
enum var_type var_get_value_type(char *ipt_value, struct var *p_ipt_var){

  char test[strlen(ipt_value)];
  strcpy(test,ipt_value);

  // ---- type boolean
  if(strcmp(test,"true")==0 || strcmp(test,"false")==0){
    // printf("Value is boolean: %s\n", ipt_value);
    return TYPE_BOOLEAN;
  }


  // ---- type string
  if(ipt_value[0]=='\'' || ipt_value[0]=='\"'){
    // printf("Value is string: %s\n", ipt_value);
    return TYPE_STRING;
  }

  // ---- check if type integer/float
  short is_float = 0; // value is 1 if dot occured first time in string

  // iterate through string
  for(char *w = ipt_value; *w!='\0'; w++){

    // if char is dot, if dot didn't occured before
    if(!is_float && *w=='.'){
      is_float = 1;
      continue;
    }

    // if char is not a digit: error,
    if(!isdigit(*w)){
      yyerror("Variable Value is not valid\n");
      return TYPE_EMPTY;
    }
  }

  // if value is float
  if(is_float){
    // printf("Value is float: %s\n", ipt_value);
    return TYPE_FLOAT;
  }

  // if value is not float: it is integer
  // printf("Value is integer: %s\n", ipt_value);
  return TYPE_INTEGER;
}




// fill variable with default values
void var_set_default(struct var *p_ipt_var){
  (*p_ipt_var).name = "";
  (*p_ipt_var).type = TYPE_INTEGER;
  (*p_ipt_var).value_integer = 0;
  (*p_ipt_var).value_float = 0;
  (*p_ipt_var).value_string = "";
  (*p_ipt_var).value_boolean = FALSE;
  (*p_ipt_var).prev_node = NULL;
}




// ---- set variable
void var_set(char *ipt_name, char *ipt_value){

  // delte variable data if existing
  /*
  if(var_find_by_name(ipt_name) != NULL){
    var_delete(var_find_by_name(ipt_name));
  }
  */

  // allocate new memory for variable
  var_alloc_memory();
  struct var *p_var = (p_variable+variable_cnt);

  // set variable struct to default value
  var_set_default(p_var);



  // ---- convert string value by type
  char test[strlen(ipt_value)];
  strcpy(test,ipt_value);
  enum var_type type = var_get_value_type(ipt_value, p_var); // get type by value
  switch(type){

    // type boolean
    case TYPE_BOOLEAN:
      p_var->value_boolean = TYPE_BOOLEAN;
      p_var->value_boolean = FALSE;
      if(strcmp(test,"true")==0){
        p_var->value_boolean = TRUE;
      }
      break;

    // type float
    case TYPE_FLOAT:
      p_var->value_float = atof(ipt_value);break;

    // type integer
    case TYPE_INTEGER:
      p_var->value_integer = atol(ipt_value);break;

    // type string
    case TYPE_STRING:
      p_var->value_string = ipt_value;break;
  }

  p_var->type = type; // set type
  p_var->name = ipt_name; // set name



  // ---- set nodes for linked list
  p_var->prev_node = variable_last_node; // previous node
  if(variable_last_node!=NULL){
    variable_last_node->next_node = p_var; // next node
  }
  variable_last_node = p_var; // gloabl last set node

  variable_cnt++; // increment global variable counter
}


void var_set_number(char *ipt_name, double ipt_value){
  char ret[50];
  float_to_string(ipt_value,ret);
  var_set(ipt_name, ret);
}


// debug
void main_var(void){

  var_set("abc", "'ABCabc'");
  var_print("abc");
  var_set("abc", "'TEXT'");
  var_print("abc");

}