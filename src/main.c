#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "http.h"
#include "html_parser.h"
#include "render.h"
#include "js_vm.h"
#include "asm/asm_api.h"

// Script-Executor deklarieren
void execute_scripts(HtmlNode *root);

// Lädt Datei in Speicher
static char *load_file(const char *path, size_t *out_size) {
    FILE *f = fopen(path, "rb");
    if (!f) {
        perror("fopen");
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (size <= 0) {
        fclose(f);
        return NULL;
    }
    char *buf = (char *)malloc(size + 1);
    fread(buf, 1, size, f);
    fclose(f);
    buf[size] = '\0';
    if (out_size) *out_size = (size_t)size;
    return buf;
}

// Trennt HTTP-Header vom Body
static char *extract_http_body(char *data) {
    char *p = strstr(data, "\r\n\r\n");
    if (!p) return data;
    return p + 4;
}

// ------------------------------------------------------------
// JS-Script-Executor
// ------------------------------------------------------------
void execute_scripts(HtmlNode *node) {
    if (!node) return;

    // Wenn es ein <script>-Tag ist
    if (node->type == NODE_TAG && node->tag_name && strcmp(node->tag_name, "script") == 0) {
        for (size_t i = 0; i < node->child_count; i++) {
            HtmlNode *child = node->children[i];
            if (child->type == NODE_TEXT && child->text) {
                js_run_placeholder(child->text);
            }
        }
    }

    // Rekursiv durch alle Kinder laufen
    for (size_t i = 0; i < node->child_count; i++) {
        execute_scripts(node->children[i]);
    }
}

// ------------------------------------------------------------
// MAIN
// ------------------------------------------------------------
int main(int argc, char **argv) {
    const char *host = NULL;
    const char *path = "/";
    const char *download_file = "download.html";
    const char *local_file = "test_pages/index.html";

    if (argc >= 2) {
        host = argv[1];
    }
    if (argc >= 3) {
        path = argv[2];
    }

    if (host) {
        printf("Fetching http://%s%s ...\n", host, path);
        if (http_get_to_file(host, path, download_file) != 0) {
            fprintf(stderr, "HTTP GET failed.\n");
            return 1;
        }
        local_file = download_file;
    } else {
        printf("No host given, using local file: %s\n", local_file);
    }

    size_t size = 0;
    char *data = load_file(local_file, &size);
    if (!data) {
        fprintf(stderr, "Could not load file: %s\n", local_file);
        return 1;
    }

    char *body = data;
    if (host) {
        body = extract_http_body(data);
    }

    HtmlNode *root = parse_html(body);

    // HTML anzeigen
    render_tree_text(root);

    // ✅ JavaScript ausführen
    execute_scripts(root);

    // Speicher freigeben
    free_html_tree(root);
    free(data);

    return 0;
}
