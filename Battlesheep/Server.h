#ifndef BATTLESHIP_SERVER

#include "UserStorage.h"
#include "Requests.h"
#include "Protocol_Messages.h"
#include "Status.h"
#include "Tools.h"

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
#include <thread>
#include <iostream>
#include <vector>

using namespace std;

/*class Server {

	// Server related methods (all static)
  public:*/
	void pool_management(int socket);
	//void client_management(int socket);
	void add_player(int socket, int player);
	void server_behavior(int socket, int player);
	//char* server_reception(int socket, int args_it);
	//bool server_reception(int socket, int args_it, char* args);
	//bool server_reception(int socket, vector<string> &args);
	bool server_reception(int socket, vector<string> &args, int min_args, int max_args);
	//vector<string> server_reception(int socket);

	void server_return(int message);
	//bool parser(int argc, char *argv[]);
	//bool parser(vector<string> args);

	bool registration(string username, string password, bool second_step);
	bool authentification(string username, string password);

	// Disallow creating an instance of this object
  /*private:
	Server();
	~Server();
};*/

#endif