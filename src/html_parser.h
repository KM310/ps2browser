#ifndef HTML_PARSER_H
#define HTML_PARSER_H

#include <stddef.h>

typedef enum {
    NODE_TEXT,
    NODE_TAG
} NodeType;

typedef struct HtmlNode {
    NodeType type;
    char *tag_name;
    char *text;

    // NEW: simple attribute support
    char *attr_src;

    struct HtmlNode **children;
    size_t child_count;
} HtmlNode;

HtmlNode *parse_html(const char *html);
void free_html_tree(HtmlNode *node);

#endif

