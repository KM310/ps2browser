#ifndef JS_VM_H
#define JS_VM_H

#include "html_parser.h"

void js_run_placeholder(const char *code);
void js_run_external(const char *src);
void execute_scripts(HtmlNode *root);

#endif
