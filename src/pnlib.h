#ifndef PNLIB_H
#define PNLIB_H

int bin_eval(int n1, int n2, char op);
int opred(const char c);
void reformat(const char* expr, char* buf);
void c_to_str(const char c, char* buf);
void infix_rpn(const char* expr, char* rpn_expr[]);
bool op_ge(const char op_a, const char op_b);
bool op_gt(const char op_a, const char op_b);
bool is_str_numeral(const char* str);
long postfix_eval(char* postfix[]);

#endif