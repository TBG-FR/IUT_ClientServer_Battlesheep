
#ifndef BATTLESHIP_SERVER

#include "UserStorage.h"
#include "Requests.h"

class Server {

private:
	UserStorage userDatabase;

public:
	Server();
	~Server();

	bool parser(int argc, char *argv[]);

	bool registration(string username, string password, bool second_step);

	bool authentification(string username, string password);

};

#endif
