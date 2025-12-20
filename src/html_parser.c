#include "html_parser.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static HtmlNode *alloc_node(NodeType type) {
    HtmlNode *n = (HtmlNode *)calloc(1, sizeof(HtmlNode));
    n->type = type;
    return n;
}

static void add_child(HtmlNode *parent, HtmlNode *child) {
    parent->children = (HtmlNode **)realloc(
        parent->children,
        sizeof(HtmlNode *) * (parent->child_count + 1)
    );
    parent->children[parent->child_count++] = child;
}

static char *strndup_simple(const char *s, size_t len) {
    char *r = (char *)malloc(len + 1);
    memcpy(r, s, len);
    r[len] = '\0';
    return r;
}

static char *trim_tagname(const char *start, const char *end) {
    while (start < end && isspace((unsigned char)*start)) start++;
    while (end > start && isspace((unsigned char)*(end - 1))) end--;
    return strndup_simple(start, end - start);
}

HtmlNode *parse_html(const char *html) {
    HtmlNode *root = alloc_node(NODE_TAG);
    root->tag_name = strndup_simple("root", 4);

    const char *p = html;
    const char *text_start = p;

    while (*p) {
        if (*p == '<') {
            // Text bis hier
            if (p > text_start) {
                HtmlNode *t = alloc_node(NODE_TEXT);
                t->text = strndup_simple(text_start, p - text_start);
                add_child(root, t);
            }

            const char *tag_start = p + 1;
            const char *tag_end = strchr(tag_start, '>');
            if (!tag_end) break;

            HtmlNode *tag = alloc_node(NODE_TAG);
            tag->tag_name = trim_tagname(tag_start, tag_end);
            add_child(root, tag);

            p = tag_end + 1;
            text_start = p;
        } else {
            p++;
        }
    }

    if (p > text_start) {
        HtmlNode *t = alloc_node(NODE_TEXT);
        t->text = strndup_simple(text_start, p - text_start);
        add_child(root, t);
    }

    return root;
}

void free_html_tree(HtmlNode *node) {
    if (!node) return;

    for (size_t i = 0; i < node->child_count; i++) {
        free_html_tree(node->children[i]);
    }
    free(node->children);

    free(node->tag_name);
    free(node->text);
    free(node);
}
