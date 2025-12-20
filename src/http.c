#include "http.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int http_get_to_file(const char *host, const char *path, const char *outfile) {
    int sockfd;
    struct hostent *he;
    struct sockaddr_in server;
    char request[1024];
    char buffer[4096];
    int bytes;
    FILE *f;

    he = gethostbyname(host);
    if (!he) {
        perror("gethostbyname");
        return -1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(80);
    memcpy(&server.sin_addr, he->h_addr_list[0], he->h_length);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return -1;
    }

    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect");
        close(sockfd);
        return -1;
    }

    snprintf(request, sizeof(request),
             "GET %s HTTP/1.0\r\n"
             "Host: %s\r\n"
             "User-Agent: ps2browser/0.1\r\n"
             "Connection: close\r\n"
             "\r\n",
             path, host);

    if (write(sockfd, request, strlen(request)) < 0) {
        perror("write");
        close(sockfd);
        return -1;
    }

    f = fopen(outfile, "wb");
    if (!f) {
        perror("fopen");
        close(sockfd);
        return -1;
    }

    // Header + Body lesen, erstmal komplett in die Datei
    while ((bytes = read(sockfd, buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, 1, bytes, f);
    }

    if (bytes < 0) {
        perror("read");
    }

    fclose(f);
    close(sockfd);

    return 0;
}
