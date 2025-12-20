#ifndef HTML_PARSER_H
#define HTML_PARSER_H

#include <stddef.h>

typedef enum {
    NODE_TEXT,
    NODE_TAG
} NodeType;

typedef struct HtmlNode {
    NodeType type;
    char *tag_name;       // NULL bei Text
    char *text;           // Nur bei TEXT-Knoten
    struct HtmlNode **children;
    size_t child_count;
} HtmlNode;

// Parsed nur sehr einfaches HTML (ohne Attribute, ohne korrektes DOM)
HtmlNode *parse_html(const char *html);

// Gibt kompletten Baum frei
void free_html_tree(HtmlNode *node);

#endif
