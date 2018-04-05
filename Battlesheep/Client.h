#ifndef BATTLESHIP_CLIENT

// includes ?

using namespace std;

/*class Client {

	// Client related methods
  public:*/
	int client_main(/*int socket*/);

	int client_reception(int socket, vector<string> &args);
	bool parser(int argc, char *argv[]);
	//bool parser(vector<string> args);

	//bool registration(string username, string password, bool second_step);
	//bool authentification(string username, string password);

	// Disallow creating an instance of this object
  /*private:
	Client();
	~Client();
};*/

#endif
