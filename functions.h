#include <stdio.h>     /* C declarations used in actions */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void debug(char *ipt_message){
  char res[100] = "<< ";
  strcat(res, ipt_message);
  strcat(res, "\n");
  fputs(res, stderr);
}

void str_to_lower(char s[]){
  int c = 0;
  char ret[strlen(s)];
  for(int c=0;s[c] != '\0';c++) {
    s[c] = tolower(s[c]);
  }
}

void str_delete_at_index(char *ipt_str, int ipt_index){
  char ret[50];
  for(int i = 0, f = 0; ipt_str[i] != '\0'; i++,f++){
    if(i == ipt_index){ f--;continue; }
    ret[f] = ipt_str[i];
  }
  strcpy(ipt_str,ret);
}

void float_to_string(double ipt_1, char *ret){
  char output_1[50];

  snprintf(output_1, 50, "%f", ipt_1);
  strcpy(ret,output_1);
}

char* str_combine(const char *s1, const char *s2){
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}