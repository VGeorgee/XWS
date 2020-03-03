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
char *parse_response(const char status_code[], char *headers[], char *body){
    int buffer_length = get_length(headers, body);
    char *response = calloc(buffer_length + 200, sizeof(uint8_t));
    //Content-Type: text/html; charset=UTF-8
    sprintf(response, "HTTP/1.1 %s\r\n", status_code);
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




////  ---------------------------------------------------------   LEADERBOARD

typedef struct leaderboard{
    char id[50];
    int  points;
}LEADERBOARD;

char *get_leaderboard(char *s){
    char *html = "{ \"1\":{\"id\": \"f24afgbv\", \"pts\": 124 }, \"2\":{\"id\": \"d41huthn\", \"pts\": 37 }}";
    char *t[] = {"Content-Type: text/json; charset=UTF-8", NULL};


    FILE *leaderboard = fopen("leaderboard.txt", "r");
    int i, length;

    LEADERBOARD board[50];
    for(i = 0; fscanf(leaderboard, "%s %d", &board[i].id, &board[i].points) != EOF; i++);
    fclose(leaderboard);
    length = i;
    puts("------------------------------ HENLO 1");
    char response[(sizeof(LEADERBOARD) + 50) * length ];
    strcpy(response, "{\n");
    puts("------------------------------ HENLO 2");

    for(i = 0; i < length - 1; i++){
        char onearray[100] = { 0 };
        sprintf(onearray, "\"%d\":{\"%s\": %d},\n", i, board[i].id, board[i].points);
        strcat(response, onearray);
    }
    char onearray[100] = { 0 };
    sprintf(onearray, "\"%d\":{\"%s\": %d}\n}", i, board[i].id, board[i].points);
    strcat(response, onearray);



    puts("------------------------------ HENLO 4");
    return parse_response(STATUSCODE_OK_SUCCESS_HEADER, t, strdup(response));
}


int cmpbrd(const void *a, const void *b){
    LEADERBOARD *pa = (LEADERBOARD *) a;
    LEADERBOARD *pb = (LEADERBOARD *) b;
    puts("IM IN CMPBRD!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    if(pa->points != pb->points){
        return pa->points - pb->points;
    }
    return strcmp(pa->id, pb->id);
}

char *post_leaderboard(char *s) {
    puts("HENLO IM IN POST LEADERBOARD");
    char html[] = "{ f24afgbv 24\r\nd41huthn 37 }";
    char *t[] = {"Content-Type: text/json; charset=UTF-8", NULL};

    printf("HENLO0\n");
    FILE *leaderboard = fopen("leaderboard.txt", "w+");
    int size_of_leaderboard;
    fseek(leaderboard, 0, SEEK_END);

    printf("HENLO01\n");
    char *player_a_id, *player_b_id;
    int player_a_points, player_b_points;

    printf("AJAJAJAJAJAJAJAAJAJJAJAJAJAJJAJAAJJAAJ: %s\n\n", strtok(html, " "));
    player_a_id = strtok(NULL, " \r\n");
    player_a_points = atoi(strtok(NULL, " \r\n"));

    player_b_id = strtok(NULL, " \r\n");
    player_b_points = atoi(strtok(NULL, " \r\n"));

    printf("HENLO1\n");
    size_of_leaderboard = ftell(leaderboard);
    int i, length;
    LEADERBOARD board[50];
    puts("HENLO 2");
    for(i = 0; fscanf(leaderboard, "%s %d", &board[i].id, &board[i].points) != EOF; i++);
    length = i;
    int a_player_exists = 0, b_player_exists = 0;

    puts("HENLO 3");
    for(i = 0; i < length; i++){
        if(strcmp(board[i].id, player_a_id) == 0){
            board[i].points += player_a_points;
            a_player_exists = 1;
        }
        if(strcmp(board[i].id, player_b_id) == 0){
            board[i].points += player_b_points;
            b_player_exists = 1;
        }
    }

    puts("HENLO 4");
    if(!a_player_exists){
        strcpy(&board[length].id, player_a_id);
        board[length++].points = player_a_points;
    }
    if(!b_player_exists){
        strcpy(&board[length].id, player_b_id);
        board[length++].points = player_b_points;
    }
    puts("HENLO 5");
    qsort(board, length, sizeof(LEADERBOARD), cmpbrd);

    puts("HENLO 6");

    fseek(leaderboard, 0, SEEK_SET);

    puts("HENLO 7");
    for(i = 0; i < length; i++){
        fprintf(leaderboard, "%s %d\n", board[i].id, board[i].points);
    }
    fclose(leaderboard);

    puts("HENLO 8");
    /*
    char response[(sizeof(LEADERBOARD) + 20)* length ];
    strcpy(response, "{\n");
    for(i = 0; i < length; i++){
        char onearray[100] = { 0 };
        sprintf(onearray, "\"%d\":{\"%s\", %d}\n", board[i].id, board[i].points);
        strcat(response, onearray);
    }
    strcat(response, "}");

    */

    return parse_response(STATUSCODE_OK_SUCCESS_HEADER, t, strdup("{ \"message\":\"OK\" }"));
}
////  ---------------------------------------------------------   LEADERBOARD