
#ifndef WEBSERVER_DRIVER_H
#define WEBSERVER_DRIVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/routes.h"

char * (* routes[])(char *);
char *get_response(char *s);

extern const char *GET_ROUTES[];
extern const char *POST_ROUTES[];
extern const char *PUT_ROUTES[];
extern const char *DELETE_ROUTES[];


#endif //WEBSERVER_DRIVER_H
