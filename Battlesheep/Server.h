#ifndef BATTLESHIP_SERVER

#include "UserStorage.h"
#include "Requests.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

#define MYPORT 3490    // Port du point de connexion
#define BACKLOG 10     // Combien de connexion en attente autorise-t-on ?
#define MAXDATASIZE 100 // Nombre maximal d'octer a envoyer en une fois

#define NB_THREADS 2 // Nombre de Threads dans notre Pool

class Server {

private:
	UserStorage userDatabase;

public:
	Server();
	~Server();

	void pool_management(int socket);
	void client_management(int socket);

	bool parser(int argc, char *argv[]);
	
	bool registration(string username, string password, bool second_step);
	bool authentification(string username, string password);

};

#endif
