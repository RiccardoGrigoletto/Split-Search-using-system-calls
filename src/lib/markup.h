//!Commenti e funzionalità in markup.c
#ifndef MARKUP
#define MARKUP


typedef int bool;
#define TRUE 1
#define FALSE 0

bool v_i(char opt,int ind_element,char** target,char** argv, int argc);
bool o(char opt,int ind_element,char** target,char** argv, int argc);
bool m(int ind_element,int* target,char** argv, int argc);
bool a(int* target);
bool check_obb_marks();
bool get_o();

#endif
