#ifndef EXERCICE1_H
#define EXERCICE1_H

/* ----- ----- INCLUDES ----- ----- */

#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>
#include <wait.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <thread>

#include "sema.h"

/* ----- ----- FUNCTIONS ----- ----- */

int exercice1(void);
void pool_management(int socket);
void daytime_thread(int socket);

#endif // EXERCICE1_H
