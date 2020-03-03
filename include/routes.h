
#ifndef WEBSERVER_ROUTES_H
#define WEBSERVER_ROUTES_H

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#define ROUTE(x) char *x(char *);

char *demofunction(char *);
char *simple_response(char *);
char *favicon(char *s);
ROUTE(get_leaderboard)
ROUTE(post_leaderboard)

#endif //WEBSERVER_ROUTES_H
