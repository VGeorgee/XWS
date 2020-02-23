#include <stdio.h>
#include <unistd.h>

#include "../include/driver.h"
#include "../include/configuration.h"


#define LOG(s) printf("[LOG]:\t%s\n", s);

int main(int argc, char **argv) {
    int default_port;

    if(argc == 2){
        default_port = atoi(argv[1]);
    } else {
        default_port = DEFAULT_PORT;
    }


    int one = 1, client_fd;
    struct sockaddr_in svr_addr, cli_addr;
    socklen_t sin_len = sizeof(cli_addr);

#if OSTYPE == 2
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return 0;
    }
#endif

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 1) return 0;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));

    int port = default_port;
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_addr.s_addr = INADDR_ANY;
    svr_addr.sin_port = htons(port);

    if (bind(sock, (struct sockaddr *) &svr_addr, sizeof(svr_addr)) == -1) {
        close(sock);
    }
    printf("RUNNING SERVER\n");
    listen(sock, 1000);
    char input_buffer[DEFAULT_BUFFER_SIZE];
    while (1) {
        LOG("WAITING TO ACCEPT CLIENT");
        client_fd = accept(sock, (struct sockaddr *) &cli_addr, &sin_len);
        LOG("WAITING TO RECIEVE DATA");
        recv(client_fd, input_buffer, 1000, 0);
        LOG("REQUEST------------------------------------------------------------")
        puts(input_buffer);
        LOG("REQUEST------------------------------------------------------------")
        LOG("DATA RECIEVED");
        if (client_fd == -1) {
            perror("Can't accept");
            continue;
        }
        char *response = get_response(input_buffer);
        LOG("RESPONSE-----------------------------------------------------------")
        puts(response);
        LOG("RESPONSE-----------------------------------------------------------")
        send(client_fd, response, strlen(response), 0); /*-1:'\0'*/
        close(client_fd);
        LOG("DONE");
    }
}
