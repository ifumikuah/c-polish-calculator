#ifndef PNLIB_H
#define PNLIB_H

int bin_eval(int n1, int n2, char op);
// int pn_eval(const char* expr);
int opred(const char c);
void reformat(const char* expr, char* buf);
void c_to_str(const char c, char* buf);
void infix_rpn(const char* expr, char* rpn_expr[]);

#endif