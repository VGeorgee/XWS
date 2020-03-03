#include "../include/driver.h"


/// GET ROUTE DEFINITION
const char *GET_ROUTES[] = {
        "/demofunction",
        "/simple",
        "/favicon.ico",
        "/api/leaderboard",
        NULL
};
/// GET ROUTE FUNCTIONS
char * (* GET[])(char *) = {
        demofunction,
        simple_response,
        favicon,
        get_leaderboard,
        NULL
};


/// POST ROUTE DEFINITION
const char *POST_ROUTES[] = {
        "/api/leaderboard",
        NULL
};
/// POST ROUTE FUNCTIONS
char * (* POST[])(char *) = {
        post_leaderboard,
        NULL
};


/// PUT ROUTE DEFINITION
const char *PUT_ROUTES[] = {
        NULL
};
/// PUT ROUTE FUNCTIONS
char * (* PUT[])(char *) = {
        NULL
};


/// DELETE ROUTE DEFINITION
const char *DELETE_ROUTES[] = {
        NULL
};
/// DELETE ROUTE FUNCTIONS
char * (* DELETE[])(char *) = {
        NULL
};

/// ------- ROUTE FUNCTION DEFINITIONS

char *(**array_of_types[])(char *)  = {
        GET,
        POST,
        PUT,
        DELETE
};

char *response_parser(char *HEAD, char **headers, char *response_body){

}

char * _get_response(char *(*aot[])(char *), char *routes[], char *body, char *route){
    //printf("POINTER OF ARRAY OF FUNCTIONS:|||%p|||\n", aot);
    for(int i = 0; (* aot[i]) && routes[i]; i++ ){
        //printf("|||%s|||\n|||%s|||\n", routes[i], route);
        if(strcmp(routes[i], route) == 0){
            return (*aot[i])(body);
        }
    }
    return NULL;
}

char default_response[];

char *get_response(char *s){
    char request[10000];
    strcpy(request, s);

    char *type = strtok(request, " ");
    char *route = strtok(NULL, " ");

    if(strcmp(route, "/exit") == 0)
        exit(0);

    //printf("\n||%s||\n", type);
    char *response = NULL;
    if(strcmp(type, "GET") == 0){
        response = _get_response(&GET, GET_ROUTES,"asd", route);
    } else if(strcmp(type, "POST") == 0){
        response = _get_response(POST, POST_ROUTES,"asd", route);
    } else if(strcmp(type, "PUT") == 0){
        response = _get_response(PUT, PUT_ROUTES,"asd", route);
    } else if(strcmp(type, "DELETE" == 0)){
        response = _get_response(DELETE, DELETE_ROUTES,"asd", route);
    }
   // printf("//%p//\n", response);
    return response ? response : strdup(default_response);
}

char default_response[] = "HTTP/1.1 200 OK\r\n"
                          "Content-Type: text/html; charset=UTF-8\r\n"
                          "Content-Length: 224\r\n\r\n"
                          "<!DOCTYPE html><html><head><title>Henlo</title>"
                          "<style>body { background-color: #666 }"
                          "h1 { font-size:4cm; text-align: center; color: black;"
                          " text-shadow: 0 0 2mm white}</style></head>"
                          "<body><h1>Hello, world!</h1></body></html>\r\n";
