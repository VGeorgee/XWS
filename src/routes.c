#include "../include/routes.h"
#include "../include/status_codes.h"

int get_length(char **headers, char *body){
    int buffer_length = sizeof(uint32_t);
    if(headers){
        int i;
        for(i = 0; headers[i]; i++){
            buffer_length += strlen(headers[i]);
        }
        buffer_length += i * 3;
    }
    if(body){
        buffer_length += strlen(body);
    }
    return buffer_length;
}

/**
 *
 * @param status_code status code of the generated response
 * @param headers
 * @param body
 * @return response
 */
char *parse_response(const char status_code[], char **headers, char *body){
    int buffer_length = get_length(headers, body);
    char *response = calloc(buffer_length + 200, sizeof(uint8_t));
    sprintf(response, "HTTP/1.1 %s\r\nContent-Type: text/html; charset=UTF-8\r\n", status_code);
    char length[50] = {0};
    sprintf(length, "Content-Length: %d\r\n", strlen(body));
    strcat(response, length);
    if(headers){
        for(int i = 0; headers[i]; i++){
            strcat(response, headers[i]);
            strcat(response, "\r\n");
        }
    }
    strcat(response, "\r\n");
    strcat(response, body);
    free(body);
    return response;
}

char *demofunction(char *s){
    char *html = malloc(1000);
    strcpy(html, "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n<!DOCTYPE html><html><head><title>Henlo</title>\n<style>body { background-color: #000 }\nh1 { font-size:6cm; text-align: center; color: white;\ntext-shadow: 0 0 2mm white}</style></head>\n<body><h1>Hello, world!</h1></body></html>\r\n");

    return html;
}

char *favicon(char *s){
    /*
    char *buffer = calloc(20000, sizeof(char));
    FILE *icon = fopen("favicon.ico", "r");
    for(int i = 0; fscanf(icon, "%c",  &buffer[i++]) != EOF;);
     */
    char *resp = malloc(100);
    strcpy(resp, "");
    return parse_response(STATUSCODE_OK_SUCCESS_HEADER, NULL, resp);
}

char *simple_response(char *s){
    char *html = malloc(1000);
    strcpy(html, "simple response");
    return parse_response(STATUSCODE_OK_SUCCESS_HEADER, NULL, html);
}
