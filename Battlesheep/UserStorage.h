#ifndef BATTLESHIP_STORAGE

#include <vector>
#include "User.h"

using namespace std;

class UserStorage {

private:
	int size;
	vector<User> users;

public:
	UserStorage();
	~UserStorage();

	bool addUser(User user);
	bool removeUser(User user);
	User findUser(string username);

	User getUser();


};

#endif
