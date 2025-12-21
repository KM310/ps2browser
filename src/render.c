#include "render.h"
#include <stdio.h>

static void render_node(HtmlNode *node, int depth) {
    // Einrückung für Baumstruktur
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    if (node->type == NODE_TEXT) {
        if (node->text && node->text[0] != '\0') {
            printf("%s\n", node->text);
        }
    } else if (node->type == NODE_TAG) {
        printf("<%s>\n", node->tag_name ? node->tag_name : "unknown");
    }

    // Kinder rendern
    for (size_t i = 0; i < node->child_count; i++) {
        render_node(node->children[i], depth + 1);
    }
}

void render_tree_text(HtmlNode *root) {
    if (!root) {
        printf("[Renderer] No HTML tree.\n");
        return;
    }

    printf("=== Rendered HTML Tree ===\n");
    render_node(root, 0);
    printf("=== End ===\n");
}
