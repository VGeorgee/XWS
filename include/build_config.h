#ifndef WEBSERVER_BUILD_CONFIG_H
#define WEBSERVER_BUILD_CONFIG_H


#if defined(linux) || defined(_linux) || defined(__linux__) || defined(__unix__)
#define OSTYPE 1
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#elif defined(_WIN32) || defined(_WINDOWS) || defined(__WINDOWS__)
#define OSTYPE 2
#include <winsock2.h>
#include <Ws2tcpip.h>
#elif defined(MSDOS) || defined(_MSDOS) || defined(__MSDOS__)
#define OSTYPE 3
#elif (defined(__MACH__) && defined(__APPLE__))
  #define OSTYPE 4
  #include <sys/socket.h>
  #include <stdlib.h>
  #include <netinet/in.h>
#else
  #define OSTYPE 0
#endif

#define DEFAULT_PORT 80
#define DEFAULT_BUFFER_SIZE 40000


#endif //WEBSERVER_BUILD_CONFIG_H
