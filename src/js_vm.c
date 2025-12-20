#include "js_vm.h"
#include "html_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------------------------------------------------------------
// Inline JavaScript execution
// ------------------------------------------------------------
void js_run_placeholder(const char *code) {
    printf("[JS] Running inline script:\n%s\n", code);
}

// ------------------------------------------------------------
// External JavaScript loader
// ------------------------------------------------------------
static char *load_js_file(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buf = malloc(size + 1);
    fread(buf, 1, size, f);
    buf[size] = '\0';
    fclose(f);
    return buf;
}

void js_run_external(const char *src) {
    char path[256];
    snprintf(path, sizeof(path), "test_pages/%s", src);

    char *code = load_js_file(path);
    if (!code) {
        printf("[JS] Could not load external script: %s\n", src);
        return;
    }

    printf("[JS] Running external script: %s\n", src);
    js_run_placeholder(code);
    free(code);
}

// ------------------------------------------------------------
// Script executor for HTML tree
// ------------------------------------------------------------
void execute_scripts(HtmlNode *node) {
    if (!node) return;

    // Check for <script> tag
    if (node->type == NODE_TAG && node->tag_name &&
        strcmp(node->tag_name, "script") == 0) {

        // External script: <script src="file.js">
        if (node->attr_src) {
            js_run_external(node->attr_src);
        }
        // Inline script: <script> ... </script>
        else {
            for (size_t i = 0; i < node->child_count; i++) {
                HtmlNode *child = node->children[i];
                if (child->type == NODE_TEXT && child->text)
                    js_run_placeholder(child->text);
            }
        }
    }

    // Continue scanning the HTML tree
    for (size_t i = 0; i < node->child_count; i++)
        execute_scripts(node->children[i]);
}
