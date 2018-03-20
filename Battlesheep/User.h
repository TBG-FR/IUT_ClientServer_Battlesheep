
#ifndef BATTLESHIP_USER

#include <string>
#include <iostream>

using namespace std;

class User {

private:
	string username;
	string password;

public:
	User();
	User(string login, string pass);
	~User();

	string getUsername();
	string getPassword();

};

#endif

